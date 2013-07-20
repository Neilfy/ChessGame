#ifndef DEFINE_H
#define DEFINE_H

#include "cocos2d.h"
USING_NS_CC;

enum ACTION
{
	ADD,//ÂäÆå
	EATE,//³ÔÆå
	MOVE//×ßÆå
};
enum PLAYER {
	BLACK = 1,
	WHITE
};
struct CHESS 
{
	PLAYER pers;
	CCSize size;
	CCSprite* pSprite;

	CHESS()
		:pers(BLACK)
		,size(60,60)
		,pSprite(NULL)
	{

	}
};
struct BOARDNODE
{
	CCRect nodeRec;
	CHESS* chess;

	BOARDNODE()
		:nodeRec(0.f,0.f,60.f,60.f)
		,chess(NULL)
	{

	}
};

enum BOARDNODEIDX
{
	NODE_1,
	NODE_2,
	NODE_3,
	NODE_4,
	NODE_5,
	NODE_6,
	NODE_7,
	NODE_8,
	NODE_9,
	NODE_10,
	NODE_11,
	NODE_12,
	NODE_13,
	NODE_14,
	NODE_15,
	NODE_16,
	NODE_17,
	NODE_18,
	NODE_19,
	NODE_20,
	NODE_21,
	NODE_22,
	NODE_23,
	NODE_24,
	NODE_25,
	NODE_NUM,
	NODE_ERROR
};

#endif