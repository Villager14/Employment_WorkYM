/*
* @file		AnimationManager.cpp
* @brief	アニメーションマネージャー
* @author	Morita
* @date		2024/08/25
*/

#include "pch.h"

#include "AnimationManager.h"

AnimationManager::AnimationManager(CharactorType type)
	:
	m_charaType(type),
	m_createHead(false)
{
	//		アニメーションの情報
	m_information = std::make_unique<AnimationInformation>();

	//		共通処理
	m_commonProcess = std::make_unique<AnimationCommonProcess>(this);

	if (m_charaType == CharactorType::Player)
	{
		m_animaInformation.insert({ AnimationState::Stay, std::make_unique<StayAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Walk, std::make_unique<WalkAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::CrouchingStay, std::make_unique<CrouchingStayAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::CrouchingWalk, std::make_unique<CrouchingWalkAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Dash, std::make_unique<DashAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Jump, std::make_unique<JumpAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Sliding, std::make_unique<SlidingAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Start, std::make_unique<StartAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Wire, std::make_unique<WireJumpAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::WallWalk, std::make_unique<WallWalkAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::WallJump, std::make_unique<WallJumpAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Upright, std::make_unique<UprightAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Fall, std::make_unique<FallAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Death, std::make_unique<DropDeadAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Attack, std::make_unique<AttackAnimationState>(this) });
	}
	else if (m_charaType == CharactorType::Result)
	{
		m_animaInformation.insert({ AnimationState::Upright, std::make_unique<UprightAnimationState>(this) });
		
		//		ワイヤーフレームにする
		m_information->SetWireJudgement(true);

		m_createHead = true;
	}
	else if (m_charaType == CharactorType::Title)
	{
		m_animaInformation.insert({ AnimationState::Upright, std::make_unique<UprightAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Stay, std::make_unique<StayAnimationState>(this) });
		m_animaInformation.insert({ AnimationState::Sliding, std::make_unique<WallJumpAnimationState>(this) });

		m_createHead = true;
	}
	else if (m_charaType == CharactorType::CommonEnemy)
	{
		m_animaInformation.insert({ AnimationState::HandGunStayA, std::make_unique<HandGunStay>(this) });
		m_animaInformation.insert({ AnimationState::HandGunStyleA, std::make_unique<HandGunStyle>(this) });

		m_createHead = true;

		//		銃を使う
		m_information->SetGunModelJudgement(true);
	}

	//		ボーンの処理
	m_bons = std::make_unique<ModelBones>(m_createHead, m_information->GetGunModelJudgement());

}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::Initialize()
{
	//		モデルの作製
	CreateModel(m_createHead);

	//		プレイヤー
	if (m_charaType == CharactorType::Player)
	{
		m_animationState = AnimationState::Start;

		m_istate = m_animaInformation[m_animationState].get();
	}
	//		リザルト
	else if (m_charaType == CharactorType::Result)
	{
		m_animationState = AnimationState::Upright;

		m_istate = m_animaInformation[m_animationState].get();
	}
	else if (m_charaType == CharactorType::Title)
	{
		m_animationState = AnimationState::Stay;

		m_istate = m_animaInformation[m_animationState].get();
	}
	//		敵（通常）
	else if (m_charaType == CharactorType::CommonEnemy)
	{
		m_animationState = AnimationState::HandGunStayA;

		m_istate = m_animaInformation[m_animationState].get();
	}
}

void AnimationManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_model.size());
		 i < max; ++i)
	{
		m_model[i]->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
			*LibrarySingleton::GetInstance()->GetCommonState(),
			*m_information->GetWorld(i), LibrarySingleton::GetInstance()->GetView(),
			LibrarySingleton::GetInstance()->GetProj(), m_information->GetWireJudgement());
	}
}

void AnimationManager::Execute(float speed, DirectX::SimpleMath::Vector3 position,
							   DirectX::SimpleMath::Vector2 angle, float height)
{
	m_istate->Update(speed, position, angle, height, m_bons->GetBonesInformation());

	//		ワールド座標の計算
	for (int i = 0, max = static_cast<int>(m_model.size());
		i < max; ++i)
	{
		*m_information->GetWorld(i) = DirectX::SimpleMath::Matrix::CreateScale(2.6f);

		m_bons->ParentProcess(m_information->GetWorld(i), (*m_bons->GetBonesInformation())[i].type);
	}
}

void AnimationManager::CreateModel(bool createHead)
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models/Player");

	//		モデルの読み込み
	LoadModel(L"Resources/Models/Player/Body.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/BodyUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/LArmAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/LArmUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/LHand.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/RArmAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/RArmUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/RHand.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/LLeagAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/LLeagUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/LShoes.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/RLeagAbove.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/RLeagUnder.cmo", m_effect);
	LoadModel(L"Resources/Models/Player/RShoes.cmo", m_effect);

	if (createHead) LoadModel(L"Resources/Models/Player/Head.cmo", m_effect);
	if (m_information->GetGunModelJudgement()) LoadModel(L"Resources/Models/Player/HandGun.cmo", m_effect);
}

void AnimationManager::LoadModel(const wchar_t* path, DirectX::EffectFactory* effect)
{
	m_model.push_back(DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()
		->GetD3DDevice(),
		path, *effect));

	//		ワールド座標
	m_information->SetModelWorld(DirectX::SimpleMath::Matrix::Identity);
}

void AnimationManager::ChangeState(AnimationState State)
{
	if (m_animationState == State)
	{
		return;
	}

	//		現在の状態の終了処理
	m_istate->Finalize();

	//		もし落下アニメーションだった場合
	if (m_animationState == AnimationState::Fall)
	{
		m_information->SetLandingTime(0.0f);

		//		落下中状態にする
		m_information->SetFallJudgement(true);
	}

	m_animationState = State;

	//		状態の更新
	m_istate = m_animaInformation[m_animationState].get();

	//		新しい状態の初期化処理
	m_istate->Initialize();
}

void AnimationManager::Finalize()
{
	m_model.clear();
	m_model.shrink_to_fit();
	m_information->Finalize();
}
