//===============================================
//
// 円柱攻撃管理処理 [ pilermanager.cpp ]
// Author : Asuma Nishio
//
//===============================================

//**********************************
// インクルードファイル宣言
//**********************************
#include "pilermanager.h"
#include "meshpiler.h"
#include "meshcircle.h"
#include "effectsmoke.h"
#include "manager.h"

//**********************************
// 名前空間
//**********************************
namespace PILERMANAGERINFO
{
	constexpr int MAX_ACTIVETIME = 600;	// 最大カウント
	constexpr int SIRCLECOUNT = 20;		// 円形生成カウント
	constexpr int PILERCOUNT = 45;		// 円柱生成カウント
	constexpr int RANDAM = 3;			// 生成数ランダムの最高値
	constexpr int ACTIVEBACE = 5;		// 生成規定値
};

//===============================
// コンストラクタ
//===============================
CPilerManager::CPilerManager()
{
	// 値のクリア
	m_nTimer = NULL;
	m_nCount = NULL;
	m_nActiveTime = NULL;
	m_LastCirclePos = VECTOR3_NULL;
	m_State = STATE_IDLE;
}
//===============================
// デストラクタ
//===============================
CPilerManager::~CPilerManager()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CPilerManager::Init(void)
{
	// 変数の初期化
	m_nTimer = NULL;
	m_nCount = NULL;
	m_State = STATE_IDLE;
	m_nActiveTime = PILERMANAGERINFO::MAX_ACTIVETIME;

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CPilerManager::Uninit(void)
{
	// 無し
}
//===============================
// 更新処理
//===============================
void CPilerManager::Update(D3DXVECTOR3* DestPos)
{
	// イベントカメラモードなら
	if (CManager::GetCamera()->GetMode() == CManager::GetCamera()->MODE_EVENT) return;

	// サウンド取得
	CSound* pSound = CManager::GetSound();
	if (pSound == nullptr) return;

	// アクティブタイムを減算
	m_nActiveTime--;

	// 0以下になったら
	if (m_nActiveTime <= 0)
	{
		// ランダム値を設定
		int nNumActive = (rand() % PILERMANAGERINFO::ACTIVEBACE) + PILERMANAGERINFO::RANDAM;

		switch (m_State)
		{
		case STATE_IDLE:	// 待機中
		
			// カウントを加算
			m_nTimer++;

			// 超えたら
			if (m_nTimer > PILERMANAGERINFO::SIRCLECOUNT)
			{
				// 出現音再生
				pSound->PlaySound(CSound::SOUND_LABEL_CIRCLE);

				// サークル出現
				CMeshCircle::Create(*DestPos);
				
				// 出現した位置を保存
				m_LastCirclePos = *DestPos;

				// タイムをリセット
				m_nTimer = NULL;

				// 状態を変更
				m_State = STATE_WAIT_PILER;
			}
			break;
		

		case STATE_WAIT_PILER:	// 待機中

			// タイムを加算
			m_nTimer++;

			// 超えたら
			if (m_nTimer > PILERMANAGERINFO::PILERCOUNT)
			{
				// 円柱出現
				CMeshPiler::Create(m_LastCirclePos);

				m_LastCirclePos = VECTOR3_NULL;

				// 出現回数を増やす
				m_nCount++;	

				// タイムカウントを初期化
				m_nTimer = NULL;

				if (m_nCount >= nNumActive)
				{
					// 状態変更
					m_State = STATE_COOLTIME;
				}
				else
				{
					// 状態変更
					m_State = STATE_IDLE;
				}
			}
			break;

		case STATE_COOLTIME:	// クールタイム

			// カウントを加算
			m_nTimer++;

			// 10秒たったら
			if (m_nTimer > PILERMANAGERINFO::MAX_ACTIVETIME)
			{
				// リセットして再び開始
				m_nTimer = NULL;
				m_nCount = NULL;
				m_State = STATE_IDLE;
				m_nActiveTime = PILERMANAGERINFO::MAX_ACTIVETIME;
			}
			break;
		}
	}
}