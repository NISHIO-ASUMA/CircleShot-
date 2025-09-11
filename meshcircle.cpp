//=====================================
//
// 円形メッシュ処理 [ meshcircle.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "meshcircle.h"
#include "manager.h"
#include "texture.h"
#include "effectsmoke.h"
#include "spread.h"

//**********************
// 名前空間
//**********************
namespace CIRCLEINFO
{
	constexpr int NUM_XVERTEX = 30;	// 頂点分割数 ( X )
	constexpr int NUM_ZVERTEX = 1;	// 頂点分割数 ( Z )
	constexpr float CIRCLERADIUS = 60.0f;	// 最大の半径
	constexpr int NUMSPREAD = 16;	// 拡散オブジェクト最大出現数
};

//===================================
// オーバーロードコンストラクタ
//===================================
CMeshCircle::CMeshCircle(int nPriority) : CObject(nPriority)
{
	// 値のクリア処理
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;

	m_nTexIdx = NULL;
	m_nNumIdx = NULL;
	m_nNumPrimitive = NULL;
	m_nNumDigitZ = NULL;
	m_nNumDigitX = NULL;
	m_nNumAllVtx = NULL;
	m_mtxWorld = {};
	m_fRadius = NULL;
	m_nLife = NULL;
}
//===================================
// デストラクタ
//===================================
CMeshCircle::~CMeshCircle()
{
	// 無し
}
//===================================
// 生成処理
//===================================
CMeshCircle* CMeshCircle::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CMeshCircle* pMeshCircle = new CMeshCircle;

	// nullチェックs
	if (pMeshCircle == nullptr)	return nullptr;

	// オブジェクト設定
	pMeshCircle->SetTexture();
	pMeshCircle->m_pos = pos;

	// 初期化失敗時
	if (FAILED(pMeshCircle->Init()))
	{
		return nullptr;
	}

	// 煙エフェクト生成
	CEffectSmoke::Create(pos, D3DXCOLOR(1.0f, 0.1f, 0.22f, 1.0f), VECTOR3_NULL, 50, 70.0f);

	// 生成されたポインタを返す
	return pMeshCircle;
}
//===================================
// 初期化処理
//===================================
HRESULT CMeshCircle::Init(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点数,インデックス数,ポリゴン数を計算する
	m_nNumAllVtx = (CIRCLEINFO::NUM_XVERTEX + 1) * (CIRCLEINFO::NUM_ZVERTEX + 1);
	m_nNumPrimitive = m_nNumAllVtx - 2;
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
	float fTexX = 1.0f / CIRCLEINFO::NUM_XVERTEX;
	int nCnt = 0;

	// 法線設定用
	D3DXVECTOR3 nor = VECTOR3_NULL;

	// 外径の計算
	for (int nCntOut = 0; nCntOut <= CIRCLEINFO::NUM_XVERTEX; nCntOut++)
	{
		// 角度を計算
		float fAngel = (D3DX_PI * 2.0f) / CIRCLEINFO::NUM_XVERTEX * nCntOut;

		// 頂点座標の設定
		pVtx[nCnt].pos = D3DXVECTOR3(sinf(fAngel) * CIRCLEINFO::CIRCLERADIUS, 2.0f, cosf(fAngel) * CIRCLEINFO::CIRCLERADIUS);

		// 法線ベクトルの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		// テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntOut, 1.0f);

		// 加算
		nCnt++;
	}

	// 内径の計算
	for (int nCntIn = 0; nCntIn <= CIRCLEINFO::NUM_XVERTEX; nCntIn++)
	{
		// 角度計算
		float fAngel = (D3DX_PI * 2.0f) / CIRCLEINFO::NUM_XVERTEX * nCntIn;

		// 頂点座標の設定
		pVtx[nCnt].pos = D3DXVECTOR3(sinf(fAngel) * 0.5f, 2.0f, cosf(fAngel) * 0.5f);

		// 法線ベクトルの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[nCnt].col = D3DXCOLOR(1.0f,0.0f,0.0f,0.5f);

		// テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntIn, 1.0f);

		// 加算
		nCnt++;
	}


	// 頂点バッファをアンロック
	m_pVtx->Unlock();

	// インデックスポインタを宣言
	WORD* pIdx;

	// インデックスバッファのロック
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	WORD IndxNum = CIRCLEINFO::NUM_XVERTEX + 1;// X

	WORD IdxCnt = 0;// 配列

	WORD Num = 0;

	// インデックスの設定
	for (int IndxCount1 = 0; IndxCount1 < CIRCLEINFO::NUM_ZVERTEX; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= CIRCLEINFO::NUM_XVERTEX; IndxCount2++, IndxNum++, Num++)
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

	m_nLife = 90;

	// サークルの円周上に石つぶてを生成
	for (int nCnt = 0; nCnt < CIRCLEINFO::NUMSPREAD; nCnt++)
	{
		// 配置角度を計算
		float fPopAngle = (D3DX_PI * 2.0f / CIRCLEINFO::NUMSPREAD) * nCnt;

		// 円周上の座標を計算
		float fRotX = sinf(fPopAngle) * CIRCLEINFO::CIRCLERADIUS;
		float fRotY = m_pos.y;
		float fRotZ = cosf(fPopAngle) * CIRCLEINFO::CIRCLERADIUS;

		// 座標セット
		D3DXVECTOR3 MathPos(fRotX, fRotY, fRotZ);

		// ワールド座標
		D3DXVECTOR3 pos = m_pos + MathPos;

		// 外側方向ベクトル
		D3DXVECTOR3 dir(sinf(fPopAngle), 0.0f, cosf(fPopAngle));

		// 正規化
		D3DXVec3Normalize(&dir, &dir);

		// 座標と角度を設定
		CSpread::Create(pos, dir);
	}

	// 初期化結果を返す
	return S_OK;
}
//===================================
// 終了処理
//===================================
void CMeshCircle::Uninit(void)
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
//===================================
// 更新処理
//===================================
void CMeshCircle::Update(void)
{
	// 時間経過で終了処理
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();

		return;
	}
}
//===================================
// 描画処理
//===================================
void CMeshCircle::Draw(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

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
}
//===================================
// テクスチャ割り当て処理
//===================================
void CMeshCircle::SetTexture(void)
{

}
