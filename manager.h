//====================================
//
// マネージャー処理 [ manager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MANAGER_H_ // このマクロ定義がされてなかったら
#define _MANAGER_H_ // 2重インクルード防止のマクロ定義

//**************************  
// インクルードファイル宣言
//**************************
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "bullet.h"
#include "enemymanager.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "blockManager.h"
#include "collision.h"
#include "meshcylinder.h"
#include "boss.h"
#include "scene.h"
#include "fade.h"

//**************************
// マネージャークラス宣言
//**************************
class CManager
{
public:
	// コンストラクタ・デストラクタ
	CManager();
	~CManager();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CJoyPad* GetJoyPad(void) { return m_pJoyPad; }
	static CSound* GetSound(void) { return m_pSound; }
	static CInputMouse* GetMouse(void) { return m_pInputMouse; }
	static CTexture* GetTexture(void) { return m_pTexture; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CLight* GetLight(void) { return m_pLight; }
	static CCollision* GetCollision(void) { return m_pCollision; }
	static CScene* Getscene(void) { return m_pScene; }
	static CFade* GetFade(void) { return m_pFade; }

	static void SetScene(CScene * pNewScene);
	static CScene::MODE GetScene(void);

private:
	static CRenderer* m_pRenderer;			// レンダラークラスのポインタ
	static CInputKeyboard* m_pInputKeyboard;// キーボードクラスのポインタ
	static CJoyPad* m_pJoyPad;				// ジョイパッドクラスのポインタ
	static CSound* m_pSound;				// サウンドオブジェクトのポインタ
	static CInputMouse* m_pInputMouse;		// マウスクラスのポインタ
	static CTexture* m_pTexture;			// テクスチャクラスのポインタ
	static CCamera* m_pCamera;				// カメラクラスのポインタ
	static CLight* m_pLight;				// ライトクラスのポインタ
	static CScene* m_pScene;				// シーン管理クラスのポインタ
	static CFade* m_pFade;					// フェードクラスのポインタ
	static CCollision* m_pCollision;		// コリジョンクラスへのポインタ
};
#endif