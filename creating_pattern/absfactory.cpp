#include <iostream>

// 抽象工厂模式
// 意图: 提供一个创建一系列相关或相互依赖的对象的接口，无需指定具体的类
// 参与者:
// AbstractFactory(一个创建抽象产品对象的接口)
// ConcreteFactory(工厂接口的具体实现)
// AbstractProduct(一类产品的接口)
// ConcreteProduct(一类具体的将被工厂创建的产品，也是AbstractProduct的具体实现)
// Client(客户，仅使用AbstractFactory及AbstractProduct声明的接口)

class product
{
    public:
        product() = default;
        virtual void operator()()
        {
            std::cout << "default" << std::endl;
        }
};

class iphone : public product
{
    public:
        iphone() = default;
        virtual void operator()() final
        {
            std::cout << "iphone product" << std::endl;
        }
};

class Huawei : public product
{
    public:
        Huawei() = default;
        virtual void operator()() final
        {
            std::cout << "Huawei product" << std::endl;
        }
};

class apple : public product
{
    public:
        apple() = default;
        virtual void operator()() final
        {
            std::cout << "apple product" << std::endl;
        }
};

class banana : public product
{
    public:
        banana() = default;
        virtual void operator()() final
        {
            std::cout << "banana product" << std::endl;
        }
};

class abstractFactory
{
    public:
        abstractFactory() = default;
        virtual product* createProduct1() = 0;
        virtual product* createProduct2() = 0;
};

class phoneFactory : public abstractFactory
{
    public:
        phoneFactory() = default;
        virtual product* createProduct1() final
        {
            return new iphone();
        }
        virtual product* createProduct2() final
        {
            return new Huawei();
        }
};

class fruitFactory : public abstractFactory
{
    public:
        fruitFactory() = default;
        virtual product* createProduct1() final
        {
            return new apple();
        } 
        virtual product* createProduct2() final
        {
            return new banana();
        } 
};

int main()
{
    abstractFactory *fac1 = new phoneFactory();
    abstractFactory *fac2 = new fruitFactory(); 
    product* phone1 = fac1->createProduct1();
    product* phone2 = fac1->createProduct2();
    (*phone1)();
    (*phone2)();
    product* fruit1 = fac2->createProduct1();
    product* fruit2 = fac2->createProduct2();
    (*fruit1)();
    (*fruit2)();
    return 0;
}