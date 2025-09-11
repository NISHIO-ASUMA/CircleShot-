//====================================================
//
// シーンファイル読み込み処理 [ sceneloader.cpp ]
// Author: Asuma Nishio
//
//====================================================

//**********************************
// インクルードファイル
//**********************************
#include "sceneloader.h"
#include "meshdome.h"
#include "meshfield.h"
#include "meshimpact.h"
#include "block.h"
#include "player.h"
#include "playerlifegage.h"
#include "bosslifegage.h"
#include "charge.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//=================================
// コンストラクタ
//=================================
CSceneLoader::CSceneLoader()
{
	// 値のクリア
}
//=================================
// デストラクタ
//=================================
CSceneLoader::~CSceneLoader()
{
	// 無し
}
//=================================
// 分割処理
//=================================
void CSceneLoader::SplitLoad(int nIdx)
{
	// 指定ファイルを開く
	std::ifstream loadFile(m_aFileList[nIdx]);

	// もしファイルが開けない場合
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", m_aFileList[nIdx], MB_OK);

		return;
	}

	// ローカル変数
	std::string line;
	int nNumFile = NULL;

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

			// 変数の初期化
			objName.clear(); motionPath.clear(); filePath.clear(); createType.clear();
			pos = VECTOR3_NULL;
			rot = VECTOR3_NULL;
			life = 0;
			radius = size = width = height = 0.0f;
			index = type = category = -1;

			// "="を格納
			std::string eq;

			// OBJNAMEを読み取る
			iss >> eq >> objName;
		}
		else if (token == "POS")
		{// 座標情報
			// "="を格納
			std::string eq;

			// 読み取った座標情報をセット
			iss >> eq >> pos.x >> pos.y >> pos.z;
		}
		else if (token == "ROT")
		{// 角度情報
			// "="を格納
			std::string eq;

			// 読み取った角度情報をセット
			iss >> eq >> rot.x >> rot.y >> rot.z;
		}
		else if (token == "LIFE")
		{// 体力パラメーター情報
			// "="を格納
			std::string eq;

			// 読み取った情報をセット
			iss >> eq >> life;
		}
		else if (token == "INDEX")
		{// インデックス情報
			// "="を格納
			std::string eq;

			// 読み取った識別番号情報をセット
			iss >> eq >> index;
		}
		else if (token == "MOTIONPASS")
		{// モーションテキストパス情報
			// "="を格納
			std::string eq;

			// 読み取ったテキストファイル情報をセット
			iss >> eq >> motionPath;
		}
		else if (token == "XFILEPASS")
		{// Xファイル情報
			// "="を格納
			std::string eq;

			// 読み込んだXファイル情報をセット
			iss >> eq >> filePath;
		}
		else if (token == "TYPE")
		{// 種類情報
			// "="を格納
			std::string eq;

			// 読み込んだ種類情報をセット
			iss >> eq >> type;
		}
		else if (token == "RADIUS")
		{// 半径情報
			// "="を格納
			std::string eq;

			// 読み取った半径情報をセット
			iss >> eq >> radius;
		}
		else if (token == "SIZE")
		{// 大きさ情報
			// "="を格納
			std::string eq;

			// 読み取った大きさ情報をセット
			iss >> eq >> size;
		}
		else if (token == "CREATETYPE")
		{// カテゴリー種類情報
			// "="を格納
			std::string eq;

			// 読み取ったカテゴリー情報をセット
			iss >> eq >> createType;
		}
		else if (token == "WIDTH")
		{// 横幅情報
			// "="を格納
			std::string eq;

			// 読み取った横幅情報をセット
			iss >> eq >> width;
		}
		else if (token == "HEIGHT")
		{// 高さ情報
			// "="を格納
			std::string eq;

			// 読み取った高さ情報をセット
			iss >> eq >> height;
		}
		else if (token == "CATEGORY")
		{// カテゴリーの内訳情報
			// "="を格納
			std::string eq;

			// 読み取った内訳をセット
			iss >> eq >> category;
		}
		else if (token == "ENDSET")
		{// 最終読み取り
			// 各種生成
			if (objName == "PLAYER")
			{
				// ゲームプレイヤー
				CPlayer::Create(pos, rot, life, index, motionPath.c_str());

				// パスのクリア
				motionPath.clear();
			}
			else if (objName == "MESH")
			{
				if (type == 0) CMeshDome::Create(pos, radius); 	// メッシュドーム
				else if (type == 1) CMeshField::Create(pos, radius); // メッシュフィールド
			}
			else if (objName == "BLOCK")
			{
				// ブロック
				CBlock::Create(filePath.c_str(), pos, rot, size,type);

				// パスのクリア
				filePath.clear();
			}
			else if (objName == "UI")
			{// UI情報
				if (createType == "PLAYER")
				{
					// 体力ゲージ
					CPlayerLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "BOSS")
				{
					// 体力ゲージ
					CBossLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "LASER")
				{
					// レーザーゲージ
					CCharge::Create(pos, width, height, category);
				}
			}
		}
	}

	// ファイルを閉じる
	loadFile.close();
}