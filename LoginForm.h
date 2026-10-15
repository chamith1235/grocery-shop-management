#pragma once
// Login screen shown before the main menu.
// Default account (created on first run): admin / admin123
//
// Designer form: right-click LoginForm.h -> View Designer.
// Layout: pnlLeft (picture + brand name) and pnlRight (the login box).

#include "Database.h"
#include "UiHelper.h"
#include "Theme.h"

namespace GroceryShop {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
			Theme::Apply(this);
			attempts = 0;
		}

	protected:
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^  pnlLeft;
	private: System::Windows::Forms::Label^  lblBrand;
	private: System::Windows::Forms::Label^  lblTagline;
	private: System::Windows::Forms::Panel^  pnlRight;
	private: System::Windows::Forms::Label^  lblTitle;
	private: System::Windows::Forms::Label^  lblSub;
	private: System::Windows::Forms::Label^  lblUser;
	private: System::Windows::Forms::Label^  lblPass;
	private: System::Windows::Forms::TextBox^  txtUser;
	private: System::Windows::Forms::TextBox^  txtPass;
	private: System::Windows::Forms::Button^  btnLogin;
	private: System::Windows::Forms::Button^  btnCancel;

	private:
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
		   int attempts;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
			this->pnlLeft = (gcnew System::Windows::Forms::Panel());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->lblTagline = (gcnew System::Windows::Forms::Label());
			this->lblBrand = (gcnew System::Windows::Forms::Label());
			this->pnlRight = (gcnew System::Windows::Forms::Panel());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->txtPass = (gcnew System::Windows::Forms::TextBox());
			this->txtUser = (gcnew System::Windows::Forms::TextBox());
			this->lblPass = (gcnew System::Windows::Forms::Label());
			this->lblUser = (gcnew System::Windows::Forms::Label());
			this->lblSub = (gcnew System::Windows::Forms::Label());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->pnlLeft->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->pnlRight->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlLeft
			// 
			this->pnlLeft->BackColor = System::Drawing::Color::SteelBlue;
			this->pnlLeft->Controls->Add(this->pictureBox2);
			this->pnlLeft->Controls->Add(this->pictureBox1);
			this->pnlLeft->Controls->Add(this->lblTagline);
			this->pnlLeft->Controls->Add(this->lblBrand);
			this->pnlLeft->Dock = System::Windows::Forms::DockStyle::Left;
			this->pnlLeft->Location = System::Drawing::Point(0, 0);
			this->pnlLeft->Name = L"pnlLeft";
			this->pnlLeft->Size = System::Drawing::Size(300, 440);
			this->pnlLeft->TabIndex = 1;
			this->pnlLeft->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &LoginForm::pnlLeft_Paint);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(54, 292);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(110, 101);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 3;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 50);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// lblTagline
			// 
			this->lblTagline->AutoSize = true;
			this->lblTagline->BackColor = System::Drawing::Color::Transparent;
			this->lblTagline->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTagline->ForeColor = System::Drawing::Color::White;
			this->lblTagline->Location = System::Drawing::Point(32, 193);
			this->lblTagline->Name = L"lblTagline";
			this->lblTagline->Size = System::Drawing::Size(199, 40);
			this->lblTagline->TabIndex = 1;
			this->lblTagline->Text = L"Manage products, customers\nand billing easily.";
			// 
			// lblBrand
			// 
			this->lblBrand->AutoSize = true;
			this->lblBrand->BackColor = System::Drawing::Color::Transparent;
			this->lblBrand->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBrand->ForeColor = System::Drawing::Color::White;
			this->lblBrand->Location = System::Drawing::Point(28, 69);
			this->lblBrand->Name = L"lblBrand";
			this->lblBrand->Size = System::Drawing::Size(150, 94);
			this->lblBrand->TabIndex = 0;
			this->lblBrand->Text = L"Grocery\nShop";
			// 
			// pnlRight
			// 
			this->pnlRight->BackColor = System::Drawing::Color::White;
			this->pnlRight->Controls->Add(this->btnCancel);
			this->pnlRight->Controls->Add(this->btnLogin);
			this->pnlRight->Controls->Add(this->txtPass);
			this->pnlRight->Controls->Add(this->txtUser);
			this->pnlRight->Controls->Add(this->lblPass);
			this->pnlRight->Controls->Add(this->lblUser);
			this->pnlRight->Controls->Add(this->lblSub);
			this->pnlRight->Controls->Add(this->lblTitle);
			this->pnlRight->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlRight->Location = System::Drawing::Point(300, 0);
			this->pnlRight->Name = L"pnlRight";
			this->pnlRight->Size = System::Drawing::Size(420, 440);
			this->pnlRight->TabIndex = 0;
			// 
			// btnCancel
			// 
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->Location = System::Drawing::Point(52, 346);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(310, 32);
			this->btnCancel->TabIndex = 7;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			// 
			// btnLogin
			// 
			this->btnLogin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLogin->Location = System::Drawing::Point(52, 292);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(310, 42);
			this->btnLogin->TabIndex = 6;
			this->btnLogin->Text = L"Login";
			this->btnLogin->UseVisualStyleBackColor = true;
			this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
			// 
			// txtPass
			// 
			this->txtPass->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtPass->Location = System::Drawing::Point(52, 230);
			this->txtPass->Name = L"txtPass";
			this->txtPass->Size = System::Drawing::Size(310, 27);
			this->txtPass->TabIndex = 5;
			this->txtPass->UseSystemPasswordChar = true;
			// 
			// txtUser
			// 
			this->txtUser->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtUser->Location = System::Drawing::Point(52, 170);
			this->txtUser->Name = L"txtUser";
			this->txtUser->Size = System::Drawing::Size(310, 27);
			this->txtUser->TabIndex = 4;
			// 
			// lblPass
			// 
			this->lblPass->AutoSize = true;
			this->lblPass->Location = System::Drawing::Point(52, 210);
			this->lblPass->Name = L"lblPass";
			this->lblPass->Size = System::Drawing::Size(53, 13);
			this->lblPass->TabIndex = 3;
			this->lblPass->Text = L"Password";
			// 
			// lblUser
			// 
			this->lblUser->AutoSize = true;
			this->lblUser->Location = System::Drawing::Point(52, 150);
			this->lblUser->Name = L"lblUser";
			this->lblUser->Size = System::Drawing::Size(55, 13);
			this->lblUser->TabIndex = 2;
			this->lblUser->Text = L"Username";
			// 
			// lblSub
			// 
			this->lblSub->AutoSize = true;
			this->lblSub->Location = System::Drawing::Point(52, 100);
			this->lblSub->Name = L"lblSub";
			this->lblSub->Size = System::Drawing::Size(120, 13);
			this->lblSub->TabIndex = 1;
			this->lblSub->Text = L"Please login to continue";
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTitle->Location = System::Drawing::Point(48, 55);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(203, 37);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Welcome back";
			// 
			// LoginForm
			// 
			this->AcceptButton = this->btnLogin;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnCancel;
			this->ClientSize = System::Drawing::Size(720, 440);
			this->Controls->Add(this->pnlRight);
			this->Controls->Add(this->pnlLeft);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Grocery Shop - Login";
			this->pnlLeft->ResumeLayout(false);
			this->pnlLeft->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->pnlRight->ResumeLayout(false);
			this->pnlRight->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void btnLogin_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			if (Database::Login(txtUser->Text, txtPass->Text))
			{
				this->DialogResult = System::Windows::Forms::DialogResult::OK;
				return;
			}
		}
		catch (Exception^ ex) { UI::Warn(ex->Message); return; }

		attempts++;
		if (attempts >= 3)
		{
			UI::Warn("Too many failed attempts.");
			this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			return;
		}
		UI::Warn("Wrong username or password. (" + (3 - attempts).ToString() + " attempts left)");
		txtPass->Clear();
		txtPass->Focus();
	}
	private: System::Void pnlLeft_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
};
}
