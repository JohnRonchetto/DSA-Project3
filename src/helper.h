#ifndef PROJECT3_HELPER_H
#define PROJECT3_HELPER_H

#include <string>
#include <vector>
#include "CampusCompass.h"

// Takes in command along with dummy name, ufid, residenceID, N, and classCodes (for removeIorder(N))
// Verifies that input is correct and assigns name, ufid, residenceID nth, N, and classCodes, which are then used in main/test.cpp
// Returns command type
std::string parseCommand(const std::string &command,
    std::string &name,
    int &studentID,
    int &residenceID,
    int &N,
    std::vector<std::string> &classCodes);

// actually executes command
bool verifyCommand(const std::string &command, CampusCompass &CC);


#endif //PROJECT3_HELPER_H