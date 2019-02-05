// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SBDL.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;
void porkonred();
void porkonb();
int Score = 0,Bscore=0;
int highscore = 0;

struct Cor {
	int x, y;
};
struct mane {
	int x;
	int y;
	bool shape;
	bool khord=false;
	bool show = true;
} blue[3],red[3];
void changeB(mane &m)
{
	int x = rand() % 2;
	if (x == 0)
		m.x = 20;
	else
		m.x = 120;
	m.y = -220;
	m.shape = rand() % 2;
	m.khord = false;
	m.show = true;
}
void changeR(mane &m)
{
	int x = rand() % 2;
	if (x == 0)
		m.x = 220;
	else
		m.x = 320;
	m.y = -220;
	m.shape = rand() % 2;
	m.khord = false;
	m.show = true;
}
bool game = false;
bool menu = true;



int main() {
	srand(time(NULL));
	bool musicOn = true;
	bool bcmr = false;
	bool bcml = false;
	bool rcmr = false;
	bool rcml = false;
	porkonred();
	porkonb();
	int i = 0, shomarande = 0, j = 0;
	struct Redcar {
		int X;
		int Y;
		int V;
	};
	struct Bluecar {
		int X;
		int Y;
		int V;
	};
	Bluecar bluecar;
	bluecar.X = 20;
	bluecar.Y = 580;
	bluecar.V = 5;
	Redcar redcar;
	redcar.X = 320;
	redcar.Y = 580;
	redcar.V = 5;
	const int windowWidth = 400;
	const int windowHeight = 712;
	SBDL::InitEngine("2cars", windowWidth, windowHeight);
	Texture background = SBDL::loadTexture("assets/background.png");
	SBDL::showTexture(background, 0, 0);
	Music* musicBack;
	Sound* musicBakht;
	Sound* musicScore;
	musicBakht = SBDL::loadSound("assets/Sounds/die2.wav");
	musicScore = SBDL::loadSound("assets/Sounds/score.wav");
	//musicBack = SBDL::loadMusic("assets/Sounds/music.wav");
	Texture Redcar = SBDL::loadTexture("assets/cars/RedCar.png");
	Texture Bluecar = SBDL::loadTexture("assets/cars/BlueCar.png");
	Texture bc = SBDL::loadTexture("assets/Obstacle/1.png");
	Texture br = SBDL::loadTexture("assets/Obstacle/2.png");
	Texture rc = SBDL::loadTexture("assets/Obstacle/3.png");
	Texture rr = SBDL::loadTexture("assets/Obstacle/4.png");
	Texture playbutton = SBDL::loadTexture("assets/Button/Play.png");
	Texture gameover = SBDL::loadTexture("assets/GameOverBackground.png");
	Font* adad;
	adad = SBDL::loadFont("assets/Font/gobold.ttf",20);
	Texture score = SBDL::createFontTexture(adad, to_string(Score),255,255,255);
	SBDL::updateRenderScreen();
	const int FPS = 25;
	const int delay = 1000 / FPS;
	int loopStartTime1 = SBDL::getTime();

	while (SBDL::isRunning()) {
		ifstream toscore("hihgscore.txt");
		toscore >> highscore;
		if (Score > highscore || highscore == 0)
		{
			highscore = Score;
			ofstream hscore("hihgscore.txt");
			hscore << highscore;
			hscore.close();
		}
		toscore.close();
		if (!game&&menu)
		{
			SBDL::showTexture(background, 0 , 0 );
			SBDL::showTexture(playbutton, 130 , 250);
			SBDL::updateRenderScreen();
			SDL_Rect play = { 130,250,150,150 };
			SBDL::updateEvents();
			if (SBDL::mouseInRect(play) && SBDL::Mouse.clicked())
			{
				porkonb();
				porkonred();
				menu = false;
				game = true;
			}
		}
		if (game&&!menu) {
			shomarande++;
			int loopStartTime = SBDL::getTime();
			SBDL::clearRenderScreen();
			SBDL::updateEvents();
			//music
			if (musicOn) {
				//SBDL::playMusic(musicBack, -1);
				musicOn = false;
			}
			//mane ha
			if (shomarande > 60)
			{
				for (int i = 0; i < 3; i++)
				{
					if (red[i].y > 712)
					{
						if (red[i].khord == 0 && red[i].shape == 1)
						{
							Bscore = Score;
							Score = 0;
							game = false;
							SBDL::playSound(musicBakht, 1);
						}
						else
							changeR(red[i]);
					}
					else
						red[i].y += 10;
				}
				for (int i = 0; i < 3; i++)
				{
					if (blue[i].y > 712)
					{
						if (blue[i].khord == 0 && blue[i].shape == 1)
						{
							Bscore = Score;
							Score = 0;
							game = false;
							SBDL::playSound(musicBakht, 1);
						}
						else
							changeB(blue[i]);
					}
					else
						blue[i].y += 10;
				}
			}
			//check kardan barkhord
			for (int i = 0; i < 3; i++)
			{
				if (red[i].y > 520)
					if (red[i].x == redcar.X)
					{
						if (red[i].shape == 1)
						{
							if (red[i].khord==false)
							Score++;
							//SBDL::playSound(musicScore, 1);
							red[i].show = false;
							red[i].khord = true;
						}
						if (red[i].shape == 0)
						{
							Bscore = Score;
							Score = 0;
							game = false;
							SBDL::playSound(musicBakht, 1);
						}
					}
			}
			for (int i = 0; i < 3; i++)
			{

				if (blue[i].y > 520)
					if (blue[i].x == bluecar.X)
					{
						if (blue[i].shape == 1)
						{
							if (blue[i].khord == false)
							Score++;
							//SBDL::playSound(musicScore, 1);
							blue[i].show = false;
							blue[i].khord = true;
						}
						if (blue[i].shape == 0)
						{
							Bscore = Score;
							game = false;
							Score = 0;
							SBDL::playSound(musicBakht, 1);
						}
					}
			}
			//in bara harekat redcare!
			if (SBDL::keyPressed(SDL_SCANCODE_RIGHT))
			{
				if (redcar.X == 320)
				{
					rcml = true;
				}
				else if (redcar.X == 220)
				{
					rcmr = true;
				}
			}
			//in bara harekate bluecare!
			if (SBDL::keyPressed(SDL_SCANCODE_LEFT))
			{
				if (bluecar.X == 20)
				{
					bcmr = true;
				}
				else if (bluecar.X == 120)
				{
					bcml = true;
				}
			}
			//bara taghire jahat redcar
			if (redcar.X <= 220 && rcml)
			{
				rcml = false;
			}
			if (redcar.X >= 320 && rcmr)
			{
				rcmr = false;
			}
			if (rcml)
			{
				redcar.X -= 20;
			}
			if (rcmr)
			{
				redcar.X += 20;
			}
			//in bara taghire jahate bluecar
			if (bluecar.X <= 20 && bcml)
			{
				bcml = false;
			}
			if (bluecar.X >= 120 && bcmr)
			{
				bcmr = false;
			}
			if (bcml)
			{
				bluecar.X -= 20;
			}
			if (bcmr)
			{
				bluecar.X += 20;
			}
			Texture score = SBDL::createFontTexture(adad, to_string(Score), 255, 255, 255);
			SBDL::showTexture(background, 0, 0);
			SBDL::showTexture(Redcar, redcar.X, redcar.Y);
			SBDL::showTexture(Bluecar, bluecar.X, bluecar.Y);
			SBDL::showTexture(score, 370, 0);
			for (int i = 0; i < 3; i++)
			{
				if (red[i].shape == true && red[i].show)
				{
					SBDL::showTexture(rc, red[i].x, red[i].y);
				}
				else if (red[i].shape == false)
				
				{
					SBDL::showTexture(rr, red[i].x, red[i].y);
				}
			}
			for (int i = 0; i < 3; i++)
			{
				if (blue[i].shape == true && blue[i].show)
				{
					SBDL::showTexture(bc, blue[i].x, blue[i].y);
				}
				else if (blue[i].shape == false)
				{
					SBDL::showTexture(br, blue[i].x, blue[i].y);
				}
			}
			SBDL::updateRenderScreen();
			//in time ro dorost mikone
			int elapsedTime = SBDL::getTime() - loopStartTime;
			if (elapsedTime < delay)
				SBDL::delay(delay - elapsedTime);
		}
	
	if(!menu&&!game)
	{
		//SBDL::clearRenderScreen();
		SBDL::updateEvents();
		SBDL::updateRenderScreen();
		SBDL::showTexture(gameover, 0, 0);
		Texture score = SBDL::createFontTexture(adad, to_string(Bscore), 255, 255, 255);
		Texture Highscore = SBDL::createFontTexture(adad, to_string(highscore), 255, 255, 255);
		SBDL::showTexture(score, 210, 190);
		SBDL::showTexture(Highscore, 210, 240);
		SDL_Rect playagain = { 150,350,120,130 };
		SDL_Rect losehome = { 60,60,125,510 };
		if (SBDL::mouseInRect(playagain) && SBDL::Mouse.clicked())
		{
			porkonb();
			porkonred();
			game = true;
		}
		if (SBDL::mouseInRect(losehome) && SBDL::Mouse.clicked())
		{
			game = false;
			menu = true;
		}

	}
}
    return 0;
}
void porkonred()
{
	for (int i = 0; i < 3; i++)
	{
		int x = rand() % 2;
		if (x == 0)
			red[i].x = 220;
		else
			red[i].x = 320;
		red[i].y = -70-i*350;
		red[i].shape = rand() % 2;
		red[i].show = true;
	}
}
void porkonb()
{
	for (int i = 0; i < 3; i++)
	{
		int x = rand() % 2;
		if (x == 0)
			blue[i].x = 20;
		else
			blue[i].x = 120;
		blue[i].y = -170-i*350;
		blue[i].shape = rand()%2;
		blue[i].show = true;
	}
}
