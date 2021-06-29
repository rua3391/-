#include <stack>
#include <deque>
#include <iostream>
#include <utility>

// 意图: 使一个类的接口转化为用户希望的形式
// 参与者:
// Target: 定义用户使用的相关接口
// Adaptee: 一个存在的接口，需要被适配
// Adapter: 对Adaptee的接口与Target的接口进行适配
// 适配器有两种形式: 对象适配器与类适配器
// 类适配器共有继承Target并且私有继承Adaptee，对象适配器拥有一个Adaptee
// 适配器复杂度取决于要适配的接口与目标接口的相似度

//目标 实现一个stack
template<typename T>
class Target
{
    public:
        virtual void push(T &i) = 0;
        virtual void push(T && i) = 0;
        virtual void pop() = 0;
        virtual T top() = 0;
        virtual size_t size() = 0;
        virtual bool empty() = 0; 
};

// myvector
template<typename T>
class vector
{
    public:
        vector() 
        {
            _begin = _cap = _emp = nullptr;
        }
        T* begin()
        {
            return _begin;
        }
        T* end()
        {
            return _emp;
        }
        void push_back(const T& i)
        {
            if(need_resize())
                resize();
            _alloc.construct(_emp++, std::forward<T&>(i));
        }
        void push_back(const T&& i)
        {
            if(need_resize())
                resize();
            _alloc.construct(_emp++, std::forward<T>(i));
        }
        void pop_back()
        {
            _alloc.destroy(_emp--);
        }
        T front()
        {
            return *_begin;
        }
        T back()
        {
            return *(_emp - 1);
        }
        size_t size()
        {
            return _emp - _begin;
        }
        size_t capcity()
        {
            return _cap - _begin;
        }
        bool empty()
        {
            return size() == 0;
        }
    private:
        bool need_resize()
        {
            return size() >= capcity();
        }
        void resize()
        {
            size_t size = this->size();
            int newsize;
            if(size == 0)
                newsize = 1;
            else
                newsize = size * 2;
            T* newbegin = _alloc.allocate(newsize);
            _cap = newbegin + newsize;
            T* newend = std::uninitialized_copy(begin(), end(), newbegin);
            while(size > 0)
            {
                _alloc.destroy(_emp--);
                size--;
            }
            _alloc.deallocate(_begin, size);
            _begin = newbegin;
            _emp = newend;
        }
        T* _begin;
        T* _emp;
        T* _cap;
        std::allocator<T> _alloc;
};

//方式1 类适配器，与target建立is-a关系，与vector建立has-a关系
template<typename T>
class stack1 : public Target<T>, private vector<T>
{
    public:
        virtual void push(T & i) final
        {
            this->push_back(i);
        }
        virtual void push(T && i) final
        {
            this->push_back(i);
        }
        virtual void pop() final
        {
            this->pop_back();
        }
        virtual T top() final
        {
            return this->back();
        }
        virtual size_t size() final
        {
            return vector<T>::size();
        }
        virtual bool empty() final
        {
            return vector<T>::empty();
        }
};

// 方式2 对象适配器
template<typename T>
class stack2 : public Target<T>
{
    public:
        virtual void push(T & i) final
        {
            _vector.push_back(i);
        }
        virtual void push(T && i) final
        {
            _vector.push_back(i);
        }
        virtual void pop() final
        {
            _vector.pop_back();
        }
        virtual T top() final
        {
            return _vector.back();
        }
        virtual size_t size() final
        {
            return _vector.size();
        }
        virtual bool empty() final
        {
            return _vector.empty();
        }
    private:
        vector<T> _vector;
};

int main()
{
    vector<int> v;
    Target<int> *s1 = new stack1<int>();
    std::cout << s1->empty() << std::endl;
    s1->push(1);
    s1->push(2);
    std::cout << s1->top() << std::endl;
    Target<int> *s2 = new stack2<int>();
    s2->push(6);
    s2->push(7);
    std::cout << s2->top() << std::endl;
    return 0;
}