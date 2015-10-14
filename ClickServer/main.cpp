//
//  main.cpp
//  ClickServer
//
//  Created by qianmengxi on 15-10-8.
//  Copyright (c) 2015年 qianmengxi. All rights reserved.
//

#include <iostream>
#include "NetManager.h"

int main(int argc, const char * argv[]) {
    //开始监听http
    NetManager::getInstance()->start();
    
    return 0;
}
