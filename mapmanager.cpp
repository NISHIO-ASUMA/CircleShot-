//===========================================
//
// マップマネージャー処理 [ mapmanager.cpp ]
// Author : Asuma Nishio
//
//===========================================

//***************************
// インクルードファイル
//***************************
#include "mapmanager.h"
#include "mapobject.h"
#include "modellist.h"
#include "manager.h"

//=========================
// コンストラクタ
//=========================
CMapManager::CMapManager(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_MapObj.clear();
	m_nSelectIdx = NULL;
}
//=========================
// デストラクタ
//=========================
CMapManager::~CMapManager()
{
	// 無し
}
//=========================
// 初期化
//=========================
HRESULT CMapManager::Init(void)
{
	// 初期化
	m_MapObj.clear();

	// 初期化結果を返す
	return S_OK;
}
//=========================
// 終了
//=========================
void CMapManager::Uninit(void)
{
	// 値のクリア
	m_MapObj.clear();

	// 自身の破棄
	CObject::Release();
}
//=========================
// 更新
//=========================
void CMapManager::Update(void)
{
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CMapObject* pMapObj = CMapObject::Create(VECTOR3_NULL, VECTOR3_NULL, m_nSelectIdx);

		// 配列に追加
		m_MapObj.push_back(pMapObj);
	}

}
//=========================
// 描画
//=========================
void CMapManager::Draw(void)
{
	// モデルリストから構造体を取得
	CModelList::MODELINFO Info = CModelList::GetInfo(m_nSelectIdx);

}
//=========================
// 生成処理
//=========================
CMapManager* CMapManager::Craete(D3DXVECTOR3 pos, int nIdx)
{
	// インスタンス生成
	CMapManager* pMapManager = new CMapManager;

	// nullなら
	if (pMapManager == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pMapManager->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pMapManager;
}













#if 0
// リスト取得
CModelList* pModelList = CEditManager::GetList();

// 配置したモデルのインデックスを取得
int nIdx = m_nSelectIndex;

// 範囲チェック
auto modelInfoVec = pModelList->GetInfo();

// モデル情報を取得
CModelList::MODELINFO& info = modelInfoVec[nIdx];

// 移動処理
if (CManager::GetInputKeyboard()->GetPress(DIK_A))
{// Aキーを押した

	m_pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;
	m_pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;

	// 角度の正規化
	if (m_rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_rot.y -= D3DX_PI * 2.0f;
	}
}
else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
{// Dキーを押した
	// Dキーのみ押した
	m_pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;
	m_pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;

	// 角度の正規化
	if (m_rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_rot.y -= D3DX_PI * 2.0f;
	}

}
else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
{// Wキーを押した

	m_pos.x += sinf(pCamera->GetRot().y) * 7.0f;
	m_pos.z += cosf(pCamera->GetRot().y) * 7.0f;

	// 角度を正規化
	if (m_rot.y < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		m_rot.y += D3DX_PI * 2.0f;
	}

}
else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
{// Sキーを押した

	m_pos.x -= sinf(pCamera->GetRot().y) * 7.0f;
	m_pos.z -= cosf(pCamera->GetRot().y) * 7.0f;

	// 角度の正規化
	if (m_rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_rot.y -= D3DX_PI * 2.0f;
	}
	}
#endif
