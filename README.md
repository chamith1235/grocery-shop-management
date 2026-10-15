# Grocery Shop Management System

ICT 1306 - Object Oriented Programming, Group Assignment
Department of Computing, Rajarata University of Sri Lanka

A Windows desktop application for a small grocery shop, written in **C++/CLI (Windows Forms)** with a **MySQL** database.

## Team members

| Name | Index number | Exam index |
|---|---|---|
| D N R Rathnayake | ICT/2024/106 | 6708 |
| D B Neththikumara | ICT/2024/093 | 6697 |
| A H T S Senivirathne | ICT/2024/116 | 6717 |
| V C M Vithanage | ICT/2024/129 | 6730 |
| P D N De Silva | ICT/2024/025 | 6639 |

## Features
- Login screen (passwords stored as SHA-256 hashes)
- **Products**: add, view, update, delete (unit price, quantity, total value)
- **Customers**: add, view, update, delete (Regular / Member, members get 5% discount)
- **Billing**: many products on one bill, stock reduced, bill number, receipt window
- Light-blue theme, resizable windows

## OOP concepts
| Concept | Where |
|---|---|
| Class / Object | `Item`, `Person` and their children (`Models.h`) |
| Encapsulation | private fields + properties that validate values |
| Abstraction | `Item` and `Person` are abstract classes |
| Inheritance | `GroceryItem`, `BeverageItem`, `HouseholdItem` : `Item`; `Customer`, `MemberCustomer` : `Person` |
| Polymorphism / virtual functions | `CalculateTotal()`, `GetDiscountRate()`, `Describe()` |

## Requirements
- Windows 10 / 11 (64-bit)
- Visual Studio with *Desktop development with C++* and *C++/CLI support*
- MySQL Server 8.0 (default folder `C:\Program Files\MySQL\MySQL Server 8.0`; if different, change `MySqlDir` in `GroceryShop.vcxproj`)

## How to run (on a new computer)
1. Install **Visual Studio** (workload *Desktop development with C++* + component *C++/CLI support*) and **MySQL Server 8.0**. Start the MySQL service.
2. Download this repository (**Code > Download ZIP**) and **unzip it** (do not run it from inside the zip).
3. Start it in one of two ways:
   - **Easy:** double-click `run.bat` - it builds the program and starts it.
   - **Visual Studio:** open `GroceryShop.sln`, choose **Debug / x64**, press **F5**.
4. Enter your MySQL **root** password when asked. The database `grocery_shop`, its tables and sample data are created automatically.
5. Log in with the default shop account: `admin` / `admin123`.

If MySQL is not in `C:\Program Files\MySQL\MySQL Server 8.0`, change `MySqlDir` in `GroceryShop.vcxproj`.

## Project files
| File | Purpose |
|---|---|
| `main.cpp` | Program start: MySQL connection, login, main menu |
| `Database.h/.cpp` | All MySQL code (connect, Execute, Query, Hash, Login) |
| `Models.h` | OOP classes |
| `LoginForm.h`, `MainForm.h`, `ProductForm.h`, `CustomerForm.h`, `BillingForm.h` | The screens (designer forms) |
| `Theme.h`, `UiHelper.h` | Look and feel, helpers |
| `images/`, `app.ico`, `app.rc` | Pictures and icon |
| `installer.iss`, `installer/` | Installer scripts |
| `docs/` | Report, project guide, code explanation, flow chart, SDLC, diagrams |