/*
* @file		LibraySingleton.h
* @brief	ライブラリシングルトン
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "DeviceResources.h"

#include <SpriteFont.h>

#include <random>

#include "Common/BinaryFile.h"

class LibrarySingleton final
{
private:

	//		コンストラクタ
	LibrarySingleton();

public:

	//		デストラクタ
	~LibrarySingleton();

	/*
	*	LibrarySingletonのインスタンスを受け取る
	*
	*	@return LibrarySingleton
	*/
	static LibrarySingleton* const GetInstance();

	//		初期化処理
	void Initialize();

public:

	//		描画距離（最大）
	const float DRAWING_DISTANCE_MAX = 370.0f;

	//		描画距離（最小）
	const float DRAWING_DISTANCE_MIN = 0.1f;

private:

	//		LibrarySingletonクラスのインスタンスのポインタ
	static std::unique_ptr<LibrarySingleton> m_library;

	//		スクリーンのサイズ
	DirectX::SimpleMath::Vector2 m_screenSize;

	//		ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	//		射影行列
	DirectX::SimpleMath::Matrix m_proj;

	//		コモンステート
	std::unique_ptr<DirectX::CommonStates> m_commonState;

	//		デバイスリソース
	std::unique_ptr<DX::DeviceResources> m_device;

	//		ステップタイマー
	DX::StepTimer* m_timer;
	
	//		キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardStateTracker;

	//		マウストラッカー
	DirectX::Mouse::ButtonStateTracker* m_buttonStateTracker;

	//		スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//		スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	//		バーテックスポジションカラー
	std::unique_ptr<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColor>> m_vertexPositionColor;

	//		バーテックスポジションカラーテクスチャ
	std::unique_ptr<DirectX::PrimitiveBatch
		<DirectX::VertexPositionColorTexture>> m_vertexPositionColorTexture;

	//		エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;

	//		デバック表示をするかどうか
	bool m_debugViewJudgment;

public:

	/*
	*	フォントを描画する
	* 
	*	@param	(string)		描画する文字の情報
	*	@param	(position)		座標
	*/
	void DrowFont(const wchar_t* string, DirectX::SimpleMath::Vector2 position)
	{
		//		デバック表示がオフの場合処理をしない
		if (!m_debugViewJudgment) return;

		m_spriteBatch->Begin();
		m_spriteFont->DrawString(m_spriteBatch.get(), string, position);
		m_spriteBatch->End();
	}

	/*
	*	デバックフォント
	*	
	*	@param	(information)	数字の情報
	*	@param	(number)		数字
	*	@param	(x)				X座標
	*	@param	(y)				Y座標
	*/
	void DebugFont(const wchar_t* information,
				  float number, int x, int y)
	{
		//		デバック表示がオフの場合処理をしない
		if (!m_debugViewJudgment) return;

		//		デバックフォント
		std::wostringstream oss;

		oss << information << " : " << number;

		DrowFont(oss.str().c_str(), 
		DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y)));
	}

	/*
	*	スクリーンのサイズを設定する
	*
	*	@param(width)	スクリーンの横サイズ
	*	@param(height)	スクリーンの縦サイズ
	*/
	void SetScreenSize(const int& width, const int& height)
	{
		m_screenSize = { static_cast<float>(width),
						 static_cast<float>(height) };
	}

	//		デバック表示をするかどうか
	void ChangeDebugView()
	{
		//		表示状態なら非表示に非表示状態なら表示にする
		if (m_debugViewJudgment) { m_debugViewJudgment = false; }
		else { m_debugViewJudgment = true; }
	}

	/*
	*	デバックをするかどうかを受け取る
	* 
	*	@return	true : デバック表示 false : デバックを表示しない
	*/
	bool GetDebugJudgement() { return m_debugViewJudgment; }

	/*
	*	範囲内のランダムな数字を受け取る
	* 
	*	@param	(min)	最小値
	*	@param	(max)	最大値
	*	@return ランダムな値
	*/
	float Random(float min, float max);

	/*
	*	ピクセルシェーダーの作製
	* 
	*	@param	(path)	ファイルパス
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader> CreatePSShader(const wchar_t* path);

	/*
	*	頂点シェーダーの作成
	* 
	*	@param	(path)	ファイルパス
	*/
	BinaryFile CreateVSShader(const wchar_t* path, Microsoft::WRL::ComPtr<ID3D11VertexShader>* vsshader);

	/*
	*	ジオメトリシェーダーの作成
	*
	*	@param	(path)	ファイルパス
	*/
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> CreateGSShader(const wchar_t* path);

	/*
	*	スクリーンのサイズを受け取る
	*
	*	@return サイズ
	*/
	const DirectX::SimpleMath::Vector2& GetScreenSize() { return m_screenSize; }

	/*
	*	コモンステートのインスタンスを受け取る
	* 
	*	@return インスタンス
	*/
	DirectX::CommonStates* GetCommonState() const { return m_commonState.get(); }

	/*
	*	デバイスリソースのインスタンスを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	DX::DeviceResources* GetDeviceResources() const { return m_device.get(); }

	/*
	*	バーテックスポジションカラーテクスチャを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* GetVertexPositionColor()
	{ return m_vertexPositionColor.get(); }

	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture >* GetVertexPositionColorTexture()
	{ return m_vertexPositionColorTexture.get(); }


	/*
	*	エフェクトファクトリーを受け取る
	* 
	*	@return インスタンス
	*/
	DirectX::EffectFactory* GetEffectFactory()
	{ return m_effectFactory.get(); }

	/*
	*	ビュー行列を設定する
	* 
	*	@param	(view) ビュー行列
	*/
	void SetView(const DirectX::SimpleMath::Matrix& view) { m_view = view; }

	/*
	*	ビュー行列を受け取る
	* 
	*	@return 行列
	*/
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }

	/*
	*	射影行列を設定する
	* 
	*	@param	(proj) 射影行列
	*/
	void SetProj(const DirectX::SimpleMath::Matrix& proj) { m_proj = proj; }

	/*
	*	射影行列を受け取る
	* 
	*	@return 行列
	*/
	DirectX::SimpleMath::Matrix& GetProj() { return m_proj; }

	/*
	*	ステップタイマーを設定する
	* 
	*	@param	(timer) ステップタイマー
	*/
	void SetStepTimer(DX::StepTimer& timer) { m_timer = &timer; }

	/*
	*	ステップタイマーを受け取る
	* 
	*	@return ステップタイマー
	*/
	const DX::StepTimer& GetStepTimer() { return *m_timer; }

	/*
	*	キーボードを設定する
	* 
	*	@param	(keyboardStateTracker)　キーボードステートトラッカーのインスタンスのポインタ
	*/
	void SetKeyboardTracker(DirectX::Keyboard::KeyboardStateTracker* keyboardStateTracker)
							{ m_keyboardStateTracker = keyboardStateTracker; }

	/*
	*	キーボードを受け取る
	* 
	*	@return キーボードステートトラッカーのポインタ
	*/
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardStateTracker()
							const { return m_keyboardStateTracker; }

	/*
	*	マウスを設定する
	* 
	*	@param	(buttonStateTracker)	ボタンステートトラッカーのインスタンのポインタ
	*/
	void SetButtonStateTracker(DirectX::Mouse::ButtonStateTracker* buttonStateTracker)
							{ m_buttonStateTracker = buttonStateTracker; }

	/*
	*	マウスを受け取る
	* 
	*	@return	ボタンステートトラッカーのポインタ
	*/
	DirectX::Mouse::ButtonStateTracker* GetButtonStateTracker()
							const {return m_buttonStateTracker;}

	/*
	*	経過秒数を受け取る
	* 
	*	@return 経過秒数
	*/
	float GetElpsedTime() { return static_cast<float>(m_timer->GetElapsedSeconds());}
};


