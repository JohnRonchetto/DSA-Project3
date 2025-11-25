#include <iostream>

#include "CampusCompass.h"
#include "parseCommand.h"

using namespace std;

int main() {
    // initializing main project object
    CampusCompass CC;

    // ingest CSV data
    CC.ParseCSV("data/edges.csv", "data/classes.csv");

    int no_of_lines;
    string command;
    cin >> no_of_lines;
    cin.ignore(); // ignore newline that first cin left over
    for (int i = 0; i < no_of_lines; i++) {
        if (!std::getline(std::cin, command)) {
            break;
        }

        if (!verifyCommand(command, CC)) {
            std::cout << "unsuccessful" << std::endl;
        }
    }

    return 0;
}
