//=============================================
//
// タイトルプレイヤー処理 [ titleplayer.cpp ]
// Author: Asuma Nishio
//
//=============================================

//********************************
// インクルードファイル宣言
//********************************
#include "titleplayer.h"
#include "manager.h"
#include "input.h"

//============================
// コンストラクタ
//============================
CTitlePlayer::CTitlePlayer(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_move = VECTOR3_NULL;
	m_rotDest = VECTOR3_NULL;
	m_nIdxPlayer = NULL;

	// モデルのポインタのクリア
	for (int nCnt = 0; nCnt < TITLE_MODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	// クラスポインタ
	m_pMotion = nullptr;
	m_pFilename = {};
}
//============================
// デストラクタ
//============================
CTitlePlayer::~CTitlePlayer()
{
	// 無い
}
//============================
// 生成処理
//============================
CTitlePlayer* CTitlePlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const int nIdxParson, const char* pFilename)
{
	// インスタンス生成
	CTitlePlayer* pTitlePlayer = new CTitlePlayer;

	// nullptrだったら
	if (pTitlePlayer == nullptr) return nullptr;

	// オブジェクト設定
	pTitlePlayer->m_pos = pos;
	pTitlePlayer->m_rot = rot;
	pTitlePlayer->m_nIdxPlayer = nIdxParson;
	pTitlePlayer->m_pFilename = pFilename;

	// 初期化失敗時
	if (FAILED(pTitlePlayer->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pTitlePlayer;
}
//============================
// 指定番号のプレイヤー取得
//============================
CTitlePlayer* CTitlePlayer::GetIdxPlayer(int Idx)
{
	// オブジェクトの先頭取得
	CObject* pObj = CObject::GetTop(static_cast<int>(CObject::PRIORITY::PLAYER));

	// pObjがnullptrじゃなかったら
	while (pObj != nullptr)
	{
		// オブジェクトのタイプがPLAYERの時
		if (pObj->GetObjType() == CObject::TYPE_PLAYER)
		{
			// プレイヤー型にキャスト
			CTitlePlayer* pPlayer = static_cast<CTitlePlayer*>(pObj);

			// 番号が一致していたら
			if (pPlayer->GetPlayerIndex() == Idx)
			{
				// ポインタを返す
				return pPlayer;
			}
		}

		// 次のプレイヤーを代入
		pObj = pObj->GetNext();
	}

	// 取得できなかった場合
	return nullptr;
}
//============================
// 初期化処理
//============================
HRESULT CTitlePlayer::Init(void)
{
	// オブジェクトの種類をセット
	SetObjType(TYPE_PLAYER);

	// モーションの読み込み
	m_pMotion = CMotion::Load(m_pFilename, TITLE_MODEL, m_apModel, TITLEMOTION_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(TITLEMOTION_MAX);

	// 初期化結果を返す
	return S_OK;
}
//============================
// 終了処理
//============================
void CTitlePlayer::Uninit(void)
{
	// モデル数分の破棄
	for (int nCnt = 0; nCnt < TITLE_MODEL; nCnt++)
	{
		// nullptrチェック
		if (m_apModel[nCnt] != nullptr)
		{
			// 終了処理
			m_apModel[nCnt]->Uninit();

			// ポインタの破棄
			delete m_apModel[nCnt];

			// nullptrにする
			m_apModel[nCnt] = nullptr;
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
//============================
// 更新処理
//============================
void CTitlePlayer::Update(void)
{
	// 入力デバイスを取得
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// 取得失敗時
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// キー入力 かつ 回転終了時 モーション変更
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A)) && CManager::GetCamera()->GetFinishRotation())
	{
		// アクション状態に変更
		m_pMotion->SetMotion(TITLEMOTION_ACTION);
	}

	// モーションの更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(m_apModel,TITLE_MODEL);
	}
}
//============================
// 描画処理
//============================
void CTitlePlayer::Draw(void)
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
	for (int nCnt = 0; nCnt < TITLE_MODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}
