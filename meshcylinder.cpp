//=============================================
//
// メッシュシリンダー処理 [ meshcylinder.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードファイル
//**********************
#include "meshcylinder.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"

//===============================
// コンストラクタ
//===============================
CMeshCylinder::CMeshCylinder(int nPrio) : CObject(nPrio)
{
	// 値のクリア処理
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;

	for (int nCnt = 0; nCnt < DIGIT_X; nCnt++)
	{
		m_vtxPos[nCnt] = VECTOR3_NULL;
	}

	m_nTexIdx = NULL;
	m_nNumIdx = NULL;
	m_nNumPrimitive = NULL;
	m_nNumDigitZ = NULL;
	m_nNumDigitX = NULL;
	m_nNumAllVtx = NULL;
	m_mtxWorld = {};
	m_fRadius = NULL;
}
//===============================
// デストラクタ
//===============================
CMeshCylinder::~CMeshCylinder()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CMeshCylinder::Init(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点数,インデックス数,ポリゴン数を計算する
	m_nNumAllVtx = (DIGIT_X + 1) * (DIGIT_Z + 1);
	m_nNumPrimitive = ((DIGIT_X * DIGIT_Z) * 2) + (4 * (DIGIT_Z - 1));
	m_nNumIdx = (m_nNumPrimitive + 2);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumAllVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdx,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標
	float fTexX = 1.0f / DIGIT_X;
	float fTexY = 1.0f / DIGIT_Z;
	int nCnt = 0;

	// 法線設定用
	D3DXVECTOR3 nor = VECTOR3_NULL;

	// 縦
	for (int nCntZ = 0; nCntZ <= DIGIT_Z; nCntZ++)
	{
		// 横
		for (int nCntX = 0; nCntX <= DIGIT_X; nCntX++)
		{
			// 角度計算
			float fAngle = (D3DX_PI * 2.0f) / DIGIT_X * nCntX;

			// 頂点座標の設定
			pVtx[nCnt].pos = D3DXVECTOR3(sinf((fAngle)) * m_fRadius, nCntZ * 10.0f, cosf((fAngle)) * m_fRadius);

			// 法線ベクトルの設定
			nor = pVtx[nCnt].pos - m_pos;	// 各頂点から原点の値を引く
			D3DXVec3Normalize(&pVtx[nCnt].nor, &nor);	// 法線の正規化

			// 法線ベクトルの設定
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCnt].col = COLOR_NULL;

			// テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntX, nCntZ * fTexY);

			// 加算
			nCnt++;
		}
	}

	// 頂点バッファをアンロック
	m_pVtx->Unlock();

	// インデックスポインタを宣言
	WORD* pIdx;

	// インデックスバッファのロック
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	WORD IndxNum = DIGIT_X + 1;// X

	WORD IdxCnt = 0;// 配列

	WORD Num = 0;

	// インデックスの設定
	for (int IndxCount1 = 0; IndxCount1 < DIGIT_Z; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= DIGIT_X; IndxCount2++, IndxNum++, Num++)
		{
			pIdx[IdxCnt] = IndxNum;
			pIdx[IdxCnt + 1] = Num;
			IdxCnt += 2;
		}

		// 最後の行じゃなかったら
		if (IndxCount1 < m_nNumDigitZ - 1)
		{
			pIdx[IdxCnt] = Num - 1;
			pIdx[IdxCnt + 1] = IndxNum;
			IdxCnt += 2;
		}
	}

	//インデックスバッファのアンロック
	m_pIdx->Unlock();

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CMeshCylinder::Uninit(void)
{
	//頂点バッファの解放
	if (m_pVtx != nullptr)
	{
		m_pVtx->Release();
		m_pVtx = nullptr;
	}

	//インデックスバッファの解放
	if (m_pIdx != nullptr)
	{
		m_pIdx->Release();
		m_pIdx = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}
//===============================
// 更新処理
//===============================
void CMeshCylinder::Update(void)
{
	// なし
}
//===============================
// 描画処理
//===============================
void CMeshCylinder::Draw(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdx);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumAllVtx, 0, m_nNumPrimitive);

	//テクスチャを戻す
	pDevice->SetTexture(0, NULL);

	// デバッグ表示
	CDebugproc::Print("メッシュシリンダーの座標 [ %.2f,%.2f,%.2f ]", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(0, 80);
}
//===============================
// テクスチャ割り当て
//===============================
void CMeshCylinder::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ割り当て
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\field100.jpg");
}
//===============================
// 生成処理
//===============================
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, float fRadius)
{
	// インスタンス生成
	CMeshCylinder* pMesh = new CMeshCylinder;

	// nullptrだったら
	if (pMesh == nullptr) return nullptr;

	// 代入
	pMesh->SetTexture();
	pMesh->m_pos = pos;
	pMesh->m_fRadius = fRadius;

	// 初期化失敗時
	if (FAILED(pMesh->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// ポインタを返す
	return pMesh;;
}

