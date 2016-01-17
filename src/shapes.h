#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

enum RCMoveType
{
	MT_NONE,
	MT_FRONT, MT_FRONTINV,  // INV = inverse, counter-clockwise move
	MT_BACK, MT_BACKINV,
	MT_LEFT, MT_LEFTINV,
	MT_RIGHT, MT_RIGHTINV,
	MT_UP, MT_UPINV,
	MT_DOWN, MT_DOWNINV,

	RT_COUNT
};

class Point3D
{
public:
	Point3D() { };
	Point3D( const GLfloat x, const GLfloat y, const GLfloat z )
		: m_x( x ), m_y( y ), m_z( z ) { };

	GLfloat x() const { return m_x; };
	GLfloat y() const { return m_y; };
	GLfloat z() const { return m_z; };

private:
	GLfloat m_x = { 0 };
	GLfloat m_y = { 0 };
	GLfloat m_z = { 0 };
};

class CubePiece
{
public:
	CubePiece() { };
	void rotatePiece( const RCMoveType rt )
	{
		unsigned int colTemp;

		if ( rt == MT_FRONT || rt == MT_BACK )
		{
			colTemp = colLeft;
			colLeft = colDown;
			colDown = colRight;
			colRight = colUp;
			colUp = colTemp;
		}
		else if ( rt == MT_FRONTINV || rt == MT_BACKINV )
		{
			colTemp = colLeft;
			colLeft = colUp;
			colUp = colRight;
			colRight = colDown;
			colDown = colTemp;
		}

	}

	unsigned int colUp = -1;
	unsigned int colDown = -1;
	unsigned int colLeft = -1;
	unsigned int colRight = -1;
	unsigned int colFront = -1;
	unsigned int colBack = -1;
};

#endif // SHAPES_H_INCLUDED
