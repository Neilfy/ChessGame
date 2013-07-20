#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Define.h"
#include "cocos2d.h"
USING_NS_CC;
class ChessBoard;
class GameRuler;
class GameManager{
public: 
	GameManager();
	~GameManager();

	cocos2d::CCScene* GetGameScene();
	void NotifyForBoardClicked(const CCPoint& position);
private:
	BOARDNODEIDX ConvertPosToIdx(const CCPoint& position);
	
private:
	cocos2d::CCScene *m_pGameScene;
	ChessBoard *m_pBoardLayer;
	GameRuler *m_pGameRuler;

};
#endif