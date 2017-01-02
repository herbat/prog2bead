#pragma once
#include <string>
#include "Container.cpp"

using namespace std;

class Container;
class Pipe {
    string name;
    int capacity;
    bool on;
    const Container * start;
    const Container * end;
    
public:
    Pipe(){};
    Pipe(string _name, int _cap, const Container * _start, const Container *  _end):
           name(_name), capacity(_cap), start(_start), end(_end){};
};
