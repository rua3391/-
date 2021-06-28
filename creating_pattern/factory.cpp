#include <iostream>
#include <vector>

// 工厂模式
// 意图: 定义一个用于创建对象的接口，让子类决定实例化哪个类
// 参与者: 
// Product(由工厂创建的对象的接口)
// ConcreteProduct(工厂所创建对象的具体实现，也就是Product的实现)
// Creator(创建对象的方法，可以是缺省的，也可以是完整的对象)
// ConcreteCreator(重定义创建对象的方法以返回实例)

class product
{
    public:
        product() = default;
        virtual void operator()()
        {
            std::cout << "default product" << std::endl;
        }
};

class apple : public product
{
    public:
        apple() = default;
        virtual void operator()() final
        {
            std::cout << "apple" << std::endl;
        }
};

class factory
{
    public:
        virtual product* getProduct()
        {
            std::cout << "called" << std::endl;
            return new product();
        }
    protected:
        factory()
        {
        }
};

template<typename T>
class standardFactory : public factory
{
    public:
        standardFactory(){}
        virtual product* getProduct() final
        {
            return new T();
        }
};

int main()
{
    standardFactory<apple> factory;
    (*factory.getProduct())();
    return 0;
}