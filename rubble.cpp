//========================================
//
// 瓦礫オブジェクト処理 [ rubble.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// インクルードファイル
//**********************************
#include "rubble.h"
#include "scene.h"
#include "manager.h"

//================================
// オーバーロードコンストラクタ
//================================
CRubble::CRubble(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_Fallingspeed = VECTOR3_NULL;
}
//================================
// デストラクタ
//================================
CRubble::~CRubble()
{
	// 無し
}
//================================
// 初期化処理
//================================
HRESULT CRubble::Init(void)
{
	// 親クラス初期化処理
	CObjectX::Init();

	// オブジェクトの種類定義
	SetObjType(CObject::TYPE_BLOCK);

	// 初期値を設定
	m_Fallingspeed = { 0.0f,1.5f,0.0f };

	// 初期化結果を返す
	return S_OK;
}
//================================
// 終了処理
//================================
void CRubble::Uninit(void)
{
	// 親クラス終了処理
	CObjectX::Uninit();
}
//================================
// 更新処理
//================================
void CRubble::Update(void)
{
	// 現在シーン取得
	CScene::MODE pMode = CManager::GetScene();

	if (pMode == CScene::MODE_GAME)
	{
		// 現在の座標を取得
		D3DXVECTOR3 NowPos = GetPos();

		// 現在の座標に対して重力値を加算する
		NowPos -= m_Fallingspeed;

		// 現在座標をセットする
		SetPos(NowPos);
	}
}
//================================
// 描画処理
//================================
void CRubble::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
//================================
// 生成処理
//================================
CRubble* CRubble::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// インスタンス生成
	CRubble* pRubble = new CRubble;

	// もしnullだったら
	if (pRubble == nullptr) return nullptr;

	// オブジェクト設定
	pRubble->SetFilePass(pFilename);
	pRubble->SetPos(pos);
	pRubble->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pRubble->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pRubble;
}
