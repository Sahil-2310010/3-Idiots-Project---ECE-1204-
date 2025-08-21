#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

class Person {
protected:
    string name;
    string pin;
};

class Student : public Person {
private:
    string department;
    int series;
    int id;

public:
    string getName() { return name; }
    string getPin() { return pin; }
    string getDept() { return department; }
    int getSeries() { return series; }
    int getId() { return id; }

    void setDetails();

    // Making JSON functions friends so that they can access pivate & protected members
    friend Student from_json(const json &j);
    friend json to_json(const Student &s);
};

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

    string pin1, pin2;
    while (true) {
        cout << "Enter password: ";
        cin >> pin1;
        cout << "Confirm password: ";
        cin >> pin2;
        if (pin1 == pin2) break;
        cout << "Passwords do not match! Try again.\n";
    }
    pin = pin1;
}

// Student to JSON
json to_json(const Student &s) {
    return {
        {"id", s.id},
        {"name", s.name},
        {"pin", s.pin},
        {"department", s.department},
        {"series", s.series}
    };
}

// JSON to Student
Student from_json(const json &j) {
    Student s;
    s.id = j.value("id", 0);
    s.name = j.value("name", "");
    s.pin = j.value("pin", "");
    s.department = j.value("department", "");
    s.series = j.value("series", 0);
    return s;
}

// Load students
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream in("students.json");
    if (in) {
        try {
            json j;
            in >> j;
            if (j.is_array()) {
                for (auto &item : j) {
                    students.push_back(from_json(item));
                }
            }
        } catch (...) {
            cerr << "Error reading students.json, starting fresh.\n";
        }
    }
    return students;
}

// Save students
void saveStudents(const vector<Student>& students) {
    json j = json::array();
    for (auto &s : students) {
        j.push_back(to_json(s));
    }
    ofstream out("students.json");
    out << setw(4) << j << endl;
}



class Admin : public Person {
public:

};

int main() {
    while (true) {
        cout << "---Choose any of these---\n1. I am student\n2. I am admin\n3. Exit program\n";
        int x;
        cin >> x;

        if (x == 1) {
            cout << "1. Log In\n2. Sign Up\n";
            int l;
            cin >> l;

            if (l == 1) {   // Login
                int id;
                cout << "Enter ID: ";
                cin >> id;
                string pin;
                cout << "Enter Password: ";
                cin >> pin;

                auto students = loadStudents();  // Load all students from student.json file
                bool found = false;
                for (auto &s : students) {
                    if (s.getId() == id && s.getPin() == pin) {
                        cout << "Login successful! Welcome " << s.getName() << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid ID or password.\n";

            } else if (l == 2) {   // Signup
                Student s;
                s.setDetails();
                auto students = loadStudents();
                students.push_back(s);
                saveStudents(students);
                cout << "Sign Up successful! You can now log in.\n";
            }
        }
        else if (x == 2) {
            cout << "Admin features coming soon...\n";
        }
        else if (x == 3) {
            cout << "Program stopped!\n";
            break;
        }
    }
}
