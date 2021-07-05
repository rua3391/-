#include <iostream>

// 意图: 定义一个操作中的算法的骨架，将一些步骤延迟到子类中
// 参与者:
// AbstractClass: (抽象类，定义抽象的原语操作)
// ConcreteClass: (具体类，实现原语操作以完成算法中与特定子类相关的步骤)
// 原语是相对而言的不是真的原子操作 

class AbstractClass
{
    public:
        AbstractClass() = default;
        void execute()
        {
            step1();
            step2();
            step3();
        }
    protected:
        virtual void step1() = 0;
        virtual void step2() = 0;
        virtual void step3() = 0;
};

class ConcreteClass : public AbstractClass
{
    public:
        ConcreteClass() = default;
    protected:
        virtual void step1() final
        {
            std::cout << "step 1" << std::endl;
        }
        virtual void step2() final
        {
            std::cout << "step 2" << std::endl;
        }
        virtual void step3() final
        {
            std::cout << "step 3" << std::endl;
        }
};

int main()
{
    AbstractClass *abs = new ConcreteClass();
    abs->execute();
    return 0;
}