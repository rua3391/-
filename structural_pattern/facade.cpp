#include <iostream>
#include <vector>
#include <string>
// 外观模式
// 意图: 为一系列接口提供统一的界面

class fruit
{
    public:
        virtual void getResult() = 0;
        std::vector<std::string> pattern;
};

class pie : public fruit
{
    public:
        void getResult() final
        {
            std::string res;
            for (auto &i : pattern){
                res += i;
                res += " ";
            }
            std::cout << res << std::endl;
        }
};

class builder
{
    public:
        void buildproduct()
        {
            product = new pie();
        }
        void addapple()
        {
            product->pattern.emplace_back("apple");
        }
        void addpear()
        {
            product->pattern.emplace_back("pear");
        }
        void addbanana()
        {
            product->pattern.emplace_back("banana");
        }
        fruit* getproduct()
        {
            return product;
        }
        fruit *product;      
};

class director
{
    public:
        fruit *build(builder &build)
        {
            build.buildproduct();
            build.addapple();
            build.addpear();
            build.addbanana();
            return build.getproduct();
        }
};

// 外观模式，隐去builder模式创建产品的过程
class facade
{
    public:
        void getpie()
        {
            builder *b = new builder();
            director *dir = new director();
            fruit *f = dir->build(*b);
            f->getResult();
        }
};

int main()
{
    facade f;
    f.getpie();
    return 0;
}