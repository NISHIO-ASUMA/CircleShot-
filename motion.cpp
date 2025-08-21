//====================================
//
// モーション処理 [ motion.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "motion.h"
#include "template.h"
#include "player.h"
#include "boss.h"
#include "debugproc.h"

//**************************
// 定数宣言
//**************************
constexpr int NEUTRAL = 0; // ニュートラル番号

//==============================
// コンストラクタ
//==============================
CMotion::CMotion()
{
	// 配列クリア
	m_aMotionInfo.clear();

	m_isLoopMotion = false;
	m_nCounterMotion = NULL;
	m_nKey = NULL;
	m_nNumKey = NULL;
	m_nNumMotion = NULL;
	m_motiontype = NULL;
	m_type = NULL;
	m_nNextKey = NULL;

	m_motiontypeBlend = NULL;
	m_nFrameBlend = NULL;
	m_nCounterBlend = NULL;
	m_nKeyBlend = NULL;
	m_nNextKeyBlend = NULL;

	m_isBlendMotion = false;
	m_isFinishMotion = false;
	m_isFirstMotion = false;
	m_isStopAction = false;

	m_nNumModels = NULL;
	m_nAllFrameCount = NULL;
	m_nNumAllFrame = NULL;
}
//==============================
// デストラクタ
//==============================
CMotion::~CMotion()
{
	// 無し
}
//==============================
// モーション読み込み関数
//==============================
CMotion* CMotion::Load(const char* pFilename,const int nMaxParts, CModel** pModel, int nDestMotions)
{
	// モーションクラスのインスタンス生成
	CMotion* pMotion = new CMotion;

	// ファイル設定
	std::ifstream file(pFilename);

	// ファイル例外チェック
	if (!file)
	{
		MessageBox(NULL, "ファイルオープン失敗", pFilename, MB_OK);

		// ポインタの破棄
		delete pMotion;

		// 失敗結果を返す
		return nullptr;
	}

	// 一行読み込む
	std::string line;

	// 使用ローカル変数
	int nModel = 0;
	int nIdx = 0;
	int nCntMotion = 0;

	// この引数に読み込むモーション総数を設定してこれの分だけm_amotionInfoでリサイズする
	pMotion->m_aMotionInfo.resize(nDestMotions);

	// 文字列を読み続ける
	while (std::getline(file, line))
	{
		// トークン設定
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		// "NUM_MODEL"読み取り時
		if (token == "NUM_MODEL")
		{
			// モデル数設定
			pMotion->SetModels(iss, nModel, nMaxParts);

			// 読み込んだモデル数を保存する
			pMotion->m_nNumModels = nModel;

		}
		// "MODEL_FILENAME"読み取り時
		else if (token == "MODEL_FILENAME")
		{
			// モデルファイル読み込み
			pMotion->SetModelFile(iss, pModel, nIdx);

			// インデックスカウントを加算
			nIdx++;
		}
		// "PARTSSET"読み取り時
		else if (token == "PARTSSET")
		{
			// パーツごとのセット
			pMotion->SetParts(file, pModel);
		}
		// "MOTIONSET"読み取り時
		else if (token == "MOTIONSET")
		{
			// パーツのモーションの設定
			pMotion->SetPartsMotion(file, pMotion, nCntMotion);

			// モーションカウントを加算
			nCntMotion++;
		}
		// "END_SCRIPT"読み取り時
		else if (token == "END_SCRIPT")
		{
			break;
		}
	}

	// ファイルを閉じる
	file.close();

	// 生成されたポインタを返す
	return pMotion;
}
//=================================
// モーションセット
//=================================
void CMotion::SetMotion(int motiontype)
{
	// ここはmotiontypeに渡された番号を取得する
	if (m_motiontype == motiontype)
	{
		// 同じだったら
		return;
	}

	// 代入
	m_motiontype = motiontype;
	m_nKey = 0;
	m_nCounterMotion = 0;
	m_nAllFrameCount = 0;
	m_isFinishMotion = false;
}
//======================================
// モーションセット情報 (ブレンド実験)
//======================================
void CMotion::SetMotion(int nMotionType, bool isBlend, int nBlendFrame,bool isBoss)
{
	// ここはmotiontypeに渡された番号を取得する
	if (m_motiontype == nMotionType)
	{
		// 同じだったら
		return;
	}

	// ブレンドが有効化
	if (isBlend == true)
	{
		// 最初のモーションブレンドが終わってたら
		if (!m_isFirstMotion)
		{
			m_isFirstMotion = true;
			m_nKeyBlend = 0;				// 0から始める
			m_nCounterBlend = 0;			// 0から始める
		}

		m_isBlendMotion = isBlend;			// ブレンドがあるかどうか
		m_nFrameBlend = nBlendFrame;		// ブレンドのフレームを代入
		m_motiontypeBlend = nMotionType;	// ブレンドするモーションのタイプを代入

		if (isBoss == false)
		{
			m_isFinishMotion = false;			// 終了判定を無効化
		}

	}
	// モーションブレンドがない
	else
	{
		// ここはmotiontypeに渡された番号を取得する
		if (m_motiontype == nMotionType)
		{
			// 同じだったら
			return;
		}

		// 代入
		m_motiontype = nMotionType;
		m_nKey = 0;
		m_nCounterMotion = 0;
		m_nAllFrameCount = 0;
		m_isFinishMotion = false;
	}
}
//==============================
// モーション全体更新処理
//==============================
void CMotion::Update(CModel** ppModel, const int nMaxPart)
{// モーションタイプの番号で該当のモーション更新するだけにする

	// モデル数格納
	int nNumModel = nMaxPart;
	
	// 例外処理
	if (nNumModel <= 0)
	{
		// 警告表示
		MessageBox(GetActiveWindow(), "モデルが存在しません", "キャラクターエラー", MB_OK);

		// 下の処理に入らないようにする
		return;
	}

	// 現在モーションキー計算
	m_motiontype = Clump(m_motiontype, 0, m_nNumMotion);
	m_nNextKey = Wrap(m_nKey + 1, 0, m_aMotionInfo[m_motiontype].nNumKey - 1);

	// 最後のキーとブレンドのキーを計算
	int nLastKey = m_aMotionInfo[m_motiontype].nNumKey - 1;

	// フラグを生成
	bool isPlayer = false;
	bool isBoss = false;

	// 最大モデル数で回す
	for (int nCnt = 0; nCnt < nNumModel; nCnt++)
	{
		// モデルのポインタ
		CModel* pModel = ppModel[nCnt];

		// nulなら
		if (!pModel) continue;

		if (pModel->IsPlayer()) isPlayer = true; 	// プレイヤーモデルかどうか判定
		if (pModel->IsBoss()) isBoss = true; 		// ボスモデルかどうか判定


		// ブレンド開始なら
		if (m_isFirstMotion)
		{
			// ブレンドモーションの更新
			UpdateBlend(ppModel, nCnt);
		}
		else
		{
			// 現在のモーション更新
			UpdateCurrentMotion(ppModel, nCnt);
		}
	}

	// フレーム進行処理
	if (m_nCounterMotion >= m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame)
	{
		// カウンターをリセット
		m_nCounterMotion = 0;

		// キー数が上限より一個下
		if (m_nKey < m_aMotionInfo[m_motiontype].nNumKey -1)
		{
			// キー数加算
			m_nKey++;
		}
		else if (m_nKey >= m_aMotionInfo[m_motiontype].nNumKey)
		{
			// キーをリセット
			m_nKey = 0;

			// フレームをリセット
			m_nCounterMotion = 0;
		}
		else
		{
			// 通常ループ
			m_nKey = Wrap(m_nKey + 1, 0, m_aMotionInfo[m_motiontype].nNumKey - 1);
		}
	}
	else
	{
		// ブレンドが開始していなかったら
		if (!m_isFirstMotion)
		{
			// カウンターを加算
			m_nCounterMotion++;
		}

		// 全体フレームカウント
		m_nAllFrameCount++;
	}

	// ブレンドモーションが始まったら
	if (m_isFirstMotion == true)
	{
		// ブレンドモーションカウントをインクリメント
		m_nCounterBlend++;
	}

	// モーションの出だしのブレンドが終了した
	if (m_isFirstMotion == true && m_nCounterBlend >= m_nFrameBlend)
	{
		m_nFrameBlend = 0;

		// フラグをもとに戻す
		m_isFirstMotion = false;

		// モーションをブレンドしたモーションにする
		m_motiontype = m_motiontypeBlend;

		// キーをリセット
		m_nKey = 0;

		// ブレンドしたフレームから開始
		m_nCounterMotion = 0;

		// ブレンドフレーム初期化
		m_nCounterBlend = 0;
	}

	// プレイヤーのモーションがアクション時 かつ 判別しているモデルがプレイヤーなら
	if (isPlayer && m_motiontype == CPlayer::PLAYERMOTION_ACTION)
	{
		// 終了フラグを立てる
		m_isFinishMotion = true;

		// 最後のキーで止める
		m_nKey = m_aMotionInfo[m_motiontype].nNumKey - 2;

		// フレームを最後のキーに設定
		m_nCounterMotion = m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame;

		// ここで関数を抜ける
		return;
	}

	// 着地モーションの終了判定
	if (isPlayer && m_motiontype == CPlayer::PLAYERMOTION_LANDING)
	{
		// 最後のキーに達していて、カウンターも終了フレームを超えていたら
		if (m_nKey >= nLastKey -1&&
			m_nCounterMotion >= m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame)
		{
			m_isFinishMotion = true;
		}
	}

	// ボスの時 かつ 最後のキーのフレームに到達していたら
	if (isBoss)
	{
		// 最後のキーに達していて、カウンターも終了フレームを超えていたら
		if (m_nCounterMotion >= m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame)
		{
			m_isFinishMotion = true;

			m_nCounterMotion = 0;

			return;
		}
	}


	// 全体フレームカウント計算用
	int nFrame = 0;

	// キーごとのフレームで回す
	for (int nCnt = 0; nCnt < m_aMotionInfo[m_motiontype].nNumKey; nCnt++)
	{
		// 全体計算用に加算
		nFrame += m_aMotionInfo[m_motiontype].aKeyInfo[nCnt].nFrame;
	}

	// 最大値よりもカウントがオーバーしたら
	if (m_nAllFrameCount >= m_nNumAllFrame)
	{
		m_nAllFrameCount = 0;
	}

	// 全体フレーム計算
	m_nNumAllFrame = nFrame;
}
//======================================
// 現在のモーションの更新関数
//======================================
void CMotion::UpdateCurrentMotion(CModel** ppModel, int nModelCount)
{
	// モーションデータの取得変数を宣言
	const INFO& motionInfo = m_aMotionInfo[m_motiontype];
	const KEY_INFO& keyInfoNow = motionInfo.aKeyInfo[m_nKey];
	const KEY_INFO& keyInfoNext = motionInfo.aKeyInfo[m_nNextKey];

	// インデックス範囲チェックしオーバーしている場合
	if (nModelCount >= keyInfoNow.aKey.size() || nModelCount >= keyInfoNext.aKey.size())
	{
		return; // 下の処理を通さない
	}

	// 現在と次のキー用の変数を宣言する
	const KEY& NowKey = keyInfoNow.aKey[nModelCount];
	const KEY& NextKey = keyInfoNext.aKey[nModelCount];

	// キー情報から位置と向きを算出
	D3DXVECTOR3 posMotion, rotMotion;

	// 角度と座標の差分を計算
	posMotion.x = NextKey.fPosX - NowKey.fPosX;
	posMotion.y = NextKey.fPosY - NowKey.fPosY;
	posMotion.z = NextKey.fPosZ - NowKey.fPosZ;

	rotMotion.x = NextKey.fRotX - NowKey.fRotX;
	rotMotion.y = NextKey.fRotY - NowKey.fRotY; 
	rotMotion.z = NextKey.fRotZ - NowKey.fRotZ;

	// 求める値を保存する変数を宣言
	D3DXVECTOR3 Pos, Rot;

	// 補間係数を計算
	float fDis = static_cast<float>(m_nCounterMotion) / keyInfoNow.nFrame;

	// 補間結果を算出
	Pos.x = NowKey.fPosX + posMotion.x * fDis;
	Pos.y = NowKey.fPosY + posMotion.y * fDis;
	Pos.z = NowKey.fPosZ + posMotion.z * fDis;

	Rot.x = NowKey.fRotX + rotMotion.x * fDis;
	Rot.y = NowKey.fRotY + rotMotion.y * fDis;
	Rot.z = NowKey.fRotZ + rotMotion.z * fDis;

	// モデルのパーツに設定
	ppModel[nModelCount]->SetPos(Pos);
	ppModel[nModelCount]->SetRot(Rot);
}

//======================================
// ブレンドモーションの更新関数
//======================================
void CMotion::UpdateBlend(CModel** ppModel, int nModelCount)
{
	// ブレンド係数を計算
	float fBlendFrame = static_cast<float>(m_nCounterBlend) / static_cast<float>(m_nFrameBlend);
	float fRateMotion = static_cast<float>(m_nCounterMotion) / static_cast<float>(m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame);

	// 現在のキーと次のキーを取得
	const KEY& nowKey = m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].aKey[nModelCount];
	const KEY& nextKey = m_aMotionInfo[m_motiontype].aKeyInfo[m_nNextKey].aKey[nModelCount];

	const KEY& nowKeyBlend = m_aMotionInfo[m_motiontypeBlend].aKeyInfo[m_nKeyBlend].aKey[nModelCount];
	const KEY& nextKeyBlend = m_aMotionInfo[m_motiontypeBlend].aKeyInfo[m_nNextKeyBlend].aKey[nModelCount];

	//==========================
	// 現在モーションの補間計算
	//==========================
	D3DXVECTOR3 DiffRot = VECTOR3_NULL; // 角度
	D3DXVECTOR3	CurrentRot = VECTOR3_NULL; // 現在角度

	// 角度を計算する
	DiffRot.x = nextKey.fRotX - nowKey.fRotX;
	DiffRot.y = nextKey.fRotY - nowKey.fRotY;
	DiffRot.z = nextKey.fRotZ - nowKey.fRotZ;

	// 角度を正規化
	// NorRot(&DiffRot.x, &DiffRot.y, &DiffRot.z);

	// 現在角度に適用
	CurrentRot.x = nowKey.fRotX + DiffRot.x * fRateMotion;
	CurrentRot.y = nowKey.fRotY + DiffRot.y * fRateMotion;
	CurrentRot.z = nowKey.fRotZ + DiffRot.z * fRateMotion;

	// 座標を計算
	D3DXVECTOR3 DiffPos = VECTOR3_NULL; // 座標
	D3DXVECTOR3	CurrentPos = VECTOR3_NULL; // 現在座標

	// 座標計算
	DiffPos.x = nextKey.fPosX - nowKey.fPosX;
	DiffPos.y = nextKey.fPosY - nowKey.fPosY;
	DiffPos.z = nextKey.fPosZ - nowKey.fPosZ;

	// 現在座標に適用
	CurrentPos.x = nowKey.fPosX + DiffPos.x * fRateMotion;
	CurrentPos.y = nowKey.fPosY + DiffPos.y * fRateMotion;
	CurrentPos.z = nowKey.fPosZ + DiffPos.z * fRateMotion;

	//===============================
	// ブレンドモーションの補間計算
	//===============================
	D3DXVECTOR3 DiffBlendRot = VECTOR3_NULL; // 角度
	D3DXVECTOR3	BlendRot = VECTOR3_NULL;	 // ブレンド角度

	// ブレンド角度を計算
	DiffBlendRot.x = nextKeyBlend.fRotX - nowKeyBlend.fRotX;
	DiffBlendRot.y = nextKeyBlend.fRotY - nowKeyBlend.fRotY;
	DiffBlendRot.z = nextKeyBlend.fRotZ - nowKeyBlend.fRotZ;

	// 角度を正規化
	// NorRot(&DiffBlendRot.x, &DiffBlendRot.y, &DiffBlendRot.z);

	// ブレンドの角度を適用
	BlendRot.x = nowKeyBlend.fRotX + DiffBlendRot.x * fBlendFrame;
	BlendRot.y = nowKeyBlend.fRotY + DiffBlendRot.y * fBlendFrame;
	BlendRot.z = nowKeyBlend.fRotZ + DiffBlendRot.z * fBlendFrame;

	D3DXVECTOR3 DiffBlendPos = VECTOR3_NULL; // 座標
	D3DXVECTOR3	BlendPos = VECTOR3_NULL;	 // ブレンド座標

	// ブレンド座標を計算
	DiffBlendPos.x = nextKeyBlend.fPosX - nowKeyBlend.fPosX;
	DiffBlendPos.y = nextKeyBlend.fPosY - nowKeyBlend.fPosY;
	DiffBlendPos.z = nextKeyBlend.fPosZ - nowKeyBlend.fPosZ;

	// ブレンドの座標を適用
	BlendPos.x = nowKeyBlend.fPosX + DiffBlendPos.x * fBlendFrame;
	BlendPos.y = nowKeyBlend.fPosY + DiffBlendPos.y * fBlendFrame;
	BlendPos.z = nowKeyBlend.fPosZ + DiffBlendPos.z * fBlendFrame;

	//===============================
	// モデルの座標,角度に適用
	//===============================

	// 最終角度,座標
	D3DXVECTOR3 LastRot = VECTOR3_NULL;
	D3DXVECTOR3 LastPos = VECTOR3_NULL;

	// 角度計算
	LastRot.x = CurrentRot.x + (BlendRot.x - CurrentRot.x) * fBlendFrame;
	LastRot.y = CurrentRot.y + (BlendRot.y - CurrentRot.y) * fBlendFrame;
	LastRot.z = CurrentRot.z + (BlendRot.z - CurrentRot.z) * fBlendFrame;

	// 座標計算
	LastPos.x = CurrentPos.x + (BlendPos.x - CurrentPos.x) * fBlendFrame;
	LastPos.y = CurrentPos.y + (BlendPos.y - CurrentPos.y) * fBlendFrame;
	LastPos.z = CurrentPos.z + (BlendPos.z - CurrentPos.z) * fBlendFrame;

	//===============================
	// モデルにセット
	//===============================
	ppModel[nModelCount]->SetPos(LastPos);
	ppModel[nModelCount]->SetRot(LastRot);
}

//======================================
// デバッグフォント関数
//======================================
void CMotion::Debug(void)
{
	CDebugproc::Print("[現在フレームカウント] %d /  [ 最大モーションフレーム ] %d", m_nAllFrameCount, m_nNumAllFrame);
	CDebugproc::Draw(800, 320);

	CDebugproc::Print("[ブレンドフレーム] %d / [ブレンドカウント] %d", m_nFrameBlend,m_nCounterBlend);
	CDebugproc::Draw(800, 340);

	CDebugproc::Print("[ キー数 ] %d  / [ 最大キー数] %d ",m_nKey, m_aMotionInfo[m_motiontype].nNumKey);
	CDebugproc::Draw(800, 360);
}

//======================================
// モデル数読み込み
//======================================
void CMotion::SetModels(std::istringstream& iss, int& nModel, int nMaxParts)
{
	// 文字列設定
	std::string eq;

	// 読み込んだモデル数を設定
	iss >> eq >> nModel;

	// 例外処理
	if (nModel > nMaxParts)
	{
		MessageBox(NULL, "最大モデル数を超えています", "モデル数エラー", MB_OK);

		return;
	}
}
//======================================
// モデルファイル読み込み
//======================================
void CMotion::SetModelFile(std::istringstream& iss, CModel** pModel, int nCnt)
{
	// 読み込み用文字列
	std::string eq, filename;

	// ファイルから読み込んだものを設定
	iss >> eq >> filename;

	// モデルの生成処理
	CModel* pNewModel = CModel::Create(VECTOR3_NULL, VECTOR3_NULL, filename.c_str());

	// モデルのポインタに格納
	pModel[nCnt] = pNewModel;
}
//======================================
// パーツごとの設定
//======================================
void CMotion::SetParts(std::ifstream& file, CModel** pModel)
{
	// 読み込み文字列
	std::string line;

	// モデル番号と親モデルの設定用変数
	int nIdx = -1, nParentIdx = -1;

	// 代入用座標と角度
	D3DXVECTOR3 pos = VECTOR3_NULL;
	D3DXVECTOR3 rot = VECTOR3_NULL;

	// 読み込みループ
	while (std::getline(file, line))
	{
		std::istringstream partss(line);
		std::string cmd;
		partss >> cmd;

		// "INDEX"を読み取った
		if (cmd == "INDEX")
		{
			// インデックスの変数に値を代入
			std::string eq; 
			partss >> eq >> nIdx;
		}
		// "PARENT"を読み取った
		else if (cmd == "PARENT")
		{
			// 親モデル設定用の変数に値を代入
			std::string eq;
			partss >> eq >> nParentIdx;

			// インデックスの範囲内なら
			if (nIdx >= 0 && pModel[nIdx])
			{
				if (nParentIdx != -1)
				{// 親モデルが存在する
					pModel[nIdx]->SetParent(pModel[nParentIdx]);
				}
				else
				{// 親モデルが存在しない
					pModel[nIdx]->SetParent(nullptr);
				}
			}	
		}
		// "POS"を読み取った
		else if (cmd == "POS")
		{
			// 読み取った座標を代入
			std::string eq; 
			partss >> eq >> pos.x >> pos.y >> pos.z;

			// 範囲内かチェック
			if (nIdx >= 0 && pModel[nIdx])
			{
				// モデルのオフセット座標に値を設定
				pModel[nIdx]->OffSetPos(pos);
			}
		}
		// "ROT"を読み取った
		else if (cmd == "ROT")
		{
			// 読み取った角度を代入
			std::string eq; 
			partss >> eq >> rot.x >> rot.y >> rot.z;

			// 範囲内かチェック
			if (nIdx >= 0 && pModel[nIdx])
			{
				// モデルのオフセット角度に値を設定
				pModel[nIdx]->OffSetRot(rot);
			}
		}
		// "PARTTYPE"を読み取った
		else if (cmd == "PARTTYPE")
		{
			// 読み取った種類を代入する
			std::string eq, partTypeStr;
			partss >> eq >> partTypeStr;

			// インデックスが0以上 かつ モデルがあるなら
			if (nIdx >= NULL && pModel[nIdx])
			{
				if (partTypeStr == "WEAPON") // 武器の部位
				{ 
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_WEAPON); 
				}
				else if (partTypeStr == "RIGHTHAND") // 右手
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_RIGHT_HAND);
				}
				else if (partTypeStr == "LEFTHAND") // 左手
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_LEFT_HAND);
				}
				else if (partTypeStr == "HEAD") // 頭
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_HEAD);
				}
				else 
				{
					// 無いとき
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_NONE); 
				}
			}
		}
		// "END_PARTSSET"を読み取った
		else if (cmd == "END_PARTSSET")
		{
			// 抜ける
			break;
		}
	}
}
//======================================
// パーツごとのモーション設定
//======================================
void CMotion::SetPartsMotion(std::ifstream& file, CMotion* pMotion, int nCntMotion)
{
	// 読み込み用1行分のバッファ
	std::string line;

	// キーセット数のカウント用変数
	int nCntKey = 0;

	// モーション設定の読み取りループ
	while (std::getline(file, line))
	{
		// 行データを分解してトークンを解析
		std::istringstream motionss(line);
		std::string token;
		motionss >> token;

		// "LOOP"を読み取った
		if (token == "LOOP")
		{
			std::string eq;
			int loopFlag;
			motionss >> eq >> loopFlag;

			// "="を読み取った
			if (eq == "=")
			{
				// モーションループフラグを設定
				pMotion->m_aMotionInfo[nCntMotion].bLoop = loopFlag;
			}
		}
		// "NUM_KEY"を読み取った
		else if (token == "NUM_KEY")
		{
			// "="代入
			std::string eq;
			
			// キー数保存
			int numKeys;

			// 値代入
			motionss >> eq >> numKeys;

			// nNumKeyを代入
			pMotion->m_aMotionInfo[nCntMotion].nNumKey = numKeys;

			// 上の処理でそのモーションのキー全体が上の処理でわかるのでその分のサイズを設定
			pMotion->m_aMotionInfo[nCntMotion].aKeyInfo.resize(numKeys);

			//	キー数の上限に達するまで
			while (nCntKey < numKeys)
			{
				// aKeyInfoのサイズがわかったらキーごとにあるパーツの情報をakeyにサイズセットをして箱を確保してあげる
				pMotion->m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey.resize(m_nNumModels); // m_nNumModelsは最大モデル数

				// キー情報の設定
				SetKey(file, pMotion, nCntMotion, nCntKey);

				// インクリメントして進める
				nCntKey++;
			}
		}
		// "END_MOTIONSET"を読み取った
		else if (token == "END_MOTIONSET")
		{
			nCntKey = 0;
			break;
		}
	}
}
//======================================
// モーションキー全体の設定
//======================================
void CMotion::SetKey(std::ifstream& file, CMotion* pMotion, int nCntMotion, int nCntKey)
{
	// 行読み込み
	std::string line;

	// 使用変数
	int frame = 0;
	int posKeyIndex = 0, rotKeyIndex = 0;

	// 読んだかフラグ
	bool ReadKey = false;

	// FRAME 行の読み込み
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string cmd, eq;
		ss >> cmd >> eq >> frame;

		// 読み取り一致時
		if (cmd == "FRAME" && eq == "=")
		{
			pMotion->m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = frame;
			break;
		}
	}

	// 読み込みループ
	while (std::getline(file, line))
	{
		if (line.find("END_KEYSET") != std::string::npos)
		{
			// キーセット終了
			break;
		}
		else if (line.find("KEY") != std::string::npos)
		{
			// 有効化
			ReadKey = true;

			// while継続
			continue;
		}
		else if (ReadKey)
		{
			std::istringstream ss(line);
			std::string param;
			ss >> param;

			if (param == "POS" || param == "ROT")
			{
				// 各キーごとの設定
				SetKeyDate(ss, param, pMotion, nCntMotion, nCntKey, posKeyIndex, rotKeyIndex);
			}
			else if (param == "END_KEY")
			{
				// 条件を無効化
				ReadKey = false;
			}
		}
	}
}
//======================================
// キーごとの情報設定
//======================================
void CMotion::SetKeyDate(std::istringstream& ss, const std::string& param, CMotion* pMotion, int nCntMotion, int nCntKey, int& posKeyIndex, int& rotKeyIndex)
{
	// 読み込み用1行分のバッファ
	std::string eq;

	// 代入用変数
    D3DXVECTOR3 Vec = VECTOR3_NULL;

	// 座標を代入
    ss >> eq >> Vec.x >> Vec.y >> Vec.z;

	// "="が来たら
    if (eq != "=") return;

	// キー情報変数に代入する
    KEY_INFO& keyInfo = pMotion->m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey];

	// "POS"読み取り時
	if (param == "POS") 
	{
		// 各座標に代入する
		keyInfo.aKey[posKeyIndex].fPosX = Vec.x;
		keyInfo.aKey[posKeyIndex].fPosY = Vec.y;
		keyInfo.aKey[posKeyIndex].fPosZ = Vec.z;

		// キー情報カウントを加算
		posKeyIndex++;
	}
	// "ROT"読み取り時
	else if (param == "ROT")
	{
		// 各パーツの角度に代入
		keyInfo.aKey[rotKeyIndex].fRotX = Vec.x;
		keyInfo.aKey[rotKeyIndex].fRotY = Vec.y;
		keyInfo.aKey[rotKeyIndex].fRotZ = Vec.z;

		// キー情報カウントを加算
		rotKeyIndex++;
	}
}
//======================================
// モーションフレーム判定
//======================================
bool CMotion::CheckFrame(int nStartMotion, int nEndMotion, int nMotionType)
{
	// StartとEndの範囲内なら
	if (m_nAllFrameCount >= nStartMotion && m_nAllFrameCount <= nEndMotion && m_motiontype == nMotionType)
		return true;

	// それ以外の時
	return false;
}
//======================================
// 角度の正規化
//======================================
void CMotion::NorRot(float* pRotX, float* pRotY, float* pRotZ)
{
	// 角度の正規化
	if (*pRotX > D3DX_PI)
	{
		*pRotX += -D3DX_PI * 2.0f;
	}
	else if (*pRotX < -D3DX_PI)
	{
		*pRotX += D3DX_PI * 2.0f;
	}

	if (*pRotY > D3DX_PI)
	{
		*pRotY += -D3DX_PI * 2.0f;
	}
	else if (*pRotY < -D3DX_PI)
	{
		*pRotY += D3DX_PI * 2.0f;
	}

	if (*pRotZ > D3DX_PI)
	{
		*pRotZ += -D3DX_PI * 2.0f;
	}
	else if (*pRotZ < -D3DX_PI)
	{
		*pRotZ += D3DX_PI * 2.0f;
	}
}
//// Loopがfalse かつ キー数が超えたら
//if (!m_aMotionInfo[m_motiontype].bLoop && m_aMotionInfo[m_motiontype].nNumKey -1 <= m_nKey)
//{
//	// モーションカウントを初期化
//	m_nCounterMotion = 0;

//	// キー数を初期化
//	m_nKey = 0;

//	// ニュートラルにする
//	SetMotion(NEUTRAL, true, 40,isBoss);
//}
