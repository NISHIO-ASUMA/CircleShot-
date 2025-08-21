//====================================
//
// テクスチャ処理 [ texture.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "texture.h"
#include "manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//**********************
// 静的メンバ変数
//**********************
int CTexture::m_nNumAll = NULL;	// 総数管理

//===============================
// コンストラクタ
//===============================
CTexture::CTexture()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}
}
//===============================
// デストラクタ
//===============================
CTexture::~CTexture()
{
	// 無し
}
//===============================
// テクスチャ読み込み
//===============================
HRESULT CTexture::Load(void)
{
#if 1
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// すべてのテクスチャ分回す
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// ファイル名が無いならスキップ
		if (TexName[nCnt] == nullptr)
			continue;

		// 列挙型の分読み込む
		if (FAILED(D3DXCreateTextureFromFile(pDevice, TexName[nCnt], &m_apTexture[nCnt])))
		{
			// 警告表示
			MessageBox(NULL, "テクスチャパスが存在しません", TexName[nCnt], MB_OK);

			return E_FAIL;
		}

		// 加算する
		m_nNumAll++;
	}
#endif

	// 結果を返す
	return S_OK;

}
//===============================
// テクスチャ破棄
//===============================
void CTexture::UnLoad(void)
{
	// すべてのテクスチャの破棄
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}
//===============================
// テクスチャ番号を登録する
//===============================
int CTexture::Register(const char* pFileName)
{
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// nullptrチェック
		if (TexName[nCnt] != nullptr)
		{
			// ファイルパス名が一致していたら
			if (strcmp(pFileName, TexName[nCnt]) == 0)
			{
				// 番号を返す
				return nCnt;
			}
		}
	}

	// テクスチャがない場合
	return -1;
}
//===============================
// テクスチャ番号取得
//===============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	// 例外処理
	if (nIdx < 0 || nIdx >= NUM_TEXTURE) return nullptr;

	// テクスチャ番号を取得
	return m_apTexture[nIdx];
}
//===============================
// テクスチャ外部読み込み処理
//===============================
void CTexture::TextLoader(const char* pFileName)
{
	// ファイル設定
	std::ifstream file(pFileName);

	// ファイル例外チェック
	if (!file)
	{
		MessageBox(NULL, "ファイルオープン失敗", pFileName, MB_OK);
		// 失敗結果を返す
		return;
	}

	// 一行読み込む
	std::string line;

	int nIdx = 0;

	while (std::getline(file, line))
	{
		// コメント行や空行をスキップ
		if (line.empty() || line[0] == '#')
			continue;

		// "FILENAME =" を探す
		const std::string key = "FILENAME =";
		size_t pos = line.find(key);

		if (pos == std::string::npos)
			continue;

		// ダブルクォートで囲まれた部分を抽出
		size_t firstQuote = line.find('"', pos);
		size_t lastQuote = line.find_last_of('"');

		if (firstQuote != std::string::npos && lastQuote != std::string::npos && lastQuote > firstQuote)
		{
			std::string path = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

			if (nIdx < NUM_TEXTURE)
			{
				// strdupでコピーして格納
				TexName[nIdx] = _strdup(path.c_str());

				// インデックス番号を加算
				nIdx++;
			}
		}
	}

	// ファイルを閉じる
	file.close();
}
