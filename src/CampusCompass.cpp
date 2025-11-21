#include "CampusCompass.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void CampusCompass::addEdge(int u, int v, int time) {
    // unidirected. open by default
    Graph[u].push_back({v, time, true});
    Graph[v].push_back({u, time, true});

}

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
    auto edges = readCSV(edges_filepath);
    if (edges.empty()) {
        return false;
    }

    for (size_t i = 1; i < edges.size(); i++) {
        auto &row = edges[i];

        int u = stoi(row[0]); // LocationID_1
        int v = stoi(row[1]); // LocationID_2
        int t = stoi(row[4]); // Time

        addEdge(u, v, t);
    }

    // Load classes.csv
    auto classInfo = readCSV(classes_filepath);
    if (classes.empty()) return false;

    for (size_t i = 1; i < classInfo.size(); i++) {
        auto &row = classInfo[i];
        if (row.size() < 4) continue;

        string code = row[0];
        int locationID = stoi(row[1]);
        int start = timeToMinutes(row[2]);
        int end = timeToMinutes(row[3]);

        classes[code] = {code, locationID, start, end};
    }

    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    return is_valid;
}
