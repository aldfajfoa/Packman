#include "OVER.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

OVER::OVER(GameObject* parent)
	:GameObject(parent, "OVER"), hpict_(-1)
{
}

void OVER::Initialize()
{
	hpict_ = Image::Load("OVER.png");
	assert(hpict_ >= 0);
}

void OVER::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
		pSM->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void OVER::Draw()
{
	Image::SetTransform(hpict_, transform_);
	Image::Draw(hpict_);
}

void OVER::Release()
{
}
