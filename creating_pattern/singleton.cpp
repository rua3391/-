#include <iostream>

// 单例模式
// 意图: 保证一个类仅有一个实例
template<typename T>
class singleton
{
    public:
        singleton(const singleton &) = delete;
        singleton(const singleton &&) = delete;
        singleton operator =(const singleton &) = delete;
        singleton operator =(const singleton &&) = delete;
        static T* getInstance()
        {
            if(_instance == nullptr)
                _instance = new T();
            return _instance;
        }
    protected:
        singleton()
        {
            // std::cout << "construct base" << std::endl;
        }
    private:
        static T* _instance;
};
template<typename T>
T* singleton<T>::_instance = nullptr;

class derived : public singleton<derived>
{
    public:
        derived () = default;
        void count()
        {
            std::cout << 1 << std::endl;
        }
};

int main()
{
    derived::getInstance()->count();
    return 0;
}