#include <iostream>
#include <unordered_map>

// 享元模式
// 意图: 创建一个共享对象让其在多个场景中使用
// 参与者:
// flyweight: (描述一个接口，通过这个接口flyweight可以接受并作用外部状态)
// ConcreteFlyweight: (flyweight接口具体实现，为内部状态增加存储空间)
// flyweightFactory: (创建并管理flyweight对象)
// client: (维持一个或多个flyweight的引用)

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

class client
{
    public:
        client() : _fac(new flyweightFactory())
        {

        }
        void useflyweight()
        {
            flyweight* whitePoint = _fac->getInstance(1);
            whitePoint->reflectpos(1,2);
            flyweight *blackPoint = _fac->getInstance(0);
            whitePoint->reflectpos(0,0);
            flyweight *blackPoint2 = _fac->getInstance(0);
            std::cout << blackPoint << " " << blackPoint2 << std::endl;
        }
    private:
        flyweightFactory *_fac;
};

int main()
{
    client cli;
    cli.useflyweight();
    return 0;
}