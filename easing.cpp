//=============================================
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
	return 1.0f - cos((t * D3DX_PI) * 0.5f);
}
//===============================
// イージングの緩やかな減速
//===============================
float CEasing::EaseOutsine(float t)
{
	return sin((t * D3DX_PI) * 0.5f);
}
//===================================
// 緩やかな加速→減速
//===================================
float CEasing::EaseInOutSine(float t)
{
	return -(cos(D3DX_PI * t) - 1.0f) * 0.5f;
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
	return 1.0f - (1.0f - t) * (1.0f - t);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuad(float t)
{
	return (float)t < 0.5f ? 2.0f * t * t : 1.0f - pow(-2.0f * t + 2.0f, 2.0f) * 0.5f;
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
	return 1.0f - pow(1.0f - t, 3.0f);
}
//===================================
// 
//===================================
float CEasing::EaseInOutCubic(float t)
{
	return (float)t < 0.5f ? 4.0f * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 3.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseBounce(float t)
{
	if (t < (1.0f / 2.75f))  // 最初のバウンド
	{
		return 20.0f * t * t;  // 強さを調整して、バウンドを強調
	}
	else if (t < (2.0f / 2.75f))  // 2番目のバウンド
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
	return 1.0f - pow(1.0f - t, 4.0f);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuart(float t)
{
	return t < 0.5f ? 8.0f * t * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 4.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseOutQuint(float t)
{
	return 1.0f - pow(1.0f - t, 5.0f);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuint(float t)
{
	return (float)t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 5.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseInBack(float t)
{
	const float s = 0.70158f;  // 引っ張り度合い
	return t * t * ((s + 1.0f) * t - s);  // 反転の動き
}
//===================================
// 
//===================================
float CEasing::EaseOutBack(float t)
{
	const float s = 0.70158f;  // 引っ張り度合い
	t -= 1.0f;
	return (t * t * ((s + 1.0f) * t + s) + 1.0f);  // 反転の動き
}
//===================================
// 
//===================================
float CEasing::EaseInOutBack(float t)
{
	const float s = 0.70158f * 1.525f;  // 引っ張り度合いの調整

	if (t < 0.5f)
	{
		t *= 2.0f;
		return 0.5f * (t * t * ((s + 1.0f) * t - s));  // 前半は反転と加速
	}
	else
	{
		t = t * 2.0f - 2.0f;
		return 0.5f * (t * t * ((s + 1.0f) * t + s) + 2.0f);  // 後半は反転と減速
	}

}

//===================================
// 
//===================================
float CEasing::EaseInElastic(float t)
{
	if (t == 0.0f)
	{
		return 0.0f;  // 開始時点
	}
	if (t == 1.0f)
	{
		return 1.0f;  // 終了時点
	}
	const float p = 0.3f;  // 振動周期
	const float s = p * 0.25f;  // 振動の強さ

	return (float)(-(pow(2.0f, 10.0f* (t -= 1.0f)) * sin((t - s) * (2.0f * D3DX_PI) / p)));  // 振動の動き
}
//===================================
// 
//===================================
float CEasing::EaseOutElastic(float t)
{
	if (t == 0.0f)
	{
		return 0.0f;  // 開始時点
	}
	if (t == 1.0f)
	{
		return 1.0f;  // 終了時点
	}

	const float p = 0.3f;  // 振動周期
	const float s = p * 0.25f;  // 振動の強さ

	return (float)(pow(2.0f, -10.0f * t) * sin((t - s) * (2.0f * D3DX_PI) / p) + 1.0f);  // 振動の動き

}
//===================================
// 
//===================================
float CEasing::EaseInOutElastic(float t)
{
	if (t == 0.0f)
	{
		return 0.0f;  // 開始時点
	}
	if (t == 1.0f)
	{
		return 1.0f;  // 終了時点
	}
	const float p = 0.3f * 1.5f;  // 振動周期
	const float s = p * 0.25f;  // 振動の強さ

	if (t < 0.5f)
	{
		return (float)(-0.5f * (pow(2.0f, 20.0f * t - 10.0f) * sin((20.0f * t - 11.125f) * (2.0f * D3DX_PI) / p)));
	}

	return (float)(pow(2.0f, -20.0f * t + 10.0f) * sin((20.0f * t - 11.125f) * (2 * D3DX_PI) / p) * 0.5f + 1.0f);

}
