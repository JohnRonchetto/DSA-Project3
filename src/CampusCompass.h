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

struct Student {
    string name;
    int residenceID;
    vector<string> classCodes; // list of enrolled class codes
};

struct Classes {
    int locationID;
    int startMinutes;
    int endMinutes;
};

class CampusCompass {
private:
    // Adjacency List: location ID -> outgoing graph edges
    unordered_map<int, vector<GraphEdge>> Graph;

    // student ID -> student info
    unordered_map<int, Student> students;

    // Not really needed for the assignment?
    // location ID -> location name
    unordered_map<int, string> locationNames;

    // Only needed for the extra credit
    // classCode -> class Info
    unordered_map<string, Classes> classes;
    //translate HH:WW to minutes
    int timeToMinutes(const string &hhmm);




    // HELPERS

    // csv reader
    vector<vector<string>> readCSV(const string &filename);
    // Add edge to graph
    void addEdge(int u, int v, int time);

    bool studentExists(int id) const;
    GraphEdge* getEdge(int u, int v);
    const GraphEdge* getEdge(int u, int v) const;
    bool toggleEdge(int u, int v);

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    // populates graph and classes Table
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);



};
