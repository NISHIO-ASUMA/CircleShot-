//============================================
//
// イージング処理 [ easing.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _EASING_H_ // このマクロ定義がされてなかったら
#define _EASING_H_ // 2重インクルード防止のマクロ定義

//*********************************
// イージングのクラス定義
//*********************************
class CEasing
{
public:
	CEasing();
	~CEasing();

	static float EaseInsine(float t);
	static float EaseOutsine(float t);

private:

};

#endif