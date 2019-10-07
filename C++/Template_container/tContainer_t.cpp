#pragma once


template <class T, class C>
class tContainer_t
{
    public:
        ~tContainer_t();
        tContainer_t();

        bool isEmpty() const;
        size_t getSize() const;
        void pushBack(const T& t);
        

    private:
        tContainer_t(const tContainer_t& c);
        tContainer_t& operator=(const tContainer_t& c);

        C container;

};