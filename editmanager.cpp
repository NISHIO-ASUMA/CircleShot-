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
#include "mapobject.h"
#include "template.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//=============================
// コンストラクタ
//=============================
CEditManager::CEditManager()
{
	// 値のクリア
	m_nSelectIndex = NULL;
	m_moveSpeed = NULL;
	m_rotSpeed = NULL;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nIdx = NULL;
	m_mtxworld = {};

	m_nSavePassIdx = NULL;
	m_nNumAll = NULL;

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
	m_moveSpeed = 5.0f;

	// 読み込み
	CModelList::Load();

	// 生成
	m_pMapManager = CMapManager::Craete();
	
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
	// カメラ
	CCamera* pCamera = CManager::GetCamera();

	// 移動処理
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// Aキーを押した

		m_pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
		m_pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// Dキーを押した
		// Dキーのみ押した
		m_pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
		m_pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// Wキーを押した

		m_pos.x += sinf(pCamera->GetRot().y) * m_moveSpeed;
		m_pos.z += cosf(pCamera->GetRot().y) * m_moveSpeed;

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// Sキーを押した

		m_pos.x -= sinf(pCamera->GetRot().y) * m_moveSpeed;
		m_pos.z -= cosf(pCamera->GetRot().y) * m_moveSpeed;
	}

	// 高さ変更
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_R))
	{
		m_pos.y += 20.0f;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_F))
	{
		m_pos.y -= 20.0f;
	}

	// 角度変更 ( Y )
	if (CManager::GetInputKeyboard()->GetPress(DIK_Y))
	{
		m_rot.y += 0.03f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_H))
	{
		m_rot.y -= 0.03f;
	}

	// 角度変更 ( X )
	if (CManager::GetInputKeyboard()->GetPress(DIK_U))
	{
		m_rot.x += 0.03f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_J))
	{
		m_rot.x -= 0.03f;
	}

	// 角度変更 ( Z )
	if (CManager::GetInputKeyboard()->GetPress(DIK_I))
	{
		m_rot.z += 0.03f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_K))
	{
		m_rot.z -= 0.03f;
	}

	// 初期化処理
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_TAB))
	{
		m_rot = VECTOR3_NULL;
	}

	// インデックスを加算 減算
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_E) && m_nIdx < 3)
	{
		m_nIdx++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_Q)&& m_nIdx >= 0)
	{
		m_nIdx--;

		//if (m_nIdx <= 0)
		//{
		//	m_nIdx = 0;
		//}
	}

	// 正規化関数
	m_rot.x = NormalAngle(m_rot.x);
	m_rot.y = NormalAngle(m_rot.y);
	m_rot.z = NormalAngle(m_rot.z);

	// キー入力で保存
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F7))
	{
		// ここに保存関数追加
		Save();
	}

	// 保存パス切り替え処理
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F6))
	{
		m_nSavePassIdx = (m_nSavePassIdx + 1) % SAVEPASS_MAX;
	}

	// キー入力で生成
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// 生成処理
		CMapObject* pMapObj = CMapObject::Create(m_pos, m_rot, m_nIdx);

		// 配列に追加
		m_pMapManager->PushBack(pMapObj);

		// 総数を加算
		m_nNumAll++;
	}
}
//=============================
// 描画処理
//=============================
void CEditManager::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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

	// モデル情報
	CModelList::MODELINFO Info = CModelList::GetInfo(m_nIdx);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)Info.pBuffMat->GetBufferPointer();

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)Info.dwNumMat; nCntMat++)
	{
		// カラー
		D3DXMATERIAL Col = pMat[nCntMat];

		Col.MatD3D.Diffuse.a = 0.5f;

		// マテリアル設定
		pDevice->SetMaterial(&Col.MatD3D);

		// インデックスに応じて変更する
		if (Info.pTexture[nCntMat] != -1)
		{
			// テクスチャ取得
			CTexture* pTexture = CManager::GetTexture();

			// テクスチャセット
			pDevice->SetTexture(0, pTexture->GetAddress(Info.pTexture[nCntMat]));
		}
		else
		{
			pDevice->SetTexture(0, NULL); // テクスチャなし
		}

		// モデル(パーツ)の描画
		Info.pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//=============================
// 描画処理
//=============================
void CEditManager::Save(void)
{
	// ファイルに保存
	// FILELIST[m_nSavePassIdx]
}
