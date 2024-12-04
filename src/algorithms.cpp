#include "algorithms.h"

void algorithms::printUserDuration(User &user) {
    std::cout << "User ID: " << user.userID << " Screen Time: " << user.Duration << " seconds" << std::endl;
}

// add the duration to the User struct
void algorithms::addDuration(User &user, double duration) {
    user.Duration += duration;
}

// calculate the duration between open/close events
double algorithms::durationCalc(const std::string& opened, const std::string& closed) {
    // std::tm represents calendar date/time, from https://en.cppreference.com/w/cpp/chrono/c/tm
    std::tm tmOpened = {};
    std::tm tmClosed = {};
    std::istringstream ssOpened(opened);
    std::istringstream ssClosed(closed);
      if (!(ssOpened >> std::get_time(&tmOpened, "%Y-%m-%d %H:%M:%S"))) {
        std::cerr << "Error parsing opened timestamp: " << opened << std::endl;
        return 0;
    }
    if (!(ssClosed >> std::get_time(&tmClosed, "%Y-%m-%d %H:%M:%S"))) {
        std::cerr << "Error parsing closed timestamp: " << closed << std::endl;
        return 0;
    }

    // mktime converts the tm struct into time in seconds, from https://en.cppreference.com/w/cpp/chrono/c/mktime
    std::time_t timeOpened = std::mktime(&tmOpened);
    std::time_t timeClosed = std::mktime(&tmClosed);

    return std::difftime(timeClosed, timeOpened); // returns duration in seconds
}

// add up time in between open/close sessions to get user's total screen time
    std::vector<User> algorithms::calculateTotalScreenTime(const std::vector<User>& sessions) {
    std::map<int, double> userDurations;  // map to store total screen time by userID
    std::map<int, std::string> lastOpened; // map to track the time of last opened event for each user
    std::map<int, User> users;
    for (const auto& session : sessions) {
        if (session.eventType == "Opened") {
            // record opened timestamp for the user
            lastOpened[session.userID] = session.timestamp;
        } else if (session.eventType == "Closed" && lastOpened.find(session.userID) != lastOpened.end()) {
            // pair closed event with the last opened event to calculate the duration
            double duration = algorithms::durationCalc(lastOpened[session.userID], session.timestamp);

            //Zane- Updates user's total duration
             if (users.find(session.userID) == users.end()) {
                // Create a new User entry if it doesn't exist
                users[session.userID] = {session.userID, 0, "", ""};
            }
            userDurations[session.userID] += duration; // add duration to total for user

             //Zane- Update category-specific duration if app has a category
            if (appCategories.find(session.appName) != appCategories.end()) {
                std::string category = appCategories[session.appName];
                users[session.userID].categoryDurations[category] += duration;
            }

            lastOpened.erase(session.userID);         // remove "opened" record

            
        }
    }

    // convert the map to a vector of Users
    std::vector<User> result;
    for (const auto& [userID, totalDuration] : userDurations) {
        result.push_back({userID, totalDuration, "", ""}); // only need user ID and duration
    }

    return result;
}


// function to be called recursively for merge sort
void algorithms::merge(std::vector<User> &users, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<User> L(users.begin() + left, users.begin() + mid + 1);
    std::vector<User> R(users.begin() + mid + 1, users.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].Duration <= R[j].Duration) { // ascending
            users[k++] = L[i++];
        } else {
            users[k++] = R[j++];
        }
    }
    while (i < n1) users[k++] = L[i++];
    while (j < n2) users[k++] = R[j++];
}

void algorithms::mergeSort(std::vector<User> &users, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(users, left, mid);
        mergeSort(users, mid + 1, right);
        merge(users, left, mid, right);
    }
}

// function to be called recursively for quick sort
int algorithms::partition(std::vector<User> &users, int low, int high) {
    double pivot = users[high].Duration;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (users[j].Duration <= pivot) { // Sort ascending
            std::swap(users[++i], users[j]);
        }
    }
    std::swap(users[i + 1], users[high]);
    return i + 1;
}

void algorithms::quickSort(std::vector<User> &users, int low, int high) {
    if (low < high) {
        int pi = partition(users, low, high);
        quickSort(users, low, pi - 1);
        quickSort(users, pi + 1, high);
    }
}

// determine how long each algorithm takes to run
void algorithms::Timer(std::vector<User> users) {
    // merge sort
    // using chrono for timing
    // Reference: https://en.cppreference.com/w/cpp/chrono
    auto mergeStart = std::chrono::high_resolution_clock::now();
    mergeSort(users, 0, users.size() - 1);
    auto mergeEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Merge Sort Speed: "
              << std::chrono::duration<double>(mergeEnd - mergeStart).count()
              << " seconds" << std::endl;

    // using std::shuffle to randomize the vector
    // Reference: https://en.cppreference.com/w/cpp/algorithm/shuffle
    std::random_device rd;  // Seed generator from https://en.cppreference.com/w/cpp/numeric/random/random_device
    std::mt19937 rng(rd()); // Mersenne Twister PRNG from https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine

    std::shuffle(users.begin(), users.end(), rng);

    // quick sort
    auto quickStart = std::chrono::high_resolution_clock::now();
    quickSort(users, 0, users.size() - 1);
    auto quickEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Quick Sort Speed: "
              << std::chrono::duration<double>(quickEnd - quickStart).count()
              << " seconds" << std::endl;
}



