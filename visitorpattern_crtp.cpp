#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>



template<typename T>
class Visitor {
public:
    virtual ~Visitor() {}
    virtual void visit(T & visitable) = 0;
};

// base
template <typename T>
class BaseVisitable
{
public:
	virtual void accept(Visitor<T> &visitor)
	{
		visitor.visit(static_cast<T &>(*this));
	}
	virtual ~BaseVisitable() {}
};

//derived starts here
class Blue: public BaseVisitable<Blue>
{
public:
    void see_the_sky () {
        std::cout << "The Sky is blue" << std::endl ;
    }
};

class Red: public BaseVisitable<Red>
{
public:
    void see_the_sun () {
       std::cout << "The Sun is red" << std::endl ;
    }
};

class Green: public BaseVisitable<Green>
{
public:
    void see_the_grass () {
       std::cout << "The Grass is green" << std::endl ;
    }
};


// derived visitors
class CallVisitor: public Visitor<Blue>, public Visitor<Red>, public Visitor<Green>
{
  public:
    void visit(Blue &b) {
        b.see_the_sky();
    }

    virtual void visit(Red &r) {
        r.see_the_sun();
    }
    virtual void visit(Green &g) {
        g.see_the_grass();
    }

};




int main(int argc, char** argv)
{
    CallVisitor cv;
    Blue().accept(cv) ;
    Red().accept(cv) ;
    Green().accept(cv) ;


    return 0;
}
