#ifndef USER_SESSION_H
#define USER_SESSION_H

#include <string>

struct UserSession {
    std::string userID;     
    std::string sessionID;   
    std::string timestamp;    
    std::string appName;    
    std::string eventType; 
};

#endif
