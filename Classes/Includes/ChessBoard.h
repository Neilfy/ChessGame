#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Define.h"
class GameManager;
class ChessBoard : public cocos2d::CCLayer
{
public:
	ChessBoard(GameManager* gameManager);
	virtual ~ChessBoard();
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void addChess(BOARDNODEIDX idx, PLAYER pers);
	void delChess(BOARDNODEIDX idx);

	BOARDNODE* getChessNodes();

private:
	BOARDNODE m_ChessNodes[NODE_NUM];
	GameManager* m_pGameManager;
};
#endif