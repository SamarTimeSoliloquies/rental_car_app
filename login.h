#ifndef login_h
#define login_h
#include <string>
using namespace std;

class LoginSystem {
private:
    int loggedInAdminId = -1;

public:
    int validateCredentials(const string& username, const string& password);
    int getLoggedInAdminId() const;
};
#endif