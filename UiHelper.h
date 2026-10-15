#pragma once
// UiHelper.h - tiny helpers so the forms stay short (forms are built in code).

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class UI abstract sealed
{
public:
    static Label^ Lbl(String^ text, int x, int y)
    {
        Label^ l = gcnew Label();
        l->Text = text;
        l->Location = Point(x, y);
        l->AutoSize = true;
        return l;
    }
    static TextBox^ Txt(int x, int y, int w)
    {
        TextBox^ t = gcnew TextBox();
        t->Location = Point(x, y);
        t->Width = w;
        return t;
    }
    static Button^ Btn(String^ text, int x, int y, int w)
    {
        Button^ b = gcnew Button();
        b->Text = text;
        b->Location = Point(x, y);
        b->Size = System::Drawing::Size(w, 32);
        return b;
    }
    static ComboBox^ Combo(int x, int y, int w)
    {
        ComboBox^ c = gcnew ComboBox();
        c->Location = Point(x, y);
        c->Width = w;
        c->DropDownStyle = ComboBoxStyle::DropDownList;
        return c;
    }
    static DataGridView^ Grid(int x, int y, int w, int h)
    {
        DataGridView^ g = gcnew DataGridView();
        g->Location = Point(x, y);
        g->Size = System::Drawing::Size(w, h);
        g->ReadOnly = true;
        g->AllowUserToAddRows = false;
        g->AllowUserToDeleteRows = false;
        g->MultiSelect = false;
        g->RowHeadersVisible = false;
        g->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        g->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        g->Anchor = AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right;
        return g;
    }
    static void Warn(String^ message)
    {
        MessageBox::Show(message, "Grocery Shop", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    }
    static void Info(String^ message)
    {
        MessageBox::Show(message, "Grocery Shop", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
};
