#include <iostream>
using namespace std;
int balance = 1000;
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
         cout<<"Your Cuurent Balance: "<<balance<<endl;  //Valid Balance
     }
    }

    catch(const char*p)
    {
        cout<<p<<endl;  //error message  
    }
        
}

// Admin

class Admin {
    string password = "Admin";
    string name = "Admin";
    string mealDay;

public:
    Admin(string pass, string nm) {
        if (password == pass && name == nm) {
            cout << "Welcome Admin" << endl;
            cout << "Choose Meal Day: ";
            cin >> mealDay;
        } else {
            cout << "Incorrect Details!" << endl;
        }
    }


    //Feast
    bool getFeast() {
        string day = mealDay;
        // Convert each character to lowercase
        for (size_t i = 0; i < day.length(); i++) {
            day[i] = tolower(day[i]);
        }

        if (day == "friday") {
            return true;
        } else {
            return false;
        }
    }


    //Regular
    bool getRegular() {
        string day = mealDay;
        // Convert each character to lowercase
        for (size_t i = 0; i < day.length(); i++) {
            day[i] = tolower(day[i]);
        }

        if (day != "friday") {
            return true;
        } else {
            return false;
        }
    }
};



int main() {
    
   /* AddBalance Test
   
   cout << "Balance after adding 500: " << addBalance(500) << endl;
    cout << "Balance after adding -100: " << addBalance(-100) << endl;
   */

    
/* CheckBalance Test

    int b1 = 1000;
    int b2 = -500;

    CheckBalance(b1);  // valid
    CheckBalance(b2);  // invalid, triggers exception
*/   

    
/* Admin Test
Admin ob("Admin", "Admin");
    if(ob.getFeast())
    {
        cout<<"Feast Available"<<endl;
    }
    else
    {
        cout<<"No Feast For The Selected Day"<<endl;
    }

    if(ob.getRegular())
    {
        cout<<"Regular Available"<<endl;
    }
    else
    {
        cout<<"No Regular Token For The Day, Try Fest"<<endl;
    }

    */
    return 0;
}
