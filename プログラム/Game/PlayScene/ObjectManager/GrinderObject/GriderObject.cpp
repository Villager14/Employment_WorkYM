/*
* @file		GriderObject.h
* @brief	�j�ӃI�u�W�F�N�g�̕`��
* @author	Morita
* @date		2024/08/09
*/

#include "pch.h"

#include "GriderObject.h"

#include <Effects.h>

#include "Common/ReaData.h"

#include <WICTextureLoader.h>

GriderObject::GriderObject(ObjectManager* objectManager)
	:
	m_rog(0.0f),
	m_objectManager(objectManager)
{
	//		�I�u�W�F�N�g���b�V���̐���
	//m_objectMesh = ;
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());
	m_objectMesh.push_back(std::make_unique<ObjectMesh>());

	//		�|�X�g�G�t�F�N�g�t���O�𐶐�����
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	//		�I�u�W�F�N�g���b�V���̐���
	//m_damageObjectMesh = std::make_unique<ObjectMesh>();
}

GriderObject::~GriderObject()
{
}

void GriderObject::Initialize(ObjectInformation information)
{
	m_position = information.position;

	m_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll
	(information.rotation);

	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_griderRotationObject = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/GrinderRotation.cmo", *m_effect);

	//		���f���̓ǂݍ���
	m_griderObject = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/Grinder.cmo", *m_effect);

	m_griderRotationObject->UpdateEffects([&](DirectX::IEffect* effect)
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

	m_griderObject->UpdateEffects([&](DirectX::IEffect* effect)
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

	CreateObjectMesh();

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

void GriderObject::Update()
{
	
	m_rog -= 10.0f * m_objectManager->GetGameManager()->GetGameSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_rotation = DirectX::SimpleMath::Quaternion
		::CreateFromYawPitchRoll(0.0f, 0.0f, m_rog);
}

void GriderObject::Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)
{
	//		�t���O��false�̏ꍇ���������Ȃ�	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	//		�J�����O����
	if (!m_objectManager->Culling(m_position, 500.0f))
	{
		return;
	}

	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	m_griderObject->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		m_world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&] {

			//		�|�X�g�G�t�F�N�g��
			if (flag & PostEffectFlag::Flag::Bloom || flag & PostEffectFlag::Flag::Alpha)
			{
				// �|�X�g�G�t�F�N�g���̃V�F�[�_�[�ݒ�
				context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
			}
		});
	
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	world = DirectX::SimpleMath::Matrix::CreateScale(1.0f);

	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation);
	
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_griderRotationObject->Draw(context,
		*LibrarySingleton::GetInstance()->GetCommonState(),
		world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj(), false, [&]{
			
			//		�|�X�g�G�t�F�N�g��
			if (flag & PostEffectFlag::Flag::Bloom)
			{
				// �|�X�g�G�t�F�N�g���̃V�F�[�_�[�ݒ�
				context->PSSetShader(postEffectObjectShader->GetPixselShader(), nullptr, 0);
			}
		});
}

void GriderObject::Finalize()
{
	m_griderRotationObject.reset();
	m_griderObject.reset();
	
	for (int i = 0; i < m_objectMesh.size(); ++i)
	{
		m_objectMesh[i]->Finalize();
	}
}

void GriderObject::CreateObjectMesh()
{
	//		����������
	m_objectMesh[0]->Initialize(L"Resources/ModelMesh/Grider.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh[0]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), m_position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh[0]->SetObuectType(ObjectMesh::ObjectType::Floor);

	//		����������
	m_objectMesh[1]->Initialize(L"Resources/ModelMesh/GriderRotation.obj");

	m_world = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));

	//		�ÓI�I�u�W�F�N�g�ɂ���
	m_objectMesh[1]->StaticProcess(DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0)), m_position);

	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		�I�u�W�F�N�g�̃^�C�v��ݒ�i���j
	m_objectMesh[1]->SetObuectType(ObjectMesh::ObjectType::DamageObject);
}
