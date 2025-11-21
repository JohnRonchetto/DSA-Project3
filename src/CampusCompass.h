#pragma once
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int fromID;
    int toID;
    string name1;
    string name2;
    int time;
};

struct ClassMeeting {
    string classCode;
    int locationID;
    int startMinutes;
    int endMinutes;
};

class CampusCompass {
private:
    // Think about what member variables you need to initialize
    // perhaps some graph representation?

    vector<Edge> edges_;
    vector<ClassMeeting> classes_;

    // helper: csv reader
    vector<vector<string>> readCSV(const string &filename);

    // helper: translate HH:WW to minutes
    int timeToMinutes(const string &hhmm);

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);
};
