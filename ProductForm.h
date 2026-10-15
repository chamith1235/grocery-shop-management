#pragma once
// Screen 2: Products (record type 1) - Add / View / Update / Delete
// Designer form: right-click ProductForm.h -> View Designer.

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
	using namespace System::Globalization;

	public ref class ProductForm : public System::Windows::Forms::Form
	{
	public:
		ProductForm(void)
		{
			InitializeComponent();
			Theme::Apply(this);
			selectedId = 0;
			cmbCategory->SelectedIndex = 0;
			LoadGrid();
		}

	protected:
		~ProductForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  lblName;
	private: System::Windows::Forms::Label^  lblCategory;
	private: System::Windows::Forms::Label^  lblPrice;
	private: System::Windows::Forms::Label^  lblQty;
	private: System::Windows::Forms::TextBox^  txtName;
	private: System::Windows::Forms::ComboBox^  cmbCategory;
	private: System::Windows::Forms::TextBox^  txtPrice;
	private: System::Windows::Forms::TextBox^  txtQty;
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
			this->lblCategory = (gcnew System::Windows::Forms::Label());
			this->lblPrice = (gcnew System::Windows::Forms::Label());
			this->lblQty = (gcnew System::Windows::Forms::Label());
			this->txtName = (gcnew System::Windows::Forms::TextBox());
			this->cmbCategory = (gcnew System::Windows::Forms::ComboBox());
			this->txtPrice = (gcnew System::Windows::Forms::TextBox());
			this->txtQty = (gcnew System::Windows::Forms::TextBox());
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
			// lblCategory
			//
			this->lblCategory->AutoSize = true;
			this->lblCategory->Location = System::Drawing::Point(20, 55);
			this->lblCategory->Name = L"lblCategory";
			this->lblCategory->Size = System::Drawing::Size(49, 13);
			this->lblCategory->TabIndex = 1;
			this->lblCategory->Text = L"Category";
			//
			// lblPrice
			//
			this->lblPrice->AutoSize = true;
			this->lblPrice->Location = System::Drawing::Point(20, 90);
			this->lblPrice->Name = L"lblPrice";
			this->lblPrice->Size = System::Drawing::Size(55, 13);
			this->lblPrice->TabIndex = 2;
			this->lblPrice->Text = L"Unit Price (Rs)";
			//
			// lblQty
			//
			this->lblQty->AutoSize = true;
			this->lblQty->Location = System::Drawing::Point(20, 125);
			this->lblQty->Name = L"lblQty";
			this->lblQty->Size = System::Drawing::Size(46, 13);
			this->lblQty->TabIndex = 3;
			this->lblQty->Text = L"Quantity";
			//
			// txtName
			//
			this->txtName->Location = System::Drawing::Point(110, 17);
			this->txtName->Name = L"txtName";
			this->txtName->Size = System::Drawing::Size(220, 20);
			this->txtName->TabIndex = 4;
			//
			// cmbCategory
			//
			this->cmbCategory->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCategory->FormattingEnabled = true;
			this->cmbCategory->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Grocery", L"Beverage", L"Household" });
			this->cmbCategory->Location = System::Drawing::Point(110, 52);
			this->cmbCategory->Name = L"cmbCategory";
			this->cmbCategory->Size = System::Drawing::Size(220, 21);
			this->cmbCategory->TabIndex = 5;
			//
			// txtPrice
			//
			this->txtPrice->Location = System::Drawing::Point(110, 87);
			this->txtPrice->Name = L"txtPrice";
			this->txtPrice->Size = System::Drawing::Size(220, 20);
			this->txtPrice->TabIndex = 6;
			this->txtPrice->TextChanged += gcnew System::EventHandler(this, &ProductForm::PriceOrQty_TextChanged);
			//
			// txtQty
			//
			this->txtQty->Location = System::Drawing::Point(110, 122);
			this->txtQty->Name = L"txtQty";
			this->txtQty->Size = System::Drawing::Size(220, 20);
			this->txtQty->TabIndex = 7;
			this->txtQty->TextChanged += gcnew System::EventHandler(this, &ProductForm::PriceOrQty_TextChanged);
			//
			// btnAdd
			//
			this->btnAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnAdd->Location = System::Drawing::Point(380, 17);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(100, 32);
			this->btnAdd->TabIndex = 8;
			this->btnAdd->Text = L"Add";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &ProductForm::btnAdd_Click);
			//
			// btnUpdate
			//
			this->btnUpdate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnUpdate->Location = System::Drawing::Point(490, 17);
			this->btnUpdate->Name = L"btnUpdate";
			this->btnUpdate->Size = System::Drawing::Size(100, 32);
			this->btnUpdate->TabIndex = 9;
			this->btnUpdate->Text = L"Update";
			this->btnUpdate->UseVisualStyleBackColor = true;
			this->btnUpdate->Click += gcnew System::EventHandler(this, &ProductForm::btnUpdate_Click);
			//
			// btnDelete
			//
			this->btnDelete->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnDelete->Location = System::Drawing::Point(600, 17);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(100, 32);
			this->btnDelete->TabIndex = 10;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &ProductForm::btnDelete_Click);
			//
			// btnClear
			//
			this->btnClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnClear->Location = System::Drawing::Point(710, 17);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(80, 32);
			this->btnClear->TabIndex = 11;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &ProductForm::btnClear_Click);
			//
			// lblInfo
			//
			this->lblInfo->AutoSize = true;
			this->lblInfo->Location = System::Drawing::Point(380, 70);
			this->lblInfo->MaximumSize = System::Drawing::Size(410, 0);
			this->lblInfo->Name = L"lblInfo";
			this->lblInfo->Size = System::Drawing::Size(238, 13);
			this->lblInfo->TabIndex = 12;
			this->lblInfo->Text = L"Select a product in the table to see its details.";
			//
			// grid
			//
			this->grid->AllowUserToAddRows = false;
			this->grid->AllowUserToDeleteRows = false;
			this->grid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->grid->Location = System::Drawing::Point(20, 170);
			this->grid->MultiSelect = false;
			this->grid->Name = L"grid";
			this->grid->ReadOnly = true;
			this->grid->RowHeadersVisible = false;
			this->grid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->grid->Size = System::Drawing::Size(764, 331);
			this->grid->TabIndex = 13;
			this->grid->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ProductForm::grid_CellClick);
			//
			// ProductForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(804, 521);
			this->Controls->Add(this->grid);
			this->Controls->Add(this->lblInfo);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnUpdate);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->txtQty);
			this->Controls->Add(this->txtPrice);
			this->Controls->Add(this->cmbCategory);
			this->Controls->Add(this->txtName);
			this->Controls->Add(this->lblQty);
			this->Controls->Add(this->lblPrice);
			this->Controls->Add(this->lblCategory);
			this->Controls->Add(this->lblName);
			this->MinimumSize = System::Drawing::Size(600, 400);
			this->Name = L"ProductForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Products";
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
				"SELECT id AS ID, name AS Name, category AS Category, price AS `Unit Price`, quantity AS Quantity, "
				"ROUND(price * quantity, 2) AS Total "
				"FROM products ORDER BY id");
		}

		// Builds an Item object from the text boxes. The Item's properties
		// validate the values and throw if something is wrong.
		// The price box is the UNIT price (price of one item).
		Item^ ReadForm()
		{
			if (cmbCategory->SelectedItem == nullptr) throw gcnew ArgumentException("Please choose a category.");
			double price;
			int qty;
			if (!Double::TryParse(txtPrice->Text, NumberStyles::Float, CultureInfo::InvariantCulture, price))
				throw gcnew ArgumentException("Unit price must be a number, e.g. 150.50");
			if (!Int32::TryParse(txtQty->Text, qty))
				throw gcnew ArgumentException("Quantity must be a whole number.");
			return ItemFactory::Create(cmbCategory->SelectedItem->ToString(), selectedId, txtName->Text, price, qty);
		}

		// live hint under the buttons: total = unit price x quantity
		void ShowTotal()
		{
			double price;
			int qty;
			if (Double::TryParse(txtPrice->Text, NumberStyles::Float, CultureInfo::InvariantCulture, price) &&
				Int32::TryParse(txtQty->Text, qty) && qty >= 0)
				lblInfo->Text = "Total = " + price.ToString("F2") + " x " + qty.ToString() + " = Rs " +
					(price * qty).ToString("F2");
		}

		void ClearForm()
		{
			selectedId = 0;
			txtName->Clear();
			txtPrice->Clear();
			txtQty->Clear();
			cmbCategory->SelectedIndex = 0;
			lblInfo->Text = "Select a product in the table to see its details.";
			grid->ClearSelection();
		}

	private: System::Void btnAdd_Click(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			Item^ it = ReadForm();
			Database::Execute(String::Format(
				"INSERT INTO products(name,category,price,quantity) VALUES('{0}','{1}',{2},{3})",
				gcnew array<Object^>{ Database::Esc(it->Name), it->GetCategory(),
					it->Price.ToString("F2", CultureInfo::InvariantCulture), it->Quantity }));
			LoadGrid();
			ClearForm();
		}
		catch (Exception^ ex) { UI::Warn(ex->Message); }
	}

	private: System::Void btnUpdate_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (selectedId == 0) { UI::Warn("Select a product from the table first."); return; }
		try
		{
			Item^ it = ReadForm();
			Database::Execute(String::Format(
				"UPDATE products SET name='{0}', category='{1}', price={2}, quantity={3} WHERE id={4}",
				gcnew array<Object^>{ Database::Esc(it->Name), it->GetCategory(),
					it->Price.ToString("F2", CultureInfo::InvariantCulture), it->Quantity, selectedId }));
			LoadGrid();
			ClearForm();
		}
		catch (Exception^ ex) { UI::Warn(ex->Message); }
	}

	private: System::Void btnDelete_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (selectedId == 0) { UI::Warn("Select a product from the table first."); return; }
		if (MessageBox::Show("Delete this product?", "Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Question)
			!= System::Windows::Forms::DialogResult::Yes) return;
		try
		{
			Database::Execute("DELETE FROM products WHERE id=" + selectedId.ToString());
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
		cmbCategory->SelectedItem = row->Cells[2]->Value->ToString();
		txtPrice->Text = row->Cells[3]->Value->ToString();
		txtQty->Text = row->Cells[4]->Value->ToString();

		// polymorphism: Describe() behaves differently for each category
		Item^ it = ReadForm();
		lblInfo->Text = it->Describe();
	}

	private: System::Void PriceOrQty_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		ShowTotal();
	}
	};
}
