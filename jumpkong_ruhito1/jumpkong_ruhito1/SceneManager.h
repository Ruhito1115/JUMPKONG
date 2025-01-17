#pragma once
//#include "SceneTitle.h"
//#include "SceneMain.h"

// �N���X�̃v���g�^�C�v�錾
// �N���X�̃|�C���^�݂̂������ꍇ�̓w�b�_�[���C���N���[�h������
// �v���g�^�C�v�錾�݂̂��s��
class SceneTitle;
class SceneMain;
class GameOverScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();

	void Update();
	void Draw();

public:
	// �񋓌^���g�p���Č��ݎ��s���̃V�[�����Ǘ�����
	enum SceneKind
	{
		kSceneTitle,
		kSceneMain,
		kGameOverScene,

		kSceneNum
	};

private:
	// ���ݎ��s���̃V�[��
	SceneKind m_kind;

	// �e�V�[���̃|�C���^
	SceneTitle* m_pSceneTitle;
	SceneMain* m_pSceneMain;
	GameOverScene* m_pGameOverScene;
};
