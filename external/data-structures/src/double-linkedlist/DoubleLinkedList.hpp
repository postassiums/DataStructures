
#include "DoubleNode.hpp"
namespace IG{
    template <typename IG::DoubleNode>
    class DoubleLinkedList
    {
        public:
            using Node=SingleNode::Node;
        private:
            Node current=nullptr;
            Node head=nullptr;
            size_t length=0;
        public:
            DoubleLinkedList()=default;
            DoubleLinkedList(SingleLinkedList& other_copy)
            {
            
            }
            DoubleLinkedList(SingleLinkedList&& other_move)
            {
                
            }
            DoubleLinkedList& operator=(SingleLinkedList&& other_move)
            {
                
            }
            DoubleLinkedList& operator=(SingleLinkedList& other_copy)
            {
                
            }
            public:

            void push(SingleNode::Type&& new_data)
            {

            }
    }
}