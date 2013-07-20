#include "GameManager.h"
#include "ChessBoard.h"
#include "GameRuler.h"
USING_NS_CC;
GameManager::GameManager()
:m_pGameScene(NULL)
,m_pBoardLayer(NULL)
,m_pGameRuler(NULL)
{
	m_pGameScene = CCScene::node();
	m_pBoardLayer = new ChessBoard(this);
	m_pBoardLayer->autorelease();//自动释放

	m_pGameScene->addChild(m_pBoardLayer);
	
	m_pGameRuler = new GameRuler(m_pBoardLayer);
}
GameManager::~GameManager()
{
	if (m_pGameRuler)
	{
		delete m_pGameRuler;
	}
	
}

CCScene* GameManager::GetGameScene()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = CCSprite::spriteWithFile("board.png");

	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	m_pBoardLayer->addChild(pSprite, 0);

	return m_pGameScene;
}

BOARDNODEIDX GameManager::ConvertPosToIdx(const CCPoint& position)
{
	BOARDNODEIDX idx = NODE_ERROR;
	BOARDNODE* nodes = m_pBoardLayer->getChessNodes();
	
	for (int i=0; i<NODE_NUM; ++i)
	{
		bool ret = CCRect::CCRectContainsPoint(nodes[i].nodeRec, position);
		if (ret)
		{
			idx = (BOARDNODEIDX)i;
			break;
		}
	}
	return idx;
}

void GameManager::NotifyForBoardClicked(const CCPoint& position)
{
	BOARDNODEIDX idx = ConvertPosToIdx(position);
	if (idx == NODE_ERROR)//没有点中棋盘节点
	{
		return;
	}
	
	m_pGameRuler->doAction(idx);
}
