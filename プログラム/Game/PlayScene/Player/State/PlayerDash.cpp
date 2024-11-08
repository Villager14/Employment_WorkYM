/*
* @file		PlayerDash.cpp
* @brief	プレイヤーのダッシュ
* @author	Morita
* @date		2024/04/29
*/

#include "pch.h"

#include "PlayerDash.h"

#include "../Player.h"

PlayerDash::PlayerDash(Player* player)
	:
	m_player(player),
	m_acceraration(0.0f),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_deceleration(0.0f),
	m_firstSpeed(0.0f)
{
}

PlayerDash::~PlayerDash()
{
}

void PlayerDash::Initialize()
{
	//		視線ベクトル
	m_direction = m_player->GetCameraInformation()->GetViewVelocity();

	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		落下時間
	m_player->GetInformation()->SetFallTime(0.0f);

	//		ダッシュをできない状態にする
	m_player->GetInformation()->SetDashJudgement(false);

	//		初期の速度
	m_firstSpeed = m_player->GetInformation()->GetAcceleration().Length();

	//		カメラを停止させる
	m_player->GetInformation()->SetCameraStop(true);

	//		頭を揺らさない状態にする
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	//		アニメーション歩き状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Dash);

	//		ダッシュ効果音効果音の再生
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::Dash);

	//		ゲームマネージャーのダッシュフラグをONにする
	m_player->GetGameManager()->TrueFlag(GameManager::DashJudgement);
}

void PlayerDash::Update()
{
	//		移動処理
	MoveProcessing();

	//		重力処理
	m_player->GetCommonProcessing()->Gravity();
}

void PlayerDash::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerDash::Animation()
{
	//		ダッシュのアニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerDash::Render()
{
}

void PlayerDash::Finalize()
{
	m_acceraration = 0.0f;

	m_deceleration = 0.0f;

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	//--
	//		最初の速度に戻す
	//--
	
	//		加速度を受け取る
	DirectX::SimpleMath::Vector3 velocity = m_player->GetInformation()->GetAcceleration();

	//		正規化
	velocity.Normalize();

	//		加速度を設定する（速度を最初の速度にする）
	m_player->GetInformation()->SetAcceleration(velocity * m_firstSpeed);

	//		カメラを停止を終了する
	m_player->GetInformation()->SetCameraStop(false);

	//		ゲームマネージャーのダッシュフラグをOFFにする
	m_player->GetGameManager()->FalseFlag(GameManager::DashJudgement);
}

void PlayerDash::MoveProcessing()
{
	if (m_acceraration < 1.0f) Acceratation();
	else Deceleration();
}

void PlayerDash::Acceratation()
{
	m_acceraration += LibrarySingleton::GetInstance()->GetElpsedTime()
		* 8.0f;

	float move = m_acceraration;

	//		初期速度からLerpを使い加速していく
	float speed = Library::Lerp(m_firstSpeed, DASH_MAX_SPEED, move);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		加速度の設定
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::Deceleration()
{
	//		経過時間
	m_deceleration += LibrarySingleton::GetInstance()->GetElpsedTime()
		* 3.0f;

	//		一以上にならないようにする
	m_deceleration = Library::Clamp(m_deceleration, 0.0f, 1.0f);

	//		イージング関数(easeInExpo)
	float move = 0.0f;

	if (m_deceleration != 0)
	{
		move = pow(2.0f, 10.0f * m_deceleration - 10.0f);
	}

	//		初期速度からLerpを使い加速していく
	float speed = Library::Lerp(DASH_MAX_SPEED, m_firstSpeed, move);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		(m_direction * speed) *
		LibrarySingleton::GetInstance()->GetElpsedTime());

	//		加速度の設定
	m_player->GetInformation()->SetAcceleration(m_direction * speed);
}

void PlayerDash::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		壁歩き状態かどうか
	m_player->GetCommonProcessing()->WallWalkJudgement();

	//		ゴールをしているかどうか
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		状態を切り替える（ゴール）
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	if (m_deceleration >= 1.0f)
	{
		//		状態を遷移する(歩き)
		m_player->ChangeState(m_player->PlayerState::Walk);
	}
}
