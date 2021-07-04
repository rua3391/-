#include <iostream>
#include <string>

// 装饰者模式
// 意图: 动态的为一个类的实例增加额外功能
// 参与者: 
// Component: (定义一个对象接口)
// ConcreteComponent: (定义一个对象，为这些对象添加一些职责)
// Decorator: (装饰者接口)
// ConcreteDecorator: (装饰者的实现接口)

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

class Icircle
{
    public:
        virtual void drawcircle() = 0;
};

// 此例中形状作为抽象化，颜色作为实例化，RefinedAbstraction(shape)补充了refined接口检查颜色类型
// 如果通过继承实现，每一个形状都会有3种颜色，当新增形状时会需要增加三个类，而使用桥接只需要增加一个形状类

// 默认圆
class circle : public RefinedAbstraction, public Icircle
{
    public:
        circle(Implementor *imp) : RefinedAbstraction(imp)
        {
            imp->setcolor(color);
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
        void drawcircle() final
        {
            Refined();
            std::cout << "draw normal " << color << " circle" << std::endl;
        }
};

// 装饰器，与圆圈共享相同的基类，保证接口一致，通过装饰器创建的只不过是有特殊操作的shape
class Decorator : public Icircle
{
    public:
        Decorator(Icircle *composite) : _composite(composite)
        {
        }
        Icircle *_composite;
        virtual void drawcircle() = 0;
};

class AreaDecorator : public Decorator
{
    public:
        AreaDecorator(Icircle *composite) : Decorator(composite)
        {
        }
        virtual void drawcircle() final
        {
            Message();
            _composite->drawcircle();
        }
    private:
        void Message()
        {
            std::cout << "Messge" << std::endl;
        }
};

int main()
{
    Implementor *imp = new Green();
    circle *Greencir = new circle(imp);
    Greencir->drawcircle();
    Icircle *AreaedCircle = new AreaDecorator(Greencir);
    AreaedCircle->drawcircle();
    return 0;
}