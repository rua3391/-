#include <iostream>
#include <list>
#include <string>

// 观察者模式:
// 意图: 定义对象间的一种一对多的依赖方式，在一个对象状态发生改变时，通知所有依赖于它的对象
// 参与者:
// subject: (目标， 目标知道它的观察者，可以有多个观察者监视一个目标，目标应提供添加删除观察者对象的接口)
// Observer: (观察者，为那些在目标发生改变时需获得通知的对象定义一个更新接口)
// ConcreteSubject: (具体目标，保存有关状态，当状态发生变化时向各个观察者发出通知)
// ConcreteObserver: (具体观察者， 维护一个指向具体目标的引用，存储自身状态应与目标状态保持一致， 维护更新接口)

class observer;
class subject
{
    public:
        virtual void onchange() = 0;
        virtual void add(observer *) = 0;
        virtual void remove(observer *) = 0;
};

class observer
{
    public:
        virtual void update() = 0;
}; 

class publicMessage : public subject
{
    public:
        virtual void onchange()
        {
            for(observer *ptr : _list){
                ptr->update();
            }
        }
        virtual void add(observer *obs){
            _list.push_back(obs);
        }
        virtual void remove(observer *obs){
            for(auto i = _list.begin(); i != _list.end();){
                if(*i == obs){
                    i = _list.erase(i);
                }
                else
                    i++;
            }
        }
    private:
        std::list<observer *>_list;
};

class user : public observer
{
    public:
        user(const std::string &str) : _name(str){

        }
        virtual void update()
        {
            std::cout << _name << " receive update" << std::endl;
        }
        std::string _name;
};

int main()
{
    subject *msg = new publicMessage();
    observer *user1 = new user("aa");
    observer *user2 = new user("bb");
    msg->add(user1);
    msg->add(user2);
    msg->onchange();
    return 0;
}