#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>



// Edge in the adjacency list graph
struct GraphEdge {
    int to;      // neighboring location ID
    int time;    // travel time
    bool open;   // true = open, false = closed
};

// student info
struct Student {
    std::string name;
    int residenceID;
    std::vector<std::string> classCodes; // enrolled class codes
};

// classes info
struct Classes {
    int locationID;
    int startMinutes;
    int endMinutes;
};

// represents edges in subgraph
struct ZoneEdge {
    int u; // location ID // one will be the residence ID
    int v; // location ID
    int w; // time
};

class CampusCompass {
private:

    // Adjacency List Graph
    // location ID -> graph edges
    std::unordered_map<int, std::vector<GraphEdge>> Graph;

    // student ID -> student info
    std::unordered_map<int, Student> students;

    // class Code -> class Info
    std::unordered_map<std::string, Classes> classes;

    // Not really needed for the assignment?
    // location ID -> location name
    std::unordered_map<int, std::string> locationNames;



    // HELPERS

    // csv reader
    std::vector<std::vector<std::string>> readCSV(const std::string &filename);
    // Add undirected edge to graph
    void addEdge(int u, int v, int time);
    // get specific edge
    GraphEdge* getEdge(int u, int v);
    // closes/opens edge. returns false if edge doesn't exist
    bool toggleEdge(int u, int v);

    // helper for printShortestEdges functions -> Dijkstra
    // also traces all parents for printStudentZone function
    void shortestPaths(int sourceID, std::unordered_map<int, int> &dist, std::unordered_map<int, int> &parent);

    // Build the subgraph for MST
    // takes a set of all vertices that appear in the shortest path (used to check if vertex is in zone)
    // outputs a list of zone edges (no duplicates -> only insert edge where u < v)
    std::vector<ZoneEdge> buildZoneSubgraph(const std::unordered_set<int> &zoneVertices);
    // Compute MST cost using Kruskal's algorithm and DSU.
    // takes the list of zoneEdges (which will be sort by weight and merged)
    // and vector version of zoneVertices (for DSU constructor)
    int computeMSTCost(const std::vector<ZoneEdge> &edges, const std::vector<int> &vertices);

    // translate HH:WW to minutes (need for verifySchedule function EC)
    int timeToMinutes(const std::string &hhmm);

public:
    CampusCompass() = default;
    CampusCompass(const std::string &edges_filename, const std::string &classes_filename);

    // populates graph and classes Table
    bool ParseCSV(const std::string &edges_filepath, const std::string &classes_filepath);

    // Project functions
    void insert(std::string name, int UFID, int residenceID,std:: vector<std::string> classCodes);
    void remove(int UFID);
    void dropClass(int UFID, std::string classCode);
    void replaceClass(int UFID, std::string classCode1, std::string classCode2);
    void removeClass(std::string classCode);
    void toggleEdgesClosure(int N, std::vector<int> &locationIDs);
    void checkEdgeStatus(int locationIDx, int locationIDy);
    void isConnected(int u, int v);
    void printShortestEdges(int UFID);
    void printStudentZone(int UFID);
};
