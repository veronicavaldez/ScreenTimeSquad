#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <map>
#include "UserSession.h"


class algorithms {
public:
    static void printUserDuration(User &user); // prints the duration of the user
    static void addDuration(User &user,double duration); // adds the duration to the User struct
    static double durationCalc(const std::string& opened, const std::string& closed); // calculates the duration, using opened closed sessions
    static std::vector<User> calculateTotalScreenTime(const std::vector<User>& sessions); // calculates user's total screen time
    static void merge(std::vector<User> &users, int left, int mid, int right); // recursive function for merge sort
    static void mergeSort(std::vector<User> &users, int left, int right); // sorts container of users in ascending order
    static int partition(std::vector<User> &users, int low, int high); // recursive function for quick sort
    static void quickSort(std::vector<User> &users, int low, int high); // 2nd sorting method
    static void Timer(std::vector<User> users); // determine how long each algorithm takes to run
};