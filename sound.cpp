//=====================================
//
// サウンド処理 [ sound.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "sound.h"

//**************************
// 名前空間
//**************************
namespace SOUND
{
	constexpr DWORD CHUNK_HEADER_SIZE = sizeof(DWORD) * 2;	// 基本サイズ定義
	constexpr int  RIFF_FORMAT_READ_SIZE = 4;				// WAVE部分の読み込みサイズ
};

//============================
// コンストラクタ
//============================
CSound::CSound()
{
	// 値のクリア
	m_SoundInterval = 0;
	m_SoundCount = 0;
	m_pXAudio2 = NULL;
	m_pMasteringVoice = NULL;

	for (int nCnt = 0; nCnt < SOUND_LABEL_MAX; nCnt++)
	{
		m_apDataAudio[nCnt] = nullptr;
		m_aSizeAudio[nCnt] = 0;
		m_apSourceVoice[nCnt] = nullptr;
	}
}
//============================
// デストラクタ
//============================
CSound::~CSound()
{
	// 無し
}
//============================
// サウンドの初期化処理
//============================
HRESULT CSound::Init(HWND hWnd)
{
	// 値の初期化
	m_SoundCount = 0;
	m_SoundInterval = 0;

	// エラーメッセージ取得用
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);

	// 作成に失敗したら
	if (FAILED(hr))
	{
		// エラーメッセージの表示
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);

	// 生成に失敗したら
	if (FAILED(hr))
	{
		// メッセージボックスの表示
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		// NULLチェック
		if (m_pXAudio2 != NULL)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(m_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		// 生成に失敗したとき
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);

		// 生成に失敗したとき
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// チャンクデータの読み込み
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);

		// 読み込みに失敗したとき
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);

		// 失敗したとき
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);

		// 読み込みに失敗したとき
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);

		// チャンクデータの読み込み
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);

		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aSoundInfo[nCntSound].nCntLoop;

		// オーディオバッファの登録
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	return S_OK;
}
//============================
// サウンドの終了処理
//============================
void CSound::Uninit(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		// NULLチェック
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;

			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	// NULLチェック
	if (m_pXAudio2 != NULL)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}
//=================================
// サウンドを再生 (再生中なら停止)
//=================================
HRESULT CSound::PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].nCntLoop;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=========================================
// サウンドを一時停止 (サウンドラベル指定)
//=========================================
void CSound::StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}
//=========================================
// サウンドを全停止 
//=========================================
void CSound::StopSound(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}
//=========================================
// チャンクのチェック
//=========================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = SOUND::RIFF_FORMAT_READ_SIZE;

			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += SOUND::CHUNK_HEADER_SIZE;

		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}
//=========================================
// チャンクデータの読み込み
//=========================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
