//====================================
//
// モデル処理 [ model.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "model.h"
#include "manager.h"
#include "texture.h"

//=================================
// コンストラクタ
//=================================
CModel::CModel()
{
	// 値のクリア
	m_dwNumMat = NULL;
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pTexture = nullptr;
	m_offPos = VECTOR3_NULL;
	m_offRot = VECTOR3_NULL;
	m_parttype = PARTTYPE_NONE;
	m_isPlayer  = false;
	m_isBoss = false;
}
//=================================
// デストラクタ
//=================================
CModel::~CModel()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char * pFilename)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// 位置の設定
	m_pos = pos;
	m_rot = rot;

	// オフセットを代入
	m_offPos = pos;
	m_offRot = rot;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// テクスチャインデックス配列の動的確保
	m_pTexture = new int[m_dwNumMat];

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// テクスチャが読み込めたら
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// テクスチャポインタ取得
			CTexture* pTexture = CManager::GetTexture();

			// テクスチャセット
			m_pTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_pTexture[nCntMat] = -1; // テクスチャなし
		}
	}

	// 結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CModel::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	// マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	// テクスチャポインタの破棄
	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;

		m_pTexture = nullptr;
	}
}
//=================================
// 更新処理
//=================================
void CModel::Update(void)
{
	// 無し
}
//=================================
// 描画処理
//=================================
void CModel::Draw(void)
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y + m_offRot.y, m_rot.x + m_offRot.x, m_rot.z + m_offRot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offPos.x, m_pos.y + m_offPos.y, m_pos.z + m_offPos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// 親のペアネント格納用変数
	D3DXMATRIX mtxParent;

	if (m_pParent != nullptr)
	{// 親が存在する
		// ワールドマトリックス取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// 親が存在しない
		// マトリックス取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 親のマトリックスとかけ合わせる
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 現在のマトリックスの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// インデックスに応じて変更する
		if (m_pTexture[nCntMat] != -1)
		{
			// テクスチャ取得
			CTexture* pTexture = CManager::GetTexture();

			// テクスチャセット
			pDevice->SetTexture(0, pTexture->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			// テクスチャなし
			pDevice->SetTexture(0, NULL); 
		}

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//=================================
// 生成処理
//=================================
CModel* CModel::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, const char* pFilename)
{
	// インスタンス生成
	CModel* pModel = new CModel;

	// nullだったら
	if (pModel == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pModel->Init(pos, rot,pFilename)))
	{
		// nullptrセット
		return  nullptr;
	}

	// ポインタを返す
	return pModel;
}
//=================================
// 親設定処理
//=================================
void CModel::SetParent(CModel* pModel)
{
	// 設定
	m_pParent = pModel;
}
