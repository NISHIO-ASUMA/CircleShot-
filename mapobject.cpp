//================================================
//
// マップに出すオブジェクト処理 [ mapobject.cpp ]
// Author: Asuma Nishio
//
//================================================

//******************************
// インクルードファイル
//******************************
#include "mapobject.h"
#include "manager.h"
#include "modellist.h"
#include "editmanager.h"

//=========================
// コンストラクタ
//=========================
CMapObject::CMapObject(int nPriority) : CObject(nPriority)
{
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxworld = {};
	m_nIdx = NULL;
}
//=========================
// デストラクタ
//=========================
CMapObject::~CMapObject()
{
	// 無し
}
//=========================
// 生成
//=========================
CMapObject* CMapObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx)
{
	// インスタンス生成
	CMapObject* pMapObject = new CMapObject;

	// nullなら
	if (pMapObject == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pMapObject->Init()))
	{
		return nullptr;
	}

	// セット
	pMapObject->m_pos = pos;
	pMapObject->m_rot = rot;
	pMapObject->m_nIdx = nIdx;

	// 生成されたポインタを返す
	return pMapObject;
}
//=========================
// 初期化
//=========================
HRESULT CMapObject::Init(void)
{
	// 値の初期化
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxworld = {};
	m_nIdx = -1;

	return S_OK;
}
//=========================
// 終了
//=========================
void CMapObject::Uninit(void)
{
	// 自身の破棄
	CObject::Release();
}
//=========================
// 更新
//=========================
void CMapObject::Update(void)
{
	// 無し
}
//=========================
// 描画
//=========================
void CMapObject::Draw(void)
{
#if 1
	if (m_nIdx == -1) return;

	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// リスト取得
	CModelList::MODELINFO Info = CModelList::GetInfo(m_nIdx);

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 現在のマトリックスの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)Info.pBuffMat->GetBufferPointer();

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)Info.dwNumMat; nCntMat++)
	{
		// マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// モデル(パーツ)の描画
		Info.pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
#endif
}