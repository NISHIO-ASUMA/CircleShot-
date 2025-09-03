//====================================
//
// マネージャー処理 [ manager.h ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// 二重インクルードガード
//**************************
#ifndef _MANAGER_H_ 
#define _MANAGER_H_ 

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
	static CRenderer* GetRenderer(void);
	static CInputKeyboard* GetInputKeyboard(void);
	static CJoyPad* GetJoyPad(void);
	static CSound* GetSound(void);
	static CInputMouse* GetMouse(void);
	static CTexture* GetTexture(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);

	static void SetScene(CScene * pNewScene);
	static CScene::MODE GetScene(void);
	static CScene* Getscene(void) { return m_pScene; }
	static CFade* GetFade(void);

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
};
#endif