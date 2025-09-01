//================================================
//
// マップに出すオブジェクト処理 [ mapobject.h ]
// Author: Asuma Nishio
//
//================================================

#ifndef _MAPOBJECT_H_ // このマクロ定義がされてなかったら
#define _MAPOBJECT_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル
//******************************
#include "object.h"

//*********************************
// マップオブジェクトクラスを定義
//*********************************
class CMapObject : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CMapObject(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CMapObject();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	D3DXVECTOR3 SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxworld; }

	// ゲッター
	D3DXVECTOR3 GetPos() const { return m_pos; }
	D3DXVECTOR3 GetRot() const { return m_rot; }
	int GetIdx() const { return m_nIdx; }

	// 静的メンバ関数
	static CMapObject* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx);

private:
	int m_nIdx; // インデックス
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;
};

#endif