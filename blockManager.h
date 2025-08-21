//=============================================
//
// ブロック全体の管理を行う [ blockmanager.h ]
// Author: Asuma Nishio
// 
// TODO : 描画いらない
// 
//==============================================

#ifndef _BLOCKMANAGER_H_ // このマクロ定義がされてなかったら
#define _BLOCKMANAGER_H_ // 2重インクルード防止のマクロ定義
 
//*******************************
// インクルードファイル宣言
//*******************************
#include "objectX.h"
#include "block.h"
#include <vector>

//********************************
// ブロックマネージャークラス定義
//********************************
class CBlockManager
{
public:
	CBlockManager();
	~CBlockManager();

	HRESULT Init(const char * filename , D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);

	static CBlock* Create(const char* pfileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot,float Size);

private:
	static std::vector<CBlock*> m_blocks; // 配列
	static int m_nIdxCount;	// モデルインデックス番号

};

#endif // !_BLOCKMANAGER_H_


