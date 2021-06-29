#include <iostream>
#include <vector>

// 命令模式
// 意图: 将一个请求封装成一个对象，从而让用户使用不同的请求把客户端参数化；对请求排队或记录日志，以及支持可撤销的操作
// 参与者:
// Command: (声明执行操作的接口)
// ConcreteCommand: (将一个接收者对象绑定于一个命令，并实现Command接口)
// Receiver: (知道如何实施与执行一个请求相关的操作)
// Invoker: (要求该命令执行请求)
// Client: 创建一个具体命令对象并设置接收者
// 使用场景:
// 当需要将各种执行的动作抽象出来，使用时通过不同的参数来决定执行哪个对象
// 当某个或者某些操作需要支持撤销的场景
// 当要对操作过程记录日志，以便后期通过日志将操作过程重新做一遍时
// 当某个操作需要支持事务操作的时候
class Receiver
{
    public:
        Receiver() = default;
        void openfile()
        {
            std::cout << "open file command" << std::endl;
        }
        void addfile()
        {
            std::cout << "add file command" << std::endl;
        }
};

class Command
{
    public: 
        virtual void execute() = 0;
};

class openCommand : public Command
{
    public:
        openCommand(Receiver *re) : _recv(re)
        {
        }
        virtual void execute() final
        {
            _recv->openfile();
        }
        Receiver *_recv;
};

class addCommand : public Command
{
    public:
        addCommand(Receiver *re) : _recv(re)
        {
        }
        virtual void execute() final
        {
            _recv->addfile();
        }
        Receiver *_recv;
};

class invoker
{
    public:
        std::vector<Command *> list;
        void add(Command *cmd)
        {
            list.emplace_back(cmd);
        }      
        void remove()
        {
            list.pop_back();
        }
        void execute()
        {
            for (Command *cmd : list){
                cmd->execute();
            }
        }
};

int main()
{
    invoker inv;
    Receiver rev;
    inv.add(new openCommand(&rev));
    inv.add(new addCommand(&rev));
    inv.execute();
    return 0;
}