/*
* @file		ResultManager.h
* @brief	上昇番号シェーダー
* @author	Morita
* @date		2024/07/05
*/

#include "pch.h"

#include "RiseNumberShader.h"

RiseNumberShader::RiseNumberShader()
{
}

RiseNumberShader::~RiseNumberShader()
{
}

void RiseNumberShader::Initialize(int dethCount, int clearTime, int score)
{
	//		UI描画の生成
	m_uiRenderManager = std::make_unique<UIRenderManager>();

	//		シェーダーの生成
	m_uiRenderManager->Create(L"Resources/Texture/ResultScene/nomber.png",
		L"Resources/Shader/UI/AboveNumber/AboveNumberVS.cso",
		L"Resources/Shader/UI/AboveNumber/AboveNumberGS.cso",
		L"Resources/Shader/UI/AboveNumber/AboveNumberPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	//		回転量を設定する
	buffer.rotationMatrix = m_uiRenderManager->GetRotationMatrix();

	//		数字の情報の作製
	CreateNumber(DethCount1,	{ DESH_POSITION.x,								DESH_POSITION.y }, 0);
	CreateNumber(DethCount2,	{ DESH_POSITION.x + INTERVAL,					DESH_POSITION.y }, 1);
	CreateNumber(DethCount3,	{ DESH_POSITION.x + INTERVAL * 2.0f,			DESH_POSITION.y }, 2);
	CreateNumber(ClearCount1,	{ SCORE_TIME_X_POSITION,						CLEAR_TIME_Y_POSITION }, 3);
	CreateNumber(ClearCount2,	{ SCORE_TIME_X_POSITION + INTERVAL,				CLEAR_TIME_Y_POSITION }, 4);
	CreateNumber(ClearCount3,	{ SCORE_TIME_X_POSITION + INTERVAL * 2.0f,		CLEAR_TIME_Y_POSITION }, 5);
	CreateNumber(ClearCount4,	{ SCORE_TIME_X_POSITION + INTERVAL * 3.0f,		CLEAR_TIME_Y_POSITION }, 6);
	CreateNumber(Score1,		{ SCORE_TIME_X_POSITION,						SCORE_Y_POSITION }, 7);
	CreateNumber(Score2,		{ SCORE_TIME_X_POSITION + INTERVAL,				SCORE_Y_POSITION }, 8);
	CreateNumber(Score3,		{ SCORE_TIME_X_POSITION + INTERVAL * 2.0f,		SCORE_Y_POSITION }, 9);
	CreateNumber(Score4,		{ SCORE_TIME_X_POSITION + INTERVAL * 3.0f,		SCORE_Y_POSITION }, 10);

	//		死亡回数
	m_numberinformation[DethCount1].number = (dethCount / 100) % 10;
	m_numberinformation[DethCount2].number = (dethCount / 10) % 10;
	m_numberinformation[DethCount3].number =  dethCount % 10;

	//		クリアタイム
	m_numberinformation[ClearCount1].number = clearTime / 60 / 10;
	m_numberinformation[ClearCount2].number = clearTime / 60 % 10;
	m_numberinformation[ClearCount3].number = clearTime % 60 / 10;
	m_numberinformation[ClearCount4].number = clearTime % 60 % 10;

	//		スコア
	m_numberinformation[Score1].number = score / 1000;
	m_numberinformation[Score2].number = (score / 100) % 10;
	m_numberinformation[Score3].number = (score / 10) % 10;
	m_numberinformation[Score4].number = score % 10;
}

void RiseNumberShader::Render(float time)
{
	//		数字の描画
	for (auto const& pair : m_numberinformation)
	{
		//		コンストバッファの値の更新
		buffer.time = { Library::Lerp(0.0f, 1.0f, Library::Clamp((time -0.3f * pair.second.viewNumber), 0.0f, 1.0f)), 0.0f, 0.0f, 0.0f };
		buffer.number = { static_cast<float>(pair.second.number), 0.0f, 0.0f, 0.0f };

		//		座標を変更する
		m_uiRenderManager->SetPosition(pair.second.position);

		//		描画
		m_uiRenderManager->Render(buffer);
	}
}

void RiseNumberShader::Finalize()
{
	/*
	//		死亡回数
	m_numberinformation[DethCount1].position = { DESH_POSITION.x,					DESH_POSITION.y };
	m_numberinformation[DethCount2].position = { DESH_POSITION.x + INTERVAL,		DESH_POSITION.y };
	m_numberinformation[DethCount3].position = { DESH_POSITION.x + INTERVAL * 2.0f, DESH_POSITION.y };

	//		クリアタイム
	m_numberinformation[ClearCount1].position = { SCORE_TIME_X_POSITION,					CLEAR_TIME_Y_POSITION };
	m_numberinformation[ClearCount2].position = { SCORE_TIME_X_POSITION + INTERVAL,			CLEAR_TIME_Y_POSITION };
	m_numberinformation[ClearCount3].position = { SCORE_TIME_X_POSITION + INTERVAL * 2.0f,	CLEAR_TIME_Y_POSITION };
	m_numberinformation[ClearCount4].position = { SCORE_TIME_X_POSITION + INTERVAL * 3.0f,	CLEAR_TIME_Y_POSITION };

	//		スコア
	m_numberinformation[Score1].position = { SCORE_TIME_X_POSITION,						SCORE_Y_POSITION };
	m_numberinformation[Score2].position = { SCORE_TIME_X_POSITION + INTERVAL,			SCORE_Y_POSITION };
	m_numberinformation[Score3].position = { SCORE_TIME_X_POSITION + INTERVAL * 2.0f,	SCORE_Y_POSITION };
	m_numberinformation[Score4].position = { SCORE_TIME_X_POSITION + INTERVAL * 3.0f,	SCORE_Y_POSITION };
	*/

	m_uiRenderManager.reset();

	m_numberinformation.clear();
}

void RiseNumberShader::CreateNumber(NumberType type,
	DirectX::SimpleMath::Vector2 position,
	int viewNumber)
{
	NumberInformation information;

	information.position = position;
	information.number = 0;
	information.viewNumber = viewNumber;

	//		数字の情報を設定する
	m_numberinformation.insert({ type, information });
}
