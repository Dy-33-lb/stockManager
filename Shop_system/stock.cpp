#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct StockItem {
    string serialNumber;
    int quantity;
};

vector<StockItem> stockItems;

void clearInput() {
    cin.ignore();
}

// Add Stock
void addStock() {
    string serial;
    int qty;

    cout << "\nAdd Stock Item\n";
    cout << "Serial Number: ";
    clearInput();
    getline(cin, serial);
    cout << "Quantity to Add: ";
    cin >> qty;

    bool found = false;
    for (auto& item : stockItems) {
        if (item.serialNumber == serial) {
            item.quantity += qty;
            found = true;
            break;
        }
    }

    if (!found) {
        StockItem newItem;
        newItem.serialNumber = serial;
        newItem.quantity = qty;
        stockItems.push_back(newItem);
    }

    cout << "Stock item added successfully!\n";
}

// Display Stock
void displayStock() {
    if (stockItems.empty()) {
        cout << "No stock available.\n";
        return;
    }

    cout << "\nStock Items:\n";
    for (const auto& item : stockItems) {
        cout << "Serial Number: " << item.serialNumber
             << " | Quantity: " << item.quantity << "\n";
    }
}

// Remove Stock
void removeStock() {
    string serial;
    int qty;

    cout << "\nRemove Stock Item\n";
    cout << "Serial Number: ";
    clearInput();
    getline(cin, serial);
    cout << "Quantity to Remove: ";
    cin >> qty;

    for (auto& item : stockItems) {
        if (item.serialNumber == serial) {
            if (item.quantity >= qty) {
                item.quantity -= qty;
                cout << "Removed " << qty << " items from stock.\n";
            } else {
                cout << "Not enough stock to remove!\n";
            }
            return;
        }
    }

    cout << "Serial number not found!\n";
}

// Save Data to File
void saveData() {
    ofstream file("stock.txt");
    if (!file) {
        cout << "Error saving data.\n";
        return;
    }

    for (const auto& item : stockItems) {
        file << item.serialNumber << "," << item.quantity << "\n";
    }

    file.close();
    cout << "Data saved successfully!\n";
}

// Load Data from File
void loadData() {
    ifstream file("stock.txt");
    if (!file) {
        cout << "No previous data found.\n";
        return;
    }

    stockItems.clear();
    string serial;
    int quantity;
    string line;

    while (getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            serial = line.substr(0, pos);
            quantity = stoi(line.substr(pos + 1));
            stockItems.push_back({serial, quantity});
        }
    }

    file.close();
    cout << "Data loaded successfully!\n";
}

// Main Menu
int main() {
    loadData();
    int choice;

    do {
        cout << "\n============================\n";
        cout << "=      STOCK MANAGER      =\n";
        cout << "============================\n";
        cout << "1. Add Stock Item\n";
        cout << "2. Display Stock\n";
        cout << "3. Remove Stock Item\n";
        cout << "4. Save Data\n";
        cout << "5. Exit\n";
        cout << "============================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStock(); break;
            case 2: displayStock(); break;
            case 3: removeStock(); break;
            case 4: saveData(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    saveData();
    return 0;
}
