//
// Created by yuchen on 17/4/26.
//

#ifndef MYSQL_MANAGER_MYSQL_MANAGER_H
#define MYSQL_MANAGER_MYSQL_MANAGER_H


#include <list>
#include <mysql/mysql.h>
#include <memory>

class mysql_manager
{
public:

    static mysql_manager& getInstance()
    {
        static  mysql_manager ma;
        return ma;
    }

    bool
    init(
            size_t size,
            size_t max_size,
            const char *host,
            const char *user,
            const char *passwd,
            const char *db,
            unsigned int port,
            const char *unix_socket,
            unsigned long clientflag
    );

    std::shared_ptr<MYSQL> get_connection();
    void release_connection(MYSQL* ptr);

private:
    mysql_manager(){};
    MYSQL* create_connection();
    std::shared_ptr<MYSQL>create_shared_ptr(MYSQL *ptr);




private:
    std::list<MYSQL *> m_list;

    size_t m_cur_size;
    size_t m_def_size;
    size_t m_max_size;

    const char    *m_host;
    const char    *m_user;
    const char    *m_passwd;
    const char    *m_db;
    unsigned int  m_port;
    const char    *m_unix_socket;
    unsigned long m_clientflag;
};


#endif //MYSQL_MANAGER_MYSQL_MANAGER_H
