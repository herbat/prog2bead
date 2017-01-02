#pragma once
#include <string>
#include <map>
#include "Pipe.hpp"

using namespace std;

typedef struct m{
    
    string name;
    int amount;
    
} Material;

class Container {
    string name;
    
    bool isClean;
    Material material;
    map<string, Pipe *> pipes;
    
public:
    int capacity;
    Container(){};
    Container(string _name, int _cap) : name(_name), capacity(_cap){};
    void addPipe(Pipe * pipe){
        pipes.emplace(pipe->name, pipe);
    }
    void addMaterial(string name, int amount){
        this->material = Material{name, amount};
    }
};
