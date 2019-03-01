#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <iostream>
#include "User.h"
#include <fstream>

using namespace std;

class Handler{

    private:
        int userCount;
        string filename;
        ifstream file;

        struct tempUser
        {
            int id;
            string name;
            string number;
            string user;
        };

        tempUser temp;
        
    
    public:
        Handler();
        ~Handler();

        bool addUser(string,string);
        bool deleteUser(int);
        User* getUser(int);
        //User** getAllUsers();
        string* getAllUsers();
};


#endif