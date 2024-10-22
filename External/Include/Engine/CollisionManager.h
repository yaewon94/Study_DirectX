#pragma once
#include "Singleton.h"
#include "LayerValues.h"

class Collider;

// 충돌한 두 Collider의 ID
union COLLIDER_ID
{
	struct
	{
		UINT left, right;
	};

	ULONGLONG ID;
};

// 두 Collider간 충돌 검사 담당 클래스
class CollisionManager : public Singleton<CollisionManager>
{
	SINGLETON(CollisionManager);

private:
	map<LAYER_TYPE, vector<Ptr<Collider>>> m_colliderMap;
	unordered_set<ULONGLONG> m_collisionSet;	// 충돌한 두 콜라이더 저장용

public:
	void AddCollider(const Ptr<Collider>& collider);
	void RemoveCollider(const Ptr<Collider>& collider);
	
public:
	void Tick();

private:
	// 다른 타입의 레이어에 속한 오브젝트 콜라이더끼리 충돌 검사
	void CheckCollision(LAYER_TYPE a, LAYER_TYPE b);
	// 충돌 여부 판별
	bool IsCollision(const Ptr<Collider>& a, const Ptr<Collider>& b);
	// 저번 프레임과 비교하여 적절한 이벤트 호출, m_CollisionSet에 추가 또는 삭제
	void ChangeCollisionSet(const Ptr<Collider>& a, const Ptr<Collider>& b, bool isCollision);
};