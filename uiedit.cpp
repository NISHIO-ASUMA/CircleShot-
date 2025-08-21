//====================================
//
// エディター処理 [ uiedit.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "uiedit.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include <fstream>
#include <iomanip> 
#include <string>

//===============================
// コンストラクタ
//===============================
CUiedit::CUiedit()
{
	// 配列クリア
	m_pUi.clear();
}
//===============================
// デストラクタ
//===============================
CUiedit::~CUiedit()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CUiedit::Init(void)
{
	// 配列クリア
	m_pUi.clear();

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CUiedit::Uninit(void)
{
	// 配列クリア
	m_pUi.clear();
}
//===============================
// 更新処理
//===============================
void CUiedit::Update(void)
{
	// キー入力用の変数
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	// 移動設定
	if (pInput->GetTrigger(DIK_A))
	{

	}
	else if (pInput->GetTrigger(DIK_D))
	{

	}
	else if (pInput->GetTrigger(DIK_W))
	{

	}
	else if (pInput->GetTrigger(DIK_S))
	{

	}

	// 配置決定キー
	if (pInput->GetTrigger(DIK_RETURN))
	{// ui追加
		// AddUi()
	}

	// 削除キー
	if (pInput->GetTrigger(DIK_BACKSPACE))
	{

	}

	// ファイル書き出しキー
	if (pInput->GetTrigger(DIK_F7))
	{
		SaveFile("data\\Ui.txt");
	}

	// ファイル再読み込みキー
	if (pInput->GetTrigger(DIK_F8))
	{
		ReloadFile("data\\Ui.txt");
	}
}
//===============================
// 描画処理
//===============================
void CUiedit::Draw(void)
{
	// オブジェクト描画
	
}
//===============================
// ui追加関数
//===============================
void CUiedit::AddUi(D3DXVECTOR3 pos, int type, float width, float height)
{
#if 0
	// Uiを生成する
	CUi* pUi = CUi::Create(pos, type, width, height);

	// nullなら
	if (pUi == nullptr) return;

	// ローカル変数宣言
	EditInfo info;
	info.pos = pos; // 座標セット
	info.nType = type; // 種類セット
	info.fWidth = width; // 横幅セット
	info.fHeight = height; // 高さセット

	info.pUi = pUi; // ポインタセット

	// 配列に追加する
	m_pUi.push_back(info);
#endif
}
//===============================
// 書き出し処理
//===============================
void CUiedit::SaveFile(const char* filename)
{
	// 書き出し用ファイルポインタ宣言
	std::ofstream fStream(filename);

	// 開けなかったら処理終了
	if (!fStream.is_open()) return;

	// ファイルヘッダー
	fStream << "#===================================\n";
	fStream << "# UI配置情報\n";
	fStream << "#===================================\n\n";

	// 配置数
	fStream << "#===================================\n";
	fStream << "# 配置数\n";
	fStream << "#===================================\n";
	fStream << "NUM_UI = " << m_pUi.size() << "\n\n";

	// 各UI情報
	fStream << "#===================================\n";
	fStream << "# 各UI情報\n";
	fStream << "#===================================\n\n";

	// 1つずつ書き出し
	for (int nUi = 0; nUi < m_pUi.size(); nUi++)
	{
		// 構造体情報を代入
		const EditInfo& ui = m_pUi[nUi];

		fStream << "#==========[" << nUi << "]番目の情報=========\n";
		fStream << "POS = "
			<< std::fixed << std::setprecision(2) // 要素を書き出す数を決める
			<< ui.pos.x << " "
			<< ui.pos.y << " "
			<< ui.pos.z << "\n";

		fStream << "TYPE = " << ui.nType << "\n";
		fStream << "WIDTH = " << ui.fWidth << "\n";
		fStream << "HEIGHT = " << ui.fHeight << "\n";
		fStream << "#================================\n\n";
	}

	// ファイルを閉じる
	fStream.close();
}
//===============================
// 再読み込み処理
//===============================
void CUiedit::ReloadFile(const char* filename)
{
#if 0
	// 破棄
	for (auto& UI : m_pUi) // 構造体の型でautoを使用
	{
		// nullptrじゃなかったら
		if (UI.pUi)
		{
			// 終了処理
			UI.pUi->Uninit();

			// ポインタの破棄
			delete UI.pUi;
		}
	}

	// 配列のクリア処理
	m_pUi.clear();

	// ファイルストリーム宣言
	std::ifstream fStream(filename);

	// 開けなかったら処理終了
	if (!fStream.is_open()) return;

	// lineで一行ずつ読んでいく
	std::string line;

	// 配置数取得用
	int nNUmUi = 0;

	// ファイルの行を読んでいく
	while (std::getline(fStream, line))
	{
		// "NUM_UI"を読み取ったら
		if (line.find("NUM_UI") != std::string::npos)
		{
			// "="を見つけたら
			size_t pos = line.find('=');

			// "="の次の文字から数値を取り出す
			if (pos != std::string::npos)
			{
				// 数値セット
				nNUmUi = std::stoi(line.substr(pos + 1));

				// while文を抜ける
				break;
			}
		}
	}

	// 各UI情報を読み込む
	for (int nCnt = 0; nCnt < nNUmUi; nCnt++)
	{
		// 代入用変数宣言
		D3DXVECTOR3 pos = VECTOR3_NULL;
		int nType = 0;
		float fWidth = 0.0f;
		float fHeight = 0.0f;

		// 一行ずつループで読んでいく
		while (std::getline(fStream, line))
		{
			// "POS"を読み取ったら
			if (line.find("POS") != std::string::npos)
			{
				// "="を見つけたら
				size_t posEqual = line.find('=');

				// "POS "から数値を代入
				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// POSをセット
					iss >> pos.x >> pos.y >> pos.z;
				}
			}
			else if (line.find("TYPE") != std::string::npos)
			{
				// "="を見つけたら
				size_t posEqual = line.find('=');

				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// 種類代入
					iss >> nType;
				}
			}
			else if (line.find("WIDTH") != std::string::npos)
			{
				// "="を見つけたら
				size_t posEqual = line.find('=');

				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// 横幅代入
					iss >> fWidth;
				}
			}
			else if (line.find("HEIGHT") != std::string::npos)
			{
				// "="を見つけたら
				size_t posEqual = line.find('=');

				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// 高さを代入
					iss >> fHeight;
				}
			}
			else if (line.find("#================================") != std::string::npos)
			{
				// 1UI分の読み込みが完了したら追加
				AddUi(pos, nType, fWidth, fHeight);

				// while文を抜ける
				break;
			}
		}
	}

	// ファイルを閉じる
	fStream.close();
#endif
}
