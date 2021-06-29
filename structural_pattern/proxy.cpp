#include <iostream>
#include <atomic>
// 意图: 为其他对象提供一种代理以控制对这个对象的访问
// 远程代理 ：为位于两个不同地址空间对象的访问提供了一种实现机制，可以将一些消耗资源较多的对象和操作移至性能更好的计算机上，提高系统的整体运行效率。
// 虚拟代理：通过一个消耗资源较少的对象来代表一个消耗资源较多的对象，可以在一定程度上节省系统的运行开销。
// 保护代理：可以控制对一个对象的访问权限，为不同用户提供不同级别的使用权限。
// 智能引用：要为一个对象的访问（引用）提供一些额外的操作时可以使用

// 缓冲代理：为某一个操作的结果提供临时的缓存存储空间，以便在后续使用中能够共享这些结果，优化系统性能，缩短执行时间。

template<typename T>
class smart_ptr
{
    public:
        smart_ptr() : _ptr(nullptr), _count(new size_t(0)) 
        {
        }
        smart_ptr(T* ptr) : 
            _ptr(ptr),
            _count(new size_t(1))
        {
        }
        smart_ptr(smart_ptr<T> &copy)
        {
            this->_ptr = copy.get();
            this->_count = copy.refcount();
            *this->_count++;
        }
        smart_ptr(smart_ptr<T> &&copy) noexcept
        {
            std::swap(this->_count, copy.refcount());
            std::swap(this->_ptr, copy.get());
        }
        smart_ptr<T> operator=(smart_ptr<T> &copy)
        {
            *this->_count--;
            release();
            this->_ptr = copy.get();
            this->_count = copy.refcount();
            *this->_count++;
        }
        smart_ptr<T> operator=(smart_ptr<T> &&copy)
        {
            *this->_count--;
            release();
            std::swap(this->_count, copy.refcount());
            std::swap(this->_ptr, copy.get());
        }
        T* get()
        {
            return _ptr;
        }
        size_t *refcount()
        {
            return _count;
        }
        T& operator *()
        {
            return (*_ptr);
        }
        T* operator ->()
        {
            return _ptr;
        }
    private:
        void release()
        {
            if(*_count == 0)
                delete(_ptr);
        }
        size_t *_count;
        T* _ptr;
};

struct test
{
    test() : i(0)
    {
    }
    void name()
    {
        std::cout << "test func" << std::endl;
    }
    int i;
};

int main()
{
    smart_ptr<int> ptr(new int(3));
    smart_ptr<test> ptr2(new test());
    std::cout << *ptr << std::endl;
    std::cout << ptr2->i << std::endl;
    return 0;
}