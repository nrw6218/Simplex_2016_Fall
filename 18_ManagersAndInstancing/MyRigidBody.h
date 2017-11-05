#pragma once
#include "MyMesh.h"
#include "MyCamera.h"
#include "Definitions.h"

/*
	Programmer: Nikolas Whiteside
	Date: November 2017
*/

namespace Simplex {

	class MyRigidBody {
	public:
		Mesh* m_BS = nullptr;
		Mesh* m_BB = nullptr;
		vector3 v3Min;
		vector3 v3Max;
		MyRigidBody(MyMesh* a_pObject);
		void Render(MyCamera* a_pCamera, matrix4 a_m4Model);
	};

}