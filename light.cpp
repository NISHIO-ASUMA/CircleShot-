//====================================
//
// ライト処理 [ light.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "light.h"
#include "manager.h"

//=================================
// コンストラクタ
//=================================
CLight::CLight()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < NUMLIGHT; nCnt++)
	{
		m_aLight[nCnt] = {};
		m_vecDir[nCnt] = {};
	}
}
//=================================
// デストラクタ
//=================================
CLight::~CLight()
{
	// 無し
}
//=================================
// ライトの初期化処理
//=================================
HRESULT CLight::Init(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ライトのクリア処理( ゼロメモリー関数 )
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	// ライトの種類を設定
	for (int nCnt = 0; nCnt < NUMLIGHT; nCnt++)
	{
		// 平行光源
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;	

		// ライトの拡散光
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// ライトの方向設定
	m_vecDir[0] = D3DXVECTOR3(0.25f, -0.84f, -0.43f);
	m_vecDir[1] = D3DXVECTOR3(-0.61f, 0.10f, 0.44f);
	m_vecDir[2] = D3DXVECTOR3(1.0f, -0.52f, 0.41f);

	// 正規化する
	for (int nCnt1 = 0; nCnt1 < NUMLIGHT; nCnt1++)
	{	
		// ベクトルの大きさを1にする
		D3DXVec3Normalize(&m_vecDir[nCnt1], &m_vecDir[nCnt1]); 

		m_aLight[nCnt1].Direction = m_vecDir[nCnt1];

		// ライトの設定
		pDevice->SetLight(nCnt1, &m_aLight[nCnt1]);

		// ライトを有効化
		pDevice->LightEnable(nCnt1, TRUE);
	}

	return S_OK;
}
//=================================
// ライトの終了処理
//=================================
void CLight::Uninit(void)
{
	// 無し
}
//=================================
// ライトの更新処理
//=================================
void CLight::Update(void)
{
	// 無し
}