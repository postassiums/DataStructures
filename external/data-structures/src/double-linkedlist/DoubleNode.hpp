
#include "single-linkedlist/SingleNodeIterator.hpp"
#include <functional>
#pragma once
namespace IG{
    
using DoubleNodeInt=SingleNode<int>;
using DoubleNodeFloat=SingleNode<float>;
using DoubleNodeDouble=SingleNode<double>;
using DoubleNodeBool=SingleNode<bool>;


template <typename T>
class SingleNode{
    public:
        using Type=T;
        using Node=IG::SingleNode<T>;
        using DataReference=T&;
        using NodePointer=Node*
        using Iterator=IG::SingleNodeIterator<Node>;

        
    private:

        NodePointer next=nullptr;
        NodePointer back=nullptr;
        T data;
    public:
        SingleNode()= default;
        ~SingleNode()
        {
            if(next!=nullptr)
            {
                
                next->~SingleNode(); 
            }
            delete next;
        }
        SingleNode(T data): data(data){

        };
        SingleNode(T data,NodePointer next) : data(data),next(next){};
        SingleNode(&SingleNode copy_from)
        {
            data=copy_from.data;
            copyChildren(copy_from);
        }
        SingleNode(SingleNode&& move_from)
        {
           data=move_from.data;
           next=move_from.next;

           move_from.next=nullptr;
           move_from.data=0; 
        }
        SingleNode& operator=(SingleNode& copy_from)
        {
            if(this==&move_from)
            {
                return *this;
            }
            
            data=copy_from.data;
            next=copy_from.next;
            copyChildren(copy_from); 

            return *this;
        }
        SingleNode& operator=(SingleNode&& move_from)
        {
            if(this==&move_from){
                return *this;
            }
            
            data=move_from.data;
            next=move_from.next;

            move_from.data=0;
            move_from.next=nullptr;
            
            return *this;
        }
        public:

        void copyChildren(SingleNode& copy_from)
        {
            
            next=copy_from.getNext(); 
            if(copy_from.getNext()!=nullptr)
            {
                NodePointer current=this;
                for(Iterator it=copy_from.begin(); it!=copy_from.end();it++) 
                {
                    current->setNext(it);
                    current=it;
                    
                }
            }
        }
        DataReference getData(){return data;}
        NodePointer getBack(){return back;}
        NodePointer getNext(){return next;}
        void setNext(NodePointer new_next){next=new_next;}
        void setBack(NodePointer new_back){back=new_back;}

        public:
            Iterator begin()
            {
                return SingleNodeIterator(this);
            }
            Iterator end()
            {
                return SingleNodeIterator(nullptr);
            }
            

        void forEach(std::function<void(NodePointer&)>& func)
        {
            if(next!=nullptr)
            {
                for(auto it=this.begin();it!=this.end();it++)
                {
                    func(it->getNext());
                }
            }

            func(this);
        }



    
};
}