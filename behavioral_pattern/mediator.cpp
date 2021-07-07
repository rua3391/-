#include <iostream>
#include <list>
#include <set>
#include <string>

// 意图： 用一个中介对象来封装一系列的对象交互，中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。
// 使用场景:
// 1、系统中对象之间存在比较复杂的引用关系，导致它们之间的依赖关系结构混乱而且难以复用该对象。 
// 2、想通过一个中间类来封装多个类中的行为，而又不想生成太多的子类
// 参与者:
// Mediator: (中介者，定义一个接口与同事通信)
// ConcreteMediator: (中介者接口实现，了解并维护它的各个同事)
// Colleague class: (同事类)

enum action
{
    online = 1,
    offline = 2,

    Max = 3
};

class Colleague;
class Mediator
{
    public:
        Mediator() = default;
        virtual void update(Colleague *coll, action act) = 0;
        virtual void sendmsg(Colleague *coll, const std::string &msg) = 0;
};

class chatRoom : public Mediator
{
    public:
        chatRoom() = default;
        virtual void update(Colleague *coll, action act) final;
        virtual void sendmsg(Colleague *coll, const std::string &msg) final;
    private:
        std::set<Colleague*> user_list;        
};

class Colleague
{
    public:
        Colleague(Mediator *mediator, const std::string &name) : _name(name), _chatroom(mediator){
            mediator->update(this, online);
        }
        void gotMsg(const std::string &msg){
            std::cout << _name << " got msg " << msg << std::endl;
        }
        void sendMsg(const std::string &msg){
            _chatroom->sendmsg(this, msg);
        }
        ~Colleague()
        {
            _chatroom->update(this, offline);
        }
    private:
        Mediator * _chatroom;
        std::string _name;
};

void chatRoom::update(Colleague *coll, action act)
{
    if (act == online)
        user_list.insert(coll);
    else if(act == offline){
        auto iter = user_list.find(coll);
        if(iter != user_list.end()){
            user_list.erase(iter);
        }
    }
}

void chatRoom::sendmsg(Colleague *coll, const std::string &msg)
{
    for(auto i : user_list){
        if(i != coll){
            i->gotMsg(msg);
        }
    }
}

int main()
{
    chatRoom *chat = new chatRoom();
    Colleague *coll1 = new Colleague(chat, "m1");
    Colleague *coll2 = new Colleague(chat, "rx79");
    coll1->sendMsg("123321");
    std::cout << std::endl;
    return 0;
}