//====================================
//
// Xファイル処理 [ objectX.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "objectX.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_dwNumMat = NULL;
	m_mtxWorld = {};
	m_nIdxTexture = NULL;
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pTexture = nullptr;
	m_pFileName = {};

	m_isUseQaut = false;
}
//=============================
// デストラクタ
//=============================
CObjectX::~CObjectX()
{
	// 無し
}
//=============================
// 初期化処理
//=============================
HRESULT CObjectX::Init(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(m_pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat = nullptr;

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
			// テクスチャなし
			m_pTexture[nCntMat] = -1; 
		}
	}

	// 結果を返す
	return S_OK;
}
//=============================
// 終了処理
//=============================
void CObjectX::Uninit(void)
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

	// nullじゃなかったら
	if (m_pTexture != nullptr)
	{
		// ポインタの破棄
		delete m_pTexture;

		// nullptrにする
		m_pTexture = nullptr;
	}

	// オブジェクトの破棄
	CObject::Release();
}
//=============================
// 更新処理
//=============================
void CObjectX::Update(void)
{
	// 無し
}
//=============================
// 描画処理
//=============================
void CObjectX::Draw(void)
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
	D3DXMatrixIdentity(&m_mtxWorld);

	if (!m_isUseQaut)
	{
		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

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
			pDevice->SetTexture(0, NULL); // テクスチャなし
		}

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//=============================
// 生成処理
//=============================
CObjectX* CObjectX::Create(const char* pFileName,D3DXVECTOR3 pos)
{
	// インスタンス生成
	CObjectX* pObjX = new CObjectX;

	// 座標代入
	pObjX->m_pos = pos;

	// ファイルパス
	pObjX->m_pFileName = pFileName;

	// 初期化処理
	if (FAILED(pObjX->Init()))
	{
		// 破棄
		delete pObjX;

		// nullptr代入
		pObjX = nullptr;

		// nullptrを返す
		return nullptr;
	}

	// ポインタを返す
	return pObjX;
}
