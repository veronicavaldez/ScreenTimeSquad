#include "data_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<UserSession> parseTSV(const std::string& filePath) {
    std::vector<UserSession> data;
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
        std::string userID, sessionID, timestamp, appName, eventType;

        if (std::getline(ss, userID, '\t') &&
            std::getline(ss, sessionID, '\t') &&
            std::getline(ss, timestamp, '\t') &&
            std::getline(ss, appName, '\t') &&
            std::getline(ss, eventType, '\t')) {
            
            // add the parsed session data to the vector
            data.push_back({userID, sessionID, timestamp, appName, eventType});
        } else {
            std::cerr << "Error: Malformed line: " << line << std::endl;
        }
    }

    file.close();
    return data;
}
