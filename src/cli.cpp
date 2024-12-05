#include "cli.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include "algorithms.h"
#include "UserSession.h"

//CLI::CLI(const std::vector<User>& users) : users(users) {
//    std::cout << "CLI initialized with " << users.size() << " users." << std::endl;
//}


void CLI::displayMenu() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "\n===== Screen Time Squad CLI =====\n";
        std::cout << "1. Compare Merge Sort and Quick Sort Speeds\n";
        std::cout << "2. Display Leaderboard\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                compareSortingAlgorithms();
                break;
            case 2:
                displayLeaderboard();
                break;
//            case 3:
//                displayCategoryBreakdown();
//                break;
            case 3:
                std::cout << "Exiting... Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void CLI::compareSortingAlgorithms() {

//        std::cout << "Debug: Number of users in compareSortingAlgorithms: " << users.size() << std::endl;

    if (users.empty()) {
        std::cerr << "No data available. Please load or process data first.\n";
        return;
    }

    // Shuffle users for unbiased comparison
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(users.begin(), users.end(), rng);

    // Measure Merge Sort speed
    auto mergeStart = std::chrono::high_resolution_clock::now();
    algorithms::mergeSort(users, 0, users.size() - 1);
    auto mergeEnd = std::chrono::high_resolution_clock::now();
    double mergeDuration = std::chrono::duration<double>(mergeEnd - mergeStart).count();

    // Shuffle again to ensure unbiased Quick Sort timing
    std::shuffle(users.begin(), users.end(), rng);

    // Measure Quick Sort speed
    auto quickStart = std::chrono::high_resolution_clock::now();
    algorithms::quickSort(users, 0, users.size() - 1);
    auto quickEnd = std::chrono::high_resolution_clock::now();
    double quickDuration = std::chrono::duration<double>(quickEnd - quickStart).count();

    // Display results
    std::cout << "\n===== Sorting Algorithm Speed Comparison =====\n";
    std::cout << "Merge Sort Time: " << std::fixed << std::setprecision(6) << mergeDuration << " seconds\n";
    std::cout << "Quick Sort Time: " << std::fixed << std::setprecision(6) << quickDuration << " seconds\n";

    // Restore the sorted state of users for later operations
    algorithms::mergeSort(users, 0, users.size() - 1);
}

void CLI::displayLeaderboard() {
    if (users.empty()) {
        std::cerr << "No data available. Please process data first.\n";
        return;
    }

    // Sort users by total screen time
    algorithms::mergeSort(users, 0, users.size() - 1);

    std::cout << "\n===== Leaderboard =====\n";
    for (size_t i = 0; i < std::min<size_t>(users.size(), 5); ++i) {
        algorithms::printUserDuration(users[i]);
    }
}

//void CLI::displayCategoryBreakdown() {
//    if (users.empty()) {
//        std::cerr << "No data available. Please process data first.\n";
//        return;
//    }
//
//    std::cout << "\n===== Category Breakdown for All Users =====\n";
//    for (const auto& user : users) {
//        std::cout << "User ID: " << user.userID << "\n";
//
//
//        // Check if categoryDurations is empty
//        if (user.categoryDurations.empty()) {
//            std::cout << "  No category data available for this user.\n";
//            continue;
//        }
//
//        // Iterate and print category breakdown
//        for (const auto& [category, time] : user.categoryDurations) {
//            std::cout << "  " << category << ": " << std::fixed << std::setprecision(2)
//            << "Category: " << category << ", Time: " << time << " seconds\n";
//
//
//        }
//    }
//}
