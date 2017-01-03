#pragma once
#include <iostream>
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
    bool isEmpty;
    Material material;
    int capacity;
    map<string, Pipe *> pipes;
    
public:
    Container(){};
    Container(string _name, int _cap) : name(_name), capacity(_cap){
        isEmpty = true;
        isClean = true;
    };
    int getCap(){
        return capacity;
    }
    void addPipe(Pipe * pipe){
        pipes.emplace(pipe->getName(), pipe);
    }
    void addMaterial(string name, int amount){
        this->material = Material{name, amount};
        isEmpty = false;
    }
    
    void clean(){
        if(isClean) return;
        for (auto i : pipes){
            i.second->switchTo(false);
            cout << "off" << i.second->getName() << endl;
        }
        isClean = true;
    }
    
    void flowTo(string dest){
        for (auto i : pipes){
            if(i.second->getStart() == dest) i.second->switchDirection();
            if (i.second->getEnd() == dest) i.second->switchTo(true);
        }
    }
};
