#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


struct Service {
    string name;
    double price;
};

struct Provider {
    unordered_map<string, string> profile;
    vector<Service> services;
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
    cout << "1. Name\n2. Email\n3. Phone\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    string newValue;
    cout << "Enter the new value: ";
    getline(cin, newValue);

    switch (choice) {
        case 1: provider.profile["name"] = newValue; break;
        case 2: provider.profile["email"] = newValue; break;
        case 3: provider.profile["phone"] = newValue; break;
        default: cout << "Invalid choice.\n"; return;
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
        cout << i + 1 << ". " << services[i].name << " - $" << services[i].price << endl;
    }
}

void addService(vector<Service>& services) {
    Service service;
    cout << "\nEnter new service name: ";
    cin.ignore();
    getline(cin, service.name);

    cout << "Enter price for " << service.name << ": ";
    cin >> service.price;

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

    if (index < 1 || index > services.size()) {
        cout << "Invalid service number.\n";
        return;
    }

    Service& service = services[index - 1];
    cout << "Enter new name for the service: ";
    cin.ignore();
    getline(cin, service.name);

    cout << "Enter new price for " << service.name << ": ";
    cin >> service.price;

    cout << "Service updated successfully.\n";
}

void deleteService(vector<Service>& services) {
    if (services.empty()) {
        cout << "No services to delete.\n";
        return;
    }

    showServices(services);

    int index;
    cout << "Enter service number to delete: ";
    cin >> index;

    if (index < 1 || index > services.size()) {
        cout << "Invalid service number.\n";
        return;
    }

    services.erase(services.begin() + (index - 1));
    cout << "Service deleted successfully.\n";
}

void deleteProvider(vector<Provider>& providers) {
    if (providers.empty()) {
        cout << "No providers available to delete.\n";
        return;
    }

    cout << "\n=== Providers ===\n";
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

void searchService(const vector<Service>& services) {
    if (services.empty()) {
        cout << "No services available.\n";
        return;
    }

    string target;
    cout << "Enter service name to search: ";
    cin.ignore();
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

int selectProvider(const vector<Provider>& providers) {
    if (providers.empty()) {
        cout << "No providers available.\n";
        return -1;
    }

    cout << "\n=== Providers ===\n";
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

int main() {
    vector<Provider> providers;

    Provider p;
    p.profile["name"] = "Aifa Magracia";
    p.profile["email"] = "25-00374@g.batstate-u.edu.ph";
    p.profile["phone"] = "09944651496";
    p.services = { {"Web Design", 150.0}, {"Programming", 200.0}, {"Tutoring", 50.0} };
    providers.push_back(p);

    int choice;
    do {
        cout << "\n === SERVIFY === \n";
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
                if (index == -1) break;

                Provider& selected = providers[index];
                int subChoice;
                do {
                    cout << "\n --- Manage Provider: " << selected.profile["name"] << " ---\n";
                    cout << "1. Show Profile\n2. Edit Profile\n3. Show Services\n";
                    cout << "4. Add Service\n5. Edit Service\n6. Delete Service\n7. Search Service\n8. Back\n";
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
                            deleteService(selected.services); 
                            break;
                        case 7: 
                            searchService(selected.services); 
                            break;
                        case 8: 
                            break;
                        default: 
                            cout << "Invalid choice.\n";
                    }
                } while (subChoice != 8);
                break;
            }
            case 2: {
                Provider newProvider;
                cout << "Enter provider name: "; getline(cin, newProvider.profile["name"]);
                cout << "Enter email: "; getline(cin, newProvider.profile["email"]);
                cout << "Enter phone: "; getline(cin, newProvider.profile["phone"]);
                providers.push_back(newProvider);
                cout << "Provider added successfully.\n";
                break;
            }
            case 3: 
                deleteProvider(providers);
                break;
            case 4: 
                cout << "Program ended.\n"; 
                break;
            default: 
                cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}