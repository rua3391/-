#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

// 备忘录模式
// 意图: 在不破坏封闭的前提下捕获一个对象的内部状态，并在该对象之外保存这个状态，从而可以将对象恢复到原先保存的状态
// 参与者:
// Memento: (备忘录存储原发器对象的内部状态，并防止原发器以外的对象访问)
// Originator: (原发器，创建一个备忘录并记录它的状态)
// Caretaker: (负责人， 负责管理备忘录)

class flyweight
{
    public:
        flyweight() = default;
        virtual void reflectpos(int x, int y) = 0;
};

class point : public flyweight
{
    public:
        point(int c) : flyweight(), _color(c)
        {
        }
        virtual void reflectpos(int x, int y) final
        {
            std::cout << "the color of point at " << x << ", " << y << " is " << _color << std::endl;           
        }
    private:
        int _color;
};

class flyweightFactory
{
    public:
        flyweightFactory(){}
        std::unordered_map<int, flyweight*> obj;        
        flyweight *getInstance(int color)
        {
            flyweight *res;
            if(obj.find(color) != obj.end())
                return obj[color];
            if(color == 0){
                res = new point(0);
                obj[color] = res;
                return res;
            }
            else
            {
                res = new point(1);
                obj[color] = res;
                return res;
            }
        }
};

class client;
class memento
{
    public:
        memento() = default;
    private:
        friend class client;
        void savememento(std::vector<std::vector<flyweight *>> &matrix)
        {
            _matrix = matrix;
        }
        std::vector<std::vector<flyweight *>> getmemento()
        {
            return _matrix;
        }
        std::vector<std::vector<flyweight *>>_matrix;
};

class caretaker
{
    public:
        std::list<memento *> list;
    public:
        void savememento(memento *mem)
        {
            list.push_back(mem);
        }
        memento * loadmemento()
        {
            auto i = list.back();
            list.pop_back();
            return i;
        }
        static caretaker* getInstance()
        {
            if(_instance == nullptr)
            {
                _instance = new caretaker();
                return _instance;
            }
            return _instance;
        }
    protected:
        caretaker() = default;
        caretaker(caretaker &) = delete;
        caretaker(caretaker &&) = delete;
        caretaker& operator =(const caretaker &) = delete;
        caretaker& operator =(const caretaker &&) = delete;
    private:
        static caretaker* _instance;
};
caretaker* caretaker::_instance = nullptr;

class client
{
    public:
        client() : _fac(new flyweightFactory())
        {
            _matrix.resize(5, std::vector<flyweight *>(5, nullptr));
        }
        void useflyweight()
        {
            flyweight* whitePoint = _fac->getInstance(1);
            whitePoint->reflectpos(1,2);
            _matrix[1][2] = whitePoint;
            flyweight *blackPoint = _fac->getInstance(0);
            whitePoint->reflectpos(0,0);
            _matrix[0][0] = blackPoint;
            flyweight *blackPoint2 = _fac->getInstance(0);
            std::cout << blackPoint << " " << blackPoint2 << std::endl;
        }
        void createMemento()
        {
            caretaker::getInstance()->savememento(saveprogress());
        }
        void loadMemento()
        {
            _matrix = caretaker::getInstance()->loadmemento()->getmemento();
            std::cout << "load end" << std::endl;
        }
        void print(){
            for (int i = 0; i < _matrix.size(); ++i){
                for(int j = 0; j < _matrix[i].size(); ++j){
                    if(_matrix[i][j] != nullptr){
                        std::cout << "i j " << i << " " << j << std::endl;
                    }
                }
            }
            std::cout << "print end" << std::endl;
        }
        memento *saveprogress()
        {
            memento *memo = new memento();
            memo->savememento(_matrix);
            return memo;
        }
    private:
        flyweightFactory *_fac;
        std::vector<std::vector<flyweight *>> _matrix;
};

int main()
{
    client *cli= new client();
    cli->createMemento();
    cli->useflyweight();
    cli->print();
    cli->loadMemento();
    cli->print();
    return 0;
}