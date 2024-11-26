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

    // view first few sessions for verification
    for (size_t i = 0; i < std::min<size_t>(sessions.size(), 5); i++) {
        const auto& session = sessions[i];
        std::cout << "UserID: " << session.userID
                  << ", SessionID: " << session.sessionID
                  << ", Timestamp: " << session.timestamp
                  << ", AppName: " << session.appName
                  << ", EventType: " << session.eventType
                  << std::endl;
    }
/*
    auto users = aggregateScreenTime(sessions);

    // merge sort
    mergeSort(users, 0, users.size() - 1);
    std::cout << "Top users sorted by screen time (Merge Sort):" << std::endl;
    for (size_t i = 0; i < std::min<size_t>(users.size(), 5); ++i) {
        std::cout << "UserID: " << users[i].first
                  << ", Total Screen Time: " << users[i].second << " hours" << std::endl;
    }

    // quick sort
    quickSort(users, 0, users.size() - 1);
    std::cout << "Top users sorted by screen time (Quick Sort):" << std::endl;
    for (size_t i = 0; i < std::min<size_t>(users.size(), 5); ++i) {
        std::cout << "UserID: " << users[i].first
                  << ", Total Screen Time: " << users[i].second << " hours" << std::endl;
    }

    return 0; 
}
*/
