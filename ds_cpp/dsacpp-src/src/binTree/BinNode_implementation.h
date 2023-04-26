/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2021. All rights reserved.
 ******************************************************************************************/

#pragma once

/******************************************************************************************
 * 将BinNode各方法的实现部分，简洁地引入BinNode.h
 * 效果等同于将这些实现直接汇入BinNode.h
 * 在export尚未被编译器支持前，如此可将定义与实现分离，以便课程讲解
 ******************************************************************************************/
#include "BinNode_macro.h"
#include "BinNode_succ.h" //取节点后继
#include "BinNode_zig.h" //顺时针旋转
#include "BinNode_zag.h" //逆时针旋转
#include "BinNode_stretchByZig.h"
#include "BinNode_stretchByZag.h"