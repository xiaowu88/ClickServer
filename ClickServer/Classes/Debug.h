//
//  Debug.h
//  AgarServer
//
//  Created by qianmengxi on 15-5-12.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#ifndef AgarServer_Debug_h
#define AgarServer_Debug_h

#define STD_LOG 0  //控制台log
#define FILE_LOG 1  //文件log
#define NO_LOG 2   //不输出log

#define DEBUG_CHUNK 1  //调试代码段

#define AUTO_LOG(...) Log::autoLog(__VA_ARGS__)
#define ERR_LOG(...) Log::autoLog(__VA_ARGS__)
#define ERR_COND(cond, errMsg) \
if (cond) \
{ \
    ERR_LOG("%s", errMsg); \
} \



#endif
