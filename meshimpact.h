//=============================================
//
// メッシュインパクト処理 [ meshimpact.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _MESHIMPACT_H_ // このマクロ定義がされてなかったら
#define _MESHIMPACT_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************
// 衝撃波のクラス定義
//**********************
class CMeshImpact : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CMeshImpact(int nPriority = static_cast<int>(CObject::PRIORITY::IMPACT));
	~CMeshImpact();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* pPos);

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	// 静的メンバ関数
	static CMeshImpact* Create(D3DXVECTOR3 pos, int nLife, float fRadius, float fInRadius,float fSpeed);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DINDEXBUFFER9 m_pIdx;
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;

	float m_fInRadius;
	float m_fOutRadius;
	int m_nLife;
	float m_fSpeed;
};

#endif