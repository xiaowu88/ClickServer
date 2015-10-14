//
//  Log.h
//  AgarServer
//
//  Created by qianmengxi on 15-5-12.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#ifndef __AgarServer__Log__
#define __AgarServer__Log__

#include "Header.h"
#include "Debug.h"

class Log
{
public:
    static void autoLog(const char * format, ...);
    static void fileLog(const char * format, va_list args);
    static void writeFileLog(const char* filePath, ssize_t len, const unsigned char* data);
    static void deleteFileLog(const char* filePath);
    static bool isFileLargerThanLimitSize(const char* filePath, unsigned long limitBytes);
    static unsigned long getFileSize(const char* filePath);
    static void stdLog();
    static const char* getFileLogPath();
};
#endif /* defined(__AgarServer__Log__) */
