#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

struct Item {
    string name;
    double price;
    int quantity;
};

class Inventory {
private:
    map<int, Item> items;

public:
    void loadFromFile() {
        ifstream file("inventory.txt");
        if (!file) return;

        int id, quantity;
        string name;
        double price;
        while (file >> id) {
            file.ignore();
            getline(file, name, ',');
            file >> price;
            file.ignore();
            file >> quantity;
            items[id] = {name, price, quantity};
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("inventory.txt");
        if (!file) {
            cout << "Error: Could not save inventory data!\n";
            return;
        }
        for (const auto &[id, item] : items)
            file << id << "," << item.name << "," << item.price << "," << item.quantity << endl;
        file.close();
    }

    bool nameExists(const string& name) {
        for (const auto& [id, item] : items) {
            if (item.name == name) return true;
        }
        return false;
    }

    void addItem(const string& name, double price, int quantity) {
        int id = (items.empty()) ? 1 : items.rbegin()->first + 1;
        items[id] = {name, price, quantity};
        cout << "Item added successfully! ID: " << id << "\n";
        saveToFile();
    }

    void deleteItem(int id) {
        if (items.erase(id)) {
            cout << "Item deleted successfully!\n";
            saveToFile();
        } else {
            cout << "Error: Item not found!\n";
        }
    }

    void updateItem(int id, const string& name, double price, int quantity) {
        if (items.find(id) != items.end()) {
            if (nameExists(name) && items[id].name != name) {
                cout << "Error: An item with this name already exists!\n";
                return;
            }
            items[id] = {name, price, quantity};
            cout << "Item updated successfully!\n";
            saveToFile();
        } else {
            cout << "Error: Item not found!\n";
        }
    }

    void displayItemsSorted(const string& criteria, const string& order) {
        vector<pair<int, Item>> sortedItems(items.begin(), items.end());

        if (criteria == "price")
            sort(sortedItems.begin(), sortedItems.end(), [order](auto &a, auto &b) { 
                return (order == "ascending") ? a.second.price < b.second.price : a.second.price > b.second.price; 
            });
        else if (criteria == "quantity")
            sort(sortedItems.begin(), sortedItems.end(), [order](auto &a, auto &b) { 
                return (order == "ascending") ? a.second.quantity < b.second.quantity : a.second.quantity > b.second.quantity; 
            });
        else if (criteria == "name")
            sort(sortedItems.begin(), sortedItems.end(), [order](auto &a, auto &b) { 
                return (order == "ascending") ? a.second.name < b.second.name : a.second.name > b.second.name; 
            });

        cout << "\nSorted Inventory (" << criteria << ", " << order << "):\n";
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        cout << "-------------------------------------------------\n";
        for (const auto& [id, item] : sortedItems) {
            cout << setw(5) << id << setw(20) << item.name << setw(10) << item.price << setw(10) << item.quantity << endl;
        }
    }
};

int main() {
    Inventory inventory;
    inventory.loadFromFile();

    int choice, id, quantity;
    string name, criteria, order;
    double price;

    while (true) {
        cout << "\n==========================\n";
        cout << "  Inventory Management   ";
        cout << "\n==========================\n";
        cout << "1. Add Item\n";
        cout << "2. Delete Item\n";
        cout << "3. Update Item\n";
        cout << "4. Display All Items\n";
        cout << "5. Sort Inventory\n";
        cout << "6. Save & Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter Item Name: ";
            cin.ignore();
            getline(cin, name);
            if (inventory.nameExists(name)) {
                cout << "Error: An item with this name already exists!\n";
                break;
            }
            cout << "Enter Item Price: ";
            while (!(cin >> price)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid price: ";
            }
            cout << "Enter Item Quantity: ";
            while (!(cin >> quantity)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid quantity: ";
            }
            inventory.addItem(name, price, quantity);
            break;
        case 2:
            cout << "Enter Item ID to Delete: ";
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid ID: ";
            }
            inventory.deleteItem(id);
            break;
        case 3:
            cout << "Enter Item ID to Update: ";
            while (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid ID: ";
            }
            cout << "Enter New Item Name: ";
            cin.ignore();
            getline(cin, name);
            if (inventory.nameExists(name)) {
                cout << "Error: An item with this name already exists!\n";
                break;
            }
            cout << "Enter New Item Price: ";
            while (!(cin >> price)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid price: ";
            }
            cout << "Enter New Item Quantity: ";
            while (!(cin >> quantity)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid quantity: ";
            }
            inventory.updateItem(id, name, price, quantity);
            break;
        case 4:
            inventory.displayItemsSorted("name", "ascending");
            break;
        case 5:
            cout << "Sort by:\n";
            cout << "Select 1 for Name\n";
            cout << "Select 2 for Price\n";
            cout << "Select 3 for Quantity\n";
            cout << "Enter your choice: ";
            int sortChoice;
            cin >> sortChoice;
            if (sortChoice == 1) criteria = "name";
            else if (sortChoice == 2) criteria = "price";
            else if (sortChoice == 3) criteria = "quantity";
            else {
                cout << "Invalid choice! Defaulting to Name.\n";
                criteria = "name";
            }

            cout << "Order:\n";
            cout << "Select 1 for Ascending\n";
            cout << "Select 2 for Descending\n";
            cout << "Enter your choice: ";
            int orderChoice;
            cin >> orderChoice;
            if (orderChoice == 1) order = "ascending";
            else if (orderChoice == 2) order = "descending";
            else {
                cout << "Invalid choice! Defaulting to Ascending.\n";
                order = "ascending";
            }
            inventory.displayItemsSorted(criteria, order);
            break;
        case 6:
            inventory.saveToFile();
            cout << "Inventory saved. Exiting the program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}
