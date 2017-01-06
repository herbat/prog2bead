#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include <list>
#include <math.h>
using namespace std;

/// tortennek valami hulyesegek a csovek vektorban
/// noemi fajlja kiakasztja a dolgokat

struct cso
{
public:
    string nev_cso;
    double d_cso;
    bool nyitvae ;
    string tar1;
    string tar2;
    bool switch_=false;
};

struct cel
{
    string cel_nev;
    string cel_nedv;
    int cel_V;
};

struct tartaly
{
    string nev_tart;
    double V;
    map<tartaly*,cso>szomsz;
    bool tisztae = true;
    string nedv;
    double V_nedv =0;
    double delta;
    
};

struct szabad_cso
{
    tartaly* t1;
    tartaly* t2;
    cso ertek;
};

struct halozat
{
    vector<tartaly*>tartalyok;
    vector<cso>csovek;
};

void calcflow (string name, vector<double>flows, halozat graf)
{   int i =0;
    while(graf.tartalyok[i]->nev_tart != name)
    {
        i++;
    }
    double sum = 0;
    for (int j=0; j<flows.size();j++)
    {
        sum = sum + flows[j];
    }
    
}
bool beolvas(string fnev, string knev, string cnev, halozat &graf, cel &C)
{
    tartaly T;
    string sor;
    ifstream bf(fnev);
    ifstream bk(knev);
    ifstream bc(cnev);
    if(!bf.good()) return false;
    stringstream ss;
    
    while( getline(bf, sor) && sor != "-")
        
    {
        
        int temp;
        ss.clear();
        ss << sor;
        sor = "";
        
        ss >> T.nev_tart;
        ss >> T.V;
        T.nedv = "Ures";
        
        graf.tartalyok.push_back(new tartaly(T));
        
    }
    
    cso CS;
    
    while( getline(bf,sor))
    {
        ss.clear();
        ss << sor;
        sor = "";
        
        
        ss >> CS.nev_cso;
        ss >> CS.d_cso;
        ss >> CS.tar1;
        ss >> CS.tar2;
        
        CS.nyitvae = false;
        CS.switch_ = false;
        
        graf.csovek.push_back(CS);
        
        
        
        for (int i=0; i<graf.tartalyok.size(); i++)
        {
            
            if (graf.tartalyok[i]->nev_tart == CS.tar1 )
            {
                for (int j=0; j<graf.tartalyok.size(); j++)
                {
                    if (graf.tartalyok[j]->nev_tart == CS.tar2)
                    {
                        graf.tartalyok[i]->szomsz.insert(pair<tartaly*,cso>(graf.tartalyok[j],CS));
                        
                        
                        
                        
                    }
                }
            }
            
            if (graf.tartalyok[i]->nev_tart == CS.tar2 )
            {
                for (int j=0; j<graf.tartalyok.size(); j++)
                {
                    if (graf.tartalyok[j]->nev_tart == CS.tar1)
                    {
                        graf.tartalyok[i]->szomsz.insert(pair<tartaly*,cso>(graf.tartalyok[j],CS));
                        
                        
                    }
                }
            }
            
            
            
        }
        /*        for (int i=0; i<graf.csovek.size();i++)
         {
         for (int j=i+1; j<graf.csovek.size();j++)
         {
         if (graf.csovek[i].ertek.nev_cso == graf.csovek[j].ertek.nev_cso)
         graf.csovek.erase(graf.csovek.begin()+j);
         }
         
         }*/
    }
    
    if(!bk.good()) return false;
    
    
    while(getline(bk,sor))
    {
        string temp_nedv;
        int temp_V = 0;
        ss.clear();
        ss << sor;
        sor = "";
        
        
        ss >> temp_nedv;
        ss >> sor;
        ss >> temp_V;
        
        
        for (int i=0; i<graf.tartalyok.size(); i++)
        {
            if (graf.tartalyok[i]->nev_tart == sor)
            {
                graf.tartalyok[i]->nedv = temp_nedv;
                graf.tartalyok[i]->V_nedv = temp_V;
                graf.tartalyok[i]->tisztae = false;
            }
        }
        
        sor="";
    }
    if(!bc.good()) return false;
    
    while(getline(bc,sor))
    {
        ss.clear();
        ss << sor;
        
        ss >> C.cel_nedv;
        ss >> C.cel_nev;
        ss >> C.cel_V;
        
    }
    
    return true;
    
    
}

double** createflowmatrix(halozat& graf, int a, int b)
{
    double** flowmatrix = 0;
    flowmatrix = new double* [a];
    for (int i=0; i<a; i++)
    {
        flowmatrix[a]= new double[b];
    }
    double flows[b];
    for(int i=0; i<graf.tartalyok.size();i++)
    {
        
        for (int j=0; j<graf.csovek.size();j++)
        {
            if (graf.tartalyok[i]->nev_tart == graf.csovek[j].tar1)
            {
                if (graf.csovek[j].nyitvae == true )
                {
                    if (graf.csovek[j].switch_ == false) flows[j] = -graf.csovek[j].d_cso;
                    if (graf.csovek[j].switch_ == true)  flows[j] =  graf.csovek[j].d_cso;
                }
                if (graf.csovek[j].nyitvae == false ) flows[j]=0;
            }
            if (graf.tartalyok[i]->nev_tart == graf.csovek[j].tar2)
            {
                if (graf.csovek[j].nyitvae == true )
                {
                    if (graf.csovek[j].switch_ == true) flows[j] = -graf.csovek[j].d_cso;
                    if (graf.csovek[j].switch_ == false)flows[j] =  graf.csovek[j].d_cso;
                }
                if (graf.csovek[j].nyitvae == false ) flows[j]=0;
            }
            
            if(graf.tartalyok[i]->nev_tart != graf.csovek[j].tar1 && graf.tartalyok[i]->nev_tart != graf.csovek[j].tar2)
            {
                flows[j]=0;
            }
            
        }
        for (int j=0; j<b;j++)
        {
            flowmatrix[i][j]=flows[j];
        }
    }
    return flowmatrix;
}

void step ( halozat& graf, double** m, int time)
{
    
    double sum[graf.tartalyok.size()];
    double flowmatrix[graf.tartalyok.size()][graf.csovek.size()] = m;
    
    double t = time;
    double t_temp = 1-time;
    int keresett = 0;
    
    for(int i = 0; i < sum.size(); i++)
    {
        for(int j=0; j<graf.csovek.size(); j++)
        {
            sum[i]+=flowmatrix[i][j];
        }
    }
    for(int i=0; graf.tartalyok.size(); i++)
    {
        if(sum[i] != 0)
        {
            if(sum[i]>0 && t_temp > (graf.tartalyok[i]->V - graf.tartalyok[i]->V_nedv)/sum[i]) {t_temp = (graf.tartalyok[i]->V - graf.tartalyok[i]->V_nedv)/sum[i]; keresett = i;}
            if(sum[i]<0 && t_temp > (0 - graf.tartalyok[i]->V_nedv)/sum[i]) {t_temp = (0 - graf.tartalyok[i]->V_nedv)/sum[i]; keresett = i;}
        }
    }
    if(t+t_temp == 1)
    {
        for(int i=0 ;i <graf.tartalyok.size();i++)
        {
            graf.tartalyok[i]->V_nedv += sum[i]*t_temp;
        }
        return;
    }
    
    else
    {
        for(int i = 0; i < graf.tartalyok.size();i++)
        {
            graf.tartalyok[i]->V_nedv += sum[i]*t_temp;
        }
    }
    double poz[graf.csovek.size()];
    int alfa = 1;
    double sumt = sum[keresett];
    
    if(sum[keresett]<0)
    {
        alfa = -1;
    }
    for(int i=0; i<graf.csovek.size();i++)
    {
        if(flowmatrix[keresett][i]*alfa > 0)
        {
            poz[i]=flowmatrix[keresett][i];
            sumt = sumt-poz[i];
        }
    }
    if(sumt == 0)
    {
        for (int i=0; i<graf.csovek.size();i++)
            
        {
            if(flowmatrix[keresett][i] != 0)
            {
                if( graf.csovek[i].tar1 == graf.tartalyok[keresett]->nev_tart)
                {
                    
                    for(int j=0; j<graf.tartalyok.size();j++)
                    {
                        if(graf.tartalyok[j]->nev_tart == graf.csovek[i].tar2)
                        {
                            flowmatrix[keresett][i]=0;
                            flowmatrix[j][i]=0;
                        }
                    }
                }
                else
                {
                    for(int j=0; j<graf.tartalyok.size();j++)
                    {
                        if(graf.tartalyok[j]->nev_tart == graf.csovek[i].tar1)
                        {
                            flowmatrix[keresett][i]=0;
                            flowmatrix[j][i]=0;
                        }
                    }
                }
            }
        }
        step(graf, flowmatrix, t+t_temp);
    }
    else
    {  alfa = 1;
        double sumt2;
        vector<double>index;
        
        if (sumt < 0)    alfa=-1;
        
        for(int i= 0; i< graf.csovek.size(); i++)
        {
            if ( flowmatrix[keresett][i]*alfa > 0 )
            {
                sumt2=+flowmatrix[keresett][i];
                index.push_back(i);
                
            }
        }
        
        for(int i=0; i<index.size();i++)
        {
            if (graf.csovek[index[i]].tar1 == graf.tartalyok[keresett]->nev_tart)
            {
                for (int j=0; j<graf.tartalyok.size();j++)
                {
                    if(graf.csovek[index[i]].tar2 == graf.tartalyok[j]->nev_tart)
                    {
                        flowmatrix[keresett][index[i]]*=(sumt2-sum[keresett])/sumt2;
                        flowmatrix[j][index[i]]*=(sumt2-sum[keresett])/sumt2;
                    }
                }
            }
        }
        step(graf,flowmatrix,t+t_temp);
    }
    
}

void kiiro(halozat &graf)
{
    for(vector<tartaly*>::iterator it=graf.tartalyok.begin();it!=graf.tartalyok.end();it++)
    {
        cout<<(*it)->nev_tart<<"( "<<(*it)->V<< " ) " << (*it)->nedv << " " << (*it)->V_nedv << endl;
        for(map<tartaly*,cso>::iterator it2=(*it)->szomsz.begin();it2!=(*it)->szomsz.end();it2++)
        {
            cout<<it2->first->nev_tart<<"("<<it2->second.nev_cso<<")";
        }
        cout<<endl;
    }
    /*     for(vector<szabad_cso>::iterator it=graf.csovek.begin();it!=graf.csovek.end();it++)
     {
     cout<<it->ertek.nev_cso<< "(" << it->ertek.d_cso <<")" << " : " << it->t1->nev_tart << " - " << it->t2->nev_tart << endl;
     
     }
     */
}
vector<tartaly*> szomszed_kereses (tartaly* t){
    vector<tartaly*> sz;
    for (map<tartaly*,cso>::iterator it = t->szomsz.begin(); it != t->szomsz.end(); it++){
        sz.push_back(it->first);
    }
    return sz;
}

void flow (halozat &graf, vector<tartaly*>ut, cel C)
{
    for (int i=0; i<ut.size(); i++)
    {
        ///on(ut[i+1]);
        while (ut[i]->V_nedv != 0 or ut[i+1]->V == ut[i+1]->V_nedv )
        {
            ///step(graf);
        }
        ///   if(ut[i]->V_nedv != 0)
        
    }
}

void takarit (vector<vector<tartaly*>>utak, cel jo_lesz, halozat &graf)
{
    vector<tartaly*>idene;
    vector<tartaly*>szomszedok;
    vector<tartaly*>szemet;
    for (int i=0;i<utak.size();i++)
    {
        for (int j=1; j<utak[i].size();j++)
        {
            if(utak[i][j]->nedv != "Ures" and utak[i][j]->nedv != jo_lesz.cel_nedv )
            {
                szemet.push_back(utak[i][j]);
            }
        }
    }
    for (int i = 0; i<utak.size(); i++)
    {
        idene = utak[i];
        for (int j=1; j<utak[i].size();j++)
        {
            
            
            if (utak[i][j]->nedv != "Ures" && utak[i][j]->nedv != jo_lesz.cel_nedv)
            {   cout << "fuck" << endl;
                szomszedok = szomszed_kereses(utak[i][j]);
                for (int k=0; k<idene.size(); k++)
                {
                    for (int m=0; m<szomszedok.size(); m++)
                    {
                        if (idene[k] == szomszedok[m]) szomszedok.erase(szomszedok.begin()+m-1);
                    }
                }
                if ( ! szomszedok.empty())
                {
                    for (int n=0; n<szomszedok.size(); n++)
                    {   ///meg kelle itt keresni melyik csorol van szo
                        ///on(szomszedok[n]);
                        while (utak[i][j]->V_nedv != 0 or szomszedok[n]->V == szomszedok[n]->V_nedv )
                        {
                            ///step(graf);
                        }
                        ///off
                        
                    }
                    if (utak[i][j]->V_nedv != 0)
                    {
                        ///on(idene[j+1])
                        while (utak[i][j]->V_nedv != 0 or idene[j+1]->V == szomszedok[j+1]->V_nedv )
                        {
                            ///step(graf);
                        }
                        ///off
                    }
                }
                else
                {  if(idene[j+1]->nev_tart==jo_lesz.cel_nev) cout<< "megoldhatatlan";
                    ///on(idene[j+1])
                    while (utak[i][j]->V_nedv != 0 or idene[j+1]->V == szomszedok[j+1]->V_nedv )
                    {
                        ///step(graf);
                    }
                    ///off
                }
            }
        }
    }
    
    return;
}



int main()
{
    halozat graf;
    cel C;
    beolvas("rendszer2.txt","kezdeti2.txt","celallapot",graf,C);
    vector<vector<tartaly*>>utak;
    vector<tartaly*>ut;
    ut.push_back(graf.tartalyok[0]);
    ut.push_back(graf.tartalyok[1]);
    ut.push_back(graf.tartalyok[2]);
    ut.push_back(graf.tartalyok[4]);
    utak.push_back(ut);
    
    takarit(utak,C,graf);
    
    /// command section
    string command;
    string name;
    string dest;
    ifstream initcommand("Command.txt");
    while(initcommand.good())
    {   int i=0;
        initcommand >> command;
        ///   if(command == "step") step();
        if(command == "off")
        {
            initcommand >> name;
            while(graf.csovek[i].nev_cso != name)
            {
                i++;
            }
            graf.csovek[i].nyitvae = false;
        }
        if(command == "on")
        {
            initcommand >> name;
            while(graf.csovek[i].nev_cso != name)
            {
                i++;
            }
            graf.csovek[i].nyitvae = true;
            
            initcommand >> dest;
            
            if(graf.csovek[i].switch_ == true && dest == graf.csovek[i].tar1) graf.csovek[i].nyitvae = true;
            else if(graf.csovek[i].switch_ == true && dest == graf.csovek[i].tar2){ graf.csovek[i].nyitvae = true; graf.csovek[i].switch_ = false;}
            else if(graf.csovek[i].switch_ == false && dest == graf.csovek[i].tar2) graf.csovek[i].nyitvae = true;
            else if(graf.csovek[i].switch_ == false && dest == graf.csovek[i].tar1) {graf.csovek[i].nyitvae = true; graf.csovek[i].switch_ = true;}
            else cout << "hibas parancs";
            
            if(command == "clean")
            {
                initcommand >> name;
                
                while(graf.tartalyok[i]->nev_tart != name)
                {
                    i++;
                }
                if (graf.tartalyok[i]->V_nedv == 0)
                {
                    for(int i=0; i<graf.csovek.size(); i++)
                    {
                        if(graf.csovek[i].tar1 == name or graf.csovek[i].tar2 == name)
                            graf.csovek[i].nyitvae = false;
                    }
                    graf.tartalyok[i]->tisztae = true;
                }
            }
        }
    }
    return 0;
}
