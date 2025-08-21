//=======================================
//
// ステンシルシャドウ処理 [ shadowS.h ]
// Author: Asuma Nishio
//
//=======================================

//**********************
// インクルードファイル
//**********************
#include "shadowS.h"
#include "Manager.h"

//==================================
// オーバーロードコンストラクタ
//==================================
CShadowS::CShadowS(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_pVtx = {};
}
//==================================
// デストラクタ
//==================================
CShadowS::~CShadowS()
{
	// 無し
}
//==================================
// 初期化処理
//==================================
HRESULT CShadowS::Init()
{
	// 親クラスの初期化処理
	CObjectX::Init();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f,			0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,			SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhwの設定(1.0fで固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	// 頂点カラーの設定 ( 黒ポリゴン )
	pVtx[0].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファのアンロック
	m_pVtx->Unlock();

	// 初期化結果を返す
	return S_OK;
}
//==================================
// 終了処理
//==================================
void CShadowS::Uninit(void)
{
	// 親クラスの終了処理
	CObjectX::Uninit();
}
//==================================
// 更新処理
//==================================
void CShadowS::Update(void)
{
}
//==================================
// 描画処理
//==================================
void CShadowS::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

//*****************************************************:
	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// Zバッファへの書き込みを無効化する
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// カラーバッファへの書き込みを無効化する
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	// ステンシルバッファの比較パラメーター設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP); // 両方合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT); // ステンシルテスト合格,Zバッファ不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); // ステンシルテスト不合格

	// 表面をカリングする(表面を描画しない)
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	// 影モデルを描画する
	CObjectX::Draw();

	// ステンシルバッファの参照値を設定("1"にする)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	// ステンシルバッファの比較パラメーター設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL); // イコールに設定

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT); // 両方合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); // ステンシルテスト合格,Zバッファ不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); // ステンシルテスト不合格

	// 裏面をカリングする (裏を描画しない)
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 影モデルを描画
	CObjectX::Draw();
	
	// カラーを有効化する
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

	// ステンシルバッファの参照値を設定("2"にする)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	// ステンシルバッファの比較パラメーター設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL); // イコールに設定

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT); // 両方合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT); // ステンシルテスト合格,Zバッファ不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCRSAT); // ステンシルテスト不合格

//*****************************************************:

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャを戻す
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
//*******************************************************

	// ステンシルテストを無効化にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// Zバッファへの書き込みを有効化する
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// カリングを元に戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// カラーバッファ書き込みを有効化する
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);
}
//==================================
// 生成処理
//==================================
CShadowS* CShadowS::Create(const char* pFileName, D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	// インスタンス生成
	CShadowS* pShadowS = new CShadowS;

	// オブジェクトX設定
	pShadowS->SetFilePass(pFileName);
	pShadowS->SetPos(pos);
	pShadowS->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pShadowS->Init()))
	{
		// ポインタの破棄
		delete pShadowS;

		// nullptr初期化
		pShadowS = nullptr;

		// 失敗結果をかえす
		return nullptr;
	}

	// 生成されたポインタを返す
	return pShadowS;
}