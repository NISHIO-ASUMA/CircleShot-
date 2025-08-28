//====================================
//
// モデル処理 [ model.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MODEL_H_ // このマクロ定義がされてなかったら
#define _MODEL_H_ // 2重インクルード防止のマクロ定義

//**********************
// モデルクラスの定義
//**********************
class CModel
{
public:
	//*********************
	// パーツのタイプ列挙型
	//********************
	enum PARTTYPE
	{
		PARTTYPE_NONE, // 何も種類を設定しない時
		PARTTYPE_HEAD, // 頭
		PARTTYPE_CHEST, // 体
		PARTTYPE_LEFT_HAND, // 左腕
		PARTTYPE_RIGHT_HAND,// 右腕
		PARTTYPE_LEFT_LEG, //左足
		PARTTYPE_RIGHT_LEG,// 右足
		PARTTYPE_WEAPON,   // 武器
		PARTTYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CModel();
	~CModel();

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetParent(CModel* pModel);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void OffSetPos(D3DXVECTOR3 offpos) { m_offPos = offpos; }
	void OffSetRot(D3DXVECTOR3 offrot) { m_offRot = offrot; }
	void SetPartType(PARTTYPE nDestPartType) { m_parttype = nDestPartType; }

	// ゲッター
	D3DXMATRIX GetMtxWorld(void) { return m_mtxworld; }
	PARTTYPE GetPartType(void) const { return m_parttype; }

	// フラグメント
	bool IsPlayer() const { return m_isPlayer; }
	bool IsBoss() const { return m_isBoss; }
	void SetIsBoss(bool flag) { m_isBoss = flag; }
	void SetIsPlayer(bool flag) { m_isPlayer = flag; }

	// 静的メンバ関数
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:

	D3DXVECTOR3 m_pos, m_rot,m_offPos,m_offRot; // 座標,角度

	D3DXMATRIX m_mtxworld;	  // ワールドマトリックス
	CModel* m_pParent;		  // 親モデル

	LPD3DXMESH m_pMesh;	   // メッシュ情報
	LPD3DXBUFFER m_pBuffMat; // マテリアル情報
	DWORD m_dwNumMat;		// マテリアル数
	int* m_pTexture;		// テクスチャポインタ

	PARTTYPE m_parttype;    // モデルの種類

	bool m_isPlayer; // プレイヤーに対応したモデルかどうか
	bool m_isBoss;
};

#endif