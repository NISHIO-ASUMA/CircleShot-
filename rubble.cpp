//========================================
//
// 瓦礫オブジェクト処理 [ rubble.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// インクルードファイル
//**********************************
#include "rubble.h"
#include "scene.h"
#include "manager.h"
#include "shadow.h"

//================================
// オーバーロードコンストラクタ
//================================
CRubble::CRubble(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_Fallingspeed = VECTOR3_NULL;
}
//================================
// デストラクタ
//================================
CRubble::~CRubble()
{
	// 無し
}
//================================
// 生成処理
//================================
CRubble* CRubble::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// インスタンス生成
	CRubble* pRubble = new CRubble;

	// もしnullだったら
	if (pRubble == nullptr) return nullptr;

	// オブジェクト設定
	pRubble->SetFilePass(pFilename);
	pRubble->SetPos(pos);
	pRubble->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pRubble->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pRubble;
}
//================================
// 初期化処理
//================================
HRESULT CRubble::Init(void)
{
	// 親クラス初期化処理
	CObjectX::Init();

	// オブジェクトの種類定義
	SetObjType(CObject::TYPE_RUBBLE);

	// 初期値を設定
	m_Fallingspeed = { 0.0f,3.0f,0.0f };

	// 影オブジェクトを生成
	m_pShadow = CShadow::Create(VECTOR3_NULL, VECTOR3_NULL);

	// 初期化結果を返す
	return S_OK;
}
//================================
// 終了処理
//================================
void CRubble::Uninit(void)
{
	// 親クラス終了処理
	CObjectX::Uninit();
}
//================================
// 更新処理
//================================
void CRubble::Update(void)
{
	// 現在シーン取得
	CScene::MODE pMode = CManager::GetScene();

	// 現在の座標を取得
	D3DXVECTOR3 NowPos = GetPos();

	// ゲームシーンなら
	if (pMode == CScene::MODE_GAME)
	{
		// 現在の座標に対して重力値を加算する
		NowPos -= m_Fallingspeed;

		// 現在座標をセットする
		SetPos(NowPos);
	}

	// 影の座標設定
	m_pShadow->UpdatePos(D3DXVECTOR3(NowPos.x,2.0f, NowPos.z));

	// 画面下
	if (NowPos.y <= -15.0f)
	{
		// 終了処理
		Uninit();

		// ここで影も消す
		m_pShadow->Uninit();

		// ここで処理を返す
		return;
	}
}
//================================
// 描画処理
//================================
void CRubble::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}
//====================================
// 当たり判定処理関数 ( 球座標で計算 )
//====================================
bool CRubble::Collision(D3DXVECTOR3 * DestPos)
{
	// 現在座標を取得
	D3DXVECTOR3 NowPos = GetPos();

	// プレイヤーとの距離差分
	float fDisX = DestPos->x - NowPos.x;
	float fDisY = DestPos->y - NowPos.y;
	float fDisZ = DestPos->z - NowPos.z;

	// 半径を設定
	float fRadius = 25.0f;

	// 半径のサイズを計算
	float fradX = fRadius + 25.0f;
	float fradY = fRadius + 25.0f;
	float fradZ = fRadius + 25.0f;

	// 差分と半径の合計を計算
	float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
	float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

	// 半径内に入っていたら
	if (fDissAll <= fRadAll)
	{
		// コリジョン判定を返す
		return true;
	}

	// 当たらないとき
	return false;
}
