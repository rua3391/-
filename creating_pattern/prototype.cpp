#include <iostream>

// 意图: 用一个原型指定创建的种类
// 参与者: 
// Prototype(原型接口)
// ConcretePrototype(原型接口的实现)
// Client(让一个原型克隆自身创建新对象)

class Prototype
{
    public:
        virtual Prototype* clone() = 0;
};

class ConcretePrototype : public Prototype
{
    public:
        ConcretePrototype(int i):tmp(new int(i))
        {
        }
        ConcretePrototype(const ConcretePrototype& copy)
        {
            tmp = new int(*copy.tmp);
        }

        virtual ConcretePrototype* clone() final
        {
            return new ConcretePrototype(*this);
        }
        int *tmp;
};

class client
{
    public:
        client() : _proto(new ConcretePrototype(5))
        {
        };
        void init()
        {
            ConcretePrototype * copy = _proto->clone();
            std::cout << copy->tmp << " " << *copy->tmp << std::endl;
            std::cout << _proto->tmp << " " << *_proto->tmp << std::endl;
        }
    private:
        ConcretePrototype *_proto;
};

int main()
{
    client cli;
    cli.init();
    return 0;
}