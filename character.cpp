//==========================================================
//
// キャラクターパラメーター設定関数 [ charactor.cpp ]
// Author : Asuma Nishio
//
//===========================================================

//**********************
// インクルードファイル
//**********************
#include "character.h"
#include "manager.h"
#include "camera.h"
#include "input.h"

//==================================
// コンストラクタ
//==================================
CCharacter::CCharacter()
{
    // 値のクリア
    m_fMove = 0.0f;
    m_nAnimCount2D = 0;
    m_nAnimPattern2D = 0;
    m_nLife = 0;
    m_nMaxLife = 0;
}
//==================================
// デストラクタ
//==================================
CCharacter::~CCharacter()
{
    // 無し
}
//==================================
// 初期化処理
//==================================
HRESULT CCharacter::Init(void)
{
    // 親クラスの初期化
    CObject2D::Init();

    // メンバ変数の初期化
    m_nLife = 10;
    m_fMove = 3.0f;

    return S_OK;;
}
//==================================
// 終了処理
//==================================
void CCharacter::Uninit(void)
{
    // 終了処理
    CObject2D::Uninit();
}
//==================================
// 更新処理
//==================================
void CCharacter::Update(void)
{
    // 無し
}
//==================================
// 移動量関係
//==================================
void CCharacter::CharactorMove(float fMove)
{
    // 移動量設定
    m_fMove = fMove;
}
//==================================
// 2Dアニメーション処理
//==================================
void CCharacter::SetAnim2D(int nMaxPattern,int nAnimCount,float TexU,float TexV)
{
    // アニメーションカウンターを加算
    m_nAnimCount2D++;

    // カウントが上限より大きくなった時
    if (m_nAnimCount2D >= nAnimCount)
    {
        m_nAnimCount2D = 0;		// カウンターを初期値に戻す

        m_nAnimPattern2D++;		// パターンナンバーを更新

        // テクスチャ座標更新
       //  SetUV(m_nAnimPattern2D * TexU, TexU + m_nAnimPattern2D * TexU, TexV); // U,U1,V1座標
    }

    // パターンナンバーが最大値より大きくなった時
    if (m_nAnimPattern2D > nMaxPattern)
    {
        m_nAnimPattern2D = 0;			// パターンナンバーを初期値に戻す
    }
}

//==================================
// オーバーロードコンストラクタ
//==================================
CCharactor3D::CCharactor3D(int nPriority) : CObject(nPriority)
{
    // 値のクリア
    m_move = VECTOR3_NULL;
    m_rotDest = VECTOR3_NULL;
    m_nLife = NULL;
    m_state = STATE_NONE;
}
//==================================
// デストラクタ
//==================================
CCharactor3D::~CCharactor3D()
{
    // 無し
}
//==================================
// 初期化処理
//==================================
HRESULT CCharactor3D::Init(void)
{
    return S_OK;
}
//==================================
// 終了処理
//==================================
void CCharactor3D::Uninit(void)
{
    // オブジェクトの破棄
    CObject::Release();
}
//==================================
// 更新処理
//==================================
void CCharactor3D::Update(void)
{
    // 無し
}
