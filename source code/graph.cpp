#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>
#include <cmath>
#include <iterator>
#include <sstream>

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    // printf("%s -> %d\n",inp.c_str(), res);
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    // cout << "new Function: " << fnc << endl;
    if(fnc.compare("mult")==0)
        f = new Multiplication(0, std::string(), idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(0, std::string(), idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);

    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){
    int fId = getFunction(fnc);
    int inpId = getVariable(inp1);
    int inpId2=getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->addInput(vars[inpId2]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[inpId2]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}


void Graph::addAssignment(string lvalue, string rvalue){
string output=lvalue;
vector<string> words;
    split1(rvalue, words);
    string fnc = words[0];
    int k=words.size();
    if(k==3) {
        addBinaryFunction(fnc,words[1],words[2],output);
    }else if(k==2){
        addUnaryFunction(fnc,words[1],output);
    }
    else{

        addUnaryFunction("identity",fnc,lvalue);
    }

}
void Graph::readGraph(string fileName){
    ifstream infile(fileName);
    vector<string> words;
    string line;
    getline(infile,line);
    split1(line,words );
    while(words[0].compare("input")==0){
        inputNodes.push_back(getVariable(words[1]));
        words.clear();
        getline(infile,line);
        split1(line,words );
    }

    outputNode=getVariable(words[1]);

    while(infile.peek()!=EOF){
        vector<string> words2;
        getline(infile,line);
        split1(line,words2 );
        string lvalue=words2[0];
        string rvalue;
        string sp=" ";

        for(int i=2;i<words2.size();i++){
            rvalue.append(words2[i]);
            rvalue.append(sp);


        }
        addAssignment(lvalue,rvalue);
    }

}

void Graph::initTopologicalOrder(queue<Node *> &q, int *incSizes){
}

bool Graph::isCyclic(){
}

double Graph::forwardPass(vector<double> inputValues){
}

vector<double> Graph::backwardPass(){
};
Graph::~Graph() {}