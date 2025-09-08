//===========================================
//
// チュートリアルボス処理 [ tutoboss.cpp ]
// Author: Asuma Nishio
//
//===========================================

//******************************
// インクルードファイル
//******************************
#include "tutorialboss.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CTutorialBoss::CTutorialBoss(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pMotion = nullptr;
	m_mtxworld = {};

	for (int nCnt = 0; nCnt < TUTO_MODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}
}
//=============================
// デストラクタ
//=============================
CTutorialBoss::~CTutorialBoss()
{
	// 無し
}
//=============================
// 生成処理
//=============================
CTutorialBoss* CTutorialBoss::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CTutorialBoss* pTutoBoss = new CTutorialBoss;
	if (pTutoBoss == nullptr) return nullptr;

	// オブジェクト設定
	pTutoBoss->m_pos = pos;

	// 初期化失敗時
	if (FAILED(pTutoBoss->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pTutoBoss;
}
//=============================
// 初期化処理
//=============================
HRESULT CTutorialBoss::Init(void)
{
	// オブジェクトの種類をセット
	SetObjType(TYPE_BOSS);

	// モーションの読み込み
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\BossTuto.txt", TUTO_MODEL, m_pModel, CTutorialBoss::TYPE_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(CTutorialBoss::TYPE_MAX);

	// 初期化結果を返す
	return S_OK;
}
//=============================
// 終了処理
//=============================
void CTutorialBoss::Uninit(void)
{
	// モデル数分の破棄
	for (int nCnt = 0; nCnt < TUTO_MODEL; nCnt++)
	{
		// nullptrチェック
		if (m_pModel[nCnt] != nullptr)
		{
			// 終了処理
			m_pModel[nCnt]->Uninit();

			// ポインタの破棄
			delete m_pModel[nCnt];

			// nullptrにする
			m_pModel[nCnt] = nullptr;
		}
	}

	// nullptrチェック
	if (m_pMotion != nullptr)
	{
		// ポインタの破棄
		delete m_pMotion;

		// nullptrにする
		m_pMotion = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}
//=============================
// 更新処理
//=============================
void CTutorialBoss::Update(void)
{
	// nullチェック
	if (m_pMotion != nullptr) m_pMotion->Update(m_pModel, TUTO_MODEL);
}
//=============================
// 描画処理
//=============================
void CTutorialBoss::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

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

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < TUTO_MODEL; nCnt++)
	{
		// 全モデル描画
		m_pModel[nCnt]->Draw();
	}
}
