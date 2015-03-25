#pragma once

#include "stdafx.h"
#include "OgreMath.h"

/**@brief A namespace to contain utility functions.*/
namespace util
{
	/**A definition of pi*/
	#define PI 3.141596f

	/**
	Create a 4x4 rotation matrix.
	@param Ogre::Vector3 The orientation of the object.
	@returns Ogre::Matrix3 The rotation matrix.
	*/
	Ogre::Matrix3 RotationMatrixXYZ(Ogre::Vector3&  orientation);

	/**
	Create a 3x3 rotation matrix for x.
	@param float The angle.
	@returns Ogre::Matrix3 The rotation matrix.
	*/
	Ogre::Matrix3 xRotationMatrix3(float angle);

	/**
	Create a 3x3 rotation matrix for y.
	@param float The angle.
	@returns Ogre::Matrix3 The rotation matrix.
	*/
	Ogre::Matrix3 yRotationMatrix3(float angle);

	/**
	Create a 3x3 rotation matrix for z.
	@param float The angle.
	@returns Ogre::Matrix3 The rotation matrix.
	*/
	Ogre::Matrix3 zRotationMatrix3(float angle);

	/**
	Create a 4x4 rotation matrix.
	@param Ogre::Vector3 The orientation of the object.
	@returns Ogre::Matrix4 The rotation matrix.
	*/
	Ogre::Matrix4 RotationMatrixXYZW(Ogre::Vector3&  orientation);

	/**
	Create a 4x4 rotation matrix for x.
	@param float The angle.
	@returns Ogre::Matrix4 The rotation matrix.
	*/
	Ogre::Matrix4 xRotationMatrix4(float angle);

	/**
	Create a 4x4 rotation matrix for y.
	@param float The angle.
	@returns Ogre::Matrix4 The rotation matrix.
	*/
	Ogre::Matrix4 yRotationMatrix4(float angle);

	/**
	Create a 4x4 rotation matrix for z.
	@param float The angle.
	@returns Ogre::Matrix4 The rotation matrix.
	*/
	Ogre::Matrix4 zRotationMatrix4(float angle);

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
	Converts the angle to a radian.
	@param float The angle to convert.
	@returns float The converted radian.
	*/
	float convertAngleToRadian(float angle);	

	/**
	Converts the angle from a radian.
	@param float The angle to convert.
	@returns float The converted angle.
	*/
	float convertRadianToDegree(float angle);

	/**
	Makes sure the angle is between 0 and 360.
	@param Ogre::Real The angle.
	@param Ogre::Real The value to add to the angle.
	@returns Ogre::Real The resultant angle between 0 and 360.
	*/
	Ogre::Real angleCheck(Ogre::Real angle, Ogre::Real angleChange);

	/**
	Work out the angle using TOA from SOHCAHTOA*.
	@param Ogre::Real The opposite length.
	@param Ogre::Real The adjacent length.
	@returns float The resultant angle.
	*/
	Ogre::Real getAngleTOA(Ogre::Real opp, Ogre::Real adj);
}