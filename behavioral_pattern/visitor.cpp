#include <iostream>
#include <vector>

// 访问者模式
// 意图: 表示一个作用于某对象结构中的各元素的操作，在不改变这个数据结构的前提下定义作用于其内部各个元素的新操作
// 参与者:
// Visitor: (访问者， 为该对象结构中的每一个ConcreteElement类声明一个Visit操作)
// ConcreteVisitor: (访问者接口的实现，实现每个有visitor声明的操作)
// Element: (元素， 定义一个accept操作，以一个访问者为参数)
// ConcreteElement: (具体元素，实现Accept操作)
// ObjectStructure: (对象结构， 能枚举它的元素，并提供一个高层的接口允许访问者访问它的元素)

class Visitor;
class Element
{
    public:
        virtual void accept(Visitor & visitor) = 0;
};  

class program : public Element
{
    public:
        virtual void accept(Visitor &visitor) final;
};

class test : public Element
{
    public:
        virtual void accept(Visitor &visitor) final;
};

class varify : public Element
{
    public:
        virtual void accept(Visitor &visitor) final;
};

class Visitor
{
    public:
        virtual void visit(program & prog) = 0;
        virtual void visit(test & tester) = 0;
        virtual void visit(varify & varifier) = 0;
};

class ConcereteVisitor : public Visitor
{
    public:
        virtual void visit(program &prog)
        {
            std::cout << "start program" << std::endl;
        }
        virtual void visit(test & tester)
        {
            std::cout << "start testing" << std::endl;
        }
        virtual void visit(varify & varifier)
        {
            std::cout << "start varifying" << std::endl;
        }
};

class ConcereteVisitor2 : public Visitor
{
    public:
        virtual void visit(program &prog)
        {
            std::cout << "start program2" << std::endl;
        }
        virtual void visit(test & tester)
        {
            std::cout << "start testing2" << std::endl;
        }
        virtual void visit(varify & varifier)
        {
            std::cout << "start varifying2" << std::endl;
        }
};

void program::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void test::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void varify::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

class Company
{
    public:
        Company()
        {
            _department.emplace_back(new program());
            _department.emplace_back(new test());
            _department.emplace_back(new varify());
        }
        void startwork(Visitor &visitor)
        {
            for(Element *ptr : _department){
                ptr->accept(visitor);
            }
        }
    private:
        std::vector<Element *> _department;
};

int main()
{
    Company c;
    Visitor *vs = new ConcereteVisitor();
    c.startwork(*vs);
    Visitor *vs2 = new ConcereteVisitor2();
    c.startwork(*vs2);
    return 0;
}