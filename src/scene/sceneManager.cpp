#include "sceneManager.h"

void SceneManager::init()
{
	registerScene<SphereScene>("SphereScene");
	registerScene<MandelBulbScene>("MandelBulbScene");
	registerScene<FractalTowerScene>("FractalTowerScene");
}

template<typename T>
void SceneManager::registerScene(const std::string& sName)
{
	if (!findScene(sName)) {
		m_Scenes[sName] = std::make_shared<T>();
	}
	else
	{
		std::cerr << "ERROR: Scene " << sName << " cannot be registered again!\n";
	}
}

void SceneManager::updateCurrentScene(const RenderSettings& rS, const int Frame)
{
	m_ActiveScene->update(rS, Frame);
}

void SceneManager::setScene(const std::string& sName)
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
	return m_Scenes.contains(sName) ? true : false;
}

const Scene* SceneManager::getCurrentScene() const
{
	if (m_ActiveScene != nullptr)
	{
		return m_ActiveScene.get();
	}
	else
	{
		std::cerr << "ERROR: No active scene to fetch\n";
		return nullptr;
	}
}
