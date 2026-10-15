#pragma once
// Database.h - small wrapper around the MySQL C API (libmysql).
// Everything the forms need: Connect, Execute (insert/update/delete), Query (select).

using namespace System;
using namespace System::Data;

public ref class Database abstract sealed
{
public:
    // Connects to MySQL on localhost as root, creates the grocery_shop
    // database + tables if they do not exist yet. Returns false and an
    // error message when the connection fails (e.g. wrong password).
    static bool Connect(String^ password, String^% error);
    static void Disconnect();

    static void Execute(String^ sql);          // throws Exception on SQL error
    static DataTable^ Query(String^ sql);      // all columns come back as text
    static String^ Esc(String^ text);          // escapes text for use inside '...'

    static String^ Hash(String^ text);         // SHA-256 hex, used for stored passwords
    static bool Login(String^ username, String^ password);   // checks the users table
};
