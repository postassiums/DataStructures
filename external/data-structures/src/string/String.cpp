#include "String.hh"
#include <string>

IG::String::String(const char* new_string){
    length=strlen(new_string);
    data=new char[length];
    memcpy(data,new_string,length);
}

IG::String::Iterator IG::String::begin(){
    return StringIterator(data);
}

IG::String::Iterator IG::String::end(){
    return StringIterator(data+length);
}

IG::String::~String(){
    delete [] data;
}

IG::String::String(String& object_to_copy){
    length=object_to_copy.length;
    data=new char[length];
    memcpy(data,object_to_copy.data,length);
}
IG::String::String(String&& object_to_move){
    length=object_to_move.length;
    data=new char[length];
    data=object_to_move.data;
    object_to_move.data=nullptr;
    object_to_move.length=0;
}

IG::String& IG::String::operator=(String& string_to_copy){
    if(this==&string_to_copy){
        return *this;
    }
    length=string_to_copy.length;
    data=new char[length];
    memcpy(data,string_to_copy.data,length);
    return *this;
}

IG::String& IG::String::operator=(String&& string_to_move){
    if(this==&string_to_move){
        return *this;
    }
    length=string_to_move.length;
    data=new char[length];
    data=string_to_move.data;
    string_to_move.data=nullptr;
    string_to_move.length=0;
    return *this;
}



char& IG::String::getChar(size_t index){
    return data[index];
}
char& IG::String::operator[](size_t index){
    return getChar(index);
}
const char* IG::String::getString()const {
    return data;
}
