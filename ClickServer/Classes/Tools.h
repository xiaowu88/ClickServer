//
//  Tools.h
//  AgarServer
//
//  Created by qianmengxi on 15-5-13.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#ifndef __AgarServer__Tools__
#define __AgarServer__Tools__

#include "Header.h"

namespace Tools
{
    void getMD5Result(const char* toProcess, uint32_t processLen, char* buffer, uint32_t bufferLen);
    long getCurMicroSecond();
    uint32_t getRandomInt(uint32_t min, uint32_t max);
    time_t getTimeStamp();
};
#endif /* defined(__AgarServer__Tools__) */
