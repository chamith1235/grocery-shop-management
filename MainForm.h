#pragma once
// Screen 1: Main menu
// Designer form: right-click MainForm.h -> View Designer.

#include "UiHelper.h"
#include "Theme.h"
#include "ProductForm.h"
#include "CustomerForm.h"
#include "BillingForm.h"

namespace GroceryShop {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			Theme::Apply(this);
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  lblTitle;
	private: System::Windows::Forms::Button^  btnProducts;
	private: System::Windows::Forms::Button^  btnCustomers;
	private: System::Windows::Forms::Button^  btnBilling;
	private: System::Windows::Forms::Button^  btnExit;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->btnProducts = (gcnew System::Windows::Forms::Button());
			this->btnCustomers = (gcnew System::Windows::Forms::Button());
			this->btnBilling = (gcnew System::Windows::Forms::Button());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblTitle
			// 
			this->lblTitle->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTitle->Location = System::Drawing::Point(115, 23);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(169, 32);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Grocery Shop";
			// 
			// btnProducts
			// 
			this->btnProducts->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->btnProducts->Location = System::Drawing::Point(98, 85);
			this->btnProducts->Name = L"btnProducts";
			this->btnProducts->Size = System::Drawing::Size(200, 32);
			this->btnProducts->TabIndex = 1;
			this->btnProducts->Text = L"Manage Products";
			this->btnProducts->UseVisualStyleBackColor = true;
			this->btnProducts->Click += gcnew System::EventHandler(this, &MainForm::btnProducts_Click);
			// 
			// btnCustomers
			// 
			this->btnCustomers->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->btnCustomers->Location = System::Drawing::Point(98, 140);
			this->btnCustomers->Name = L"btnCustomers";
			this->btnCustomers->Size = System::Drawing::Size(200, 32);
			this->btnCustomers->TabIndex = 2;
			this->btnCustomers->Text = L"Manage Customers";
			this->btnCustomers->UseVisualStyleBackColor = true;
			this->btnCustomers->Click += gcnew System::EventHandler(this, &MainForm::btnCustomers_Click);
			// 
			// btnBilling
			// 
			this->btnBilling->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->btnBilling->Location = System::Drawing::Point(98, 196);
			this->btnBilling->Name = L"btnBilling";
			this->btnBilling->Size = System::Drawing::Size(200, 32);
			this->btnBilling->TabIndex = 3;
			this->btnBilling->Text = L"Billing / Sales";
			this->btnBilling->UseVisualStyleBackColor = true;
			this->btnBilling->Click += gcnew System::EventHandler(this, &MainForm::btnBilling_Click);
			// 
			// btnExit
			// 
			this->btnExit->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->btnExit->Location = System::Drawing::Point(98, 251);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(200, 32);
			this->btnExit->TabIndex = 4;
			this->btnExit->Text = L"Exit";
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(404, 341);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->btnBilling);
			this->Controls->Add(this->btnCustomers);
			this->Controls->Add(this->btnProducts);
			this->Controls->Add(this->lblTitle);
			this->MinimumSize = System::Drawing::Size(420, 380);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Grocery Shop Management";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void btnProducts_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ProductForm^ f = gcnew ProductForm();
		f->ShowDialog(this);
		delete f;
	}

	private: System::Void btnCustomers_Click(System::Object^  sender, System::EventArgs^  e)
	{
		CustomerForm^ f = gcnew CustomerForm();
		f->ShowDialog(this);
		delete f;
	}

	private: System::Void btnBilling_Click(System::Object^  sender, System::EventArgs^  e)
	{
		BillingForm^ f = gcnew BillingForm();
		f->ShowDialog(this);
		delete f;
	}

	private: System::Void btnExit_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->Close();
	}
	};
}
