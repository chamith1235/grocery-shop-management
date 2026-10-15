#pragma once
// Models.h - the OOP classes of the Grocery Shop.
//
//  Item (abstract)  <- GroceryItem, BeverageItem, HouseholdItem
//  Person (abstract) <- Customer, MemberCustomer
//
//  class / object ...... every class below, and the objects created from DB rows
//  encapsulation ....... private fields + properties that validate data
//  abstraction ......... Item and Person are abstract (pure virtual functions)
//  inheritance ......... derived classes reuse the fields/properties of the base
//  polymorphism ........ virtual CalculateTotal / GetDiscountRate / Describe are
//                        overridden and called through base-class handles

using namespace System;

// ---------------------------------------------------------------- Item
public ref class Item abstract
{
private:                       // ENCAPSULATION: data is hidden
    int id;
    String^ name;
    double price;
    int quantity;

public:
    Item(int id, String^ name, double price, int quantity)
    {
        this->id = id;
        Name = name;           // go through the validating properties
        Price = price;
        Quantity = quantity;
    }

    property int Id { int get() { return id; } }

    property String^ Name
    {
        String^ get() { return name; }
        void set(String^ v)
        {
            if (String::IsNullOrWhiteSpace(v)) throw gcnew ArgumentException("Product name cannot be empty.");
            name = v->Trim();
        }
    }
    property double Price
    {
        double get() { return price; }
        void set(double v)
        {
            if (v < 0) throw gcnew ArgumentException("Price cannot be negative.");
            price = v;
        }
    }
    property int Quantity
    {
        int get() { return quantity; }
        void set(int v)
        {
            if (v < 0) throw gcnew ArgumentException("Quantity cannot be negative.");
            quantity = v;
        }
    }

    // ABSTRACTION + POLYMORPHISM: pure virtual functions, each category decides.
    virtual String^ GetCategory() abstract;
    virtual double CalculateTotal(int qty) abstract;

    // virtual with a default body, overridden by the derived classes
    virtual String^ Describe()
    {
        return GetCategory() + ": " + name + " @ Rs " + price.ToString("F2");
    }

    virtual String^ ToString() override { return name; }   // used by combo boxes
};

// INHERITANCE: each class below IS-A Item
public ref class GroceryItem : public Item
{
public:
    GroceryItem(int id, String^ n, double p, int q) : Item(id, n, p, q) {}

    virtual String^ GetCategory() override { return "Grocery"; }
    virtual double CalculateTotal(int qty) override { return Price * qty; }   // no tax
    virtual String^ Describe() override { return Item::Describe() + "  (no tax)"; }
};

public ref class BeverageItem : public Item
{
public:
    BeverageItem(int id, String^ n, double p, int q) : Item(id, n, p, q) {}

    virtual String^ GetCategory() override { return "Beverage"; }
    virtual double CalculateTotal(int qty) override { return Price * qty * 1.08; }   // 8% tax
    virtual String^ Describe() override { return Item::Describe() + "  (8% tax)"; }
};

public ref class HouseholdItem : public Item
{
public:
    HouseholdItem(int id, String^ n, double p, int q) : Item(id, n, p, q) {}

    virtual String^ GetCategory() override { return "Household"; }
    virtual double CalculateTotal(int qty) override                          // 10% off for 5+
    {
        double t = Price * qty;
        return qty >= 5 ? t * 0.90 : t;
    }
    virtual String^ Describe() override { return Item::Describe() + "  (10% off when buying 5 or more)"; }
};

// Creates the right derived object for a category name.
public ref class ItemFactory abstract sealed
{
public:
    static Item^ Create(String^ category, int id, String^ name, double price, int qty)
    {
        if (category == "Beverage")  return gcnew BeverageItem(id, name, price, qty);
        if (category == "Household") return gcnew HouseholdItem(id, name, price, qty);
        if (category == "Grocery")   return gcnew GroceryItem(id, name, price, qty);
        throw gcnew ArgumentException("Please choose a category.");
    }
};

// -------------------------------------------------------------- Person
public ref class Person abstract
{
private:
    int id;
    String^ name;
    String^ phone;

public:
    Person(int id, String^ name, String^ phone)
    {
        this->id = id;
        Name = name;
        Phone = phone;
    }

    property int Id { int get() { return id; } }

    property String^ Name
    {
        String^ get() { return name; }
        void set(String^ v)
        {
            if (String::IsNullOrWhiteSpace(v)) throw gcnew ArgumentException("Customer name cannot be empty.");
            name = v->Trim();
        }
    }
    property String^ Phone
    {
        String^ get() { return phone; }
        void set(String^ v) { phone = (v == nullptr) ? "" : v->Trim(); }
    }

    virtual String^ GetMembership() abstract;
    virtual double GetDiscountRate() abstract;       // 0.05 = 5%

    virtual String^ Describe()
    {
        return GetMembership() + " customer: " + name + "  (discount " + (GetDiscountRate() * 100).ToString("F0") + "%)";
    }

    virtual String^ ToString() override { return name; }
};

public ref class Customer : public Person
{
public:
    Customer(int id, String^ n, String^ ph) : Person(id, n, ph) {}
    virtual String^ GetMembership() override { return "Regular"; }
    virtual double GetDiscountRate() override { return 0.0; }
};

public ref class MemberCustomer : public Person
{
public:
    MemberCustomer(int id, String^ n, String^ ph) : Person(id, n, ph) {}
    virtual String^ GetMembership() override { return "Member"; }
    virtual double GetDiscountRate() override { return 0.05; }
};

public ref class PersonFactory abstract sealed
{
public:
    static Person^ Create(String^ membership, int id, String^ name, String^ phone)
    {
        if (membership == "Member")  return gcnew MemberCustomer(id, name, phone);
        if (membership == "Regular") return gcnew Customer(id, name, phone);
        throw gcnew ArgumentException("Please choose a membership type.");
    }
};
