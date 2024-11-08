/*
* @file		PlayerCommonProcessing.cpp
* @brief	プレイヤーの共通処理クラス
* @author	Morita
* @date		2024/07/18
*/

#include "pch.h"

#include "PlayerCommonProcessing.h"

#include "Player.h"

#include <bitset>

PlayerCommonProcessing::PlayerCommonProcessing(Player* player)
	:
	m_player(player)
{
}

PlayerCommonProcessing::~PlayerCommonProcessing()
{
}

void PlayerCommonProcessing::Gravity(bool weekJudgement)
{
	float speed = 2.0f;

	//		落下時間を受け取る
	float fallTime = m_player->GetInformation()->GetFallTime();

	if (weekJudgement)
	{
		speed = 1.0f;

		//		重力加速度
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;

		m_player->GetInformation()->SetGravity(m_player->GetInformation()->
			GetGravitationalAcceleration() * (fallTime * fallTime));

	}
	else
	{
		//		重力加速度
		fallTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed * 
			(m_player->GetInformation()->GetTimeSpeed() * m_player->GetInformation()->GetTimeSpeed());

		m_player->GetInformation()->SetGravity(m_player->GetInformation()->GetGravitationalAcceleration()
											* (fallTime * fallTime));
	}

	//		落下時間を設定する
	m_player->GetInformation()->SetFallTime(fallTime);

	m_player->GetInformation()->SetPlanPosition({ m_player->GetInformation()->GetPlanPosition().x,
									 m_player->GetInformation()->GetPlanPosition().y - 
									m_player->GetInformation()->GetGravity() *
									LibrarySingleton::GetInstance()->GetElpsedTime()
									* m_player->GetInformation()->GetTimeSpeed(),
									 m_player->GetInformation()->GetPlanPosition().z });
}

bool PlayerCommonProcessing::FloorMeshHitJudgement()
{
	//		床に当たっているか
	if (m_player->GetCollitionInformation()->GetFloorMeshHitPoint().size() != 0)
	{
		//		メッシュのY座標を受け取る
		m_player->GetInformation()->SetPlanPosition({ m_player->GetInformation()->GetPlanPosition().x,
			m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y,
			m_player->GetInformation()->GetPlanPosition().z });

		//		落下時間を０にする
		m_player->GetInformation()->SetFallTime(0.0f);

		//		ジャンプできる状態にする
		m_player->GetInformation()->SetJumpJudgement(true);

		//		頭を揺らす状態にする
		m_player->GetInformation()->SetHeadShakingJudgement(true);

		return true;
	}

	//		頭を揺らさない状態にする
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	return false;
}

bool PlayerCommonProcessing::WallMeshHitJudgement()
{
	if (m_player->GetCollitionInformation()->GetWallHitVelocity().size() > 0)
	{
		DirectX::SimpleMath::Vector3 planePosition = m_player->GetInformation()->GetPlanPosition();

		planePosition.x = m_player->GetCollitionInformation()->GetWallHitVelocity()[0].x;
		planePosition.z = m_player->GetCollitionInformation()->GetWallHitVelocity()[0].y;

		m_player->GetInformation()->SetPlanPosition(planePosition);

		return true;
	}

	return false;
}

void PlayerCommonProcessing::PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed)
{
	DirectX::SimpleMath::Vector3 headPosition = m_player->GetInformation()->GetPosition();

	float heightTime = m_player->GetInformation()->GetHeightTime();

	//		一以上なら処理をしない
	if (heightTime < 1.0f)
	{
		if (!m_player->GetCollitionInformation()->GetCeilingJudgement())
		{
			//		遷移速度
			heightTime += LibrarySingleton::GetInstance()->GetElpsedTime() * speed;
		}

		//		一以上にならないようにする
		heightTime = Library::Clamp(heightTime, 0.0f, 1.0f);

		//		easeOutQuart
		float move = 1.0f - pow(1.0f - heightTime, 4.0f);

		m_player->GetInformation()->SetHeightTime(heightTime);

		//		ラープで初期の高さから立ちの高さへ
		headPosition.y = m_player->GetInformation()->GetPosition().y + Library::Lerp(firstHeight, endHeight, move);
	}
	else
	{
		headPosition.y = m_player->GetInformation()->GetPosition().y + endHeight;
	}

	if (m_player->GetInformation()->GetHeadMove() > 0.0f)
	{

		float headMove = m_player->GetInformation()->GetHeadMove();

		//		移動速度
		headMove -= m_player->GetInformation()->GetHeadMoveSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

		//		移動量の制限
		headMove = Library::Clamp(headMove, 0.0f, m_player->GetInformation()->GetHeadMoveMAX());

		

		//		頭の移動量を足す
		headPosition.x += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().x * headMove;
		headPosition.z += m_player->GetPlayerInformationCollition()->GetWallWalkNormalize().z * headMove;

		m_player->GetInformation()->SetHeadMove(headMove);
	}

	//		高さを設定する
	m_player->GetInformation()->SetPlayerHeight(headPosition);

}

void PlayerCommonProcessing::SpeedUpperLimit()
{
	float speed = m_player->GetInformation()->GetAcceleration().Length();

	if (speed <= 70.0f) return;

	DirectX::SimpleMath::Vector3 velocity = m_player->GetInformation()->GetAcceleration();

	velocity.Normalize();

	m_player->GetInformation()->SetAcceleration(velocity * 70.0f);
}

DirectX::SimpleMath::Vector3 PlayerCommonProcessing::Direction(bool* keyPressjudgement)
{
	std::bitset<4> directionbit;

	//		キーボードStateの取得
	DirectX::Keyboard::State m_keyboard = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::W))
	{
		directionbit.set(0, 1);

		direction.z += 1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::S))
	{
		directionbit.set(1, 1);

		direction.z += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::D))
	{
		directionbit.set(2, 1);

		direction.x += -1.0f;
	}

	if (m_keyboard.IsKeyDown(DirectX::Keyboard::A))
	{
		directionbit.set(3, 1);

		direction.x += 1.0f;
	}

	if (directionbit != 0)
	{
		//		キーが押されている
		*keyPressjudgement = true;
	}

	return direction;
}

DirectX::SimpleMath::Vector3 PlayerCommonProcessing::MoveDirection(const DirectX::SimpleMath::Vector3 direction)
{
	//		カメラの向き
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x));

	//		移動する方向
	return DirectX::SimpleMath::Vector3::Transform(
		direction, matrixY.Invert());
}

bool PlayerCommonProcessing::WireActionJudgement()
{
	//		ワイヤーを使用できない状態にする
	m_player->GetInformation()->SetWireJudgement(false);

	//		ワイヤーオブジェクトがない場合
	if (m_player->GetWireObjectInformation()->size() == 0)
	{
		//		処理をしない
		return false;
	}

	for (int i = 0, max = static_cast<int>((*m_player->GetWireObjectInformation()).size()); i < max; ++i)
	{

		if (!(*m_player->GetWireObjectInformation())[i].m_usedJudgement || (*m_player->GetWireObjectInformation())[i].m_actionJudgement) continue;

		//		ワイヤーのある方向
		DirectX::SimpleMath::Vector3 wireDirection = (*m_player->GetWireObjectInformation())[i].position - m_player->GetInformation()->GetPlayerHeight();

		//		視線ベクトル
		DirectX::SimpleMath::Vector3 viewDirection = m_player->GetInformation()->GetViewVelocity();

		//		正規化
		wireDirection.Normalize();
		viewDirection.Normalize();

		//		内積を取る
		float dot = wireDirection.Dot(viewDirection);

		//		ワイヤーの方向を向いていなかったら
		if (dot < 0.9f) continue;

		//		ワイヤーを使用できる状態にする
		m_player->GetInformation()->SetWireJudgement(true);

		//		マウストラッカーの値を受け取る
		DirectX::Mouse::ButtonStateTracker* mouse = LibrarySingleton::GetInstance()->GetButtonStateTracker();

		//		マウスが押された場合
		if (mouse->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		移動ワイヤーの座標を設定する
			DirectX::SimpleMath::Vector3 wireMovePosition = (*m_player->GetWireObjectInformation())[i].position;

			wireMovePosition.y -= 12.0f;

			//		移動ワイヤー座標を設定する
			m_player->GetInformation()->SetWireMovePosition(wireMovePosition);

			//m_player->ChangeState(Player::PlayerState::Wire);

			//(*m_player->GetWireObjectInformation()[i]).m_actionJudgement = true;

			m_player->ChangeWireState(i);

			return true;
		}
	}

	return false;
}

void PlayerCommonProcessing::WallWalkJudgement()
{
	//		壁に当たっている場合
	if (m_player->GetCollitionInformation()->GetMeshWallNormalize().size() == 1)
	{
		DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

		acceleation.Normalize();

		float dot = m_player->GetCollitionInformation()->GetMeshWallNormalize()[0].Dot(acceleation);

		//		プレイヤーが一定の角度を向いている場合処理をする
		if (dot <= -0.1f && dot >= -0.95f)
		{
			//		法線を代入する
			m_player->GetPlayerInformationCollition()->SetWallWalkNormalize(m_player->GetCollitionInformation()->GetMeshWallNormalize()[0]);

			//		状態を切り替える(壁歩き状態)
			m_player->ChangeState(Player::PlayerState::WallWalk);

			return;
		}
	}
}

void PlayerCommonProcessing::DashCoolTime()
{
	if (!m_player->GetInformation()->GetDashJudgement())
	{
		//		クールタイム
		float coolTime = m_player->GetInformation()->GetDashCoolTime();

		//		経過時間
		coolTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		//		一定時間たったら
		if (coolTime >= 2.0f)
		{
			m_player->GetInformation()->SetDashJudgement(true);
			coolTime = 0.0f;
		}

		//		クールタイムを設定する
		m_player->GetInformation()->SetDashCoolTime(coolTime);
	}
}
