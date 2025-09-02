//=========================================================
//
// UIエディターオブジェクト管理処理 [ uiobjectmanager.cpp ]
// Author : Asuma Nishio
// 
// TODO : 家で作業する
//
//=========================================================

//**********************************
// インクルードファイル
//**********************************
#include "uiobjectmanager.h"
#include "uiobject.h"

//=====================================
// コンストラクタ
//=====================================
CUiObjectManager::CUiObjectManager(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_UiObj.clear();
}
//=====================================
// デストラクタ
//=====================================
CUiObjectManager::~CUiObjectManager()
{
	// 無し
}
//=====================================
// 初期化処理
//=====================================
HRESULT CUiObjectManager::Init(void)
{
	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CUiObjectManager::Uninit(void)
{
	// 値のクリア
	m_UiObj.clear();

	// 自身の破棄
	CObject::Release();
}
//=====================================
// 更新処理
//=====================================
void CUiObjectManager::Update(void)
{

}
//=====================================
// 描画処理
//=====================================
void CUiObjectManager::Draw(void)
{

}
//=====================================
// 生成処理
//=====================================
CUiObjectManager* CUiObjectManager::Craete(void)
{
	// インスタンス生成
	CUiObjectManager* pUiObj = new CUiObjectManager;

	// nnullチェック
	if (pUiObj == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pUiObj->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタ
	return pUiObj;
}
