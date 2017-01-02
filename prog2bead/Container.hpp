#pragma once
#include <string>
#include <map>
#include "Pipe.hpp"

using namespace std;

class Container {
    string name;
    int capacity;
    map<string, Pipe *> pipes;
    
public:
    Container(){};
    Container(string _name, int _cap) : name(_name), capacity(_cap){};
    void addPipe(Pipe * pipe);
};

