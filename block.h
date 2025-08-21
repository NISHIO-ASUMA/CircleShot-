//====================================
//
// ブロック処理 [ block.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BLOCK_H_ // このマクロ定義がされてなかったら
#define _BLOCK_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//************************************
// ブロッククラスを定義
//************************************
class CBlock : public CObjectX
{
public:
	CBlock(int nPriority = static_cast<int>(CObject::PRIORITY::BLOCK));
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	float GetSize(void) const { return m_size; }

	static CBlock* Create(const char* pFileName, D3DXVECTOR3 pos,D3DXVECTOR3 rot, float fSize);

private:
	float m_size; // サイズ設定用
};

#endif
