//
//  DBConnector.h
//  ClickServer
//
//  Created by qianmengxi on 15-10-14.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#ifndef __ClickServer__DBConnector__
#define __ClickServer__DBConnector__

#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DBConnector
{
public:
    static DBConnector* getInstance();
    bool connect(const std::string& ip, const std::string& username, const std::string& pwd);
    //user must delete resultSet after finish query!
    sql::ResultSet* query(const std::string& sql);
    int update(const std::string& sql);
    
private:
    DBConnector();
    
private:
    sql::Connection* m_pConnection;
};

#endif /* defined(__ClickServer__DBConnector__) */
