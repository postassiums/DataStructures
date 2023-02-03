#include "SingleNodeIterator.hpp"
#include <functional>
#pragma once
namespace IG{



template <typename T>
class SingleNode{
    public:
        using Type=T;
        using Node=SingleNode<T>;
        using DataReference=T&;
        using DataTemporary=T&&;
        using NodePointer=Node*;
        using Iterator= SingleNodeIterator<Node>;


    private:

        NodePointer next=nullptr;
        T data;
    public:
        SingleNode()= default;

        ~SingleNode()
        {
            delete next;
        }
        SingleNode(const T&& data): data(std::move(data)){

        };
        SingleNode(const T&& data,NodePointer next) : data(std::move(data)),next(next){};
        SingleNode(const SingleNode& copy_from): data(data)
        {
        }
        SingleNode(SingleNode&& move_from): data(std::move(data))
        {
           move_from.next=nullptr;
           move_from.data=0;
        }
        SingleNode& operator=(SingleNode& copy_from)
        {
            if(this==&copy_from)
            {
                return *this;
            }

            data=copy_from.data;

            return *this;
        }
        SingleNode& operator=(SingleNode&& move_from)
        {
            if(this==&move_from){
                return *this;
            }
            data=std::move(move_from.data);

            move_from.data=0;
            move_from.next=nullptr;

            return *this;
        }
        public:

        void copyChildren(const SingleNode& copy_from)
        {

            if(copy_from.getNext()!=nullptr)
            {
                NodePointer current=this;
                auto lambda=[&] (Iterator& next_value)
                {
                    NodePointer new_node=new Node(next_value->getData());
                    current->setNext(new_node);
                    current=new_node;

                };
                copy_from->forEach(lambda);
            }
        }
        DataReference getData()const {return data;}
        NodePointer getNext()const {return next;}
        void setNext (const NodePointer new_next){next=new_next;}
        void setNext(const Iterator& new_iterator)
        {
            next=new_iterator->operator();
        }


        public:
        Iterator begin()
        {
            return SingleNodeIterator(this);
        }
        Iterator end()
        {
            return SingleNodeIterator<Node>();
        }


        void forEach(std::function<void(Iterator&)>& func)
        {
            if(next!=nullptr)
            {
                for(SingleNode<T>::Iterator it=this->begin();it!=this->end();it++)
                {
                    func(it);
                }
            }

            func(this);
        }
        DataReference getDataFromNext() const
        {
            return std::move(next->getData());

        }
        DataTemporary getTemporaryDataFromNext() const
        {
            return std::move(next->getData());

        }
        DataTemporary getTemporaryData() const
        {

            return std::move(data);
        }
        void operator[](const SingleNode* new_next)
        {
            next=new_next;
        }

        bool operator==(const Node& other) const
        {

            return next==other.next;
        }
        bool operator!=(const Node& other) const
        {

            return next!=other.next;
        }
        bool operator==(const Iterator& other) const
        {

            return next==other.node_pointer.next;
        }
        bool operator!=(const Iterator& other) const
        {
            return next!=other.node_pointer.next;

        };




};
using SingleNodeInt= SingleNode<int>;
using SingleNodeFloat=SingleNode<float>;
using SingleNodeDouble=SingleNode<double>;
using SingleNodeBool=SingleNode<bool>;
}
