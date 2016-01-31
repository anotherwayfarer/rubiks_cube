#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//#include <GL/gl.h>
#include "shapes.h"
#include "rcubemodel.h"
#include "myquaternion.h"

class GameObject
{
public:
	virtual ~GameObject();

	virtual void drawObject() = 0;
	void rotateObject();
	void setRotates( const int newDirX, const int newDirY, const int newDirZ, const bool isPos );
//	bool isRotating() const { return ( m_rotateVec.length() > 0 ); };

protected:
//	MyQuaternion m_rotateQuat;

	GameObject();	// Hide public constructor
	bool isAxisVisible( const RC::RCAxis ax ) const;

	template < class T >
	GLuint loadGLArrayBuffer( T * pArr, const int arrSize ) const
	{
		GLuint bId;
		glGenBuffers( 1, &bId );
		glBindBuffer( GL_ARRAY_BUFFER, bId );
		glBufferData( GL_ARRAY_BUFFER, arrSize, pArr, GL_STATIC_DRAW );

		return bId;
	}

	GLuint loadGLTexture2D( const char * filename ) const;

private:
/*	Point3D m_pos;
	float m_rotateAngle = { 0 };
	bool m_isPositive = { true };
	Vector3D m_rotateVec;
	RC::RCAxis m_axesPos[ RC::AX_COUNT ];
*/
	void updateAxesPos();
};

#endif // GAMEOBJECT_H
