// ---------------------------------------------
// 名前:	Factory.cpp
// 内容:	オブジェクトの生成・初期化を行うクラス
//			使用するキーもここで登録する
// 作成:	池田
// ---------------------------------------------


#include "pch.h"
#include "Factory.h"
#include "../Messenger/KeyboardMessenger.h"		// キー入力メッセンジャー
#include "../Messenger/EventMessenger.h"		// イベントメッセンジャー
#include "../Scene/PlayScene.h"								// プレイシーン
#include "../Camera/Camera.h"								// カメラ
#include "Effects/Particle.h"								// パーティクル
#include "../Stage/SkySphere/SkySphere.h"					// 天球
#include "../Stage/Floor/Floor.h"							// 床
#include "../Stage/Sea/Sea.h"								// 海
#include "../Stage/Wall/Wall.h"								// 壁
#include "../Player/Player.h"								// プレイヤー
#include "../Boss/Boss.h"									// 鬼（敵）
#include "../Goblin/Goblin.h"								// ゴブリン
#include "../Weapon/Sword/Sword.h"							// プレイヤーの武器
#include "../Weapon/Cudgel/Cudgel.h"						// 鬼（敵）の武器
#include "Libraries/MyLib/Collision/CollisionManager.h"		// 当たり判定統括
#include "../UI/!PlaySceneUIManager/PlaySceneUIManager.h"	// プレイシーンのUI
#include "../EnemyManager/EnemyManager.h"					// 敵マネージャー
#include "../Quest/QuestManager.h"							// クエストマネージャー

// ---------------------------------------------
/// <summary>
/// 衝突判定の生成関数
/// </summary>
/// <returns>衝突判定のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<CollisionManager> Factory::CreateCollisionManager()
{
	// 当たり判定統括を宣言する
	std::unique_ptr<CollisionManager> collisionManager;
	collisionManager = std::make_unique<CollisionManager>();
	// 当たり判定統括の設定
	return collisionManager;
}

// ---------------------------------------------
/// <summary>
/// カメラの生成関数
/// </summary>
/// <returns>カメラのポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Camera> Factory::CreateCamera()
{
	// カメラを宣言する
	std::unique_ptr<Camera> camera;
	camera = std::make_unique<Camera>();

	// カメラの設定
	return camera;
}

// ---------------------------------------------
/// <summary>
/// 天球の生成関数
/// </summary>
/// <returns>天球のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<SkySphere> Factory::CreateSkySphere()
{
	// 天球を宣言する
	std::unique_ptr<SkySphere> skySphere;
	skySphere = std::make_unique<SkySphere>();
	// 初期化処理
	skySphere->LoadSkySphereModel();
	// 天球の設定
	return skySphere;
}

// ---------------------------------------------
/// <summary>
/// パーティクルの生成関数
/// </summary>
/// <returns>パーティクルのポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Particle> Factory::CreateParticle()
{
	// パーティクルを宣言する
	std::unique_ptr<Particle> particle;
	particle = std::make_unique<Particle>();
	// 初期化処理
	particle->Create();
	// パーティクルの設定
	return particle;
}

// ---------------------------------------------
/// <summary>
/// 床の生成関数
/// </summary>
/// <returns>床のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Floor> Factory::CreateFloor()
{
	// 床を宣言する
	std::unique_ptr<Floor> floor;
	floor = std::make_unique<Floor>();
	// 床の設定
	return floor;
}

// ---------------------------------------------
/// <summary>
/// 海の生成関数
/// </summary>
/// <returns>海のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Sea> Factory::CreateSea()
{
	std::unique_ptr<Sea> sea;
	sea = std::make_unique<Sea>();
	return sea;
}

// ---------------------------------------------
/// <summary>
/// 壁の生成関数
/// </summary>
/// <returns>壁のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Wall> Factory::CreateWall()
{
	// 壁を宣言する
	std::unique_ptr<Wall> wall;
	wall = std::make_unique<Wall>();
	// 初期化処理
	wall->Initialize();
	// 壁の設定
	return wall;
}

// ---------------------------------------------
/// <summary>
/// プレイヤーの生成関数
/// </summary>
/// <returns>プレイヤーのポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Player> Factory::CreatePlayer()
{
	// プレイヤーを宣言する
	std::unique_ptr<Player> player;
	// プレイヤーを生成する
	player = std::make_unique<Player>();
	// 初期化処理
	player->Initialize();
	// キーを登録
	KeyboardMessenger::Attach(DirectX::Keyboard::X,			player.get(), KeyboardMessenger::KeyPressType::PRESSED);
	KeyboardMessenger::Attach(DirectX::Keyboard::LeftShift, player.get(), KeyboardMessenger::KeyPressType::PRESSED);
	KeyboardMessenger::Attach(DirectX::Keyboard::Left,		player.get(), KeyboardMessenger::KeyPressType::DOWN);
	KeyboardMessenger::Attach(DirectX::Keyboard::Right,		player.get(), KeyboardMessenger::KeyPressType::DOWN);
	KeyboardMessenger::Attach(DirectX::Keyboard::Up,		player.get(), KeyboardMessenger::KeyPressType::DOWN);
	KeyboardMessenger::Attach(DirectX::Keyboard::Down,		player.get(), KeyboardMessenger::KeyPressType::DOWN);

	return player;
}

// ---------------------------------------------
/// <summary>
/// 鬼（敵）の生成関数
/// </summary>
/// <returns>鬼（敵）のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Boss> Factory::CreateBoss()
{
	// 鬼（敵）を宣言する
	std::unique_ptr<Boss> boss;
	boss = std::make_unique<Boss>();
	// 初期化処理
	boss->Initialize();

	// 鬼（敵）の設定
	return boss;
}

// ---------------------------------------------
/// <summary>
/// ゴブリンの生成関数
/// </summary>
/// <returns>ゴブリンのポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Goblin> Factory::CreateGoblin()
{
	// ゴブリンの宣言
	std::unique_ptr<Goblin> goblin;
	goblin = std::make_unique<Goblin>();
	// 初期化処理
	goblin->Initialize();
	// ゴブリンの設定
	return goblin;
}

// ---------------------------------------------
/// <summary>
/// プレイヤーの武器の生成関数
/// </summary>
/// <param name="player">プレイヤーのポインタ</param>
/// <returns>プレイヤーの武器のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Sword> Factory::CreateSword(Player* player)
{
	// プレイヤーの武器を宣言する
	std::unique_ptr<Sword> sword;
	sword = std::make_unique<Sword>(player);
	// 初期化処理
	sword->Initialize();

	// プレイヤーの武器のステートを変更
	EventMessenger::Attach(EventList::ChangeSwordState, std::bind(&Sword::ChangeState, sword.get(), std::placeholders::_1));

	// プレイヤーの武器の設定
	return sword;
}

// ---------------------------------------------
/// <summary>
/// 鬼（敵）の武器の生成関数
/// </summary>
/// <param name="boss">鬼（敵）のポインタ</param>
/// <returns>鬼（敵）の武器のポインタ</returns>
// ---------------------------------------------
std::unique_ptr<Cudgel> Factory::CreateCudgel(Boss* boss)
{
	// 鬼（敵）の武器を宣言する
	std::unique_ptr<Cudgel> cudgel;

	cudgel = std::make_unique<Cudgel>(boss);
	// 初期化処理
	cudgel->Initialize();
	// 鬼（敵）の武器の設定
	return cudgel;
}

// ---------------------------------------------
/// <summary>
/// プレイシーンのUIの生成関数
/// </summary>
/// <param name="playScene">プレイシーンのポインタ</param>
/// <returns>プレイシーンのUIマネージャーのポインタ</returns>
// ---------------------------------------------
std::unique_ptr<PlaySceneUIManager> Factory::CreateUIManager(PlayScene* playScene)
{
	// プレイシーンのUIを宣言する
	std::unique_ptr<PlaySceneUIManager> uiManager;
	uiManager = std::make_unique<PlaySceneUIManager>(playScene);
	// 初期化処理
	uiManager->Initialize();
	// プレイシーンのUIの設定
	return uiManager;
}

// ---------------------------------------------
/// <summary>
/// 敵マネージャーの生成関数
/// </summary>
/// <returns>敵マネージャーのポインタ</returns>
// ---------------------------------------------
std::unique_ptr<EnemyManager> Factory::CreateEnemyManager()
{
	// 敵マネージャーを宣言する
	std::unique_ptr<EnemyManager> enemyManager;
	enemyManager = std::make_unique<EnemyManager>();
	// 初期化処理
	enemyManager->Initialize();
	// 敵マネージャーの設定
	return enemyManager;
}

// ---------------------------------------------
/// <summary>
/// クエストマネージャーの生成関数
/// </summary>
/// <param name="playScene">プレイシーンのポインタ</param>
/// <returns>クエストマネージャーのポインタ</returns>
// ---------------------------------------------
std::unique_ptr<QuestManager> Factory::CreateQuestManager(PlayScene* playScene)
{
	// クエストマネージャーを宣言する
	std::unique_ptr<QuestManager> questManager;
	questManager = std::make_unique<QuestManager>(playScene);
	// 初期化処理
	questManager->InitializeQuest();
	// クエストマネージャーの設定
	return questManager;
}