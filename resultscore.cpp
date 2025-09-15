//=======================================
//
// リザルトスコア処理 [ resultscore.h ]
// Author: Asuma Nishio
// 
//=======================================

//**********************
// インクルードファイル
//**********************
#include "resultscore.h"
#include "manager.h"
#include "texture.h"

//================================
// コンストラクタ
//================================
CResultScore::CResultScore(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_nScore = NULL;
	m_nLastScore = NULL;
	m_nTimeScore = NULL;
	m_nIdxTexture = NULL;

	m_pos = VECTOR3_NULL;

	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
}
//================================
// デストラクタ
//================================
CResultScore::~CResultScore()
{
	// 無し
}
//================================
// 生成処理
//================================
CResultScore* CResultScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	// インスタンス生成
	CResultScore* pResultScore = new CResultScore;
	if (pResultScore == nullptr) return nullptr;

	// 座標,サイズ設定
	pResultScore->m_pos = pos;
	pResultScore->m_fWidth = fWidth;
	pResultScore->m_fHeight = fHeight;
	pResultScore->m_nType = nType;

	// 初期化失敗時
	if (FAILED(pResultScore->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pResultScore;
}
//================================
// 初期化処理
//================================
HRESULT CResultScore::Init(void)
{
	// 横幅計算
	float fTexPos = m_fWidth / NUM_RESULTSCORE;

	// 桁数分
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// インスタンス生成
		m_apNumber[nCnt] = new CNumber;

		// ナンバー変数のサイズ
		m_apNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		// 座標設定
		m_apNumber[nCnt]->SetPos(m_pos);

		// 初期化処理
		m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);
	}

	// テクスチャセット
	SetTexture();

	// 初期化結果を返す
	return S_OK;

}
//================================
// 終了処理
//================================
void CResultScore::Uninit(void)
{
	// 使った分破棄
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// nullptrチェック
		if (m_apNumber[nCnt] != nullptr)
		{
			// 終了
			m_apNumber[nCnt]->Uninit();

			// 破棄
			delete m_apNumber[nCnt];

			// ポインタ初期化
			m_apNumber[nCnt] = nullptr;
		}
	}

	// 自身の破棄
	CObject::Release();
}
//================================
// 更新処理
//================================
void CResultScore::Update(void)
{
	switch (m_nType)
	{
	case SCORE_GAME:
	{
		// スコア格納
		int nScore = m_nScore;

		// 八桁分
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // 右から処理
		{
			// 桁数ごとに分割する値を計算
			int nDigit = nScore % NUM_RESULTDIGIT;

			nScore /= NUM_RESULTDIGIT;

			// ナンバー更新
			m_apNumber[nCntScore]->Update();

			// 桁更新
			m_apNumber[nCntScore]->SetDigit(nDigit);
		}
	}
	break;

	case SCORE_TIME:
	{
		// タイム用のスコア格納
		int nTimescore = m_nTimeScore;

		// 八桁分
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // 右から処理
		{
			// 桁数ごとに分割する値を計算
			int nDigitTime = nTimescore % NUM_RESULTDIGIT;

			nTimescore /= NUM_RESULTDIGIT;

			// ナンバー更新
			m_apNumber[nCntScore]->Update();

			// 桁更新
			m_apNumber[nCntScore]->SetDigit(nDigitTime);
		}
	}
	break;

	case SCORE_LAST:
	{
		// スコア格納
		int nLastScore = m_nLastScore;

		// 八桁分
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // 右から処理
		{
			// 桁数ごとに分割する値を計算
			int nDigitLast = nLastScore % NUM_RESULTDIGIT;

			nLastScore /= NUM_RESULTDIGIT;

			// ナンバー更新
			m_apNumber[nCntScore]->Update();

			// 桁更新
			m_apNumber[nCntScore]->SetDigit(nDigitLast);
		}
	}
	break;

	default:
		break;
	}
}
//================================
// 描画処理
//================================
void CResultScore::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	// 使っている桁数分の描画
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// テクスチャセット
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		// ナンバー描画
		m_apNumber[nCnt]->Draw();
	}
}
//================================
// テクスチャ処理
//================================
void CResultScore::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ割り当て
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\num001.png");
}
//================================
// クリアタイムのスコアを計算
//================================
int CResultScore::MathTimescore(void)
{
	// 読み込んだ値
	float fValue = (float)m_nTimeScore;

	// 上限値
	const float fMaxReadValue = 120.0f;

	// 最大スコア
	const int nMaxTimeScore = 50000;

	// 比率を算出
	float fRatio = 1.0f - (fValue / fMaxReadValue);

	// 範囲補正
	if (fRatio < 0.0f) fRatio = 0.0f;
	if (fRatio > 1.0f) fRatio = 1.0f;

	// スコア計算
	int nMathscore = (int)(nMaxTimeScore * fRatio);

	return nMathscore;
}
