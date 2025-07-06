#pragma once

class Scene
{
protected:
	std::list<GameObject*> gameObjects;

	std::list<GameObject*> objectsToAdd;
	std::list<GameObject*> objectsToRemove;

	std::vector<std::string> texIds;
	std::vector<std::string> fontIds;
	std::vector<std::string> soundIds;

public:
	const SceneIds Id;

	Scene(SceneIds id);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	GameObject* AddGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go);

	GameObject* FindGameObject(const std::string& name);
};

struct DrawOrderComparer
{
	bool operator()(const GameObject* a, const GameObject* b)
	{
		if (a->sortingLayer != b->sortingLayer) {
			return  a->sortingLayer < b->sortingLayer;
		}
		return a->sortingOrder < b->sortingOrder;
	}
};
