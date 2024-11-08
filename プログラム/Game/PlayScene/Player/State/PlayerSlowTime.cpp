/*
* @file		PlayerSlowTime.cpp
* @brief	プレイヤーの低速時間状態
* @author	Morita
* @date		2024/04/29
*/

#include "pch.h"

#include "PlayerSlowTime.h"

#include "../Player.h"

PlayerSlowTime::PlayerSlowTime(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f)
{
}

PlayerSlowTime::~PlayerSlowTime()
{
}

void PlayerSlowTime::Initialize()
{
	//		移動方向
	m_direction = m_player->GetCommonProcessing()->MoveDirection(m_player->GetInformation()->GetDirection());

	//		時間の速度を設定する
	m_player->GetInformation()->SetTimeSpeed(0.1f);

	//		高さの取得
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;
}

void PlayerSlowTime::Update()
{
	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		移動処理
	MoveProcessing();

	//		メッシュと当たった時の処理
	//m_player->Gravity();
}

void PlayerSlowTime::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());
	
	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetPosition().y + m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerSlowTime::Animation()
{
}

void PlayerSlowTime::Render()
{
}

void PlayerSlowTime::Finalize()
{
	m_time = 0.0f;

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		時間の速度を設定する
	m_player->GetInformation()->SetTimeSpeed(1.0f);

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		前方にダッシュ
	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f));
}

void PlayerSlowTime::MoveProcessing()
{
	//		キーボードStateの取得
	DirectX::Keyboard::State m_keyboard = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::D))
	{
		direction.x += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::A))
	{
		direction.x += 1.0f;
	}

	float speed = 10.0f;

	//		移動する方向
	DirectX::SimpleMath::Vector3 velocity = m_player->GetCommonProcessing()->MoveDirection(direction) * speed *
		LibrarySingleton::GetInstance()->GetElpsedTime();

	//		移動予定場所
	m_player->GetInformation()->SetPlanPosition(velocity + m_player->GetInformation()->GetPosition());

}

void PlayerSlowTime::ChangeStateJudgement()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		spaceでジャンプ
	if (keyboard.IsKeyReleased(DirectX::Keyboard::LeftShift))
	{
		//		状態を切り替える(ダッシュ状態)
		m_player->ChangeState(m_player->PlayerState::Dash);
	}

	if (m_time > 3.0f)
	{
		//		状態を切り替える(ダッシュ状態)
		m_player->ChangeState(m_player->PlayerState::Dash);
	}
}
