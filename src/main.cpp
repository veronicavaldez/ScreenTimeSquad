#include <iostream>
#include "data_parser.h"
#include "algorithms.h"
#include "cli.h"
#include "UserSession.h"

  

 int main() {
    std::string filePath = "src/lsapp.tsv";
    std::vector<User> sessions = parseTSV(filePath);

    if (sessions.empty()) {
        std::cerr << "No data loaded from the file." << std::endl;
        return 1;
    }

    std::cout << "Data loaded successfully! Number of sessions: " << sessions.size() << std::endl;

    std::vector<User> users = algorithms::calculateTotalScreenTime(sessions);

    if (users.empty()) {
        std::cerr << "No valid user data." << std::endl;
        return 1;
    }

   //  Debug: Print the first few users
    std::cout << "Number of users after processing: " << users.size() << std::endl;
    for (size_t i = 0; i < std::min<size_t>(users.size(), 5); ++i) {
        std::cout << "User ID: " << users[i].userID << ", Total Duration: " << users[i].Duration << std::endl;
    }

    // Pass users to CLI
    CLI cli(users);


    cli.displayMenu();

    return 0;
}


