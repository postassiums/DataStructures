#include <cstddef>
#include <cstring>
#pragma once
namespace IG{

    class StringIterator{
        public:
        using PointerToChar=char*;
        using ReferenceToChar=char&;

        StringIterator(PointerToChar ptr);
        StringIterator& operator++();
        StringIterator operator++(int);

        StringIterator& operator--();
        StringIterator operator--(int);

        PointerToChar operator->();
        ReferenceToChar operator*();

        ReferenceToChar operator[](size_t index);

        bool operator==(StringIterator& other);
        bool operator!=(StringIterator& other);

        private:
            PointerToChar pointer=nullptr;

    };
}

