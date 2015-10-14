//
//  NetManager.h
//  ClickServer
//
//  Created by qianmengxi on 15-10-14.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#ifndef __ClickServer__NetManager__
#define __ClickServer__NetManager__

#include <stdio.h>

class NetManager
{
public:
    static NetManager* getInstance();
    bool start();
};

#endif /* defined(__ClickServer__NetManager__) */
