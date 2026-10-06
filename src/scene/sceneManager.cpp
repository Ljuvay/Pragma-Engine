#include "sceneManager.h"

SceneManager::SceneManager() {}

void SceneManager::init()
{
	registerScene<SphereScene>("SphereScene");
	registerScene<MandelBulbScene>("MandelBulbScene");
	registerScene<KochSnowFlakeScene>("KockSnowFlakeScene");
}

template<typename T>
const void SceneManager::registerScene(const std::string& sName)
{
	if (!findScene(sName)) {
		m_Scenes[sName] = std::make_shared<T>();
	}
	else
	{
		std::cerr << "ERROR: Scene " << sName << " cannot be registered again!\n";
	}
}

const void SceneManager::setScene(const std::string& sName)
{
	if (findScene(sName)) {
		m_ActiveScene = m_Scenes[sName];
	}
	else
	{
		std::cerr << "ERROR: Scene " << sName << " cannot be found\n";
	}
}

const bool SceneManager::findScene(const std::string& sName) const
{
	for (const auto& [key, value] : m_Scenes)
	{
		if (key == sName) return true;
	}
	return false;
}

const std::shared_ptr<Scene> SceneManager::getCurrentScene() const
{
	if (m_ActiveScene != nullptr)
	{
		return m_ActiveScene;
	}
	else
	{
		std::cerr << "ERROR: No active scene to fetch\n";
		return m_ActiveScene;
	}
}
