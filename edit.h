//========================================
//
// エディターシーン処理 [ edit.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _EDIT_H_ // このマクロ定義がされてなかったら
#define _EDIT_H_ // 2重インクルード防止のマクロ定義

//**********************************
// インクルードファイル
//**********************************
#include "scene.h"

//**********************************
// 前方宣言
//**********************************
class CEditManager;

//**********************************
// エディターシーンクラスを定義
//**********************************
class CEdit : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CEdit();
	~CEdit();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEdit* Create(void);

private:
	CEditManager* m_pEditManager; // マネージャークラスポインタ

};

#endif
