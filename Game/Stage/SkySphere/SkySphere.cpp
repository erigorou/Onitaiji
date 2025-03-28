// -------------------------
//
// 　天球に関するクラス
//
// --------------------------

#include "pch.h"

#include "SkySphere.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"

const float SkySphere::SKYSPHERE_SCALE = 100.f;

// -------------------------------
//  コンストラクタ
// -------------------------------
SkySphere::SkySphere()
	:
	m_skySphereModel()
{
}

// -------------------------------
//  デストラクタ
// -------------------------------
SkySphere::~SkySphere()
{
}

// -------------------------------
//  ロード処理
// -------------------------------
void SkySphere::LoadSkySphereModel()
{
	auto commonResources = CommonResources::GetInstance();
	auto device = commonResources->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_skySphereModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Stage/SkySphere/skySphere.cmo", *fx);
}

// -------------------------------
//  描画処理
// -------------------------------
void SkySphere::DrawSkySphere(
	DirectX::SimpleMath::Matrix view,
	DirectX::SimpleMath::Matrix projection
)
{
	using namespace DirectX;

	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = resources->GetCommonStates();

	// モデルのエフェクト情報を更新する処理
	m_skySphereModel->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// 個別のライトをすべて無効化する
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// モデルを自発光させる
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// 初期状態のワールドマトリックスを設定
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	// サイズを調整する
	world *= SimpleMath::Matrix::CreateScale(SKYSPHERE_SCALE);

	// 天球を描画する
	m_skySphereModel->Draw(context, *states, world, view, projection);
}