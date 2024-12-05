#include "data_parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "UserSession.h"


//Zane- adding hashmap to store app-to-app categories
#include <unordered_map>
#include <string>

//Zane- Hashmap creation
std::unordered_map<std::string, std::string> appCategories = {
        {
                {"Minesweeper Classic (Mines)", "Games"},
                {"Gmail", "Productivity"},
                {"Google", "Information & Reading"},
                {"Instagram", "Social"},
                {"Google Chrome", "Utilities"},
                {"Clock", "Utilities"},
                {"Maps", "Travel"},
                {"YouTube", "Entertainment"},
                {"Facebook", "Social"},
                {"Messages", "Utilities"},
                {"Phone", "Utilities"},
                {"Snapchat", "Social"},
                {"Settings", "Utilities"},
                {"Google Photos", "Creativity"},
                {"Hangouts", "Social"},
                {"Amazon Shopping", "Shopping"},
                {"Facebook Messenger", "Social"},
                {"Google Play Store", "Utilities"},
                {"Calendar", "Productivity"},
                {"Discord", "Social"},
                {"Google Drive", "Productivity"},
                {"Twitter", "Social"},
                {"Spotify Music", "Music"},
                {"Reddit", "Information & Reading"},
                {"Android In Call UI", "Utilities"},
                {"Receipt Hog", "Finance"},
                {"Ibotta", "Finance"},
                {"PayPal Mobile Cash", "Finance"},
                {"Contacts", "Utilities"},
                {"Samsung Notes", "Productivity"},
                {"Messaging", "Utilities"},
                {"Samsung Gallery", "Creativity"},
                {"eBay", "Shopping"},
                {"Flipboard Briefing", "Information & Reading"},
                {"Camera", "Creativity"},
                {"Yahoo Mail", "Productivity"},
                {"S’more", "Entertainment"},
                {"Lucktastic", "Games"},
                {"Pinterest", "Creativity"},
                {"Words With Friends 2", "Games"},
                {"Google Play Music", "Music"},
                {"Calculator", "Utilities"},
                {"Samsung Internet Browser", "Utilities"},
                {"Hulu", "Entertainment"},
                {"Walmart", "Shopping"},
                {"MUIQ Survey App", "Other"},
                {"WhatsApp Messenger", "Social"},
                {"Robinhood", "Finance"},
                {"Calorie Counter", "Health & Fitness"},
                {"Pandora Music", "Music"},
                {"Microsoft Outlook", "Productivity"},
                {"Samsung Email", "Productivity"},
                {"Netflix", "Entertainment"},
                {"Messenger Lite", "Social"},
                {"Reward Stash", "Other"},
                {"OfferUp", "Shopping"},
                {"Brave Browser", "Utilities"},
                {"Slidejoy", "Other"},
                {"Verizon Messages", "Utilities"},
                {"Samsung Pay", "Finance"},
                {"TextNow", "Utilities"},
                {"imo", "Social"},
                {"Swagbucks", "Finance"},
                {"Telegram", "Social"},
                {"Clean Master", "Utilities"},
                {"Podcast Addict", "Entertainment"},
                {"The PCH App", "Games"},
                {"Quora", "Information & Reading"},
                {"Movie Play Box", "Entertainment"},
                {"Microsoft Bing Search", "Information & Reading"},
                {"SurveyCow", "Other"},
                {"Baseball Boy!", "Games"},
                {"Swagbucks Watch (TV)", "Entertainment"},
                {"MAX Cleaner", "Utilities"},
                {"Kik", "Social"},
                {"Army Men Strike", "Games"},
                {"MetroZone", "Utilities"},
                {"AOL", "Information & Reading"},
                {"Badoo", "Social"},
                {"Text One", "Utilities"},
                {"Telegram X", "Social"},
                {"WeChat", "Social"},
                {"Pixlr", "Creativity"},
                {"Faceu", "Creativity"},
                {"Flickr", "Creativity"},
                {"EntertaiNow", "Entertainment"},
                {"DigiHUD Pro Speedometer", "Utilities"}
        }

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


                // add the parsed data to the vector
                data.push_back(user);


            } else {
                std::cerr << "Error: Malformed line: " << line << std::endl;
            }
        }


    }
    file.close();
    return data;
}