#include<iostream>
using namespace std;
int balance = 1000; // Global variable for balance

class Hall{
    int regular_token=40;
    int feast_token=120;

public:
    int getRegularToken() {
        return regular_token;
    }

    int getFeastToken() {
        return feast_token;
    }
    void buyRegularToken();
    void buyFeastToken(); 
    virtual void buy() = 0; 
};

void Hall::buyRegularToken() {
     cout << "Buy a regular token for " << getRegularToken() << " tk" << endl; 
        cout << "Number of Token you want to  buy for Lunch-  " << endl;
        int n1;
        cin >> n1;
        cout << "Number of Token you want to  buy for Dinner-  " << endl;
        int n2;
        cin >> n2;
        int n = n1 + n2;
         cout << "Total number of token you want to buy: " << n << endl;
        cout << "Total cost: " << getRegularToken() * n << " tk" << endl;
         try{
    if (n * getRegularToken() > balance) {
        cout << "Insufficient balance!" << endl;
        return;
    }

    else{
        balance -= getRegularToken() * n;
        cout << "Remaining balance: " << balance << " tk" << endl;
    }
}
    catch(...) {
        cout << "You don't have enough money. Please recharge to you profile !" << endl;
        return;
    }
    
}

void Hall::buyFeastToken() {
    cout << "Buy a feast token for " << getFeastToken() << " tk" << endl; 
    cout << "How many token you want to buy? ";
    int n;
    cin >> n;
    cout << "Total cost: " << getFeastToken() * n << " tk" << endl;
    
    
    try{                                            //exception handling achieved here
    if (n * getFeastToken() > balance) {
        cout << "Insufficient balance!" << endl;
        return;
    }

    else{
        balance -= getFeastToken() * n;
        cout << "Remaining balance: " << balance << " tk" << endl;
    }
}
    catch(...) {
        cout << "You don't have enough money. Please recharge to you profile !" << endl;
        return;
    }
    
}

//ENCAPSULATION AND ABSTRUCT CLASS ACHIEVED

class Zia:public Hall{
public:
    void buy()  {


        cout << "Press 1 to buy a regular token" << endl;
        cout << "Press 2 to buy a feast token" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            buyRegularToken();
        }
        else if (choice == 2) {
            buyFeastToken();
        }
       
    }

};

//single operation for every hall to achieve run time polymorphism through virtual function and respective hall unique features

class Hamid:public Hall{
public:
    void buy()  {
        cout << "Press 1 to buy a regular token" << endl;
        cout << "Press 2 to buy a feast token" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            buyRegularToken();
        }
        else if (choice == 2) {
            buyFeastToken();
        }
       
    }

};

class Selim:public Hall{
public:
    void buy()  {
        cout << "Press 1 to buy a regular token" << endl;
        cout << "Press 2 to buy a feast token" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            buyRegularToken();
        }
        else if (choice == 2) {
            buyFeastToken();
        }
       
    }

};

class Shohidul:public Hall{
public:
    void buy()  {
        cout << "Press 1 to buy a regular token" << endl;
        cout << "Press 2 to buy a feast token" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            buyRegularToken();
        }
        else if (choice == 2) {
            buyFeastToken();
        }
       
    }

};

class Bongobondhu:public Hall{
public:
    void buy()  {
        cout << "Press 1 to buy a regular token" << endl;
        cout << "Press 2 to buy a feast token" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            buyRegularToken();
        }
        else if (choice == 2) {
            buyFeastToken();
        }
       
    }

};

class Tinshed:public Hall{
public:
    void buy()  {
        cout << "Press 1 to buy a regular token" << endl;
        cout << "Press 2 to buy a feast token" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            buyRegularToken();
        }
        else if (choice == 2) {
            buyFeastToken();
        }
       
    }

};

int main() {
    
}
