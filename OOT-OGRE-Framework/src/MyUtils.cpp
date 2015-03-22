#include "stdafx.h"
#include "MyUtils.h"

namespace util
{
	//*** Exerise 3: define reusable utility functions
	Ogre::Matrix3 RotationMatrixXYZ(Ogre::Vector3&  orientation)
	{
		Ogre::Matrix3 rotateX, rotateY, rotateZ;
		const float angleX = orientation.x;
		const float angleY = orientation.y;
		const float angleZ = orientation.z;

        
		rotateX = Ogre::Matrix3(
			1.0, 0.0, 0.0,
			0.0, std::cos(angleX), -std::sin(angleX),
			0.0, std::sin(angleX), std::cos(angleX)
			);

		rotateY = Ogre::Matrix3(
			std::cos(angleY), 0.0, std::sin(angleY),
			0.0, 1.0, 0.0,
			-std::sin(angleY), 0.0, std::cos(angleY)
			);

		rotateZ = Ogre::Matrix3(
			std::cos(angleZ), -std::sin(angleZ), 0.0,
			std::sin(angleZ),  std::cos(angleZ), 0.0,
			0.0, 0.0, 1.0
			);

		Ogre::Matrix3 rotation = rotateZ*rotateY*rotateX;
		
		return rotation;
	}

	Ogre::Matrix3 rotate_x(float angle)
	{
		Ogre::Matrix3 matX, rotateY, rotateZ;
		matX = Ogre::Matrix3(
			1.0, 0.0, 0.0,
			0.0, std::cos(angle), -std::sin(angle),
			0.0, std::sin(angle), std::cos(angle)
			);

		return matX;
	}

	Ogre::Matrix3 rotate_y(float angle)
	{
		Ogre::Matrix3 matY;
		matY = Ogre::Matrix3(
			std::cos(angle), 0.0, std::sin(angle),
			0.0, 1.0, 0.0,
			-std::sin(angle), 0.0, std::cos(angle)
			);
		return matY;
	}

	Ogre::Matrix3 rotate_z(float angle)
	{
		Ogre::Matrix3 matZ;

		matZ = Ogre::Matrix3(
			std::cos(angle), -std::sin(angle), 0.0,
			std::sin(angle), std::cos(angle), 0.0,
			0.0, 0.0, 1.0
			);
		return matZ;
	}

	float deg2Rad(float deg)
	{
		return deg * 0.0174532925f;
	}

	/**************************************************************************************************************/

	/*Create a 4x4 rotation matrix.*/
	Ogre::Matrix4 RotationMatrixXYZW(Ogre::Vector3&  orientation)
	{
		/*initialise a 4x4 matrix for each axis rotation*/
		Ogre::Matrix4 rotateX, rotateY, rotateZ;

		/*initialise the angles from the orientation*/
		const float angleX = orientation.x;
		const float angleY = orientation.y;
		const float angleZ = orientation.z;

		/*create the x 4x4 rotation matrix*/
		rotateX = Ogre::Matrix4(
			1.0,	0.0,				0.0,				0.0,
			0.0,	std::cos(angleX),	-std::sin(angleX),	0.0,
			0.0,	std::sin(angleX),	std::cos(angleX),	0.0,
			0.0,	0.0,				0.0,				1.0
			);

		/*create the y 4x4 rotation matrix*/
		rotateY = Ogre::Matrix4(
			std::cos(angleY),	0.0,	std::sin(angleY),	0.0,
			0.0,				1.0,	0.0,				0.0,
			-std::sin(angleY),	0.0,	std::cos(angleY),	0.0,
			0.0,				0.0,	0.0,				1.0
			);

		/*create the z 4x4 rotation matrix*/
		rotateZ = Ogre::Matrix4(
			std::cos(angleZ),	-std::sin(angleZ),	0.0,	0.0,
			std::sin(angleZ),	std::cos(angleZ),	0.0,	0.0,
			0.0,				0.0,				1.0,	0.0,
			0.0,				0.0,				0.0,	1.0
			);

		/*combine these 3 matrix's in to one matrix*/
		Ogre::Matrix4 rotation = rotateZ*rotateY*rotateX;

		/*return the 4x4 rotation matrix*/
		return rotation;
	}

	/**************************************************************************************************************/

	/*Convert the rotation to a quaternion rotation.*/
	Ogre::Quaternion covertRotateToQuaternion(Ogre::Vector3 rotationAxis, float rotateAngle)
	{
		/*create the rotation matrix*/
		Ogre::Matrix3 rotateMat;

		/*create a matrix using the angle and the axis to rotate along*/
		rotateMat = util::RotationMatrixXYZ(Ogre::Vector3(rotateAngle * rotationAxis.x, 
			rotateAngle * rotationAxis.y, rotateAngle * rotationAxis.z));

		/*convert the matrix to a quaternion*/
		Ogre::Quaternion orientationQ;
		orientationQ.FromRotationMatrix(rotateMat);

		/*return the quaternion*/
		return orientationQ;
	}

	/**************************************************************************************************************/

	/*Convert the rotation to a quaternion rotation.*/
	Ogre::Quaternion covertRotateToQuaternion(Ogre::Vector3 rotation)
	{
		/*create the rotation matrix*/
		Ogre::Matrix3 rotateMat;

		/*create a matrix using the angle and the axis to rotate along*/
		rotateMat = util::RotationMatrixXYZ(Ogre::Vector3(rotation.x, rotation.y, rotation.z));

		/*convert the matrix to a quaternion*/
		Ogre::Quaternion orientationQ;
		orientationQ.FromRotationMatrix(rotateMat);

		/*return the quaternion*/
		return orientationQ;
	}

	/**************************************************************************************************************/

	/*Converts the rotate speed to a rotation angle.*/
	float convertToAngle(float speed)
	{
		/*return the converted angle*/
		return (speed * 3.141596f / 180.0f);
	}
}