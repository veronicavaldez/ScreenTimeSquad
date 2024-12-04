#include "data_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Zane- adding hashmap to store app-to-app categories
#include <unordered_map>
#include <string>

//Zane- Hashmap creation
std::unordered_map<std::string, std::string> appCategories = {
    {"Instagram", "Social"},
    {"Facebook", "Social"},
    {"Slack", "Productivity"},
    {"YouTube", "Entertainment"},
    //More mappings to add later
};

std::vector<User> parseTSV(const std::string& filePath) {
    std::vector<User> data;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return data;
    }

    std::string line;
    bool isHeader = true;

    while (std::getline(file, line)) {
        // skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        std::stringstream ss(line);
        std::string userIDStr, sessionID, timestamp, appName, eventType;

        if (std::getline(ss, userIDStr, '\t') &&
            std::getline(ss, sessionID, '\t') &&
            std::getline(ss, timestamp, '\t') &&
            std::getline(ss, appName, '\t') &&
            std::getline(ss, eventType, '\t')) {
        
            // add data to User struct
            User user;
            user.userID = std::stoi(userIDStr);
            user.timestamp = timestamp;
            user.eventType = eventType;
            user.appName = appName;
            user.Duration = 0;   // duration calculated later

            //Zane- Categorizing app usage
            if (appCategories.find(appName) != appCategories.end()) {
                // Assign category-specific duration (initially 0, calculated later)
                user.categoryDurations[appCategories[appName]] += 0;
            }

            // add the parsed data to the vector
            data.push_back(user);

        } else {
            std::cerr << "Error: Malformed line: " << line << std::endl;
        }
    }

    file.close();
    return data;
}
