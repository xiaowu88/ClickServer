//
//  MySqlConnetor.h
//  ClickServer
//
//  Created by qianmengxi on 15-10-8.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#ifndef __ClickServer__MySqlConnetor__
#define __ClickServer__MySqlConnetor__

#include <stdio.h>

class DBConnector
{
public:
    static DBConnector* getInstance();
    bool connect();
};

#endif /* defined(__ClickServer__MySqlConnetor__) */
