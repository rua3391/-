#include <iostream>
#include <utility>
#include <initializer_list>
#include <memory>

// 意图: 提供一种方法顺序访问一个容器对象中的各个元素，而又不需要暴露该对象的内部表示
// 参与者:
// Iterator: (迭代器接口)
// ConcreteIterator: (迭代器实现)
// Aggregate: (聚合)
// ConcreteAggregate: (聚合实现)
// 聚合应提供接口创建迭代器

template<typename T>
class Iterator
{
    public:
        virtual T& operator *() = 0;
        virtual T* operator ->() = 0;
        virtual bool operator ==(const Iterator<T>& another) = 0;
        virtual bool operator !=(const Iterator<T>& another) = 0;
        virtual T* base() const = 0;
};

template<typename T>
class randomAccessIterator : public Iterator<T>
{
    public:
        randomAccessIterator(T* pos): _ptr(pos)
        {

        }
        randomAccessIterator(randomAccessIterator<T> &&copy) noexcept
        {
            std::swap(copy.base(), this->base());  
        } 
        virtual T* base() const
        {
            return _ptr;
        }
        virtual T& operator *()
        {
            return *_ptr;
        }
        virtual T* operator ->()
        {
            return _ptr;
        }
        randomAccessIterator<T>& operator ++()
        {
            ++_ptr;
            return *this;
        }
        randomAccessIterator<T> operator ++(int)
        {
            return randomAccessIterator<T>(_ptr++);
        }
        randomAccessIterator<T> operator +(int num)
        {
            return randomAccessIterator<T>(_ptr + num);
        }
        randomAccessIterator<T> operator -(int num)
        {
            return randomAccessIterator<T>(_ptr - num);
        }
        randomAccessIterator<T>& operator +=(int num)
        {
            _ptr += num;
            return this;
        }
        randomAccessIterator<T>& operator -=(int num)
        {
            _ptr -= num;
            return this;
        }
        bool operator ==(const Iterator<T>& another)
        {
            return another.base() == this->base();
        }
        bool operator !=(const Iterator<T>& another){
            return another.base() != this->base();
        }
        ~randomAccessIterator()
        {
            _ptr = nullptr;
        }
    private:
        T* _ptr;
};


// myvector
template<typename T>
class vector
{
    public:
        // friend class randomAccessIterator<T>;
        vector() 
        {
            _begin = _cap = _emp = nullptr;
        }
        randomAccessIterator<T> begin()
        {
            return randomAccessIterator<T>(_begin);
        }
        randomAccessIterator<T> end()
        {
            return randomAccessIterator<T>(_emp);
        }
        void push_back(const T& i)
        {
            if(need_resize())
                resize();
            _alloc.construct(_emp++, i);
        }
        void push_back(const T&& i)
        {
            if(need_resize())
                resize();
            _alloc.construct(_emp++, i);
        }
        void push_back(const std::initializer_list<T>& list)
        {
            for(auto i : list){
                this->push_back(i);
            }
        }
        template<typename ...args>
        void emplace_back(args && ... arg)
        {
            if(need_resize())
                resize();
            _alloc.construct(_emp++, std::forward<args>(arg)...);
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
            T* newend = std::uninitialized_copy(_begin, _emp, newbegin);
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

struct test
{
    test(int i) : _i(i){}
    int _i;
};

int main()
{
    vector<int> vec;
    vec.push_back({1,2,3,4,5,6,7,8,9});
    for(auto i = vec.begin(); i != vec.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::cout << vec.capcity() << std::endl;
    vector<test> vec2;
    vec2.emplace_back(2);
    auto i = vec2.begin();
    std::cout << i->_i << std::endl;
    return 0;
}