//
//  Tools.cpp
//  AgarServer
//
//  Created by qianmengxi on 15-5-13.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#include "Tools.h"
#include "md5/md5.h"
#include <sys/time.h>

static	void print_sig(const unsigned char *sig)
{
    const unsigned char	*sig_p;
    
    for (sig_p = sig; sig_p < sig + MD5_SIZE; sig_p++) {
        (void)printf("%02x", *sig_p);
    }
}

namespace Tools
{
    void getMD5Result(const char* toProcess, uint32_t processLen, char* buffer, uint32_t bufferLen)
    {
        unsigned char sign[MD5_SIZE];
        
        md5_t md5;
        md5_init(&md5);
        md5_process(&md5, toProcess, processLen);
        md5_finish(&md5, sign);
        md5_sig_to_string(sign, (char*)buffer, bufferLen);
    };
    
    long getCurMicroSecond()
    {
        struct timeval stCurrentTime;
        gettimeofday(&stCurrentTime, NULL);
        return stCurrentTime.tv_sec*1000000 + stCurrentTime.tv_usec; //millseconds
    }
    
    uint32_t getRandomInt(uint32_t min, uint32_t max)
    {
        return rand()%(max - min + 1) + min;
    }
    
    time_t getTimeStamp()
    {
        time_t t;
        time(&t);
        return t;
    }
}