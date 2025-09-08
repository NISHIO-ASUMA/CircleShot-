//=============================================
//
// チュートリアルタスク処理 [ tutotask.cpp ]
// Author: Asuma Nishio
//
//=============================================

//******************************
// インクルードファイル宣言
//******************************
#include "tutotask.h"
#include "manager.h"
#include "player.h"
#include "tutorialui.h"
#include <fstream>
#include <iostream>
#include <sstream>

//******************************
// 名前空間
//******************************
namespace TASKS
{
	constexpr const char* FILENAME = "data\\Loader\\TutoUi.txt"; // ファイル名
}
//================================
// コンストラクタ
//================================
CTutoTask::CTutoTask()
{
	// 値のクリア
	m_pTutoUi.clear();
	m_Info = {};
	m_pCurrentUi = nullptr;
	m_nCurrentIndex = NULL;
}
//================================
// デストラクタ
//================================
CTutoTask::~CTutoTask()
{
	// 無し
}
//================================
// 初期化処理
//================================
HRESULT CTutoTask::Init(void)
{
	// 値のクリア
	m_pTutoUi.clear();

	// 読み込み
	Load();

	if (!m_pTutoUi.empty())
	{
		// 最初に表示するUIを生成
		CreateTaskUi(0);
	}

	// 初期化結果を返す
	return S_OK;
}
//================================
// 終了処理
//================================
void CTutoTask::Uninit(void)
{
	// 動的配列をクリア
	m_pTutoUi.clear();
}
//================================
// 更新処理
//================================
void CTutoTask::Update(void)
{
	// nullなら処理を通さない
	if (m_pCurrentUi == nullptr) return;

	// フェードアウト完了時
	if (m_pCurrentUi->IsFinished())
	{
		// nullにする
		m_pCurrentUi = nullptr;

		// インデックス番号を加算
		m_nCurrentIndex++;

		// 配列オーバーしていなければ
		if (m_nCurrentIndex < (int)m_pTutoUi.size())
		{
			// タスク生成
			CreateTaskUi(m_nCurrentIndex);
		}
	}
}
//================================
// 読み込み処理
//================================
void CTutoTask::Load(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 指定ファイルを開く
	std::ifstream loadFile(TASKS::FILENAME);

	// もしファイルが開けない場合
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", TASKS::FILENAME, MB_OK);

		return;
	}

	// ローカル変数
	std::string line;
	int nNumFile = NULL;
	int nCnt = 0;

	// 配列のクリア処理
	m_pTutoUi.clear();

	// 読み込み終わりまで回す
	while (std::getline(loadFile, line))
	{
		// ファイルの読み込むラインを選択
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_UI")
		{// "NUM_FILE"読み取り時

			// "="の時
			std::string eq;

			// 代入
			iss >> eq >> nNumFile;

			// 最大サイズを設定
			m_pTutoUi.resize(nNumFile);
		}
		else if (token == "SET")
		{// SET読み取り時
			while (std::getline(loadFile, line))
			{
				// コメントスキップ
				if (line.empty() || line[0] == '#') continue;

				std::istringstream subIss(line);
				std::string key;
				subIss >> key;

				if (key == "POS")
				{// POS読み取り時

					// "="を格納
					std::string eq;

					// 座標を格納
					subIss >> eq
						>> m_pTutoUi[nCnt].pos.x
						>> m_pTutoUi[nCnt].pos.y
						>> m_pTutoUi[nCnt].pos.z;
				}
				else if (key == "WIDTH")
				{// "WIDTH"読み取り時

					// "="を格納
					std::string eq;

					// 横幅を格納
					subIss >> eq >> m_pTutoUi[nCnt].fWidth;
				}
				else if (key == "HEIGHT")
				{// "HEIGHT"読み取り時

					// "="を格納
					std::string eq;

					// 高さを格納
					subIss >> eq >> m_pTutoUi[nCnt].fHeight;
				}
				else if (key == "TEXTURE")
				{// "TEXTURE"読み取り時

					// "="を格納
					std::string eq;

					// ファイル名を格納
					subIss >> eq >> m_pTutoUi[nCnt].TexName;
				}
				else if (key == "STATE")
				{// "STATE"読み取り時

					// "="を格納
					std::string eq;

					// 状態を格納
					subIss >> eq >> m_pTutoUi[nCnt].nState;
				}
				else if (key == "ENDSET")
				{
					// 次のUI情報に行く
					nCnt++;

					// while文を抜ける
					break;
				}
			}
		}
	}

	// ファイルを閉じる
	loadFile.close();
}
//================================
// タスク進行処理
//================================
void CTutoTask::NextTask(void)
{
	// nullじゃなかったら
	if (m_pCurrentUi != nullptr)
	{
		// 状態変更
		m_pCurrentUi->SetState(CTutorialUi::STATE_EXIT);
	}
}
//================================
// 生成処理
//================================
void CTutoTask::CreateTaskUi(int index)
{
	// 例外チェック
	if (index < 0 || index >= (int)m_pTutoUi.size()) return;

	// 構造体情報をセット
	const TASKINFO& data = m_pTutoUi[index];

	// nullならUI生成をする
	if (m_pCurrentUi == nullptr)
	{
		m_pCurrentUi = CTutorialUi::Create(
			data.pos,
			data.fWidth,
			data.fHeight,
			data.TexName.c_str(),
			data.nState
		);
	}
}