#include "User.h"
using namespace std;

// Constructor
User::User(string username, string password, string role)
{
    this->username = username;
    this->password = password;
    this->role = role;
}

// User authentication
bool User::authenticate(string inputPassword) const
{
    return password == inputPassword;
}

// Returns role of user
string User::getRole() const
{
    return role;
}

// Returns username
string User::getUsername() const
{
    return username;
}