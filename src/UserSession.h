#ifndef USER_SESSION_H
#define USER_SESSION_H

#include <string>
#include <unordered_map>

struct User {
    int userID;
    double Duration;
    std::string timestamp;
    std::string eventType;
    //Zane - Added category durations 
    std::unordered_map<std::string, double> categoryDurations;
    std::string appName;
};
//Zane- Global declaration of hashmap for app categories
extern std::unordered_map<std::string, std::string> appCategories;

#endif


