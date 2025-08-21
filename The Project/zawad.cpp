#include<iostream>
using namespace std;
int balance = 1000;

template<class T>
class AddBalance{
 T amount;

 public:
     AddBalance(T amnt)
     {
         try{
         if(amnt<0)
         {
             throw "Invalid Amount";
         }
         else
         {
             amount =amnt;
         }
         }
         catch(const char*e)
         {
             cout<<e<<endl;
             amount = 0;
         }

     }

     T getBalance()
     {
         return amount+balance;
     }
};

int main() {
    /*AddBalance<int> a1(500);
    cout << "Balance: " << a1.getBalance() << endl;

    AddBalance<int> a2(-100); // Will trigger exception
    cout << "Balance: " << a2.getBalance() << endl;
    */
    return 0;
}
