#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <map>
#include "Pipe.cpp"
#include "Container.cpp"

using namespace std;

const string fileURL =  "/Users/atus/Documents/schoolprog/prog2bead/prog2bead/test.txt";//to be replaced with actual fileURL

int main(int argc, const char * argv[]) {
    map<string, Container> containers;
    map<string, Pipe> pipes;
    
    int cap;
    string line;
    char name [20], start [20], end[20];
    ifstream initFile(fileURL);//to be replaced with actual file
    
    while(getline(initFile, line)){//get containers
        if(line == "-") break;
        
        sscanf(line.c_str(), "%s %d", name, &cap);
        cout << name << " " << cap << endl;
        containers.emplace(name, Container(name, cap));
    }
    
    while(getline(initFile, line)){//get pipes
        sscanf(line.c_str(), "%s %d %s %s", name, &cap, start, end);
        cout << name << " " << cap << start << end << endl;
        containers.emplace(name, Pipe(name, cap, &containers[start], &containers[end]));
    }
    
    return 0;
}
