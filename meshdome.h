//====================================
//
// メッシュドーム処理 [ meshdome.h ]
// Author: Asuma Nishio
//
//====================================

#ifndef _MESHDONE_H_ // このマクロ定義がされてなかったら
#define _MESHDONE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"

//**********************************
// メッシュドームクラスを定義
//**********************************
class CMeshDome : public CObject
{
public:
	CMeshDome(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshDome();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshDome* Create(D3DXVECTOR3 pos, float nRadius);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetTexture(void);
private:

	static constexpr int MeshDome_X_BLOCK = 10;		// Xブロック数
	static constexpr int MeshDome_Z_BLOCK = 10;		// Zブロック数
	static constexpr int MeshDome_VERTEX_NUM = (MeshDome_X_BLOCK + 1) * (MeshDome_Z_BLOCK + 1); // 頂点数
	static constexpr int MeshDome_INDEX_NUM = MeshDome_X_BLOCK * MeshDome_Z_BLOCK * 6;			// インデックス数
	static constexpr int MeshDome_PRIMITIVE_NUM = (MeshDome_X_BLOCK * MeshDome_Z_BLOCK * 2) + ((MeshDome_Z_BLOCK - 1) * 2); // ポリゴン数

	LPDIRECT3DINDEXBUFFER9 m_pIdx; // インデックスバッファ
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// 頂点バッファ

	D3DXVECTOR3 m_pos;		// 座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	float m_nRadius;		// 半径
	int m_nTexIdx;
};


#endif