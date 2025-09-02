//===============================================
//
// UIエディターシーン管理処理 [ uieditmanager.h ]
// Author : Asuma Nishio
//
//===============================================

//*********************************
// インクルードファイル
//*********************************
#include "uieditmanager.h"

//===============================
// コンストラクタ
//===============================
CUiEditManager::CUiEditManager()
{
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nTypeIdx = NULL;
	m_mtxworld = {};

	m_nSavePassIdx = NULL;
	m_nNumAll = NULL;
}
//===============================
// デストラクタ
//===============================
CUiEditManager::~CUiEditManager()
{

}
//===============================
// 初期化
//===============================
HRESULT CUiEditManager::Init(void)
{
	return S_OK;
}
//===============================
// 終了
//===============================
void CUiEditManager::Uninit(void)
{

}
//===============================
// 更新
//===============================
void CUiEditManager::Update(void)
{

}
//===============================
// 描画
//===============================
void CUiEditManager::Draw(void)
{

}
//===============================
// 保存
//===============================
void CUiEditManager::Save(void)
{

}
