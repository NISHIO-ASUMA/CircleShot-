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
	m_SubListFiles.clear();
	m_nUseType = FILETYPE_SMALL;
}
//=====================================
// デストラクタ
//=====================================
CRubbleManager::~CRubbleManager()
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CRubble* CRubbleManager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// インスタンス生成
	CRubble* pNewRubble = CRubble::Create(pos, rot, pFilename);

	// インスタンスの生成ができたら
	if (pNewRubble)
	{
		// 配列に追加
		m_rubbles.push_back(pNewRubble);

		// インデックス
		m_nIdxCount++;

		// 生成されたポインタを返す
		return pNewRubble;
	}
	else
	{
		// 何にもないポインタを返す
		return nullptr;
	}
}

//=====================================
// 初期化処理
//=====================================
HRESULT CRubbleManager::Init(void)
{
	// 値のクリア
	m_rubbles.clear();
	m_SubListFiles.clear();

	// 全リストファイル読み込み
	CRubbleManager::LoadAllList(FILEPASS);

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
	m_SubListFiles.clear();
}
//=====================================
// 更新処理
//=====================================
void CRubbleManager::Update(void)
{
	// 無し
}
//=====================================
// 全ファイルリスト読み込み処理
//=====================================
void CRubbleManager::LoadAllList(const char* pFileList)
{
	// 指定ファイルを開く
	std::ifstream loadFile(pFileList);

	// もしファイルが開けない場合
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", pFileList, MB_OK);

		return;
	}

	// ローカル変数
	std::string line;
	int nNumFile = NULL;

	// 配列のクリア処理
	m_SubListFiles.clear();

	// 読み込み終わりまで回す
	while (std::getline(loadFile, line))
	{
		// ファイルの読み込むラインを選択
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_FILE")
		{// "NUM_FILE"読み取り時

			// "="の時
			std::string eq;

			// 代入
			iss >> eq >> nNumFile;

			// ファイル配列のサイズを確保
			m_SubListFiles.reserve(nNumFile);

		}
		else if (token == "FILENAME")
		{// "FILENAME"読み取り時

			// パスと"="を代入
			std::string eq, filepath;

			// ファイルパスを変数に格納
			iss >> eq >> filepath;

			// 動的配列に追加
			m_SubListFiles.push_back(filepath);
		}
	}

	// ファイルを閉じる
	loadFile.close();
}
//=====================================
// 分割ファイル読み込み処理
//=====================================
void CRubbleManager::LoadSplitFile(FILETYPE type)
{
	// 種類番号が0以下 または ファイルサイズを超過するとき
	if (type < 0 || type >= m_SubListFiles.size()) return;

	// 読み込むファイルのタイプを保存する
	const std::string& FilePath = m_SubListFiles[type];

	// ファイルを開く
	std::ifstream loadFile(FilePath);

	// もしファイルが開けない場合
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", FilePath.c_str(), MB_OK);
		return;
	}

	// ローカル変数宣言
	std::string line;
	int nNumRubbles = NULL;

	// 読み込み終わりまで回す
	while (std::getline(loadFile, line))
	{
		// 行読み込み
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_RUBBLES")
		{// NUM_RUBBLES 読み取り

			// "="の時
			std::string eq;

			// 値を代入
			iss >> eq >> nNumRubbles;

			// while終了
			break;
		}
	}

	// 読み込んだオブジェクト情報読み込み
	for (int nCnt = 0; nCnt < nNumRubbles; nCnt++)
	{
		// ローカル変数宣言
		D3DXVECTOR3 pos = VECTOR3_NULL;
		D3DXVECTOR3 rot = VECTOR3_NULL;
		std::string filePath;

		// 生成可能フラグ
		bool inSetting = false;

		// 読み込み終わりまで回す
		while (std::getline(loadFile, line))
		{
			// コメントの文字が来たら
			if (line.empty() || line[0] == '#') continue;

			// 行読み込み
			std::istringstream iss(line);
			std::string token;
			iss >> token;

			if (token == "SETTING")
			{// "SETTING"読み取り時

				// 生成フラグを有効化
				inSetting = true;
			}
			else if (token == "POS")
			{// "POS"読み取り時

				// "="の時
				std::string eq;

				// 値を代入
				iss >> eq >> pos.x >> pos.y >> pos.z;
			}
			else if (token == "ROT")
			{// "ROT"読み取り時

				// "="の時
				std::string eq;

				// 値を代入
				iss >> eq >> rot.x >> rot.y >> rot.z;
			}
			else if (token == "FILEPASS")
			{// "FILEPASS"読み取り時

				// "="の時
				std::string eq;

				// ファイルパスを格納
				iss >> eq >> filePath;
			}
			else if (token == "END_SETTING" && inSetting)
			{// "END_SETTING"読み取り時 かつ 生成フラグが有効なら

				// オブジェクト生成
				CRubbleManager::Create(pos, rot, filePath.c_str());

				break; // 次のオブジェクトへ
			}
		}
	}

	// ファイルを閉じる
	loadFile.close();
}
//=====================================
// 分割ファイル書き出し処理
//=====================================
void CRubbleManager::SaveSplitFile(const char* pFileList)
{
	// 書き出すファイルを選択する
	std::ofstream ofs(pFileList);

	// nullなら
	if (!ofs)
	{
		MessageBox(NULL, "ファイル書き込み失敗", pFileList, MB_OK);

		return;
	}

	// 書き出し情報
	ofs << "//==========================================================\n";
	ofs << "// 出現するオブジェクトの数\n";
	ofs << "//==========================================================\n";
	ofs << "NUM_RUBBLES  = " << m_rubbles.size() << "\n\n";

	ofs << "//==========================================================\n";
	ofs << "// 各オブジェクト情報\n";
	ofs << "//==========================================================\n\n";

	for (int nCnt = 0; nCnt < m_rubbles.size(); nCnt++)
	{
		// モデルのポインタ
		CRubble* pRubble = m_rubbles[nCnt];

		if (!pRubble) continue;

		D3DXVECTOR3 pos = pRubble->GetPos();
		D3DXVECTOR3 rot = pRubble->GetRot();
		const std::string& path = pRubble->GetFileName();

		ofs << "------ [ " << nCnt << "番目 ] -------\n";
		ofs << "SETTING\n";
		ofs << "POS = " << pos.x << " " << pos.y << " " << pos.z << " # 座標\n";
		ofs << "ROT = " << rot.x << " " << rot.y << " " << rot.z << " # 角度\n";
		ofs << "FILEPASS = " << path << " # Xファイル\n";
		ofs << "END_SETTING\n\n";
	}

	// ファイルを閉じる
	ofs.close();
}
