#include "CampusCompass.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<vector<string>> CampusCompass::readCSV(const string &filename) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: could not open: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    return data;
}

int CampusCompass::timeToMinutes(const string &hhmm) {
    // size_t -> unsigned int
    size_t pos = hhmm.find(':');

    // string::npos -> size_t(-1)
    if (pos == string::npos) {
        return 0;
    }

    int hour = stoi(hhmm.substr(0, pos));
    int minute = stoi(hhmm.substr(pos + 1));
    return hour * 60 + minute;
}

CampusCompass::CampusCompass() {
    // initialize your object
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // load edges.csv
    auto edgesTable = readCSV(edges_filepath);
    if (edgesTable.empty()) {
        return false;
    }

    edges_.clear();
    // skip header row at index 0
    for (size_t i = 1; i < edgesTable.size(); ++i) {
        const auto &row = edgesTable[i];

        Edge e;
        e.fromID = stoi(row[0]);
        e.toID   = stoi(row[1]);
        e.name1  = row[2];
        e.name2  = row[3];
        e.time   = stoi(row[4]);

        edges_.push_back(e);
    }

    // load classes.csv
    auto classesTable = readCSV(classes_filepath);
    if (classesTable.empty()) return false;

    classes_.clear();
    // skip first row
    for (size_t i = 1; i < classesTable.size(); ++i) {
        const auto &row = classesTable[i];

        ClassMeeting c;
        c.classCode    = row[0];
        c.locationID   = stoi(row[1]);
        c.startMinutes = timeToMinutes(row[2]);
        c.endMinutes   = timeToMinutes(row[3]);

        classes_.push_back(c);
    }

    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}
