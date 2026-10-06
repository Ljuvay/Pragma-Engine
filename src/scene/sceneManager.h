#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "scene.h"

class SceneManager
{
public:
	SceneManager() {}
	void init();

	template<typename T>
	const void registerScene(const std::string& sName);

	const void setScene(const std::string& sName);

	const bool findScene(const std::string& sName) const;

	const std::shared_ptr<Scene> getCurrentScene() const;
private:
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_ActiveScene = nullptr;
};

#endif // !SCENEMANAGER_H
