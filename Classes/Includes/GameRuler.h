#ifndef GAMERULER_H
#define GAMERULER_H
#include "Define.h"
class ChessBoard;
class GameRuler
{
public:
	GameRuler(ChessBoard* chessBoard);
	~GameRuler();

	void doAction(BOARDNODEIDX idx);
	
private:
	void PlayerActionAdd(BOARDNODEIDX idx);
	void PlayerActionEate(BOARDNODEIDX idx);
	void PlayerActionMove(BOARDNODEIDX idx);
	bool canBeAddChess(BOARDNODEIDX idx);
	bool canBeEatChess(BOARDNODEIDX idx);
	bool isValidNode(int row,int col);
	void updateInfo(BOARDNODEIDX idx);


private:
	ChessBoard* m_pChessBoard;
	PLAYER m_curPlayer;
	ACTION m_curAction;
	int m_stepCount;
	int m_curChessCount;
	bool m_IsfirstEat;
	BOARDNODEIDX m_curActiveChess;

};

#endif