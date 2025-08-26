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

//================================
// オーバーロードコンストラクタ
//================================
CRubble::CRubble(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
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
	// 一時保留
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
