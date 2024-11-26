#include <iostream>
#include <string>
#include "UserSession.h"


class algorithms {
public:
    void printUserDuration(User &user); // prints the duration of the user
    void addDuration(User &user,double Duration); // adds the duration to the User struct
    double durationCalc(int opened, int closed); // calculates the duration, using opened closed sessions
    void mergeSort(); // figure out parameters needed
    void quickSort(); // figure out parameters needed
    void Timer(); // determine how long each algorithm takes to run
};