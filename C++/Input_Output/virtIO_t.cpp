#include "virtIO_t.h"

VirtIO_t::VirtIO_t()
{
    m_name = "";
    m_access = "";
    m_position = 0;
    m_status = ok_e;
    m_fp = 0;
}

VirtIO_t::VirtIO_t(const string& name, const string& access)
{
    m_name = name;
    m_access = access;
    m_position = 0;
    m_status = ok_e;
    m_fp = 0;
}

void VirtIO_t::open()
{
    if()
    {

    }
}

void VirtIO_t::close()
{

}

size_t VirtIO_t::getFileLenght() const
{
    size_t lenght = 0;
    if(m_fp)
    {
        fseek(m_fp, 0, SEEK_END);
        lenght = ftell(m_fp);
        setPosition(m_position);
    }
    return lenght;
}

void VirtIO_t::setPosition(size_t position)
{
    if(m_fp)
    {
        fseek(m_fp, position, SEEK_SET);
        m_position = position;
    }
}

bool VirtIO_t::validRead()
{
    bool isValid = true;
    if(!m_fp || m_access != "r" || m_access != "r+")
    {
        m_status = readErr_e;
        isValid = false;
    }
    return isValid;
}

bool VirtIO_t::validWrite()
{
    bool isValid = true;
    if(!m_fp || m_access != "w" || m_access != "w+")
    {
        m_status = writeErr_e;
        isValid = false;
    }
    return isValid;
}