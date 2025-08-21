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

int main() {
   /* cout << "Balance after adding 500: " << addBalance(500) << endl;
    cout << "Balance after adding -100: " << addBalance(-100) << endl;
    */
    return 0;
}
