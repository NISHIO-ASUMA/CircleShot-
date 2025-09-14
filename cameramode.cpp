//=========================================
//
// カメラ作成シーン処理 [ cameramode.h ]
// Author: Asuma Nishio
//
//=========================================

//******************************
// インクルードファイル
//******************************
#include "cameramode.h"
#include "tutorialboss.h"
#include "meshfield.h"
#include "meshdome.h"
#include "block.h"

//==============================
// オーバーロードコンストラクタ
//==============================
CCameraMode::CCameraMode() : CScene(CScene::MODE_CAMERAEDIT)
{
	// 値のクリア
}
//==============================
// デストラクタ
//==============================
CCameraMode::~CCameraMode()
{

}
//==============================
// 生成処理
//==============================
CCameraMode* CCameraMode::Create(void)
{
	// インスタンス生成
	CCameraMode* pCameraMode = new CCameraMode;
	if (pCameraMode == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pCameraMode->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pCameraMode;
}
//==============================
// 初期化処理
//==============================
HRESULT CCameraMode::Init(void)
{
	// ボス生成
	CTutorialBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f));

	// フィールド生成
	CMeshField::Create(D3DXVECTOR3(0.0f, -95.0f, 0.0f), 2000.0f);

	// 半球生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 890.0f);

	// ブロック生成
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f, 0);

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CCameraMode::Uninit(void)
{
	// 無し
}
//==============================
// 更新処理
//==============================
void CCameraMode::Update(void)
{
	// 無し
}
//==============================
// 描画処理
//==============================
void CCameraMode::Draw(void)
{
	// 無し
}