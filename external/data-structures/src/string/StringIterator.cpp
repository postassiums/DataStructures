#include "StringIterator.hh"

IG::StringIterator::StringIterator(IG::StringIterator::PointerToChar ptr) :
    pointer(ptr)
{

}

IG::StringIterator& IG::StringIterator::operator++(){
    pointer++;
    return *this;
}

IG::StringIterator& IG::StringIterator::operator--(){
    pointer--;
    return *this;
}

IG::StringIterator IG::StringIterator::operator++(int){
    IG::StringIterator save=*this;
    ++pointer;
    return save;
}
IG::StringIterator IG::StringIterator::operator--(int){
    IG::StringIterator save=*this;
    --pointer;
    return save;
}
IG::StringIterator::PointerToChar IG::StringIterator::operator->(){
    return pointer;
}
IG::StringIterator::ReferenceToChar IG::StringIterator::operator*(){
    return *pointer;
}
bool IG::StringIterator::operator==(StringIterator& other){
    return pointer==other.pointer;
}
bool IG::StringIterator::operator!=(StringIterator& other){
    return pointer!=other.pointer;
}

IG::StringIterator::ReferenceToChar IG::StringIterator::operator[](size_t index){
    return *(pointer+index);
}


