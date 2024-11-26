#include <iostream>
#include "data_parser.h"

int main() {
    std::string filePath = "src/lsapp.tsv";
    std::vector<UserSession> sessions = parseTSV(filePath);

    if (sessions.empty()) {
        std::cerr << "No data loaded from the file." << std::endl;
        return 1;
    }

    std::cout << "Data loaded successfully! Number of sessions: " << sessions.size() << std::endl;

    // Print the first few sessions for verification
    for (size_t i = 0; i < std::min<size_t>(sessions.size(), 5); i++) {
        const auto& session = sessions[i];
        std::cout << "UserID: " << session.userID
                  << ", SessionID: " << session.sessionID
                  << ", Timestamp: " << session.timestamp
                  << ", AppName: " << session.appName
                  << ", EventType: " << session.eventType
                  << std::endl;
    }

    return 0;
}
