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
    return 0;
}
