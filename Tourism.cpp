#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#ifdef _WIN32
#include <windows.h> // For Windows console colors
#else
#include <unistd.h> // For Linux compatibility
#endif

using namespace std;

// Console color functions
void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    cout << "\033[" << color << "m"; // ANSI escape codes for Linux
#endif
}

void resetColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Default white
#else
    cout << "\033[0m"; // Reset to default color
#endif
}

// Package structure
struct Package {
    int id;
    string details;
    double price;
    Package* next;
};

// Hotel structure
struct Hotel {
    string name;
    double price;
    Hotel* next;
};

// Vehicle options
enum Vehicle { BUS = 1, TRAIN };

// Sorting function for Packages
void sortPackages(Package*& head) {
    if (!head || !head->next) return; // No sorting needed for 0 or 1 element
    for (Package* i = head; i->next; i = i->next) {
        for (Package* j = i->next; j; j = j->next) {
            if (i->price > j->price) {
                // Swap values
                swap(i->id, j->id);
                swap(i->details, j->details);
                swap(i->price, j->price);
            }
        }
    }
}

// Sorting function for Hotels
void sortHotels(Hotel*& head) {
    if (!head || !head->next) return; // No sorting needed for 0 or 1 element
    for (Hotel* i = head; i->next; i = i->next) {
        for (Hotel* j = i->next; j; j = j->next) {
            if (i->price > j->price) {
                // Swap values
                swap(i->name, j->name);
                swap(i->price, j->price);
            }
        }
    }
}

// Functions for Linked List (Packages)
void addPackage(Package*& head, int id, string details, double price) {
    Package* newPackage = new Package{id, details, price, nullptr};
    if (!head) {
        head = newPackage;
        return;
    }
    Package* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newPackage;
    sortPackages(head); // Sort after adding
}

void displayPackages(Package* head) {
    if (!head) {
        setColor(12); // Red
        cout << "No packages available.\n";
        resetColor();
        return;
    }
    setColor(11); // Cyan
    cout << "\nAvailable Packages (Sorted by Price):\n";
    resetColor();
    while (head) {
        setColor(10); // Green
        cout << "ID: " << head->id
             << ", Details: " << head->details
             << ", Price (per person): ৳" << fixed << setprecision(2) << head->price << endl;
        resetColor();
        head = head->next;
    }
}

// Functions for Linked List (Hotels)
void addHotel(Hotel*& head, string name, double price) {
    if (price > 10000) return; // Restrict prices above 10,000
    Hotel* newHotel = new Hotel{name, price, nullptr};
    if (!head) {
        head = newHotel;
        return;
    }
    Hotel* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newHotel;
    sortHotels(head); // Sort after adding
}

bool displayHotels(Hotel* head, double budget) {
    bool found = false;
    while (head) {
        if (head->price <= budget) {
            if (!found) {
                setColor(11); // Cyan
                cout << "\nHotels within your budget (৳0 - ৳" << budget << "):\n";
                resetColor();
                found = true;
            }
            setColor(10); // Green
            cout << "- " << head->name << ", Price: ৳" << fixed << setprecision(2) << head->price << endl;
            resetColor();
        }
        head = head->next;
    }
    if (!found) {
        setColor(12); // Red
        cout << "No hotels found within your budget.\n";
        resetColor();
    }
    return found;
}

// Predefined data
void initializeData(map<string, Package*>& packagesByLocation, map<string, Hotel*>& hotelsByLocation) {
    vector<string> locations = {"Dhaka", "Cox's Bazar", "Sylhet", "Rangamati", "Sundarbans", "Khulna"};
    for (const auto& loc : locations) {
        packagesByLocation[loc] = nullptr;
        hotelsByLocation[loc] = nullptr;
    }

    addPackage(packagesByLocation["Dhaka"], 1, "Historical Tour - 2 days", 3500.00);
    addPackage(packagesByLocation["Dhaka"], 2, "Shopping Tour - 1 day", 6000.00);

    addPackage(packagesByLocation["Cox's Bazar"], 3, "Beach Tour - 3 days", 7500.00);
    addPackage(packagesByLocation["Cox's Bazar"], 4, "Adventure Tour - 4 days", 12000.00);

    addPackage(packagesByLocation["Sylhet"], 5, "Tea Gardens Tour - 2 days", 8000.00);
    addPackage(packagesByLocation["Sylhet"], 6, "Sylhet Hills Tour - 3 days", 10500.00);

    addPackage(packagesByLocation["Rangamati"], 7, "Lake Tour - 2 days", 8500.00);
    addPackage(packagesByLocation["Rangamati"], 8, "Hill Adventure - 3 days", 5000.00);

    addPackage(packagesByLocation["Sundarbans"], 9, "Forest Adventure - 2 days", 12000.00);
    addPackage(packagesByLocation["Sundarbans"], 10, "Wildlife Exploration - 3 days", 8500.00);

    addPackage(packagesByLocation["Khulna"], 11, "City and Sundarbans Combo - 3 days", 10000.00);
    addPackage(packagesByLocation["Khulna"], 12, "Heritage Tour - 2 days", 5500.00);

    addHotel(hotelsByLocation["Dhaka"], "Pan Pacific Sonargaon", 10000.00);
    addHotel(hotelsByLocation["Dhaka"], "InterContinental Dhaka", 9000.00);
    addHotel(hotelsByLocation["Cox's Bazar"], "The Cox Today", 8000.00);
    addHotel(hotelsByLocation["Cox's Bazar"], "Seagull Hotel", 7000.00);
    addHotel(hotelsByLocation["Sylhet"], "Tea Resort", 7000.00);
    addHotel(hotelsByLocation["Rangamati"], "Rangamati Lake Resort", 6000.00);
    addHotel(hotelsByLocation["Sundarbans"], "Sundarbans Resort", 12000.00);
    addHotel(hotelsByLocation["Khulna"], "Hotel Castle Salam", 4500.00);
}

// Admin Section Implementation
void adminSection(map<string, Package*>& packagesByLocation, map<string, Hotel*>& hotelsByLocation) {
    string password;
    cout << "\nEnter admin password: ";
    cin >> password;

    if (password != "12345") {
        setColor(12); // Red
        cout << "Invalid password. Returning to main menu.\n";
        resetColor();
        return;
    }

    int choice;
    do {
        cout << "\n=== Admin Section ===\n";
        cout << "1. View Packages\n";
        cout << "2. Add Package\n";
        cout << "3. Add Location\n";
        cout << "4. Add Hotel\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            for (const auto& loc : packagesByLocation) {
                displayPackages(loc.second);
            }
        } else if (choice == 2) {
            string location, details;
            double price;
            cout << "\nEnter location for the new package: ";
            cin.ignore();
            getline(cin, location);
            if (packagesByLocation.find(location) == packagesByLocation.end()) {
                cout << "Location not found. Please add the location first.\n";
                continue;
            }

            cout << "Enter package details: ";
            getline(cin, details);
            cout << "Enter package price: ";
            cin >> price;

            static int packageId = 1;
            addPackage(packagesByLocation[location], packageId++, details, price);
            cout << "Package added successfully.\n";
        } else if (choice == 3) {
            string location;
            cout << "\nEnter new location: ";
            cin.ignore();
            getline(cin, location);

            if (packagesByLocation.find(location) != packagesByLocation.end()) {
                cout << "Location already exists.\n";
            } else {
                packagesByLocation[location] = nullptr;
                hotelsByLocation[location] = nullptr;
                cout << "Location added successfully.\n";
            }
        } else if (choice == 4) {
            string location, hotelName;
            double hotelPrice;
            cout << "\nEnter location where hotel is to be added: ";
            getline(cin, location);

            if (hotelsByLocation.find(location) == hotelsByLocation.end()) {
                cout << "Location not found. Please add the location first.\n";
                continue;
            }

            cout << "Enter hotel name: ";
            getline(cin, hotelName);
            cout << "Enter hotel price: ";
            cin >> hotelPrice;

            addHotel(hotelsByLocation[location], hotelName, hotelPrice);
            cout << "Hotel added successfully.\n";
        }
    } while (choice != 5);
}

// Main Function
int main() {
    map<string, Package*> packagesByLocation;
    map<string, Hotel*> hotelsByLocation;
    initializeData(packagesByLocation, hotelsByLocation);

    int choice;
    do {
        setColor(14); // Yellow
        cout << "\n\t\t\t\t\t=== Dream Tour ===\t\t\t\t\t\n";
        resetColor();
        cout << "1. Customer Section\n"
             << "2. Admin Section\n"
             << "3. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, contact, location, hotelName;
            double budget;
            int packageChoice, members, vehicleChoice, numRooms;

            cin.ignore();
            cout << "\nEnter your name: ";
            getline(cin, name);
            cout << "Enter your contact number: ";
            getline(cin, contact);

            cout << "\nAvailable Locations:\n";
            for (const auto& loc : packagesByLocation) {
                setColor(10); // Green
                cout << "- " << loc.first << endl;
                resetColor();
            }
            cout << "Enter location for your trip: ";
            getline(cin, location);

            if (packagesByLocation.find(location) != packagesByLocation.end()) {
                displayPackages(packagesByLocation[location]);

                cout << "\nChoose a package by entering its ID: ";
                cin >> packageChoice;

                Package* selectedPackage = packagesByLocation[location];
                while (selectedPackage && selectedPackage->id != packageChoice) {
                    selectedPackage = selectedPackage->next;
                }

                if (!selectedPackage) {
                    setColor(12); // Red
                    cout << "Invalid package ID selected.\n";
                    resetColor();
                    continue;
                }

                cout << "\nEnter number of members for the trip: ";
                cin >> members;

                cin.ignore();
                cout << "\nDo you want us to book rooms at a hotel? (1 for Yes, 0 for No): ";
                int bookHotel;
                cin >> bookHotel;

                if (bookHotel == 1) {
    bool validHotels = false;
    do {
        cout << "\nEnter your budget for hotels (৳): ";
        cin >> budget;

        validHotels = displayHotels(hotelsByLocation[location], budget);
        if (!validHotels) {
            setColor(12); // Red
            cout << "No hotels found within the budget. Please try a different budget.\n";
            resetColor();
        }
    } while (!validHotels);

    cout << "Choose a hotel by entering its name: ";
    cin.ignore();
    getline(cin, hotelName);

    Hotel* temp = hotelsByLocation[location];
    bool validHotel = false;
    while (temp) {
        if (temp->name == hotelName && temp->price <= budget) {
            validHotel = true;
            break;
        }
        temp = temp->next;
    }

    if (!validHotel) {
        setColor(12); // Red
        cout << "Invalid hotel selection or out of budget. Returning to main menu.\n";
        resetColor();
        continue;
    }

    cout << "How many rooms do you need? ";
    cin >> numRooms;
}

                cout << "\nSelect mode of transport:\n1. Bus\n2. Train\n";
                cin >> vehicleChoice;

                // Payment Method Integration
                cout << "\nChoose a payment method:\n1. Bkash\n2. Nagad\n3. Rocket\n";
                int paymentMethod;
                cin >> paymentMethod;

                string paymentMethodName;
                switch (paymentMethod) {
                    case 1:
                        paymentMethodName = "Bkash";
                        break;
                    case 2:
                        paymentMethodName = "Nagad";
                        break;
                    case 3:
                        paymentMethodName = "Rocket";
                        break;
                    default:
                        setColor(12); // Red
                        cout << "Invalid payment method selected. Returning to main menu.\n";
                        resetColor();
                        continue;
                }

                string paymentPhoneNumber;
                cout << "Enter the phone number for " << paymentMethodName << ": ";
                cin.ignore();
                getline(cin, paymentPhoneNumber);

                setColor(10); // Green
                cout << "\nPayment confirmed successfully using " << paymentMethodName
                     << " (" << paymentPhoneNumber << ").\n";
                resetColor();

                // Final Confirmation
                setColor(14); // Yellow
                cout << "\n\t\t\t\t=== Final Confirmation ===\t\t\t\t\t\n";
                resetColor();
                cout << "Name: " << name << endl;
                cout << "Contact: " << contact << endl;
                cout << "Location: " << location << endl;
                cout << "Package: " << selectedPackage->details << endl;
                cout << "Number of Members: " << members << endl;
                cout << "Hotel: " << (hotelName.empty() ? "No hotel selected" : hotelName) << endl;
                cout << "Rooms Booked: " << (hotelName.empty() ? 0 : numRooms) << endl;
                cout << "Total Package Cost: ৳" << (selectedPackage->price * members) << endl;
                cout << "Mode of Transport: " << (vehicleChoice == BUS ? "Bus" : "Train") << endl;
                cout << "Payment Method: " << paymentMethodName << " (" << paymentPhoneNumber << ")\n";
            } else {
                setColor(12); // Red
                cout << "Location not found. Returning to main menu.\n";
                resetColor();
            }
        } else if (choice == 2) {
            adminSection(packagesByLocation, hotelsByLocation);
        }
    } while (choice != 3);

    setColor(14); // Yellow
    cout << "\n\t\t\t\tThank you for using Dream Tour! Goodbye. \t\t\t\t\n";
    resetColor();
    return 0;
}
