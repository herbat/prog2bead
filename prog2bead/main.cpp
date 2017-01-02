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

int main(int argc, const char * argv[]) {
    map<string, Container> containers;
    map<string, Pipe> pipes;
    
    int cap, amt;
    string line;
    char name [MAX], start [MAX], end[MAX], cont[MAX];
    ifstream initFile(fileURL);
    
    //INITIAL STATE--------------------------------------------------
    
    while(getline(initFile, line)){//get containers
        if(line == "-") break;
        sscanf(line.c_str(), "%s %d", name, &cap);
        containers.emplace(name, Container(name, cap));
    }
    
    while(getline(initFile, line)){//get pipes
        sscanf(line.c_str(), "%s %d %s %s", name, &cap, start, end);
        if(containers.find(cont) == containers.end()) break;
        pipes.emplace(name, Pipe(name, cap, start, end));
        containers[start].addPipe(&pipes[name]);
    }
    
    while(scanf("%s %s %d", name, cont, &amt)){
        cout << name << " " << amt;
        if(containers.find(cont) == containers.end()) break;
        if(containers[cont].capacity < amt) continue;
        containers[cont].addMaterial(name, amt);
    }
    
    //---------------------------------------------------------------
    
    //TODO: Managing pathfinding
    
    return 0;
}

vector<string> findpath(map<string, Container> containers, string start, string end,vector<string> path){
    path.push_back(start);
    if (start == end)
        return path;
    if (containers.find(start) == containers.end())
        return * new vector<string>;
    for (auto i : containers[start].pipes){
        vector<string> newpath;
        if(find(path.begin(), path.end(), i.first) == path.end())
            newpath = findpath(containers, i.first, end, path);
        if(newpath.size() != 0)
            return newpath;
    }
    return * new vector<string>;
}

