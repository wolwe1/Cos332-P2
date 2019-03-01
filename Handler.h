#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <iostream>
#include "User.h"  
#include <cstdio>
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

class Handler{

    private:
        int userCount;
        string filename;
        ifstream file;

        // struct tempUser
        // {
        //     int id;
        //     string name;
        //     string number;
        //     string user;
        // };

        vector<User*> users;
        // tempUser temp;
        
    
    public:
        Handler();
        ~Handler();

        bool addUser(string,string);
        bool deleteUser(int,int);
        User* getUser(string,int);
        User* getUser(int);
        User* getAllUsers(int sd);
        bool rewriteFile();
        bool updateUser(int,string,string,int);
        vector<User*> loadUsers();
        //string* getAllUsers();
};


#endif