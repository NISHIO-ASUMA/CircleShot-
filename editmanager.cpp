//================================================
//
// エディターシーン管理処理 [ editmanager.cpp ]
// Author : Asuma Nishio
//
//================================================

//**************************
// インクルードファイル宣言
//**************************
#include "editmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "rubblemanager.h"
#include "rubble.h"
#include "editmodel.h"
#include "mapmanager.h"
#include "mapobject.h"
#include "template.h"
#include "shadow.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

//*******************************
// 名前空間
//*******************************
namespace EDITINFO
{
	constexpr float MOVESPEED = 5.0f;
	constexpr float ROTVALUE = 0.03f;
	constexpr float VALUEHEIGHT = 5.0f;
};

//=============================
// コンストラクタ
//=============================
CEditManager::CEditManager()
{
	m_pShadow = nullptr;
	m_pMapManager = nullptr;
}
//=============================
// デストラクタ
//=============================
CEditManager::~CEditManager()
{
	// 無し
}
//=============================
// 初期化処理
//=============================
HRESULT CEditManager::Init(void)
{
	// モデルリストを読み込み
	CModelList::Load();

	// マネージャー生成
	m_pMapManager = CMapManager::Craete();
	
	m_pShadow = CShadow::Create(VECTOR3_NULL, VECTOR3_NULL);

	// 初期化結果を返す
	return S_OK;
}
//=============================
// 終了処理
//=============================
void CEditManager::Uninit(void)
{
	// 破棄
	CModelList::UnLoad();
}
//=============================
// 更新処理
//=============================
void CEditManager::Update(void)
{
	// カメラ
	CCamera* pCamera = CManager::GetCamera();

	// nullなら
	if (pCamera == nullptr) return;

	// 移動処理
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// Aキーを押した

		m_pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
		m_pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// Dキーを押した

		m_pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
		m_pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// Wキーを押した

		m_pos.x += sinf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;
		m_pos.z += cosf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// Sキーを押した

		m_pos.x -= sinf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;
		m_pos.z -= cosf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;
	}

	// 高さ変更
	if (CManager::GetInputKeyboard()->GetPress(DIK_R))
	{
		m_pos.y += EDITINFO::VALUEHEIGHT;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_F))
	{
		m_pos.y -= EDITINFO::VALUEHEIGHT;
	}

	// 角度変更 ( Y )
	if (CManager::GetInputKeyboard()->GetPress(DIK_Y))
	{
		m_rot.y += EDITINFO::ROTVALUE;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_H))
	{
		m_rot.y -= EDITINFO::ROTVALUE;
	}

	// 角度変更 ( X )
	if (CManager::GetInputKeyboard()->GetPress(DIK_U))
	{
		m_rot.x += EDITINFO::ROTVALUE;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_J))
	{
		m_rot.x -= EDITINFO::ROTVALUE;
	}

	// 角度変更 ( Z )
	if (CManager::GetInputKeyboard()->GetPress(DIK_I))
	{
		m_rot.z += EDITINFO::ROTVALUE;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_K))
	{
		m_rot.z -= EDITINFO::ROTVALUE;
	}

	// 初期化処理
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_TAB))
	{
		m_rot = VECTOR3_NULL;
	}

	// 種類インデックスを加算 減算
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_E) && m_nTypeIdx < 3)
	{
		m_nTypeIdx++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_Q)&& m_nTypeIdx > 0)
	{
		m_nTypeIdx--;
	}

	// 角度を正規化する
	if (m_rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_rot.y -= D3DX_PI * 2.0f;
	}
	// 角度の正規化
	if (m_rot.y < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		m_rot.y += D3DX_PI * 2.0f;
	}

	// 角度を正規化する
	if (m_rot.x > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_rot.x -= D3DX_PI * 2.0f;
	}
	// 角度の正規化
	if (m_rot.x < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		m_rot.x += D3DX_PI * 2.0f;
	}

	// 角度を正規化する
	if (m_rot.z > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_rot.z -= D3DX_PI * 2.0f;
	}
	// 角度の正規化
	if (m_rot.z < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		m_rot.z += D3DX_PI * 2.0f;
	}

	// キー入力で保存
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F7))
	{
		// 保存関数実行
		Save();
	}

	// 保存パス切り替え処理
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F6))
	{
		m_nSavePassIdx = (m_nSavePassIdx + 1) % SAVEPASS_MAX;
	}

	// キー入力で生成
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// 生成処理
		CMapObject* pMapObj = CMapObject::Create(m_pos, m_rot, m_nTypeIdx);

		// 配列に追加
		m_pMapManager->PushBack(pMapObj);

		// 総数を加算
		m_nNumAll++;
	}

	m_pShadow->UpdatePos(D3DXVECTOR3(m_pos.x, 2.0f, m_pos.z));
}
//=============================
// 描画処理
//=============================
void CEditManager::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);
	
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 現在のマトリックスの取得
	pDevice->GetMaterial(&matDef);

	// モデル情報
	CModelList::MODELINFO Info = CModelList::GetInfo(m_nTypeIdx);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)Info.pBuffMat->GetBufferPointer();

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)Info.dwNumMat; nCntMat++)
	{
		// カラー
		D3DXMATERIAL Col = pMat[nCntMat];

		Col.MatD3D.Diffuse.a = 0.5f;

		// マテリアル設定
		pDevice->SetMaterial(&Col.MatD3D);

		// インデックスに応じて変更する
		if (Info.pTexture[nCntMat] != -1)
		{
			// テクスチャ取得
			CTexture* pTexture = CManager::GetTexture();

			// テクスチャセット
			pDevice->SetTexture(0, pTexture->GetAddress(Info.pTexture[nCntMat]));
		}
		else
		{
			pDevice->SetTexture(0, NULL); // テクスチャなし
		}

		// モデル(パーツ)の描画
		Info.pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);

	// デバッグ表示
	CDebugproc::Print("選択オブジェクトの座標 { %.2f,%.2f,%.2f }", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(0, 140);

	// デバッグ表示
	CDebugproc::Print("選択オブジェクトの角度 { %.2f,%.2f,%.2f }", m_rot.x, m_rot.y, m_rot.z);
	CDebugproc::Draw(0, 160);

	// デバッグ表示
	CDebugproc::Print("Editオブジェクトの数 { %d }",m_nNumAll);
	CDebugproc::Draw(0, 180);

	// デバッグ表示
	CDebugproc::Print("ファイルインデックス { %d }", m_nSavePassIdx);
	CDebugproc::Draw(0, 200);

}


//=============================
// 保存処理
//=============================
void CEditManager::Save(void)
{
	// 開くファイル設定
	std::ofstream ofs(FILELIST[m_nSavePassIdx]);

	// 例外処理
	if (!ofs.is_open())
	{
		MessageBox(NULL, "保存ファイルを開けませんでした", "エラー", MB_OK);

		return;
	}

	// float出力を固定小数点形式にする
	ofs << std::fixed << std::setprecision(2);

	ofs << "//==========================================================\n";
	ofs << "// \n";
	ofs << "// ゲーム中に出現する瓦礫オブジェクト [ "<< FILELIST[m_nSavePassIdx] << " ]\n";
	ofs << "// Author : Asuma Nishio\n";
	ofs << "// \n";
	ofs << "//==========================================================\n\n";

	ofs << "//==========================================================\n";
	ofs << "// 出現するオブジェクトの数\n";
	ofs << "//==========================================================\n";
	ofs << "NUM_RUBBLES = " << m_pMapManager->GetSize() << "\n\n";

	ofs << "//==========================================================\n";
	ofs << "// 各オブジェクト情報\n";
	ofs << "//==========================================================\n\n";

	// サイズ分で回す
	for (int nCnt = 0; nCnt < m_pMapManager->GetSize(); nCnt++)
	{
		// オブジェクトの情報取得
		CMapObject* pObj = m_pMapManager->GetInfo(nCnt);

		// 無かったら
		if (!pObj) continue;

		// 座標,角度を取得
		D3DXVECTOR3 pos = pObj->GetPos();
		D3DXVECTOR3 rot = pObj->GetRot();

		// モデルファイルパスを取得
		CModelList::MODELINFO info = CModelList::GetInfo(pObj->GetIdx());

		ofs << "------ [ " << nCnt << "番目 ] -------\n";
		ofs << "SETTING \n";
		ofs << "POS = " << pos.x << " " << pos.y << " " << pos.z << "   # 座標\n";
		ofs << "ROT = " << rot.x << " " << rot.y << " " << rot.z << "   # 角度\n";
		ofs << "FILEPASS = " << info.FileName << "\t# Xファイル\n";
		ofs << "END_SETTING\n\n";
	}

	// ファイルを閉じる
	ofs.close();
}
//=============================
// ファイル再読み込み処理
//=============================
void CEditManager::Reload(void)
{
	// 開くファイル設定
	std::ofstream ofs(FILELIST[m_nSavePassIdx]);

	// 例外処理
	if (!ofs.is_open())
	{
		MessageBox(NULL, "データが入っていません", "エラー", MB_OK);

		return;
	}
}
