/*
* @file		PlayerGoal.h
* @brief	プレイヤーゴール状態
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "PlayerGoal.h"

#include "../Player.h"

PlayerGoal::PlayerGoal(Player* player)
	:
	m_player(player),
	m_firstHeight(0.0f)
{
}

PlayerGoal::~PlayerGoal()
{
}

void PlayerGoal::Initialize()
{

		//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		アニメーション立ち状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Upright);

	//		メニューを使えないようにする
	m_player->SetMenuUiseJudgement(false);

	//		加速度が０になる
	m_player->GetInformation()->SetAcceleration(DirectX::SimpleMath::Vector3::Zero);
}

void PlayerGoal::Update()
{
	//		メッシュと当たった時の処理
	m_player->GetCommonProcessing()->Gravity();
}

void PlayerGoal::Move()
{
	//		床に当たっているか
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		シーンを切り替えるかどうか
	ChangeSceneJudgement();
}

void PlayerGoal::Animation()
{
	//		待機アニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerGoal::Render()
{
}

void PlayerGoal::Finalize()
{
}

void PlayerGoal::ChangeSceneJudgement()
{
	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		マウスの取得
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Spaceまたは左クリックを押した場合復活する
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		リザルトシーンへ
		m_player->GetGameManager()->TrueFlag(GameManager::EndJudgement);
	}
}
