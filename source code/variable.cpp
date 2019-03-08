#include "variable.h"
#include "function.h"

Variable::Variable(){}
Variable::Variable(int _id, string _name, double _value) {

    this->id=_id;
    this->name=_name;
    this->value=_value;

}

void Variable::setFrom(Function *_from) {
    this->from=_from;
}
void Variable::addTo(Function *_to) {
    this->to.push_back(_to);
}

vector<Node *> Variable::getIncomings() {
    vector <Node *> a;

    a.push_back(from);
    return a;
}
vector<Node*> Variable::getOutgoings() {
    vector<Node*> a;
    vector<Function*>::iterator it;
    for(it=to.begin();it!=to.end();++it) {
        a.push_back(*it);
    }
    return a;
}
Variable::~Variable() {}
Node::~Node() {}