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
class CShadow;

//**********************************
// 瓦礫クラスを定義
//**********************************
class CRubble : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CRubble(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CRubble();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collison(D3DXVECTOR3 *DestPos);

	// 生成処理
	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:
	D3DXVECTOR3 m_Fallingspeed;	// 落下速度
	CShadow* m_pShadow;			// 影クラスポインタ
};

#endif