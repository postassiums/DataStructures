#pragma once
namespace IG{

template <typename SingleNode>
class SingleNodeIterator
{
    public:
    using Pointer=SingleNode*;
    using Reference=SingleNode&;
    public:



    SingleNodeIterator(Pointer new_value=nullptr): node_pointer(new_value),index(0)
    {
    }
    SingleNodeIterator operator++()
    {
        node_pointer=node_pointer->getNext();
        return *this;
    }
    SingleNodeIterator& operator++(int)
    {
        SingleNodeIterator save=*this;
        this->operator++();
        index++;
        return save;
    }
    SingleNodeIterator operator[](size_t index)
    {
        SingleNodeIterator save=*this;
        for(size_t i=0;i<index;i++)
        {
            save++;
        }
        return save;
    }

    bool operator==(const SingleNodeIterator& other)
    {
        return node_pointer==other.node_pointer;

    }
    bool operator==(const size_t& other_index)
    {
        return index==other_index;
    }
    bool operator!=(const size_t& other_index)
    {
        return index==other_index;
    }
    bool operator!=(const SingleNodeIterator& other)
    {
        return node_pointer!=other.node_pointer;
    }

    Reference operator*()
    {
        return *node_pointer;
    }

    Pointer operator->()
    {
        return node_pointer;

    }






    private:
        Pointer node_pointer;
        size_t index;


    };
}
