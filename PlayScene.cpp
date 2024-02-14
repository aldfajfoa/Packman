#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Gauge.h"
#include "Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Gauge>(this);
}

void PlayScene::Update()
{
	//if (hp->GetCrr() <= 0) {
	//	SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
	//	pSM->ChangeScene(SCENE_ID::SCENE_ID_CLEAR);
	//}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
