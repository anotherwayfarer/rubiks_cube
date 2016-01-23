#include "all.h"

#include "gamestate.h"
#include "playstate.h"
#include "gameengine.h"
#include "myquaternion.h"
#include "rcubeparams.h"

CPlayState CPlayState::m_PlayState;

void CPlayState::Init()
{
	glClearDepth( 1.0 );
	glDepthFunc( GL_LESS );
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

//	gluPerspective( 40.0f, ( float ) SCREEN_WIDTH / ( float ) SCREEN_HEIGHT, 0.1f, 20.0f );

//	const float margin = 0.1;
//	glFrustum( -margin * wdh * 1.2, margin* wdh, -margin, margin* 1.2, 0.1, 20.0 );

	const float wdh = ( float ) SCREEN_WIDTH / ( float ) SCREEN_HEIGHT;
	const float margin = 4;
	GLfloat cavalierPMatrix[ 16 ] = {
		1 , 0 , 0 , 0,
		0 , 1 , 0 , 0,
		0.3345, -0.3345, 1 , 0,
		0 , 0 , 0 , 1
	};

	glOrtho( -margin * wdh, margin * wdh, -margin, margin, 0.0, 20.0 );
	glMultMatrixf( cavalierPMatrix );

	glMatrixMode( GL_MODELVIEW );

	m_RCube = new RCubeObject;
}

void CPlayState::Cleanup()
{
	delete m_RCube;

	MoveParams::cleanup();
	Colors::cleanup();
	AxisParams::cleanup();
}

void CPlayState::Pause()
{

}

void CPlayState::Resume()
{

}

void CPlayState::HandleEvents( CGameEngine* game )
{
	static bool lastEvent = false;
	SDL_Event event;

	const Uint32 start = SDL_GetTicks();
	bool allEventsRunOut = false;

	while ( SDL_PollEvent( &event ) && !allEventsRunOut && ( SDL_GetTicks() - start ) < 15 )
	{
		switch( event.type )
		{
		case SDL_QUIT:
			game->Quit();
			break;

		case SDL_KEYDOWN:
			lastEvent = true;
			switch( event.key.keysym.sym )
			{
			case SDLK_ESCAPE:
				game->Quit();
				break;

			case SDLK_UP:
			case SDLK_w:
				m_gkStates[ GK_LOOKUP ].setDown();
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_gkStates[ GK_LOOKDOWN ].setDown();
				break;

			case SDLK_LEFT:
			case SDLK_a:
				m_gkStates[ GK_LOOKLEFT ].setDown();
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_gkStates[ GK_LOOKRIGHT ].setDown();
				break;

			case SDLK_PAGEDOWN:
			case SDLK_e:
				m_gkStates[ GK_ROTATECOUNTERCLOCKWISE ].setDown();
				break;

			case SDLK_DELETE:
			case SDLK_q:
				m_gkStates[ GK_ROTATECLOCKWISE ].setDown();
				break;

			case SDLK_i:
				m_gkStates[ GK_MOVEFRONT ].setDown();
				break;

			case SDLK_u:
				m_gkStates[ GK_MOVEFRONTINV ].setDown();
				break;

			case SDLK_p:
				m_gkStates[ GK_MOVEBACK ].setDown();
				break;

			case SDLK_o:
				m_gkStates[ GK_MOVEBACKINV ].setDown();
				break;

			case SDLK_k:
				m_gkStates[ GK_MOVELEFT ].setDown();
				break;

			case SDLK_j:
				m_gkStates[ GK_MOVELEFTINV ].setDown();
				break;

			case SDLK_SEMICOLON:
				m_gkStates[ GK_MOVERIGHT ].setDown();
				break;

			case SDLK_l:
				m_gkStates[ GK_MOVERIGHTINV ].setDown();
				break;

			case SDLK_m:
				m_gkStates[ GK_MOVEUP ].setDown();
				break;

			case SDLK_n:
				m_gkStates[ GK_MOVEUPINV ].setDown();
				break;

			case SDLK_PERIOD:
				m_gkStates[ GK_MOVEDOWN ].setDown();
				break;

			case SDLK_COMMA:
				m_gkStates[ GK_MOVEDOWNINV ].setDown();
				break;

			case SDLK_SPACE:
				m_gkStates[ GK_INCCOLOR ].setDown();
				break;
			}
			break;
		default:
			if ( lastEvent )
			{
				for ( int i = 0; i < GK_COUNT; ++i )
					m_gkStates[ i ].releasePress();

				lastEvent = false;
				allEventsRunOut = true;
			}

			break;
		}
	}
}

void CPlayState::Update( CGameEngine * game )
{
	if ( !m_RCube->isRotating() )
	{
        if ( m_gkStates[ GK_LOOKDOWN ].isNewDown() )
		{
			m_RCube->setRotates( 1, 0, 0, false );
			m_gkStates[ GK_LOOKDOWN ].releaseNewDown();
		}
		else if ( m_gkStates[ GK_LOOKUP ].isNewDown() )
		{
			m_RCube->setRotates( 1, 0, 0, true );
			m_gkStates[ GK_LOOKUP ].releaseNewDown();
		}
		else if ( m_gkStates[ GK_LOOKRIGHT ].isNewDown() )
		{
			m_RCube->setRotates( 0, 1, 0, false );
			m_gkStates[ GK_LOOKRIGHT ].releaseNewDown();
		}
		else if ( m_gkStates[ GK_LOOKLEFT ].isNewDown() )
		{
			m_RCube->setRotates( 0, 1, 0, true );
			m_gkStates[ GK_LOOKLEFT ].releaseNewDown();
		}
		else if ( m_gkStates[ GK_ROTATECOUNTERCLOCKWISE ].isNewDown() )
		{
			m_RCube->setRotates( 0, 0, 1, false );
			m_gkStates[ GK_ROTATECOUNTERCLOCKWISE ].releaseNewDown();
		}
		else if ( m_gkStates[ GK_ROTATECLOCKWISE ].isNewDown() )
		{
			m_RCube->setRotates( 0, 0, 1, true );
			m_gkStates[ GK_ROTATECLOCKWISE ].releaseNewDown();
		}
	}

	if ( !m_RCube->isMoving() && !m_RCube->isRotating() )
	{
		for ( int i = 0; i < GK_MOVELAST - GK_MOVEFIRST + 1; i++ )
		{
			if ( m_gkStates[ GK_MOVEFRONT + i ].isNewDown() )
			{
				m_RCube->setMove( ( RCMoveType ) ( MT_FRONT + i ) );
				m_gkStates[ GK_MOVEFRONT + i ].releaseNewDown();
				break;
			}
		}
	}

	if ( m_gkStates[ GK_INCCOLOR ].isNewDown() )
	{
		RC::Colors::incScheme();
		m_gkStates[ GK_INCCOLOR ].releaseNewDown();
		m_needRedraw = true;
	}
}

void CPlayState::Draw( CGameEngine * game )
{
	static int drCount = 0;

	if ( m_needRedraw || m_RCube->isRotating() || m_RCube->isMoving() )
	{
		Uint32 start = SDL_GetTicks();

		glClearColor( Colors::colR( RC_BG ), Colors::colG( RC_BG ), Colors::colB( RC_BG ), 0.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glLoadIdentity();
//		glTranslatef( 0.0f, 0.0f, -7.0 );
		glTranslatef( 0.0f, 0.0, -2.0 );

//		glRotatef( 15, 1.0f, 0.0f, 0.0f );

		m_RCube->rotateObject();
		m_RCube->drawObject();

		glFlush();

		if ( SDL_GetTicks() - start < SCREEN_TICK_PER_FRAME )
			SDL_Delay( SCREEN_TICK_PER_FRAME - ( SDL_GetTicks() - start ) );

		drCount++;
		if ( drCount > 1 ) m_needRedraw = false;
#ifdef MY_DEBUG
//		if ( drCount % 5 == 0 )
//			std::cout << "DrawCount: " << drCount << std::endl;
#endif // MY_DEBUG
	}
}

