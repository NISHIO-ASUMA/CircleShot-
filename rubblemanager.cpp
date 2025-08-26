//=================================================
//
// 瓦礫オブジェクト管理処理 [ rubblemanager.cpp ]
// Author : Asuma Nishio
//
//=================================================

//**********************************
// インクルードファイル
//**********************************
#include "rubblemanager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//**********************************
// 静的メンバ変数宣言
//**********************************
std::vector<CRubble*>CRubbleManager::m_rubbles = {}; // 動的配列
int CRubbleManager::m_nIdxCount = NULL;	// インデックスカウント

//=====================================
// コンストラクタ
//=====================================
CRubbleManager::CRubbleManager()
{
	// 値のクリア
	m_rubbles.clear();
}
//=====================================
// デストラクタ
//=====================================
CRubbleManager::~CRubbleManager()
{
	// 無し
}
//=====================================
// 初期化処理
//=====================================
HRESULT CRubbleManager::Init(void)
{
	// 値のクリア
	m_rubbles.clear();

	// ファイル読み込み
	Load();

	// 初期化結果を返す
	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CRubbleManager::Uninit(void)
{
	// 値のクリア
	m_rubbles.clear();
}
//=====================================
// 更新処理
//=====================================
void CRubbleManager::Update(void)
{
	// 無し
}
//=====================================
// ファイル読み込み関数
//=====================================
void CRubbleManager::Load(void)
{
	// 読み込むファイルパスを設定
	std::ifstream loadFile(FILEPASS);
	
	// ファイル例外チェック
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", FILEPASS, MB_OK);
		return;
	}
	
	// 読み込む行を設定
	std::string loadline;
	
	int nNumAll = NULL; // 総数
	
	// NUM_RUBBLES 読み取り
	while (std::getline(loadFile, loadline))
	{
		std::istringstream iss(loadline);
		std::string token;
		iss >> token;

		if (token == "NUM_RUBBLES")
		{
			std::string eq;
			iss >> eq >> nNumAll;
			break;
		}
	}

	// オブジェクト情報を順に読み込む
	for (int nCnt = 0; nCnt < nNumAll; nCnt++)
	{
		D3DXVECTOR3 pos = VECTOR3_NULL;
		D3DXVECTOR3 rot = VECTOR3_NULL;
		std::string filePath;

		bool inSetting = false;

		while (std::getline(loadFile, loadline))
		{
			// 空行,コメントスキップ
			if (loadline.empty() || loadline[0] == '#') continue;

			std::istringstream iss(loadline);
			std::string token;
			iss >> token;

			if (token == "SETTING")
			{
				// 生成可能状態に変更
				inSetting = true;
			}
			else if (token == "POS")
			{
				std::string eq;

				iss >> eq >> pos.x >> pos.y >> pos.z; // 座標代入
			}
			else if (token == "ROT")
			{
				std::string eq;

				iss >> eq >> rot.x >> rot.y >> rot.z; // 角度代入
			}
			else if (token == "FILEPASS")
			{
				std::string eq;

				iss >> eq >> filePath; // モデルファイルパス
			}
			else if (token == "END_SETTING" && inSetting)
			{
				// オブジェクト生成
				CRubbleManager::Create(pos, rot, filePath.c_str());

				// 次のオブジェクトへ
				break; 
			}
		}
	}

	// ファイルを閉じる
	loadFile.close();
}
//=====================================
// 生成処理
//=====================================
CRubble* CRubbleManager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// インスタンス生成
	CRubble* pNewBlock = CRubble::Create(pos,rot,pFilename);

	// インスタンスの生成ができたら
	if (pNewBlock)
	{
		// 配列に追加
		m_rubbles.push_back(pNewBlock);

		// インデックス
		m_nIdxCount++;

		// 生成されたポインタを返す
		return pNewBlock;
	}
	else
	{
		// 何にもないポインタを返す
		return nullptr;
	}
}
