#include <cstddef>
#include <utility>
#pragma once
template <typename DynamicArray>
class VectorIterator
{
    public:
        using Type=typename DynamicArray::Type;
        using PointerType=Type*;
        using ReferenceType=Type&;
    private:
        PointerType pointer;


    public:
        VectorIterator(PointerType ptr): pointer(ptr){};
        VectorIterator& operator++()
        {
            pointer++;
            return *this;
        }
        VectorIterator operator++(int)
        {
            VectorIterator copy = *this;
            pointer++;
            return copy;
        }
        VectorIterator& operator--()
        {
            pointer--;
            return *this;
        }
        VectorIterator operator--(int)
        {
            VectorIterator copy = *this;
            pointer--;
            return copy;
        }
        ReferenceType operator[](int index)
        {
            return *(pointer + index);
        }
        PointerType operator->()
        {
            return pointer;
        }
        ReferenceType operator*()
        {
            return *pointer;
        }
        bool operator==(const VectorIterator& other) const
        {
            return pointer == other.pointer;
        }
        bool operator!=(const VectorIterator& other) const
        {
            return pointer != other.pointer;
        }
};
template <typename T>
class DynamicArray
{
public:
    using Type=T;
    using Iterator=VectorIterator<DynamicArray<T>>;

private:
    T* data=nullptr;
    size_t size=0;
    size_t capacity=0;
public:
    DynamicArray()
    {
        realloc(2);
    }
    ~DynamicArray()
    {
        clear();
        ::operator delete(data,capacity*sizeof(T));
        
    }
    template<typename... Args>
    void emplace(Args&&... args)
    {
        if(size>=capacity)
            realloc(capacity+capacity/2);
        new(&data[size]) T(std::forward<Args>(args)...);

    }
    void pushBack(T&& value)
    {
        
        if(size>=capacity)
        {
            realloc(capacity+capacity/2);
        }
        data[size]=std::move(value);
        size++;
    }
    void pushBack(const T& value)
    {
        if(size>=capacity)
        {
            realloc(capacity+capacity/2);
        }
        data[size]=value;
        size++;
    }
    void pop()
    {
        if(size>0)
        {
            size--;
            data[size].~T();
        }
    }
    void clear()
    {
        for(size_t i=0;i<size;i++)
        {
            data[i].~T();
        }
        size=0;
    }
    const T& operator[](size_t index) const
    {
        if(index>=size)
        {

        }
        return data[index];
    }
    T& operator[](size_t index){
        if(index>=size)
        {

        }
        return data[index];
    }
    size_t length() const {return size;}
    void realloc(size_t new_capacity)
    {
        T* new_block=(T*)::operator new(new_capacity*sizeof(T));
        if(new_capacity<size){
            size=new_capacity;
        }
        for(size_t i=0;i<size;i++)
        {
            new (&new_block[i]) T(std::move(data[i]));

        }
        for(size_t i=0;i<size;i++)
        {
            data[i].~T();
        }
        ::operator delete(data,capacity*sizeof(T));
        data=new_block;
        capacity=new_capacity;
    }
    Iterator begin() {
        return Iterator(data);
    }
    Iterator end() {
        return Iterator(data + size);
    }


};