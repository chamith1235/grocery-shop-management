#include "Database.h"
#include "Theme.h"
#include "LoginForm.h"
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace GroceryShop;

// Small dialog asking for the MySQL root password.
static bool AskPassword(String^ message, String^% password)
{
    Form^ f = gcnew Form();
    f->Text = "MySQL connection";
    f->ClientSize = System::Drawing::Size(420, 150);
    f->StartPosition = FormStartPosition::CenterScreen;
    f->FormBorderStyle = FormBorderStyle::FixedDialog;
    f->MaximizeBox = false;
    f->MinimizeBox = false;

    Label^ l = UI::Lbl(message, 15, 12);
    l->MaximumSize = System::Drawing::Size(390, 0);
    f->Controls->Add(l);

    TextBox^ t = UI::Txt(15, 80, 390);
    t->UseSystemPasswordChar = true;
    f->Controls->Add(t);

    Button^ ok = UI::Btn("Connect", 220, 108, 90);
    Button^ cancel = UI::Btn("Cancel", 315, 108, 90);
    ok->DialogResult = System::Windows::Forms::DialogResult::OK;
    cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    f->Controls->Add(ok);
    f->Controls->Add(cancel);
    f->AcceptButton = ok;
    f->CancelButton = cancel;

    Theme::Apply(f);
    bool accepted = (f->ShowDialog() == System::Windows::Forms::DialogResult::OK);
    password = t->Text;
    return accepted;
}

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    String^ password = "";
    String^ error = "";
    while (!Database::Connect(password, error))
    {
        if (!AskPassword("Could not connect to MySQL (user: root).\n" + error +
                         "\n\nEnter the MySQL root password:", password))
            return 1;
    }

    LoginForm^ login = gcnew LoginForm();
    if (login->ShowDialog() != System::Windows::Forms::DialogResult::OK)
    {
        Database::Disconnect();
        return 0;
    }

    Application::Run(gcnew MainForm());
    Database::Disconnect();
    return 0;
}
