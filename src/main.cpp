#include <iostream>

#include "CampusCompass.h"
#include "parseCommand.h"

using namespace std;

int main() {
    // initializing main project object
    CampusCompass CC;

    // ingest CSV data
    CC.ParseCSV("data/edges.csv", "data/classes.csv");

    int num_of_lines;
    string command;
    getline(cin, command);
    num_of_lines = stoi(command);
    for (int i = 0; i < num_of_lines; i++) {
        if (!std::getline(std::cin, command)) {
            break;
        }

        if (!verifyCommand(command, CC)) {
            std::cout << "unsuccessful" << std::endl;
        }
    }

    return 0;
}
