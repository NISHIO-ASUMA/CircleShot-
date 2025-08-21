//============================================
//
// メッシュフィールド処理 [ meshfield.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードファイル
//**********************
#include "meshfield.h"
#include "manager.h"
#include "texture.h"

//*******************************
// マクロ定義
//*******************************
#define XVTX (1) // Xの値
#define ZVTX (1) // Zの値

#define VERTEX ((XVTX + 1) * (ZVTX + 1))				 // 頂点数
#define POLYGON (((XVTX * ZVTX) * 2)) + (4 * (ZVTX - 1)) // ポリゴン数
#define INDEX (POLYGON + 2)								 // インデックス数

//============================================
// コンストラクタ
//============================================
CMeshField::CMeshField(int nPrio) : CObject(nPrio)
{
	// 値のクリア処理
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxWorld = {};
	m_fRadius = NULL;
	m_nNumAllVtx = 0;
	m_nNumIdx = 0;
	m_nNumPrimitive = 0;
	m_nTexIdx = NULL;
}
//============================================
// デストラクタ
//============================================
CMeshField::~CMeshField()
{
	// 無し
}
//============================================
// 生成処理
//============================================
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, float fRadius)
{
	// インスタンス生成
	CMeshField* pMeshField = new CMeshField;

	// nullptrだったら
	if (pMeshField == nullptr) return nullptr;

	// 座標代入
	pMeshField->m_pos = pos;

	// 半径代入
	pMeshField->m_fRadius = fRadius;

	// テクスチャ設定
	pMeshField->SetTexture();

	// 初期化失敗時
	if (FAILED(pMeshField->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// 生成されたポインタを返す
	return pMeshField;
}
//============================================
// テクスチャ設定
//============================================
void CMeshField::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// 割り当て
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\DomeTex.jpg");
}
//============================================
// 初期化処理
//============================================
HRESULT CMeshField::Init(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdx,
		NULL);

	// 変数の初期化
	m_rot = VECTOR3_NULL;

	// 頂点情報のポインタを宣言
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を計算する変数
	float fTexX = 1.0f / XVTX;
	float fTexY = 1.0f / ZVTX;
	int nCnt = 0;

	//縦
	for (int nCntZ = 0; nCntZ <= ZVTX; nCntZ++)
	{
		//横
		for (int nCntX = 0; nCntX <= XVTX; nCntX++)
		{
			// 頂点座標の設定
			pVtx[nCnt].pos = D3DXVECTOR3(
				(0.0f + (m_fRadius / XVTX) * nCntX) - (m_fRadius * 0.5f),
				 0.0f,
				 m_fRadius - ((m_fRadius / XVTX) * nCntZ) - (m_fRadius * 0.5f));

			// 法線ベクトルの設定
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCnt].col = COLOR_WHITE;

			// テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntX, nCntZ * fTexY);

			// 加算
			nCnt++;
		}
	}

	// アンロック
	m_pVtx->Unlock();

	// インデックスバッファのポインタ
	WORD* pIdx;

	// インデックスバッファのロック
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	WORD IndxNum = XVTX + 1;// X

	WORD IdxCnt = 0;// 配列

	WORD Num = 0;

	// インデックスの設定
	for (int IndxCount1 = 0; IndxCount1 < ZVTX; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= XVTX; IndxCount2++, IndxNum++, Num++)
		{
			pIdx[IdxCnt] = IndxNum;
			pIdx[IdxCnt + 1] = Num;
			IdxCnt += 2;
		}

		// NOTE:最後の行じゃなかったら
		if (IndxCount1 < ZVTX - 1)
		{
			pIdx[IdxCnt] = Num - 1;
			pIdx[IdxCnt + 1] = IndxNum;
			IdxCnt += 2;
		}
	}

	// インデックスバッファのアンロック
	m_pIdx->Unlock();

	return S_OK;
}
//============================================
// 終了処理
//============================================
void CMeshField::Uninit(void)
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
//============================================
// 更新処理
//============================================
void CMeshField::Update(void)
{
	// 無し
}
//============================================
// 描画処理
//============================================
void CMeshField::Draw(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// セット
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

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdx);

	// テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX, 0, POLYGON);

	// テクスチャを戻す
	pDevice->SetTexture(0, NULL);

}
