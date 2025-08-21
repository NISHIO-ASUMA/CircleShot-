//====================================
//
// サウンド処理 [ sound.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SOUND_H_ // このマクロ定義がされてなかったら
#define _SOUND_H_ // 2重インクルード防止のマクロ定義

//******************************
// サウンドクラスを定義
//******************************
class CSound
{
public:
	// サウンドの種類列挙型
	enum SOUND_LABEL
	{
		SOUND_LABEL_TITLE_BGM,	// タイトルBGM
		SOUND_LABEL_GAMEBGM,	// ゲームBGM
		SOUND_LABEL_RESULTBGM,  // リザルトBGM
		SOUND_LABEL_TUTORIALBGM, // チュートリアルBGM

		SOUND_LABEL_SELECT, // キー選択SE
		SOUND_LABEL_RETURN, // 決定キーSE
		SOUND_LABEL_MAX
	};

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	// サウンド情報の構造体定義
	struct SOUNDINFO
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	};

	// サウンドの情報列挙型宣言
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/titlebgm.wav", -1},		 // タイトルBGM
		{"data/BGM/gamebgm.wav",-1},		 // ゲームBGM
		{"data/BGM/resultbgm.wav",-1},		 // リザルトBGM
		{"data/BGM/tutorialbgm.wav",-1},	 // チュートリアルBGM
		{"data/SE/keyselect.wav",0},		 // 選択キーSE
		{"data/SE/keyenter.wav",0},			 // 決定キーSE
	};

	IXAudio2* m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	int m_SoundCount;										// サウンドのカウント
	int m_SoundInterval;									// インターバルカウント

};
#endif