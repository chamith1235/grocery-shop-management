#pragma once
// Screen 3: Customers (record type 2) - Add / View / Update / Delete
// Designer form: right-click CustomerForm.h -> View Designer.

#include "Database.h"
#include "Models.h"
#include "UiHelper.h"
#include "Theme.h"

namespace GroceryShop {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Data;

	public ref class CustomerForm : public System::Windows::Forms::Form
	{
	public:
		CustomerForm(void)
		{
			InitializeComponent();
			Theme::Apply(this);
			selectedId = 0;
			cmbMembership->SelectedIndex = 0;
			LoadGrid();
		}

	protected:
		~CustomerForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  lblName;
	private: System::Windows::Forms::Label^  lblPhone;
	private: System::Windows::Forms::Label^  lblMembership;
	private: System::Windows::Forms::TextBox^  txtName;
	private: System::Windows::Forms::TextBox^  txtPhone;
	private: System::Windows::Forms::ComboBox^  cmbMembership;
	private: System::Windows::Forms::Button^  btnAdd;
	private: System::Windows::Forms::Button^  btnUpdate;
	private: System::Windows::Forms::Button^  btnDelete;
	private: System::Windows::Forms::Button^  btnClear;
	private: System::Windows::Forms::Label^  lblInfo;
	private: System::Windows::Forms::DataGridView^  grid;

	private:
		System::ComponentModel::Container ^components;
		int selectedId;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->lblPhone = (gcnew System::Windows::Forms::Label());
			this->lblMembership = (gcnew System::Windows::Forms::Label());
			this->txtName = (gcnew System::Windows::Forms::TextBox());
			this->txtPhone = (gcnew System::Windows::Forms::TextBox());
			this->cmbMembership = (gcnew System::Windows::Forms::ComboBox());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->btnUpdate = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->lblInfo = (gcnew System::Windows::Forms::Label());
			this->grid = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grid))->BeginInit();
			this->SuspendLayout();
			//
			// lblName
			//
			this->lblName->AutoSize = true;
			this->lblName->Location = System::Drawing::Point(20, 20);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(35, 13);
			this->lblName->TabIndex = 0;
			this->lblName->Text = L"Name";
			//
			// lblPhone
			//
			this->lblPhone->AutoSize = true;
			this->lblPhone->Location = System::Drawing::Point(20, 55);
			this->lblPhone->Name = L"lblPhone";
			this->lblPhone->Size = System::Drawing::Size(38, 13);
			this->lblPhone->TabIndex = 1;
			this->lblPhone->Text = L"Phone";
			//
			// lblMembership
			//
			this->lblMembership->AutoSize = true;
			this->lblMembership->Location = System::Drawing::Point(20, 90);
			this->lblMembership->Name = L"lblMembership";
			this->lblMembership->Size = System::Drawing::Size(64, 13);
			this->lblMembership->TabIndex = 2;
			this->lblMembership->Text = L"Membership";
			//
			// txtName
			//
			this->txtName->Location = System::Drawing::Point(110, 17);
			this->txtName->Name = L"txtName";
			this->txtName->Size = System::Drawing::Size(220, 20);
			this->txtName->TabIndex = 3;
			//
			// txtPhone
			//
			this->txtPhone->Location = System::Drawing::Point(110, 52);
			this->txtPhone->Name = L"txtPhone";
			this->txtPhone->Size = System::Drawing::Size(220, 20);
			this->txtPhone->TabIndex = 4;
			//
			// cmbMembership
			//
			this->cmbMembership->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbMembership->FormattingEnabled = true;
			this->cmbMembership->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Regular", L"Member" });
			this->cmbMembership->Location = System::Drawing::Point(110, 87);
			this->cmbMembership->Name = L"cmbMembership";
			this->cmbMembership->Size = System::Drawing::Size(220, 21);
			this->cmbMembership->TabIndex = 5;
			//
			// btnAdd
			//
			this->btnAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnAdd->Location = System::Drawing::Point(380, 17);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(100, 32);
			this->btnAdd->TabIndex = 6;
			this->btnAdd->Text = L"Add";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &CustomerForm::btnAdd_Click);
			//
			// btnUpdate
			//
			this->btnUpdate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnUpdate->Location = System::Drawing::Point(490, 17);
			this->btnUpdate->Name = L"btnUpdate";
			this->btnUpdate->Size = System::Drawing::Size(100, 32);
			this->btnUpdate->TabIndex = 7;
			this->btnUpdate->Text = L"Update";
			this->btnUpdate->UseVisualStyleBackColor = true;
			this->btnUpdate->Click += gcnew System::EventHandler(this, &CustomerForm::btnUpdate_Click);
			//
			// btnDelete
			//
			this->btnDelete->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnDelete->Location = System::Drawing::Point(600, 17);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(100, 32);
			this->btnDelete->TabIndex = 8;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &CustomerForm::btnDelete_Click);
			//
			// btnClear
			//
			this->btnClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnClear->Location = System::Drawing::Point(710, 17);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(80, 32);
			this->btnClear->TabIndex = 9;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &CustomerForm::btnClear_Click);
			//
			// lblInfo
			//
			this->lblInfo->AutoSize = true;
			this->lblInfo->Location = System::Drawing::Point(380, 70);
			this->lblInfo->MaximumSize = System::Drawing::Size(410, 0);
			this->lblInfo->Name = L"lblInfo";
			this->lblInfo->Size = System::Drawing::Size(246, 13);
			this->lblInfo->TabIndex = 10;
			this->lblInfo->Text = L"Select a customer in the table to see the details.";
			//
			// grid
			//
			this->grid->AllowUserToAddRows = false;
			this->grid->AllowUserToDeleteRows = false;
			this->grid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->grid->Location = System::Drawing::Point(20, 140);
			this->grid->MultiSelect = false;
			this->grid->Name = L"grid";
			this->grid->ReadOnly = true;
			this->grid->RowHeadersVisible = false;
			this->grid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->grid->Size = System::Drawing::Size(764, 321);
			this->grid->TabIndex = 11;
			this->grid->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &CustomerForm::grid_CellClick);
			//
			// CustomerForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(804, 481);
			this->Controls->Add(this->grid);
			this->Controls->Add(this->lblInfo);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnUpdate);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->cmbMembership);
			this->Controls->Add(this->txtPhone);
			this->Controls->Add(this->txtName);
			this->Controls->Add(this->lblMembership);
			this->Controls->Add(this->lblPhone);
			this->Controls->Add(this->lblName);
			this->MinimumSize = System::Drawing::Size(600, 400);
			this->Name = L"CustomerForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Customers";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grid))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	// ------------------------------------------------------------ code
	private:
		void LoadGrid()
		{
			grid->DataSource = Database::Query(
				"SELECT id AS ID, name AS Name, phone AS Phone, membership AS Membership FROM customers ORDER BY id");
		}

		Person^ ReadForm()
		{
			if (cmbMembership->SelectedItem == nullptr) throw gcnew ArgumentException("Please choose a membership type.");
			return PersonFactory::Create(cmbMembership->SelectedItem->ToString(), selectedId, txtName->Text, txtPhone->Text);
		}

		void ClearForm()
		{
			selectedId = 0;
			txtName->Clear();
			txtPhone->Clear();
			cmbMembership->SelectedIndex = 0;
			lblInfo->Text = "Select a customer in the table to see the details.";
			grid->ClearSelection();
		}

	private: System::Void btnAdd_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			Person^ p = ReadForm();
			Database::Execute(String::Format(
				"INSERT INTO customers(name,phone,membership) VALUES('{0}','{1}','{2}')",
				gcnew array<Object^>{ Database::Esc(p->Name), Database::Esc(p->Phone), p->GetMembership() }));
			LoadGrid();
			ClearForm();
		}
		catch (Exception^ ex) { UI::Warn(ex->Message); }
	}

	private: System::Void btnUpdate_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (selectedId == 0) { UI::Warn("Select a customer from the table first."); return; }
		try
		{
			Person^ p = ReadForm();
			Database::Execute(String::Format(
				"UPDATE customers SET name='{0}', phone='{1}', membership='{2}' WHERE id={3}",
				gcnew array<Object^>{ Database::Esc(p->Name), Database::Esc(p->Phone), p->GetMembership(), selectedId }));
			LoadGrid();
			ClearForm();
		}
		catch (Exception^ ex) { UI::Warn(ex->Message); }
	}

	private: System::Void btnDelete_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (selectedId == 0) { UI::Warn("Select a customer from the table first."); return; }
		if (MessageBox::Show("Delete this customer?", "Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			!= System::Windows::Forms::DialogResult::Yes) return;
		try
		{
			Database::Execute("DELETE FROM customers WHERE id=" + selectedId.ToString());
			LoadGrid();
			ClearForm();
		}
		catch (Exception^ ex) { UI::Warn(ex->Message); }
	}

	private: System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e)
	{
		ClearForm();
	}

	private: System::Void grid_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
		if (e->RowIndex < 0) return;
		DataGridViewRow^ row = grid->Rows[e->RowIndex];
		selectedId = Int32::Parse(row->Cells[0]->Value->ToString());
		txtName->Text = row->Cells[1]->Value->ToString();
		txtPhone->Text = row->Cells[2]->Value->ToString();
		cmbMembership->SelectedItem = row->Cells[3]->Value->ToString();

		// polymorphism: Describe() / GetDiscountRate() depend on the real class
		Person^ p = ReadForm();
		lblInfo->Text = p->Describe();
	}
	};
}
