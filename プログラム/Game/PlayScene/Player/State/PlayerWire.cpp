/*
* @file		PlayerWire.cpp
* @brief	プレイヤーのワイヤー状態
* @author	Morita
* @date		2024/05/13
*/

#include "pch.h"

#include "PlayerWire.h"

#include "../Player.h"

PlayerWire::PlayerWire(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_fallJudgement(false),
	m_length(0.0f),
	m_floorHitJudgement(false),
	m_wallHitJudgement(false),
	m_firstSpeed(0.0f),
	m_decelerationJudgement(false),
	m_accelerationSpeed(0.0f)
{
}

PlayerWire::~PlayerWire()
{
}

void PlayerWire::Initialize()
{
	//		速度の初期化処理
	SpeedInitlaize();

	//		移動方向
	m_direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	m_direction.Normalize();

	m_player->GetInformation()->SetDirection({0.0f, 0.0f, 1.0f});

	//		落下時間を０にする
	m_player->GetInformation()->SetFallTime(0.0f);

	//		距離
	m_length = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		アニメーションワイヤージャンプ状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Wire);

	//		ダッシュ効果音効果音の再生
	MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::Wire);

	//		ゲームマネージャーのダッシュフラグをONにする
	m_player->GetGameManager()->TrueFlag(GameManager::DashJudgement);
}

void PlayerWire::Update()
{
	//		移動処理
	MoveProcessing();

	//		重力処理
	m_player->GetCommonProcessing()->Gravity(true);
}

void PlayerWire::Move()
{
	//		壁メッシュの当たり判定
	if (m_player->GetCommonProcessing()->WallMeshHitJudgement())
	{
		//		影に当たっている
		if (m_fallJudgement)m_wallHitJudgement = true;
	}

	//		床に当たっているか
	if (m_player->GetCommonProcessing()->FloorMeshHitJudgement())
	{
		//		床に当たっている
		if (m_fallJudgement)m_floorHitJudgement = true;
	}
	
	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		落下状態にするかどうか
	FallJudgement();

	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerWire::Animation()
{
	//		ワイヤーアニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerWire::Render()
{
}

void PlayerWire::Finalize()
{
	m_time = 0.0f;

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_wallHitJudgement = false;

	m_floorHitJudgement = false;

	m_fallJudgement = 0.0f;

	m_decelerationJudgement = false;

	//		アニメーション待機状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Stay);

	//std::vector<WireObjectInformation>* m_wireInformation = m_player->GetWireObjectInformation();

	for (int i = 0; i < (*m_player->GetWireObjectInformation()).size(); ++i)
	{
		(*m_player->GetWireObjectInformation())[i].m_actionJudgement = false;
	}

	//		ゲームマネージャーのダッシュフラグをOFFにする
	m_player->GetGameManager()->FalseFlag(GameManager::DashJudgement);
}

void PlayerWire::MoveProcessing()
{
	//		落下状態か判断する
	if (!m_fallJudgement) AttractProcess();
	else FallProcess();

	DirectX::SimpleMath::Vector3 velocity = m_direction * m_speed;

	m_player->GetInformation()->SetAcceleration(velocity);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() + m_direction *
		m_speed * LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWire::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		ワイヤーアクションができるかどうか判断する
	m_player->GetCommonProcessing()->WireActionJudgement();

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		キーボードステートの取得
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift))
	{
		//		ダッシュできるかどうか
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->PlayerState::Dash);

			return;
		}
	}

	if (m_floorHitJudgement)
	{
		//		移動キーを押したとき
		if (keyboardState.IsKeyDown(DirectX::Keyboard::W) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::A) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::S) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::D))
		{
			//		状態を切り替える（歩き)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
		else
		{
			//		状態を切り替える（待機)
			m_player->ChangeState(m_player->PlayerState::Stay);
		}
	}

	if (m_wallHitJudgement)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation.Normalize();

		if (m_player->GetCollitionInformation()->GetMeshWallNormalize().size() == 0) return;

		float dot = m_player->GetCollitionInformation()->GetMeshWallNormalize()[0].Dot(acceleation);

		//		プレイヤーが一定の角度を向いている場合処理をする
		if (dot <= -0.2f && dot >= -0.9f)
		{
			//		法線を代入する
			m_player->GetPlayerInformationCollition()->SetWallWalkNormalize(
				(m_player->GetCollitionInformation()->GetMeshWallNormalize()[0]));

			//		状態を切り替える(壁歩き状態)
			m_player->ChangeState(m_player->PlayerState::WallWalk);
		}	
	}
}

void PlayerWire::AttractProcess()
{
	if (!m_decelerationJudgement)AccelerationProcess();
	else DecelerationProcess();
}

void PlayerWire::AccelerationProcess()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * ACCELERATION_RATE_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		速度の遷移
	m_speed = Library::Lerp(m_firstSpeed, m_firstSpeed + MAX_SPEED, m_time);

	//		現在の距離
	float nowLength = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		開始時距離と現在距離の割合が7以下の場合減速処理にする
	if (nowLength / m_length <= ACCELERATION_RATE)
	{
		//		減速処理にする
		m_decelerationJudgement = true;

		//		加速速度を現在の速度にする
		m_accelerationSpeed = m_speed;
	}
}

void PlayerWire::DecelerationProcess()
{
	//		現在の距離
	float nowLenght = (m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition()).Length();

	//		割合
	float ratio = nowLenght / m_length;

	m_speed = Library::Lerp(m_firstSpeed, m_accelerationSpeed, ratio);
}

void PlayerWire::FallProcess()
{
	//		キーを押しているかどうか
	bool keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->GetCommonProcessing()->Direction(&keyInputJudgement);

	//		正規化
	direction.Normalize();

	//		移動する方向を追加する
	m_direction += m_player->GetCommonProcessing()->MoveDirection(direction) * 0.7f * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		正規化
	m_direction.Normalize();

	//		速度が最大速度以上の場合
	if (m_speed >= m_player->GetInformation()->GetMaxSpeed())
	{
		//		最大速度にする　
		m_speed = m_player->GetInformation()->GetMaxSpeed();
	}
}

void PlayerWire::FallJudgement()
{
	//		プレイヤーから見たワイヤーオブジェクトの方向を求める
	DirectX::SimpleMath::Vector3 direction = m_player->GetInformation()->GetWireMovePosition() - m_player->GetInformation()->GetPosition();

	//		正規化
	direction.Normalize();

	//		内積
	float dot2 = m_direction.Dot(direction);

	//		プレイヤーの移動方向と現在の方向が別の場合落下処理にする
	if (dot2 < 0.0f)
	{
		m_fallJudgement = true;

		m_time = 0.0f;
	}
}

void PlayerWire::SpeedInitlaize()
{
	//		高さの取得
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y;

	//		初期速度
	m_firstSpeed = m_player->GetInformation()->GetAcceleration().Length();

	//		初期速度が歩く速度以下の場合
	if (m_firstSpeed <= m_player->GetInformation()->GetWalkSpeed())
	{
		m_firstSpeed = m_player->GetInformation()->GetWalkSpeed();
	}

	m_speed = m_firstSpeed;
}
