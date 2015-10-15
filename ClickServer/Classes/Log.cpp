//
//  Log.cpp
//  AgarServer
//
//  Created by qianmengxi on 15-5-12.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#include "Log.h"
#include <sys/stat.h>
#include <stdarg.h>
#include <string>

#define MAX_FILE_LOG_BUFFER_SIZE 1024*8
#define FILE_LOG_NAME "server_log.txt"
/*
 STD_LOG 0  //控制台log
 FILE_LOG 1  //文件log
 NO_LOG 2   //不输出log
 */
#define SERVER_LOG STD_LOG

static std::string s_logFilePath("");
void Log::autoLog(const char * format, ...)
{
    va_list args;
    va_start(args, format);
#if (SERVER_LOG == FILE_LOG)
    
#elif (SERVER_LOG == STD_LOG)
    char buf[MAX_FILE_LOG_BUFFER_SIZE];
    vsnprintf(buf, MAX_FILE_LOG_BUFFER_SIZE-3, format, args);
    strcat(buf, "\n");
    
    // Linux, Mac, iOS, etc
    fprintf(stdout, "server: %s", buf);
    fflush(stdout);
#endif
    va_end(args);
}

void Log::fileLog(const char * format, va_list args)
{
    /*
    char buffer[MAX_FILE_LOG_BUFFER_SIZE];
    std::string nowTime = TimeDefault::getInstance()->getNowTime();
    nowTime += " ";
    auto timeLen = nowTime.length();
    strcpy(buffer, nowTime.c_str());
    vsnprintf(buffer+timeLen, MAX_FILE_LOG_BUFFER_SIZE-timeLen-3, format, args);
    strcat(buffer, "\n");
    
    writeFileLog(getFileLogPath(), strlen(buffer), (unsigned char*)buffer);
     */
    GAME_ASSERT(0);
}

void Log::writeFileLog(const char* filePath, ssize_t len, const unsigned char* data)
{
    //auto startTime = GlobalFunc::getCurMicroSecond();
    FILE* file = fopen(filePath, "ab");
    if (file == NULL)
    {
        GAME_ASSERT(0);
    }
    else
    {
        fwrite(data, sizeof(unsigned char), len, file);
        fflush(file);
        fclose(file);
    }
}

void Log::deleteFileLog(const char* filePath)
{
    if (remove(filePath) == 0)
    {
        //success
    }
    else
    {
        GAME_ASSERT(0);
    }
}

bool Log::isFileLargerThanLimitSize(const char* filePath, unsigned long limitBytes)
{
    auto fileSize = getFileSize(filePath);
    return fileSize > limitBytes;
}

unsigned long Log::getFileSize(const char* filePath)
{
    unsigned long fileSize = -1;
    struct stat statbuff;
    if(stat(filePath, &statbuff) < 0)
    {
        return fileSize;
    }
    else
    {
        fileSize = statbuff.st_size;
    }
    
    return fileSize;
}

const char* Log::getFileLogPath()
{
    if (s_logFilePath.length() > 0)
        return s_logFilePath.c_str();
    else
    {
        /*
        s_logFilePath = GlobalFunc::getStoragePath();
        if (s_logFilePath.back() != '/')
        {
            s_logFilePath += "/";
        }
        s_logFilePath += RESOURCE_DIR;
        s_logFilePath += "/";
        s_logFilePath += FILE_LOG_NAME;
        return s_logFilePath.c_str();
         */
        GAME_ASSERT(0);
    }
}