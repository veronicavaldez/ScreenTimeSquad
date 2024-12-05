#ifndef CLI_H
#define CLI_H

#include "UserSession.h"
#include "data_parser.h"
// #include "algorithms.h"
#include <string>
#include <vector>

class CLI {
public:
    CLI(const std::vector<User>& users) : users(users) {}  // Constructor to initialize users

    void displayMenu();  // Displays the main menu.
    void loadFile(const std::string& filePath);  // Loads data from a file.
    void displayLeaderboard();  // Displays the leaderboard.
    void displayCategoryBreakdown();  // Displays screen time by category.
    void compareSortingAlgorithms();
private:
    std::vector<User> users;  // Stores the processed user data.
};

#endif