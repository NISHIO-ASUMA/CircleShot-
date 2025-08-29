//====================================
//
// タイム処理 [ time.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "time.h"
#include "manager.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_fHeight = NULL;
	m_fWidth = NULL;
	m_nAllTime = NULL;
	m_nCurrentTime = NULL;
	m_nIdxTexture = NULL;

	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		m_pNumber[nCnt] = nullptr;
	}
}
//===============================
// デストラクタ
//===============================
CTime::~CTime()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CTime* CTime::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// タイムクラスのインスタンス生成
	CTime* pTime = new CTime;

	// nullptrだったら
	if (pTime == nullptr) return nullptr;

	// メンバ変数にセット
	pTime->m_fHeight = fHeight;
	pTime->m_fWidth = fWidth;
	pTime->m_pos = pos;

	// 初期化失敗時
	if (FAILED(pTime->Init()))
	{
		// nullptr代入
		return nullptr;
	}

	// 結果を返す
	return pTime;
}
//===============================
// 初期化処理
//===============================
HRESULT CTime::Init(void)
{
	// メンバ変数の初期化
	m_nAllTime = NUMTIME;
	m_nCurrentTime = NULL;

	// 横幅計算
	float fTexPos = m_fWidth / DIGIT_TIME;

	// 桁数分回す
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// インスタンス生成
		m_pNumber[nCnt] = new CNumber;

		// ナンバー変数の初期化
		m_pNumber[nCnt]->SetSize(fTexPos, m_fHeight);
		m_pNumber[nCnt]->SetPos(m_pos);
		m_pNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);
	}

	// テクスチャセット
	SetTexture();

	// 結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CTime::Uninit(void)
{
	// 使った分破棄
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// nullptrチェック
		if (m_pNumber[nCnt] != nullptr)
		{
			// 終了処理
			m_pNumber[nCnt]->Uninit();

			// ポインタの破棄
			delete m_pNumber[nCnt];

			// null初期化
			m_pNumber[nCnt] = nullptr;
		}
	}

	// オブジェクトの破棄
	CObject::Release();
}
//===============================
// 更新処理
//===============================
void CTime::Update(void)
{
	// カウントを加算
	m_nCurrentTime++;

	// 1フレーム経過後
	if (m_nCurrentTime >= CARVETIME)
	{
		// 総時間を減らす
		m_nAllTime--;

		// 0以下なら
		if (m_nAllTime <= 0) m_nAllTime = 0;

		// カウンターを初期化する
		m_nCurrentTime = 0;
	}

	// 最大時間を格納
	int time = m_nAllTime;

	// 一の位から百の位まで順に分解
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// 桁数計算
		int digit = time % DIVIDE;
		time /= DIVIDE;

		// ナンバー更新と桁設定
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Update();
			m_pNumber[nCnt]->SetDigit(digit);
		}
	}
}
//===============================
// 描画処理
//===============================
void CTime::Draw(void)
{
#if 0
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	// 桁数分描画
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// テクスチャ設定
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		// タイマー描画
		m_pNumber[nCnt]->Draw();
	}
#endif
}
//===============================
// テクスチャセット
//===============================
void CTime::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ割り当て
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\score001.png");
}
