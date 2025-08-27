//================================================
//
// エディターシーン管理処理 [ editmanager.cpp ]
// Author : Asuma Nishio
//
//================================================

//**************************
// インクルードファイル宣言
//**************************
#include "editmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "rubblemanager.h"
#include "rubble.h"
#include "editmodel.h"
#include "mapmanager.h"

//=============================
// コンストラクタ
//=============================
CEditManager::CEditManager()
{
	// 値のクリア
	m_nSelectIndex = NULL;
	m_moveSpeed = NULL;
	m_rotSpeed = NULL;

	for (int nCnt = 0; nCnt < MAX_EDITOBJ; nCnt++)
	{
		m_pRubbleObj[nCnt] = nullptr;
	}

	m_pMapManager = nullptr;
}
//=============================
// デストラクタ
//=============================
CEditManager::~CEditManager()
{
	// 無し
}
//=============================
// 初期化処理
//=============================
HRESULT CEditManager::Init(void)
{
	// メンバ変数初期化
	m_nSelectIndex = 0;
	m_moveSpeed = 1.5f;
	m_rotSpeed = 0.03f;

	// 読み込み
	CModelList::Load();

	m_pMapManager = CMapManager::Craete(VECTOR3_NULL,NULL);
	
	// 初期化結果を返す
	return S_OK;
}
//=============================
// 終了処理
//=============================
void CEditManager::Uninit(void)
{
	// 破棄
	CModelList::UnLoad();
}
//=============================
// 更新処理
//=============================
void CEditManager::Update(void)
{

}
//=============================
// 描画処理
//=============================
void CEditManager::Draw(void)
{
	// マネージャー描画
	m_pMapManager->Draw();
}
