#ifndef ALL_H_INCLUDED
#define ALL_H_INCLUDED

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Screen FPS
const int SCREEN_FPS = 30;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const uint CUBE_COUNT = 3;
const uint COLOR_COUNT = 6;

const float COLOR_MATR[ COLOR_COUNT ][ 3 ] =
{
	{  52 / 255.0, 152 / 255.0, 219 / 255.0 }, // Peter river
	{  46 / 255.0, 204 / 255.0, 113 / 255.0 }, // Emerald
	{ 155 / 255.0,  89 / 255.0, 182 / 255.0 }, // Amethyst
	{ 241 / 255.0, 196 / 255.0,  15 / 255.0 }, // Sum flower
	{ 231 / 255.0,  76 / 255.0,  60 / 255.0 }, // Alizarin
	{ 236 / 255.0, 240 / 255.0, 241 / 255.0 }  // Clouds
};

const float COLOR_DARKGRAY[ 3 ] = 	{  52 / 255.0,  73 / 255.0,  94 / 255.0 }; // Wet asphalt
const float COLOR_LIGHTGRAY[ 3 ] = 	{ 149 / 255.0, 165 / 255.0, 166 / 255.0 }; // Concrete

#endif // ALL_H_INCLUDED