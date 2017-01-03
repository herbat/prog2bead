#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Pipe.cpp"
#include "Container.cpp"

using namespace std;

const int MAX = 20;
const string fileURL =  "/Users/atus/Documents/schoolprog/prog2bead/prog2bead/test.txt";//to be replaced with actual fileURL
const string fileURL2 =  "/Users/atus/Documents/schoolprog/prog2bead/prog2bead/test2.txt";
void step();

int main(int argc, const char * argv[]) {
    map<string, Container> containers;
    map<string, Pipe> pipes;
    
    int cap, amt;
    string line;
    char name [MAX], start [MAX], end[MAX], cont[MAX], command[MAX];
    ifstream initFile(fileURL);
    ifstream initFile2(fileURL2);
    
    //INITIAL STATE--------------------------------------------------
    
    while(getline(initFile, line)){//get containers
        if(line == "-") break;
        sscanf(line.c_str(), "%s %d", name, &cap);
        containers.emplace(name, Container(name, cap));
    }
    
    while(getline(initFile, line)){//get pipes
        sscanf(line.c_str(), "%s %d %s %s", name, &cap, start, end);
        if(containers.find(start) == containers.end() || containers.find(end) == containers.end()) break;
        pipes.emplace(name, Pipe(name, cap, start, end));
        containers[start].addPipe(&pipes[name]);
    }
    
    while(getline(initFile2, line)){
        sscanf("%s %s %d", name, cont, &amt);
        cout << name << " " << amt;
        if(containers.find(cont) == containers.end()) break;
        if(containers[cont].getCap() < amt) continue;
        containers[cont].addMaterial(name, amt);
    }
    
    //---------------------------------------------------------------
    
    //COMMAND SECTION------------------------------------------------
    
    while(scanf("%s %s %s", command, name, end)){
        if(strcmp(command, "step")) {
            step();
        } else if (strcmp(command, "off") && pipes.find(name) == pipes.end()) {
            pipes[name].switchTo(false);
        } else if (strcmp(command, "clean") && containers.find(name) == containers.end()) {
            containers[name].clean();
        } else if (strcmp(command, "on") && pipes.find(name) == pipes.end() && containers.find(end) == containers.end()) {
            if(pipes[name].getEnd() == end)
                pipes[name].switchTo(true);//just open it
            
            else if(pipes[name].getStart() == end)
                containers[pipes[name].getEnd()].flowTo(end);//reverse direction and open it
            
            else { cout << "Bad command" << endl; continue; }// bad command so skip
        } else {
            cout << "Bad command" << endl;
            continue;
        }
    }
    
    //---------------------------------------------------------------
    
    
    
    
    //vector<string> path = findpath(containers, "A", "B", * new vector<string>);
    //cout << path[0] << endl;
    return 0;
}














//vector<string> findpath(map<string, Container> containers, string start, string end,vector<string> path){
//    // The set of nodes already evaluated.
//    closedSet := {}
//    // The set of currently discovered nodes still to be evaluated.
//    // Initially, only the start node is known.
//    openSet := {start}
//    // For each node, which node it can most efficiently be reached from.
//    // If a node can be reached from many nodes, cameFrom will eventually contain the
//    // most efficient previous step.
//    cameFrom := the empty map
//    
//    // For each node, the cost of getting from the start node to that node.
//    gScore := map with default value of Infinity
//    // The cost of going from start to start is zero.
//    gScore[start] := 0
//    // For each node, the total cost of getting from the start node to the goal
//    // by passing by that node. That value is partly known, partly heuristic.
//    fScore := map with default value of Infinity
//    // For the first node, that value is completely heuristic.
//    fScore[start] := heuristic_cost_estimate(start, goal)
//    
//    while openSet is not empty {
//        current := the node in openSet having the lowest fScore[] value
//        if current = goal
//            return reconstruct_path(cameFrom, current);
//            
//        openSet.Remove(current)
//        closedSet.Add(current)
//        for each neighbor of current {
//            if neighbor in closedSet
//                continue		// Ignore the neighbor which is already evaluated.
//            // The distance from start to a neighbor
//            tentative_gScore := gScore[current] + dist_between(current, neighbor)
//            if neighbor not in openSet	// Discover a new node
//                openSet.Add(neighbor)
//            else if tentative_gScore >= gScore[neighbor]
//                continue		// This is not a better path.
//                            
//            // This path is the best until now. Record it!
//            cameFrom[neighbor] := current
//            gScore[neighbor] := tentative_gScore
//            fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
//        }
//        return failure
//                            
//        function reconstruct_path(cameFrom, current)
//            total_path := [current]
//                            while current in cameFrom.Keys:
//                                current := cameFrom[current]
//                                total_path.append(current)
//                                return total_path
//}
//
