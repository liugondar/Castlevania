#include "Stage.h"



Stage::Stage()
{
}


Stage::~Stage()
= default;


void Stage::addObjectToList(GameObject* gameObject, vector<GameObject*> &container)
{
	container.push_back(gameObject);
}

void Stage::removeObjectFromList(GameObject* gameObject, vector<GameObject*>& container) const
{
	auto index = -1;
	for (auto i = container.begin(); i < container.end(); )
	{
		index++;
		if (index == container.size()) break;
		if (container[index] == gameObject) {
			i = container.erase(i);
		}
		else {
			++i;
		}
	}
}
