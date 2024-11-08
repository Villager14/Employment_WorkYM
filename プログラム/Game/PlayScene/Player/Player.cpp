/*
* @file		Player.cpp
* @brief	プレイヤーの処理
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"
#include "Player.h"

Player::Player(GameManager* gameManager)
	:
	m_state{},
	m_collitionInformation(),
	m_gameManager(gameManager),
	m_cameraInformation(),
	m_playerState{},
	m_menuUseJudgement(false)
{
	Generation();
}

Player::~Player()
{
}

void Player::Initialize()
{
	//		情報の初期化
	m_information->Initialize();

	//		プレイヤーのアニメーションの初期化
	m_playerAnimation->Initialize();

	//		初期状態
	m_playerState = PlayerState::Start;

	//		初期状態
	m_state = m_stateInformation[PlayerState::Start].get();

	//		状態を初期化する
	m_state->Initialize();

	//		立っている高さを入れておく
	m_information->SetPlayerHeight(DirectX::SimpleMath::Vector3(0.0f, m_information->GetStandingHeight(), 0.0f));
}

void Player::Generation()
{
	//		プレイヤーの情報を生成する
	m_information = std::make_unique<PlayerInformation>();

	//		派生クラスの生成
	m_stateInformation.insert({ PlayerState::Stay, std::make_unique<PlayerStay>(this) });
	m_stateInformation.insert({ PlayerState::Walk, std::make_unique<PlayerWalk>(this) });
	m_stateInformation.insert({ PlayerState::Jump, std::make_unique<PlayerJump>(this) });
	m_stateInformation.insert({ PlayerState::Crouching, std::make_unique<PlayerCrouching>(this) });
	m_stateInformation.insert({ PlayerState::Dash, std::make_unique<PlayerDash>(this) });
	m_stateInformation.insert({ PlayerState::WallWalk, std::make_unique<PlayerWallWalk>(this) });
	m_stateInformation.insert({ PlayerState::WallJump, std::make_unique<PlayerWallJump>(this) });
	m_stateInformation.insert({ PlayerState::Sliding, std::make_unique<PlayerSliding>(this) });
	m_stateInformation.insert({ PlayerState::Wire, std::make_unique<PlayerWire>(this) });
	m_stateInformation.insert({ PlayerState::Start, std::make_unique<PlayerStart>(this) });
	m_stateInformation.insert({ PlayerState::Death, std::make_unique<PlayerDeath>(this) });
	m_stateInformation.insert({ PlayerState::Goal, std::make_unique<PlayerGoal>(this) });
	m_stateInformation.insert({ PlayerState::Fall, std::make_unique<PlayerFall>(this) });

	//		プレイヤーのアニメーションの生成
	m_playerAnimation = std::make_unique<AnimationManager>(AnimationManager::Player);

	//		当たり判定用プレイヤーの情報を生成する
	m_playerInformationCollition = std::make_unique<PlayerInformationCollition>();

	//		プレイヤーの共通処理
	m_commonProcessing = std::make_unique<PlayerCommonProcessing>(this);


	//		ポストエフェクトフラグ
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	//		通常描画をするようにする
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

	//		ブルームを掛けるようにする
	m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);

	//		ブルームの深度描画は描画しない
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);

	//		フォグの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

	//		アルファの処理の場合描画する
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);

}

void Player::Update(PlayerCameraInformation* cameraInformation)
{
	m_cameraInformation = cameraInformation;

	//		更新処理
	m_state->Update();

	m_playerInformationCollition->SetPlayerPosition(m_information->GetPlanPosition());
	m_playerInformationCollition->SetPlayerHeight(m_information->GetPlayerHeight());

	//		ダッシュのクールタイムの処理
	m_commonProcessing->DashCoolTime();

	m_information->SetWallWalkNormalize(m_playerInformationCollition->GetWallWalkNormalize());

	//		デバック用
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->IsKeyPressed(DirectX::Keyboard::Enter))
	{
		m_gameManager->TrueFlag(GameManager::EndJudgement);
	}
}

void Player::MeshUpdate()
{
	//		移動処理
	m_state->Move();
}

void Player::AnimationUpdate()
{
	m_state->Animation();
}

void Player::ModelRender(PostEffectFlag::Flag flag)
{
	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	//		ボーンの描画
	m_playerAnimation->Render();
}

void Player::DebugRender()
{
	//		座標
	LibrarySingleton::GetInstance()->DebugFont(L"PositionX", m_information->GetPosition().x, 0, 0);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionY", m_information->GetPosition().y, 0, 20);
	LibrarySingleton::GetInstance()->DebugFont(L"PositionZ", m_information->GetPosition().z, 0, 40);

	//		速度
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_information->GetAcceleration().Length(), 0, 80);

	//		重力
	LibrarySingleton::GetInstance()->DebugFont(L"gravity", m_information->GetGravity(), 0, 100);
}

void Player::Finalize()
{
	m_information->Finalize();

	m_playerAnimation->Finalize();
}

void Player::DeathJudgement()
{
	if (m_gameManager->FlagJudgement(GameManager::TimeLimitJudgement))
	{
		//		死亡状態に切り替える
		ChangeState(PlayerState::Death);
	}

	//		簡易死亡判定
	if (m_information->GetPosition().y < -150.0f)
	{
		//		死亡状態に切り替える
		ChangeState(PlayerState::Death);

		//		落下死をしている
		//m_gameManager->SetFallDeadJudgement(true);
		m_gameManager->TrueFlag(GameManager::FallDead);
	}

	//		オブジェクトに当たり死亡している場合
	if (m_gameManager->FlagJudgement(GameManager::DamageObjectHit))
	{
		//		死亡状態に切り替える
		ChangeState(PlayerState::Death);
	}
}

void Player::ChangeState(PlayerState state)
{
	//		同じ状態なら処理をしない
	if (m_playerState == state) return;

	//		現在の状態の終了処理をする
	m_state->Finalize();

	//		状態を切り替える
	m_playerState = state;

	//		状態の変更
	m_state = m_stateInformation[m_playerState].get();

	//		新しい状態の初期化処理をする
	m_state->Initialize();
}

void Player::ChangeWireState(int index)
{
	//		状態を遷移する
	m_state->Finalize();

	//		ワイヤー状態にする
	m_playerState = PlayerState::Wire;

	m_state = m_stateInformation[m_playerState].get();

	(*m_wireInformation)[index].m_actionJudgement = true;

	m_state->Initialize();
}
