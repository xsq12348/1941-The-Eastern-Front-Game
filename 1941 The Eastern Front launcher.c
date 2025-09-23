#include"star engine.h"
int gamemode = FALSE, startgame = FALSE, historygame = FALSE, power = FALSE;
void main()
{
	int gameok = TRUE;
	GAME Game;
	InitialisationGame(&Game, L"1941 The Eastern Front launcher", -1, -1, 515, 339, 100, 0, 0, 1);
	GameLoop(&Game, 1);
	FILE* fp = fopen("Game/setting.star", "wb");
	fwrite(&GAMEPOWER, sizeof(int), 1, fp);
	fwrite(&gamemode, sizeof(int), 1, fp);
	fwrite(&gameok, sizeof(int), 1, fp);
	fclose(fp);
	GameOver(&Game, 0);
	if(gamemode)RunProgram(L"1941 The Eastern Front.exe");
}
void GameLogic(GAME* Game)
{
	Sleep(1);
	startgame = ButtonA(Game->Windowhwnd, 0, 21, 73, 179, 23, 0);
	historygame = ButtonA(Game->Windowhwnd, 0, 21, 123, 195, 32, 0);
	power = ButtonA(Game->Windowhwnd, 0, 22, 182, 130, 20, 0);
	if (MOUSEX > 196 && MOUSEX < 216 && MOUSEY>182 && MOUSEY < 202 && KeyState(1))GAMEPOWER = !GAMEPOWER;
	if (startgame == 1) gamemode = 1;
	if (historygame == 1) gamemode = 2;
	if(gamemode) GAMEDEAD = TRUE;
}
void GameDrawing(GAME* Game)
{
	BoxC(0, Game->doublebuffer.hdc, 0, 0, 500, 300, 0xffffff);
	Img(0, Game->doublebuffer.hdc, L"img/1941 The Eastern Front launcher.bmp", 0, 0);
	if (startgame == 2)
	{
		IMGA(Game, L"img/NewGame.bmp", 21, 73, 1, 1, 0xffffff);
		Text(0, Game->doublebuffer.hdc, MOUSEX - 60, MOUSEY - 10, L"开始游戏", 0x00ee00);
	}
	if (historygame == 2)
	{
		IMGA(Game, L"img/HistoryGame.bmp", 21, 123, 1, 1, 0xffffff);
		Text(0, Game->doublebuffer.hdc, MOUSEX - 60, MOUSEY - 10, L"历史游戏", 0x00ee00);
	}
	if (power == 2)Text(0, Game->doublebuffer.hdc, MOUSEX - 80, MOUSEY - 10, L"高性能游戏", 0x00ee00);
	if (GAMEPOWER)
	{
		LINE(Game, 196, 182, 196 + 20, 182 + 20, 0x0000ff);
		LINE(Game, 196 + 20, 182, 196, 182 + 20, 0x0000ff);
	}

}
