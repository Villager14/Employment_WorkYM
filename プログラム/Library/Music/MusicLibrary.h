/*
* @file		MusicLibrary.h
* @brief	音楽ライブラリシングルトン
* @author	Morita
* @date		2024/06/28
*/

#pragma once

#include <Audio.h>

#include <unordered_map>

class MusicLibrary final
{
private:

	//		コンストラクタ
	MusicLibrary();

public:

	//		デストラクタ
	~MusicLibrary();

	/*
	*	MusicLibraryのインスタンスを受け取る
	*
	*	@return MusicLibrary
	*/
	static MusicLibrary* const GetInstance();

	//		初期化処理
	void Initialize();

private:

	//		MusicLibraryクラスのインスタンスのポインタ
	static std::unique_ptr<MusicLibrary> m_library;

public:

	enum BGMType
	{
		TitleScene,
		PlayScene,
		ResultScene,
		Empty
	};

	enum SoundEffectType
	{
		Select,
		Decision,
		Jump,
		Dash,
		Wire,
	};

public:

	//		初期の効果音の大きさ
	const float FIRST_SOUND_EFFECT_VOLUME = 0.1f;

	//		初期のBGMの大きさ
	const float FIRST_BMG_VOLUME = 0.1f;

private:

	//		オーディオエンジンBGM
	std::unique_ptr<DirectX::AudioEngine> m_audioEngineBGM;

	//		オーディオエンジン効果音
	std::unique_ptr<DirectX::AudioEngine> m_audioEngineSoundEffect;

	//		ループサウンド
	std::unique_ptr<DirectX::SoundEffectInstance> m_audioLoop;

	//		BGMの情報
	std::unordered_map<BGMType, std::unique_ptr<DirectX::SoundEffect>> m_bgmInformation;

	//		効果音の情報
	std::unordered_map<SoundEffectType, std::unique_ptr<DirectX::SoundEffect>> m_soundEffectTypeInformation;


	//		BGMのボリューム
	float m_bgmVolume;

	//		効果音のボリューム
	float m_soundEffectVolum;

	//		再生中のBGM
	BGMType m_nowBGM;

	//		最大音量
	float m_maxVolume;

	//		マスターボリューム
	float m_mastarVolume;

public:

	/*
	*	BGMの再生
	* 
	*	@param	(type)	BGMの種類
	*/
	void PlayBGM(BGMType type) 
	{
		if (type == m_nowBGM) return;

		m_nowBGM = type;

		m_audioLoop = m_bgmInformation[m_nowBGM]->CreateInstance();

		m_audioLoop->Play(true);
	}


	/*
	*	効果音の再生
	* 
	*	@param	(tpe)	効果音の種類
	*/
	void PlaySoundEffect(SoundEffectType type)
	{
		m_soundEffectTypeInformation[type]->Play();
	}

	/*
	*	シーンの音量の遷移
	* 
	*	@param	(time)	遷移時間
	*/
	void SceneLerpVolume(float time)
	{
		//		音量の遷移
		m_bgmVolume = Library::Lerp(0.0f, m_maxVolume, time);

		//		初期のボリューム
		m_audioEngineBGM->SetMasterVolume(Library::Lerp(0.0f, m_bgmVolume, m_mastarVolume));
	}

	/*
	*	BGMのボリュームを設定する
	* 
	*	@param	(val)	ボリューム
	*/
	void SetBGMVolume(float val)
	{
		m_bgmVolume = Library::Clamp(val, 0.0f, 1.0f);

		m_audioEngineBGM->SetMasterVolume(Library::Lerp(0.0f, m_bgmVolume, m_mastarVolume));
	}

	/*
	*	効果音のボリュームを設定する
	*
	*	@param	(val)	ボリューム
	*/
	void SetSoundEffectVolume(float val)
	{
		m_soundEffectVolum = Library::Clamp(val, 0.0f, 1.0f);

		m_audioEngineSoundEffect->SetMasterVolume(Library::Lerp(0.0f, m_soundEffectVolum, m_mastarVolume));
	}

	/*
	*	マスターボリュームを設定する
	*	
	*	@param	(val)	ボリューム
	*/
	void SetMastaraVolume(float val)
	{
		m_mastarVolume = Library::Clamp(val, 0.01f, 1.0f); 

		m_audioEngineBGM->SetMasterVolume(Library::Lerp(0.0f, m_bgmVolume, m_mastarVolume));
		m_audioEngineSoundEffect->SetMasterVolume(Library::Lerp(0.0f, m_soundEffectVolum, m_mastarVolume));
	}

private:

	/*
	*	BGMの作製
	* 
	*	@param	(type)	BGMの種類
	*	@param	(path)	フォルダパス
	*/
	void CreateBGM(BGMType type, const wchar_t* path);

	/*
	*	効果音の作成
	* 
	*	@param	(type)	効果音の種類
	*	@param	(path)	ファイルパス
	*/
	void CreateSoundEffect(SoundEffectType type, const wchar_t* path);
};