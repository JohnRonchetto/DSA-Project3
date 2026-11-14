# CampusCompass

A C++ campus navigation system built on a weighted graph of campus buildings.
It stores students with their residence hall and class schedule, then answers
routing questions with classic graph algorithms:

- **Dijkstra's algorithm:** the fastest route from a student's residence to each class
- **Kruskal's algorithm + disjoint-set union:** the minimum spanning tree of a student's "zone"
- **Breadth-first search:** whether two buildings are still connected when paths are closed
- **Dijkstra + sorting by class time:** whether there's enough time to get between back-to-back classes

## Example

```
$ ./Main
3
insert "Brandy" 45679999 20 2 COP3530 MAC2311
printShortestEdges 45679999
printStudentZone 45679999
```
```
successful
Name: Brandy
COP3530 | Total Time: 20
MAC2311 | Total Time: 15
Student Zone Cost For Brandy: 22
```

## Commands

The first line is the number of commands that follow.

| Command | What it does |
|---|---|
| `insert "NAME" ID RESIDENCE N CLASS...` | Add a student with an 8-digit ID, a residence location and 1 to 6 class codes. |
| `remove ID` | Remove a student. |
| `dropClass ID CLASS` | Drop one class from a student's schedule. |
| `replaceClass ID OLD NEW` | Swap one class for another. |
| `removeClass CLASS` | Remove a class from every student. |
| `toggleEdgesClosure N u1 v1 u2 v2 ...` | Open or close N paths between locations. |
| `checkEdgeStatus u v` | Print whether a path is open, closed or doesn't exist. |
| `isConnected u v` | Check whether two locations can reach each other using open paths. |
| `printShortestEdges ID` | Shortest travel time from the student's residence to each of their classes. |
| `printStudentZone ID` | Cost of the minimum spanning tree covering the student's routes to class. |
| `verifySchedule ID` | Check whether each pair of consecutive classes can be reached in time. |

Invalid commands or input print `unsuccessful`.

## How it works

- **Graph:** an adjacency list of campus locations, loaded from `data/edges.csv`.
  Each edge has a travel time in minutes and can be opened or closed.
- **Shortest paths:** Dijkstra's algorithm from the student's residence, skipping closed edges.
- **Student zone:** collects every location on the student's shortest routes,
  builds the subgraph between them, and finds its minimum spanning tree with
  **Kruskal's algorithm** and a **disjoint-set union** structure.
- **Connectivity:** breadth-first search over open edges only.
- **Schedule check:** sorts the student's classes by start time, then compares the shortest travel time between consecutive classes
  with the gap between them, using class times from `data/classes.csv`.

## Build and run

Requires CMake 3.22+ and a C++17 compiler.

```bash
cmake -S . -B build
cmake --build build
cd build && ./Main
```

The build copies `data/` next to the executable, so run it from `build/`.

## Project structure

```
src/
  CampusCompass.cpp/.h   graph, student records and all commands
  kruskalDS.cpp/.h       disjoint-set union used by Kruskal's algorithm
  parseCommand.cpp/.h    command parsing and validation
  main.cpp               loads the CSVs and reads commands from stdin
data/
  edges.csv              campus locations and travel times
  classes.csv            class locations and meeting times
```

Built for a Data Structures & Algorithms course.
