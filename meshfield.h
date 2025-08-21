//============================================
//
// メッシュフィールド処理 [ meshfield.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _MESHFIELD_H_ // このマクロ定義がされてなかったら
#define _MESHFIELD_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************************
// メッシュフィールドクラスを定義
//**********************************
class CMeshField : public CObject
{
public:
	CMeshField(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshField();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField* Create(D3DXVECTOR3 pos, float fRadius);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetTexture(void);

private:
	LPDIRECT3DINDEXBUFFER9 m_pIdx; // インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// 頂点バッファ

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	float m_fRadius;

	int m_nNumPrimitive;	// プリミティブ数
	int m_nNumIdx;			// インデックス数
	int m_nNumAllVtx;		// 全体頂点数

	int m_nTexIdx;
};
#endif
