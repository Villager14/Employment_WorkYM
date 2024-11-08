/*
* @file		SignboardObject.cpp
* @brief	�ŔI�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/10/31
*/

#include "pch.h"

#include "SignboardObject.h"

#include <Effects.h>

SignboardObject::SignboardObject(ObjectManager* objectManager)
	:
	m_signboardModel{},
	m_objectManager(objectManager)
{
	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();
}

SignboardObject::~SignboardObject()
{

}

void SignboardObject::Initialize(ObjectInformation information)
{
	LoadModel(information);

	//		Y���̉�]
	m_world = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(information.rotation.y));

	m_position = information.position;

	//		���W
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(information.position);

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

void SignboardObject::Update()
{
}

void SignboardObject::Render(PostEffectFlag::Flag flag,
		PostEffectObjectShader* postEffectObjectShader)
{
	//		�t���O��false�̏ꍇ���������Ȃ�	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	auto common = LibrarySingleton::GetInstance()->GetCommonState();
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		���f���̕`��
	m_signboardModel->Draw(context, *common,
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
}

void SignboardObject::Finalize()
{
	m_signboardModel.reset();
}

void SignboardObject::LoadModel(ObjectInformation information)
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	std::wostringstream oss;

	oss << Library::StringToWString(information.modelPath);

	//		���f���̓ǂݍ���
	m_signboardModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		oss.str().c_str(), *m_effect);

	m_signboardModel->UpdateEffects([&](DirectX::IEffect* effect)
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

	std::wostringstream oss2;

	oss2 << Library::StringToWString(information.collitionPath);

	//		�e�N�X�`���̓ǂݍ���
	m_objectShader->LoadTexture(oss2.str().c_str());

	//		�V�F�[�_�[�̓ǂݍ��݁i�s�N�Z���V�F�[�_�[�j
	m_objectShader->LoadShader(ObjectShaderManager::PixelShader,
		L"Resources/Shader/Model/BillShader/BillShaderPS.cso");
}
