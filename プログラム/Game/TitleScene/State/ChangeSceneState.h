/*
* @file		ChangeSceneState.h
* @brief	シーン切り替えをした状態
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../ITitleSelect.h"

#include "../TitleSelectManager.h"

class TitleSelectManager;

class ChangeSceneState : public ITitleSelect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(titleSelectManager)	タイトル選択マネージャーのインスタンスのポインタ
	*/
	ChangeSceneState(TitleSelectManager* titleSelectManager);

	//		デストラクタ
	~ChangeSceneState();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		タイトルセレクトマネージャーのインスタンスのポインタ
	TitleSelectManager* m_titleSelectManager;

	//		時間
	float m_time;
};