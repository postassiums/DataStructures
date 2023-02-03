#include <utility>
#include <cstddef>
#include "DynamicArrayIterator.hpp"
#pragma once

namespace IG{
template <typename T>
class DynamicArray{
    public:
        using Type=T;
        using Iterator=IG::DynamicArrayIterator<DynamicArray<T>>;

    private:
        size_t capacity=10;
        size_t length=0;
        T* data=nullptr;
    public:
    template<typename... Type>
    DynamicArray(const Type&&... args)
    {
        add(args...);
    }
    DynamicArray(){
        data=new T[capacity];

    }
    DynamicArray(DynamicArray& copy_from)
    {
        capacity=copy_from.capacity;
        T* new_data=(T*)::operator new(sizeof(T)*capacity);
        for (auto i = copy_from.begin(); i != copy_from.end(); i++)
        {
            new_data[i]=copy_from[i];
        }
        data=new_data;
        length=copy_from.length;

    }
    DynamicArray(DynamicArray&& move_from)
    {
        data=move_from.data;
        capacity=move_from.capacity;
        length=move_from.length;
    }
    DynamicArray& operator=(DynamicArray& copy_from)
    {
        if(this==&copy_from)
        {
            return this;
        }

        capacity=copy_from.capacity;
        T* new_data=(T*)::operator new(sizeof(T)*capacity);
        for (auto i = copy_from.begin(); i != copy_from.end(); i++)
        {
            new_data[i]=copy_from[i];
        }
        data=new_data;
        length=copy_from.length;

        return this;

    }
    DynamicArray& operator=(DynamicArray&& move_from)
    {

        if(this==&move_from)
        {
            return this;
        }

        capacity=move_from.capacity;
        T* new_data=(T*)::operator new(sizeof(T)*capacity);
        for (auto i = move_from.begin(); i != move_from.end(); i++)
        {
            new(&new_data[i]) T(std::move(move_from[i]));
        }
        data=new_data;
        length=move_from.length;

        move_from.data=0;
        move_from.length=0;
        move_from.data=nullptr;
        return this;
    }
    ~DynamicArray(){
        clear();
        ::operator delete(data,capacity*sizeof(T));
    }
    void resize(){
        size_t new_capacity=capacity*2;
        T* new_data=(T*)::operator new(new_capacity*sizeof(T));
        for (size_t i = 0; i < length; i++)
        {
            new(&new_data[i]) T(std::move(data[i]));
        }
        for (size_t i = 0; i < length; i++)
        {
            data[i].~T();/* code */
        }

        ::operator delete(data,capacity*sizeof(T));
        data=new_data;
        capacity=new_capacity;



    }
    T& operator[](size_t index){
        return getData(index);
    }
    T& getData(size_t index){
        return data[index];
    }
    template <typename... Args>
    void add(const T&& new_data,const Args&&... args)
    {
        add(std::forward<T>(new_data));
        add(std::forward<Args>(args)...);
    }
    void add(const T&& new_data){
        if(length==capacity){
            resize();
        }
        new(&data[length++]) T(std::move(new_data));
    }
    void pop(){
        if(length>0){
            data[--length].~T();
        }
    }
    void clear(){
        for (size_t i = 0; i < length; i++)
        {
            data[i].~T();
        }

    }
    template <typename... Args>
    void emplace(Args&&... args)
    {
       if(length>capacity)
       {
        resize();
       }
        new(&data[length++]) T(std::forward<Args>(args)...);
    }
    Iterator begin(){
        return DynamicArrayIterator(data);
    }
    Iterator end(){
        return DynamicArrayIterator(data+length);
    }
};

}
