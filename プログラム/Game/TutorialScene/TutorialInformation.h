/*
* @file		TutorialInformation.h
* @brief	チュートリアル情報
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "../PlayScene/Player/Player.h"

class TutorialInformation
{
public:

	//		コンストラクタ
	TutorialInformation()
	:
		m_player{nullptr}
	{};

	//		デストラクタ
	~TutorialInformation() {};

	//		初期化処理
	void Initialize(Player* player)
	{
		m_player = player;
	}

public:


private:

	//		プレイヤー
	Player* m_player;

public:

	/*
	*	プレイヤーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	Player* GetPlayer() { return m_player; }

};