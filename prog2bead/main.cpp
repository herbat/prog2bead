#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Pipe.cpp"
#include "Container.cpp"

using namespace std;

const int MAX = 20;
const string initfileURL = "/Users/atus/Documents/schoolprog/prog2bead/prog2bead/test.txt";//to be replaced with actual fileURL
const string endfileURL  = "/Users/atus/Documents/schoolprog/prog2bead/prog2bead/end.txt";

typedef struct{
    string name;
    string cont;
    double amt;
} Mat;

template<class T>
void printVector(vector<T> vec, int dim);
bool isFinished(map<string, Container> containers, vector<Mat> finish);
vector<vector<Material> > createflowmatrix(map<string, Container> containers, map<string, Pipe> pipes);
vector<string> pathf(map<string, Container> containers, map<string, Pipe> &pipes, string start, string end);
void step (map<string, Container> &containers, map<string, Pipe> &pipes,  vector<vector<Material>> flowmatrix, double time);

int main(int argc, const char * argv[]) {
    map<string, Container> containers;
    map<string, Pipe> pipes;
    
    vector<Mat> source, finish;
    vector<string> path;
    vector<vector<Material>> flowmatrix;
    
    int cap, amt;
    //double time;
    string line;
    char name [MAX], start [MAX], end[MAX], cont[MAX];
    ifstream initFile(initfileURL);
    ifstream endFile(endfileURL);
    
    //INITIAL STATE--------------------------------------------------
    
    while(getline(initFile, line)){//get containers
        if(line == "-") break;
        sscanf(line.c_str(), "%s %d", name, &cap);
        containers.emplace(name, Container(name, cap));
    }
    
    while(getline(initFile, line)){//get pipes
        if(line == "-") break;
        sscanf(line.c_str(), "%s %d %s %s", name, &cap, start, end);
        if(containers.find(start) == containers.end() || containers.find(end) == containers.end()) break;
        pipes.emplace(name, Pipe(name, cap, start, end));
        containers[start].addPipe(&pipes[name]);
        containers[end].addPipe(&pipes[name]);
    }
    
    while(getline(initFile, line)){//get materials
        if(line == "-") break;
        sscanf(line.c_str(), "%s %s %d", name, cont, &amt);
        if(containers.find(cont) == containers.end()) break;
        if(containers[cont].getCap() < amt) continue;
        containers[cont].addMaterial(name, amt);
        source.push_back(Mat{name, cont, static_cast<double>(amt)});
    }
    
    while(getline(endFile, line)){//get end conditions
        if(line == "-") break;
        sscanf(line.c_str(), "%s %s %d", name, cont, &amt);
        if(containers.find(cont) == containers.end()) break;
        if(containers[cont].getCap() < amt) continue;
        finish.push_back(Mat{name, cont, static_cast<double>(amt)});
    }
    
    path = pathf(containers, pipes, source[0].cont, finish[0].cont);
    
    while(!isFinished(containers, finish)){
    
        for(auto pipe : path){
            if(!pipes[pipe].isOn()){
                pipes[pipe].switchTo(true);
                cout << "on " << pipes[pipe].getName() << " " << pipes[pipe].getEnd() << endl;
            }
        }
        flowmatrix = createflowmatrix(containers, pipes);
        step(containers, pipes, flowmatrix, 0);
    
    }
    cout << "Mission complete." << endl;
    return 0;
}

vector<string> pathf(map<string, Container> containers, map<string, Pipe> &pipes, string start, string end){
    vector<string> path;
    if (start == end) return path;
    for (auto p : containers[start].getPipes()) {
        if (p.second->getEnd() == end) path.push_back(p.second->getName());
        else if (p.second->getStart() == end) {p.second->switchDirection(); path.push_back(p.second->getName());}
    }
    return path;
}

vector<vector<Material>> createflowmatrix(map<string, Container> containers, map<string, Pipe> pipes) {
    vector<vector<Material>> flowmatrix;
    
    for(auto source : containers) {//c is every container
        vector<Material> flows;
        map<string, Pipe * > conPipes =  source.second.getPipes();//pipes connected to the actual container
        
        for (auto end : containers) {
            
            if(end.first == source.first) { flows.push_back(Material{"", 0}); continue; }
            map<string, Pipe * > endPipes = end.second.getPipes();//pipes connected to the other containers
            bool added = false;
            
            for (auto p : conPipes){
                
                if (endPipes.find(p.first) != endPipes.end() && p.second->isOn()) {//if pipe is connected to both containers
                    
                    if (p.second->getStart() == source.first){
                        flows.push_back(Material{source.second.getMaterial(), static_cast<double>(-p.second->getCap())});//and cont is source, then negative
                        added = true;
                    } else { //if not source, then end, which means positive
                        flows.push_back(Material{   end.second.getMaterial(), static_cast<double>( p.second->getCap())});
                        added = true;
                    }
                    
                }
                
            }
            if (!added) flows.push_back(Material{"", 0});
        }
        flowmatrix.push_back(flows);
    }
    
    return flowmatrix;
}

void step (map<string, Container> &containers, map<string, Pipe> &pipes,  vector<vector<Material>> flowmatrix, double time) {
    
    cout << "step" << endl;
    vector<double> sum;
    vector<string> materials;
    double t_temp = 1-time;
    int keresett = 0;//ahol update kell a flowban
    
    for(int i = 0; i < containers.size(); i++) {
        double tsum = 0;
        bool added = false;
        
        for(auto c : flowmatrix[i]){
            tsum += c.amount;
            if(!added) { materials.push_back(c.name); added = true;}//prevent multiple materials flowing into one container
        }
        
        sum.push_back(tsum);
    }
    
    int count = 0;
    for(auto c : containers) {
        
        if(sum[count] != 0) {
            if(sum[count] > 0 && t_temp*sum[count] > c.second.getLeftVolume()) {//ha megtelőben van, akkor számoljuk újra az időt
                t_temp = (c.second.getLeftVolume())/sum[count];
                keresett = count;
                cout << " fund " << endl;
            } else if(t_temp*sum[count] < (0 - c.second.getAmt())) {
                t_temp = (0-c.second.getAmt())/sum[count];
                keresett = count;
            }
        }
        count++;
    }
    
    count = 0;
    for(auto c : containers) {
        
        if(c.second.isEmpty())
            containers[c.first].addMaterial(materials[count], sum[count]*t_temp);
        else containers[c.first].addAmount(sum[count]*t_temp);
        count++;
    }
    
}

bool isFinished(map<string, Container> containers, vector<Mat> finish){
    for(auto f : finish) {
        if(!(containers[f.cont].getMaterial() == f.name && containers[f.cont].getAmt() == f.amt)){
            return false;
        }
    }
    return true;
}

template<class T>
void printVector(vector<T> vec, int dim){
    if(dim == 1) {
        for(auto i : vec){
            cout << &i << " " << endl;
        }
    } else if (dim == 2) {
        for(auto r : vec){
            for(auto c : r){
                cout << c.amount << " ";
            }
            cout << endl;
        }
    }
}

