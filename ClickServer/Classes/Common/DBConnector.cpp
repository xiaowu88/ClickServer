//
//  DBConnector.cpp
//  ClickServer
//
//  Created by qianmengxi on 15-10-14.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#include "DBConnector.h"

#define __TRY \
try {

#define __CATCH_SQL_EXCEPTION \
} catch(sql::SQLException &e) { \
cout << "# ERR: SQLException in " << __FILE__; \
cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl; \
cout << "# ERR: " << e.what(); \
cout << " (MySQL error code: " << e.getErrorCode(); \
cout << ", SQLState: " << e.getSQLState() <<" )" << endl; \
}

using namespace std;

static DBConnector* s_dbConnector = NULL;
DBConnector* DBConnector::getInstance()
{
    if (!s_dbConnector)
    {
        s_dbConnector = new DBConnector();
    }
    
    return s_dbConnector;
}

bool DBConnector::connect(const std::string& ip, const std::string& username, const std::string& pwd)
{
    __TRY
    sql::Driver *driver = get_driver_instance();
    m_pConnection = driver->connect(ip, username, pwd);
    //con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    
    return true;
    __CATCH_SQL_EXCEPTION
    
    return false;
}

sql::ResultSet* DBConnector::query(const std::string& sql)
{
    if (m_pConnection)
    {
        __TRY
        sql::PreparedStatement* pStmt;
        sql::ResultSet* ret;
        pStmt = m_pConnection->prepareStatement(sql);
        ret = pStmt->executeQuery();
        delete pStmt;
        return ret;
        __CATCH_SQL_EXCEPTION
    }
    
    return nullptr;
}

int DBConnector::update(const std::string& sql)
{
    if (m_pConnection)
    {
        __TRY
        int rows;
        sql::PreparedStatement* pStmt;
        pStmt = m_pConnection->prepareStatement(sql);
        rows = pStmt->executeUpdate();
        delete pStmt;
        return rows;
        __CATCH_SQL_EXCEPTION
    }
    return 0;
}

DBConnector::DBConnector()
:m_pConnection(nullptr)
{
    
}