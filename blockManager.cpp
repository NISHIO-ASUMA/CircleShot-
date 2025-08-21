//=============================================
//
// ブロック全体の管理を行う [ blockmanager.h ]
// Author: Asuma Nishio
//
//==============================================

//*******************************
// インクルードファイル宣言
//*******************************
#include "blockManager.h"
#include "manager.h"
#include "json.hpp"

//*******************************
// 静的メンバ変数宣言
//*******************************
std::vector<CBlock*>CBlockManager::m_blocks = {}; // 動的配列
int CBlockManager::m_nIdxCount = NULL;	// インデックスカウント

//===============================
// コンストラクタ
//===============================
CBlockManager::CBlockManager()
{
	// 無し
}
//===============================
// デストラクタ
//===============================
CBlockManager::~CBlockManager()
{
	// 無い
}
//===============================
// 初期化
//===============================
HRESULT CBlockManager::Init(const char* filename, D3DXVECTOR3 pos)
{
	// 配列を初期化 (サイズを0にする)
	m_blocks.clear();

	return S_OK;
}
//===============================
// 終了
//===============================
void CBlockManager::Uninit(void)
{
	// 配列を空にする (サイズを0にする)
	m_blocks.clear();
}
//===============================
// 更新
//===============================
void CBlockManager::Update(void)
{

}
//===============================
// 生成
//===============================
CBlock* CBlockManager::Create(const char* pfileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot,float Size)
{
	// インスタンス生成
	CBlock* pNewBlock = CBlock::Create(pfileName,pos,rot,Size);

	// 成功時
	if (pNewBlock)
	{
		// 配列に追加
		m_blocks.push_back(pNewBlock);

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
