#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//initializing the model
	m_pModel = new Simplex::Model();

	//Load a model
	m_pModel->Load("Minecraft\\Steve.obj");

	//allocate the primitive
	m_pMesh = new MyMesh();
	m_pMesh->GenerateTorus(3.0f, 2.0f, 7, 7, C_RED);

	m_pMesh2 = new MyMesh();
	m_pMesh2->GenerateCone(0.5f, 1.0f, 6, C_GREEN);

	//create a new camera
	m_pCamera = new MyCamera();
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	//Attach the model matrix that takes me from the world coordinate system
	//m_pModel->SetModelMatrix(m_mModel);

	//Send the model to render list
	//m_pModel->AddToRenderList();
}
void Application::Display(void)
{
	//Clear the screen
	ClearScreen();
	
	//draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	static float fPos = 0.0f;
	m_pCamera->SetPosition(vector3(fPos, 0.0f, 10.0f));
	m_pCamera->SetTarget(vector3(fPos, 0.0f, 9.0f));
	fPos -= 0.01f;

	//float fRatio = static_cast<float>(m_pSystem->GetWindowWidth()) / static_cast<float>(m_pSystem->GetWindowHeight());
	float fRatio = m_pSystem->GetWindowRatio(); //Same thing as above

	vector3 m_v3LookingAt = m_v3CameraPosition;
	m_v3LookingAt.z -= 1.0f;
	matrix4 m4Projection = glm::perspective(45.0f, fRatio, 0.01f, 1000.0f);
	//matrix4 m4Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
	matrix4 m4View = glm::lookAt(vector3(0, 0, 30) + m_v3CameraPosition, vector3(0, 0, 0) + m_v3LookingAt, AXIS_Y);  //m_pCameraMngr->GetViewMatrix();
	matrix4 m4Model = ToMatrix4(m_qArcBall);

	m_pMesh->Render(m4Projection, m4View, m4Model);

	//m_pMesh2->Render(m_pCamera, glm::translate(vector3(0.0f, 0.0f, -5.0f)));

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release model
	SafeDelete(m_pModel);

	//release primitive
	SafeDelete(m_pMesh);

	//release primitive
	SafeDelete(m_pMesh2);

	//release the camera
	SafeDelete(m_pCamera);
	
	//release GUI
	ShutdownGUI();
}
