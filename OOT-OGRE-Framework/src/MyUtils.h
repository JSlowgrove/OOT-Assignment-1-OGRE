#pragma once

#include "stdafx.h"
#include "OgreMath.h"

namespace util
{
	//*** Exerise 3: declare reusable utility functions
	Ogre::Matrix3 RotationMatrixXYZ(Ogre::Vector3&  orientation);
	Ogre::Matrix3 rotate_x(float angle);
	Ogre::Matrix3 rotate_y(float angle);
	Ogre::Matrix3 rotate_z(float angle);

	float deg2Rad(float deg);

	/**
	Create a 4x4 rotation matrix.
	@param Ogre::Vector3 The orientation of the object.
	*/
	Ogre::Matrix4 RotationMatrixXYZW(Ogre::Vector3&  orientation);

	/**
	Convert the rotation to a quaternion rotation.
	@param Ogre::Vector3 The rotation axis of the object. 
	E.g. to rotate on the x rotation axis will be (1.0f,0.0f,0.0f).
	@param float The angle to rotate by.
	*/
	Ogre::Quaternion covertRotateToQuaternion(Ogre::Vector3 rotationAxis, float rotateAngle);

	/**
	Convert the rotation to a quaternion rotation.
	@param Ogre::Vector3 The rotation of the object. 
	*/
	Ogre::Quaternion covertRotateToQuaternion(Ogre::Vector3 rotation);

	/**
	Converts the rotate speed to a rotation angle.
	@param float The speed to convert.
	@returns float The converted angle.
	*/
	float convertToAngle(float speed);	
}