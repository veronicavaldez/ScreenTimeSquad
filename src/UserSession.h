#ifndef USER_SESSION_H
#define USER_SESSION_H

#include <string>

struct User {
    int userID;
    double Duration;
    std::string timestamp;
    std::string eventType;
};

#endif
