#include "ChessBoard.h"
#include "GameManager.h"
USING_NS_CC;


ChessBoard::ChessBoard(GameManager* gameManager)
:m_pGameManager(gameManager)
{
	//初始化棋盘节点位置
	int NodeSize = 60;
	float hafSize = NodeSize/2.f;
	m_ChessNodes[0].nodeRec = CCRectMake(10-hafSize, 10-hafSize, NodeSize, NodeSize);
	m_ChessNodes[1].nodeRec = CCRectMake(110-hafSize, 10-hafSize, NodeSize, NodeSize);
	m_ChessNodes[2].nodeRec = CCRectMake(210-hafSize, 10-hafSize, NodeSize, NodeSize);
	m_ChessNodes[3].nodeRec = CCRectMake(310-hafSize, 10-hafSize, NodeSize, NodeSize);
	m_ChessNodes[4].nodeRec = CCRectMake(410-hafSize, 10-hafSize, NodeSize, NodeSize);

	m_ChessNodes[5].nodeRec = CCRectMake(10-hafSize, 110-hafSize, NodeSize, NodeSize);
	m_ChessNodes[6].nodeRec = CCRectMake(110-hafSize, 110-hafSize, NodeSize, NodeSize);
	m_ChessNodes[7].nodeRec = CCRectMake(210-hafSize, 110-hafSize, NodeSize, NodeSize);
	m_ChessNodes[8].nodeRec = CCRectMake(310-hafSize, 110-hafSize, NodeSize, NodeSize);
	m_ChessNodes[9].nodeRec = CCRectMake(410-hafSize, 110-hafSize, NodeSize, NodeSize);

	m_ChessNodes[10].nodeRec = CCRectMake(10-hafSize, 210-hafSize, NodeSize, NodeSize);
	m_ChessNodes[11].nodeRec = CCRectMake(110-hafSize, 210-hafSize, NodeSize, NodeSize);
	m_ChessNodes[12].nodeRec = CCRectMake(210-hafSize, 210-hafSize, NodeSize, NodeSize);
	m_ChessNodes[13].nodeRec = CCRectMake(310-hafSize, 210-hafSize, NodeSize, NodeSize);
	m_ChessNodes[14].nodeRec = CCRectMake(410-hafSize, 210-hafSize, NodeSize, NodeSize);

	m_ChessNodes[15].nodeRec = CCRectMake(10-hafSize, 310-hafSize, NodeSize, NodeSize);
	m_ChessNodes[16].nodeRec = CCRectMake(110-hafSize, 310-hafSize, NodeSize, NodeSize);
	m_ChessNodes[17].nodeRec = CCRectMake(210-hafSize, 310-hafSize, NodeSize, NodeSize);
	m_ChessNodes[18].nodeRec = CCRectMake(310-hafSize, 310-hafSize, NodeSize, NodeSize);
	m_ChessNodes[19].nodeRec = CCRectMake(410-hafSize, 310-hafSize, NodeSize, NodeSize);

	m_ChessNodes[20].nodeRec = CCRectMake(10-hafSize, 410-hafSize, NodeSize, NodeSize);
	m_ChessNodes[21].nodeRec = CCRectMake(110-hafSize, 410-hafSize, NodeSize, NodeSize);
	m_ChessNodes[22].nodeRec = CCRectMake(210-hafSize, 410-hafSize, NodeSize, NodeSize);
	m_ChessNodes[23].nodeRec = CCRectMake(310-hafSize, 410-hafSize, NodeSize, NodeSize);
	m_ChessNodes[24].nodeRec = CCRectMake(410-hafSize, 410-hafSize, NodeSize, NodeSize);

	setIsTouchEnabled(true);
}

ChessBoard::~ChessBoard()
{
	for (int i=0; i<NODE_NUM; ++i)
	{
		if (m_ChessNodes[i].chess)
		{
			delete m_ChessNodes[i].chess;
		}
	}
}

void ChessBoard::addChess(BOARDNODEIDX idx, PLAYER pers)
{
	CCAssert(!m_ChessNodes[idx].chess,"chess exist!");

	CHESS* chess = new CHESS();
	chess->pers = pers;
	switch(pers)
	{
	case BLACK:
		chess->pSprite = CCSprite::spriteWithFile("Chess_black.png");
		break;
	case WHITE:
		chess->pSprite = CCSprite::spriteWithFile("Chess_white.png");
		break;
	}
	chess->pSprite->setScale(0.5);
	chess->pSprite->setPosition( ccp(CCRect::CCRectGetMidX(m_ChessNodes[idx].nodeRec)
		,CCRect::CCRectGetMidY(m_ChessNodes[idx].nodeRec)) );
	this->addChild(chess->pSprite);
	
	m_ChessNodes[idx].chess = chess;
	//m_Chesses[idx].
}

void ChessBoard::delChess(BOARDNODEIDX idx)
{
	CCAssert(m_ChessNodes[idx].chess,"chess isn't exist!");
	this->removeChild(m_ChessNodes[idx].chess->pSprite,true);
	delete m_ChessNodes[idx].chess;
	m_ChessNodes[idx].chess = NULL;
}

BOARDNODE* ChessBoard::getChessNodes()
{
	return m_ChessNodes;
}

void ChessBoard::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint location = touch->locationInView( touch->view() );
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

	m_pGameManager->NotifyForBoardClicked(convertedLocation);
}