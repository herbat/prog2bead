#pragma once
#include <string>
#include <vector>
#include "Pipe.cpp"

using namespace std;

class Pipe;
class Container {
    string name;
    int capacity;
    vector<Pipe *> pipes;
    
public:
    Container(){};
    Container(string _name, int _cap) : name(_name), capacity(_cap){};
};
