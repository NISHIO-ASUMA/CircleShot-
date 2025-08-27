//=========================================
//
// モデルファイルリスト [ modellist.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// インクルードファイル
//**********************
#include "modellist.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "manager.h"

//****************************
// 静的メンバ変数宣言
//****************************
std::vector<CModelList::MODELINFO> CModelList::m_ModelInfo = {}; // 動的リスト

//======================
// コンストラクタ
//======================
CModelList::CModelList()
{
	// 
}
//======================
// デストラクタ
//======================
CModelList::~CModelList()
{
	// 無し
}
//=========================
// モデル情報読み込み処理
//=========================
void CModelList::Load(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 指定ファイルを開く
	std::ifstream loadFile(MODELLIST);

	// もしファイルが開けない場合
	if (!loadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", MODELLIST, MB_OK);

		return;
	}

	// ローカル変数
	std::string line;
	int nNumFile = NULL;

	// 配列のクリア処理
	m_ModelInfo.clear();

	// 読み込み終わりまで回す
	while (std::getline(loadFile, line))
	{
		// ファイルの読み込むラインを選択
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_MODELFILE")
		{// "NUM_FILE"読み取り時

			// "="の時
			std::string eq;

			// 代入
			iss >> eq >> nNumFile;

			// ファイル配列のサイズを確保
			m_ModelInfo.reserve(nNumFile);
		}
		else if (token == "FILENAME")
		{// "FILENAME"読み取り時

			// 構造体変数
			MODELINFO info = {};

			// クリア
			ZeroMemory(&info, sizeof(MODELINFO));

			// ファイル名
			std::string eq, filepath;

			iss >> eq >> filepath;

			// 文字列取得
			strncpy_s(info.FileName, filepath.c_str(), sizeof(info.FileName) - 1);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(info.FileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&info.pBuffMat,
				NULL,
				&info.dwNumMat,
				&info.pMesh);

			// マテリアルデータへのポインタ
			D3DXMATERIAL* pMat = nullptr;

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)info.pBuffMat->GetBufferPointer();

			// テクスチャインデックス配列
			info.pTexture.resize(info.dwNumMat, -1);

			// マテリアル数だけ回す
			for (int nCntMat = 0; nCntMat < (int)info.dwNumMat; nCntMat++)
			{
				// テクスチャが読み込めたら
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// テクスチャポインタ取得
					CTexture* pTexture = CManager::GetTexture();

					// テクスチャセット
					int texID = pTexture->Register(pMat[nCntMat].pTextureFilename);

					// テクスチャ情報を格納
					info.pTexture[nCntMat] = texID;
				}
				else
				{
					// テクスチャなし
					info.pTexture[nCntMat] = -1;
				}
			}

			// 配列追加
			m_ModelInfo.push_back(info);
		}
	}

	// ファイルを閉じる
	loadFile.close();
}
//======================
// 破棄
//======================
void CModelList::UnLoad(void)
{
	// 配列クリア
	m_ModelInfo.clear();
}
