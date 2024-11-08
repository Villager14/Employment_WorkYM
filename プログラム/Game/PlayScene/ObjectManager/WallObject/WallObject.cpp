/*
* @file		FloorObject.cpp
* @brief	���I�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/04/04
*/

#include "pch.h"

#include "WallObject.h"

#include <Effects.h>

WallObject::WallObject(ObjectManager* objectManager)
	:
	m_wallModel{},
	m_objectManager(objectManager),
	m_time(0.0f)
{
	//		�I�u�W�F�N�g���b�V���̐���
	m_objectMesh = std::make_unique<ObjectMesh>();

	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

WallObject::~WallObject()
{

}

void WallObject::Initialize(ObjectInformation information)
{
	LoadModel(information);

	std::wostringstream oss2;

	oss2 << Library::StringToWString(information.collitionPath);

	//		����������
	m_objectMesh->Initialize(oss2.str().c_str());

	//		Y���̉�]
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY
				(DirectX::XMConvertToRadians(information.rotation.y));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh->StaticProcess(m_world, information.position);

	m_position = information.position;

	//		���W
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

	//		�I�u�W�F�N�g�^�C�v�̐ݒ�i�ǁj
	m_objectMesh->SetObuectType(ObjectMesh::ObjectType::Wall);

	if (information.effectFlag)
	{
		//		�ʏ�`�������悤�ɂ���
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

		//		�u���[�����|����悤�ɂ���
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Bloom);

		//		�u���[���̐[�x�`��͕`�悵�Ȃ�
		m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::BloomDepth);

		//		�t�H�O�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

		//		�A���t�@�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	}
	else
	{
		//		�ʏ�`�������悤�ɂ���
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Normal);

		//		�u���[�����|����悤�ɂ���
		m_postEffectFlag->FalseFlag(PostEffectFlag::Flag::Bloom);

		//		�u���[���̐[�x�`��͕`�悵�Ȃ�
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::BloomDepth);

		//		�t�H�O�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Fog);

		//		�A���t�@�̏����̏ꍇ�`�悷��
		m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	}
}

void WallObject::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_time > 5.0f)
	{
		m_time = 0.0f;
	}

	m_constBuffer.Time = { m_time, 0.0f, 0.0f, 0.0f };

	m_objectShader->UpdateBuffer(m_constBuffer);
}

void WallObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	//		�t���O��false�̏ꍇ���������Ȃ�	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	auto common = LibrarySingleton::GetInstance()->GetCommonState();
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		���f���̕`��
	m_wallModel->Draw(context, *common,
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//		�|�X�g�G�t�F�N�g��
			if (flag & PostEffectFlag::Flag::Alpha)
			{
				// �|�X�g�G�t�F�N�g���̃V�F�[�_�[�ݒ�
				context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
			}
			else
			{
				m_objectShader->SetShader(context);
			}
		});

	//		���b�V���̕`��
	//drawMesh->StaticRender(m_objectMesh.get());
}

void WallObject::Finalize()
{
	m_wallModel.reset();
	m_objectMesh->Finalize();
}

void WallObject::LoadModel(ObjectInformation information)
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		���f���̓ǂݍ���
	m_wallModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		oss.str().c_str(), *m_effect);

	m_wallModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(false);
			}
		});

	//		�I�u�W�F�N�g�V�F�[�_�[�}�l�[�W���[�̐���
	m_objectShader = std::make_unique<ObjectShaderManager>();

	//		�e�N�X�`���̓ǂݍ���
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/WallTexture.png");
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/wallFantom.png");
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/wallSpray.png");
	m_objectShader->LoadTexture(L"Resources/Texture/Object/Wall/NormalMap.png");

	//		�V�F�[�_�[�̓ǂݍ��݁i�s�N�Z���V�F�[�_�[�j
	m_objectShader->LoadShader(ObjectShaderManager::PixelShader,
					L"Resources/Shader/Model/Wall/WallPS.cso");
	m_objectShader->LoadShader(ObjectShaderManager::VertexShader,
					L"Resources/Shader/Model/Wall/WallVS.cso");

	//		�R���X�g�o�b�t�@�̍쐻
	m_objectShader->CreateConstBuffer(m_constBuffer);

}
