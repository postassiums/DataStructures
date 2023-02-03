#include "StringIterator.hh"
#pragma once

namespace IG{
class String{
    public:
        using Iterator= IG::StringIterator;
    public:
        String()=default;
        String(const char* new_string);
        ~String();
        String(String& object_to_copy);

        String(String&& object_to_move);

        String& operator=(String& string_to_copy);

        String& operator=(String&& string_to_move);

        Iterator begin();
        Iterator end();

        char& getChar(size_t index);
        char& operator[](size_t index);
        const char* getString()const;
    private:
        size_t length=0;
        char* data;
};

}
