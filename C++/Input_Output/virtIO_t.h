#pragma once
#include <string>
#include <cstdio>

using namespace std;

typedef enum {ok_e, cant_open_file_e, bad_access_e, writeErr_e, readErr_e} Status;

class VirtIO_t
{
    public:
        VirtIO_t();
        VirtIO_t(const string& name, const string& access);
        virtual ~VirtIO_t() {}

        void open();
        void close();

        const string& getName() const { return m_name; }
        const string& getAccess() const { return m_access; }

        size_t getFileLenght();

        size_t getPosition() const { return m_position; }
        void setPosition(size_t position);

        Status getStatus() const { return m_status; }

        virtual VirtIO_t& operator>>(char& val) = 0;
        virtual VirtIO_t& operator<<(char val) = 0;

        /*virtual VirtIO_t& operator>>(unsigned char& val) = 0;
        virtual VirtIO_t& operator<<(unsigned char val) = 0;

        virtual VirtIO_t& operator>>(short& val) = 0;
        virtual VirtIO_t& operator<<(short val) = 0;
        
        virtual VirtIO_t& operator>>(unsigned short& val) = 0;
        virtual VirtIO_t& operator<<(unsigned short val) = 0;

        virtual VirtIO_t& operator>>(int& val) = 0;
        virtual VirtIO_t& operator<<(int val) = 0;

        virtual VirtIO_t& operator>>(unsigned int& val) = 0;
        virtual VirtIO_t& operator<<(unsigned int val) = 0;

        virtual VirtIO_t& operator>>(long& val) = 0;
        virtual VirtIO_t& operator<<(long val) = 0;

        virtual VirtIO_t& operator>>(unsigned long& val) = 0;
        virtual VirtIO_t& operator<<(unsigned long val) = 0;

        virtual VirtIO_t& operator>>(float& val) = 0;
        virtual VirtIO_t& operator<<(float val) = 0;

        virtual VirtIO_t& operator>>(double& val) = 0;
        virtual VirtIO_t& operator<<(double val) = 0;*/

    protected:
        string m_name;
        string m_access;
        size_t m_position;
        Status m_status;
        FILE* m_fp;

        void setStatus(Status status) { m_status = status; }
        bool validRead();
        bool validWrite();

    private:
        VirtIO_t(const VirtIO_t& v);
        VirtIO_t& operator=(const VirtIO_t& v);
};