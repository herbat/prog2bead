#pragma once
#include <string>

using namespace std;

class Pipe {
    int capacity;
    bool on;
    const string start;
    const string end;
    
public:
    string name;
    Pipe(){};
    Pipe(string _name, int _cap, const string _start, const string _end):
           name(_name), capacity(_cap), start(_start), end(_end){};
    string getName();
};


