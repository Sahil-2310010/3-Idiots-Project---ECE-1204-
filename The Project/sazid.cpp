#include <iostream>
using namespace std;
int balance;
int feast_price;
string hall;
string time;
// Generic function
template <class T>
T addBalance(T amount) {
    try {
        if (amount < 0) {
            throw "Invalid Amount";
        }
        else
        {
            return balance + amount;
        }
        
    } 
    catch (const char* e) {
        cout << e << endl;
        return balance; // return current balance if invalid
    }
}


//Generic Function for Balance Checking

template<class S>
void CheckBalance(S &balance)
{
    try{
        //For Negative balance
     if(balance<0)
     {
         throw "Invalid Balance";   //Exception
     }
     else
     {
         cout<<"Your Curent Balance: "<<balance<<endl;  //Valid Balance
     }
    }

    catch(const char*p)
    {
        cout<<p<<endl;  //error message  
    }
        
}

// Admin

class Admin {                            // Admin class to manage feast settings
                                        //Admin doesnt have the authority to cancel a student's token or id
    string password = "101820";
    string name = "SZS23";
    
    int price;

public:

    void signin(string pass, string nm) {
        while(true){
        if (password == pass && name == nm) {
            cout << "Welcome Admin" << endl;
            break;
            
        } else {
            cout << "Incorrect Details!" << endl;
            ;
        }
    
        }
    }

    void setFeast() {
        cout << "Which hall do you set for feast?\n 1.Zia\n 2.Bongobondhu\n 3.Tinshed\n 4.Hamid\n 5.Selim\n 6.Shohidul\n" << endl;
        int a;
        cin >> a;
        switch (a) {
            case 1:
                hall = "Zia";
                break;
            case 2:
                hall = "Bongobondhu";
                break;
            case 3:
                hall = "Tinshed";
                break;
            case 4:
                hall = "Hamid";
                break;
            case 5:
                hall = "Selim";
                break;
            case 6:
                hall = "Shohidul";
                break;
            
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


class Hall: public Admin{
    int regular_token=40;
    int feast_token= feast_price; // Price of feast token, set by admin;

public:
    int getRegularToken() {
        return regular_token;
    }

    int getFeastToken() {  // Function to get the feast token price
        return feast_price;
    }
    void buyRegularToken();
    void buyFeastToken();
    void halllist();
    virtual void buy() = 0;
};
void Hall::halllist() {
    cout << "Available Halls:" << endl;
    cout << "1. Zia Hall" << endl;
    cout << "2. Bongobondhu Hall" << endl;
    cout << "3. Tinshed Hall" << endl;
    cout << "4. Hamid Hall" << endl;
    cout << "5. Selim Hall" << endl;
    cout << "6. Shohidul Hall" << endl;
}

void Hall::buyRegularToken() {

        cout << "Want to buy \n1.Lunch token\n2.Dinner token\n3.Both" << endl;
        
        int abc;
        cin >> abc;
        if (abc == 1) {
            if(balance >= getRegularToken()) {
                balance -= getRegularToken();
                cout << "Regular token for lunch bought successfully!" << endl;
            } else {
                cout << "Insufficient balance for regular token." << endl;
            }
    }
    else if (abc == 2) {
        if(balance >= getRegularToken()) {
            balance -= getRegularToken();
            cout << "Regular token for dinner bought successfully!" << endl;
        } else {
            cout << "Insufficient balance for regular token." << endl;
        }
    }
    else if (abc == 3) {
        if(balance >= 2 * getRegularToken()) {
            balance -= 2 * getRegularToken();
            cout << "Regular tokens for both lunch and dinner bought successfully!" << endl;
        } else {
            cout << "Insufficient balance for regular tokens." << endl;
        }
    }
    else{
        cout << "Invalid choice!" << endl;
    }
    
    

};

void Hall::buyFeastToken() {

try {
    if (getFeastToken() > balance) {
        throw "Insufficient balance!";
    }
    else {
        cout << "Feast token bought successfully!" << endl;
    }
    
    balance -= getFeastToken();
    cout << "Remaining balance: " << balance << " tk" << endl;

}
catch (const char* s) {
    cout << s << endl;
    
}
};

class SpecificHall: public Hall {
public:
    void buy() override {
        halllist();
        cout << "N.B: Feast available for " << hall << " at " << time << endl;
        cout << "Choose a hall to buy token:" << endl;
        int hall_choice;
        cin >> hall_choice;
        switch (hall_choice) {
            case 1:
                hall = "Zia";
                break;
            case 2:
                hall = "Bongobondhu";
                break;
            case 3:
                hall = "Tinshed";
                break;
            case 4:
                hall = "Hamid";
                break;
            case 5:
                hall = "Selim";
                break;
            case 6:
                hall = "Shohidul";
                break;
            default:
                cout << "Invalid Hall" << endl;
                return; // Exit if invalid hall
        }

        cout << "1. Buy Regular Token" << endl;
        cout << "2. Buy Feast Token (chose hall with feast to buy feast token)" << endl;

        int choice;
        cin >> choice;
        if (choice == 1) {
            buyRegularToken(); // Buy regular token
        } else if (choice == 2) {
            buyFeastToken(); // Buy feast token
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
};


int main() {
    while (true) {  
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as Student" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            Admin admin;
            cout << "Enter Admin Password: ";
            string pass;
            cin >> pass;
            cout << "Enter Admin Name: ";
            string name;
            cin >> name;
            admin.signin(pass, name);

            // Admin loop
            while (true) {
                cout << "\n-- Admin Menu --" << endl;
                cout << "1. Set Feast" << endl;
                cout << "2. Back to Main Menu" << endl;
                int admin_choice;
                cin >> admin_choice;
                if (admin_choice == 1) {
                    admin.setFeast();
                    cout << "Feast set for hall " << hall<< " at " <<time << endl;
                } else if (admin_choice == 2) {
                    break; 
                } else {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        else if (choice == 2) {
           
            while (true) {
                cout << "\n-- Student Menu --" << endl;
                cout << "1. Buy Token" << endl;
                cout << "2. Check Balance" << endl;
                cout << "3. Add money to balance" << endl;
                cout << "4. Back to Main Menu" << endl;
                int student_choice;
                cin >> student_choice;

                if (student_choice == 1) {
                    Hall *p;
                    SpecificHall h;
                    p = &h;
                    p->buy(); 
                } 
                else if (student_choice == 2) {
                    CheckBalance(balance);
                } 
                else if (student_choice == 3) {
                    int add;
                    cout << "Enter amount to add: ";
                    cin >> add;
                    balance = addBalance(add);
                    CheckBalance(balance);
                }
                else if (student_choice == 4) {
                    break; 
                }
                else {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
        else if (choice == 3) {
            cout << "Exiting program. Goodbye!" << endl;
            break; 
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
}
