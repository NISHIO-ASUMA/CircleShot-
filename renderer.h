//====================================
//
// レンダリング処理 [ renderer.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RENDERER_H_ // このマクロ定義がされてなかったら
#define _RENDERER_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "debugproc.h"

//*************************
// レンダラークラスを定義
//*************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

	static CDebugproc* GetDebug(void) { return m_pDebug; }
	static void GetFps(int nFps);

	void SetSize(UINT uWidth, UINT uHeight) { m_Width = uWidth, m_Height = uHeight; }
	UINT GetWidth(void) { return m_Width; }
	UINT GetHeight(void) { return m_Height; }

	void OnWireFrame();
	void OffWireFrame();

	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureFeedMT(void) { return m_apTextureMT[0]; }

	static inline constexpr int NUM_FEEDBACKPOLYGON = 2; // フィードバック用ポリゴン

private:
	LPDIRECT3D9 m_pD3D;					// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3Dデバイスへのポインタ
	static CDebugproc* m_pDebug;		// デバッグ
	static int m_fps;					// fps
	bool m_isDeviceLost;				// デバイスロスト対処
	bool m_isbuller;					// ブラーかどうか

	D3DPRESENT_PARAMETERS m_d3dpp;
	UINT m_Width;
	UINT m_Height;

	LPDIRECT3DSURFACE9 m_pRenderDef; // マルチターゲットレンダリング用インターフェース保存用
	LPDIRECT3DSURFACE9 m_pZBuffDef;	 // マルチターゲットレンダリング用Zバッファ保存用

	LPDIRECT3DTEXTURE9 m_apTextureMT[NUM_FEEDBACKPOLYGON]; // レンダリングターゲット用テクスチャ
	LPDIRECT3DSURFACE9 m_apRenderMT[NUM_FEEDBACKPOLYGON];	 // テクスチャレンダリング用インターフェース
	LPDIRECT3DSURFACE9 m_pZBuffMT;	 // テクスチャレンダリング用Zバッファ
	D3DVIEWPORT9 m_viewportMT;		 // テクスチャレンダリング用ビューポート

	LPDIRECT3DVERTEXBUFFER9 m_pVtxMT;  // ポリゴン用頂点バッファ

};

#endif