#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Edge in the adjacency list
struct GraphEdge {
    int to;      // neighboring location ID
    int time;    // travel time / weight
    bool open;   // true = open, false = closed
};

struct Classes {
    string classCode;
    int locationID;
    int startMinutes;
    int endMinutes;
};

struct Students {
    string name;
    int residenceID;
    vector<string> classCodes; // list of enrolled class codes
};

class CampusCompass {
private:
    // Adjacency List: location ID -> outgoing graph edges
    unordered_map<int, vector<GraphEdge>> Graph;

    // classCode -> class Info
    unordered_map<string, Classes> classes;

    // student ID -> student info // for command line operation
    unordered_map<int, Students> students;


    void addEdge(int u, int v, int time);


    // helpers

    // csv reader
    vector<vector<string>> readCSV(const string &filename);
    //translate HH:WW to minutes
    int timeToMinutes(const string &hhmm);

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    // populates graph and classes Table
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);
};
