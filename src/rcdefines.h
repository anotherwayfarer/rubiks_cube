#ifndef RCDEFINES_H_INCLUDED
#define RCDEFINES_H_INCLUDED

namespace RC
{
	const int CUBIE_COUNT = 3;
	const float CUBE_EDGE = 1.0;

	enum RCAxis
	{
		AX_FRONT = 0, AX_UP, AX_BACK, AX_DOWN, AX_LEFT, AX_RIGHT,
		AX_COUNT, AX_NONE,
		AX_FIRST = AX_FRONT
	};

	enum RCMoveType
	{
		MT_FRONT, MT_FRONTINV,
		MT_BACK, MT_BACKINV,
		MT_LEFT, MT_LEFTINV,
		MT_RIGHT, MT_RIGHTINV,
		MT_UP, MT_UPINV,
		MT_DOWN, MT_DOWNINV,

		MT_COUNT,
		MT_NONE,
		MT_FIRST = MT_FRONT
	};

	enum GameKeys
	{
		GK_LOOKUP, GK_LOOKDOWN, GK_LOOKLEFT, GK_LOOKRIGHT, GK_ROTATECW, GK_ROTATEACW,

		GK_MOVEFRONT, GK_MOVEFRONTINV, GK_MOVEBACK, GK_MOVEBACKINV,
		GK_MOVELEFT, GK_MOVELEFTINV, GK_MOVERIGHT, GK_MOVERIGHTINV,
		GK_MOVEUP, GK_MOVEUPINV, GK_MOVEDOWN, GK_MOVEDOWNINV,
		GK_MOVEFIRST = GK_MOVEFRONT,
		GK_MOVELAST = GK_MOVEDOWNINV,

		GK_MOVEMOUSE,
		GK_ROTATEMOUSE,

		GK_CHANGECOLOR,
		GK_CHANGEPROJ,

		GK_CUBERESET,

		GK_COUNT,
		GK_FIRST = GK_LOOKUP
	};
}

#endif // RCDEFINES_H_INCLUDED
