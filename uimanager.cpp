//=========================================
//
// UI全体を管理する処理 [ uimanager.cpp ]
// Author: Asuma Nishio
//
//=========================================

//****************************
// インクルードファイル宣言
//****************************
#include "uimanager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//****************************
// 名前空間
//****************************
namespace
{
	const char* FILEPASS = "data\\UI\\GameUi.txt"; // ファイルパス
}

//****************************
// 静的メンバ変数宣言
//****************************
int CUimanager::m_nIdxUi = NULL; // 総配置数
std::vector<CUi*>CUimanager::m_aUidata = {}; // 動的配列

//===============================
// コンストラクタ
//===============================
CUimanager::CUimanager()
{
	// 値のクリア
	m_aUidata.clear();
}
//===============================
// デストラクタ
//===============================
CUimanager::~CUimanager()
{
	// 無い
}
//===============================
// 初期化処理
//===============================
HRESULT CUimanager::Init(void)
{
	// ファイルロード関数
	CUimanager::Load("data\\UI\\GameUi.txt");

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CUimanager::Uninit(void)
{
	// 値のクリア
	m_aUidata.clear();
}
//===============================
// 更新処理
//===============================
void CUimanager::Update(void)
{
	// 無し
}
//===============================
// テキスト読み込み処理
//===============================
void CUimanager::Load(const char* pFileName)
{
	// 読み込むファイルパスを設定
	std::ifstream loadFile(pFileName);

	// ファイル例外チェック
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", pFileName, MB_OK);

		// 失敗結果を返す
		return;
	}

	// 一行ずつ読み込む変数
	std::string loadline;

	// 総数設定
	int nNumAll = 0;

	// 文字列を読み続ける
	while (std::getline(loadFile, loadline))
	{
		// トークン設定
		std::istringstream Stringname(loadline);
		std::string Token;
		Stringname >> Token;

		// "NUM_UI"読み取り時
		if (Token == "NUM_UI")
		{
			// 文字列設定
			std::string eq;

			// 読み込んだモデル数を設定
			Stringname >> eq >> nNumAll;
		}
		// "SET_UI"読み取り時
		else if (Token == "SET_UI")
		{
			// 2Dオブジェクトの設定
			SetObjectUi(loadFile);

			// インデックスカウントを加算
			m_nIdxUi++;
		}
	}

	// ファイルを閉じる
	loadFile.close();
}
//===============================
// UIオブジェクト生成関数処理
//===============================
void CUimanager::SetObjectUi(std::ifstream& file)
{
	// 行読み込み設定
	std::string line;

	// 使用ローカル変数
	D3DXVECTOR3 pos = VECTOR3_NULL;
	float fWidth = 0.0f;
	float fHeight = 0.0f;
	int nAnchorType = 0;

	// テクスチャパス格納
	std::string texturePath;

	// 特定の文字が来るまで読む
	while (std::getline(file, line))
	{
		// トークン設定
		std::istringstream iString(line);
		std::string Token;
		iString >> Token;

		// "="の飛ばし
		std::string eqal;

		if (Token == "POS")
		{// "POS"読み取り時

			// 座標設定
			iString >> eqal >> pos.x >> pos.y >> pos.z;
		}
		else if (Token == "WIDTH")
		{// "WIDTH"読み取り時

			// 横幅設定
			iString >> eqal >> fWidth;
		}
		else if (Token == "HEIGHT")
		{// "HEIGHT"読み取り時

			// 高さ設定
			iString >> eqal >> fHeight;
		}
		else if (Token == "ANCHORTYPE")
		{// "ANCHORTYPE"読み取り時

			// 頂点生成種類を設定
			iString >> eqal >> nAnchorType;
		}
		else if (Token == "TEXTURE_PASS")
		{// "TEXTURE_PASS"読み取り時

			size_t equalPos = line.find('=');

			if (equalPos != std::string::npos)
			{
				texturePath = line.substr(equalPos + 1);

				// 空白除去
				texturePath.erase(0, texturePath.find_first_not_of(" \t"));
				texturePath.erase(texturePath.find_last_not_of(" \t") + 1);

				// コメント削除
				size_t commentPos = texturePath.find('#');
				if (commentPos != std::string::npos)
				{
					texturePath = texturePath.substr(0, commentPos);
					texturePath.erase(texturePath.find_last_not_of(" \t") + 1);
				}

				// クォーテーション削除
				if (!texturePath.empty() && texturePath.front() == '"') 
				{
					texturePath.erase(0, 1); // 先頭の " を削除
				}
				if (!texturePath.empty() && texturePath.back() == '"') 
				{
					texturePath.pop_back();  // 末尾の " を削除
				}
			}
		}
		else if (Token == "END_SETUI")
		{// "END_SETUI"読み取り時

			// ここでUI生成する
			CUi* pUi = CUi::Create(pos,fWidth, fHeight, texturePath.c_str(),nAnchorType);

			// nullじゃなかったら
			if (pUi != nullptr)
			{
				// 配列に追加
				m_aUidata.push_back(pUi);
			}

			break;
		}
	}
}