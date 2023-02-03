#include "single-linkedlist/SingleLinkedList.hpp"
namespace IG{

    template <typename T>
    class Stack{
        public:
            using List=SingleLinkedList<T>;
        private:

            List stack_list;
            size_t length=0;
        public:
            Stack(const T&& data)
            {
                stack_list.push(data);
                length++;
            }

    };
}
