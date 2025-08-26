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
#include "meshdome.h"
#include "meshfield.h"
#include "block.h"
#include "camera.h"
#include "rubblemanager.h"
#include "rubble.h"

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
	// ドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

	// フィールド生成
	CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

	// ブロック配置
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

	// メンバ変数初期化
	m_nSelectIndex = -1;
	m_moveSpeed = 1.5f;
	m_rotSpeed = 0.03f;

	// 初期化結果を返す
	return S_OK;
}
//=============================
// 終了処理
//=============================
void CEditManager::Uninit(void)
{
	// nullチェック

}
//=============================
// 更新処理
//=============================
void CEditManager::Update(void)
{
	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();



}
//=============================
// データセーブ処理
//=============================
void CEditManager::Save(void)
{

}
