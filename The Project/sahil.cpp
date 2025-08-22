#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;

// int balance;
int feast_price;
string hall;
// string time;

// Generic Function to CHECK BALANCE
template<class S>
void CheckBalance(const S &balance)
{
    try {
     if(balance < 0) //For Negative balance
         throw "Invalid Balance";   //Exception

     else
        cout << "Your Cuurent Balance: " << balance << endl;  //Valid Balance
    }

    catch(const char *p) {
        cout << p << endl;  //error message
    }
}



class Person {
protected:
    string name;
    string password;
    
};

class Student : public Person {
private:
    string department;
    int series;
    int id;
    float balance;

public:
    string getName() { return name; }
    string getpassword() { return password; }
    string getDept() { return department; }
    int getSeries() { return series; }
    int getId() { return id; }
    float getBalance() { return balance; }

    void setBalance(float bal) { 
        if(balance + bal >= 0) {
            balance += bal;
            cout << "Balance updated! New balance: " << balance << endl;
        }
        else
            cout << "Insufficient balance!\n";    
    }

    void setDetails(); // Set all necessary details for Student

    // Making JSON functions friends so that they can access pivate & protected members
    friend Student student_from_json(const json &j);
    friend json student_to_json(const Student &s);
};

// Set all necessary details for Student
void Student :: setDetails() 
{
    balance = 0.00;
    cout << "Enter series: ";
    cin >> series;
    cout << "Enter department name: ";
    cin >> department;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter your roll (ID): ";
    cin >> id;

    string password1, password2;
    while (true) {
        cout << "Enter password: ";
        cin >> password1;
        cout << "Confirm password: ";
        cin >> password2;
        if (password1 == password2) break;
        cout << "Passwords do not match! Try again.\n";
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
    s.balance = j.value("balance", 0);
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
    for (auto &s : students) {
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
        cout << "Balance updated in JSON file.\n";
    } else {
        cout << "Student ID not found!\n";
    }
}



class Admin : public Person {
public:
    Admin() {
        name = "SZS23";
        password = "101820";
    }
    string time;

    bool signin(string pass, string nam) {
        if (password == pass && name == nam) {
            cout << "Welcome Admin" << endl;
            return true;
        } else {
            cout << "Incorrect Details!" << endl;
            return false;
        }
    }

    void setFeast() {
        cout << "Which hall do you set for feast?\n 1.Zia\n 2.Bongobondhu\n 3.Tinshed\n 4.Hamid\n 5.Selim\n 6.Shohidul\n" << endl;
        int a;
        cin >> a;
        switch (a) {
            case 1: hall = "Zia"; break;
            case 2: hall = "Bongobondhu"; break;
            case 3: hall = "Tinshed"; break;
            case 4: hall = "Hamid"; break;
            case 5: hall = "Selim"; break;
            case 6: hall = "Shohidul"; break;
        }

        cout << "Time?\n 1.Lunch \n 2.Dinner" << endl;
        int t;
        cin >> t;
        
        if (t == 1) {
            time = "Lunch";
            cout << "Feast set for Lunch" << endl;
        } else if (t == 2) {
            time = "Dinner";
            cout << "Feast set for Dinner" << endl;
        }

        cout << "What is the price of the feast?" << endl;
        cin >> feast_price;
        cout << "Feast set for " << hall << endl;
    }
};



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

// Add purchase (rules: maximum 200, no duplicate in same date with same time)
bool addPurchase(const string &purchase_file, int studentId, const string &time) {
    json data = loadPurchases(purchase_file);
    string today = getTodayDate();

    // Check if student already bought the Token
    for (auto &entry : data) {
        if (entry["studentId"] == studentId && entry["date"] == today && entry["time"] == time) {
            cout << "You already purchased a token today!" << endl;
            return false;
        }
    }

    // If more than 200 then reset file
    if (data.size() >= 200) {
        cout << "Resetting purchase history (limit reached)." << endl;
        data = json::array();
    }

    // Add new record
    json newEntry = {
        {"studentId", studentId},
        {"date", today},
        {"time", time}
    };
    data.push_back(newEntry);

    savePurchases(purchase_file, data);

    cout << "Token purchased successfully on " << today << endl;
    return true;
}

// Show all purchases for a student
void viewPurchases(const string &purchase_file, int studentId) {
    json data = loadPurchases(purchase_file);
    cout << "--- Your Purchases ---\n";
    bool found = false;
    for (auto &entry : data) {
        if (entry["studentId"] == studentId) {
            cout << "Date: " << entry["date"]
                 << " | Token: " << entry["time"] << endl;
            found = true;
        }
    }
    if (!found) cout << "No purchases found.\n";
}




int main() 
{
    while (true) {
        auto students = loadStudents();           // load all students

        cout << "\n===== Main Menu =====\n" ;
        cout << "1. Login/Signup as Student\n";
        cout << "2. Login as Admin\n";
        cout << "3. Exit Program\n";
        cout << "Enter choice: ";
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
                    if (s.getId() == id && s.getpassword() == password) {
                        cout << "\nLogin successful!\n\n===Welcome to Hall Automation " << s.getName() << "===" << endl;
                        found = true;
                        st = &s;
                        break;
                    }
                }
                if (!found) cout << "Invalid ID or password.\n";
                else if (found)
                {
                    while(true)
                    {
                        cout << "1. Buy Meal Token\n";
                        cout << "2. View Purchase status\n";
                        cout << "3. Check Balance\n";
                        cout<< "4. Add Balance to Wallet\n";
                        cout << "5. Return to main menu\n";
                        int choice;
                        cin >> choice;

                        if (choice == 1) // Buy Token
                        {
                            cout << "1. Lunch Token\n2. Dinner Token\n";
                            int time;
                            cin >> time;
                            
                            if(st->getBalance() >= 40)
                            {
                                if (addPurchase("purchases.json", id, ((time == 1) ? "Lunch" : "Dinner"))) {
                                    
                                    for (auto &s : students)
                                    {
                                        if (s.getId() == id) {
                                            s.setBalance(-40);  // Deduct price from balance
                                            break;
                                        }
                                    }
                                    saveStudents(students); // Save updated vector to JSON
                                }
                            } 
                            else {
                                cout << "Insufficient Balance! Recharge first.\n";
                            }
                                
                        }
                        else if (choice == 2) {     // Purchase history
                        
                            viewPurchases("purchases.json", id);
                        }
                        else if (choice == 3) {     // Check balance
                            CheckBalance(st->getBalance());
                        }
                        else if (choice == 4)       // Add balance to Wallet
                        {
                            float amnt;
                            cin >> amnt;
                            
                            updateStudentBalance(students, id, amnt); // Update balance in vector and JSON
                        }
                        else if(choice == 5) {      // Returns to the main-menu
                            break;
                        }  
                        else
                            cout << "Invalid choice!";
                    }
                }
            }

            else if (log_sign == 2) // Student signup
            {   
                Student s;
                s.setDetails();     // Setting information for new student
                auto students = loadStudents();
                students.push_back(s);
                saveStudents(students);     // Saving new Student in the students.json file
                cout << "Sign Up successful! Now you can login.\n";
            }
        }
        
        else if (x == 2) // Admin Part
        { 
            Admin admin;

            cout << "Enter Admin Password: ";
            string pass;
            cin >> pass;
            
            cout << "Enter Admin Name: ";
            string nm;
            cin >> nm;

            if (!admin.signin(pass, nm)) {
                continue; // only go to Admin Menu if signin success
            }
            cout << "\n-- Admin Menu --\n";
            cout << "1. Set Feast\n";
            cout << "2. Back to Main Menu\n";

            int admin_choice;
            cin >> admin_choice;

            if (admin_choice == 1) 
            {
                admin.setFeast();
                cout << "Feast set for hall " << hall << " at " << time << endl;
            }
            else if (admin_choice == 2)
                break;
            else
                cout << "Invalid choice!" << endl;
        }

        else if (x == 3) // Exit Program
        {
            cout << "Program stopped!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
            
    }
}
