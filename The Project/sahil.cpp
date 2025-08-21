#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

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

public:
    string getName() { return name; }
    string getpassword() { return password; }
    string getDept() { return department; }
    int getSeries() { return series; }
    int getId() { return id; }

    void setDetails(); // Set all necessary details for student

    // Making JSON functions friends so that they can access pivate & protected members
    friend Student student_from_json(const json &j);
    friend json student_to_json(const Student &s);
};

// Set all necessary details for student
void Student :: setDetails() 
{
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



class Admin : public Person {
private:
    string admin_id;

public:
    string getAdmin_id() { return admin_id; }
    string getHall_name() { return name; }
    string getPassword() { return password; }

    void setAdminDetails(); // Set all necessary details for admin

    // Making JSON functions friends so that they can access pivate & protected members
    friend Admin admin_from_json(const json &j);
    friend json admin_to_json(const Admin &ad);
};

// Set all necessary details for admin
void Admin :: setAdminDetails()
{
    cout << "Enter hall name: ";
    cin >> name;

    cout << "Enter ID: ";
    cin.ignore();
    getline(cin, admin_id);

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

// Admin to JSON
json admin_to_json(const Admin &ad)
{
    return {
        {"hall_name", ad.name},
        {"admin_id", ad.admin_id},
        {"password", ad.password}
    };
}

// JSON to Admin
Admin admin_from_json(const json &j)
{
    Admin ad;

    ad.admin_id = j.value("admin_id", "");
    ad.name = j.value("hall_name", "");
    ad.password = j.value("password", "");

    return ad;
}

// Load Admins from admins.json
vector<Admin> loadAdmins() 
{
    vector<Admin> admins;

    ifstream in("admins.json");

    if(in)
    {
        try {
            json j;
            in >> j;
            if (j.is_array()) {
                for (auto &item : j) {
                    admins.push_back(admin_from_json(item));
                }
            }
        } catch (...) {
            cerr << "Error reading admins.json, starting fresh.\n";
        }
    }
    return admins;
}

// Save Admins to admins.json
void saveAdmins(const vector<Admin> &admins) 
{
    json j = json::array();
    for (auto &ad : admins) {
        j.push_back(admin_to_json(ad));
    }
    ofstream out("admins.json");
    out << setw(4) << j << endl;
}

int main() {
    while (true) {
        cout << "---Choose any of these---\n1. I am student\n2. I am admin\n3. Exit program\n";
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

                auto students = loadStudents();  // Load all Students from students.json file
                bool found = false;
                for (auto &s : students) {
                    if (s.getId() == id && s.getpassword() == password) {
                        cout << "Login successful! Welcome " << s.getName() << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid ID or password.\n";

            }
            else if (log_sign == 2) // Student signup
            {   
                Student s;
                s.setDetails();
                auto students = loadStudents();
                students.push_back(s);
                saveStudents(students);
                cout << "Sign Up successful! You can now log in.\n";
            }
        }
        
        else if (x == 2) // Admin Part
        { 
            cout << "1. Log In\n2. Sign Up\n";
            int log_sign;
            cin >> log_sign;
            
            if (log_sign == 1) // Admin login
            {
                string admin_id;
                cout << "Enter Admin-ID: ";
                cin >> admin_id;
                string password;
                cout << "Enter Password: ";
                cin >> password;

                auto admins = loadAdmins();  // Load all Admins from admins.json file
                bool found = false;
                for (auto &ad : admins) {
                    if (ad.getAdmin_id() == admin_id && ad.getPassword() == password) {
                        cout << "Login successful! Welcome " << ad.getAdmin_id() << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid ID or password.\n";
            }
            else if(log_sign == 2) // Admin signup
            { 
                Admin ad;
                ad.setAdminDetails();
                auto admins = loadAdmins();
                admins.push_back(ad);
                saveAdmins(admins);
            }
        }
        else if (x == 3) {
            cout << "Program stopped!\n";
            break;
        }
    }
}
