#include "virtIO_t.h"

VirtIO_t::VirtIO_t()
{
    m_status = ok_e;
    m_fp = 0;
}

VirtIO_t::VirtIO_t(const string& name, const string& access)
{
    m_name = name;
    m_access = access;
    m_status = ok_e;
    m_fp = 0;
}

void VirtIO_t::open()
{
    if(m_access == "r" || m_access == "r+" || m_access == "w" || m_access == "w+")
    {
        m_fp = fopen(m_name.c_str(), m_access.c_str());
        if(!m_fp)
        {
            m_status = cant_open_file_e;
            throw string("Can't open file");
        }
    }
    else
    {
        m_status = bad_access_e;
        throw string("Bad access");
    }    
}

void VirtIO_t::close()
{
    if(m_fp)
    {
        fclose(m_fp);
        m_fp = 0;
    }
}

 size_t VirtIO_t::getPosition() const
 {
    size_t position = 0;
    if(m_fp)
    {        
        position = ftell(m_fp);
    }
 }

size_t VirtIO_t::getFileLenght() const
{
    size_t lenght = 0, currPosition = ftell(m_fp);

    if(m_fp)
    {
        fseek(m_fp, 0, SEEK_END);
        lenght = ftell(m_fp);
        fseek(m_fp, currPosition, SEEK_SET);
    }
    return lenght;
}

void VirtIO_t::setPosition(size_t position)
{
    if(m_fp)
    {
        fseek(m_fp, position, SEEK_SET);
    }
}

bool VirtIO_t::validRead()
{
    return (!m_fp || (m_access != "r" && m_access != "r+" && m_access != "w+")) ? false : true;
}

bool VirtIO_t::validWrite()
{
    return (!m_fp || (m_access != "w" && m_access != "w+" && m_access != "r+")) ? false : true;
}