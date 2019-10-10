#pragma once

template <class T>
class FindValue
{
    public:
        FindValue(T t) : val(t) {}
        bool operator()(T* param) const {return *param == val;}
    
    private:
        T val;
};