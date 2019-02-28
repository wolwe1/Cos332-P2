#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>

using namespace std;

class User{
private:

    int id;
    string name;
    string number;
    ofstream file;

public:
    User(string,string,int,string);
    ~User();

};

#endif
