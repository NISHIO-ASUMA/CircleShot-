//=====================================================================================
//
// UIエディターオブジェクト [ uiobject.cpp ]
// Author : Asuma Nishio
// 
// TODO : 家で作業する		ここにテクスチャファイル名,アンカータイプを追加する
// 書き出したオブジェクトはUIクラス使ってLoadする
//======================================================================================

//**********************************
// インクルードファイル
//**********************************
#include "uiobject.h"

//==============================
// コンストラクタ
//==============================
CUiObject::CUiObject(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_nIdx = -1;
}
//==============================
// デストラクタ
//==============================
CUiObject::~CUiObject()
{
	// 無し
}
//==============================
// 初期化処理
//==============================
HRESULT CUiObject::Init(void)
{
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_nIdx = -1;

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CUiObject::Uninit(void)
{
	// 自身の破棄
	CObject::Release();
}
//==============================
// 更新処理
//==============================
void CUiObject::Update(void)
{

}
//==============================
// 描画処理
//==============================
void CUiObject::Draw(void)
{

}
//==============================
// 生成処理
//==============================
CUiObject* CUiObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nIdx)
{
	// インスタンス生成
	CUiObject* pObj = new CUiObject;

	// nullチェック
	if (pObj == nullptr) return nullptr;

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pObj->m_pos = pos;
	pObj->m_rot = rot;
	pObj->m_fWidth = fWidth;
	pObj->m_fHeight = fHeight;
	pObj->m_nIdx = nIdx;

	// 生成されたポインタ
	return pObj;
}
