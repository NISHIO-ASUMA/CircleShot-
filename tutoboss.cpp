//==========================================
//
// チュートリアルボス処理 [ tutoboss.cpp ]
// Author: Asuma Nishio
//
//==========================================

//******************************
// インクルードファイル
//******************************
#include "tutoboss.h"
#include "manager.h"

//==============================
// オーバーロードコンストラクタ
//==============================
CTutoBoss::CTutoBoss(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pMotion = nullptr;
	m_mtxworld = {};

	for (int nCnt = 0; nCnt < TUTOMODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_nType = NULL;
}
//==============================
// デストラクタ
//==============================
CTutoBoss::~CTutoBoss()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CTutoBoss* CTutoBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンス生成
	CTutoBoss* pTutoBoss = new CTutoBoss();
	if (pTutoBoss == nullptr) return nullptr;

	// オブジェクト設定
	pTutoBoss->m_pos = pos;
	pTutoBoss->m_rot = rot;

	// 初期化失敗時
	if (FAILED(pTutoBoss->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pTutoBoss;
}
//==============================
// 初期化処理
//==============================
HRESULT CTutoBoss::Init(void)
{

	// オブジェクトの種類をセット
	SetObjType(TYPE_BOSS);

	// タイプ代入
	m_nType = CTutoBoss::TYPE_MAX;

	// モーションの読み込み
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\TutoBoss.txt", TUTOMODEL, m_pModel, CTutoBoss::TYPE_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(m_nType);

	// 初期化結果を返す
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CTutoBoss::Uninit(void)
{
	// モデル数分の破棄
	for (int nCnt = 0; nCnt < TUTOMODEL; nCnt++)
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
//==============================
// 更新処理
//==============================
void CTutoBoss::Update(void)
{
	// nullチェック
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(m_pModel,TUTOMODEL);
	}
}
//==============================
// 描画処理
//==============================
void CTutoBoss::Draw(void)
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
	for (int nCnt = 0; nCnt < TUTOMODEL; nCnt++)
	{
		// 全モデル描画
		m_pModel[nCnt]->Draw();
	}
}
