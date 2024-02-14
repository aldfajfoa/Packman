#include "CLEAR.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

CLEAR::CLEAR(GameObject* parent)
	:GameObject(parent, "CLEAR"), hpict_(-1)
{
}

void CLEAR::Initialize()
{
	hpict_ = Image::Load("CLEAR.png");
	assert(hpict_ >= 0);
}

void CLEAR::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
		pSM->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void CLEAR::Draw()
{
	Image::SetTransform(hpict_, transform_);
	Image::Draw(hpict_);
}

void CLEAR::Release()
{
}
