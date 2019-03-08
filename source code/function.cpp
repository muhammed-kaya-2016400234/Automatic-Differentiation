#include "function.h"
#include <cmath>
using namespace std;
Function::Function(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Function::addInput(Variable *input) {
    this->inputs.push_back(input);
}
void Function::setOutput(Variable *_output) {
    this->output=_output;
}
vector<Node *> Function::getIncomings() {
    vector<Node*>a;
    vector<Variable*>::iterator it;
    for(it=inputs.begin();it!=inputs.end();++it) {
        a.push_back(*it);
    }
    return a;
}
vector<Node *> Function::getOutgoings() {
    vector<Node*>a;
    a.push_back(output);
}
Function::~Function() {}

Function::Function() {}

Multiplication::Multiplication(int _id1, string _name1, int _id, string _name) {
     this->id=_id;
     this->name=_name;
 }
void Multiplication::doForward() {
    vector<Variable*>::iterator it;
    double a;
    for(it=this->inputs.begin();it!=this->inputs.end();++it){
        a*=(*it)->value;
    }
    this->output->value=a;
}
void Multiplication::doBackward() {
    inputs[0]->derivative+=output->derivative*inputs[1]->value;
    inputs[1]->derivative+=output->derivative*inputs[0]->value;

}
Addition::Addition(int _id1, string _name1, int _id, string _name)  {
    this->id=_id;
    this->name=_name;

}
void Addition::doForward() {
    vector<Variable*>::iterator it;
    double a;
    for(it=this->inputs.begin();it!=this->inputs.end();++it){
        a+=(*it)->value;
    }
    this->output->value=a;

}
void Addition::doBackward() {

    inputs[0]->derivative+=output->derivative;
    inputs[1]->derivative+=output->derivative;
}
Sine::Sine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Sine::doForward()  {
    double a=this->inputs[0]->value;
    this->output->value=sin(a);
}
void Sine::doBackward() {
    double a=this->output->derivative;
    double b=this->inputs[0]->value;
    double c=cos(b);
    this->inputs[0]->derivative+=c*a;
}

Subtraction::Subtraction(int _id1, string _name1, int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Subtraction::doForward() {
    this->output->value=inputs[0]->value-inputs[1]->value;
}
void Subtraction::doBackward() {
    inputs[0]->derivative+=output->derivative;
    inputs[1]->derivative-=output->derivative;
}
Division::Division(int _id, string _name) {
    this->id=_id;
    this->name=_name;

}
void Division::doForward() {
    this->output->value=this->inputs[0]->value/this->inputs[1]->value;
}
void Division::doBackward() {
    inputs[0]->derivative+=(1/inputs[1]->value)*this->output->derivative;
    inputs[1]->derivative-=(inputs[0]->value/(pow(inputs[1]->value,2)))*this->output->derivative;
}
Cosine::Cosine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Cosine::doForward() {
    this->output->value=cos(this->inputs[0]->value);
}
void Cosine::doBackward() {
    double a=this->output->derivative;
    double b=this->inputs[0]->value;
    double c=-1*sin(b);
    this->inputs[0]->derivative+=c*a;
}

Identity::Identity(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Identity::doForward() {
    this->output->value=this->inputs[0]->value;
}
void Identity::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative;
}

Tangent::Tangent(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void Tangent::doForward() {
    this->output->value=tan(this->inputs[0]->value);
}
void Tangent::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative*(1/(pow(cos(this->inputs[0]->value),2)));

}
ArcCosine::ArcCosine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void ArcCosine::doForward() {
    this->output->value=acos(this->inputs[0]);
}
void ArcCosine::doBackward() {
    double a=this->output->derivative;
    double x=this->inputs[0]->value;
    this->inputs[0]->derivative+=a*((-1)/sqrt(1-pow(x,2)));

}

ArcSine::ArcSine(int _id, string _name) {this->id=_id;
    this->name=_name;}
void ArcSine::doForward() {
    this->output->value=asin(this->inputs[0]->value);
}
void ArcSine::doBackward() {
    double a=this->output->derivative;
    double x=this->inputs[0]->value;
    this->inputs[0]->derivative+=a*(1/sqrt(1-pow(x,2)));
}

ArcTangent::ArcTangent(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
void ArcTangent::doForward() {
    this->output->value=atan(this->inputs[0]->value);
}
void ArcTangent::doBackward() {
    double a=this->output->derivative;
    double x=this->inputs[0]->value;
    this->inputs[0]->derivative+=a*(1/1+pow(x,2));
}

Exponential::Exponential(int _id, string _name) {
    this->id = _id;
    this->name = _name;
}

    void Exponential::doForward(){
        this->output->value=exp(this->inputs[0]);
    }
    void Exponential::doBackward() {
        this->inputs[0]->derivative+=this->output->derivative*exp(this->inputs[0]->value);
    }
Log::Log(int _id, string _name) {this->id=_id;
    this->name=_name;}

    void Log::doForward() {
        this->output->value=log(this->inputs[0]->value);
    }
    void Log::doBackward() {
        double a=this->inputs[0]->value;
        double b=this->output->derivative;
        this->inputs[0]->derivative+=b*1/a;
    }
Log10::Log10(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
    void Log10::doForward() {
        this->output->value=log10(this->inputs[0]->value);
    }
    void Log10::doBackward() {
       double a=this->inputs[0]->value;
        double b=this->output->derivative;
       this->inputs[0]->derivative+=b*1/(a*log(10));
    }
Power::Power( int _id,int _name) {
    this->id=_id;
    this->name=_name;
}
    void Power::doForward() {
        double a=this->inputs[0]->value;
        double b=this->inputs[1]->value;
        this->output->value=pow(a,b);
    }
    void Power::doBackward() {
        double a=this->inputs[0]->value;
        double b=this->inputs[1]->value;
        double c=this->output->derivative;
        this->inputs[0]->derivative+=c*(b*pow(a,b-1));
        this->inputs[1]->derivative+=c*(log(a)*pow(a,b));
    }
Sqrt::Sqrt(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}
    void Sqrt::doForward() {
        this->output->value=sqrt(this->inputs[0]->value);
    }
    void Sqrt::doBackward() {
        this->inputs[0]->derivative+=(pow(this->inputs[0]->value,-0.5))/2;
    }

