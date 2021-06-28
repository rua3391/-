#include <iostream>
#include <string>

// builder：生成器模式
// 意图: 将构建与表示分离，使得同样的构建过程可以创建不同的表示
// 参与者:
// builder(接口)
// concreteBuilder(接口实现)
// Director(使用builder的对象)
// Product(被构造的复杂对象)

class product : public std::string
{
};

class builder
{
    public:
        builder() = default;
        virtual void buildproduct()
        {
            std::cout << "default built" << std::endl;
        }
        virtual void buildfst()
        {
            std::cout << "default fst" << std::endl;
        }
        virtual void buildsec()
        {
            std::cout << "default sec" << std::endl;
        }
        virtual void buildthr()
        {
            std::cout << "default thr" << std::endl;
        }
        virtual product* getProduct()
        {
            std::cout << "default product" << std::endl;
            return nullptr;
        }
};

class concreteBuilder : public builder
{
    public:
        concreteBuilder() : _product(nullptr)
        {

        };
        virtual void buildproduct() final
        {
            if(!_product)
                _product = new product();
        }
        virtual void buildfst() final
        {
            _product->push_back('a');
        }
        virtual void buildsec() final
        {
            _product->push_back('x');
        }
        virtual void buildthr() final
        {
            _product->push_back('e');
        }
        virtual product *getProduct() final
        {
            return _product;
        }
    private:
        product *_product;
};

class Director
{
    public:
        product* create(builder &build)
        {
            build.buildproduct();
            build.buildfst();
            build.buildsec();
            build.buildthr();
            return build.getProduct();
        }
};

int main()
{
    concreteBuilder builder;
    Director dir;
    auto i = dir.create(builder);
    std::cout << *i << std::endl;
    return 0;
}