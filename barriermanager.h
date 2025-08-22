//===================================================
//
// バリアオブジェクトの管理処理 [ barriermanager.h ]
// Author : Asuma Nishio
//
//===================================================

#ifndef _BARRIERMANAGER_H_ // このマクロ定義がされてなかったら
#define _BARRIERMANAGER_H_ // 2重インクルード防止のマクロ定義

//************************************
// バリアオブジェクト管理クラスを定義
//************************************
class CBarrierManager
{
public:
	CBarrierManager();
	~CBarrierManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};

#endif