#ifndef PROJECT3_HELPER_H
#define PROJECT3_HELPER_H

#include "CampusCompass.h"

#include <string>
#include <vector>

// helper for verify command
// Takes in command along with dummy name, ufid, residenceID, N, classCodes, and locationIDs
// Verifies that input is correct and assigns name, ufid, residenceID, N, classCodes, and locationIDs
// which are then used in main/test.cpp
// Returns command type
std::string parseCommand(const std::string &command,
    std::string &name,
    int &studentID,
    int &residenceID,
    int &N,
    std::vector<std::string> &classCodes);

// actually cals function to executes command -> used in main/test
bool verifyCommand(const std::string &command, CampusCompass &CC);


#endif //PROJECT3_HELPER_H