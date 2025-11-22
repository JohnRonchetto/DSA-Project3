#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Edge in the adjacency list graph
struct GraphEdge {
    int to;      // neighboring location ID
    int time;    // travel time / weight
    bool open;   // true = open, false = closed
};

// student info
struct Student {
    string name;
    int residenceID;
    vector<string> classCodes; // list of enrolled class codes
};

// classes info
struct Classes {
    int locationID;
    int startMinutes;
    int endMinutes;
};

class CampusCompass {
private:
    // Adjacency List
    // location ID -> graph edges
    unordered_map<int, vector<GraphEdge>> Graph;

    // student ID -> student info
    unordered_map<int, Student> students;

    // class Code -> class Info
    unordered_map<string, Classes> classes;

    // Not really needed for the assignment?
    // location ID -> location name
    unordered_map<int, string> locationNames;



    // HELPERS

    // csv reader
    vector<vector<string>> readCSV(const string &filename);
    // Add undirected edge to graph
    void addEdge(int u, int v, int time);
    // get specific edge
    GraphEdge* getEdge(int u, int v);
    // closes/opens edge. returns false if edge doesn't exist
    bool toggleEdge(int u, int v);

    //translate HH:WW to minutes (need for verifySchedule function EC)
    int timeToMinutes(const string &hhmm);

public:
    CampusCompass();
    CampusCompass(const string &edges_filename, const string &classes_filename);

    // populates graph and classes Table
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);

    // Project functions
    void insert(string name, int UFID, int residenceID, vector<string> classCodes);
    void remove(int UFID);
    void dropClass(int UFID, string classCode);
    void replaceClass(int UFID, string classCode1, string classCode2);
    void removeClass(string classCode);
    void toggleEdgesClosure(int N, vector<int> &locationIDs);

};
