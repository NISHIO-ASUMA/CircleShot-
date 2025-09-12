//==================================
//
// 円形メッシュ処理 [ meshcircle.h ]
// Author: Asuma Nishio
//
//==================================

#ifndef _MESHCIRCLE_H_ // このマクロ定義がされてなかったら
#define _MESHCIRCLE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**************************
// 円形メッシュクラス定義
//**************************
class CMeshCircle : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CMeshCircle(int nPriority = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshCircle();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CMeshCircle* Create(D3DXVECTOR3 pos);

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
	int m_nLife;			// 寿命
	float m_fRadius;		// 半径
};

#endif