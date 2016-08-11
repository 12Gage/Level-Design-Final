
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdint.h>
#include <sstream>

using namespace std;

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#include <unistd.h>

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/Level-Design-Final/image/";
#endif

#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <direct.h>
#define getcwd _getcwd

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/Level-Design-Final/image/";

#endif

bool Pfront = true, Pback = false, Pright = false, Pleft = false;

int main(int argc, char* argv[]) {

    SDL_Window *window = NULL;                    // Declare a pointer

    SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

    SDL_Renderer* renderer = NULL;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_CENTERED,           // initial x position
		SDL_WINDOWPOS_CENTERED,           // initial y position
        1024,                               // width, in pixels
        768,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = true;

    SDL_Event e;

    //Player player1(renderer, 0, images_dir.c_str(), 10.0, 250.0);

    SDL_Texture *Player = IMG_LoadTexture(renderer, (images_dir + "Player.png").c_str());
    SDL_Texture *PlayerB = IMG_LoadTexture(renderer, (images_dir + "PlayerB.png").c_str());
    SDL_Texture *PlayerR = IMG_LoadTexture(renderer, (images_dir + "PlayerR.png").c_str());
    SDL_Texture *PlayerL = IMG_LoadTexture(renderer, (images_dir + "PlayerL.png").c_str());

    SDL_Rect PlayerPos;

    PlayerPos.x = 0;

    PlayerPos.y = 250;

    PlayerPos.w = 28;

    PlayerPos.h = 56;

	const int PLAYER_VEL = 3.5;

	int pVelX = 0;
	int pVelY = 0;

    SDL_Texture *bkgd = IMG_LoadTexture(renderer, (images_dir + "Path.png").c_str());

    SDL_Rect bkgdRect;

    bkgdRect.x = 0;

    bkgdRect.y = -700;

    int w, h;
    SDL_QueryTexture(bkgd, NULL, NULL, &w, &h);
    bkgdRect.w = w;
    bkgdRect.h = h;

    SDL_Texture *people = IMG_LoadTexture(renderer, (images_dir + "people.png").c_str());
    SDL_Rect peoplePos;

    peoplePos.x = 0;
    peoplePos.y = -700;

    SDL_QueryTexture(bkgd, NULL, NULL, &w, &h);
    peoplePos.w = w;
    peoplePos.h = h;

    SDL_Texture *bush = IMG_LoadTexture(renderer, (images_dir + "bush.png").c_str());
    SDL_Rect bushPos;

    bushPos.x = 0;
    bushPos.y = -700;
    bushPos.w = w;
    bushPos.h = h;

    SDL_Texture *dog = IMG_LoadTexture(renderer, (images_dir + "dog.png").c_str());
    SDL_Rect dogPos;

    dogPos.x = 0;
    dogPos.y = -700;
    dogPos.w = w;
    dogPos.h = h;

    SDL_Texture *items = IMG_LoadTexture(renderer, (images_dir + "items.png").c_str());
    SDL_Rect itemsPos;

    itemsPos.x = 0;
    itemsPos.y = -700;
    itemsPos.w = w;
    itemsPos.h = h;

    SDL_Texture *healthPickup = IMG_LoadTexture(renderer, (images_dir + "HealthPickup.png").c_str());
    SDL_Rect healthPickupPos;

    healthPickupPos.x = 50;
    healthPickupPos.y = -700;
    healthPickupPos.w = w;
    healthPickupPos.h = h;

    SDL_Texture *ammoPickup = IMG_LoadTexture(renderer, (images_dir + "ammoPickup.png").c_str());
    SDL_Rect ammoPickupPos;

    ammoPickupPos.x = 0;
    ammoPickupPos.y = -700;
    ammoPickupPos.w = w;
    ammoPickupPos.h = h;


    SDL_Rect Wall;

    Wall.x = 0;
    Wall.y = -700;
    Wall.w = 3072;
    Wall.h = 10;

    SDL_Rect Wall2;

	Wall2.x = 0;
	Wall2.y = -700;
	Wall2.w = 10;
	Wall2.h = 2304;

    SDL_Rect Wall3;

	Wall3.x = 0;
	Wall3.y = 1600;
	Wall3.w = 3072;
	Wall3.h = 10;

    SDL_Rect Wall4;

	Wall4.x = 3072;
	Wall4.y = -700;
	Wall4.w = 10;
	Wall4.h = 2304;

    SDL_Texture *bagOpen1 = IMG_LoadTexture(renderer, (images_dir + "bagOpen1.png").c_str());
    SDL_Rect bag1Pos;

    bag1Pos.x = 375;
    bag1Pos.y = 10;
    bag1Pos.w = 90;
    bag1Pos.h = 135;

    SDL_Texture *bagOpen2 = IMG_LoadTexture(renderer, (images_dir + "bagOpen2.png").c_str());
    SDL_Rect bag2Pos;

    bag2Pos.x = 475;
    bag2Pos.y = 10;
    bag2Pos.w = 90;
    bag2Pos.h = 135;

    SDL_Texture *bagOpen3 = IMG_LoadTexture(renderer, (images_dir + "bagOpen3.png").c_str());
    SDL_Rect bag3Pos;

    bag3Pos.x = 575;
    bag3Pos.y = 10;
    bag3Pos.w = 90;
    bag3Pos.h = 135;

    SDL_Texture *Ammo0 = IMG_LoadTexture(renderer, (images_dir + "Ammo0.png").c_str());
    SDL_Rect Ammo0Pos;

    Ammo0Pos.x = 50;
    Ammo0Pos.y = 675;
    Ammo0Pos.w = 45;
    Ammo0Pos.h = 65;

    SDL_Texture *Empty, *Full;

    SDL_Rect EmptyPos, FullPos;

    Empty = IMG_LoadTexture(renderer, (images_dir + "HealthEmpty.png").c_str());
    Full = IMG_LoadTexture(renderer, (images_dir + "HealthFull.png").c_str());

    EmptyPos.x = FullPos.x = 10;
    EmptyPos.y = FullPos.y = 50;
    EmptyPos.w = FullPos.w = 239;
    EmptyPos.h = FullPos.h = 32;

    SDL_Texture *Lake = IMG_LoadTexture(renderer, (images_dir + "Lake.png").c_str());
    SDL_Rect LakePos;
    LakePos.x = 185;
    LakePos.y = -525;
    LakePos.w = 430;
    LakePos.h = 333;

    SDL_Texture *Dock = IMG_LoadTexture(renderer, (images_dir + "Dock.png").c_str());
    SDL_Rect DockPos;
    DockPos.x = 85;
    DockPos.y = -485;
    DockPos.w = 119;
    DockPos.h = 96;

    SDL_Texture *boat = IMG_LoadTexture(renderer, (images_dir + "boat.png").c_str());
    SDL_Rect boatPos;
    boatPos.x = 300;
    boatPos.y = -450;
    boatPos.w = 36;
    boatPos.h = 44;

    SDL_Texture *tree = IMG_LoadTexture(renderer, (images_dir + "turret.png").c_str());
    SDL_Rect treePos;
    treePos.x = 275;
    treePos.y = 525;
    treePos.w = 100;
    treePos.h = 100;

    SDL_Rect tree2Pos;
    tree2Pos.x = 150;
    tree2Pos.y = 700;
    tree2Pos.w = 100;
    tree2Pos.h = 100;

    SDL_Rect tree3Pos;
    tree3Pos.x = 475;
    tree3Pos.y = 750;
    tree3Pos.w = 100;
    tree3Pos.h = 100;

    SDL_Rect tree4Pos;
    tree4Pos.x = 275;
    tree4Pos.y = 975;
    tree4Pos.w = 100;
    tree4Pos.h = 100;

    SDL_Rect tree5Pos;
    tree5Pos.x = 475;
    tree5Pos.y = 975;
    tree5Pos.w = 100;
    tree5Pos.h = 100;

    SDL_Rect tree6Pos;
    tree6Pos.x = 2650;
    tree6Pos.y = 625;
    tree6Pos.w = 100;
    tree6Pos.h = 100;

    SDL_Rect tree7Pos;
    tree7Pos.x = 925;
    tree7Pos.y = 450;
    tree7Pos.w = 100;
    tree7Pos.h = 100;

    SDL_Rect tree8Pos;
    tree8Pos.x = 1075;
    tree8Pos.y = 450;
    tree8Pos.w = 100;
    tree8Pos.h = 100;

    SDL_Rect tree9Pos;
    tree9Pos.x = 1375;
    tree9Pos.y = 450;
    tree9Pos.w = 100;
    tree9Pos.h = 100;

    SDL_Rect tree10Pos;
    tree10Pos.x = 1525;
    tree10Pos.y = 450;
    tree10Pos.w = 100;
    tree10Pos.h = 100;

    SDL_Rect tree11Pos;
    tree11Pos.x = 925;
    tree11Pos.y = 0;
    tree11Pos.w = 100;
    tree11Pos.h = 100;

    SDL_Rect tree12Pos;
    tree12Pos.x = 1075;
    tree12Pos.y = 0;
    tree12Pos.w = 100;
    tree12Pos.h = 100;

    SDL_Rect tree13Pos;
    tree13Pos.x = 1375;
    tree13Pos.y = 0;
    tree13Pos.w = 100;
    tree13Pos.h = 100;

    SDL_Rect tree14Pos;
    tree14Pos.x = 1525;
    tree14Pos.y = 0;
    tree14Pos.w = 100;
    tree14Pos.h = 100;

    SDL_Rect tree15Pos;
    tree15Pos.x = 2500;
    tree15Pos.y = 800;
    tree15Pos.w = 100;
    tree15Pos.h = 100;

    SDL_Rect tree16Pos;
    tree16Pos.x = 2765;
    tree16Pos.y = 850;
    tree16Pos.w = 100;
    tree16Pos.h = 100;

    SDL_Texture *Tree = IMG_LoadTexture(renderer, (images_dir + "Tree.png").c_str());
    SDL_Rect TreePos;
    TreePos.x = 250;
    TreePos.y = 650;
    TreePos.w = 68;
    TreePos.h = 60;

    SDL_Rect TreePos2;
    TreePos2.x = 400;
    TreePos2.y = 650;
    TreePos2.w = 68;
    TreePos2.h = 60;

    SDL_Rect TreePos3;
    TreePos3.x = 525;
    TreePos3.y = 625;
    TreePos3.w = 68;
    TreePos3.h = 60;

    SDL_Rect TreePos4;
    TreePos4.x = 525;
    TreePos4.y = 725;
    TreePos4.w = 68;
    TreePos4.h = 60;

    SDL_Rect TreePos5;
    TreePos5.x = 575;
    TreePos5.y = 800;
    TreePos5.w = 68;
    TreePos5.h = 60;

    SDL_Rect TreePos6;
    TreePos6.x = 550;
    TreePos6.y = 925;
    TreePos6.w = 68;
    TreePos6.h = 60;

    SDL_Rect TreePos7;
    TreePos7.x = 465;
    TreePos7.y = 875;
    TreePos7.w = 68;
    TreePos7.h = 60;

    SDL_Rect TreePos8;
    TreePos8.x = 400;
    TreePos8.y = 785;
    TreePos8.w = 68;
    TreePos8.h = 60;

    SDL_Rect TreePos9;
    TreePos9.x = 300;
    TreePos9.y = 725;
    TreePos9.w = 68;
    TreePos9.h = 60;

    SDL_Rect TreePos10;
    TreePos10.x = 235;
    TreePos10.y = 800;
    TreePos10.w = 68;
    TreePos10.h = 60;

    SDL_Rect TreePos11;
    TreePos11.x = 235;
    TreePos11.y = 925;
    TreePos11.w = 68;
    TreePos11.h = 60;

    SDL_Rect TreePos12;
    TreePos12.x = 335;
    TreePos12.y = 875;
    TreePos12.w = 68;
    TreePos12.h = 60;

    SDL_Rect TreePos13;
    TreePos13.x = 400;
    TreePos13.y = 975;
    TreePos13.w = 68;
    TreePos13.h = 60;

    SDL_Rect TreePos14;
    TreePos14.x = 2750;
    TreePos14.y = 850;
    TreePos14.w = 68;
    TreePos14.h = 60;

    SDL_Rect TreePos15;
    TreePos15.x = 2600;
    TreePos15.y = 835;
    TreePos15.w = 68;
    TreePos15.h = 60;

    SDL_Rect TreePos16;
    TreePos16.x = 2585;
    TreePos16.y = 755;
    TreePos16.w = 68;
    TreePos16.h = 60;

    SDL_Rect TreePos17;
    TreePos17.x = 2675;
    TreePos17.y = 765;
    TreePos17.w = 68;
    TreePos17.h = 60;

    SDL_Rect TreePos18;
    TreePos18.x = 2780;
    TreePos18.y = 750;
    TreePos18.w = 68;
    TreePos18.h = 60;

    SDL_Rect TreePos19;
    TreePos19.x = 2400;
    TreePos19.y = -250;
    TreePos19.w = 68;
    TreePos19.h = 60;

    SDL_Rect TreePos20;
    TreePos20.x = 1435;
    TreePos20.y = -655;
    TreePos20.w = 68;
    TreePos20.h = 60;

    SDL_Rect TreePos21;
    TreePos21.x = 1000;
    TreePos21.y = -660;
    TreePos21.w = 68;
    TreePos21.h = 60;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );

	while(quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = false;
			}
			else
			{
				if(e.type == SDL_KEYDOWN && e.key.repeat == 0){

					switch(e.key.keysym.sym){

					case SDLK_w:
					pVelY -= PLAYER_VEL;
					Pfront = false;
					Pback = true;
					Pright = false;
					Pleft = false;
					break;
					case SDLK_s:
					pVelY += PLAYER_VEL;
					Pfront = true;
					Pback = false;
					Pright = false;
					Pleft = false;
					break;
					case SDLK_a:
					pVelX -= PLAYER_VEL;
					Pfront = false;
					Pback = false;
					Pright = false;
					Pleft = true;
					break;
					case SDLK_d:
					pVelX += PLAYER_VEL;
					Pfront = false;
					Pback = false;
					Pright = true;
					Pleft = false;
					break;
					}
				}

				else if(e.type == SDL_KEYUP && e.key.repeat == 0)
				{
					switch(e.key.keysym.sym){

					case SDLK_w:
					pVelY += PLAYER_VEL;
					break;
					case SDLK_s:
					pVelY -= PLAYER_VEL;
					break;
					case SDLK_a:
					pVelX += PLAYER_VEL;
					break;
					case SDLK_d:
					pVelX -= PLAYER_VEL;
					break;

					}
				}
			}
		}

		PlayerPos.x += pVelX;


		if(PlayerPos.x > (1024 - (PlayerPos.w * 2))){

			PlayerPos.x = (1024 - (PlayerPos.w * 2));

			bkgdRect.x -= pVelX;

			Wall.x -= pVelX;
			Wall2.x -= pVelX;
			Wall3.x -= pVelX;
			Wall4.x -= pVelX;

			LakePos.x -=pVelX;

			DockPos.x -=pVelX;

			treePos.x -=pVelX;
			tree2Pos.x -=pVelX;
			tree3Pos.x -=pVelX;
			tree4Pos.x -=pVelX;
			tree5Pos.x -=pVelX;
			tree6Pos.x -=pVelX;
			tree7Pos.x -=pVelX;
			tree8Pos.x -=pVelX;
			tree9Pos.x -=pVelX;
			tree10Pos.x -=pVelX;
			tree11Pos.x -=pVelX;
			tree12Pos.x -=pVelX;
			tree13Pos.x -=pVelX;
			tree14Pos.x -=pVelX;
			tree15Pos.x -=pVelX;
			tree16Pos.x -=pVelX;

			peoplePos.x -=pVelX;

			boatPos.x -=pVelX;

			bushPos.x -=pVelX;

			dogPos.x -=pVelX;

			TreePos.x -=pVelX;
			TreePos2.x -=pVelX;
			TreePos3.x -=pVelX;
			TreePos4.x -=pVelX;
			TreePos5.x -=pVelX;
			TreePos6.x -=pVelX;
			TreePos7.x -=pVelX;
			TreePos8.x -=pVelX;
			TreePos9.x -=pVelX;
			TreePos10.x -=pVelX;
			TreePos11.x -=pVelX;
			TreePos12.x -=pVelX;
			TreePos13.x -=pVelX;
			TreePos14.x -=pVelX;
			TreePos15.x -=pVelX;
			TreePos16.x -=pVelX;
			TreePos17.x -=pVelX;
			TreePos18.x -=pVelX;
			TreePos19.x -=pVelX;
			TreePos20.x -=pVelX;
			TreePos21.x -=pVelX;

			itemsPos.x -=pVelX;

			healthPickupPos.x -=pVelX;

			ammoPickupPos.x -=pVelX;
		}

		if(PlayerPos.x < (0 + (PlayerPos.w * 2))){

			PlayerPos.x = (0 + (PlayerPos.w * 2));

			bkgdRect.x -= pVelX;

			Wall.x -= pVelX;
			Wall2.x -= pVelX;
			Wall3.x -= pVelX;
			Wall4.x -= pVelX;

			LakePos.x -=pVelX;

			DockPos.x -=pVelX;

			treePos.x -=pVelX;
			tree2Pos.x -=pVelX;
			tree3Pos.x -=pVelX;
			tree4Pos.x -=pVelX;
			tree5Pos.x -=pVelX;
			tree6Pos.x -=pVelX;
			tree7Pos.x -=pVelX;
			tree8Pos.x -=pVelX;
			tree9Pos.x -=pVelX;
			tree10Pos.x -=pVelX;
			tree11Pos.x -=pVelX;
			tree12Pos.x -=pVelX;
			tree13Pos.x -=pVelX;
			tree14Pos.x -=pVelX;
			tree15Pos.x -=pVelX;
			tree16Pos.x -=pVelX;

			peoplePos.x -=pVelX;

			boatPos.x -=pVelX;

			bushPos.x -=pVelX;

			dogPos.x -=pVelX;

			TreePos.x -=pVelX;
			TreePos2.x -=pVelX;
			TreePos3.x -=pVelX;
			TreePos4.x -=pVelX;
			TreePos5.x -=pVelX;
			TreePos6.x -=pVelX;
			TreePos7.x -=pVelX;
			TreePos8.x -=pVelX;
			TreePos9.x -=pVelX;
			TreePos10.x -=pVelX;
			TreePos11.x -=pVelX;
			TreePos12.x -=pVelX;
			TreePos13.x -=pVelX;
			TreePos14.x -=pVelX;
			TreePos15.x -=pVelX;
			TreePos16.x -=pVelX;
			TreePos17.x -=pVelX;
			TreePos18.x -=pVelX;
			TreePos19.x -=pVelX;
			TreePos20.x -=pVelX;
			TreePos21.x -=pVelX;

			itemsPos.x -=pVelX;

			healthPickupPos.x -=pVelX;

			ammoPickupPos.x -=pVelX;
		}

		if( SDL_HasIntersection(&PlayerPos, &Wall) || SDL_HasIntersection(&PlayerPos, &Wall2) ||
				SDL_HasIntersection(&PlayerPos, &Wall3) || SDL_HasIntersection(&PlayerPos, &Wall4) ||
				SDL_HasIntersection(&PlayerPos, &LakePos)){

			PlayerPos.x -= pVelX;
		}


		PlayerPos.y += pVelY;

		if(PlayerPos.y < (0 + (PlayerPos.h * 2))){

			PlayerPos.y = (0 + (PlayerPos.h * 2));

			bkgdRect.y -= pVelY;

			Wall.y -= pVelY;
			Wall2.y -= pVelY;
			Wall3.y -= pVelY;
			Wall4.y -= pVelY;

			LakePos.y -=pVelY;

			DockPos.y -=pVelY;

			treePos.y -=pVelY;
			tree2Pos.y -=pVelY;
			tree3Pos.y -=pVelY;
			tree4Pos.y -=pVelY;
			tree5Pos.y -=pVelY;
			tree6Pos.y -=pVelY;
			tree7Pos.y -=pVelY;
			tree8Pos.y -=pVelY;
			tree9Pos.y -=pVelY;
			tree10Pos.y -=pVelY;
			tree11Pos.y -=pVelY;
			tree12Pos.y -=pVelY;
			tree13Pos.y -=pVelY;
			tree14Pos.y -=pVelY;
			tree15Pos.y -=pVelY;
			tree16Pos.y -=pVelY;

			peoplePos.y -=pVelY;

			boatPos.y -=pVelY;

			bushPos.y -=pVelY;

			dogPos.y -=pVelY;

			TreePos.y -=pVelY;
			TreePos2.y -=pVelY;
			TreePos3.y -=pVelY;
			TreePos4.y -=pVelY;
			TreePos5.y -=pVelY;
			TreePos6.y -=pVelY;
			TreePos7.y -=pVelY;
			TreePos8.y -=pVelY;
			TreePos9.y -=pVelY;
			TreePos10.y -=pVelY;
			TreePos11.y -=pVelY;
			TreePos12.y -=pVelY;
			TreePos13.y -=pVelY;
			TreePos14.y -=pVelY;
			TreePos15.y -=pVelY;
			TreePos16.y -=pVelY;
			TreePos17.y -=pVelY;
			TreePos18.y -=pVelY;
			TreePos19.y -=pVelY;
			TreePos20.y -=pVelY;
			TreePos21.y -=pVelY;

			itemsPos.y -=pVelY;

			healthPickupPos.y -=pVelY;

			ammoPickupPos.y -=pVelY;
		}

		if(PlayerPos.y > (768 - (PlayerPos.h * 2))){

			PlayerPos.y = 768 - (PlayerPos.h * 2);

			bkgdRect.y -= pVelY;

			Wall.y -= pVelY;
			Wall2.y -= pVelY;
			Wall3.y -= pVelY;
			Wall4.y -= pVelY;

			LakePos.y -=pVelY;

			DockPos.y -=pVelY;

			treePos.y -=pVelY;
			tree2Pos.y -=pVelY;
			tree3Pos.y -=pVelY;
			tree4Pos.y -=pVelY;
			tree5Pos.y -=pVelY;
			tree6Pos.y -=pVelY;
			tree7Pos.y -=pVelY;
			tree8Pos.y -=pVelY;
			tree9Pos.y -=pVelY;
			tree10Pos.y -=pVelY;
			tree11Pos.y -=pVelY;
			tree12Pos.y -=pVelY;
			tree13Pos.y -=pVelY;
			tree14Pos.y -=pVelY;
			tree15Pos.y -=pVelY;
			tree16Pos.y -=pVelY;

			peoplePos.y -=pVelY;

			boatPos.y -=pVelY;

			bushPos.y -=pVelY;

			dogPos.y -=pVelY;

			TreePos.y -=pVelY;
			TreePos2.y -=pVelY;
			TreePos3.y -=pVelY;
			TreePos4.y -=pVelY;
			TreePos5.y -=pVelY;
			TreePos6.y -=pVelY;
			TreePos7.y -=pVelY;
			TreePos8.y -=pVelY;
			TreePos9.y -=pVelY;
			TreePos10.y -=pVelY;
			TreePos11.y -=pVelY;
			TreePos12.y -=pVelY;
			TreePos13.y -=pVelY;
			TreePos14.y -=pVelY;
			TreePos15.y -=pVelY;
			TreePos16.y -=pVelY;
			TreePos17.y -=pVelY;
			TreePos18.y -=pVelY;
			TreePos19.y -=pVelY;
			TreePos20.y -=pVelY;
			TreePos21.y -=pVelY;

			itemsPos.y -=pVelY;

			healthPickupPos.y -=pVelY;

			ammoPickupPos.y -=pVelY;
		}

		if( SDL_HasIntersection(&PlayerPos, &Wall) || SDL_HasIntersection(&PlayerPos, &Wall2)  ||
				SDL_HasIntersection(&PlayerPos, &Wall3) || SDL_HasIntersection(&PlayerPos, &Wall4) ||
				SDL_HasIntersection(&PlayerPos, &LakePos)||SDL_HasIntersection(&PlayerPos, &DockPos)) {

			PlayerPos.y -= pVelY;
		}



		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, bkgd, NULL, &bkgdRect);

		SDL_RenderCopy(renderer, Lake, NULL, &LakePos);

		SDL_RenderCopy(renderer, Dock, NULL, &DockPos);

		SDL_RenderCopy(renderer, boat, NULL, &boatPos);

		SDL_RenderCopy(renderer, bush, NULL, &bushPos);

		SDL_RenderCopy(renderer, dog, NULL, &dogPos);

		SDL_RenderCopy(renderer, items, NULL, &itemsPos);

		SDL_RenderCopy(renderer, healthPickup, NULL, &healthPickupPos);

		SDL_RenderCopy(renderer, ammoPickup, NULL, &ammoPickupPos);

		if(Pfront == true)
		{
		SDL_RenderCopy(renderer, Player, NULL, &PlayerPos);
		}
		if(Pback == true)
		{
		SDL_RenderCopy(renderer, PlayerB, NULL, &PlayerPos);
		}
		if(Pright == true)
		{
		SDL_RenderCopy(renderer, PlayerR, NULL, &PlayerPos);
		}
		if(Pleft == true)
		{
		SDL_RenderCopy(renderer, PlayerL, NULL, &PlayerPos);
		}

		SDL_RenderCopy(renderer, people, NULL, &peoplePos);

		SDL_RenderCopy(renderer, Tree, NULL, &TreePos);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos2);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos3);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos4);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos5);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos6);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos7);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos8);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos9);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos10);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos11);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos12);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos13);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos14);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos15);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos16);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos17);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos18);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos19);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos20);
		SDL_RenderCopy(renderer, Tree, NULL, &TreePos21);

		SDL_RenderCopy(renderer, tree, NULL, &treePos);
		SDL_RenderCopy(renderer, tree, NULL, &tree2Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree3Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree4Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree5Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree6Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree7Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree8Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree9Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree10Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree11Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree12Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree13Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree14Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree15Pos);
		SDL_RenderCopy(renderer, tree, NULL, &tree16Pos);

		SDL_RenderCopy(renderer, bagOpen1, NULL, &bag1Pos);

		SDL_RenderCopy(renderer, bagOpen2, NULL, &bag2Pos);

		SDL_RenderCopy(renderer, bagOpen3, NULL, &bag3Pos);

		SDL_RenderCopy(renderer, Ammo0, NULL, &Ammo0Pos);

		SDL_RenderCopy(renderer, Empty, NULL, &EmptyPos);

		SDL_RenderCopy(renderer, Full, NULL, &FullPos);

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}


    // The window is open: could enter program loop here (see SDL_PollEvent())

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
