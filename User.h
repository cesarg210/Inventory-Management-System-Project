#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User {
    
protected:
    string username;
    string password;
    string role;

public:
    // Constructor
    User(string username, string password, string role);

    // User authentication
    bool authenticate(string inputPassword) const;

    // Get role / username
    string getRole() const;
    string getUsername() const;
};
#endif