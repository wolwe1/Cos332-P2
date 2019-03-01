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
    User(string,string,int);
    void write(string );
    string print();
    int getId();
    string getName();
    string getNumber();
    string getAllDetails();
    bool changeDetails(string,string);
    ~User();

};

#endif
