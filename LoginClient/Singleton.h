#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"
template <typename T>
class Singleton{
protected:
    // 私有构造函数，防止外部实例化
    Singleton() = default;
    // 禁用拷贝和复制
    Singleton(const Singleton<T>&) =delete;
    Singleton& operator = (const Singleton&) = delete;
    static std::shared_ptr<T> _instance;
public:
    //获取实例的唯一方法
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag,[&](){
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }
    void PrintAddress(){
        std::cout<<_instance.get()<<std::endl;
    }
    ~Singleton(){
        std::cout<<"this singleton destruct"<<std::endl;
    }
};
template<typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
#endif // SINGLETON_H
