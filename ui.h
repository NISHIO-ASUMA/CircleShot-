//====================================
//
// UI処理 [ ui.h ]
// Author: Asuma Nishio
//
//=====================================
#ifndef _UI_H_ // このマクロ定義がされてなかったら
#define _UI_H_ // 2重インクルード防止のマクロ定義

//****************************
// インクルードファイル宣言
//****************************
#include "object2D.h"

//****************************
// UIクラスを定義
//****************************
class CUi : public CObject2D
{
public:

	//***************************
	// UIの種類定義
	//***************************
	enum UITYPE
	{
		UITYPE_NONE,
		UITYPE_MOVE,
		UITYPE_MAX
	};

	CUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * Filename,int nAnchorType);

	void SetTexture(const char * pRegistername);

private:
	int m_nTexIdxType;		// テクスチャインデックス
	int m_type;
};

#endif