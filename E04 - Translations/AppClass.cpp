#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Make MyMesh object
	cubes = new MyMesh[46];
	locations = new matrix4[46];

	for (int i = 0; i < 46; i++) {
		cubes[i] = MyMesh();
		cubes[i].GenerateCube(1.0f, C_BLACK);
	}
	
	//Initial positions
	locations[1] = glm::translate(locations[1], vector3(-5.0f, 0.0f, 0.0f));
	locations[2] = glm::translate(locations[2], vector3(-5.0f, 1.0f, 0.0f));
	locations[3] = glm::translate(locations[3], vector3(-5.0f, 2.0f, 0.0f));

	locations[4] = glm::translate(locations[4], vector3(-4.0f, 3.0f, 0.0f));
	locations[5] = glm::translate(locations[5], vector3(-4.0f, 2.0f, 0.0f));

	locations[6] = glm::translate(locations[6], vector3(-3.0f, 6.0f, 0.0f));
	locations[7] = glm::translate(locations[7], vector3(-3.0f, 4.0f, 0.0f));
	locations[8] = glm::translate(locations[8], vector3(-3.0f, 3.0f, 0.0f));
	locations[9] = glm::translate(locations[9], vector3(-3.0f, 2.0f, 0.0f));
	locations[10] = glm::translate(locations[10], vector3(-3.0f, 1.0f, 0.0f));
	locations[11] = glm::translate(locations[11], vector3(-3.0f, 0.0f, 0.0f));

	locations[12] = glm::translate(locations[12], vector3(-2.0f, 5.0f, 0.0f));
	locations[13] = glm::translate(locations[13], vector3(-2.0f, 4.0f, 0.0f));
	locations[14] = glm::translate(locations[14], vector3(-2.0f, 2.0f, 0.0f));
	locations[15] = glm::translate(locations[15], vector3(-2.0f, 1.0f, 0.0f));
	locations[16] = glm::translate(locations[16], vector3(-2.0f, -1.0f, 0.0f));

	locations[17] = glm::translate(locations[17], vector3(-1.0f, 4.0f, 0.0f));
	locations[18] = glm::translate(locations[18], vector3(-1.0f, 3.0f, 0.0f));
	locations[19] = glm::translate(locations[19], vector3(-1.0f, 2.0f, 0.0f));
	locations[20] = glm::translate(locations[20], vector3(-1.0f, 1.0f, 0.0f));
	locations[21] = glm::translate(locations[21], vector3(-1.0f, -1.0f, 0.0f));

	locations[22] = glm::translate(locations[22], vector3(0.0f, 4.0f, 0.0f));
	locations[23] = glm::translate(locations[23], vector3(0.0f, 3.0f, 0.0f));
	locations[24] = glm::translate(locations[24], vector3(0.0f, 2.0f, 0.0f));
	locations[25] = glm::translate(locations[25], vector3(0.0f, 1.0f, 0.0f));

	locations[26] = glm::translate(locations[26], vector3(1.0f, 4.0f, 0.0f));
	locations[27] = glm::translate(locations[27], vector3(1.0f, 3.0f, 0.0f));
	locations[28] = glm::translate(locations[28], vector3(1.0f, 2.0f, 0.0f));
	locations[29] = glm::translate(locations[29], vector3(1.0f, 1.0f, 0.0f));
	locations[30] = glm::translate(locations[30], vector3(1.0f, -1.0f, 0.0f));

	locations[31] = glm::translate(locations[31], vector3(2.0f, 5.0f, 0.0f));
	locations[32] = glm::translate(locations[32], vector3(2.0f, 4.0f, 0.0f));
	locations[33] = glm::translate(locations[33], vector3(2.0f, 2.0f, 0.0f));
	locations[34] = glm::translate(locations[34], vector3(2.0f, 1.0f, 0.0f));
	locations[35] = glm::translate(locations[35], vector3(2.0f, -1.0f, 0.0f));

	locations[36] = glm::translate(locations[36], vector3(3.0f, 6.0f, 0.0f));
	locations[37] = glm::translate(locations[37], vector3(3.0f, 4.0f, 0.0f));
	locations[38] = glm::translate(locations[38], vector3(3.0f, 3.0f, 0.0f));
	locations[39] = glm::translate(locations[39], vector3(3.0f, 2.0f, 0.0f));
	locations[40] = glm::translate(locations[40], vector3(3.0f, 1.0f, 0.0f));
	locations[41] = glm::translate(locations[41], vector3(3.0f, 0.0f, 0.0f));

	locations[42] = glm::translate(locations[42], vector3(4.0f, 3.0f, 0.0f));
	locations[43] = glm::translate(locations[43], vector3(4.0f, 2.0f, 0.0f));

	locations[44] = glm::translate(locations[44], vector3(5.0f, 0.0f, 0.0f));
	locations[45] = glm::translate(locations[45], vector3(5.0f, 1.0f, 0.0f));
	locations[0] = glm::translate(locations[0], vector3(5.0f, 2.0f, 0.0f));
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//Render the cubes
	for (int i = 0; i < 46; i++) {
		//Translate the mesh and render
		locations[i] = glm::translate(locations[i], vector3(0.01f, 0.0f, 0.0f));
		cubes[i].Render(m4Projection, m4View, locations[i]);
	}
		
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
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
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}

	if (cubes != nullptr) {
		delete[] cubes;
		cubes = nullptr;
	}
	if (locations != nullptr) {
		delete[] locations;
		locations = nullptr;
	}
	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}