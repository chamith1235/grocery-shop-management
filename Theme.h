#pragma once
// Theme.h - light-blue theme + UI scale. Each form calls Theme::Apply(this)
// right after InitializeComponent().
//
//  * UiScale()  - make the whole UI bigger (2.0 = twice as big). If the window
//                 would not fit on the screen the scale is reduced automatically.
//  * Colours    - change the Color::FromArgb(...) values to restyle everything.
//  * Pictures   - loaded from the "images" folder next to the .exe:
//                   images\background.png  background of the normal screens
//                   images\login_side.png  picture on the left of the login screen
//                 Replace them with your own (e.g. AI-generated) pictures.

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class Theme abstract sealed
{
public:
	static double UiScale()   { return 1.0; }                              // 1.0 = normal size

	static Color Background() { return Color::FromArgb(232, 242, 252); }   // light blue window
	static Color Primary()    { return Color::FromArgb(41, 128, 214); }    // buttons, grid header
	static Color PrimaryHot() { return Color::FromArgb(30, 100, 175); }    // button hover
	static Color Danger()     { return Color::FromArgb(205, 80, 80); }     // delete
	static Color Neutral()    { return Color::FromArgb(110, 140, 170); }   // cancel / clear / exit
	static Color Text()       { return Color::FromArgb(25, 55, 95); }      // dark navy text

	static void Apply(Control^ c)
	{
		ApplyStyle(c);

		Form^ form = dynamic_cast<Form^>(c);
		if (form != nullptr)
		{
			double s = FitScale(form);
			if (s > 1.01)
			{
				form->AutoScaleMode = AutoScaleMode::None;     // we scale by hand, once
				ScaleFonts(form, (float)s);
				form->Scale(SizeF((float)s, (float)s));
			}
		}
	}

private:
	// biggest scale (up to UiScale) at which the form still fits the screen
	static double FitScale(Form^ f)
	{
		System::Drawing::Rectangle wa = Screen::PrimaryScreen->WorkingArea;
		double sw = (wa.Width * 0.96) / f->Width;
		double sh = (wa.Height * 0.94) / f->Height;
		double s = UiScale();
		if (sw < s) s = sw;
		if (sh < s) s = sh;
		return s;
	}

	static void ScaleFonts(Control^ c, float s)
	{
		c->Font = gcnew System::Drawing::Font(c->Font->FontFamily, c->Font->Size * s, c->Font->Style);

		DataGridView^ g = dynamic_cast<DataGridView^>(c);
		if (g != nullptr)
		{
			System::Drawing::Font^ hf = g->ColumnHeadersDefaultCellStyle->Font;
			if (hf != nullptr)
				g->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(hf->FontFamily, hf->Size * s, hf->Style);
			g->ColumnHeadersHeight = (int)(g->ColumnHeadersHeight * s);
			g->RowTemplate->Height = (int)(g->RowTemplate->Height * s);
		}

		for each (Control^ child in c->Controls)
			ScaleFonts(child, s);
	}

	static void ApplyStyle(Control^ c)
	{
		Form^ form = dynamic_cast<Form^>(c);
		if (form != nullptr)
		{
			form->BackColor = Background();
			form->ForeColor = Text();
			SetPicture(form, "background.png");
			try { form->Icon = System::Drawing::Icon::ExtractAssociatedIcon(Application::ExecutablePath); } catch (Exception^) {}
		}

		Panel^ p = dynamic_cast<Panel^>(c);
		if (p != nullptr)
		{
			if (p->Name == "pnlLeft")  { p->BackColor = Primary(); SetPicture(p, "login_side.png"); }
			if (p->Name == "pnlRight") { p->BackColor = Color::White; }
		}

		Button^ b = dynamic_cast<Button^>(c);
		if (b != nullptr) StyleButton(b);

		Label^ l = dynamic_cast<Label^>(c);
		if (l != nullptr) StyleLabel(l);

		DataGridView^ g = dynamic_cast<DataGridView^>(c);
		if (g != nullptr) StyleGrid(g);

		for each (Control^ child in c->Controls)
			ApplyStyle(child);
	}

	static void SetPicture(Control^ target, String^ fileName)
	{
		try
		{
			String^ path = Path::Combine(Application::StartupPath, "images", fileName);
			if (!File::Exists(path)) return;
			// read through a MemoryStream so the file is not locked
			MemoryStream^ ms = gcnew MemoryStream(File::ReadAllBytes(path));
			target->BackgroundImage = gcnew Bitmap(ms);
			target->BackgroundImageLayout = ImageLayout::Stretch;
		}
		catch (Exception^) {}
	}

	static void StyleLabel(Label^ l)
	{
		l->BackColor = Color::Transparent;
		String^ n = l->Name;
		if (n == "lblTitle")                           l->ForeColor = Primary();
		else if (n == "lblBrand" || n == "lblTagline") l->ForeColor = Color::White;
		else if (n == "lblSub")                        l->ForeColor = Neutral();
		else                                           l->ForeColor = Text();
	}

	static void StyleButton(Button^ b)
	{
		Color back = Primary();
		Color hot = PrimaryHot();
		String^ n = b->Name;
		if (n == "btnDelete") { back = Danger(); hot = Color::FromArgb(170, 60, 60); }
		else if (n == "btnCancel" || n == "btnClear" || n == "btnExit") { back = Neutral(); hot = Color::FromArgb(85, 115, 145); }

		b->FlatStyle = FlatStyle::Flat;
		b->FlatAppearance->BorderSize = 0;
		b->FlatAppearance->MouseOverBackColor = hot;
		b->BackColor = back;
		b->ForeColor = Color::White;
		b->Cursor = Cursors::Hand;
		b->UseVisualStyleBackColor = false;
	}

	static void StyleGrid(DataGridView^ g)
	{
		g->BackgroundColor = Color::White;
		g->BorderStyle = System::Windows::Forms::BorderStyle::None;
		g->GridColor = Color::FromArgb(210, 225, 240);
		g->EnableHeadersVisualStyles = false;
		g->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;

		g->ColumnHeadersDefaultCellStyle->BackColor = Primary();
		g->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
		g->ColumnHeadersDefaultCellStyle->SelectionBackColor = Primary();
		g->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
		g->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
		g->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
		g->ColumnHeadersHeight = 32;

		g->DefaultCellStyle->ForeColor = Text();
		g->DefaultCellStyle->SelectionBackColor = Color::FromArgb(180, 214, 245);
		g->DefaultCellStyle->SelectionForeColor = Text();
		g->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(243, 248, 254);
		g->RowTemplate->Height = 26;
	}
};
