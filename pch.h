//====================================
//
// プリコンパイルヘッダー [ pch.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PCH_H_ // このマクロ定義がされてなかったら
#define _PCH_H_ // 2重インクルード防止のマクロ定義

//***************************
// インクルードファイル宣言
//***************************
#include <windows.h>
#include "d3dx9.h"					// 描画処理に必要
#include "d3d9.h"
#define DIRECTINPUT_VERSION (0x0800)// ビルド時警告対処用のマクロ
#include "dinput.h"					// 入力処理に必要
#include "Xinput.h"					// ジョイパッド処理に必要
#include "xaudio2.h"
#include <time.h>
#include <Shlwapi.h>
#include <assert.h>					// アサート関数ヘッダー
#include <stdlib.h>
#include <cstdio>

//**************************
// ライブラリのリンク宣言
//**************************
#pragma comment(lib,"d3d9.lib")		// 描画処理に必要
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	// DirectXコンポーネント(部品)使用に必要
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")	// ジョイパッド処理に必要
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"shlwapi.lib")

//**************************
// 定数宣言
//**************************
inline const D3DXVECTOR3 VECTOR3_NULL = { 0.0f, 0.0f, 0.0f }; // 座標初期化

inline const D3DXCOLOR COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };// 黒
inline const D3DXCOLOR COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f }; // 白

inline const D3DXCOLOR COLOR_RED = { 1.0f, 0.0f, 0.0f, 1.0f }; // 赤
inline const D3DXCOLOR COLOR_GREEN = { 0.0f, 1.0f, 0.0f, 1.0f }; // 緑
inline const D3DXCOLOR COLOR_YERROW = { 1.0f, 1.0f, 0.0f, 1.0f }; // 黄色
inline const D3DXCOLOR COLOR_BLUE = { 0.0f, 0.0f, 1.0f, 1.0f }; // 青

inline const D3DXCOLOR COLOR_NULL = { 0.0f, 0.0f, 0.0f, 0.0f } ; // 完全透明
inline constexpr int MAX_WORD = 512;			// 最大文字配列数

//**************************
// マクロ定義
//**************************
#define SCREEN_WIDTH (1280)		// ウインドウの幅
#define SCREEN_HEIGHT (720)		// ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// 頂点フォーマット[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL |  D3DFVF_DIFFUSE | D3DFVF_TEX1)  // 座標,法線,カラー,テクスチャ
#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2) // 座標,法線,カラー,マルチテクスチャ

//**********************
// 頂点情報[2D]の構造体
//**********************
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_2D;

//**********************
// 頂点情報[3D]の構造体
//**********************
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_3D;

//*****************************
// 頂点情報[3D_マルチ]の構造体
//*****************************
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
	D3DXVECTOR2 texM;	// マルチテクスチャ
}VERTEX_3D_MULTI;

#endif