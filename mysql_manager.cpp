//
// Created by yuchen on 17/4/26.
//

#include "mysql_manager.h"
#include <cstdlib>

bool mysql_manager::init(
        size_t size,
        size_t max_size,
        const char *host,
        const char *user,
        const char *passwd,
        const char *db,
        unsigned int port,
        const char *unix_socket,
        unsigned long clientflag
)
{
    m_cur_size    = 0;
    m_def_size    = size;
    m_max_size    = max_size;
    m_host        = host;
    m_user        = user;
    m_passwd      = passwd;
    m_db          = db;
    m_port        = port;
    m_unix_socket = unix_socket;
    m_clientflag  = clientflag;

    while (m_cur_size < m_def_size)
    {
        auto ptr = create_connection();
        if (!ptr)
        {
            return false;
        }
        m_list.push_back(ptr);
    }

    return true;

}
std::shared_ptr<MYSQL> mysql_manager::get_connection()
{

    if(!m_list.empty())
    {
        auto ptr = m_list.front();
        m_list.pop_front();
        return create_shared_ptr(ptr);
    }else
    {
        if(m_cur_size < m_max_size)
        {
            return create_shared_ptr(create_connection());
        }else
        {
            return create_shared_ptr(nullptr);
        }
    }
}

void mysql_manager::release_connection(MYSQL* ptr)
{
    if(ptr)
    {
        m_list.push_back(ptr);
    }
}

MYSQL* mysql_manager::create_connection()
{
    MYSQL *ptr = static_cast<MYSQL *>(malloc(sizeof(MYSQL)));
    mysql_init(ptr);
    if (mysql_real_connect(ptr, m_host, m_user, m_passwd, m_db, m_port, m_unix_socket, m_clientflag))
    {
        ++m_cur_size;
        return ptr;
    }
    else
    {
        free(ptr);
        return nullptr;
    }


}

std::shared_ptr<MYSQL> mysql_manager::create_shared_ptr(MYSQL *ptr)
{
    std::shared_ptr<MYSQL>sptr(ptr,
     [](MYSQL *p)
    {
        mysql_manager::getInstance().release_connection(p);
    });
    return sptr;
}