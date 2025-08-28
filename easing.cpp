//============================================
//
// イージング処理 [ easing.cpp ]
// Author: Asuma Nishio
//
//=============================================

//***************************
// インクルードファイル宣言
//***************************
#include "easing.h"

//===============================
// コンストラクタ
//===============================
CEasing::CEasing()
{

}
//===============================
// デストラクタ
//===============================
CEasing::~CEasing()
{

}

//===============================
// セッター
//===============================
float CEasing::SetEase(int EaseFrame, int MaxEaseFrame)
{
	// フレームが最大まで行ったら止める
	if (EaseFrame >= MaxEaseFrame)
	{
		EaseFrame = MaxEaseFrame;
	}

	// tを求める
	float t = (float)EaseFrame / (float)MaxEaseFrame;

	// tの値を返す
	return t;
}

//===============================
// イージングの緩やかな加速
//===============================
float CEasing::EaseInsine(float t)
{
	return 1 - cos((t * D3DX_PI) / 2);
}
//===============================
// イージングの緩やかな減速
//===============================
float CEasing::EaseOutsine(float t)
{
	return sin((t * D3DX_PI) / 2);
}
//===================================
// 緩やかな加速→減速
//===================================
float CEasing::EaseInOutSine(float t)
{
	return -(cos(D3DX_PI * t) - 1) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseInQuad(float t)
{
	return t * t;
}
//===================================
// 
//===================================
float CEasing::EaseOutQuad(float t)
{
	return 1 - (1 - t) * (1 - t);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuad(float t)
{
	return (float)t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseInCubic(float t)
{
	return t * t * t;
}
//===================================
// 
//===================================
float CEasing::EaseOutCubic(float t)
{
	return 1 - pow(1 - t, 3);
}
//===================================
// 
//===================================
float CEasing::EaseInOutCubic(float t)
{
	return (float)t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseBounce(float t)
{
	if (t < (1 / 2.75f))  // 最初のバウンド
	{
		return 20.0f * t * t;  // 強さを調整して、バウンドを強調
	}
	else if (t < (2 / 2.75f))  // 2番目のバウンド
	{
		t -= (1.5f / 2.75f);
		return 20.0f * t * t + 0.75f;  // 強さを調整して、バウンドを強調
	}
	else if (t < (2.5f / 2.75f))  // 3番目のバウンド
	{
		t -= (2.25f / 2.75f);
		return 20.0f * t * t + 0.9375f;  // 強さを調整して、バウンドを強調
	}
	else  // 最後のバウンド
	{
		t -= (2.625f / 2.75f);
		return 20.0f * t * t + 0.984375f;  // 強さを調整して、バウンドを強調
	}
}

//===================================
// 
//===================================
float CEasing::EaseOutQuart(float t)
{
	return 1 - pow(1 - t, 4);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuart(float t)
{
	return t < 0.5 ? 8 * t * t * t * t : 1 - pow(-2 * t + 2, 4) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseOutQuint(float t)
{
	return 1 - pow(1 - t, 5);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuint(float t)
{
	return (float)t < 0.5 ? 16 * t * t * t * t * t : 1 - pow(-2 * t + 2, 5) / 2;
}

//===================================
// 
//===================================
float CEasing::EaseInBack(float t)
{
	const float s = 0.70158f;  // 引っ張り度合い
	return t * t * ((s + 1) * t - s);  // 反転の動き
}
//===================================
// 
//===================================
float CEasing::EaseOutBack(float t)
{
	const float s = 0.70158f;  // 引っ張り度合い
	t -= 1;
	return (t * t * ((s + 1) * t + s) + 1);  // 反転の動き
}
//===================================
// 
//===================================
float CEasing::EaseInOutBack(float t)
{
	const float s = 0.70158f * 1.525f;  // 引っ張り度合いの調整

	if (t < 0.5f)
	{
		t *= 2;
		return 0.5f * (t * t * ((s + 1) * t - s));  // 前半は反転と加速
	}
	else
	{
		t = t * 2 - 2;
		return 0.5f * (t * t * ((s + 1) * t + s) + 2);  // 後半は反転と減速
	}

}

//===================================
// 
//===================================
float CEasing::EaseInElastic(float t)
{
	if (t == 0)
	{
		return 0;  // 開始時点
	}
	if (t == 1)
	{
		return 1;  // 終了時点
	}
	const float p = 0.3f;  // 振動周期
	const float s = p / 4;  // 振動の強さ

	return (float)(-(pow(2, 10 * (t -= 1)) * sin((t - s) * (2 * D3DX_PI) / p)));  // 振動の動き
}
//===================================
// 
//===================================
float CEasing::EaseOutElastic(float t)
{
	if (t == 0)
	{
		return 0;  // 開始時点
	}
	if (t == 1)
	{
		return 1;  // 終了時点
	}

	const float p = 0.3f;  // 振動周期
	const float s = p / 4;  // 振動の強さ

	return (float)(pow(2, -10.0f * t) * sin((t - s) * (2 * D3DX_PI) / p) + 1);  // 振動の動き

}
//===================================
// 
//===================================
float CEasing::EaseInOutElastic(float t)
{
	if (t == 0)
	{
		return 0;  // 開始時点
	}
	if (t == 1)
	{
		return 1;  // 終了時点
	}
	const float p = 0.3f * 1.5f;  // 振動周期
	const float s = p / 4;  // 振動の強さ

	if (t < 0.5f)
	{
		return (float)(-0.5f * (pow(2, 20 * t - 10) * sin((20 * t - 11.125f) * (2 * D3DX_PI) / p)));
	}

	return (float)(pow(2, -20 * t + 10) * sin((20 * t - 11.125f) * (2 * D3DX_PI) / p) * 0.5f + 1);

}
