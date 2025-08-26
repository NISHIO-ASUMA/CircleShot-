//========================================
//
// 瓦礫オブジェクト処理 [ rubble.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _RUBBLE_H_ // このマクロ定義がされてなかったら
#define _RUBBLE_H_ // 2重インクルード防止のマクロ定義

//**********************************
// インクルードファイル
//**********************************
#include "objectX.h"

//**********************************
// 前方宣言
//**********************************
class CObject;

//**********************************
// 瓦礫クラスを定義
//**********************************
class CRubble : public CObjectX
{
public:
	CRubble(int nPriority = static_cast<int>(CObject::PRIORITY::BLOCK));
	~CRubble();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:
	
};

#endif