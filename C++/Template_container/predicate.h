#pragma once

template <class T>
class FindValue
{
    public:
        FindValue(const T& t) : val(t) {}
        bool operator()(const T* param) const {return *param == val;}
    
    private:
        T val;
};