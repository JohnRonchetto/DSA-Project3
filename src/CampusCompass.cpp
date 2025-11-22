#include "CampusCompass.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <limits>

using namespace std;

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

void CampusCompass::shortestPaths(int sourceID, std::unordered_map<int, int> &dist, std::unordered_map<int, int> &parent) {

    dist.clear();
    parent.clear();

    // location id -> shortest distance from source
    // std::unordered_map<int, int> &dist

    // child Node -> parent Node
    // std::unordered_map<int, int> &parent

    const int INF = numeric_limits<int>::max();

    // this declares the type for the pq
    // pair<dist, id>
    using node = pair<int, int>;
    // min heap
    // pq(dist, id)
    priority_queue<node, vector<node>, greater<node>> pq;

    dist[sourceID] = 0;
    parent[sourceID] = -1;
    pq.push({0, sourceID});


    while (!pq.empty()) {
        // node with smallest distance in pq
        auto curr = pq.top();
        int d = curr.first;
        int u = curr.second;
        pq.pop();

        // no decrease key function so
        // if duplicate with old state found -> skip
        if (d > dist[u]) {
            continue;
        }

        auto it = Graph.find(u);
        // should not happen, but just in case
        if (it == Graph.end()) {
            continue;
        }

        const vector<GraphEdge> &neighbors = it->second;

        // Relax all open outgoing edges
        for (const GraphEdge &edge : neighbors) {
            // check if edge is open
            if (!edge.open) {
                continue;
            }

            int v = edge.to;
            int w = edge.time;

            int oldDist;

            // checks if distance known first
            if (dist.count(v) != 0) {
                // already know a distance
                oldDist = dist[v];
            } else {
                // don't know a distance yet
                oldDist = INF;
            }

            int newDist = d + w;

            // relaxation step
            // if new distance (time) is less than the current
            if (newDist < oldDist) {
                dist[v] = newDist; // update distance
                parent[v] = u; // update parent
                pq.push({newDist, v});
            }
        }
    }
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

void CampusCompass::addEdge(int u, int v, int time) {
    // unidirected. open by default
    Graph[u].push_back({v, time, true});
    Graph[v].push_back({u, time, true});

}

GraphEdge * CampusCompass::getEdge(int u, int v) {
    auto it = Graph.find(u);

    // edge doesn't exist
    if (it == Graph.end()) {
        return nullptr;
    }

    for (auto &edge : it->second) {
        if (edge.to == v) {
            return &edge;
        }
    }

    // v not a neighbor of u;
    return nullptr;


}

bool CampusCompass::toggleEdge(int u, int v) {
    GraphEdge* e1 = getEdge(u, v);
    GraphEdge* e2 = getEdge(v, u);

    // edge does not exist
    if (e1 == nullptr || e2 == nullptr) {
        return false;
    }

    e1->open = !e1->open;
    e2->open = !e2->open;

    return true;
}


CampusCompass::CampusCompass() {
}

CampusCompass::CampusCompass(const string &edges_filename, const string &classes_filename) {
    if (!ParseCSV(edges_filename, classes_filename)) {
        cerr << "Error: could not parse CSV files" << endl;
    }
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // load edges.csv
    auto edges = readCSV(edges_filepath);

    if (edges.empty()) {
        return false;
    }

    for (size_t i = 1; i < edges.size(); i++) {
        auto &row = edges[i];

        int u = stoi(row[0]); // Location ID 1
        int v = stoi(row[1]); // Location ID 2
        string locName1 = row[2]; // Location name 1
        string locName2 = row[3]; // Location name 2
        int t = stoi(row[4]); // Time

        // making sure names exist before inserting into map
        if (!locName1.empty())
            // (emplace only inserts if key doesn't exist)
            locationNames.emplace(u, locName1);
        if (!locName2.empty())
            locationNames.emplace(v, locName2);

        addEdge(u, v, t);
    }

    // Load classes.csv
    auto classInfo = readCSV(classes_filepath);

    if (classInfo.empty()) {
        return false;
    }

    for (size_t i = 1; i < classInfo.size(); i++) {
        auto &row = classInfo[i];

        string code = row[0];
        int locationID = stoi(row[1]);
        int start = timeToMinutes(row[2]);
        int end = timeToMinutes(row[3]);

        classes[code] = {locationID, start, end};
    }

    return true;
}



// check if residence ID exists???????
void CampusCompass::insert(string name, int UFID, int residenceID, vector<string> classCodes) {

    // check if student id is unique
    if (students.find(UFID) != students.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    Student s;
    s.name = name;
    s.residenceID = residenceID;
    s.classCodes = classCodes;

    students[UFID] = s;
    cout << "successful" << endl;
}

void CampusCompass::remove(int UFID) {

    auto it = students.find(UFID);
    // check if student exist
    if(it == students.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    students.erase(it);
    cout << "successful" << endl;

}

void CampusCompass::dropClass(int UFID, string classCode) {

    // check if student exists
    auto it = students.find(UFID);
    if (it == students.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    // check if class code exists in the class codes table
    if (classes.find(classCode) == classes.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    Student &s = it->second;

    // check if student is enrolled in that class
    auto codeIt = find(s.classCodes.begin(), s.classCodes.end(), classCode);
    if (codeIt == s.classCodes.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    s.classCodes.erase(codeIt);

    // remove student if 0 classes (considered success)
    if (s.classCodes.empty()) {
        students.erase(it);
    }

    cout << "successful" << endl;

}

void CampusCompass::replaceClass(int UFID, string classCode1, string classCode2) {

    // check if student exists
    auto it = students.find(UFID);
    if (it == students.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    // check if class code 2 exists in class codes table
    if (classes.find(classCode2) == classes.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    Student &s = it->second;

    // check if student has class code 1
    auto codeIt1 = find(s.classCodes.begin(), s.classCodes.end(), classCode1);
    if (codeIt1 == s.classCodes.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    // check that student doesn't already have class code 2
    auto codeIt2 = find(s.classCodes.begin(), s.classCodes.end(), classCode2);
    if (codeIt2 != s.classCodes.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    // replace class code 1 with code 2 (In-place)
    // dereferencing pointer to code 1 and overwriting it
    *codeIt1 = classCode2;

    cout << "successful" << endl;

}

void CampusCompass::removeClass(string classCode) {

    int dropCounter = 0;

    // verify that class code exists
    auto itC = classes.find(classCode);
    if (itC == classes.end()) {
        cout << 0 << endl;
        return;
    }

    // iterate over all the students
    for (auto it = students.begin(); it != students.end(); ) {

        Student &s = it->second;

        // iterator for searching if students has class
        auto itSC = find(s.classCodes.begin(), s.classCodes.end(), classCode);
        // student has the class to be dropped
        if (itSC != s.classCodes.end()) {
            s.classCodes.erase(itSC);
            dropCounter++;

            // check if student has any classes
            if (s.classCodes.empty()) {
                // when erase is called -> it points to next !!!
                it = students.erase(it);
                // need to skip because we just deleted the iterator
                // and already points to the next class code
                continue;
            }
        }

        ++it;
    }

    cout << dropCounter << endl;


}

void CampusCompass::toggleEdgesClosure(int N, vector<int> &locationIDs) {
    // (edges always valid)

    // N already checked in parse command
    for (int i = 0; i < 2 * N; i += 2) {
        toggleEdge(locationIDs[i], locationIDs[i + 1]);
    }

    cout << "successful" << endl;

}

void CampusCompass::checkEdgeStatus(int locationIDx, int locationIDy) {
    GraphEdge* e = getEdge(locationIDx, locationIDy);

    if (e == nullptr) {
        cout << "DNE" << endl;
    } else if (e->open) {
        cout << "open" << endl;
    } else {
        cout << "closed" << endl;
    }
}

void CampusCompass::isConnected(int u, int v) {
    // check that edges exists
    if (Graph.find(u) == Graph.end() || Graph.find(v) == Graph.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    // check if they are the same
    if (u == v) {
        cout << "unsuccessful" << endl;
        return;
    }

    // BFS

    queue<int> q;
    unordered_set<int> visited;

    q.push(u);
    visited.insert(u);

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        vector<GraphEdge> neighbors = Graph[t];
        for (auto &s : neighbors) {

            // path not open then do not insert in queue and set
            if (!s.open) {
                continue;
            }

            // already visited
            if (visited.count(s.to) != 0) {
                continue;
            }

            // path found
            if (s.to == v) {
                cout << "successful" << endl;
                return;
            }

            visited.insert(s.to);
            q.push(s.to);
        }
    }

    cout << "unsuccessful" << endl;

}

