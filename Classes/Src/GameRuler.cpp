#include "GameRuler.h"
#include "ChessBoard.h"

BOARDNODEIDX RULE_3XIE_LIST[4][3]=
{
	{ NODE_3, NODE_7, NODE_11 },
	{ NODE_3, NODE_9, NODE_15 },
	{ NODE_11, NODE_17, NODE_23 },
	{ NODE_15, NODE_19, NODE_23 }
};

BOARDNODEIDX RULE_4XIE_LIST[4][4]=
{
	{ NODE_4, NODE_8, NODE_12, NODE_16 },
	{ NODE_2, NODE_8, NODE_14, NODE_20 },
	{ NODE_6, NODE_12, NODE_18, NODE_24 },
	{ NODE_10, NODE_14, NODE_18, NODE_22 }
};

BOARDNODEIDX RULE_5XIE_LIST[5][5]=
{
	{ NODE_1, NODE_7, NODE_13, NODE_19, NODE_25 },
	{ NODE_5, NODE_9, NODE_13, NODE_17, NODE_21 }
};

GameRuler::GameRuler(ChessBoard* chessBoard)
:m_pChessBoard(chessBoard)
,m_curPlayer(BLACK)
,m_curAction(ADD)
,m_stepCount(1)
,m_curChessCount(0)
,m_IsfirstEat(false)
,m_curActiveChess(NODE_ERROR)
{

}

GameRuler::~GameRuler()
{

}

void GameRuler::doAction(BOARDNODEIDX idx)
{
	switch (m_curAction)
	{
	case ADD:
		PlayerActionAdd(idx);
		break;
	case EATE:
		PlayerActionEate(idx);
		break;
	case MOVE:
		PlayerActionMove(idx);
		break;
	default:
		{
			//nothing to do
		}

	}
}

void GameRuler::updateInfo(BOARDNODEIDX idx)
{
	//=========保留以后再说========
	//根据上次落子计算是否形成三斜，四斜等。。
	//3xie
	BOARDNODE* nodes = m_pChessBoard->getChessNodes();
	int step = 0;
	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<3; ++j)
		{
			if (RULE_3XIE_LIST[i][j] == idx)
			{
				if ( nodes[RULE_3XIE_LIST[i][0]].chess && (nodes[RULE_3XIE_LIST[i][0]].chess->pers==m_curPlayer)
					&& nodes[RULE_3XIE_LIST[i][1]].chess && (nodes[RULE_3XIE_LIST[i][1]].chess->pers==m_curPlayer)
					&& nodes[RULE_3XIE_LIST[i][2]].chess && (nodes[RULE_3XIE_LIST[i][2]].chess->pers==m_curPlayer) )
				{
					step++;
				}
				break;
			}
		}
	}
	
	//4xie
	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			if (RULE_4XIE_LIST[i][j] == idx)
			{
				if ( nodes[RULE_4XIE_LIST[i][0]].chess && (nodes[RULE_4XIE_LIST[i][0]].chess->pers==m_curPlayer)
					&& nodes[RULE_4XIE_LIST[i][1]].chess && (nodes[RULE_4XIE_LIST[i][1]].chess->pers==m_curPlayer)
					&& nodes[RULE_4XIE_LIST[i][2]].chess && (nodes[RULE_4XIE_LIST[i][2]].chess->pers==m_curPlayer)
					&& nodes[RULE_4XIE_LIST[i][3]].chess && (nodes[RULE_4XIE_LIST[i][3]].chess->pers==m_curPlayer) )
				{
					step +=2 ;
				}
				break;
			}
		}
	}

	//5xie
	for (int i=0; i<2; ++i)
	{
		for (int j=0; j<5; ++j)
		{
			if (RULE_5XIE_LIST[i][j] == idx)
			{
				if ( nodes[RULE_5XIE_LIST[i][0]].chess && (nodes[RULE_5XIE_LIST[i][0]].chess->pers==m_curPlayer)
					&& nodes[RULE_5XIE_LIST[i][1]].chess && (nodes[RULE_5XIE_LIST[i][1]].chess->pers==m_curPlayer)
					&& nodes[RULE_5XIE_LIST[i][2]].chess && (nodes[RULE_5XIE_LIST[i][2]].chess->pers==m_curPlayer)
					&& nodes[RULE_5XIE_LIST[i][3]].chess && (nodes[RULE_5XIE_LIST[i][3]].chess->pers==m_curPlayer) 
					&& nodes[RULE_5XIE_LIST[i][4]].chess && (nodes[RULE_5XIE_LIST[i][4]].chess->pers==m_curPlayer) )
				{
					step +=3 ;
				}
				break;
			}
		}
	}

	//一边
	int row = ((int)idx)/5;
	int col = ((int)idx)%5;
	bool isOneSide = true;
	for (int i=0; i<5; ++i)
	{
		if (!(nodes[row*5+i].chess && nodes[row*5+i].chess->pers == m_curPlayer))
		{
			isOneSide = false;
			break;
		}
	}
	if (isOneSide)
	{
		step += 2;
	}

	isOneSide = true;
	for (int i=0; i<5; ++i)
	{
		if (!(nodes[i*5+col].chess && nodes[i*5+col].chess->pers == m_curPlayer))
		{
			isOneSide = false;
			break;
		}
	}
	if (isOneSide)
	{
		step += 2;
	}

	//xiaojing
	//1
	if (isValidNode(row+1,col) && isValidNode(row+1,col+1) && isValidNode(row,col+1))
	{
		if (nodes[(row+1)*5+col].chess && nodes[(row+1)*5+col].chess->pers == m_curPlayer
			&& nodes[(row+1)*5+(col+1)].chess && nodes[(row+1)*5+(col+1)].chess->pers == m_curPlayer
			&& nodes[row*5+col+1].chess && nodes[row*5+col+1].chess->pers == m_curPlayer)
		{
			step += 1;
		}
	}
	//2
	if (isValidNode(row+1,col) && isValidNode(row+1,col-1) && isValidNode(row,col-1))
	{
		if (nodes[(row+1)*5+col].chess && nodes[(row+1)*5+col].chess->pers == m_curPlayer
			&& nodes[(row+1)*5+(col-1)].chess && nodes[(row+1)*5+(col-1)].chess->pers == m_curPlayer
			&& nodes[row*5+col-1].chess && nodes[row*5+col-1].chess->pers == m_curPlayer)
		{
			step += 1;
		}
	}
	//3
	if (isValidNode(row,col-1) && isValidNode(row-1,col-1) && isValidNode(row-1,col))
	{
		if (nodes[(row)*5+col-1].chess && nodes[(row)*5+col-1].chess->pers == m_curPlayer
			&& nodes[(row-1)*5+(col-1)].chess && nodes[(row-1)*5+(col-1)].chess->pers == m_curPlayer
			&& nodes[(row-1)*5+col].chess && nodes[(row-1)*5+col].chess->pers == m_curPlayer)
		{
			step += 1;
		}
	}
	//4
	if (isValidNode(row,col+1) && isValidNode(row-1,col+1) && isValidNode(row-1,col))
	{
		if (nodes[(row)*5+col+1].chess && nodes[(row)*5+col+1].chess->pers == m_curPlayer
			&& nodes[(row-1)*5+(col+1)].chess && nodes[(row-1)*5+(col+1)].chess->pers == m_curPlayer
			&& nodes[(row-1)*5+col].chess && nodes[(row-1)*5+col].chess->pers == m_curPlayer)
		{
			step += 1;
		}
	}
	

	m_stepCount += step ;
	//======================
	
	if (m_stepCount == 0)
	{
		//change player
		if (m_curPlayer == BLACK)
		{
			m_curPlayer = WHITE;
		}else
		{
			m_curPlayer = BLACK;
		}
		m_stepCount = 1;

		//action 更新，比较麻烦 以后再写
		//m_curAction = ?;
	}
}

bool GameRuler::isValidNode(int row,int col)
{
	if (row>=0&&row<5 && col>=0&&col<5)
	{
		return true;
	}else
	{
		return false;
	}
}

void GameRuler::PlayerActionAdd(BOARDNODEIDX idx)
{
	//计算是否可以在此处落子
	bool ret = canBeAddChess(idx);
	if (ret)
	{
		m_pChessBoard->addChess(idx, m_curPlayer);
		m_curChessCount++;
		if (m_curChessCount==25)
		{
			m_curAction=EATE;
			m_stepCount = 0;
			m_curPlayer = BLACK;
			m_IsfirstEat = true;
		}else
		{
			m_stepCount--;
			updateInfo(idx);
		}
		
	}

}

void GameRuler::PlayerActionEate(BOARDNODEIDX idx)
{
	bool ret = canBeEatChess(idx);
	if (ret)
	{
		m_pChessBoard->delChess(idx);
		if (m_IsfirstEat)
		{
			m_curPlayer = WHITE;
			m_IsfirstEat = false;
		}else
		{
			m_curAction = MOVE;
		}
		
	}
}

void GameRuler::PlayerActionMove(BOARDNODEIDX idx)
{
	BOARDNODE* boardNodes = m_pChessBoard->getChessNodes();
	if (m_curActiveChess == NODE_ERROR)
	{
		if (boardNodes && boardNodes[idx].chess && boardNodes[idx].chess->pers == m_curPlayer)
		{
			m_curActiveChess = idx;
		}
	}else
	{
		if (boardNodes && !boardNodes[idx].chess)
		{
			m_pChessBoard->delChess(m_curActiveChess);
			m_pChessBoard->addChess(idx,m_curPlayer);
		}

	}
}

bool GameRuler::canBeEatChess(BOARDNODEIDX idx)
{
	BOARDNODE* boardNodes = m_pChessBoard->getChessNodes();
	if (boardNodes && boardNodes[idx].chess && boardNodes[idx].chess->pers != m_curPlayer)
	{
		return true;
	}
	return false;
}

bool GameRuler::canBeAddChess(BOARDNODEIDX idx)
{
	BOARDNODE* boardNodes = m_pChessBoard->getChessNodes();
	if (boardNodes && !boardNodes[idx].chess)
	{
		return true;
	}
	return false;
}