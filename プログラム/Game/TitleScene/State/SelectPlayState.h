/*
* @file		SelectPlayerState.h
* @brief	プレイを選択した状態
* @author	Morita
* @date		2024/05/25
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleSelectManager.h"

class TitleSelectManager;

class SelectPlayState : public ITitleSelect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleSelectManager)	タイトル選択マネージャーのインスタンスのポインタ
	*/
	SelectPlayState(TitleSelectManager* titleSelectManager);

	//		デストラクタ
	~SelectPlayState();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	//		UIの移動
	void UIMove();

	//		シーンを切り替える処理
	void ChangeSceneProcess();

private:

	//		タイトル選択マネージャーのインスタンスのポインタ
	TitleSelectManager* m_titleSelectManager;

	//		時間
	float m_time;
};