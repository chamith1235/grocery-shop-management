#pragma once
// Screen 4: Billing - one bill for one customer with MANY products.
//   1. choose the customer
//   2. choose a product + quantity and press "Add to Bill" (repeat for more products)
//   3. press "Complete Sale": stock is reduced, every line is saved under one
//      bill number, and the bill is shown.
// Uses the virtual functions: Item::CalculateTotal and Person::GetDiscountRate.
// Designer form: right-click BillingForm.h -> View Designer.

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
	using namespace System::Text;

	public ref class BillingForm : public System::Windows::Forms::Form
	{
	public:
		BillingForm(void)
		{
			InitializeComponent();
			cartItems = gcnew System::Collections::Generic::List<Item^>();
			cartQty = gcnew System::Collections::Generic::List<int>();
			Theme::Apply(this);
			LoadCombos();
			RefreshCart();
			LoadSales();
		}

	protected:
		~BillingForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  lblCustomer;
	private: System::Windows::Forms::Label^  lblProduct;
	private: System::Windows::Forms::Label^  lblQty;
	private: System::Windows::Forms::ComboBox^  cmbCustomer;
	private: System::Windows::Forms::ComboBox^  cmbProduct;
	private: System::Windows::Forms::NumericUpDown^  numQty;
	private: System::Windows::Forms::Button^  btnAdd;
	private: System::Windows::Forms::Button^  btnRemove;
	private: System::Windows::Forms::Button^  btnClear;
	private: System::Windows::Forms::Label^  lblBillTitle;
	private: System::Windows::Forms::DataGridView^  gridCart;
	private: System::Windows::Forms::Label^  lblTotal;
	private: System::Windows::Forms::Button^  btnSell;
	private: System::Windows::Forms::Label^  lblHistory;
	private: System::Windows::Forms::DataGridView^  grid;

	private:
		System::ComponentModel::Container ^components;
		System::Collections::Generic::List<Item^>^ cartItems;   // products on the current bill
		System::Collections::Generic::List<int>^ cartQty;       // matching quantities

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblCustomer = (gcnew System::Windows::Forms::Label());
			this->lblProduct = (gcnew System::Windows::Forms::Label());
			this->lblQty = (gcnew System::Windows::Forms::Label());
			this->cmbCustomer = (gcnew System::Windows::Forms::ComboBox());
			this->cmbProduct = (gcnew System::Windows::Forms::ComboBox());
			this->numQty = (gcnew System::Windows::Forms::NumericUpDown());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->btnRemove = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->lblBillTitle = (gcnew System::Windows::Forms::Label());
			this->gridCart = (gcnew System::Windows::Forms::DataGridView());
			this->lblTotal = (gcnew System::Windows::Forms::Label());
			this->btnSell = (gcnew System::Windows::Forms::Button());
			this->lblHistory = (gcnew System::Windows::Forms::Label());
			this->grid = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numQty))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grid))->BeginInit();
			this->SuspendLayout();
			//
			// lblCustomer
			//
			this->lblCustomer->AutoSize = true;
			this->lblCustomer->Location = System::Drawing::Point(20, 20);
			this->lblCustomer->Name = L"lblCustomer";
			this->lblCustomer->Size = System::Drawing::Size(51, 13);
			this->lblCustomer->TabIndex = 0;
			this->lblCustomer->Text = L"Customer";
			//
			// lblProduct
			//
			this->lblProduct->AutoSize = true;
			this->lblProduct->Location = System::Drawing::Point(20, 55);
			this->lblProduct->Name = L"lblProduct";
			this->lblProduct->Size = System::Drawing::Size(44, 13);
			this->lblProduct->TabIndex = 1;
			this->lblProduct->Text = L"Product";
			//
			// lblQty
			//
			this->lblQty->AutoSize = true;
			this->lblQty->Location = System::Drawing::Point(20, 90);
			this->lblQty->Name = L"lblQty";
			this->lblQty->Size = System::Drawing::Size(46, 13);
			this->lblQty->TabIndex = 2;
			this->lblQty->Text = L"Quantity";
			//
			// cmbCustomer
			//
			this->cmbCustomer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCustomer->FormattingEnabled = true;
			this->cmbCustomer->Location = System::Drawing::Point(110, 17);
			this->cmbCustomer->Name = L"cmbCustomer";
			this->cmbCustomer->Size = System::Drawing::Size(250, 21);
			this->cmbCustomer->TabIndex = 3;
			this->cmbCustomer->SelectedIndexChanged += gcnew System::EventHandler(this, &BillingForm::cmbCustomer_SelectedIndexChanged);
			//
			// cmbProduct
			//
			this->cmbProduct->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbProduct->FormattingEnabled = true;
			this->cmbProduct->Location = System::Drawing::Point(110, 52);
			this->cmbProduct->Name = L"cmbProduct";
			this->cmbProduct->Size = System::Drawing::Size(250, 21);
			this->cmbProduct->TabIndex = 4;
			//
			// numQty
			//
			this->numQty->Location = System::Drawing::Point(110, 87);
			this->numQty->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->numQty->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numQty->Name = L"numQty";
			this->numQty->Size = System::Drawing::Size(100, 20);
			this->numQty->TabIndex = 5;
			this->numQty->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			//
			// btnAdd
			//
			this->btnAdd->Location = System::Drawing::Point(400, 17);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(140, 32);
			this->btnAdd->TabIndex = 6;
			this->btnAdd->Text = L"Add to Bill";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &BillingForm::btnAdd_Click);
			//
			// btnRemove
			//
			this->btnRemove->Location = System::Drawing::Point(550, 17);
			this->btnRemove->Name = L"btnRemove";
			this->btnRemove->Size = System::Drawing::Size(140, 32);
			this->btnRemove->TabIndex = 7;
			this->btnRemove->Text = L"Remove Item";
			this->btnRemove->UseVisualStyleBackColor = true;
			this->btnRemove->Click += gcnew System::EventHandler(this, &BillingForm::btnRemove_Click);
			//
			// btnClear
			//
			this->btnClear->Location = System::Drawing::Point(700, 17);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(140, 32);
			this->btnClear->TabIndex = 8;
			this->btnClear->Text = L"Clear Bill";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &BillingForm::btnClear_Click);
			//
			// lblBillTitle
			//
			this->lblBillTitle->AutoSize = true;
			this->lblBillTitle->Location = System::Drawing::Point(20, 128);
			this->lblBillTitle->Name = L"lblBillTitle";
			this->lblBillTitle->Size = System::Drawing::Size(105, 13);
			this->lblBillTitle->TabIndex = 9;
			this->lblBillTitle->Text = L"Products on this bill";
			//
			// gridCart
			//
			this->gridCart->AllowUserToAddRows = false;
			this->gridCart->AllowUserToDeleteRows = false;
			this->gridCart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->gridCart->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->gridCart->Location = System::Drawing::Point(20, 150);
			this->gridCart->MultiSelect = false;
			this->gridCart->Name = L"gridCart";
			this->gridCart->ReadOnly = true;
			this->gridCart->RowHeadersVisible = false;
			this->gridCart->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->gridCart->Size = System::Drawing::Size(860, 170);
			this->gridCart->TabIndex = 10;
			//
			// lblTotal
			//
			this->lblTotal->AutoSize = true;
			this->lblTotal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTotal->Location = System::Drawing::Point(20, 333);
			this->lblTotal->MaximumSize = System::Drawing::Size(650, 0);
			this->lblTotal->Name = L"lblTotal";
			this->lblTotal->Size = System::Drawing::Size(67, 20);
			this->lblTotal->TabIndex = 11;
			this->lblTotal->Text = L"Total: -";
			//
			// btnSell
			//
			this->btnSell->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSell->Location = System::Drawing::Point(700, 333);
			this->btnSell->Name = L"btnSell";
			this->btnSell->Size = System::Drawing::Size(180, 48);
			this->btnSell->TabIndex = 12;
			this->btnSell->Text = L"Complete Sale";
			this->btnSell->UseVisualStyleBackColor = true;
			this->btnSell->Click += gcnew System::EventHandler(this, &BillingForm::btnSell_Click);
			//
			// lblHistory
			//
			this->lblHistory->AutoSize = true;
			this->lblHistory->Location = System::Drawing::Point(20, 400);
			this->lblHistory->Name = L"lblHistory";
			this->lblHistory->Size = System::Drawing::Size(135, 13);
			this->lblHistory->TabIndex = 13;
			this->lblHistory->Text = L"Sales history (latest 100)";
			//
			// grid
			//
			this->grid->AllowUserToAddRows = false;
			this->grid->AllowUserToDeleteRows = false;
			this->grid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->grid->Location = System::Drawing::Point(20, 422);
			this->grid->MultiSelect = false;
			this->grid->Name = L"grid";
			this->grid->ReadOnly = true;
			this->grid->RowHeadersVisible = false;
			this->grid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->grid->Size = System::Drawing::Size(860, 238);
			this->grid->TabIndex = 14;
			//
			// BillingForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 680);
			this->Controls->Add(this->grid);
			this->Controls->Add(this->lblHistory);
			this->Controls->Add(this->btnSell);
			this->Controls->Add(this->lblTotal);
			this->Controls->Add(this->gridCart);
			this->Controls->Add(this->lblBillTitle);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnRemove);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->numQty);
			this->Controls->Add(this->cmbProduct);
			this->Controls->Add(this->cmbCustomer);
			this->Controls->Add(this->lblQty);
			this->Controls->Add(this->lblProduct);
			this->Controls->Add(this->lblCustomer);
			this->MinimumSize = System::Drawing::Size(700, 560);
			this->Name = L"BillingForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Billing";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numQty))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grid))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	// ------------------------------------------------------------ code
	private:
		// Fills the combo boxes with Item / Person OBJECTS (they print their name).
		void LoadCombos()
		{
			cmbCustomer->Items->Clear();
			DataTable^ c = Database::Query("SELECT id, name, phone, membership FROM customers ORDER BY name");
			for each (DataRow^ r in c->Rows)
				cmbCustomer->Items->Add(PersonFactory::Create(r[3]->ToString(), Int32::Parse(r[0]->ToString()),
					r[1]->ToString(), r[2]->ToString()));

			cmbProduct->Items->Clear();
			DataTable^ p = Database::Query("SELECT id, name, category, price, quantity FROM products ORDER BY name");
			for each (DataRow^ r in p->Rows)
				cmbProduct->Items->Add(ItemFactory::Create(r[2]->ToString(), Int32::Parse(r[0]->ToString()),
					r[1]->ToString(),
					Double::Parse(r[3]->ToString(), CultureInfo::InvariantCulture),
					Int32::Parse(r[4]->ToString())));
			if (cmbCustomer->Items->Count > 0) cmbCustomer->SelectedIndex = 0;
			if (cmbProduct->Items->Count > 0) cmbProduct->SelectedIndex = 0;
		}

		void LoadSales()
		{
			grid->DataSource = Database::Query(
				"SELECT bill_no AS Bill, customer_name AS Customer, product_name AS Product, quantity AS Qty, "
				"total AS Total, sale_date AS Date FROM sales ORDER BY id DESC LIMIT 100");
		}

		Person^ SelectedCustomer() { return dynamic_cast<Person^>(cmbCustomer->SelectedItem); }

		// Sum of all lines. CalculateTotal is VIRTUAL: every product class prices itself.
		double Subtotal()
		{
			double sum = 0;
			for (int i = 0; i < cartItems->Count; i++)
				sum += cartItems[i]->CalculateTotal(cartQty[i]);
			return sum;
		}

		// Rebuilds the "products on this bill" table and the totals text.
		void RefreshCart()
		{
			if (cartItems == nullptr) return;

			DataTable^ t = gcnew DataTable();
			t->Columns->Add("Product");
			t->Columns->Add("Qty");
			t->Columns->Add("Unit Price");
			t->Columns->Add("Line Total");
			for (int i = 0; i < cartItems->Count; i++)
			{
				Item^ it = cartItems[i];
				int q = cartQty[i];
				t->Rows->Add(gcnew array<Object^>{ it->Name, q.ToString(), it->Price.ToString("F2"),
					it->CalculateTotal(q).ToString("F2") });
			}
			gridCart->DataSource = t;

			Person^ c = SelectedCustomer();
			double rate = (c == nullptr) ? 0.0 : c->GetDiscountRate();   // VIRTUAL: depends on customer class
			double sub = Subtotal();
			double disc = sub * rate;
			if (cartItems->Count == 0)
				lblTotal->Text = "Total: -";
			else
				lblTotal->Text = "Items: " + cartItems->Count.ToString() + "     Subtotal: Rs " + sub.ToString("F2") +
					"\nDiscount (" + (rate * 100).ToString("F0") + "%): - Rs " + disc.ToString("F2") +
					"\nTOTAL: Rs " + (sub - disc).ToString("F2");
		}

		void ShowReceipt(String^ text)
		{
			Form^ f = gcnew Form();
			f->Text = "Bill";
			f->ClientSize = System::Drawing::Size(460, 520);
			f->StartPosition = FormStartPosition::CenterParent;
			f->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			f->MaximizeBox = false;
			f->MinimizeBox = false;

			TextBox^ t = gcnew TextBox();
			t->Multiline = true;
			t->ReadOnly = true;
			t->ScrollBars = ScrollBars::Vertical;
			t->Font = gcnew System::Drawing::Font("Consolas", 10);
			t->BackColor = Color::White;
			t->Location = Point(15, 15);
			t->Size = System::Drawing::Size(430, 440);
			t->Text = text;
			f->Controls->Add(t);

			Button^ close = UI::Btn("Close", 330, 470, 115);
			close->DialogResult = System::Windows::Forms::DialogResult::OK;
			f->Controls->Add(close);
			f->AcceptButton = close;

			Theme::Apply(f);
			f->ShowDialog(this);
			delete f;
		}

		static String^ Cut(String^ s, int width)
		{
			return (s->Length > width) ? s->Substring(0, width) : s->PadRight(width);
		}

	private: System::Void cmbCustomer_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		RefreshCart();
	}

	private: System::Void btnAdd_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Item^ item = dynamic_cast<Item^>(cmbProduct->SelectedItem);
		if (item == nullptr) { UI::Warn("Choose a product first."); return; }
		int qty = (int)numQty->Value;

		// same product again -> add to its quantity instead of a new line
		int index = -1;
		int already = 0;
		for (int i = 0; i < cartItems->Count; i++)
			if (cartItems[i]->Id == item->Id) { index = i; already = cartQty[i]; }

		if (already + qty > item->Quantity)
		{
			UI::Warn("Not enough stock for " + item->Name + ". Only " + item->Quantity.ToString() + " in stock.");
			return;
		}
		if (index >= 0) cartQty[index] = already + qty;
		else { cartItems->Add(item); cartQty->Add(qty); }

		numQty->Value = 1;
		RefreshCart();
	}

	private: System::Void btnRemove_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (gridCart->SelectedRows->Count == 0) { UI::Warn("Select a product in the bill table first."); return; }
		int index = gridCart->SelectedRows[0]->Index;
		if (index < 0 || index >= cartItems->Count) return;
		cartItems->RemoveAt(index);
		cartQty->RemoveAt(index);
		RefreshCart();
	}

	private: System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e)
	{
		cartItems->Clear();
		cartQty->Clear();
		RefreshCart();
	}

	private: System::Void btnSell_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Person^ customer = SelectedCustomer();
		if (customer == nullptr) { UI::Warn("Choose a customer first."); return; }
		if (cartItems->Count == 0) { UI::Warn("Add at least one product to the bill."); return; }

		double rate = customer->GetDiscountRate();
		double sub = Subtotal();
		double grand = sub * (1.0 - rate);

		try
		{
			// make sure the stock is still there (read it fresh from the database)
			for (int i = 0; i < cartItems->Count; i++)
			{
				DataTable^ q = Database::Query("SELECT quantity FROM products WHERE id=" + cartItems[i]->Id.ToString());
				if (q->Rows->Count == 0) throw gcnew Exception(cartItems[i]->Name + " no longer exists.");
				if (Int32::Parse(q->Rows[0][0]->ToString()) < cartQty[i])
					throw gcnew Exception("Not enough stock for " + cartItems[i]->Name + ".");
			}

			int billNo = Int32::Parse(Database::Query("SELECT COALESCE(MAX(bill_no),0)+1 FROM sales")->Rows[0][0]->ToString());

			Database::Execute("START TRANSACTION");
			try
			{
				for (int i = 0; i < cartItems->Count; i++)
				{
					Item^ it = cartItems[i];
					double lineTotal = it->CalculateTotal(cartQty[i]) * (1.0 - rate);
					Database::Execute(String::Format("UPDATE products SET quantity = quantity - {0} WHERE id={1}",
						gcnew array<Object^>{ cartQty[i], it->Id }));
					Database::Execute(String::Format(
						"INSERT INTO sales(bill_no,customer_name,product_name,quantity,total,sale_date) VALUES({0},'{1}','{2}',{3},{4},NOW())",
						gcnew array<Object^>{ billNo, Database::Esc(customer->Name), Database::Esc(it->Name), cartQty[i],
							lineTotal.ToString("F2", CultureInfo::InvariantCulture) }));
				}
				Database::Execute("COMMIT");
			}
			catch (Exception^)
			{
				try { Database::Execute("ROLLBACK"); } catch (Exception^) {}
				throw;
			}

			// ---- the bill
			StringBuilder^ sb = gcnew StringBuilder();
			String^ line = gcnew String(L'-', 44);
			sb->AppendLine("           GROCERY SHOP");
			sb->AppendLine(line);
			sb->AppendLine("Bill No : " + billNo.ToString());
			sb->AppendLine("Date    : " + DateTime::Now.ToString("yyyy-MM-dd HH:mm"));
			sb->AppendLine("Customer: " + customer->Name + " (" + customer->GetMembership() + ")");
			sb->AppendLine(line);
			sb->AppendLine(Cut("Item", 20) + " " + String::Format("{0,4}", "Qty") + " " + String::Format("{0,16}", "Amount"));
			sb->AppendLine(line);
			for (int i = 0; i < cartItems->Count; i++)
				sb->AppendLine(Cut(cartItems[i]->Name, 20) + " " + String::Format("{0,4}", cartQty[i]) + " " +
					String::Format("{0,16}", cartItems[i]->CalculateTotal(cartQty[i]).ToString("F2")));
			sb->AppendLine(line);
			sb->AppendLine(String::Format("{0,-26}{1,18}", "Subtotal", sub.ToString("F2")));
			sb->AppendLine(String::Format("{0,-26}{1,18}", "Discount " + (rate * 100).ToString("F0") + "%", "-" + (sub * rate).ToString("F2")));
			sb->AppendLine(line);
			sb->AppendLine(String::Format("{0,-26}{1,18}", "TOTAL (Rs)", grand.ToString("F2")));
			sb->AppendLine(line);
			sb->AppendLine("        Thank you! Come again.");

			cartItems->Clear();
			cartQty->Clear();
			LoadCombos();       // refresh stock levels
			RefreshCart();
			LoadSales();
			ShowReceipt(sb->ToString());
		}
		catch (Exception^ ex)
		{
			UI::Warn(ex->Message);
		}
	}
	};
}
