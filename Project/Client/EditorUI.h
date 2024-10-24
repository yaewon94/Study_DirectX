#pragma once
#include "ImguiManager.h"
#include "imgui/imgui.h"

#define SAMELINE_VALUE 130
#define CHILDSIZE_ROW 35

class ComponentUI;
class EditorUI;

typedef void(EditorUI::* EUI_CALLBACK)(void*);

template<typename T>
concept not_component_ui = std::is_base_of_v<EditorUI, T> && !std::is_base_of_v<ComponentUI, T>;

// �����͸�� ��� UI���� �ֻ��� Ŭ���� (�߻�Ŭ����)
// TODO : ���ӿ�����Ʈ ���� ���
// TODO : �� EditorUI�� X ǥ�ø� ������ �ش� ������Ʈ ���� (TransformUI ����)
// TODO : UI ������ ��ũ��Ʈ���� ����
class EditorUI
{
	NO_COPY_ASSIGN(EditorUI);

// static members
private:
	static UINT nextID;

// about EditorUI
private:
	bool m_isActive;
	bool m_isModal;	// ��� �����찡 Ȱ��ȭ �Ǿ��ִ� ������, �ٸ� �۾��� �� �� ����

	// imgui ��ü�� �̸��� ������ �Ȱ��� ��ü�� ����Ѵ�
	// ## ���� ���ڿ��� ȭ�鿡 ��µ��� �ʴ´�
	// ex) box##1, box##2 �̷� ������ ���� �̸��� �ٸ���, ȭ�鿡 ��µǴ� �̸��� ���� �� �� �ִ�
	const string m_name;

	EditorUI* m_parent;
	vector<EditorUI*> m_children;

// Destructor
protected:
	virtual ~EditorUI();

// Constructor, call Destructor
public:
	EditorUI(const string& name);
	void Destroy();

// [public] Getter, Setter
public:
	virtual EDITOR_UI_TYPE GetType() = 0;

	bool IsActive() { return m_isActive; }
	void SetActive(bool isActive);

	bool IsModal() { return m_isModal; }
	void SetModal(bool isModal) { m_isModal = isModal; }

	const string& GetName() const { return m_name; }

	const EditorUI* const GetParent() { return m_parent; }
	virtual ImVec2 GetChildSize() { return ImVec2(0, 0); }
	
	template<typename T> requires std::derived_from<T, EditorUI>
	EditorUI* GetChild()
	{
		for (EditorUI* child : m_children)
		{
			if (dynamic_cast<T*>(child) != nullptr)
			{
				return child;
			}
		}

		return nullptr;
	}

	
	// ���ø� �޼ҵ�� virtual ��� �Ұ��� �� ������� ��
	template<typename T> requires not_component_ui<T>
	void AddChild()
	{
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("�̹� ������ �ִ� UI �Դϴ�");
		}

		RegisterChild<T>(new T);
	}

// about EditorUI functions called every frame
public:
	virtual void Tick() final;
	virtual void Render() final;

// functions for overriding
protected:
	virtual void TickUpdate() {}
	virtual void RenderUpdate() = 0;

	virtual void ActivateOnOff() {}

protected:
	// ���� UI ��ü�� �޸𸮿� ���
	template<typename T> requires std::derived_from<T, EditorUI>
	const EditorUI& RegisterChild(T& t)
	{
		m_children.push_back(&t);
		m_children.back()->m_parent = this; // �θ� ����
		ImguiManager::GetInstance()->AddUI(*m_children.back()); // ImguiManager�� ���
		return *(m_children.back());
	}

	// Ÿ��Ʋ ������
	void RenderTitle();

private:
	void RenderModal();
	void RenderModalless();
	void RenderChild();
};