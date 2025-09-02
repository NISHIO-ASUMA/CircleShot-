//=========================================
//
// ゲーム管理処理 [ gamemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// インクルードファイル宣言
//***************************
#include "gamemanager.h"
#include "manager.h"
#include "debugproc.h"
#include "score.h"
#include "time.h"
#include "meshdome.h"
#include "meshfield.h"
#include "player.h"
#include "meshimpact.h"
#include "playerlifegage.h"
#include "bosslifegage.h"
#include "parameter.h"
#include "result.h"
#include "sound.h"
#include "item.h"
#include "barrierdurability.h"
#include "bullethorming.h"
#include "itemmanager.h"
#include "effectlaser.h"
#include "charge.h"
#include "sceneloader.h"
#include <fstream>
#include <iostream>
#include <sstream>

//**************************
// 静的メンバ変数宣言
//**************************
CMeshCylinder* CGameManager::m_pMeshCylinder = nullptr;	// 円柱
CBoss* CGameManager::m_pBoss = nullptr;					// ボス
CTime* CGameManager::m_pTime = nullptr;					// タイマー
CUimanager* CGameManager::m_puimanager = nullptr;		// UIマネージャー
CBarrierManager* CGameManager::m_pBarrier = nullptr;	// バリアマネージャー
CRubbleManager* CGameManager::m_pRubble = nullptr;

//========================
// コンストラクタ
//========================
CGameManager::CGameManager()
{
	// 値のクリア
}
//========================
// デストラクタ
//========================
CGameManager::~CGameManager()
{
	// 無し
}
//========================
// 初期化処理
//========================
HRESULT CGameManager::Init(void)
{
	// シリンダー生成
	m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 550.0f);

	// ボス生成
	m_pBoss = CBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f), 60.0f, 1000);

	// タイマー生成
	m_pTime = CTime::Create(D3DXVECTOR3(150.0f, 50.0f, 0.0f), 80.0f, 50.0f);

	// シーンオブジェクト読み込み
	CSceneLoader::SplitLoad(1);

	// ファイル情報
	// CGameManager::Load();

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// nullだったら
	if (pSound == nullptr) return E_FAIL;

	 // サウンド再生
	 pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);

	// バリアマネージャー生成
	 m_pBarrier = new CBarrierManager;

	// nullじゃなかったら初期化
	if (m_pBarrier != nullptr)
	{
		// 初期化処理
		m_pBarrier->Init();
	}

	// uiマネージャー生成
	m_puimanager = new CUimanager;

	// nullじゃなかったら初期化
	if (m_puimanager != nullptr)
	{
		// 初期化処理
		m_puimanager->Init();
	}

	// 瓦礫オブジェクトマネージャー生成
	m_pRubble = new CRubbleManager;

	// nullじゃなかったら初期化
	if (m_pRubble != nullptr)
	{
		// 初期化処理
		m_pRubble->Init();
	}

	// アイテムマネージャー生成
	m_pItemManager = new CItemManager;

	// nullじゃなかったら
	if (m_pItemManager != nullptr)
	{
		// 初期化処理
		m_pItemManager->Init();
	}

	// 初期化結果を返す
	return S_OK;
}
//========================
// 終了処理
//========================
void CGameManager::Uninit(void)
{
	// 使用したポインタのnull初期化
	m_pBoss = nullptr;
	m_pMeshCylinder = nullptr;
	m_pTime = nullptr;

	// nullじゃなかったら
	if (m_puimanager != nullptr)
	{
		// 終了処理
		m_puimanager->Uninit();

		// ポインタの破棄
		delete m_puimanager;

		// null初期化
		m_puimanager = nullptr;
	}

	// nullじゃなかったら
	if (m_pBarrier != nullptr)
	{
		// 終了処理
		m_pBarrier->Uninit();

		// ポインタの破棄
		delete m_pBarrier;

		// null初期化
		m_pBarrier = nullptr;
	}

	// nullじゃなかったら
	if (m_pRubble != nullptr)
	{
		// 終了処理
		m_pRubble->Uninit();

		// ポインタの破棄
		delete m_pRubble;

		// null初期化
		m_pRubble = nullptr;
	}

	// nullじゃなかったら
	if (m_pItemManager != nullptr)
	{
		// 終了処理
		m_pItemManager->Uninit();

		// ポインタの破棄
		delete m_pItemManager;

		// null初期化
		m_pItemManager = nullptr;
	}
}
//========================
// 更新処理
//========================
void CGameManager::Update(void)
{
	// nullじゃなかったら
	if (m_pBarrier != nullptr)
	{
		// 更新処理
		m_pBarrier->Update();
	}

	// nullじゃなかったら
	if (m_pItemManager != nullptr)
	{
		// 更新処理
		m_pItemManager->Update();
	}
#ifdef _DEBUG

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_O))
	{
		CBulletHorming::Create("data\\MODEL\\ATTACKMODEL\\bulletobject000.x", D3DXVECTOR3(0.0f, 300.0f, 0.0f));
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_L))
	{
		// ファイル処理
		m_pRubble->LoadSplitFile(m_pRubble->FILETYPE_SMALL);
	}

	if (CManager::GetInputKeyboard()->GetPress(DIK_Y))
	{
		// レーザーエフェクト生成
		// CEffectLaser::Create(D3DXVECTOR3(0.0f, 50.0f, -550.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), LASER, 30.0f, 150, 50.0f);
		// CEffectLaser::Create(D3DXVECTOR3(0.0f, 10.0f, -550.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), COLOR_WHITE, 10.0f, 150, 30.0f);
		// CEffectLaser::Create(D3DXVECTOR3(0.0f, 50.0f, -550.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), LASER, 30.0f, 100, 30.0f);

	}

	// jキー
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_J))
	{
		// カメラ
		CCamera* pCamera = CManager::GetCamera();

		// プレイヤー取得
		CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
		if (pPlayer == nullptr) return;

		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		// 後方距離と高さ
		float backDistance = 550.0f;
		float heightOffset = 150.0f;

		// プレイヤーの向きの逆方向を取得
		float rotY = pPlayer->GetRotDest().y;
		D3DXVECTOR3 backwardVec = D3DXVECTOR3(-sinf(rotY), 0.0f, -cosf(rotY));

		// カメラ位置
		D3DXVECTOR3 camPos = playerPos + backwardVec * backDistance;
		camPos.y += heightOffset; // プレイヤーより少し上くらい

		// 注視
		D3DXVECTOR3 targetPos = playerPos + D3DXVECTOR3(0.0f, 250.0f, 0.0f); // Yを大きくして見上げる

		// カメラチェンジ
		pCamera->SetCameraMode(pCamera->MODE_EVENT);

		// イベントカメラ開始
		pCamera->StartEventCamera(camPos, targetPos, 200);

		// カメラの振動
		pCamera->ShakeCamera(195);
	}

#endif // _DEBUG

}
//========================
// 読み込み処理
//========================
void CGameManager::Load(void)
{
	// 指定ファイルを開く
	std::ifstream loadFile("data\\SceneText\\GameObj.txt");

	// もしファイルが開けない場合
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", "data\\SceneText\\GameObj.txt", MB_OK);

		return;
	}

	// ローカル変数
	std::string line;
	int nNumObj = NULL;

	// 読み込んだ名前
	std::string objName, motionPath, filePath, createType;

	// 読み込み情報格納
	D3DXVECTOR3 pos = VECTOR3_NULL;
	D3DXVECTOR3 rot = VECTOR3_NULL;
	int life = 0;
	float radius = 0.0f;
	float size = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
	int index = -1, type = -1, category = -1;

	// 読み込み終わりまで回す
	while (std::getline(loadFile, line))
	{
		// コメント飛ばし
		if (line.empty() || line[0] == '#') continue;

		// ファイルの読み込むラインを選択
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "OBJNAME")
		{// "FILENAME"読み取り時

			// 初期化して新しいオブジェクト開始
			objName.clear(); motionPath.clear(); filePath.clear(); createType.clear();

			pos = VECTOR3_NULL; 
			rot = VECTOR3_NULL;

			life = 0;

			radius = size = width = height = 0.0f;

			index = type = category = -1;

			std::string eq;

			iss >> eq >> objName;
		}
		else if (token == "POS")
		{
			std::string eq;
			iss >> eq >> pos.x >> pos.y >> pos.z;
		}
		else if (token == "ROT")
		{
			std::string eq;
			iss >> eq >> rot.x >> rot.y >> rot.z;
		}
		else if (token == "LIFE")
		{
			std::string eq;
			iss >> eq >> life;
		}
		else if (token == "INDEX")
		{
			std::string eq;
			iss >> eq >> index;
		}
		else if (token == "MOTIONPASS")
		{
			std::string eq;
			iss >> eq >> motionPath;
		}
		else if (token == "FILEPASS")
		{
			std::string eq;
			iss >> eq >> filePath;
		}
		else if (token == "TYPE")
		{
			std::string eq;
			iss >> eq >> type;
		}
		else if (token == "RADIUS")
		{
			std::string eq;
			iss >> eq >> radius;
		}
		else if (token == "SIZE")
		{
			std::string eq;
			iss >> eq >> size;
		}
		else if (token == "CREATETYPE")
		{
			std::string eq;
			iss >> eq >> createType;
		}
		else if (token == "WIDTH")
		{
			std::string eq;
			iss >> eq >> width;
		}
		else if (token == "HEIGHT")
		{
			std::string eq;
			iss >> eq >> height;
		}
		else if (token == "CATEGORY")
		{
			std::string eq;
			iss >> eq >> category;
		}
		else if (token == "ENDSET")
		{
			// 各種生成
			if (objName == "PLAYER")
			{
				// プレイヤー
				CPlayer::Create(pos, rot, life, index, motionPath.c_str());

				motionPath.clear();
			}
			else if (objName == "MESH")
			{
				// メッシュ
				if (type == 0) CMeshDome::Create(pos, radius);

				else if (type == 1) CMeshField::Create(pos, radius);
			}
			else if (objName == "BLOCK")
			{
				// ブロック
				CBlock::Create(filePath.c_str(), pos, rot, size);

				filePath.clear();
			}
			else if (objName == "UI")
			{
				if (createType == "PLAYER")
				{
					CPlayerLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "BOSS")
				{
					CBossLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "LASER")
				{
					CCharge::Create(pos, width, height, category);
				}
			}
		}
	}

	// ファイルを閉じる
	loadFile.close();
}

#if 0

//// プレイヤー生成
//// ドーム生成
//CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

//// ドーム生成
//CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);

//// フィールド生成
//CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

//CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 0, "data\\MOTION\\Player\\Player100motion.txt");
//CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 1, "data\\MOTION\\Player\\Player200motion.txt");

////地面ブロック配置
//CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

//// プレイヤー体力ゲージ生成
//CPlayerLifeGage::Create(D3DXVECTOR3(95.0f, 38.0f, 0.0f), 0.0f, 0.0f, CPlayerLifeGage::GAGE_BAR);
//CPlayerLifeGage::Create(D3DXVECTOR3(3.0f, 0.0f, 0.0f), 450.0f, 100.0f, CPlayerLifeGage::GAGE_FRAME);

//// ボス体力ゲージ生成
//CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), 0.0f, 0.0f, CBossLifeGage::TYPE_GAGE);
//CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), SCREEN_WIDTH * 0.4f, 60.0f, CBossLifeGage::TYPE_FRAME);

//// レーザーゲージ生成
//CCharge::Create(D3DXVECTOR3(138.0f, 98.0f, 0.0f), 0.0f, 0.0f, CCharge::CHARGE_BAR);
//CCharge::Create(D3DXVECTOR3(0.0f, 95.0f, 0.0f), 450.0f, 45.0f, CCharge::CHARGE_FRAME);

#endif