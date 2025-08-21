//====================================
//
// 数字処理 [ number.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _NUMBER_H_ // このマクロ定義がされてなかったら
#define _NUMBER_H_ // 2重インクルード防止のマクロ定義

//**********************
// ナンバークラスを定義
//**********************
class CNumber
{
public:
	CNumber();
	~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, float fwidth, float fheight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetSize(float fWidth, float fHeight);
	void SetDigit(int nDigit);

private:
	static constexpr float DIGIT_VALUE = 0.1f; // テクスチャ分割数割合

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ

	D3DXVECTOR3 m_pos;				// 座標情報
	float m_fWidth, m_fHeight;		// 横幅,高さ
	float m_TexU, m_TexU1,m_TexV;	// テクスチャ座標
};

#endif