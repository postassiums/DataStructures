#pragma once
namespace IG
{
    template <typename DynamicArray>
    class DynamicArrayIterator
    {
        public:
            using Type=typename DynamicArray::Type;
            using PointerType=Type*;
            using ReferenceType=Type&;
        private:
            PointerType pointer;
            size_t index=0;

        public:
            DynamicArrayIterator(PointerType ptr) : pointer(ptr){};


            DynamicArrayIterator operator++()
            {
                pointer++;
                index++;
                return *this;
            }
            DynamicArrayIterator operator--()
            {
                pointer++;
                index--;
                return *this;
            }
            DynamicArrayIterator& operator++(int)
            {
                DynamicArrayIterator save=*this;
                index++;
                pointer++;
                return save;
            }
            DynamicArrayIterator& operator--(int)
            {

                DynamicArrayIterator save=*this;
                index--;
                pointer--;
                return save;
            }

            ReferenceType operator*()
            {
                return *pointer;
            }
            PointerType operator->()
            {
               return pointer;
            }

            bool operator==(DynamicArrayIterator other)
            {
                return  pointer==other.pointer;
            }

            bool operator!=(DynamicArrayIterator other)
            {
                return pointer==other.pointer;
            }



    };
};
