#pragma once
#include "Engine/GameObject.h"
class OVER :
    public GameObject
{
    int hpict_;
public:
    //�R���X�g���N�^
  //�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
    OVER(GameObject* parent);

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

