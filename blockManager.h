//==============================================
//
// ブロック全体の管理を行う [ blockmanager.h ]
// Author: Asuma Nishio
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
	// コンストラクタ・デストラクタ
	CBlockManager();
	~CBlockManager();

	// メンバ関数
	HRESULT Init(const char * filename , D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);

	// 静的メンバ関数
	static CBlock* Create(const char* pfileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot,float Size);

private:
	static std::vector<CBlock*> m_blocks; // 配列
	static int m_nIdxCount;	// モデルインデックス番号

};

#endif // !_BLOCKMANAGER_H_


