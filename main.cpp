#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

struct Service {
    string name;
    double price;
};

struct Booking {
    string customerName;
    string serviceName;
};

struct Provider {
    unordered_map<string, string> profile;
    vector<Service> services;
    queue<Booking> bookings;
    stack<Service> deletedServices;
};

void showProfile(const Provider& provider) {
    cout << "\n=== PROFILE DETAILS ===\n";
    cout << "Name   : " << provider.profile.at("name") << endl;
    cout << "Email  : " << provider.profile.at("email") << endl;
    cout << "Phone  : " << provider.profile.at("phone") << endl;
}

void editProfile(Provider& provider) {
    int choice;

    cout << "\nWhat do you want to edit on your profile?\n";
    cout << "1. Name\n";
    cout << "2. Email\n";
    cout << "3. Phone\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    string newValue;
    cout << "Enter the new value: ";
    getline(cin, newValue);

    switch (choice) {
        case 1:
            provider.profile["name"] = newValue;
            break;
        case 2:
            provider.profile["email"] = newValue;
            break;
        case 3:
            provider.profile["phone"] = newValue;
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }

    cout << "Profile updated successfully.\n";
}

void showServices(const vector<Service>& services) {
    cout << "\n=== SERVICES ===\n";

    if (services.empty()) {
        cout << "No services found.\n";
        return;
    }

    for (int i = 0; i < services.size(); i++) {
        cout << i + 1 << ". " << services[i].name
             << " - $" << services[i].price << endl;
    }
}

void addService(vector<Service>& services) {
    Service service;

    cout << "\nEnter new service name: ";
    getline(cin, service.name);

    cout << "Enter price for " << service.name << ": ";
    cin >> service.price;
    cin.ignore();

    services.push_back(service);

    cout << "Service added successfully.\n";
}

void editService(vector<Service>& services) {
    if (services.empty()) {
        cout << "No services to edit.\n";
        return;
    }

    showServices(services);

    int index;
    cout << "Enter service number to edit: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > services.size()) {
        cout << "Invalid service number.\n";
        return;
    }

    Service& service = services[index - 1];

    cout << "Enter new name for the service: ";
    getline(cin, service.name);

    cout << "Enter new price for " << service.name << ": ";
    cin >> service.price;
    cin.ignore();

    cout << "Service updated successfully.\n";
}

void deleteService(Provider& provider) {
    if (provider.services.empty()) {
        cout << "No services to delete.\n";
        return;
    }

    showServices(provider.services);

    int index;
    cout << "Enter service number to delete: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > provider.services.size()) {
        cout << "Invalid service number.\n";
        return;
    }

    Service deletedService = provider.services[index - 1];

    provider.deletedServices.push(deletedService);
    provider.services.erase(provider.services.begin() + (index - 1));

    cout << "Service deleted successfully.\n";
    cout << "Deleted service saved. You can restore it using Undo Restore.\n";
}

void restoreDeletedService(Provider& provider) {
    if (provider.deletedServices.empty()) {
        cout << "No deleted service to restore.\n";
        return;
    }

    Service restored = provider.deletedServices.top();
    provider.deletedServices.pop();

    provider.services.push_back(restored);

    cout << "Last deleted service restored successfully.\n";
    cout << "Restored service: " << restored.name
         << " - $" << restored.price << endl;
}

void searchService(const vector<Service>& services) {
    if (services.empty()) {
        cout << "No services available.\n";
        return;
    }

    string target;
    cout << "Enter service name to search: ";
    getline(cin, target);

    bool found = false;

    for (int i = 0; i < services.size(); i++) {
        if (services[i].name == target) {
            cout << "Service found at position " << i + 1 << ": "
                 << services[i].name << " - $" << services[i].price << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Service not found.\n";
    }
}

void bookService(Provider& provider) {
    if (provider.services.empty()) {
        cout << "No services available for booking.\n";
        return;
    }

    showServices(provider.services);

    int index;
    cout << "Enter service number to book: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > provider.services.size()) {
        cout << "Invalid service number.\n";
        return;
    }

    Booking booking;

    cout << "Enter customer name: ";
    getline(cin, booking.customerName);

    booking.serviceName = provider.services[index - 1].name;
    provider.bookings.push(booking);

    cout << "Booking added to queue successfully.\n";
}

void serveNextCustomer(Provider& provider) {
    if (provider.bookings.empty()) {
        cout << "No bookings in queue.\n";
        return;
    }

    Booking next = provider.bookings.front();
    provider.bookings.pop();

    cout << "\nNow serving:\n";
    cout << "Customer: " << next.customerName << endl;
    cout << "Service : " << next.serviceName << endl;
}

void showBookings(queue<Booking> bookings) {
    if (bookings.empty()) {
        cout << "No bookings in queue.\n";
        return;
    }

    cout << "\n=== BOOKING QUEUE ===\n";

    int count = 1;

    while (!bookings.empty()) {
        Booking b = bookings.front();
        bookings.pop();

        cout << count << ". " << b.customerName
             << " booked " << b.serviceName << endl;

        count++;
    }
}

void deleteProvider(vector<Provider>& providers) {
    if (providers.empty()) {
        cout << "No providers available to delete.\n";
        return;
    }

    cout << "\n=== PROVIDERS ===\n";

    for (int i = 0; i < providers.size(); i++) {
        cout << i + 1 << ". " << providers[i].profile.at("name") << endl;
    }

    int index;
    cout << "Enter the provider number to delete: ";
    cin >> index;
    cin.ignore();

    if (index < 1 || index > providers.size()) {
        cout << "Invalid provider number.\n";
        return;
    }

    providers.erase(providers.begin() + (index - 1));

    cout << "Provider deleted successfully.\n";
}

int selectProvider(const vector<Provider>& providers) {
    if (providers.empty()) {
        cout << "No providers available.\n";
        return -1;
    }

    cout << "\n=== PROVIDERS ===\n";

    for (int i = 0; i < providers.size(); i++) {
        cout << i + 1 << ". " << providers[i].profile.at("name") << endl;
    }

    int choice;
    cout << "Select a provider by number: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > providers.size()) {
        cout << "Invalid choice.\n";
        return -1;
    }

    return choice - 1;
}

void addProvider(vector<Provider>& providers) {
    Provider newProvider;

    cout << "\nEnter provider name: ";
    getline(cin, newProvider.profile["name"]);

    cout << "Enter email: ";
    getline(cin, newProvider.profile["email"]);

    cout << "Enter phone: ";
    getline(cin, newProvider.profile["phone"]);

    providers.push_back(newProvider);

    cout << "Provider added successfully.\n";
}

int main() {
    vector<Provider> providers;

    Provider p;
    p.profile["name"] = "Aifa Magracia";
    p.profile["email"] = "25-00374@g.batstate-u.edu.ph";
    p.profile["phone"] = "09944651496";
    p.services = {
        {"Web Design", 150.0},
        {"Programming", 200.0},
        {"Tutoring", 50.0}
    };

    providers.push_back(p);

    int choice;

    do {
        cout << "\n=== SERVIFY ===\n";
        cout << "1. Select Provider\n";
        cout << "2. Add Provider\n";
        cout << "3. Delete Provider\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int index = selectProvider(providers);

                if (index == -1) {
                    break;
                }

                Provider& selected = providers[index];

                int subChoice;

                do {
                    cout << "\n--- Manage Provider: "
                         << selected.profile["name"] << " ---\n";

                    cout << "1. Show Profile\n";
                    cout << "2. Edit Profile\n";
                    cout << "3. Show Services\n";
                    cout << "4. Add Service\n";
                    cout << "5. Edit Service\n";
                    cout << "6. Delete Service\n";
                    cout << "7. Search Service\n";
                    cout << "8. Book Service\n";
                    cout << "9. Serve Next Customer\n";
                    cout << "10. Show Bookings\n";
                    cout << "11. Restore Last Deleted Service\n";
                    cout << "12. Back\n";
                    cout << "Enter choice: ";

                    cin >> subChoice;
                    cin.ignore();

                    switch (subChoice) {
                        case 1:
                            showProfile(selected);
                            break;

                        case 2:
                            editProfile(selected);
                            break;

                        case 3:
                            showServices(selected.services);
                            break;

                        case 4:
                            addService(selected.services);
                            break;

                        case 5:
                            editService(selected.services);
                            break;

                        case 6:
                            deleteService(selected);
                            break;

                        case 7:
                            searchService(selected.services);
                            break;

                        case 8:
                            bookService(selected);
                            break;

                        case 9:
                            serveNextCustomer(selected);
                            break;

                        case 10:
                            showBookings(selected.bookings);
                            break;

                        case 11:
                            restoreDeletedService(selected);
                            break;

                        case 12:
                            cout << "Returning to main menu.\n";
                            break;

                        default:
                            cout << "Invalid choice.\n";
                    }

                } while (subChoice != 12);

                break;
            }

            case 2:
                addProvider(providers);
                break;

            case 3:
                deleteProvider(providers);
                break;

            case 4:
                cout << "Program ended.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}