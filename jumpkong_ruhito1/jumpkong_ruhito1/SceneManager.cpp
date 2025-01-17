#include "SceneManager.h"
#include <cassert>
#include "DxLib.h"

#include "Pad.h"

// �w�b�_�[�ł̓N���X�̃v���g�^�C�v�錾�݂̂��s��
// cpp�Ńw�b�_�[�̃C���N���[�h���s��
#include "SceneTitle.h"
#include "SceneMain.h"
#include "GameOverScene.h"

SceneManager::SceneManager() :
	m_kind(kSceneTitle),
	m_pSceneTitle(nullptr), // ���������m�ۂ��Ă��Ȃ����
	m_pSceneMain(nullptr),   // ���������m�ۂ��Ă��Ȃ����
	m_pGameOverScene(nullptr)	//���������m�ۂ��Ă��Ȃ����
{
	// �R���X�g���N�^�Ŋe�����o�̃������m��
	// �͕�����₷�����K�v�̂Ȃ�������������ɒu��������̂�
	// �����������͂�낵���Ȃ�

	// �K�v�ȃV�[���̂݃��������m�ۂ��邱�ƂŃ������������悭�g�p����
	// 
	// �e�V�[���̃������m��
//	m_pSceneTitle = new SceneTitle();
//	m_pSceneMain = new SceneMain();
}

SceneManager::~SceneManager()
{
	// �e�V�[���̃��������
	if (m_pSceneTitle != nullptr) // �{����delete���Ń`�F�b�N���Ă��邩��s�v
	{
		delete m_pSceneTitle;
		m_pSceneTitle = nullptr;
	}

	if (m_pSceneMain != nullptr)
	{
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
	}

	if (m_pGameOverScene != nullptr)
	{
		delete m_pGameOverScene;
		m_pGameOverScene = nullptr;
	}
}

void SceneManager::Init()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle = new SceneTitle();
		m_pSceneTitle->Init();
		break;
	case SceneManager::kSceneMain:
		m_pSceneMain = new SceneMain();
		m_pSceneMain->Init();
		break;
	case SceneManager::kGameOverScene:
		m_pGameOverScene = new GameOverScene();
		m_pGameOverScene->Init();
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // false�̏ꍇ�͕K���~�܂�
		break;
	}
}

void SceneManager::End()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->End();
		delete m_pSceneTitle;
		m_pSceneTitle = nullptr;
		break;
	case SceneManager::kSceneMain:
		m_pSceneMain->End();
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
		break;
	case SceneManager::kGameOverScene:
		m_pGameOverScene->End();
		delete m_pGameOverScene;
		m_pGameOverScene = nullptr;
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // false�̏ꍇ�͕K���~�܂�
		break;
	}
}

void SceneManager::Update()
{
	// �p�b�h���͏�Ԃ̍X�V
	Pad::Update();

	// �J�ڐ�V�[���̔ԍ�
	SceneKind nextKind = m_kind;

	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		nextKind = m_pSceneTitle->Update();
		break;
	case SceneManager::kSceneMain:
		nextKind = m_pSceneMain->Update();
		break;
	case SceneManager::kGameOverScene:
		nextKind = m_pGameOverScene->Update();
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // false�̏ꍇ�͕K���~�܂�
		break;
	}

	// ���݂̃V�[���ƈႤ�V�[���ւ̐؂�ւ���v�����ꂽ�ꍇ
	// ���̃V�[���ւ̑J�ڂ��s��
	if (nextKind != m_kind)
	{
		// ���ݎ��s���̃V�[��(m_kind)�̏I������
		End();

		// ���̃V�[���ɐ؂�ւ�
		m_kind = nextKind;
		// �؂�ւ���̃V�[���̏�����
		Init();
	}
}

void SceneManager::Draw()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Draw();
		break;
	case SceneManager::kSceneMain:
		m_pSceneMain->Draw();
		break;
	case SceneManager::kGameOverScene:
		m_pGameOverScene->Draw();
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // false�̏ꍇ�͕K���~�܂�
		break;
	}
}