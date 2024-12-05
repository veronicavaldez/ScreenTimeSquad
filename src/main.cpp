#include <iostream>
#include "data_parser.h"
#include "algorithms.h"

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

    std::cout << "\nComparing sorting execution times...\n";
    algorithms::Timer(users);

    // use merge sort for displaying ranked users
    algorithms::mergeSort(users, 0, users.size() - 1);

    // display ranking
    std::cout << "\nLeaderboard:" << std::endl;
    for (size_t i = 0; i < std::min<size_t>(users.size(), 5); ++i) {
        algorithms::printUserDuration(users[i]);
    }

    // Zane- Display category-specific breakdown for all users
    std::cout << "\nCategory Breakdown for All Users:\n";
    for (const auto& user : users) {
        std::cout << "User ID: " << user.userID << "\n";
        for (const auto &[category, time]: user.categoryDurations) {
            std::cout << "  " << category << ": " << time << " seconds\n";
        }
    }

    return 0;
}