#pragma once
#include <string>
using namespace std;

enum Gir {Standart, Automatic};

class Car_t
{
    public:
        Car_t(): id(defId++) {}
        Car_t(unsigned int c): id(defId++) {capacity = c;}
        Car_t(const Car_t& c): id(defId++);

        Car_t& operator=(const Car_t& c);
        bool operator<(const Car_t& c) const;

        string getName() const {return name;}
        Gir getGir() const {return girType;}
        unsigned int getCapacity() const {return capacity;}

        bool compare(const Car_t& c) const;

    protected:
        ~Car_t() {}

        void setName(string n) {name = n;}
        void setGir(Gir g) {girType = g;}
        void setCapacity(unsigned int c) {capacity = c;}

    private:
        unsigned int capacity;
        const unsigned int id;
        static unsigned int defId;
        string name;
        Gir girType;
};




