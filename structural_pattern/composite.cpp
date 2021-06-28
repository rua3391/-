#include <iostream>
#include <vector>

// 组合模式 
// 意图: 以相同的方式处理单个对象和对象的组合体(本质是个多叉树)
// 参与者: 
// component: (为所有参与组合的对象声明接口)
// Leaf: (表示叶子节点)
// composite: (定义每一个子部件的行为，存储子部件)

class component
{
    public:
        virtual void add(component *node) = 0;
        virtual int getcount() = 0;
};

class composite : public component
{
    public:
        composite()
        {
        }
        virtual void add(component *node) final
        {
            _nodes.push_back(node);
        }  
        virtual int getcount() final
        {
            int count = 0;
            for(component *node: _nodes)
            {
                count += node->getcount();
            }
            return count;
        }
    private:
        std::vector<component *> _nodes;
};

class leaf : public component
{
    public:
        leaf()
        {

        }
        virtual void add(component *node) final
        {
            std::cout << "can't add node to leaf" << std::endl;
        }
        virtual int getcount() final
        {
            return 1;
        }
};

int main()
{
    component *root = new composite();
    component *apartment = new composite();
    component *node1 = new leaf();
    component *node2 = new leaf();
    apartment->add(node1);
    apartment->add(node2);
    root->add(apartment);
    std::cout << root->getcount() << std::endl;
    return 0;
}