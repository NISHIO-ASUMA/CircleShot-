//=============================================
//
// メッシュシリンダー処理 [ meshcylinder.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _MESHCYLINDER_H_ // このマクロ定義がされてなかったら
#define _MESHCYLINDER_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************************
// メッシュシリンダークラスを定義
//**********************************
class CMeshCylinder : public CObject
{
public:
	CMeshCylinder(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshCylinder();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(void);

	static CMeshCylinder* Create(D3DXVECTOR3 pos, float fRadius);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetRadius(void) const { return m_fRadius; }

	static inline constexpr int DIGIT_X = 30;
	static inline constexpr int DIGIT_Z = 1;

private:
	int m_nTexIdx;		// テクスチャインデックス
	LPDIRECT3DINDEXBUFFER9 m_pIdx; // インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// 頂点バッファ

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 m_vtxPos[DIGIT_X]; // 判定用座標

	int m_nNumPrimitive;	// プリミティブ数
	int m_nNumIdx;			// インデックス数
	int m_nNumAllVtx;		// 全体頂点数
	int m_nNumDigitX, m_nNumDigitZ;		// 分割数
	float m_fRadius;		// 半径
};

#endif