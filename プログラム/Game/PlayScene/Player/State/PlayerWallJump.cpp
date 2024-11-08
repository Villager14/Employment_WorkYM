/*
* @file		PlayerWallJump.cpp
* @brief	プレイヤーの壁ジャンプ
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "PlayerWallJump.h"

#include "../Player.h"

PlayerWallJump::PlayerWallJump(Player* player)
	:
	m_player(player),
	m_elapsedTime(0.0f),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_stopJump(false),
	m_rayprocessJudgement(false),
	m_rayHitJudgement(false)
{


}

PlayerWallJump::~PlayerWallJump()
{
}

void PlayerWallJump::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		移動していないかどうか
	if (m_player->GetInformation()->GetDirection().Length() < FLT_EPSILON)
	{
		//		移動していない
		m_stopJump = true;
	}
	//		移動している
	else m_stopJump = false;

	m_player->GetInformation()->SetGravity(0.0f);
	m_player->GetInformation()->SetFallTime(0.0f);

	//		ジャンプできない状態にする
	m_player->GetInformation()->SetJumpJudgement(false);

	//		アニメーション壁ジャンプ状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Jump);

	//		ジャンプ効果音の再生
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::Jump);
}

void PlayerWallJump::Update()
{
	//		ジャンプの処理
	Jump();

	//		移動処理
	MoveProcessing();

	//		重力処理
	m_player->GetCommonProcessing()->Gravity();
}

void PlayerWallJump::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		レイの処理を行うかどうか
	if (m_rayprocessJudgement)
	{
		//		当たった場所がなければ処理をしない
		if (m_player->GetCollitionInformation()->GetFloorMeshHitPoint().size() != 0)
		{
			if (abs(m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y -
				m_player->GetInformation()->GetPlanPosition().y) < 1.0f)
			{
				DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPlanPosition();

				position.y = m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y;

				m_player->GetInformation()->SetPlanPosition(position);

				m_player->GetInformation()->SetFallTime(0.0f);

				m_rayHitJudgement = true;
			}
		}
	}

	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		立つ処理
	//m_player->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態を遷移するかどうか
	ChangeStateJudgement();
}

void PlayerWallJump::Animation()
{
	//		ジャンプアニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);

}

void PlayerWallJump::Render()
{
}

void PlayerWallJump::Finalize()
{
	m_elapsedTime = 0.0f;

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_rayprocessJudgement = false;

	m_rayHitJudgement = false;
}

void PlayerWallJump::MoveProcessing()
{
	
	//		キーを押しているかどうか
	m_keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = 
		DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->GetCommonProcessing()->Direction(&m_keyInputJudgement);

	//		移動方向を設定する
	m_player->GetInformation()->SetDirection(direction);

	DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPosition();

	position.y = m_player->GetInformation()->GetPlanPosition().y;

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(position +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWallJump::Jump()
{
	//		一秒以上は処理をしない
	if (m_elapsedTime >= 1.0f)
	{
		return;
	}

	//		ジャンプする時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * JUMP_SPEED;

	//		一以上にならないようにする
	m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

	//		プレイヤーの座標を受け取る
	DirectX::SimpleMath::Vector3 m_jumpPosition = m_player->GetInformation()->GetPosition();

	//		easeInCirc
	float move = 1.0f - std::sqrt(1.0f - pow(m_elapsedTime, 2.0f));

	//		勢いを少しずつなくす
	float speed = Library::Lerp(JUMP_MAX_SPEED, JUMP_MIN_SPEED, move);

	//		移動量を計算する
	m_jumpPosition.y += speed * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		座標にセットする
	m_player->GetInformation()->SetPlanPosition(m_jumpPosition);
}

void PlayerWallJump::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		壁歩き状態かどうか
	m_player->GetCommonProcessing()->WallWalkJudgement();

	//		一秒経過後処理をする
	if (m_elapsedTime >= 1.0f) { m_rayprocessJudgement = true; }

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		キーボードステートの取得
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		Shiftを押した場合
	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift)
		&& keyboardState.IsKeyDown(DirectX::Keyboard::W))
	{		
		//		ダッシュできるかどうか
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->PlayerState::Dash);
		}
	}

	//		ゴールをしているかどうか
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		状態を切り替える（ゴール）
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		ワイヤーを飛ぶことができるかどうか
	m_player->GetCommonProcessing()->WireActionJudgement();

	//		床に当たったら別の状態にする
	if (m_rayHitJudgement)
	{
		//		キーが押されていない場合
		if (!m_keyInputJudgement)
		{
			//		状態を遷移する(待機状態)
			m_player->ChangeState(m_player->PlayerState::Stay);
		}
		else if (keyboardState.IsKeyDown(DirectX::Keyboard::LeftControl))
		{
			//		状態を遷移する(スライディング)
			m_player->ChangeState(m_player->PlayerState::Sliding);
		}
		else
		{
			//		状態を切り替える(歩き状態)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}

		return;
	}
}