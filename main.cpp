#include "Handler.h"
#include <iostream>

using namespace std;

void addUser(Handler* handler){

    string userName,number;

    cout << "Enter user name:";
    cin >> userName;

    cout << "Enter user number:";
    cin >> number;

    handler->addUser(userName,number);

}

void deleteUser(Handler* handler){
    
    int id;

    cout << "Enter user id:";
    cin >> id;

    handler->deleteUser(id);
}

void showUsers(Handler* handler){
    
    handler->getAllUsers();
}

int main(){

    Handler* handler = new Handler();
    int choice = 1;

    while(choice != 0){
        
        cout << "\n1: Add User"<<endl;
        cout << "2: Delete User"<<endl;
        cout << "3: Show Users"<<endl;

        cin >> choice;

        switch(choice){

            case 1 :
                addUser(handler);
                break;
            case 2 :
                deleteUser(handler);
                break;
            case 3 :
                showUsers(handler);
                break;
        }
    }
}