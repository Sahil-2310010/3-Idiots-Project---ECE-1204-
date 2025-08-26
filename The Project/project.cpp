#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <ctime>

using namespace std;
using json = nlohmann::json;

// Generic Function to CHECK BALANCE
template<class S>
void CheckBalance(const S &balance)
{
    try {
        if(balance < 0) // For Negative balance
            throw "Invalid Balance";   // Exception
        else
            cout << "========= Account Summary =========" << endl;
            cout << "   Current Balance : " << balance << endl;
            cout << "===================================" << endl;
  // Valid Balance
    }
    catch(const char *p) {
        cout << "[ ERROR ] -> " << p << endl;   // Error message
    }
}

// Base class Person
class Person {
protected:
    string name;
    string password;
    string hall;
    int feast_price = 60;  // Default feast price
    int regular_price = 40;

    void setFeastPrice(int price) { feast_price = price; }

public:
    int getFeastPrice() const { return feast_price; }
    int getRegularPrice() const { return regular_price; }
    string getHall() const { return hall; }
    void setHall(const string& h) { hall = h; }
};

// Forward declaration for friend functions
class Student;
Student student_from_json(const json &j);
json student_to_json(const Student &s);

// Student class inherited from Person
class Student : virtual public Person {
private:
    string department;
    int series;
    int id;
    float balance;

public:
    Student() : balance(0.0), series(0), id(0) {}
    
    string getName() const { return name; }
    string getPassword() const { return password; }
    string getDept() const { return department; }
    int getSeries() const { return series; }
    int getId() const { return id; }
    float getBalance() const { return balance; }

    void setBalance(float bal) { 
        if(balance + bal >= 0) {
            balance += bal;
            cout << "==========Balance Updated!==========" << endl;
            cout << " New Balance : " << balance << endl;
            cout << "====================================" << endl;

        }
        else
            cout << "+----------------------------------+" << endl;
            cout << "|        Insufficient Balance!     |" << endl;
            cout << "+----------------------------------+" << endl;
    
    }

    void setDetails(); // Set all necessary details for Student

    // Making JSON functions friends so that they can access private & protected members
    friend Student student_from_json(const json &j);
    friend json student_to_json(const Student &s);
};

// Set all necessary details for Student
void Student::setDetails() {
    cout << "+----------------------------------+" << endl;
    cout << "|      Student Registration Form   |" << endl;
    cout << "+----------------------------------+" << endl;

    balance = 0.00;
    cout << "| Series         : ";
    cin >> series;

    cout << "| Department     : ";
    cin >> department;

    cout << "| Name           : ";
    cin.ignore();
    getline(cin, name);

    cout << "| Roll (ID)      : ";
    cin >> id;

    cout << "+----------------------------------+" << endl;


    string password1, password2;
    while (true) {
        cout << "+-----------------------------+" << endl;
        cout << "|       Set Your Password     |" << endl;
        cout << "+-----------------------------+" << endl;

        cout << "| Enter Password   : ";
        cin >> password1;

        cout << "| Confirm Password : ";
        cin >> password2;

        if (password1 == password2) {
            cout << "+-----------------------------+" << endl;
            cout << "|  Password set successfully! |" << endl;
            cout << "+-----------------------------+" << endl;
            break;
        } 
        else {
            cout << "| Passwords do not match!   |" << endl;
            cout << "| Try again...              |" << endl;
            cout << "+---------------------------+" << endl;
        }
    }

    
    password = password1;
}

// Student to JSON
json student_to_json(const Student &s) {
    return {
        {"id", s.id},
        {"name", s.name},
        {"password", s.password},
        {"balance", s.balance},
        {"department", s.department},
        {"series", s.series}
    };
}

// JSON to Student
Student student_from_json(const json &j) {
    Student s;
    s.id = j.value("id", 0);
    s.name = j.value("name", "");
    s.password = j.value("password", "");
    s.balance = j.value("balance", 0.0f);
    s.department = j.value("department", "");
    s.series = j.value("series", 0);
    return s;
}

// Load Students from students.json
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream in("students.json");
    if (in) {
        try {
            json j;
            in >> j;
            if (j.is_array()) {
                for (auto &item : j) {
                    students.push_back(student_from_json(item));
                }
            }
        } catch (...) {
            cerr << "Error reading students.json, starting fresh.\n";
        }
    }
    return students;
}

// Save Students to students.json
void saveStudents(const vector<Student> &students) {
    json j = json::array();
    for (const auto &s : students) {
        j.push_back(student_to_json(s));
    }
    ofstream out("students.json");
    out << setw(4) << j << endl;
}

// Update Student Balance in json file
void updateStudentBalance(vector<Student> &students, int studentId, float amount) {
    bool found = false;
    for (auto &s : students) {
        if (s.getId() == studentId) {
            s.setBalance(amount);    // update object in memory
            found = true;
            break;
        }
    }
    if (found) {
        saveStudents(students);      // save updated vector to JSON
        cout << "========================" << endl;
        cout << "    Balance updated!   " << endl;
        cout << "========================" << endl;

    } else {
        cout << "===========================" << endl;
        cout << "   STUDENT ID NOT FOUND!   " << endl;
        cout << "===========================" << endl;

    }
}

// Global feast configuration storage
struct FeastConfig {
    string hall;
    string time;
    int price;
    bool isSet;
    
    FeastConfig() : price(60), isSet(false) {}
};

FeastConfig currentFeast;

// Admin class inherited from Person
class Admin : virtual public Person {
public:
    void configurePrice(int feast) {  // Set prices for Feast Token and Regular Token
        setFeastPrice(feast);
        currentFeast.price = feast;
    }

    Admin() {
        name = "SZS23";
        password = "101820";
    }
    
    string time;

    bool signin(const string& pass, const string& nam) {
        if (password == pass && name == nam) {
            cout << "+----------------------------------+" << endl;
            cout << "|           Welcome Admin          |" << endl;
            cout << "+----------------------------------+" << endl;


            return true;
        } else {
            cout << "====================================" << endl;
            cout << "           INCORRECT DETAILS!       " << endl;
            cout << "====================================" << endl;

            return false;
        }
    }
    
    void setFeast(); // Setting feast for specific halls with feast_price
};

void Admin::setFeast() {     
    cout << "+----------------------------------+" << endl;
    cout << "|         Select Feast Hall        |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "| 1. Zia                           |" << endl;
    cout << "| 2. Bongobondhu                   |" << endl;
    cout << "| 3. Tinshed                       |" << endl;
    cout << "| 4. Hamid                         |" << endl;
    cout << "| 5. Selim                         |" << endl;
    cout << "| 6. Shohidul                      |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "Enter your choice: ";
    
    int a;
    cin >> a;
    switch (a) {
        case 1: hall = "Zia"; break;
        case 2: hall = "Bongobondhu"; break;
        case 3: hall = "Tinshed"; break;
        case 4: hall = "Hamid"; break;
        case 5: hall = "Selim"; break;
        case 6: hall = "Shohidul"; break;
        default: 
            cout << "+----------------------------------+" << endl;
            cout << "|       INVALID HALL SELECTION!    |" << endl;
            cout << "+----------------------------------+" << endl;
            return;
    }
    currentFeast.hall = hall;

    cout << "+----------------------------------+" << endl;
    cout << "|           Select Time            |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "| 1. Lunch                         |" << endl;
    cout << "| 2. Dinner                        |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "Enter your choice: ";

    int t;
    cin >> t;
    
    if (t == 1) {
        time = "Lunch";
    } else if (t == 2) {
        time = "Dinner";
    } else {
        cout << "====================================" << endl;
        cout << "         INVALID TIME SELECTION!    " << endl;
        cout << "====================================" << endl;

        return;
    }
    currentFeast.time = time;
    
    cout << "+----------------------------------+" << endl;
    cout << "|      Enter Feast Token Price      |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "| Price: ";
    
    cin >> feast_price;
    configurePrice(feast_price);
    currentFeast.isSet = true;

    cout << "+----------------------------------+"  << endl;
    cout << "|        Feast Set Successfully     |" << endl;
    cout << "+----------------------------------+"  << endl;
    cout << "| Hall        : "              << hall << endl;
    cout << "| Time        : "              << time << endl;
    cout << "| Feast Price : "       << feast_price << endl;
    cout << "+----------------------------------+"  << endl;

}

// Hall class inherited from Student & Admin
class Hall : public Student, public Admin {
private:
    int regular_token;
    int feast_token;

public:
    Hall() {
        regular_token = getRegularPrice();
        feast_token = getFeastPrice();
    }

    int getRegularToken() const {
        return regular_token;
    }

    int getFeastToken() const {
        return feast_token;
    }

    void buyRegularToken(int studentId, const string& selectedHall, const string& mealTime);
    void buyFeastToken(int studentId, const string& selectedHall, const string& mealTime);
    void hall_list() const;
    virtual void buy() = 0; // Pure virtual function
};

// Concrete implementation class
class MealTokenSystem : public Hall {
public:
    void buy() override {
        cout << "+----------------------------------+" << endl;
        cout << "|   Meal Token Purchase System     |" << endl;
        cout << "|            ACTIVATED             |" << endl;
        cout << "+----------------------------------+" << endl;
            
    }
};

// Hall list implementation
void Hall::hall_list() const {
    cout << "+----------------------------------+" << endl;
    cout << "|           Available Halls         |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "| 1. Zia Hall                       |" << endl;
    cout << "| 2. Bongobondhu Hall               |" << endl;
    cout << "| 3. Tinshed Hall                   |" << endl;
    cout << "| 4. Hamid Hall                     |" << endl;
    cout << "| 5. Selim Hall                     |" << endl;
    cout << "| 6. Shohidul Hall                  |" << endl;
    cout << "+----------------------------------+" << endl;

}

// Buy Regular Token implementation
void Hall::buyRegularToken(int studentId, const string& selectedHall, const string& mealTime) {
    cout << "Purchasing Regular Token for " << selectedHall << " - " << mealTime << endl;
    cout << "Price: " << regular_token << " Taka" << endl;
}

// Buy Feast Token implementation
void Hall::buyFeastToken(int studentId, const string& selectedHall, const string& mealTime) {
    if (!currentFeast.isSet) {
        cout << "No feast is currently set by admin!" << endl;
        return;
    }
    
    if (currentFeast.hall != selectedHall || currentFeast.time != mealTime) {
        cout << "Feast is not available for " << selectedHall << " - " << mealTime << endl;
        cout << "Current feast: " << currentFeast.hall << " - " << currentFeast.time << endl;
        return;
    }
    
    cout << "Purchasing Feast Token for " << selectedHall << " - " << mealTime << endl;
    cout << "Price: " << currentFeast.price << " Taka" << endl;
}

// ---------- Meal Token Handling ----------

// Get today's date in Year-Month-Day format
string getTodayDate() 
{
    time_t t = time(0);
    tm *now = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    return string(buffer);
}

// Load purchases from purchases.json
json loadPurchases(const string &purchase_file) {
    ifstream in(purchase_file);
    json data;
    if (in.is_open()) 
    {
        try {
            in >> data;
        } catch (...) {
            cerr << "Error reading purchases.json, starting fresh.\n";
        }
        in.close();
    }
    if (!data.is_array()) data = json::array();
    return data;
}

// Save purchases to purchases.json
void savePurchases(const string &purchase_file, const json &data) {
    ofstream out(purchase_file);
    out << setw(4) << data << endl;
    out.close();
}

// Add purchase (rules: maximum 100, no duplicate in same date with same time)
bool addPurchase(const string &purchase_file, int studentId, const string &time, const string &hall, const string &tokenType, int price) {
    json data = loadPurchases(purchase_file);
    string today = getTodayDate();

    // Check if student already bought the same token today
    for (const auto &entry : data) {
        if (entry["studentId"] == studentId && entry["date"] == today && 
            entry["time"] == time && entry["hall"] == hall) {
            cout << "You already purchased a " << tokenType << " token for " << hall << " - " << time << " today!" << endl;
            return false;
        }
    }

    // If more than 100 entries, keep only the last 30
    if (data.size() >= 100) {
        cout << "Purchase history limit reached. Keeping last 30 entries and removing older ones.\n";
        json newData = json::array();
        for (size_t i = (data.size() > 30 ? data.size() - 30 : 0); i < data.size(); ++i) {
            newData.push_back(data[i]);
        }
        data = newData;
    }
    
    // Add new record
    json newEntry = {
        {"studentId", studentId},
        {"date", today},
        {"time", time},
        {"hall", hall},
        {"tokenType", tokenType},
        {"price", price}
    };
    data.push_back(newEntry);

    savePurchases(purchase_file, data);

    cout << tokenType << " token purchased successfully for " << hall << " - " << time << " on " << today << endl;
    return true;
}

// Show all purchases for a student
void viewPurchases(const string &purchase_file, int studentId) {
    json data = loadPurchases(purchase_file);
    cout << "\n=== Your Purchase History ===\n";
    bool found = false;
    for (const auto &entry : data) {
        if (entry["studentId"] == studentId) {
            cout << "Date: " << entry["date"]
                 << " | Hall: " << entry.value("hall", "N/A")
                 << " | Time: " << entry["time"]
                 << " | Type: " << entry.value("tokenType", "Regular")
                 << " | Price: " << entry.value("price", 40) << " Taka" << endl;
            found = true;
        }
    }
    if (!found) cout << "No purchases found.\n";
}

// Helper function to get hall name from choice
string getHallName(int choice) {
    switch(choice) {
        case 1: return "Zia";
        case 2: return "Bongobondhu";
        case 3: return "Tinshed";
        case 4: return "Hamid";
        case 5: return "Selim";
        case 6: return "Shohidul";
        default: return "";
    }
}

int main() 
{
    while (true) {
        auto students = loadStudents();           // load all students

        cout << "\n===== Main Menu =====\n";
        cout << "1. Login/Signup as Student\n";
        cout << "2. Login as Admin\n";
        cout << "3. Exit Program\n";
        cout << "\nEnter choice: ";
        int x;
        cin >> x;

        if (x == 1) // Student Part
        {
            cout << "1. Log In\n2. Sign Up\n";
            int log_sign;
            cin >> log_sign;

            if (log_sign == 1) // Student login
            {   
                int id;
                cout << "Enter ID: ";
                cin >> id;
                string password;
                cout << "Enter Password: ";
                cin >> password;

                bool found = false;
                Student *st = nullptr;
                for (auto &s : students)
                {
                    if (s.getId() == id && s.getPassword() == password) {
                        cout << "\nLogin successful!\n\n=== Welcome to Hall Automation " << s.getName() << " ===" << endl;
                        found = true;
                        st = &s;
                        break;
                    }
                }
                if (!found) {
                    cout << "Invalid ID or password.\n";
                }
                else if (found)
                {
                    while(true)
                    {
                        cout << "\n=== Student Menu ===\n";
                        cout << "1. Buy Meal Token\n";
                        cout << "2. View Purchase History\n";
                        cout << "3. Check Balance\n";
                        cout << "4. Add Balance to Wallet\n";
                        cout << "5. Return to main menu\n";
                        cout << "Enter choice: ";
                        int choice;
                        cin >> choice;

                        if (choice == 1) // Buy Token
                        {
                            cout << "\nWhich hall do you prefer?\n";
                            cout << "1. Zia Hall\n2. Bongobondhu Hall\n3. Tinshed Hall\n";
                            cout << "4. Hamid Hall\n5. Selim Hall\n6. Shohidul Hall\n";
                            cout << "Enter hall choice: ";
                            int hall_choice;
                            cin >> hall_choice;

                            string selectedHall = getHallName(hall_choice);
                            if (selectedHall.empty()) {
                                cout << "Invalid hall selection!\n";
                                continue;
                            }

                            cout << "\nSelect meal time:\n";
                            cout << "1. Lunch Token\n2. Dinner Token\n";
                            cout << "Enter time choice: ";
                            int time_choice;
                            cin >> time_choice;

                            string mealTime = (time_choice == 1) ? "Lunch" : "Dinner";
                            if (time_choice != 1 && time_choice != 2) {
                                cout << "Invalid time selection!\n";
                                continue;
                            }

                            cout << "\nSelect token type:\n";
                            cout << "1. Regular Token (40 Taka)\n";
                            cout << "2. Feast Token";
                            if (currentFeast.isSet && currentFeast.hall == selectedHall && currentFeast.time == mealTime) {
                                cout << " (" << currentFeast.price << " Taka)";
                            } else {
                                cout << " (Not Available)";
                            }
                            cout << "\nEnter token type: ";
                            int token_type;
                            cin >> token_type;

                            int tokenPrice = 40; // Default regular price
                            string tokenTypeStr = "Regular";

                            if (token_type == 2) { // Feast token
                                if (!currentFeast.isSet) {
                                    cout << "No feast is currently set by admin!\n";
                                    continue;
                                }
                                if (currentFeast.hall != selectedHall || currentFeast.time != mealTime) {
                                    cout << "Feast is not available for " << selectedHall << " - " << mealTime << endl;
                                    cout << "Current feast: " << currentFeast.hall << " - " << currentFeast.time << endl;
                                    continue;
                                }
                                tokenPrice = currentFeast.price;
                                tokenTypeStr = "Feast";
                            } else if (token_type != 1) {
                                cout << "Invalid token type selection!\n";
                                continue;
                            }
                            
                            if (st->getBalance() >= tokenPrice) {
                                if (addPurchase("purchases.json", id, mealTime, selectedHall, tokenTypeStr, tokenPrice)) {
                                    // Deduct price from balance
                                    for (auto &s : students) {
                                        if (s.getId() == id) {
                                            s.setBalance(-tokenPrice);
                                            break;
                                        }
                                    }
                                    saveStudents(students); // Save updated vector to JSON
                                }
                            } else {
                                cout << "Insufficient Balance! You need " << tokenPrice << " Taka. Current balance: " << st->getBalance() << " Taka\n";
                            }
                        }
                        else if (choice == 2) {     // Purchase history
                            viewPurchases("purchases.json", id);
                        }
                        else if (choice == 3) {     // Check balance
                            CheckBalance(st->getBalance());
                        }
                        else if (choice == 4) {     // Add balance to Wallet
                            cout << "Enter amount to add: ";
                            float amount;
                            cin >> amount;
                            
                            if (amount <= 0) {
                                cout << "Invalid amount! Please enter a positive value.\n";
                                continue;
                            }
                            
                            updateStudentBalance(students, id, amount); // Update balance in vector and JSON
                            // Refresh local student pointer
                            for (auto &s : students) {
                                if (s.getId() == id) {
                                    st = &s;
                                    break;
                                }
                            }
                        }
                        else if (choice == 5) {      // Returns to the main-menu
                            break;
                        }  
                        else {
                            cout << "Invalid choice!\n";
                        }
                    }
                }
            }
            else if (log_sign == 2) // Student signup
            {   
                Student s;
                s.setDetails();     // Setting information for new student
                
                // Check if ID already exists
                bool idExists = false;
                for (const auto& student : students) {
                    if (student.getId() == s.getId()) {
                        cout << "ID already exists! Please try with a different ID.\n";
                        idExists = true;
                        break;
                    }
                }
                
                if (!idExists) {
                    students.push_back(s);
                    saveStudents(students);     // Saving new Student in the students.json file
                    cout << "Sign Up successful! Now you can login.\n";
                }
            }
        }
        else if (x == 2) // Admin Part
        { 
            Admin admin;

            cout << "Enter Admin Name: ";
            string nm;
            cin >> nm;
            
            cout << "Enter Admin Password: ";
            string pass;
            cin >> pass;

            if (!admin.signin(pass, nm)) {
                continue; // only go to Admin Menu if signin success
            }
            
            while (true) {
                cout << "\n=== Admin Menu ===\n";
                cout << "1. Set Feast\n";
                cout << "2. View Current Feast Settings\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter choice: ";

                int admin_choice;
                cin >> admin_choice;

                if (admin_choice == 1) {
                    admin.setFeast();
                }
                else if (admin_choice == 2) {
                    if (currentFeast.isSet) {
                        cout << "\n=== Current Feast Settings ===\n";
                        cout << "Hall: " << currentFeast.hall << endl;
                        cout << "Time: " << currentFeast.time << endl;
                        cout << "Price: " << currentFeast.price << " Taka" << endl;
                    } else {
                        cout << "No feast is currently set.\n";
                    }
                }
                else if (admin_choice == 3) {
                    break;
                }
                else {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        else if (x == 3) // Exit Program
        {
            cout << "Thank you for using Hall Automation System!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}
