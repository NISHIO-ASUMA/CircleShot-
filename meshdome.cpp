//=====================================
//
// メッシュドーム処理 [ meshdome.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "meshdome.h"
#include "manager.h"
#include "texture.h"

//==================================
// コンストラクタ
//==================================
CMeshDome::CMeshDome(int nPrio) : CObject(nPrio)
{
	// 値のクリア処理
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxWorld = {};
	m_nRadius = NULL;

	m_nTexIdx = NULL;
}
//==================================
// デストラクタ
//==================================
CMeshDome::~CMeshDome()
{
	// 無し
}
//==================================
// 初期化処理
//==================================
HRESULT CMeshDome::Init(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MeshDome_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MeshDome_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdx,
		NULL);

	// 頂点バッファのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV <= MeshDome_Z_BLOCK; nCntV++)
	{
		for (int nCntH = 0; nCntH <= MeshDome_X_BLOCK; nCntH++)
		{
			// nCntH番目の角度を計算
			float angleH = (360.0f / MeshDome_X_BLOCK) * nCntH;

			// nCntV番目の角度を計算
			float angleV = 90.0f * ((float)nCntV / MeshDome_Z_BLOCK);

			// 頂点の位置を設定
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos = D3DXVECTOR3(
				sinf(D3DXToRadian(angleH)) * m_nRadius * cosf(D3DXToRadian(angleV)), // X座標
				m_nRadius * sinf(D3DXToRadian(angleV)),								 // Y座標
				cosf(D3DXToRadian(angleH)) * m_nRadius * cosf(D3DXToRadian(angleV))  // Z座標
			);

			// 法線を計算 (頂点座標からの単位ベクトル)
			D3DXVECTOR3 normal = D3DXVECTOR3(
				pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos.x / m_nRadius,
				pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos.y / m_nRadius,
				pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos.z / m_nRadius
			);

			// 正規化する
			D3DXVec3Normalize(&normal, &normal);

			// 法線に割り当て
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].nor = normal;

			// 頂点カラーを設定
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].col = COLOR_WHITE;

			// テクスチャ座標を設定
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].tex = D3DXVECTOR2(
				(float)nCntH / MeshDome_X_BLOCK,						// U座標（円周方向）
				1.0f - (float)nCntV / MeshDome_Z_BLOCK				    // V座標（高さ方向）
			);
		}
	}

	// 頂点バッファをアンロック
	m_pVtx->Unlock();

	// インデックスバッファのポインタ
	WORD* pIdx = NULL;

	// インデックスバッファをロック
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	WORD idx = 0;

	for (int nCntV = 0; nCntV < MeshDome_Z_BLOCK; nCntV++)
	{
		for (int nCntX = 0; nCntX < MeshDome_X_BLOCK; nCntX++)
		{
			// 基準のインデックス
			WORD baseIndex = nCntV * (MeshDome_X_BLOCK + 1) + nCntX;

			// 三角形1
			pIdx[idx++] = baseIndex;
			pIdx[idx++] = baseIndex + MeshDome_X_BLOCK + 1;
			pIdx[idx++] = baseIndex + 1;

			// 三角形2
			pIdx[idx++] = baseIndex + 1;
			pIdx[idx++] = baseIndex + MeshDome_X_BLOCK + 1;
			pIdx[idx++] = baseIndex + MeshDome_X_BLOCK + 2;
		}

	}

	// インデックスバッファをアンロック
	m_pIdx->Unlock();

	return S_OK;
}
//==================================
// 終了処理
//==================================
void CMeshDome::Uninit(void)
{
	// 頂点バッファの解放
	if (m_pVtx != nullptr)
	{
		m_pVtx->Release();
		m_pVtx = nullptr;
	}

	// インデックスバッファの解放
	if (m_pIdx != nullptr)
	{
		m_pIdx->Release();
		m_pIdx = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}
//==================================
// 更新処理
//==================================
void CMeshDome::Update(void)
{
	// 無し
}
//==================================
// 描画処理
//==================================
void CMeshDome::Draw(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdx);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MeshDome_VERTEX_NUM, 0, MeshDome_INDEX_NUM);

	// テクスチャNULL
	pDevice->SetTexture(0, NULL);
}
//==================================
// 生成処理
//==================================
CMeshDome* CMeshDome::Create(D3DXVECTOR3 pos, float nRadius)
{
	// インスタンス生成
	CMeshDome* pMeshDome = new CMeshDome;

	// nullptrだったら
	if (pMeshDome == nullptr) return nullptr;

	// オブジェクト設定
	pMeshDome->m_pos = pos;
	pMeshDome->m_nRadius = nRadius;
	pMeshDome->SetTexture();

	// 初期化失敗時
	if (FAILED(pMeshDome->Init()))
	{
		// nulptrを返す
		return nullptr;
	}

	// ドームのポインタを返す
	return pMeshDome;
}
//==================================
// テクスチャ設定
//==================================
void CMeshDome::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ割り当て
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\DomeTex.jpg");
}
