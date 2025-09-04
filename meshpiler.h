//==================================
//
// 柱メッシュ処理 [ meshpiler.h ]
// Author: Asuma Nishio
//
//==================================

#ifndef _MESHPILER_H_ // このマクロ定義がされてなかったら
#define _MESHPILER_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"

//***************************
// 柱状メッシュクラスを定義
//***************************
class CMeshPiler : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CMeshPiler(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshPiler();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* CollisionPos);

	// セッター
	void SetTexture(void);

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	// 静的メンバ関数
	static CMeshPiler* Create(D3DXVECTOR3 pos, float fSpeed);

private:
	int m_nTexIdx;		// テクスチャインデックス

	LPDIRECT3DINDEXBUFFER9 m_pIdx; // インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// 頂点バッファ

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス

	int m_nNumPrimitive;	// プリミティブ数
	int m_nNumIdx;			// インデックス数
	int m_nNumAllVtx;		// 全体頂点数
	int m_nNumDigitX, m_nNumDigitZ;		// 分割数
	int m_nLife;
	float m_fMoveSpeed;
	float m_fNowHeight;	// 現在高さ

	int m_nLifeFrame;		 // 生存時間（フレーム数）
	int m_nActiveDelay;		// 当たり判定が有効になるまでの遅延フレーム数
};

#endif