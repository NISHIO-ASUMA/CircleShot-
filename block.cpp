//====================================
//
// ブロック処理 [ block.cpp ]
// Author: Asuma Nishio
//
//=====================================

//******************************
// インクルードファイル宣言
//******************************
#include "block.h"
#include "template.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_size = NULL;
	m_nType = NULL;
}
//===============================
// デストラクタ
//===============================
CBlock::~CBlock()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CBlock::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// 結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CBlock::Uninit(void)
{
	// 親クラスの終了
	CObjectX::Uninit();
}
//===============================
// 更新処理
//===============================
void CBlock::Update(void)
{
	// 回転するなら
	if (m_nType == ROTTYPE_ROTATION)
	{
		// 角度取得
		D3DXVECTOR3 rot = GetRot();

		// 加算
		rot.y += 0.03f;

		// 正規化
		rot.y = NormalAngle(rot.y);

		// 角度にセット
		SetRot(rot);
	}
}
//===============================
// 描画処理
//===============================
void CBlock::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
//===============================
// 生成処理
//===============================
CBlock* CBlock::Create(const char* pFileName, D3DXVECTOR3 pos,D3DXVECTOR3 rot,float fSize,int nType)
{
	// インスタンスを生成
	CBlock* pBlock = new CBlock;

	// nullptrだったら
	if (pBlock == nullptr) return nullptr;

	// オブジェクト設定
	pBlock->SetFilePass(pFileName);
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->m_size = fSize;
	pBlock->m_nType = nType;

	// 初期化に失敗したら
	if (FAILED(pBlock->Init()))
	{
		// nullptrを返す
		return nullptr;
	}

	// 生成ポインタを返す
	return pBlock;
}