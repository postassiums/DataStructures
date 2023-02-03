#include "SingleNode.hpp"
namespace IG{
    template <typename SingleNode>
    class SingleLinkedList
    {
        public:
            using Node=typename SingleNode::Node;
            using NodeType=typename Node::Type;
            using NodeTypeTemporary=NodeType&&;
            using Iterator=typename SingleNode::Iterator;
            using SingleNodePointer=typename SingleNode::NodePointer;
        private:
            SingleNodePointer current=nullptr;
            SingleNodePointer head=nullptr;
            size_t length=0;
        public:
            SingleLinkedList()=default;
            ~SingleLinkedList()
            {
                head->~SingleNode();

                current=nullptr;
            }
            SingleLinkedList(SingleLinkedList& other_copy)
            {
                head.copyChildren(other_copy);

            }
            SingleLinkedList(SingleLinkedList&& other_move)
            {
                head=std::move(other_move.head);

                auto lambda=[this](Iterator& item)
                {
                    current=head[item];
                };
                other_move[1].forEach(lambda);
            }
            SingleLinkedList& operator=(SingleLinkedList&& other_move)
            {
                if(other_move==&this)
                {
                    return *this;
                }
                return *this;
            }
            SingleLinkedList& operator=(SingleLinkedList& other_copy)
            {
                if(other_copy==&this)
                {
                    return *this;
                }
                head.copyChildren(other_copy);
                return *this;
            }
            public:
            template <typename... NodeType>
            void push(const NodeType&&... args)
            {

            }

            void push(const NodeType&& new_data)
            {

                SingleNodePointer new_node=new Node(std::move(new_data));
                if(head==nullptr)
                {
                    head=new_node;
                    current=head;

                }else
                {

                    current->next=new_node;
                }
                length++;
            }
            NodeType pop()
            {
                if(current==nullptr)
                {

                }

                auto last_but_one=head->begin();
                for(;last_but_one!=head->end();last_but_one++)
                {

                    if(last_but_one->getNext()==head->end())
                    {
                        break;

                    }
                }
                current=last_but_one;
                NodeType to_be_returned=last_but_one->getData();
                last_but_one->getNext()->~SingleNode();
                return to_be_returned;



            }
            void reverse()
            {

            }
            void deleteAt(const size_t index)
            {
                if(head==nullptr || index>indexizeLength())
                {
                    return;
                }
                auto lambda=[&index](Iterator& item)
                {
                    if(item[1]==index)
                    {

                        item[1]->setNext(item[2]);
                        ::operator delete(item->operator(),sizeof(SingleNode));
                        return;
                    }
                };
               this->head->forEach(lambda);

            }
            size_t indexizeLength() const {return length-1;}
            void addAt(const NodeType&& new_data,const size_t index)
            {
                SingleNodePointer new_node=new Node(std::move(new_data));
                SingleNodePointer past_in_front_node=nullptr;
                if(head==nullptr || index>indexizeLength())
                {
                    return;
                }
                if(index==indexizeLength())
                {
                    push(std::forward<NodeType>(new_data));
                }
                auto lambda=[&index](Iterator& item)
                {
                    if(item==index)
                    {
                        past_in_front_node=item->getNext();
                        item[new_node];
                        new_node[past_in_front_node];
                        return;
                    }
                };
               this->head->forEach(lambda);


            }
            void forEach(std::function<void(Iterator&)>& func)
            {
                if(head!=nullptr)
                {
                    head.forEach(func);
                }
            }
            void clear(){
                if(head!=nullptr){

                    head->~SingleNode();
                }



            }
            SingleNodePointer operator[](size_t index)
            {
                SingleNodePointer returned_node=head;
                auto lambda=[&](SingleNodePointer item)
                {

                    if(item==index)
                    {
                        return returned_node;

                    }
                    returned_node=item;
                };
                head.forEach(lambda);
            }


    };
}
