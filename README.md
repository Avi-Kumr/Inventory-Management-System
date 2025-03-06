# Inventory Management System

## Overview
This is a simple **Inventory Management System** written in C++ that allows users to manage items efficiently. It provides functionalities such as adding, deleting, updating, and sorting items. The data is stored in a file (`inventory.txt`) to ensure persistence.

## Features
- **Add Items**: Add new items with a unique ID, name, price, and quantity.
- **Delete Items**: Remove an item from the inventory using its ID.
- **Update Items**: Modify existing item details (name, price, quantity).
- **Sort Inventory**: View inventory sorted by **name, price, or quantity** in ascending or descending order.
- **File Persistence**: Saves and loads inventory data from `inventory.txt`.
- **User Input Validation**: Prevents invalid inputs and ensures smooth operation.

## Installation & Compilation
### **Requirements**
- C++ Compiler (G++ / Clang / MSVC)
- A terminal or command prompt

### **Compiling the Program**
Use the following command to compile:
```sh
 g++ inventory.cpp -o inventory
```

### **Running the Program**
After compilation, run the executable:
```sh
 ./inventory
```

## Usage Guide
Upon running the program, a menu will appear with options:
```
==========================
  Inventory Management   
==========================
1. Add Item
2. Delete Item
3. Update Item
4. Display All Items
5. Sort Inventory
6. Save & Exit
==========================
Enter your choice:
```
- **Option 1**: Add a new item by entering its name, price, and quantity.
- **Option 2**: Delete an item by providing its ID.
- **Option 3**: Update an item’s details by entering its ID and new values.
- **Option 4**: Display all items sorted by name in ascending order.
- **Option 5**: Choose sorting criteria (**Name, Price, Quantity**) and order (**Ascending, Descending**).
- **Option 6**: Save changes to file and exit the program.

## File Storage
The program reads and writes data to `inventory.txt` in the format:
```
ID,Item Name,Price,Quantity
1,Apple,1.5,50
2,Banana,0.8,100
```

## OOP Concepts Used
- **Encapsulation**: Private data members (`items` map), accessed via public methods.
- **Abstraction**: Users interact with simple functions; file handling and sorting logic are hidden.
- **Polymorphism**: Sorting logic uses lambda functions for dynamic sorting.




