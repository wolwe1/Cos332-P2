#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <iostream>
#include "User.h"
#include <fstream>
#include <vector>

using namespace std;

class Handler{

    private:
        int userCount;
        string filename;
        ifstream file;
        vector<User*> users;
    
    public:
        Handler();
        ~Handler();

        bool addUser(string,string);
        bool deleteUser(int);
        User* getUser(int);
        vector<User*> loadUsers();
        string* getAllUsers();
        bool rewriteFile();
        bool updateUser(int,string,string);
};


#endif