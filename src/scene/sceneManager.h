#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

#include "scene.h"

class SceneManager
{
public:
	SceneManager() {}
	void init();

	template<typename T>
	void registerScene(const std::string& sName);

	void updateCurrentScene(const int Frame);

	void setScene(const std::string& sName);

	const bool findScene(const std::string& sName) const;

	const Scene* getCurrentScene() const;
private:
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_ActiveScene = nullptr;
	uint32_t nextID{0};
};

#endif // !SCENEMANAGER_H
