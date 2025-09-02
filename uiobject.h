//===============================================
//
// UIエディターオブジェクト [ uiobject.h ]
// Author : Asuma Nishio
// 
// TODO : 家で作業する
//
//===============================================

#ifndef _UIOBJECT_H_ // このマクロ定義がされてなかったら
#define _UIOBJECT_H_ // 2重インクルード防止のマクロ定義

//**********************************
// インクルードファイル
//**********************************
#include "object2D.h"

//**********************************
// UIオブジェクトクラスを定義
//**********************************
class CUiObject : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CUiObject(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUiObject();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	D3DXVECTOR3 SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	// ゲッター
	D3DXVECTOR3 GetPos() const { return m_pos; }
	D3DXVECTOR3 GetRot() const { return m_rot; }
	int GetIdx() const { return m_nIdx; }

	// 静的メンバ関数
	static CUiObject* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth,float fHeight,int nIdx);

private:
	int m_nIdx;			// インデックス
	float m_fWidth;		// 横幅
	float m_fHeight;	// 高さ
	D3DXVECTOR3 m_pos;	// 座標
	D3DXVECTOR3 m_rot;	// 角度
};

#endif
