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
	int nCnt = 0;

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

			// 
			m_ModelInfo.resize(nNumFile);
		}
		else if (token == "FILENAME")
		{// "FILENAME"読み取り時

			// ファイル名
			std::string eq, filepath;

			iss >> eq >> filepath;

			// 文字列取得
			strncpy_s(m_ModelInfo[nCnt].FileName, filepath.c_str(), sizeof(m_ModelInfo[nCnt].FileName) - 1);

			// Xファイルの読み込み
			D3DXLoadMeshFromX(m_ModelInfo[nCnt].FileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_ModelInfo[nCnt].pBuffMat,
				NULL,
				&m_ModelInfo[nCnt].dwNumMat,
				&m_ModelInfo[nCnt].pMesh);

			// マテリアルデータへのポインタ
			D3DXMATERIAL* pMat = nullptr;

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)m_ModelInfo[nCnt].pBuffMat->GetBufferPointer();

			// テクスチャインデックス配列
			m_ModelInfo[nCnt].pTexture.resize(m_ModelInfo[nCnt].dwNumMat);

			// マテリアル数だけ回す
			for (int nCntMat = 0; nCntMat < (int)m_ModelInfo[nCnt].dwNumMat; nCntMat++)
			{
				// テクスチャが読み込めたら
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// テクスチャポインタ取得
					CTexture* pTexture = CManager::GetTexture();

					// テクスチャセット
					int texID = pTexture->Register(pMat[nCntMat].pTextureFilename);

					// テクスチャ情報を格納
					m_ModelInfo[nCnt].pTexture[nCntMat] = texID;
				}
				else
				{
					// テクスチャなし
					m_ModelInfo[nCnt].pTexture[nCntMat] = -1;
				}
			}

			// インクリメント
			nCnt++;
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
	for (auto iter = m_ModelInfo.begin(); iter != m_ModelInfo.end(); iter++)
	{
		if ((*iter).pMesh != nullptr)
		{
			(*iter).pMesh->Release();
			(*iter).pMesh = nullptr;
		}
		if ((*iter).pBuffMat != nullptr)
		{
			(*iter).pBuffMat->Release();
			(*iter).pBuffMat = nullptr;
		}

		(*iter).pTexture.clear();

		if ((*iter).FileName != NULL)
		{
			ZeroMemory(&((*iter).FileName), sizeof((*iter).FileName));
		}

		if ((*iter).dwNumMat != NULL)
		{
			(*iter).dwNumMat = 0;
		}
	}

	// 配列クリア
	m_ModelInfo.clear();
}