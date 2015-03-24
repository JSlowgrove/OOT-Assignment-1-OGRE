#include "stdafx.h"
#include "MyUtils.h"

/*A namespace to contain utility functions.*/
namespace util
{
	/*Create a 4x4 rotation matrix.*/
	Ogre::Matrix3 RotationMatrixXYZ(Ogre::Vector3&  orientation)
	{
		/*get a rotation matrix for x*/
		Ogre::Matrix3 rotateX = xRotationMatrix3(orientation.x);

		/*get a rotation matrix for y*/
		Ogre::Matrix3 rotateY = yRotationMatrix3(orientation.y);

		/*get a rotation matrix for z*/
		Ogre::Matrix3 rotateZ = zRotationMatrix3(orientation.z);

		/*create a rotation matrix by combining all 3 rotation matrix's*/
		Ogre::Matrix3 resultantMatrix = rotateZ * rotateY * rotateX;

		/*return the resultant matrix*/
		return resultantMatrix;
	}

	/**************************************************************************************************************/

	/*Create a 3x3 rotation matrix for x.*/
	Ogre::Matrix3 xRotationMatrix3(float angle)
	{
		/*create the 3x3 rotation matrix*/
		Ogre::Matrix3 rotationMatrix;
		rotationMatrix = Ogre::Matrix3(
			1.0,	0.0,				0.0,
			0.0,	std::cos(angle),	-std::sin(angle),
			0.0,	std::sin(angle),	std::cos(angle)
			);

		/*return the matrix*/
		return rotationMatrix;
	}

	/**************************************************************************************************************/

	/*Create a 3x3 rotation matrix for y.*/
	Ogre::Matrix3 yRotationMatrix3(float angle)
	{
		/*create the 3x3 rotation matrix*/
		Ogre::Matrix3 rotationMatrix;
		rotationMatrix = Ogre::Matrix3(
			std::cos(angle),	0.0,	std::sin(angle),
			0.0,				1.0,	0.0,
			-std::sin(angle),	0.0,	std::cos(angle)
			);

		/*return the matrix*/
		return rotationMatrix;
	}

	/**************************************************************************************************************/

	/*Create a 3x3 rotation matrix for z.*/
	Ogre::Matrix3 zRotationMatrix3(float angle)
	{
		/*create the 3x3 rotation matrix*/
		Ogre::Matrix3 rotationMatrix;
		rotationMatrix = Ogre::Matrix3(
			std::cos(angle),	-std::sin(angle),	0.0,
			std::sin(angle),	std::cos(angle),	0.0,
			0.0,				0.0,				1.0
			);

		/*return the matrix*/
		return rotationMatrix;
	}

	/**************************************************************************************************************/

	/*Create a 4x4 rotation matrix.*/
	Ogre::Matrix4 RotationMatrixXYZW(Ogre::Vector3&  orientation)
	{
		/*create the x 4x4 rotation matrix*/
		Ogre::Matrix4 rotateX = xRotationMatrix4(orientation.x);

		/*create the y 4x4 rotation matrix*/
		Ogre::Matrix4 rotateY = yRotationMatrix4(orientation.y);

		/*create the z 4x4 rotation matrix*/
		Ogre::Matrix4 rotateZ = zRotationMatrix4(orientation.z);

		/*create a rotation matrix by combining all 3 rotation matrix's*/
		Ogre::Matrix4 resultantMatrix = rotateZ * rotateY * rotateX;

		/*return the resultant matrix*/
		return resultantMatrix;
	}
	
	/**************************************************************************************************************/

	/*Create a 4x4 rotation matrix for x.*/
	Ogre::Matrix4 xRotationMatrix4(float angle)
	{
		/*create the 4x4 rotation matrix*/
		Ogre::Matrix4 rotationMatrix;
		rotationMatrix = Ogre::Matrix4(
			1.0,	0.0,				0.0,				0.0,
			0.0,	std::cos(angle),	-std::sin(angle),	0.0,
			0.0,	std::sin(angle),	std::cos(angle),	0.0,
			0.0,	0.0,				0.0,				1.0
			);

		/*return the matrix*/
		return rotationMatrix;
	}

	/**************************************************************************************************************/

	/*Create a 4x4 rotation matrix for y.*/
	Ogre::Matrix4 yRotationMatrix4(float angle)
	{
		/*create the 4x4 rotation matrix*/
		Ogre::Matrix4 rotationMatrix;
		rotationMatrix = Ogre::Matrix4(
			std::cos(angle),	0.0,	std::sin(angle),	0.0,
			0.0,				1.0,	0.0,				0.0,
			-std::sin(angle),	0.0,	std::cos(angle),	0.0,
			0.0,				0.0,	0.0,				1.0
			);

		/*return the matrix*/
		return rotationMatrix;
	}

	/**************************************************************************************************************/

	/*Create a 4x4 rotation matrix for z.*/
	Ogre::Matrix4 zRotationMatrix4(float angle)
	{
		/*create the 4x4 rotation matrix*/
		Ogre::Matrix4 rotationMatrix;
		rotationMatrix = Ogre::Matrix4(
			std::cos(angle),	-std::sin(angle),	0.0,	0.0,
			std::sin(angle),	std::cos(angle),	0.0,	0.0,
			0.0,				0.0,				1.0,	0.0,
			0.0,				0.0,				0.0,	1.0
			);

		/*return the matrix*/
		return rotationMatrix;
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

	/*Converts the angle to a radian.*/
	float convertAngleToRadian(float angle)
	{
		/*return the radian*/
		return (angle * 3.141596f / 180.0f);
	}

	/**************************************************************************************************************/

	/*Makes sure the angle is between 0 and 360.*/
	Ogre::Real angleCheck(Ogre::Real angle, Ogre::Real angleChange)
	{
		/*work out the new angle*/
		if ((angle + angleChange) > 360)
		{
			/*store the new angle after reseting it to 0*/
			angle = (angle + angleChange) - 360;
		}
		else if ((angle + angleChange) < 0)
		{
			/*store the new angle after reseting it to 360*/
			angle = (angle + angleChange) + 360;
		}
		else
		{
			/*store the new angle*/
			angle += angleChange;
		}

		/*returns the new angle*/
		return angle;
	}
}