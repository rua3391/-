#include <iostream>

// 责任链模式
// 意图: 避免请求发送者与接收者耦合在一起，让多个对象都有可能接收请求，将这些对象连接成一条链，并且沿着这条链传递请求，直到有对象处理它为止
// 关键部分: 实现后继者链，避免环路
// 参与者:
// Handler: (定义处理链接的接口)
// ConcreteHandler: (如果可处理请求，就处理，否则转发给后继)
// Client: (向链上的ConcreteHandler发起请求)

class Handler
{
    public:
        Handler(Handler *h) : _handler(h)
        {

        }
        virtual void handle(int i)
        {
            if(_handler)
                _handler->handle(i);
        };
    private:
        Handler *_handler;
};

class GroupLeader : public Handler
{   
    public:
        GroupLeader(Handler *h) : Handler(h)
        {

        }
        virtual void handle(int i) final
        {
            if(i < 1000)
            {
                std::cout << "GroupLeader can handle" << std::endl;
            }
            else
                Handler::handle(i);
        }
};

class Manager : public Handler
{
    public:
        Manager(Handler *h) : Handler(h)
        {

        }
        virtual void handle(int i) final
        {
            if(i < 2500)
            {
                std::cout << "Manager can handle" << std::endl;
            }
            else 
                Handler::handle(i);
        }
};

class Boss : public Handler
{
    public:
        Boss() : Handler(nullptr)
        {

        }
        virtual void handle(int i) final
        {
            std::cout << "Boss can handle" << std::endl;
        }
};

int main()
{
    Handler *boss = new Boss();
    Handler *manager = new Manager(boss);
    Handler *groupleader = new GroupLeader(manager);
    groupleader->handle(2000);
    return 0;
}