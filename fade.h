//=====================================
//
// フェード処理 [ fade.h ]
// Author: Asuma Nishio
// 
//=====================================

#ifndef _FADE_H_ // このマクロ定義がされてなかったら
#define _FADE_H_ // 2重インクルード防止のマクロ定義

//**********************
// 前方宣言
//**********************
class CScene;

//**********************
// フェードクラスを定義
//**********************
class CFade
{
public:

	//**********************
	// フェード状態列挙型
	//**********************
	enum FADE
	{
		FADE_NONE,	// 何もない
		FADE_IN,	// フェードイン
		FADE_OUT,	// フェードアウト
		FADE_MAX
	};

	// コンストラクタ・デストラクタ
	CFade();
	~CFade();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetFade(CScene * pNewScene);

	// ゲッター
	FADE GetFade(void) { return m_fade; }

private:

	static constexpr float AlphaFade = 0.025f; // フェードで加算する値

	LPDIRECT3DVERTEXBUFFER9 m_pVtx; // 頂点バッファ
	D3DXCOLOR m_col;				// ポリゴンカラー
	FADE m_fade;					// フェードの列挙型変数
	CScene* m_pScene;				// シーンクラスのポインタ
};

#endif