/*
* @file		DegitalRain.h
* @brief	デジタル雨マネージャー
* @author	Morita
* @date		2024/10/14
*/

#include "pch.h"

#include "DegitalRain.h"

#include "Game/PlayScene/Effect/EffectManager.h"

#include <WICTextureLoader.h>

#include "Common/BinaryFile.h"

DegitalRain::DegitalRain(EffectManager* effectManager)
	:
	m_effectManager(effectManager),
	m_time(0.0f)
{
	m_effectShaderManager = std::make_unique<EffectShaderManager<ConstBuffer>>();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

DegitalRain::~DegitalRain()
{
}

void DegitalRain::Initialzie()
{	
	m_effectShaderManager->Create(
		L"Resources/Texture/TEST.png",
		L"Resources/Shader/Effect/DegitalRain/DegitalRainVS.cso",
		L"Resources/Shader/Effect/DegitalRain/DegitalRainGS.cso",
		L"Resources/Shader/Effect/DegitalRain/DegitalRainPS.cso",
		m_constBuffer,
		{0.0f, 0.0f, 0.0f},
		{1.0f, 1.0f}
	);

	m_effectShaderManager->LoadTexture(L"Resources/Texture/TEST2.png");

	DegitalRainParameter parameta;

	for (int i = 0; i < 50; ++i)
	{
		//		パラメーターを追加
		m_parameta.push_back(parameta);

		//		座標を設定
		GenerationPosition(i);

		//		落下速度
		m_parameta[i].speed = LibrarySingleton::GetInstance()->Random(2.0f, 5.0f);

		CreateNumber(i);
	}
}

void DegitalRain::Update()
{
	for (int i = 0; i < m_parameta.size(); ++i)
	{
		m_parameta[i].position.y -= m_parameta[i].speed * LibrarySingleton::GetInstance()->GetElpsedTime();

		DirectX::SimpleMath::Vector3 cameraDirection = m_effectManager->GetCameraInformation()->GetViewVelocity();

		cameraDirection.y = 0.0f;

		cameraDirection.Normalize();

	  	DirectX::SimpleMath::Vector3 objectPos = m_parameta[i].position - m_effectManager->GetPlayerInformation()->GetPosition();

		if (objectPos.Length() > MAX_LENGTH + 5.0f ||
			objectPos.Length() < 0.0f)
		{
			GenerationPosition(i);
		}

		if (cameraDirection.Dot(objectPos) < 0.0f)
		{
			GenerationPosition(i);
		}

		if (m_parameta[i].position.y < m_parameta[i].resetHeight)
		{
			GenerationPosition(i);
		}
	}

	
	for (int i = 0; i < m_parameta.size(); ++i)
	{
		Billbord(m_effectManager->GetCameraInformation()->GetEye(),
			m_effectManager->GetCameraInformation()->GetUP(), i);
	}

	//		ソート処理
	Sort();

	//		クールタイムの処理
	CoolTime();

	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 30.0f;
}

void DegitalRain::Render(PostEffectFlag::Flag flag)
{
	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	m_effectShaderManager->RenderProcedure();

	m_constBuffer = m_effectShaderManager->GetConstBuffer();

	for (int i = 0; i < m_parameta.size(); ++i)
	{
		m_constBuffer.matWorld = m_parameta[i].billbord.Transpose();
		//DirectX::SimpleMath::Matrix world;
		//m_constBuffer.matWorld = m_parameta[i].billbord.Transpose();

		//m_constBuffer.number = { static_cast<float>(m_parameta[i].number), 0.0f, 0.0f, 0.0f };
		m_constBuffer.number = m_parameta[i].number;

		m_effectShaderManager->SetPosition(m_parameta[i].position);

		m_effectShaderManager->Render(m_constBuffer);
	}
}

int DegitalRain::BinaryDigits(int number)
{
	int answer = 100000;

	int count = 0;

	for (int i = 0;; ++i)
	{
		int val = number % 2;

		number /= 2;

		if (count == 0) answer += val;
		else
		{
			int powval = static_cast<int>(std::pow(10.0f, count));

			answer += val * powval;
		}

		count++;

		if (number <= 1)
		{
			int powval = static_cast<int>(std::pow(10.0f, count));

			answer += number * powval;

			break;
		}
	}

	return answer;
}

void DegitalRain::Sort()
{
	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 playerPosition = m_effectManager->GetPlayerInformation()->GetPosition();

	//		プレイヤーからの距離を計算する
	for (int i = 0; i < m_parameta.size(); ++i)
	{
		m_parameta[i].length = (m_parameta[i].position - playerPosition).Length();
	}

	for (int i = 0; i < m_parameta.size(); ++i)
	{
		for (int j = 0; j < m_parameta.size(); ++j)
		{
			if (m_parameta[i].length > m_parameta[j].length)
			{
				std::swap(m_parameta[i], m_parameta[j]);
			}
		}
	}
}

void DegitalRain::CreateNumber(int index)
{
	m_parameta[index].coolTime = LibrarySingleton::GetInstance()->Random(0.3f, 0.5f);

	//		乱数生成
	float random = LibrarySingleton::GetInstance()->Random(15.0f, 32.0f);

	//		描画番号
	m_parameta[index].number = BinaryDigits(static_cast<int>(random));
}

void DegitalRain::CoolTime()
{
	//		クールタイムの更新
	for (int i = 0; i < m_parameta.size(); ++i)
	{
		m_parameta[i].coolTime -= LibrarySingleton::GetInstance()->GetElpsedTime();

		//		０以下になったら
		if (m_parameta[i].coolTime < 0.0f)
		{
			//		数字の更新をする
			CreateNumber(i);
		}
	}
}

void DegitalRain::GenerationPosition(int index)
{
	DirectX::SimpleMath::Vector3 cameraDirection = m_effectManager->GetCameraInformation()->GetViewVelocity();

	cameraDirection.Normalize();

	DirectX::SimpleMath::Vector2 cameraDirectionMax = { -cameraDirection.z, cameraDirection.x };
	DirectX::SimpleMath::Vector2 cameraDirectionMin = { cameraDirection.z, -cameraDirection.x };

	DirectX::SimpleMath::Vector2 velocity = Library::Lerp23(cameraDirectionMin,
			{ cameraDirection.x, cameraDirection.z },
			cameraDirectionMax, LibrarySingleton::GetInstance()->Random(0.0f, 1.0f));

	float length = LibrarySingleton::GetInstance()->Random(MIN_LENGTH, MAX_LENGTH);

	DirectX::SimpleMath::Vector3 position = m_effectManager->GetPlayerInformation()->GetPlayerHeight();

	position.y += LibrarySingleton::GetInstance()->Random(-5.0f, 40.0f);

	DirectX::SimpleMath::Vector3 val = { velocity.x, 0.0f, velocity.y };

	val.Normalize();

	val *= length;

	position += DirectX::SimpleMath::Vector3(velocity.x, 0.0f, velocity.y) * length;

	m_parameta[index].position = position;

	m_parameta[index].resetHeight = m_effectManager->GetPlayerInformation()->GetPosition().y - 20.0f;
}

void DegitalRain::Billbord(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up, int index)
{
	//		Yの値が変化しないようにする
	DirectX::SimpleMath::Vector3 fixedEye = DirectX::SimpleMath::Vector3(eye.x, m_parameta[index].position.y, eye.z);

	DirectX::SimpleMath::Matrix  billboard = DirectX::SimpleMath::Matrix::CreateBillboard
	(DirectX::SimpleMath::Vector3::Zero, fixedEye - m_parameta[index].position, up);


	DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	billboard = rot * billboard;

	m_parameta[index].billbord = billboard;
}

void DegitalRain::Finalize()
{
	m_parameta.clear();
	
	m_time = 0.0f;
}


