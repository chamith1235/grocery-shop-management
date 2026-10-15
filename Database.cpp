#include <winsock2.h>
#include <mysql.h>
#include <string>
#include <cstring>
#include "Database.h"

using namespace System::Text;

static MYSQL* g_conn = nullptr;

static std::string ToUtf8(String^ s)
{
    array<Byte>^ b = Encoding::UTF8->GetBytes(s);
    std::string r(b->Length, '\0');
    if (b->Length > 0)
    {
        pin_ptr<Byte> p = &b[0];
        memcpy(&r[0], p, b->Length);
    }
    return r;
}

static String^ FromUtf8(const char* c, unsigned long len)
{
    if (c == nullptr) return "";
    return gcnew String((const char*)c, 0, (int)len, Encoding::UTF8);
}

bool Database::Connect(String^ password, String^% error)
{
    Disconnect();
    g_conn = mysql_init(nullptr);
    mysql_options(g_conn, MYSQL_SET_CHARSET_NAME, "utf8mb4");

    std::string pw = ToUtf8(password);
    if (!mysql_real_connect(g_conn, "localhost", "root", pw.c_str(), nullptr, 3306, nullptr, 0))
    {
        error = FromUtf8(mysql_error(g_conn), (unsigned long)strlen(mysql_error(g_conn)));
        mysql_close(g_conn);
        g_conn = nullptr;
        return false;
    }

    try
    {
        Execute("CREATE DATABASE IF NOT EXISTS grocery_shop CHARACTER SET utf8mb4");
        Execute("USE grocery_shop");
        Execute("CREATE TABLE IF NOT EXISTS products ("
                "id INT AUTO_INCREMENT PRIMARY KEY,"
                "name VARCHAR(100) NOT NULL,"
                "category VARCHAR(20) NOT NULL,"
                "price DECIMAL(10,2) NOT NULL,"
                "quantity INT NOT NULL)");
        Execute("CREATE TABLE IF NOT EXISTS customers ("
                "id INT AUTO_INCREMENT PRIMARY KEY,"
                "name VARCHAR(100) NOT NULL,"
                "phone VARCHAR(20),"
                "membership VARCHAR(10) NOT NULL)");
        Execute("CREATE TABLE IF NOT EXISTS sales ("
                "id INT AUTO_INCREMENT PRIMARY KEY,"
                "bill_no INT NOT NULL DEFAULT 0,"
                "customer_name VARCHAR(100) NOT NULL,"
                "product_name VARCHAR(100) NOT NULL,"
                "quantity INT NOT NULL,"
                "total DECIMAL(12,2) NOT NULL,"
                "sale_date DATETIME NOT NULL)");

        // older databases: add the bill number column
        if (Query("SHOW COLUMNS FROM sales LIKE 'bill_no'")->Rows->Count == 0)
            Execute("ALTER TABLE sales ADD COLUMN bill_no INT NOT NULL DEFAULT 0");

        Execute("CREATE TABLE IF NOT EXISTS users ("
                "id INT AUTO_INCREMENT PRIMARY KEY,"
                "username VARCHAR(50) NOT NULL UNIQUE,"
                "password_hash VARCHAR(64) NOT NULL)");
        if (Query("SELECT id FROM users LIMIT 1")->Rows->Count == 0)
            Execute("INSERT INTO users(username,password_hash) VALUES('admin','" + Hash("admin123") + "')");

        // sample data the first time the program runs
        if (Query("SELECT id FROM products LIMIT 1")->Rows->Count == 0)
        {
            Execute("INSERT INTO products(name,category,price,quantity) VALUES"
                    "('Rice 1kg','Grocery',240.00,50),"
                    "('Sugar 1kg','Grocery',260.00,40),"
                    "('Orange Juice','Beverage',350.00,30),"
                    "('Soap','Household',120.00,60)");
        }
        if (Query("SELECT id FROM customers LIMIT 1")->Rows->Count == 0)
        {
            Execute("INSERT INTO customers(name,phone,membership) VALUES"
                    "('Nimal Perera','0771234567','Regular'),"
                    "('Kamala Silva','0712345678','Member')");
        }
    }
    catch (Exception^ ex)
    {
        error = ex->Message;
        Disconnect();
        return false;
    }
    return true;
}

void Database::Disconnect()
{
    if (g_conn != nullptr)
    {
        mysql_close(g_conn);
        g_conn = nullptr;
    }
}

void Database::Execute(String^ sql)
{
    if (g_conn == nullptr) throw gcnew InvalidOperationException("Not connected to the database.");
    std::string q = ToUtf8(sql);
    if (mysql_real_query(g_conn, q.c_str(), (unsigned long)q.size()) != 0)
        throw gcnew Exception(FromUtf8(mysql_error(g_conn), (unsigned long)strlen(mysql_error(g_conn))));
}

DataTable^ Database::Query(String^ sql)
{
    Execute(sql);
    MYSQL_RES* res = mysql_store_result(g_conn);
    DataTable^ table = gcnew DataTable();
    if (res == nullptr) return table;

    unsigned int n = mysql_num_fields(res);
    MYSQL_FIELD* fields = mysql_fetch_fields(res);
    for (unsigned int i = 0; i < n; i++)
        table->Columns->Add(gcnew String(fields[i].name), String::typeid);

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr)
    {
        unsigned long* len = mysql_fetch_lengths(res);
        array<Object^>^ values = gcnew array<Object^>(n);
        for (unsigned int i = 0; i < n; i++)
            values[i] = FromUtf8(row[i], len[i]);
        table->Rows->Add(values);
    }
    mysql_free_result(res);
    return table;
}

String^ Database::Hash(String^ text)
{
    System::Security::Cryptography::SHA256^ sha = System::Security::Cryptography::SHA256::Create();
    array<Byte>^ h = sha->ComputeHash(Encoding::UTF8->GetBytes(text));
    StringBuilder^ sb = gcnew StringBuilder();
    for each (Byte b in h) sb->Append(b.ToString("x2"));
    return sb->ToString();
}

bool Database::Login(String^ username, String^ password)
{
    DataTable^ t = Query("SELECT id FROM users WHERE username='" + Esc(username) +
                         "' AND password_hash='" + Hash(password) + "'");
    return t->Rows->Count == 1;
}

String^ Database::Esc(String^ text)
{
    if (g_conn == nullptr || text == nullptr) return "";
    std::string u = ToUtf8(text);
    std::string out(u.size() * 2 + 1, '\0');
    unsigned long n = mysql_real_escape_string(g_conn, &out[0], u.c_str(), (unsigned long)u.size());
    return FromUtf8(out.c_str(), n);
}
