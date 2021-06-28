#include <iostream>
#include <functional>
#include <memory>
#include <string>

// 桥接模式
// 意图: 将实现与抽象分离，使他们可以独立变化
// 参与者:
// Abstraction(抽象类的接口)
// RefinedAbstraction(扩充和修正Abstraction定义的接口)
// Implementor(实现类的接口)
// ConcreteImplementor(实现Implementor的接口)

class Implementor;
class Abstraction
{
    public:
        Implementor *_imp;
        Abstraction(Implementor *imp) : _imp(imp){} 
        virtual void getResult() = 0;
};

class RefinedAbstraction : public Abstraction
{
    public:
        RefinedAbstraction(Implementor *imp) : Abstraction(imp)
        {
        }
        virtual void Refined() = 0;
        std::string color;
};

class Implementor
{
    public:
        Implementor() = default;
        virtual void setcolor(std::string &co) = 0;
};

class Red : public Implementor
{
    public:
        Red() = default;
        virtual void setcolor(std::string &co) final
        {
            co = std::string("Red");
        }
};

class Blue : public Implementor
{
    public:
        Blue() = default;
        virtual void setcolor(std::string &co) final
        {
            co = std::string("Blue");
        }
};

class Green : public Implementor
{
    public:
        Green() = default;
        virtual void setcolor(std::string &co) final
        {
            co = std::string("Green");
        }
};

// 此例中形状作为抽象化，颜色作为实例化，RefinedAbstraction补充了refined接口检查颜色类型
// 如果通过继承实现，每一个形状都会有3种颜色，当新增形状时会需要增加三个类，而使用桥接只需要增加一个形状类

class circle : public RefinedAbstraction
{
    public:
        circle(Implementor *imp) : RefinedAbstraction(imp)
        {
            _imp->setcolor(color);
        }
        void getResult()
        {
            Refined();
            std::cout << "circle color is " << color << std::endl;
        }
        void Refined() final
        {
            if (color != "Red" && color != "Green" && color != "Blue")
                color = "null";
        }
};

void test(int i, int, double)
{
    std::cout << i << std::endl;
}

class recur
{
    public:
        void func(int a, int b, double c)
        {
            std::cout << "class member function" << std::endl;
        }
};

template<typename ...args>
class testclass
{
    using functype = std::function<void(args...)>;
    public:
        void tt()
        {
            std::cout << "test" << std::endl;
        }
        template<typename T>
        void bind(T && f)
        {
            this->_fn = [this, fn = std::forward<T>(f)](args &&... arg) mutable ->void 
            {
                (*fn)(std::forward<args>(arg)...);
            };
        }
        template<typename T, typename C>
        void bind(T && f, C && s)
        {
            this->_fn = [this, fn = std::forward<T>(f), c = std::forward<C>(s)](args && ...arg) mutable->void
            {
                ((*c).*fn)(std::forward<args>(arg)...);
            };
        }
        void operator ()(args&& ... arg)
        {
            _fn(std::forward<args>(arg)...);
        }
        functype _fn;
};

void func(int a, int b, double c)
{
    std::cout << "a: " << a << "b: " << b << "c: " << c << std::endl;
}

int main()
{
    // testclass<int, int ,double> t;
    // t.bind(func);
    // t(5,10, 15.0);
    // t.bind(&recur::func, std::make_shared<recur>());
    // t(10, 15, 20.0);

    Implementor *imp = new Red();
    circle *Redcir = new circle(imp);
    Redcir->getResult();
    Implementor *imp2 = new Green();
    circle *Greencir = new circle(imp2);
    Greencir->getResult();
    return 0;
}