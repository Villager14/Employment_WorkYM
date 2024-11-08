/*
* @file		CommonEnemyBullet.h
* @brief	一般的な敵の弾
* @author	Morita
* @date		2024/05/06
*/

#include "pch.h"

#include "CommonEnemyBullet.h"

CommonEnemyBullet::CommonEnemyBullet()
	:
	m_firingJudgement(false),
	m_elapsedTime(0.0f)
{
}

CommonEnemyBullet::~CommonEnemyBullet()
{
}

void CommonEnemyBullet::Initialize()
{
	//		エフェクトファクトリーを受け取る
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		画像の読み込み
	m_effect->SetDirectory(L"Resources/Models");

	//		モデルの読み込み
	m_model = DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/CommonBullet.cmo", *m_effect);
}

void CommonEnemyBullet::Update(float timeSpeed)
{
	if (!m_firingJudgement) return;

	float speed = 80.0f;

	m_position += m_velocity * speed * timeSpeed * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		経過時間
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		一定時間経過後
	if (m_elapsedTime > 10.0f)
	{
		//		終了処理
		Finalize();
	}
}

void CommonEnemyBullet::Render()
{
	if (!m_firingJudgement) return;

	//		ワールド座標
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		モデルの描画
	m_model->Draw(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());
}

void CommonEnemyBullet::Finalize()
{
	m_elapsedTime = 0.0f;

	m_firingJudgement = false;
}
