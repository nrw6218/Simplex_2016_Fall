#include "MyEntityManager.h"
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	m_uEntityCount = 0;
	m_entityList.clear();
}
void MyEntityManager::Release(void)
{
	//Remove each entity
	for (uint i = 0; i < m_entityList.size(); i++) {
		MyEntity* temp = m_entityList[i];
		SafeDelete(temp);
	}

	//Set the count to 0
	m_uEntityCount = 0;
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	SafeDelete(m_pInstance);
}
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{
	//Loop and look for the unique ID
	for (uint i = 0; i < m_entityList.size(); i++) {
		if (a_sUniqueID == m_entityList[i]->GetUniqueID()) {
			return i;
		}
	}

	//Default value if it wasn't found
	return -1;
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{
	if(m_entityList.size() == 0 || a_uIndex > m_entityList.size())
		return nullptr;

	return m_entityList[a_uIndex]->GetModel();
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{
	int index = GetEntityIndex(a_sUniqueID);

	if (m_entityList.size() == 0 || index == -1)
		return nullptr;

	return m_entityList[index]->GetModel();
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{
	if (m_entityList.size() == 0 || a_uIndex > m_entityList.size())
		return nullptr;

	return m_entityList[a_uIndex]->GetRigidBody();
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	int index = GetEntityIndex(a_sUniqueID);

	if (m_entityList.size() == 0 || index == -1)
		return nullptr;

	return m_entityList[index]->GetRigidBody();
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{
	if (m_entityList.size() == 0 || a_uIndex > m_entityList.size())
		return IDENTITY_M4;

	return m_entityList[a_uIndex]->GetModelMatrix();
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{
	int index = GetEntityIndex(a_sUniqueID);

	if (m_entityList.size() == 0 || index == -1)
		return IDENTITY_M4;

	return m_entityList[index]->GetModelMatrix();
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	int index = GetEntityIndex(a_sUniqueID);

	if (!(m_entityList.size() == 0) && !(index == -1))
		m_entityList[index]->SetModelMatrix(a_m4ToWorld);
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	if (!(m_entityList.size()) == 0 && !(a_uIndex == -1))
		m_entityList[a_uIndex]->SetModelMatrix(a_m4ToWorld);
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{
	//Check for collisison between all entities in the list
	for (uint i = 0; i < m_entityList.size(); i++) {
		for (uint j = i + 1; j < m_entityList.size(); j++) {
			m_entityList[i]->IsColliding(m_entityList[j]);
		}
	}
}
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	m_entityList.push_back(new MyEntity(a_sFileName, a_sUniqueID));
	m_uEntityCount++;
}
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{
	m_entityList.push_back(GetEntity(a_uIndex));
	m_uEntityCount--;
}
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	m_entityList.push_back(GetEntity(GetEntityIndex(a_sUniqueID)));
	m_uEntityCount--;
}
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{
	if (m_entityList[a_uIndex] != nullptr) {
		return m_entityList[a_uIndex]->GetUniqueID();
	}
	else {
		return "Entity does not exist";
	}
}
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{
	if (a_uIndex < m_entityList.size()) {
		return m_entityList[a_uIndex];
	}
	else {
		return nullptr;
	}
}
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{
	//Get the entity at the index and add it to the render list
	if(a_uIndex > 0 && a_uIndex < m_entityList.size())
		m_entityList[a_uIndex]->AddToRenderList(a_bRigidBody);
}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{
	//Get the entity with the given ID and add it to the render list
	GetEntity(GetEntityIndex(a_sUniqueID))->AddToRenderList(a_bRigidBody);
}