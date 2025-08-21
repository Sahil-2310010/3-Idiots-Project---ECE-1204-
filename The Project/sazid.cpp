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
    virtual void buy(const char* s) = 0;
};

void Hall::buyRegularToken() {
     cout << "Buy a regular token for " << getRegularToken() << " tk" << endl;
        cout << "Do you want to buy a token for lunch?- \n 1.Yes \n 2.No " << endl;
        int c1,n=0;
        cin >> c1;
        if (c1 == 1)
            n++;
        cout << "Do you want to buy a token for dinner?- \n 1.Yes \n 2.No " << endl;
        int c2;
        cin >> c2;
        if (c2 == 1)
            n++;
         cout << "Total number of token you are buying-: " << n << endl;
        cout << "Total cost: " << getRegularToken() * n << " tk" << endl;
        try{                                            //exception handling achieved here
    if (n * getRegularToken() > balance) {
        throw "Insufficient balance!";
    }
        balance -= getRegularToken() * n;
        cout << "Remaining balance: " << balance << " tk" << endl;

}
    catch(char *s) {
        cout << s << endl;
    }

}

void Hall::buyFeastToken() {
    cout << "Buy a feast token for " << getFeastToken() << " tk" << endl;
    cout << "Press 1 to buy a feast token" << endl;
    int c;
    cin >> c;
    if (c != 1) {
        cout << "No feast token bought." << endl;
        return;
    }
    else {

    cout << "Total cost: " << getFeastToken()<< " tk" << endl;


    try{                                            //exception handling achieved here
    if (getFeastToken() > balance) {
        throw "Insufficient balance!";
    }
        balance -= getFeastToken();
        cout << "Remaining balance: " << balance << " tk" << endl;

}
    catch(char *s) {
        cout << s << endl;
    }

}
}

class SpecificHall: public Hall {
public:
    void buy(const char* s) override {
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

int main(){

    cout << "Welcome to the Hall Token System!" << endl;
    Hall *h;
    SpecificHall spec;
    h = &spec;

    cout << "Choose a hall:" << endl;
    cout << "1.Zia Hall" << endl;
    cout << "2.Bongobondhu Hall" << endl;
    cout << "3.Tinshed Hall" << endl;
    cout << "4.Hamid Hall" << endl;
    cout << "5.Selim Hall" << endl;
    cout << "6.Shohidul Hall" << endl;

    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "You have chosen Zia Hall." << endl;
            h->buy("Zia Hall");
            break;
        case 2:
            cout << "You have chosen Bongobondhu Hall." << endl;
            h->buy("Bongobondhu Hall");
            break;
        case 3:
            cout << "You have chosen Tinshed Hall." << endl;
            h->buy("Tinshed Hall");
            break;
        case 4:
            cout << "You have chosen Hamid Hall." << endl;
            h->buy("Hamid Hall");
            break;
        case 5:
            cout << "You have chosen Selim Hall." << endl;
            h->buy("Selim Hall");
            break;
        case 6:
            cout << "You have chosen Shohidul Hall." << endl;
            h->buy("Shohidul Hall");
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }

    return 0;


}
