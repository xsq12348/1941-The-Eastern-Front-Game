//All notes are in English and Chinese, and the rest of the languages are garbled
/*
* 改编自作者桌游，略有不同
* Adapted from the author's board game, slightly different
作者:xsq1234
邮箱:1993346266@qq.com(常用),c6668883535357a@163.com(不常用)
工程创建日期:2025.7.16~2025.7.29,2025.8.2~8.3
名称:1941 东线(1941 The Eastern Front)
未经授权禁止转载!xsq1234保留部分权利。
您可以修改源代码，拓展等等，但必须保留游戏原作者署名。倘若修改，您的商业化权利将被剥夺.
如若需要二次分发，请在咨询xsq1234后在下方写下您的邮箱
邮箱:
如若需要作为商品或放在软件分发平台发放，必须咨询xsq1234后在下方写下您的邮箱，并且告知可能的盈利
邮箱:
源代码只要分发出去，序列号就不得相同
序列号 00000-00000-00001
版本信息:测试版
Author: xsq1234
Email: 1993346266@qq.com (commonly used), c6668883535357a@163.com (not commonly used)
Project creation date: 2025.7.16~2025.7.29,2025.8.2~8.3
Name: 1941 The Eastern Front
Unauthorized reproduction is prohibited! XSQ1234 All rights reserved.
You can modify the source code, extensions, etc., but you must keep the original author's attribution. If modified, your commercialization rights will be forfeited.
If you need to distribute it again, please write your email address below after consulting xsq1234
Mailbox:
If you need to distribute it as a commodity or on a software distribution platform, you must consult xsq1234 and write down your email address below, and inform you of the possible profit
Mailbox:
As long as the source code is distributed, the serial number must not be the same
Serial number 00000-00000-00001
Version information: beta version

如果您是从GitHub仓库里得到它的，那么以上限制作废，遵循仓库中的许可证条款。
If you obtained it from the GitHub repository, then the above limitations are void, and you should follow the license terms in the repository.

* Mapping V
* Hexagon correlation V
* Map editor V
* Script interpreter V
* Combat frame V
* Unit Movement Frame V
* Phase V
* AI X
* ??? X
*/
#pragma warning(disable:4996)
#define STARTOpenCL 0
#include"star engine.h"
#define RANGE(a,b,c) min(max(a,b),c)
#define switchlogic(alpha) if(alpha && 0);
#define caselogic(beta) else if(beta)
#define ROT2DMATRIX(rad) {{ cos(rad), sin(rad)}, { -sin(rad), cos(rad)}};
#define MAPWIDTH		33
#define MAPHEIGHT		23
#define MAPIMGWIDTH		1500
#define MAPIMGHEIGHT	1220
#define WINDOWWIDTH		1500 
#define WINDOWHEIGHT	857
#define PARENTWINDOWWIDTH 53
#define AXISCOLOR		RGB(150,150,150)
#define USSRCOLOR		0x18179d
#define HEXAGONR		30
#define NOTFOUND		-1

typedef struct
{
	int x;
	int y;
}NEWPOINT;
typedef struct
{
	int unit;		//单位种类
	int people;		//人员
	int Attacker;	//攻击力
	int Defender;	//防御力
	int Mobility;	//移动力
	int sid;		//阵营
	int supply;		//补给状态
	int battleemblem;//战斗标志
}UNIT;
typedef struct MAP
{
	int citysid;			//城市归属
	char ragionname[255];	//城市名称
	int terrain;			//地形
	int AXISReplenish;		//补给
	int USSRReplenish;		//补给
	struct MAP* hexagon[6];	//邻居格子
	UNIT unit[5];			//unit
	int Boundary[6];		//边界属性
	int traintracks[6];		//train
}MAP;

enum
{
	INF = 1,
	TANK,
	MECHINF,
	MOT,
	HQ,
	SEC,
	ROMINF,
	ROMTANK,
	CAV,
	MTND
};

DOUBLEBUFFER mapimg, unitimg;
NEWPOINT hexagonpointA = { 0 };
MAP map[MAPWIDTH * MAPHEIGHT] = { 0 };
int mapx = 0, mapy = 0, arrcombatjudgmenttableout = 0, phase = 1, gameyear = 1941, gamemon = 3, axisvictory = FALSE, ussrvictory = FALSE, unitreinforcementoptions = 1,
ussrmanpower = 21, axismanpower = 9, ussrindustry = 56, axisindustry = 24, rommanpower = 1, romindustry = 1, mapaxiscitynumber = 0, mapussrcitynumber = 0;
unitselect[5] = { 0 },
mousebufferpoint[2] = { 0 },
cityascription[MAPWIDTH * MAPHEIGHT] = { 0 },
gamesupplypoint[MAPWIDTH * MAPHEIGHT] = { 0 };
char arrgameoutname[30] = "Game/oldgame.star",
	 arrgamereadname[30] = "Game/oldgame.star";
const int arrcombatjudgmenttable[7][6] =
{
	{0x1a,0x1a,0x0e, 0x0e, 0xd1, 0xd1},
	{0x1a,0x0e,0x0e, 0xd1, 0xd1, 0xd2},
	{0x0e,0x0e,0xd1, 0xd1, 0xd2, 0xd2},
	{0x0e,0xd1,0xd1, 0xd2, 0xd2, 0x1d2},
	{0xd1,0xd1,0xd2, 0xd2, 0x1d2,0x1d2},
	{0xd1,0xd2,0xd2, 0x1d2,0x1d2,0x2d2},
	{0xd2,0xd2,0x1d2,0x1d2,0x2d2,0x3d2},
};

#if STARTOpenCL
cl_program programA;
cl_kernel kernelfindunit;
const char* hexagonopencl =
{
"#define MAPWIDTH		33"
"#define MAPHEIGHT		23"
"typedef struct"
"{"
"	int unit;"		//单位种类
"	int people;"	//人员
"	int Attacker;"	//攻击力
"	int Defender;"	//防御力
"	int Mobility;"	//移动力
"	int sid;"		//阵营
"	int coor;"		//坐标
"}UNIT;"
"typedef struct"
"{"
"	int citysid;"			//城市归属
"	char ragionname[255];"	//城市名称
"	int terrain;"			//地形
"	int terrainnumber;"		//移动代价
"	int AXISReplenish;"		//补给
"	int USSRReplenish;"		//补给
"	int hexagon[6];"		//邻居格子
"	int unit;"				/*Unittype and Unitnumber if unit > 0 then ussrunitnumber elseif unit < 0 then axisunitnumber*/
"	int Boundary[6];"		//边界属性
"	int traintracks[6];"	//train
"}MAP;"
"__kernel void FindUnit(__global UNIT* unit, __global int* coor, __global int* returncoord)"
"{"
"	int number = get_global_id(0);"
"	if(unit[number].people > 0)"
"		if(unit[number].coor == *coor)"
"		{"
"			*returncoord = *coor;"
"			return;"
"		}"
"		else return;"
"	return;"
"}"
""

"__kernel void HexagonMouse( __global int *R, __global int *mousex, __global int *mousey,__global int *mapx, __global int *mapy, __global int *returnhexagonx, __global int *returnhexagony)"
"{"
"	int alpha = get_global_id(0);"
"	int x2 = *R * 1.73 / 2;"
"	int hexagonx = alpha / MAPWIDTH - *mapx;"
"	int hexagony = alpha % MAPWIDTH - *mapy;"
"	int hexagonmapx = hexagonx * 1.5 * *R + *R;"
"	int hexagonmapy = hexagony * 1.73 * *R + (hexagonx % 2 ? x2 : 0) + x2;"
"	int pointx[6] = { hexagonmapx + *R, hexagonmapx + *R / 2, hexagonmapx - *R / 2, hexagonmapx - *R, hexagonmapx - *R / 2, hexagonmapx + *R / 2};"
"	int pointy[6] = { hexagonmapy, hexagonmapy + 1.73 * *R / 2, hexagonmapy + 1.73 / 2 * *R, hexagonmapy, hexagonmapy - 1.73 * *R / 2, hexagonmapy - 1.73 * *R / 2};"
"	int beta[6];"
"	int beta[6] = "
"	{"
"		(*mousex - pointx[0]) * (pointy[0] - pointy[1]) - (*mousey - pointy[0]) * (pointx[0] - pointx[1]),"
"		(*mousex - pointx[1]) * (pointy[1] - pointy[2]) - (*mousey - pointy[1]) * (pointx[1] - pointx[2]),"
"		(*mousex - pointx[2]) * (pointy[2] - pointy[3]) - (*mousey - pointy[2]) * (pointx[2] - pointx[3]),"
"		(*mousex - pointx[3]) * (pointy[3] - pointy[4]) - (*mousey - pointy[3]) * (pointx[3] - pointx[4]),"
"		(*mousex - pointx[4]) * (pointy[4] - pointy[5]) - (*mousey - pointy[4]) * (pointx[4] - pointx[5]),"
"		(*mousex - pointx[5]) * (pointy[5] - pointy[0]) - (*mousey - pointy[5]) * (pointx[5] - pointx[0]) "
"	};"
"	if (beta[0] > 0 && beta[1] > 0 && beta[2] > 0 && beta[3] > 0 && beta[4] > 0 && beta[5] > 0)"
"	{"
"		*returnhexagonx = hexagonx;"
"		*returnhexagony = hexagony;"
"	}"
"	else return;"
"}"
};

programA = clCreateProgramWithSource(context, 1, (const char**)&hexagonopencl, NULL, NULL);
clBuildProgram(programA, 1, &deviceid, NULL, NULL, NULL);
kernelfindunit = clCreateKernel(program, "FindUnit", NULL);
clReleaseProgram(programA);
#endif

void NewLine(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, int width, COLORREF color)
{
	HDC hDc = hdc;
	HPEN hpen = CreatePen(PS_SOLID, width, color);
	HPEN holdpen = (HPEN)SelectObject(hDc, hpen);
	MoveToEx(hDc, x2, y2, NULL);
	LineTo(hDc, x1, y1);
	SelectObject(hDc, holdpen);
	DeleteObject(hpen);
	ReleaseDC(hwnd, hDc);
}
void NewPrintf(HWND hwnd, HDC hdc, int x, int y, LPCSTR arrtext, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);//设置字体背景透明
	int size = strlen(arrtext);
	SetTextColor(hdc, color);
	TextOut(hdc, x, y, CharToLPCWSTR(arrtext), size);
	ReleaseDC(hwnd, hdc);
}

//----------------------------------------------------------------------------------------------------------------Hexagon----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//画六边形
void HexagonA(HDC hdc, int R, int X, int Y, COLORREF color)
{
	int r = R;
	int x, y, x2 = R * 1.732 / 2;
	x = X * 1.5 * r + r;
	y = Y * 1.732 * R + (x % 2 ? x2 : 0) + x2;
	POINT hexagon[6] = { 0 };
	hexagon[0].x = x + r;
	hexagon[0].y = y;
	hexagon[1].x = x + r / 2;
	hexagon[1].y = y + 1.732 * r / 2 + 1;
	hexagon[2].x = x - r / 2;
	hexagon[2].y = y + 1.732 * r / 2 + 1;
	hexagon[3].x = x - r;
	hexagon[3].y = y;
	hexagon[4].x = x - r / 2;
	hexagon[4].y = y - 1.732 * r / 2;
	hexagon[5].x = x + r / 2;
	hexagon[5].y = y - 1.732 * r / 2;
	HBRUSH hbrush = CreateSolidBrush(color);
	HPEN hnPen = CreatePen(PS_SOLID, 1, 0x3232ac);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hnPen);
	SelectObject(hdc, hbrush);
	Polygon(hdc, hexagon, 6);
	DeleteObject(hbrush);
	DeleteObject(hnPen);
}
void HexagonB(HDC hdc, int R, int r, int X, int Y, COLORREF color)
{
	int x, y, x2 = R * 1.732 / 2;
	x = X * 1.5 * R + R;
	y = Y * 1.732 * R + (x % 2 ? x2 : 0) + x2;
	POINT hexagon[6] = { 0 };
	hexagon[0].x = x + r;
	hexagon[0].y = y;
	hexagon[1].x = x + r / 2;
	hexagon[1].y = y + 1.732 * r / 2 + 1;
	hexagon[2].x = x - r / 2;
	hexagon[2].y = y + 1.732 * r / 2 + 1;
	hexagon[3].x = x - r;
	hexagon[3].y = y;
	hexagon[4].x = x - r / 2;
	hexagon[4].y = y - 1.732 * r / 2;
	hexagon[5].x = x + r / 2;
	hexagon[5].y = y - 1.732 * r / 2;
	HBRUSH hbrush = CreateSolidBrush(color);
	HPEN hnPen = CreatePen(PS_SOLID, 1, 0x3232ac);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hnPen);
	SelectObject(hdc, hbrush);
	Polygon(hdc, hexagon, 6);
	DeleteObject(hbrush);
	DeleteObject(hnPen);
}

//六边形
void Hexagon(HDC hdc, int R, int x, int y, int width, COLORREF color)
{
	NewLine(0, hdc, x + R / 2, y - 1.73 * R / 2, x + R, y, width, color);
	NewLine(0, hdc, x - R / 2, y - 1.73 * R / 2, x - R, y, width, color);
	NewLine(0, hdc, x + R / 2, y + 1.73 * R / 2, x + R, y, width, color);
	NewLine(0, hdc, x - R / 2, y + 1.73 * R / 2, x - R, y, width, color);
	NewLine(0, hdc, x - R / 2, y - 1.73 * R / 2, x + R / 2, y - 1.73 * R / 2, width, color);
	NewLine(0, hdc, x - R / 2, y + 1.73 * R / 2, x + R / 2, y + 1.73 * R / 2, width, color);
}

//实际坐标转换成六边形坐标
NEWPOINT HexagonTransitionPoint(int transitionpointx, int transitionpointy, int R)
{
	int xi = transitionpointy / (1.73 * R), xo = transitionpointx / (1.5 * R);
	NEWPOINT alpha = { -1,-1 };
	for (int i = xi - 1; i <= xi + 1; i++)
		for (int o = xo - 1; o <= xo + 1; o++)
		{
			int x2 = R * 1.73 / 2, x = 1.5 * R * o + R, y = 1.73 * R * i + (o % 2 ? x2 : 0) + x2, beta[6] = { 0 },
				hexagonmapx = o * 1.5 * R + R, hexagonmapy = i * 1.73 * R + (o % 2 ? x2 : 0) + x2,
				pointx[6] = { hexagonmapx + R, hexagonmapx + R / 2, hexagonmapx - R / 2, hexagonmapx - R, hexagonmapx - R / 2, hexagonmapx + R / 2 },
				pointy[6] = { hexagonmapy, hexagonmapy + 1.73 * R / 2, hexagonmapy + 1.73 / 2 * R, hexagonmapy, hexagonmapy - 1.73 * R / 2, hexagonmapy - 1.73 * R / 2 };
			for (int k = 0; k < 6; k++) beta[k] = (transitionpointx - pointx[k]) * (pointy[k] - pointy[(k + 1) % 6]) - (transitionpointy - pointy[k]) * (pointx[k] - pointx[(k + 1) % 6]);
			if (beta[0] > 0 && beta[1] > 0 && beta[2] > 0 && beta[3] > 0 && beta[4] > 0 && beta[5] > 0) { alpha.x = o; alpha.y = i; }
		}
	return alpha;
}

//六边形坐标转换成实际坐标
NEWPOINT HexagonTurningPoint(int pointx, int pointy, int R)
{
	NEWPOINT returnpoint = { 0 };
	returnpoint.x = 1.5 * R * pointx + R;
	returnpoint.y = 1.73 * R * pointy + (pointx % 2 ? 1.73 / 2 * R : 0) + 1.73 / 2 * R;
	return returnpoint;
}

//创建连接关系
void HexagonConversion()
{
	for (int k = 0; k < MAPHEIGHT * MAPWIDTH; k++)
	{
		int o = k / MAPHEIGHT, i = k % MAPHEIGHT;
		for (int j = 0; j < 6; j++)map[k].hexagon[j] = -1;
		map[k].hexagon[4] = &map[RANGE(o, 0, 32) * MAPHEIGHT + RANGE(i - 1, 0, 22)];
		map[k].hexagon[1] = &map[RANGE(o, 0, 32) * MAPHEIGHT + RANGE(i + 1, 0, 22)];
		switch (o % 2)
		{
		case 0:
			map[k].hexagon[0] = &map[RANGE(o + 1, 0, 32) * MAPHEIGHT + RANGE(i, 0, 22)];
			map[k].hexagon[2] = &map[RANGE(o - 1, 0, 32) * MAPHEIGHT + RANGE(i, 0, 22)];
			map[k].hexagon[3] = &map[RANGE(o - 1, 0, 32) * MAPHEIGHT + RANGE(i - 1, 0, 22)];
			map[k].hexagon[5] = &map[RANGE(o + 1, 0, 32) * MAPHEIGHT + RANGE(i - 1, 0, 22)];
			break;

		case 1:
			map[k].hexagon[0] = &map[RANGE(o + 1, 0, 32) * MAPHEIGHT + RANGE(i + 1, 0, 22)];
			map[k].hexagon[2] = &map[RANGE(o - 1, 0, 32) * MAPHEIGHT + RANGE(i + 1, 0, 22)];
			map[k].hexagon[3] = &map[RANGE(o - 1, 0, 32) * MAPHEIGHT + RANGE(i, 0, 22)];
			map[k].hexagon[5] = &map[RANGE(o + 1, 0, 32) * MAPHEIGHT + RANGE(i, 0, 22)];
			break;
		}
	}
}

//修饰地形
void TerrainModification(HDC hdc, int boundary, int rad, int R, int X, int Y)
{
	int r = R,
		x = HexagonTurningPoint(X, Y, HEXAGONR).x,
		y = HexagonTurningPoint(X, Y, HEXAGONR).y;
	NEWPOINT hexagon[6] = { 0 }, hexagonA[6] = { 0 };
	hexagon[0].x = x + r;
	hexagon[0].y = y;
	hexagon[1].x = x + r / 2;
	hexagon[1].y = y + 1.732 * r / 2;
	hexagon[2].x = x - r / 2;
	hexagon[2].y = y + 1.732 / 2 * r;
	hexagon[3].x = x - r;
	hexagon[3].y = y;
	hexagon[4].x = x - r / 2;
	hexagon[4].y = y - 1.732 * r / 2;
	hexagon[5].x = x + r / 2;
	hexagon[5].y = y - 1.732 * r / 2;
	r = R + 1;
	hexagonA[0].x = x + r / 4. * 3;
	hexagonA[0].y = y + 1.732 / 4 * r;
	hexagonA[1].x = x;
	hexagonA[1].y = y + 1.732 / 2 * r;
	hexagonA[2].x = x - r / 4. * 3;
	hexagonA[2].y = y + 1.732 / 4 * r;
	hexagonA[3].x = x - r / 4. * 3;
	hexagonA[3].y = y - 1.732 / 4 * r;
	hexagonA[4].x = x;
	hexagonA[4].y = y - 1.732 / 2 * r;
	hexagonA[5].x = x + r / 4. * 3;
	hexagonA[5].y = y - 1.732 / 4 * r;
	switch (boundary)
	{
	case 'o': NewLine(0, hdc, hexagon[rad].x, hexagon[rad].y, hexagon[(rad + 1) % 6].x, hexagon[(rad + 1) % 6].y, 20, 0xc05c4a); break;
	case 'r': NewLine(0, hdc, hexagon[rad].x, hexagon[rad].y, hexagon[(rad + 1) % 6].x, hexagon[(rad + 1) % 6].y, 5, 0xff9b63); break;
	}
	if (map[X * MAPHEIGHT + Y].traintracks[rad] == TRUE) Line(0, hdc, x, y, hexagonA[rad].x, hexagonA[rad].y, 0x003a1c);
}

//绘制地图
void HexagonMapDrawing(HDC hdc, int R)
{
	BoxB(0, hdc, 0, 0, MAPIMGWIDTH, MAPIMGHEIGHT, 0xfcdbcb);
	for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
	{
		int x = i / MAPHEIGHT, y = i % MAPHEIGHT;
		switch (map[i].terrain)
		{
		case 'o': HexagonA(hdc, R, x, y, 0xc05c4a); break;
		case 'l': HexagonA(hdc, R, x, y, 0xd8f0fa); break;
		case 't':
		{
			NEWPOINT point = HexagonTurningPoint(x, y, HEXAGONR);
			HexagonA(hdc, R, x, y, 0xd8f0fa);
			for (int g = 0; g < 10; g++)
			{
				NEWPOINT pointA = { point.x - 10 + RANDOM(0, 20), point.y - 10 + RANDOM(0, 20) };
				NewLine(0, hdc, pointA.x, pointA.y, pointA.x, pointA.y, 15, 0x00823f);
			}
		}
		break;
		case 'm': HexagonA(hdc, R, x, y, 0xd8f0fa); HexagonB(hdc, R, R / 2, x, y, 0x3b568f); break;
		}
	}
	//river
	for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
	{
		int X = i / MAPHEIGHT, Y = i % MAPHEIGHT;
		for (int o = 0; o < 6; o++) TerrainModification(hdc, map[i].Boundary[o], o, HEXAGONR, X, Y);
		if (map[X * MAPHEIGHT + Y].citysid > FALSE)
			for (int o = 0; o < 6; o++)
			{
				int x = HexagonTurningPoint(X, Y, HEXAGONR).x,
					y = HexagonTurningPoint(X, Y, HEXAGONR).y;
				RECT city = { x - 15 + RANDOM(0,30), y - 15 + RANDOM(0,30),10, 10, };
				BoxC(0, hdc, city.left, city.top, city.right, city.bottom, (map[X * MAPHEIGHT + Y].citysid == 1 ? USSRCOLOR : (map[X * MAPHEIGHT + Y].citysid == 2 ? AXISCOLOR : 0)));
				NewPrintf(0, hdc, x - HEXAGONR / 2, y, map[X * MAPHEIGHT + Y].ragionname, (map[X * MAPHEIGHT + Y].citysid == 1 ? 0x8888ff : (map[X * MAPHEIGHT + Y].citysid == 2 ? 0 : 0)));
			}

	}
}

//----------------------------------------------------------------------------------------------------------------Unit----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//单位图标
void UnitIcon(HDC hdc, UNIT unit, RECT rect, int R)
{
	int alpha = R / 3, beta = alpha >> 1;
	RECT rectA = { rect.left + alpha, rect.top + beta, rect.left + alpha + 20, rect.top + beta + 15 };
	BoxA(0, hdc, rectA.left, rectA.top, rectA.right, rectA.bottom, 0);
	rectA.right -= 1, rectA.bottom -= 1;
	switch (unit.unit)
	{
		//inf
	case INF:
		Line(0, hdc, rectA.left, rectA.top, rectA.right, rectA.bottom, 0);
		Line(0, hdc, rectA.left, rectA.bottom, rectA.right, rectA.top, 0);
		break;
		//tank
	case TANK: Circle(0, hdc, 5, (rectA.left + rectA.right + 1) >> 1, (rectA.top + rectA.bottom + 1) >> 1, 0); break;
		//mechinf
	case MECHINF:
		Circle(0, hdc, 5, (rectA.left + rectA.right + 1) >> 1, (rectA.top + rectA.bottom + 1) >> 1, 0);
		Line(0, hdc, rectA.left, rectA.top, rectA.right, rectA.bottom, 0);
		Line(0, hdc, rectA.left, rectA.bottom, rectA.right, rectA.top, 0);
		break;
		//mot
	case MOT:
		Line(0, hdc, rectA.left, rectA.top, rectA.right, rectA.bottom, 0);
		Line(0, hdc, rectA.left, rectA.bottom, rectA.right, rectA.top, 0);
		NewLine(0, hdc, rectA.left + 3, rectA.bottom, rectA.left + 2, rectA.bottom, 6, 0);
		NewLine(0, hdc, rectA.right - 2, rectA.bottom, rectA.right - 2, rectA.bottom, 6, 0);
		break;
		//hq
	case HQ:
		BoxB(0, hdc, rectA.left, rectA.top, (rectA.left + rectA.right + 1) >> 1, (rectA.top + rectA.bottom + 1) >> 1, 0);
		BoxB(0, hdc, (rectA.left + rectA.right + 1) >> 1, (rectA.top + rectA.bottom + 1) >> 1, rectA.right, rectA.bottom, 0);
		break;
		//sec
	case SEC: Text(0, hdc, rectA.left - 2, rectA.top, L"sec", 0); break;
		//rominf
	case ROMINF:
		Text(0, hdc, rect.left, rect.top + alpha, L"r", 0x00ff00);
		Line(0, hdc, rectA.left, rectA.top, rectA.right, rectA.bottom, 0x00ee00);
		Line(0, hdc, rectA.left, rectA.bottom, rectA.right, rectA.top, 0x00ee00);
		break;
		//romtank
	case ROMTANK:
		Text(0, hdc, rect.left, rect.top + alpha, L"r", 0x00ff00);
		Circle(0, hdc, 5, (rectA.left + rectA.right + 1) >> 1, (rectA.top + rectA.bottom + 1) >> 1, 0x00ee00);
		break;
		//cav
	case CAV: Line(0, hdc, rectA.left, rectA.bottom, rectA.right, rectA.top, 0); break;
		//mtnd
	case MTND:
		Line(0, hdc, rectA.left, rectA.top, rectA.right, rectA.bottom, 0);
		Line(0, hdc, rectA.left, rectA.bottom, rectA.right, rectA.top, 0);
		NewLine(0, hdc, (rectA.left + rectA.right) >> 1, rectA.bottom - 2, (rectA.left + rectA.right + 1) >> 1, rectA.bottom - 2, 6, 0);
		break;
	}
}

//绘制单位
void UnitDrawing(HDC hdc, UNIT unit, int sid, int X, int Y, int mousehexagonx, int mousehexagony, int Mapx, int Mapy)
{
	if (sid <= 0)return;
	int alpha = HEXAGONR / 3, beta = alpha >> 1;
	NEWPOINT coor = HexagonTurningPoint(X, Y, HEXAGONR);
	RECT rect = { coor.x - alpha * 1.7 + Mapx, coor.y - alpha * 1.7 + Mapy, alpha * 3.5, alpha * 3.5 };
	if (X == mousehexagonx && Y == mousehexagony)
	{
		BoxC(0, hdc, rect.left, rect.top, rect.right, rect.bottom, 0x777777);
		rect.left = coor.x - alpha * 2 + Mapx;
		rect.top = coor.y - alpha * 2 + Mapy;
		rect.right = alpha * 3.5;
		rect.bottom = alpha * 3.5;
		BoxC(0, hdc, rect.left, rect.top, rect.right, rect.bottom, (sid == 1 ? USSRCOLOR : AXISCOLOR));
	}
	else
	{
		BoxC(0, hdc, rect.left, rect.top, rect.right, rect.bottom, 0x333333);
		rect.left = coor.x - alpha * 1.9 + Mapx;
		rect.top = coor.y - alpha * 1.9 + Mapy;
		rect.right = alpha * 3.5;
		rect.bottom = alpha * 3.5;
		BoxC(0, hdc, rect.left, rect.top, rect.right, rect.bottom, (sid == 1 ? USSRCOLOR : AXISCOLOR));
	}
	UnitIcon(hdc, unit, rect, HEXAGONR);
	if (unit.supply <= 0)NewLine(0, hdc, rect.left + 3, rect.top + 3, rect.left + 3, rect.top + 3, 7, 0x00eeee);
	if (unit.battleemblem)NewLine(0, hdc, rect.left + 3, rect.top + 10, rect.left + 3, rect.top + 10, 7, 0x009900);
	Dight(0, hdc, rect.left + beta, rect.top + beta + alpha * 1.5, unit.Attacker, 0xeeee00);		//攻击力
	Dight(0, hdc, rect.left + beta + 8, rect.top + beta + alpha * 1.5, unit.Defender, 0x30ee6a);	//防御力
	Dight(0, hdc, rect.left + beta + 16, rect.top + beta + alpha * 1.5, unit.Mobility, 0xffffff);	//移动力
}

//统一绘制地图单位
void UnitMapDrawing(HDC hdc)
{
	for (int o = 0; o < MAPWIDTH; o++)
		for (int i = 0; i < MAPHEIGHT; i++)
		{
			if (map[o * MAPHEIGHT + i].unit[0].people <= 0)continue;
			if ((map[o * MAPHEIGHT + i].unit[0].sid == 1 && (map[o * MAPHEIGHT + i].unit[0].unit >= 6 && map[o * MAPHEIGHT + i].unit[0].unit <= 8)) || (map[o * MAPHEIGHT + i].unit[0].sid == 2 && map[o * MAPHEIGHT + i].unit[0].unit == 9))map[o * MAPHEIGHT + i].unit[0].people = 0;
			if (map[o * MAPHEIGHT + i].unit[0].people > 0) UnitDrawing(hdc, map[o * MAPHEIGHT + i].unit[0], map[o * MAPHEIGHT + i].unit[0].sid, o, i, hexagonpointA.x, hexagonpointA.y, mapx, mapy);
		}
}

//重置单位移动力
void UnitReset(UNIT* unit, int mode)
{
	//mode 1 Round | 2 fight
	if (unit->people <= 0)return;
	switch (unit->unit)
	{
	case 1:  unit->Mobility = (mode == 1 ? 4 : 0); break;	//inf 
	case 2:  unit->Mobility = (mode == 1 ? 6 : 0); break;	//tank 
	case 3:  unit->Mobility = (mode == 1 ? 10 : 0); break;	//mechinf 
	case 4:  unit->Mobility = (mode == 1 ? 6 : 0); break;	//mot 
	case 5:  unit->Mobility = (mode == 1 ? 8 : 0); break;	//hq
	case 6:  unit->Mobility = (mode == 1 ? 4 : 0); break;	//sec
	case 7:  unit->Mobility = (mode == 1 ? 4 : 0); break;	//rominf 
	case 8:  unit->Mobility = (mode == 1 ? 6 : 0); break;	//romtank
	case 9:  unit->Mobility = (mode == 1 ? 5 : 0); break;	//cav 
	case 10: unit->Mobility = (mode == 1 ? 4 : 0); break;	//mtnd
	}
}

//重置单位移战斗力
void UnitPeople(UNIT* unit)
{
	if (unit->people <= 0)return;
	if (unit->people > 2)unit->people = 2;
	if (unit->unit == 7 || unit->unit == 8 || unit->unit == 5)unit->people = 1;
	switch (unit->people)
	{
	case 2:
		switch (unit->sid)
		{
		case 1:
			switch (unit->unit)
			{
			case INF: unit->Attacker = 2; unit->Defender = 2; break;	//inf 
			case TANK:unit->Attacker = 4; unit->Defender = 2; break;	//tank 
			case MECHINF:unit->Attacker = 3; unit->Defender = 3; break;	//mechinf 
			case MOT:unit->Attacker = 2; unit->Defender = 3; break;	//mot 
			case CAV:unit->Attacker = 2; unit->Defender = 2; break;	//cav 
			case MTND:unit->Attacker = 2; unit->Defender = 2; break;	//mtnd
			}
			break;

		case 2:
			switch (unit->unit)
			{
			case INF:unit->Attacker = 3; unit->Defender = 3; break;	//inf 
			case TANK:unit->Attacker = 8; unit->Defender = 4; break;	//tank 
			case MECHINF:unit->Attacker = 6; unit->Defender = 5; break;	//mechinf 
			case MOT:unit->Attacker = 5; unit->Defender = 5; break;	//mot 
			case SEC:unit->Attacker = 2; unit->Defender = 2; break;	//sec
			case MTND:unit->Attacker = 3; unit->Defender = 3; break;	//mtnd
			}
			break;
		}
		break;

	case 1:
		switch (unit->sid)
		{
		case 1:
			switch (unit->unit)
			{
			case INF:unit->Attacker = 1; unit->Defender = 1; break;	//inf 
			case TANK:unit->Attacker = 3; unit->Defender = 1; break;	//tank 
			case MECHINF:unit->Attacker = 2; unit->Defender = 2; break;	//mechinf 
			case MOT:unit->Attacker = 1; unit->Defender = 2; break;	//mot 
			case HQ:unit->Attacker = 0; unit->Defender = 0; break;	//hq
			case CAV:unit->Attacker = 1; unit->Defender = 1; break;	//cav 
			case MTND:unit->Attacker = 1; unit->Defender = 1; break;	//mtnd
			}
			break;

		case 2:
			switch (unit->unit)
			{
			case INF:unit->Attacker = 2; unit->Defender = 2; break;	//inf 
			case TANK:unit->Attacker = 7; unit->Defender = 3; break;	//tank 
			case MECHINF:unit->Attacker = 5; unit->Defender = 4; break;	//mechinf 
			case MOT:unit->Attacker = 4; unit->Defender = 4; break;	//mot 
			case HQ:unit->Attacker = 0; unit->Defender = 0; break;	//hq
			case SEC:unit->Attacker = 1; unit->Defender = 1; break;	//sec
			case ROMINF:unit->Attacker = 1; unit->Defender = 1; break;	//rominf 
			case ROMTANK:unit->Attacker = 2; unit->Defender = 1; break;	//romtank
			case MTND:unit->Attacker = 2; unit->Defender = 2; break;	//mtnd
			}
			break;
		}
		break;
	}
}

//清零
void UnitZero(UNIT* unit)
{
	unit->Attacker = 0;
	unit->Defender = 0;
	unit->Mobility = 0;
	unit->people = 0;
	unit->sid = 0;
	unit->supply = 0;
	unit->unit = 0;
	unit->battleemblem = 0;
}

//单位压栈
void UnitStacking(MAP* map)
{
	for (int i = 0; i < 5; i++)
		for (int o = 4; o > 0; o--)
			if (map->unit[(o - 1)].people <= 0)
			{
				map->unit[(o - 1)] = map->unit[(o)];
				UnitZero(&(map->unit[o]));
			}
}

//战斗函数
int UnitCombat(MAP* map, MAP* targetpoint)
{
	if (map->unit[0].people <= 0 || targetpoint->unit[0].people <= 0)return Error;
	int number = NOTFOUND, out = 0;
	for (int i = 0; i < 6; i++)
		if (map->hexagon[i] == targetpoint) { number = i; break; }
	if (!(number + 1))return Error;
	else if (targetpoint->unit[0].sid == map->unit[0].sid || targetpoint->unit[0].sid == 0)return Error;
	else if (unitselect[0] || unitselect[1] || unitselect[2] || unitselect[3] || unitselect[4])
	{
		int Attacker = 0, Defender = 0, superstacked = 0, harm = 0, outcome = NOTFOUND, Attackernumber = 0;
		for (int i = 0; i < 5; i++)
		{
			int beta = 0;
			if (unitselect[i])
			{
				if (targetpoint->unit[i].people > 0 && map->unit[i].supply > 0) Defender += targetpoint->unit[i].Defender;
				if (map->unit[i].people <= 0 || map->unit[i].supply <= 0 || map->unit[i].battleemblem)continue;
				Attacker += map->unit[i].Attacker;
				if (map->unit[0].sid == 2)UnitReset(&(map->unit[i]), 2);
				if (map->unit[i].sid == 1 && beta == 3)break;
				if (map->unit[i].sid == 2 && beta == 2)break;
				beta++;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			int beta = 0;
			if (targetpoint->unit[i].people > 0)beta++;
			if (targetpoint->unit[i].sid == 1 && beta > 3)superstacked = 1;
			if (targetpoint->unit[i].sid == 2 && beta > 2)superstacked = 1;
		}
		if (Attacker == 0)return Error;
		if (map->Boundary[number] == 'r')Attacker /= 2;
		if (Attacker < Defender)return Error;
		if (Defender > 0)
		{
			int alpha = Attacker / Defender, battlesrand = RANDOM(0, 6);
			if (targetpoint->terrain == 'm')alpha = 0;
			if (targetpoint->citysid > 0)alpha = RANGE(alpha - 2, 0, 7);
			if (targetpoint->hexagon == 't')alpha = RANGE(alpha - 1, 0, 7);
			alpha = RANGE(alpha - 1, 0, 6);//匹配裁决表
			outcome = arrcombatjudgmenttable[RANGE(alpha, 0, 6)][battlesrand];
			for (int i = 0; i < 5; i++)
				if (unitselect[i])map->unit[i].battleemblem = 1;
			//printf("alpha:%d ", alpha);
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				UnitZero(&(targetpoint->unit[i]));
				if (unitselect[i])map->unit[i].battleemblem = 1;
			}
			return Error;
		}
		if (superstacked) harm = Attacker * RANDOM(1, 7);
		switch (outcome)
		{
		case 0x1a:
		{
			for (int i = 0; i < 5; i++) if (unitselect[i] && map->unit[Attackernumber].people > 0)Attackernumber = i;
			map->unit[Attackernumber].people -= 1;
		}
		break;
		case 0x0e:
		{
			harm = 1;
			for (int i = 0; i < 5; i++) if (unitselect[i] && map->unit[Attackernumber].people > 0)Attackernumber = i;
			map->unit[Attackernumber].people -= 1;
			if (map->unit[Attackernumber].people <= 0)UnitZero(&(map->unit[Attackernumber]));
			UnitPeople(&(map->unit[Attackernumber]));
		}
		break;
		case 0x1d1:harm = 1; break;
		case 0x1d2:harm = 1; break;
		case 0x2d2:harm = 2; break;
		case 0x3d2:harm = 3; break;
		}
		//printf("harm:%d outcome:%x\n", harm, outcome);
		for (int i = 0; i < 5; i++)
		{
			int harmnumber = 0;
			for (int o = 0; o < harm; o++)
			{
				harmnumber++;
				targetpoint->unit[i].people -= 1;
				if (targetpoint->unit[i].people <= 0)break;
			}
			harm -= harmnumber;
		}
		if (map->unit[Attackernumber].people <= 0)UnitZero(&(map->unit[Attackernumber]));
		for (int i = 0; i < 5; i++)
		{
			if (targetpoint->unit[i].people <= 0)UnitZero(&(targetpoint->unit[i]));
			UnitPeople(&(targetpoint->unit[i]));
		}
		UnitStacking(map);
		UnitStacking(targetpoint);
		out = outcome;
	}
	return out;
}

//单位撤退辅助函数
MAP* UnitFallBackTransform(int sid, MAP* targetpoint)
{
	//if (targetpoint->unit[0].sid == sid)return targetpoint;
	//Only the defenders will retreat
	MAP* returnmap;
	int score[6] = { 0 }, number = 0, enemy = FALSE;
	for (int i = 6; i < 12; i++)
	{
		if ((targetpoint->unit[0].sid == 1 && targetpoint->hexagon[i % 6]->unit[0].sid == 2) || (targetpoint->unit[0].sid == 2 && targetpoint->hexagon[i % 6]->unit[0].sid == 1))
		{
			score[i % 6] -= 999;
			score[(i + 3) % 6] += 23;
			score[(i + 2) % 6] += 23;
			score[(i - 2) % 6] += 23;
			score[(i + 1) % 6] += 5;
			score[(i - 1) % 6] += 5;
		}
		if (targetpoint->hexagon[i % 6]->terrain == 'o' || targetpoint->Boundary[i % 6] == 'o')score[i % 6] -= 999;
		if (targetpoint->hexagon[i % 6]->unit[4].people > 0)score[i % 6] -= 999;
		if (targetpoint->Boundary[i % 6] == 'r')score[i % 6] += 15;
		for (int o = 0; o < 6; o++)
			if ((targetpoint->hexagon[i % 6]->unit[o].sid == 1 && targetpoint->unit[o].sid == 2) || (targetpoint->hexagon[i % 6]->unit[o].sid == 2 && targetpoint->unit[o].sid == 1)) { score[i % 6] -= 15; break; }
	}
	score[RANDOM(0, 6)] += 10;
	for (int i = 0; i < 6; i++)
		if (score[number] <= score[i])number = i;
	if (score[number] < 0)
	{
		for (int i = 0; i < 6; i++)UnitZero(&(targetpoint->unit[i]));
		return targetpoint;
	}
	else returnmap = targetpoint->hexagon[number];

	for (int i = 0; i < 6; i++)
		if (returnmap->hexagon[i]->unit[0].sid != targetpoint->unit[0].sid && returnmap->hexagon[i]->unit[0].sid != 0) enemy = TRUE;

	if (enemy)
	{
		targetpoint->unit[0].people -= 1;
		if (targetpoint->unit[0].people <= 0)
		{
			UnitZero(&(targetpoint->unit[0]));
			UnitStacking(targetpoint);
			return targetpoint;
		}
		else UnitPeople(&(targetpoint->unit[0]));
		//printf("[ok]\n");
	}
	if (returnmap->unit[0].people <= 0)
	{
		for (int i = 0; i < 5; i++)
		{
			returnmap->unit[i] = targetpoint->unit[i];
			UnitZero(&(targetpoint->unit[i]));
		}
		return targetpoint;
	}
	else if (returnmap->unit[0].people > 0)
	{
		int numberA = 0;
		for (int i = 0; i < 5; i++)
			if (returnmap->unit[i].people > 0)continue;
			else { returnmap->unit[i] = targetpoint->unit[numberA]; numberA++; }
		for (int i = 0; i < 6; i++)UnitZero(&(targetpoint->unit[i]));
	}
	return returnmap;
}

//单位撤退
void UnitFallBack(int sid, int combatoutcome, MAP* map, MAP* targetpoint)
{
	if (combatoutcome == 0xd1)
		UnitFallBackTransform(sid, targetpoint);
	else if (combatoutcome == 0xd2 || combatoutcome == 0x1d2 || combatoutcome == 0x2d2 || combatoutcome == 0x3d2)
	{
		MAP* ta = UnitFallBackTransform(sid, targetpoint);
		UnitFallBackTransform(sid, ta);
	}
	//Attacker reward
	if (combatoutcome == 0xd1 || combatoutcome == 0xd2 || combatoutcome == 0x1d2 || combatoutcome == 0x2d2 || combatoutcome == 0x3d2)
		for (int i = 0; i < 5; i++)
			if (unitselect[i])
			{
				map->unit[i].Mobility = 2;
				if (map->unit[i].unit == TANK || map->unit[i].unit == MECHINF)map->unit[i].Mobility += 2;
				unitselect[i] = FALSE;
			}
}

//UnitMove辅助函数
void UnitMoveTransform(int Mobility, MAP* map, MAP* targetpoint, int i, int numberA)
{
	if (map->unit[i].Mobility - Mobility >= 0)
	{
		map->unit[i].Mobility -= Mobility;
		targetpoint->unit[numberA] = map->unit[i];
		UnitZero(&(map->unit[i]));
	}
}

//单位移动
void UnitMove(MAP* map, MAP* targetpoint)
{
	if (map->unit[0].people <= 0)return;
	int number = NOTFOUND;
	for (int i = 0; i < 6; i++)
		if (map->hexagon[i] == targetpoint) { number = i; break; }
	if (!(number + 1))return;
	else if (targetpoint->terrain == 'o' || map->Boundary[number] == 'o')return;
	else if (!(targetpoint->unit[0].sid == 0 || targetpoint->unit[0].sid == map->unit[0].sid))return;
	else if (unitselect[0] || unitselect[1] || unitselect[2] || unitselect[3] || unitselect[4])
	{
		for (int i = 0; i < 5; i++)
			if (unitselect[i])
			{
				if (map->unit[i].people <= 0 || map->unit[i].supply <= 0)continue;
				int numberA = NOTFOUND;
				for (int o = 0; o < 5; o++)
					if (!targetpoint->unit[o].people) { numberA = o; break; }
				if (numberA != NOTFOUND)
				{
					if (map->traintracks[number]) UnitMoveTransform(1, map, targetpoint, i, numberA);
					else if (map->Boundary[number] == 'r')
					{
						switch (map->unit[i].unit)
						{
						case INF:  UnitMoveTransform(4, map, targetpoint, i, numberA); break;	//inf 
						case TANK:  UnitMoveTransform(6, map, targetpoint, i, numberA); break;	//tank 
						case MECHINF:  UnitMoveTransform(10, map, targetpoint, i, numberA); break;//mechinf 
						case MOT:  UnitMoveTransform(6, map, targetpoint, i, numberA); break;	//mot 
						case HQ:  UnitMoveTransform(8, map, targetpoint, i, numberA); break;	//hq
						case SEC:  UnitMoveTransform(4, map, targetpoint, i, numberA); break;	//sec
						case ROMINF:  UnitMoveTransform(4, map, targetpoint, i, numberA); break;	//rominf 
						case ROMTANK:  UnitMoveTransform(6, map, targetpoint, i, numberA); break;	//romtank
						case CAV:  UnitMoveTransform(5, map, targetpoint, i, numberA); break;	//cav 
						case MTND: UnitMoveTransform(4, map, targetpoint, i, numberA); break;	//mtnd
						}
					}
					else switch (targetpoint->terrain)
					{
					case 'l': UnitMoveTransform(2, map, targetpoint, i, numberA); break;
					case 'm':
						if (map->unit[i].Mobility - 4 >= 0 && map->unit[i].unit == 10)
						{
							map->unit[i].Mobility -= 4;
							targetpoint->unit[numberA] = map->unit[i];
							UnitZero(&(map->unit[i]));
						}
						break;
					case 't': UnitMoveTransform(4, map, targetpoint, i, numberA); break;
					}
				}
			}
		UnitStacking(map);
		UnitStacking(targetpoint);
	}
}

//绘制命令栏
void UnitCommandDrawing(MAP map, HDC hdc)
{
	if (map.unit[0].people > 0)
		for (int i = 0; i < 5; i++)
		{
			//if (map.unit[i].people <= 0) continue; // 跳过空单位槽
			GAME Game; Game.doublebuffer.hdc = hdc;
			int alpha = HEXAGONR / 3;
			RECT rect = { 0, i * (PARENTWINDOWWIDTH + 5), PARENTWINDOWWIDTH, PARENTWINDOWWIDTH };
			RECT rectA = { rect.left + PARENTWINDOWWIDTH / 10 * 7, rect.top + PARENTWINDOWWIDTH / 8, rect.left + PARENTWINDOWWIDTH / 4 * 3 + alpha, rect.top + PARENTWINDOWWIDTH / 4 + HEXAGONR / 4 };
			BoxC(0, hdc, 0, i * (PARENTWINDOWWIDTH + 5), PARENTWINDOWWIDTH, PARENTWINDOWWIDTH, (map.unit[i].sid == 1 ? USSRCOLOR : (map.unit[i].sid == 2 ? AXISCOLOR : 0x333333)));
			UnitIcon(hdc, map.unit[i], rect, HEXAGONR);
			BoxA(0, hdc, rectA.left, rectA.top, rectA.right, rectA.bottom, 0);
			if (map.unit[i].supply <= 0)NewLine(0, hdc, rect.left + 3, rect.top + 3, rect.left + 3, rect.top + 3, 7, 0x00eeee);
			if (map.unit[i].battleemblem)NewLine(0, hdc, rect.left + 3, rect.top + 10, rect.left + 3, rect.top + 10, 7, 0x009900);
			Dight(0, hdc, rect.left + alpha / 2, rect.top + alpha * 3, map.unit[i].Attacker, 0xeeee00);			//攻击力
			Dight(0, hdc, rect.left + alpha / 2 + 10, rect.top + alpha * 3, map.unit[i].Defender, 0x00ee00);	//防御力
			Dight(0, hdc, rect.left + alpha / 2 + 20, rect.top + alpha * 3, map.unit[i].Mobility, 0xffffff);	//移动力
			Dight(0, hdc, rect.left + alpha, rect.top + alpha * 3 - alpha * 1.2, map.unit[i].people, 0xffffff);	//people
			Dight(0, hdc, rect.left + alpha * 2, rect.top + alpha * 3 - alpha * 1.2, map.unit[i].supply, 0xff00ff);	//supply
			if (unitselect[i])
			{
				BOXA(&Game, rect.left + alpha / 3, rect.top + alpha / 3, PARENTWINDOWWIDTH - alpha / 3 * 2, PARENTWINDOWWIDTH - alpha / 3 * 2, 0x00aaaa);
				Text(0, hdc, rectA.left + 3, rectA.top - 1, L"X", 0x006400);
			}
		}
	else BoxB(0, hdc, 0, 0, PARENTWINDOWWIDTH, 5 * (PARENTWINDOWWIDTH + 5), 0xeeeeee);
	Line(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5), PARENTWINDOWWIDTH, 5 * (PARENTWINDOWWIDTH + 5), 0);
}

//命令栏单位选择
void UnitChoose(int mode)
{
	int number = MOUSEY / (PARENTWINDOWWIDTH + 5);
	if (number >= 0 && number < 5) unitselect[number] = (mode ? TRUE : FALSE);
}

//初始化单位
int InitialisationUnit(UNIT* unit, int unittype, int sid)
{
	int out = FALSE;
	unit->unit = unittype;
	unit->sid = sid;
	unit->supply = 1;
	unit->people = 2;
	if (unittype == 5 || unittype == 7 || unittype == 8)unit->people = 1;
	switch (sid)
	{
	case 1:
		switch (unittype)
		{
		case 1:unit->Attacker = 2; unit->Defender = 2; unit->Mobility = 4; out = TRUE; break;	//inf
		case 2:unit->Attacker = 4; unit->Defender = 2; unit->Mobility = 6; out = TRUE; break;	//tank
		case 3:unit->Attacker = 3; unit->Defender = 3; unit->Mobility = 10; out = TRUE; break;	//mechinf
		case 4:unit->Attacker = 2; unit->Defender = 3; unit->Mobility = 6; out = TRUE; break;	//mot
		case 5:unit->Attacker = 0; unit->Defender = 0; unit->Mobility = 8; out = TRUE; break;	//hq
		case 9:unit->Attacker = 2; unit->Defender = 2; unit->Mobility = 5; out = TRUE; break;	//cav
		case 10:unit->Attacker = 2; unit->Defender = 2; unit->Mobility = 4; out = TRUE; break;	//mtnd
		}
		break;
	case 2:
		switch (unittype)
		{
		case 1:unit->Attacker = 3; unit->Defender = 3; unit->Mobility = 4; out = TRUE; break;	//inf
		case 2:unit->Attacker = 8; unit->Defender = 4; unit->Mobility = 6; out = TRUE; break;	//tank
		case 3:unit->Attacker = 6; unit->Defender = 5; unit->Mobility = 10; out = TRUE; break;	//mechinf
		case 4:unit->Attacker = 5; unit->Defender = 5; unit->Mobility = 10; out = TRUE; break;	//mot
		case 5:unit->Attacker = 0; unit->Defender = 0; unit->Mobility = 8; out = TRUE; break;	//hq
		case 6:unit->Attacker = 2; unit->Defender = 2; unit->Mobility = 4; out = TRUE; break;	//sec
		case 7:unit->Attacker = 1; unit->Defender = 1; unit->Mobility = 4; out = TRUE; break;	//rominf
		case 8:unit->Attacker = 2; unit->Defender = 1; unit->Mobility = 6; out = TRUE; break;	//romtank
		case 10:unit->Attacker = 3; unit->Defender = 3; unit->Mobility = 4; out = TRUE; break;	//mtnd
		}
		break;
	}
	return out;
}

//补给判定辅助函数
void UnitSupplyTransform(int i, int sid, int hqsupply)
{
	for (int o = 0; o < 5; o++)
		if (map[i].unit[o].people > 0 && map[i].unit[o].unit == HQ && map[i].unit[o].sid == sid) hqsupply = TRUE;
	for (int o = 0; o < 6; o++)
	{
		int disseminate = FALSE;
		for (int j = 0; j < 5; j++)
			if (map[i].hexagon[o]->terrain != 'o' || map[i].Boundary != 'o')
				if (map[i].hexagon[o]->unit[j].people > 0 && map[i].hexagon[o]->unit[j].sid == sid && hqsupply) map[i].hexagon[o]->unit[j].supply += 1;
		if ((map[i].hexagon[o]->unit[0].sid == sid || map[i].hexagon[o]->unit[0].sid <= 0) && hqsupply) disseminate = TRUE;
		if (disseminate)
			for (int k = 0; k < 6; k++)
				for (int j = 0; j < 5; j++)
					if (map[i].hexagon[o]->hexagon[k]->unit[j].people > 0 && map[i].hexagon[o]->hexagon[k]->unit[j].sid == sid && hqsupply) map[i].hexagon[o]->hexagon[k]->unit[j].supply += 1;
	}
}

//补给判定函数
void UnitSupply(int sid)
{
	for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
	{
		int hqsupply = FALSE;
		switch (sid)
		{
		case 1: if (map[i].USSRReplenish == TRUE) UnitSupplyTransform(i, 1, hqsupply); break;
		case 2: if (map[i].AXISReplenish == TRUE) UnitSupplyTransform(i, 2, hqsupply); break;
		}
		for (int o = 0; o < 5; o++) if (map[i].unit[o].people > 0 && map[i].unit[o].unit == HQ && map[i].unit[o].sid == sid) map[i].unit[o].supply = TRUE;
		for (int o = 0; o < 5; o++)
			if (map[i].unit[o].unit != MOT) map[i].unit[o].supply = min(map[i].unit[o].supply, 2);
			else map[i].unit[o].supply = min(map[i].unit[o].supply, (sid == 1 ? 6 : (sid == 2 ? 4 : 0)));
	}
}

//增援
void UnitReinforce(MAP* Map, int sid, int* manpower, int* industry, int* rommanpower, int* romindustry)
{
	if (Map->terrain == 'o')return;
	if (MOUSEX >= 0 && MOUSEX < WINDOWWIDTH && MOUSEY >= 0 && MOUSEY < WINDOWHEIGHT)
	{
		int hqfound = FALSE;
		if (Map->unit[0].sid == sid || Map->unit[0].sid == 0)
		{
			for (int i = 0; i < 6; i++)
				for (int o = 0; o < 5; o++)
					if (Map->hexagon[i]->unit[o].people > 0 && Map->hexagon[i]->unit[o].unit == HQ && (sid == 1 ? Map->hexagon[i]->USSRReplenish : (sid == 2 ? Map->hexagon[i]->AXISReplenish : FALSE)) && Map->hexagon[i]->unit[o].sid == sid)
						hqfound = TRUE;
			for (int o = 0; o < 5; o++)
				if (Map->unit[o].people > 0 && Map->unit[o].unit == HQ && (sid == 1 ? Map->USSRReplenish : (sid == 2 ? Map->AXISReplenish : FALSE)) && Map->unit[o].sid == sid)
					hqfound = TRUE;
		}
		if (hqfound)
			for (int i = 0; i < 5; i++)
				if (Map->unit[i].people <= 0)
				{
					int gamma = InitialisationUnit(&Map->unit[i], unitreinforcementoptions, sid);
					if (gamma)
					{

						switch (unitreinforcementoptions)
						{
						case INF:		if (*manpower < 3)							UnitZero(&Map->unit[i]); else { *manpower -= 3; } break;
						case TANK:		if (*manpower < 3 || *industry < 8)			UnitZero(&Map->unit[i]); else { *manpower -= 3; *industry -= 8; } break;
						case MECHINF:	if (*manpower < 6 || *industry < 4)			UnitZero(&Map->unit[i]); else { *manpower -= 6; *industry -= 4; } break;
						case MOT:		if (*manpower < 6 || *industry < 6)			UnitZero(&Map->unit[i]); else { *manpower -= 6; *industry -= 6; } break;
						case HQ:		if (*manpower < 8)							UnitZero(&Map->unit[i]); else { *manpower -= 8; } break;
						case SEC:		if (*manpower < 2)							UnitZero(&Map->unit[i]); else { *manpower -= 2; } break;
						case ROMINF:	if (*rommanpower < 1)						UnitZero(&Map->unit[i]); else { *rommanpower -= 1; } break;
						case ROMTANK:	if (*rommanpower < 1 || *romindustry < 1)	UnitZero(&Map->unit[i]); else { *rommanpower -= 1; *romindustry -= 1; } break;
						case CAV:		if (*manpower < 4)							UnitZero(&Map->unit[i]); else { *manpower -= 4; } break;
						case MTND:		if (*manpower < 4)							UnitZero(&Map->unit[i]); else { *manpower -= 4; } break;
						}
					}
					return;
				}
	}
	else if (MOUSEX >= WINDOWWIDTH && MOUSEX < WINDOWWIDTH + 17 + PARENTWINDOWWIDTH && MOUSEY >= (7 * (PARENTWINDOWWIDTH + 10)) && MOUSEY < (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 10 + 20)
	{
		unitreinforcementoptions = (MOUSEY - (7 * (PARENTWINDOWWIDTH + 10))) / 20;
	}
}
void UnitReinforceA(HDC hdc)
{
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 1, L"INF", (unitreinforcementoptions == 1 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 2, L"TANK", (unitreinforcementoptions == 2 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 3, L"MECHINF", (unitreinforcementoptions == 3 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 4, L"MOT", (unitreinforcementoptions == 4 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 5, L"HQ", (unitreinforcementoptions == 5 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 6, L"SEC", (unitreinforcementoptions == 6 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 7, L"ROMINF", (unitreinforcementoptions == 7 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 8, L"ROMTANK", (unitreinforcementoptions == 8 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 9, L"CAV", (unitreinforcementoptions == 9 ? 0x0000ff : 0));
	Text(0, hdc, 0, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 10, L"MTND", (unitreinforcementoptions == 10 ? 0x0000ff : 0));
}

//----------------------------------------------------------------------------------------------------------------Game----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//铁路补给传输
void GameSupply(MAP* startmap, int sid, int depth)
{
	depth--;
	if (depth <= 0)return;
	MAP* nextmap[6] = { NULL };
	BOOL out[6] = { FALSE };
	for (int i = 0; i < 6; i++)
		if (startmap->traintracks[i] == TRUE)
			switch (sid)
			{
			case 1:
				if (!startmap->hexagon[i]->USSRReplenish)
				{
					startmap->hexagon[i]->USSRReplenish = TRUE;
					nextmap[i] = startmap->hexagon[i];
				}
				else out[i] = TRUE;
				if (startmap->unit[0].people > 0 && startmap->unit[0].sid == 2)out[i] = TRUE;
				break;

			case 2:
				if (!startmap->hexagon[i]->AXISReplenish)
				{
					startmap->hexagon[i]->AXISReplenish = TRUE;
					nextmap[i] = startmap->hexagon[i];
				}
				else out[i] = TRUE;
				if (startmap->unit[0].people > 0 && startmap->unit[0].sid == 1)out[i] = TRUE;
				break;
			}
		else out[i] = TRUE;
	for (int i = 0; i < 6; i++)
		if (out[i])continue;
		else GameSupply(nextmap[i], sid, depth);
}

void GamePhaseTransform(int sid, int state, NEWPOINT beta)
{
	if (MOUSEX >= 0 && MOUSEX < WINDOWWIDTH && MOUSEY >= 0 && MOUSEY < WINDOWHEIGHT)
		if (map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y].unit[0].sid == sid)
			switch (state)
			{
			case 1: UnitMove(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], &map[beta.x * MAPHEIGHT + beta.y]); break;//move
				//combat
			case 2:
				arrcombatjudgmenttableout = UnitCombat(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], &map[beta.x * MAPHEIGHT + beta.y]);
				UnitFallBack(sid, arrcombatjudgmenttableout, &map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], &map[beta.x * MAPHEIGHT + beta.y]);
				break;
			}
}

void GameOut()
{
	FILE* fp = fopen(arrgameoutname, "wb");
	fwrite(&phase, sizeof(int), 1, fp);
	fwrite(&gameyear, sizeof(int), 1, fp);
	fwrite(&gamemon, sizeof(int), 1, fp);
	fwrite(&axismanpower, sizeof(int), 1, fp);
	fwrite(&axisindustry, sizeof(int), 1, fp);
	fwrite(&rommanpower, sizeof(int), 1, fp);
	fwrite(&romindustry, sizeof(int), 1, fp);
	fwrite(&ussrmanpower, sizeof(int), 1, fp);
	fwrite(&ussrindustry, sizeof(int), 1, fp);
	fwrite(cityascription, sizeof(int), MAPWIDTH*MAPHEIGHT, fp);
	fwrite(gamesupplypoint, sizeof(int), MAPWIDTH*MAPHEIGHT, fp);
	fwrite(map, sizeof(MAP), MAPWIDTH * MAPHEIGHT, fp);
	fclose(fp);
}

void ReadGame()
{
	FILE* fp = fopen(arrgamereadname, "rb");
	if (fp == NULL) fp = fopen("Game/game.star", "rb");
	fread(&phase, sizeof(int), 1, fp);
	fread(&gameyear, sizeof(int), 1, fp);
	fread(&gamemon, sizeof(int), 1, fp);
	fread(&axismanpower, sizeof(int), 1, fp);
	fread(&axisindustry, sizeof(int), 1, fp);
	fread(&rommanpower, sizeof(int), 1, fp);
	fread(&romindustry, sizeof(int), 1, fp);
	fread(&ussrmanpower, sizeof(int), 1, fp);
	fread(&ussrindustry, sizeof(int), 1, fp);
	fread(cityascription, sizeof(int), MAPWIDTH * MAPHEIGHT, fp);
	fread(gamesupplypoint, sizeof(int), MAPWIDTH * MAPHEIGHT, fp);
	fread(map, sizeof(MAP), MAPWIDTH * MAPHEIGHT, fp);
	fclose(fp);
}

//游戏回合阶段
void GamePhase(int number)
{
	//The Soviet Union advocated attack, so it attacked first and then moved
	NEWPOINT beta = HexagonTransitionPoint(MOUSEX - mapx, MOUSEY - mapy, HEXAGONR);
	switch (number % 8)
	{
		//单位准备
	case 0: UnitReinforce(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], 2, &axismanpower, &axisindustry, &rommanpower, &romindustry); break;
	case 1: 
		UnitReinforce(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], 1, &ussrmanpower, &ussrindustry, &rommanpower, &romindustry); 
		if (phase == 1)
		{
			GamePhaseTransform(2, 2, beta);
			UnitMove(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], &map[beta.x * MAPHEIGHT + beta.y]);
		}
		break;
	case 2:GamePhaseTransform(2, 1, beta); break;
	case 3:
		GamePhaseTransform(2, 2, beta);
		if (map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y].unit[0].sid == 2)
			UnitMove(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], &map[beta.x * MAPHEIGHT + beta.y]);
		break;
	case 4:
		GamePhaseTransform(1, 2, beta);
		if (map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y].unit[0].sid == 1)
			UnitMove(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], &map[beta.x * MAPHEIGHT + beta.y]);
		break;
	case 5:GamePhaseTransform(1, 1, beta); break;
	case 6:
		for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
			for (int o = 0; o < 5; o++)
				map[i].unit[o].battleemblem = FALSE;
		break;
	case 7:
		if (map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y].unit[0].sid == 2)
			UnitMove(&map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], &map[beta.x * MAPHEIGHT + beta.y]);
		break;
	}
}
void GamePhaseA(HDC hdc)
{
	BoxC(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 55, PARENTWINDOWWIDTH, 40, 0xeaeaea);
	switch (phase % 8)
	{
	case 0:		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"德国", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"增援", 0xba7bd7);		break;
	case 1:
	if(phase==1) { Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"德国", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"袭击", 0xba7bd7); }
	else { Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"苏联", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"增援", 0xba7bd7); }
		break;
	case 2:		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"轴心国", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"移动", 0xba7bd7);		break;
	case 3:		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"轴心国", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"进攻", 0xba7bd7);		break;
	case 4:		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"苏联", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"进攻", 0xba7bd7);		break;
	case 5:		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"苏联", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"移动", 0xba7bd7);		break;
	case 6:		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"判断", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"补给", 0xba7bd7);		break;
	case 7:		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 60, L"轴心国", 0);		Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 80, L"装甲轮", 0xba7bd7);		break;
	}
	Dight(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 100, phase % 8 + 1, 0);
	BoxC(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 10, PARENTWINDOWWIDTH, 40, 0xaaaaaa);
	Text(0, hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 10, L"裁决表:", 0);
	if (arrcombatjudgmenttableout != Error)
		switch (arrcombatjudgmenttableout)
		{
		case 0x1a:  Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"1A", 0x006400); break;
		case 0x0e:  Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"EX", 0x006400); break;
		case 0xd1:  Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"D1", 0x006400); break;
		case 0xd2:  Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"D2", 0x006400); break;
		case 0x1d1: Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"1D1", 0x006400); break;
		case 0x1d2: Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"1D2", 0x006400); break;
		case 0x2d2: Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"2D2", 0x006400); break;
		case 0x3d2: Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"3D2", 0x006400); break;
		}
	else Text(0, hdc, 0 + 25, 5 * (PARENTWINDOWWIDTH + 5) + 25, L"NO", 0x0000ff);
	BoxC(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 5), PARENTWINDOWWIDTH, 40, 0xcccccc);
	Text(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 5), L"年:", 0);
	Text(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"月:", 0);
	switch (gamemon)
	{
	case 1: Text(0, hdc, 18, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"1~3", 0x775ba4); break;
	case 2: Text(0, hdc, 18, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"4~5", 0x775ba4); break;
	case 3: Text(0, hdc, 18, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"6", 0x775ba4); break;
	case 4: Text(0, hdc, 18, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"7", 0x775ba4); break;
	case 5: Text(0, hdc, 18, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"8", 0x775ba4); break;
	case 6: Text(0, hdc, 18, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"9", 0x775ba4); break;
	case 7: Text(0, hdc, 18, 7 * (PARENTWINDOWWIDTH + 5) + 20, L"10~12", 0x775ba4); break;
	}
	Dight(0, hdc, 20, 7 * (PARENTWINDOWWIDTH + 5), gameyear, 0x3d4f6e);
	BoxC(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 10), PARENTWINDOWWIDTH, 20, 0xeeeeee);
	Line(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 10) + 20, PARENTWINDOWWIDTH, 7 * (PARENTWINDOWWIDTH + 10) + 20, 0);
	Line(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 10) + 20 * 11, PARENTWINDOWWIDTH, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 11, 0);
	switch (map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y].terrain)
	{
	case 'l':Text(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 10), L"平原", 0); break;
	case 'm':Text(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 10), L"山地", 0x3b568f); break;
	case 'o':Text(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 10), L"海洋", 0xc05c4a); break;
	case 't':Text(0, hdc, 0, 7 * (PARENTWINDOWWIDTH + 10), L"森林", 0x00823f); break;
	}
}

//Read Game/map.txt
void ReadMap()
{
	/*
	o ocean
	l land
	t tree
	m mountain
	r river		Rivers are not formal topography, but boundary properties
	*/
	FILE* fp = fopen("Game/map.txt", "r");
	if (fp == NULL) { printf("[No map]\n"); return; }
	char arrterrain[34];
	for (int o = 0; o < MAPWIDTH; o++)
	{
		FILEFP(fp, o);
		fgets(arrterrain, 33, fp);
		for (int i = 0; i < MAPHEIGHT; i++) map[o * MAPHEIGHT + i].terrain = arrterrain[i];
	}
	fclose(fp);
}

const char* stardoorscript[] =
{
	"EXIT",		//0
	"BOUNDARY",	//1
	"TERRAIN",	//2
	"TRAIN",	//3
	"RAGION",	//4 city and ragionname
	"UNIT",		//5
	"TIME",		//6
	"READGAME",	//7
	"OUTGAME",	//8
	"SUPPLY",	//9
};

void ScriptCoord(FILE* fp, int* x, int* y, char* arr[])
{
	fscanf(fp, "%29s", arr);
	*x = atoi(arr);
	fscanf(fp, "%29s", arr);
	*y = atoi(arr);
}

void RunScript()
{
	FILE* fp = fopen("Game/Script.txt", "r");
	int fpline = 0;
	if (fp == NULL) { printf("[Error][No Script]\n"); return; }
	char arrcommandtext[30] = { 0 };
	int alpha = 0;
	do
	{
		if (alpha++ > 100000)break;
		int number[5] = { 0 };
		char text;
		fscanf(fp, "%29s", arrcommandtext);
		switchlogic(arrcommandtext)
			caselogic(!strcmp(arrcommandtext, stardoorscript[0])) break;
		caselogic(!strcmp(arrcommandtext, stardoorscript[1]))
		{
			ScriptCoord(fp, &number[0], &number[1], arrcommandtext);	//坐标
			fscanf(fp, "%29s", arrcommandtext);
			number[2] = atoi(arrcommandtext);
			fscanf(fp, "%c", &text);
			fscanf(fp, "%c", &text);
			map[max((number[0] * MAPHEIGHT + number[1]) % (MAPWIDTH * MAPHEIGHT), 0)].Boundary[max(number[2] % 6, 0)] = text;
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[2]))
		{
			ScriptCoord(fp, &number[0], &number[1], arrcommandtext);	//坐标
			fscanf(fp, "%c", &text);
			fscanf(fp, "%c", &text);
			map[max((number[0] * MAPHEIGHT + number[1]) % (MAPWIDTH * MAPHEIGHT), 0)].terrain = text;
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[3]))
		{
			ScriptCoord(fp, &number[0], &number[1], arrcommandtext);	//坐标
			fscanf(fp, "%29s", arrcommandtext);
			number[2] = atoi(arrcommandtext);
			map[max((number[0] * MAPHEIGHT + number[1]) % (MAPWIDTH * MAPHEIGHT), 0)].traintracks[number[2]] = TRUE;
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[4]))
		{
			ScriptCoord(fp, &number[0], &number[1], arrcommandtext);	//坐标
			fscanf(fp, "%29s", arrcommandtext);
			number[2] = atoi(arrcommandtext);
			fscanf(fp, "%29s", arrcommandtext);
			map[max((number[0] * MAPHEIGHT + number[1]) % (MAPWIDTH * MAPHEIGHT), 0)].citysid = number[2];
			strcpy(map[max((number[0] * MAPHEIGHT + number[1]) % (MAPWIDTH * MAPHEIGHT), 0)].ragionname, arrcommandtext);
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[5]))
		{
			ScriptCoord(fp, &number[0], &number[1], arrcommandtext);	//坐标
			fscanf(fp, "%29s", arrcommandtext);
			number[2] = atoi(arrcommandtext);
			fscanf(fp, "%29s", arrcommandtext);
			number[3] = atoi(arrcommandtext);
			fscanf(fp, "%29s", arrcommandtext);
			number[4] = atoi(arrcommandtext);
			InitialisationUnit(&map[max((number[0] * MAPHEIGHT + number[1]) % (MAPWIDTH * MAPHEIGHT), 0)].unit[number[2] % 5], number[3] % 11, number[4]);
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[6]))
		{
			ScriptCoord(fp, &number[0], &number[1], arrcommandtext);	//时间
			gameyear = number[0];
			gamemon = number[1] % 12 + 1;
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[7]))
		{
			fscanf(fp, "%29s", arrgamereadname);
			ReadGame();
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[8]))
		{
			fscanf(fp, "%29s", arrgameoutname);
		}
		caselogic(!strcmp(arrcommandtext, stardoorscript[9]))
		{
			ScriptCoord(fp, &number[0], &number[1], arrcommandtext);
			fscanf(fp, "%29s", arrcommandtext);
			number[2] = atoi(arrcommandtext);
			gamesupplypoint[max((number[0] * MAPHEIGHT + number[1]) % (MAPWIDTH * MAPHEIGHT), 0)] = number[2];
		}
		fpline++;
		FILEFP(fp, fpline);
	} while (1);
	fclose(fp);
}

//游戏开始设置
void GameStartSetting()
{
	BoxC(0, unitimg.hdc, 0, 0, MAPIMGWIDTH, MAPIMGHEIGHT, RGB(1, 1, 1));
	ReadMap();
	int gamemode = FALSE, gameok = FALSE;
	FILE* fp = fopen("Game/setting.star", "rb");
	fread(&GAMEPOWER, sizeof(int), 1, fp);
	fread(&gamemode, sizeof(int), 1, fp);
	fread(&gameok, sizeof(int), 1, fp);
	fclose(fp);
	if (gameok == FALSE) { MessageBox(0, L"您必须从合法的启动器启动", L"Waring", MB_OK | MB_ICONERROR); exit(0); }
	if (gamemode == 1) RunScript();
	else if (gamemode == 2) { strcpy(arrgamereadname, arrgameoutname); ReadGame(); }
	HexagonConversion();
	HexagonMapDrawing(mapimg.hdc, HEXAGONR);
	BoxB(0, unitimg.hdc, 0, 0, PARENTWINDOWWIDTH, WINDOWHEIGHT, 0xeeeeee);
	for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
	{
		for (int o = 0; o < 5; o++)UnitReset(&(map[i].unit[o]), 1);
		if (map[i].unit[0].sid == 1)
			for (int o = 0; o < 5; o++) UnitReset(&map[i].unit[o], 2);
		cityascription[i] = map[i].citysid;
		if (map[i].citysid == 1)mapussrcitynumber += 1;
		else if (map[i].citysid == 2)mapaxiscitynumber += 1;
		if (phase == 1) for (int o = 0; o < 5; o++) UnitReset(&map[i].unit[o], 2);
	}
}

void main()
{
	srand(0);
	GAME Game;
	InitialisationGame(&Game, L"1941 The Eastern Front Parent", -1, -1, WINDOWWIDTH + 17 + PARENTWINDOWWIDTH, WINDOWHEIGHT + 39, 100, 0, 0, 1);

	//取消全屏按钮
	LONG style = GetWindowLong(Game.Windowhwnd, GWL_STYLE);// 去除全屏按钮
	style &= ~WS_MAXIMIZEBOX;// 应用修改后的样式
	SetWindowLong(Game.Windowhwnd, GWL_STYLE, style);// 刷新窗口以应用新的样式
	SetWindowPos(Game.Windowhwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

	mapimg.hdc = DoubleBuffer(Game.Windowhwnd, mapimg.hBitmap, MAPIMGWIDTH, MAPIMGHEIGHT);
	unitimg.hdc = DoubleBuffer(Game.Windowhwnd, unitimg.hBitmap, PARENTWINDOWWIDTH, WINDOWHEIGHT);
	GameStartSetting();
	srand(time(0));
	GameLoop(&Game, 1);
	DeletBuffer(mapimg.hBitmap, mapimg.hdc);
	DeletBuffer(unitimg.hBitmap, unitimg.hdc);
	GameOut();
	if(ussrvictory)MessageBox(Game.Windowhwnd, L"经历了长达数年残忍的,难以想象的,旷日持久的的战争\n红军以巨大的牺牲逆转战局，一路反攻至柏林\n[苏维埃社会主义共和国联盟]彻底击败了[轴心国家联合]", L"USSR WIN", MB_OK);
	if(axisvictory)MessageBox(Game.Windowhwnd, L"自巴巴罗萨开始的偷袭,在伤亡几十上百万人之后,取得了俄罗斯战役的胜利\n[德意志第三帝国]彻底击败了[苏维埃社会主义共和国联盟]", L"AXIS WIN", MB_OK);
	int gamemode = FALSE, gameok = FALSE;
	FILE* fp = fopen("Game/setting.star", "wb");
	fwrite(&GAMEPOWER, sizeof(int), 1, fp);
	fwrite(&gamemode, sizeof(int), 1, fp);
	fwrite(&gameok, sizeof(int), 1, fp);
	fclose(fp);
	GameOver(&Game, 0);
	RunProgram(L"1941 The Eastern Front launcher.exe");
}

void GameLogic(GAME* Game)
{
	if (!GAMEPOWER)Sleep(1);
	if (KeyState(VK_F1))unitselect[0] = !unitselect[0];
	if (KeyState(VK_F2))unitselect[1] = !unitselect[1];
	if (KeyState(VK_F3))unitselect[2] = !unitselect[2];
	if (KeyState(VK_F4))unitselect[3] = !unitselect[3];
	if (KeyState(VK_F5))unitselect[4] = !unitselect[4]; 
	if (KeyState(VK_SPACE))
	{
		phase++;
		switch (phase % 8)
		{
		case 0:
		case 1:
		{
			int axiscitynumber = 0, ussrcitynumber = 0;
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
			{
				ussrcitynumber += (cityascription[i] == 1 ? 1 : 0);
				axiscitynumber += (cityascription[i] == 2 ? 1 : 0);
				int x = i / MAPHEIGHT, y = i % MAPHEIGHT;
				if (map[i].terrain == 'o') Pix(0, unitimg.hdc, x, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 11 + 5 + y, 0xff0000);
				else if (map[i].terrain == 'l') Pix(0, unitimg.hdc, x, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 11 + 5 + y, 0xffffff);
				else if (map[i].terrain == 't') Pix(0, unitimg.hdc, x, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 11 + 5 + y, 0x00ff00);
				else if (map[i].terrain == 'm') Pix(0, unitimg.hdc, x, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 11 + 5 + y, 0x22aaeb);
				if (map[i].unit[0].sid == 2) Pix(0, unitimg.hdc, x, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 11 + 5 + y, 0);
				else if (map[i].unit[0].sid == 1) Pix(0, unitimg.hdc, x, (7 * (PARENTWINDOWWIDTH + 10)) + 20 * 11 + 5 + y, 0x0000ff);
			}
			if (axiscitynumber == 0) { ussrvictory = TRUE; GAMEDEAD = TRUE; }
			else if (ussrcitynumber < mapussrcitynumber * .25) { axisvictory = TRUE; GAMEDEAD = TRUE; }
		}
			gamemon = gamemon % 8 + 1;
			rommanpower = 1;
			ussrmanpower = 21;
			axismanpower = 9;
			if (gamemon == 1) { ussrindustry = 56; axisindustry = 24; romindustry = 1; gameyear++; }
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
			{
				if (map[i].citysid > 0 && map[i].unit[0].people > 0)cityascription[i] = map[i].unit[0].sid;
				if (map[i].unit[0].sid == 2) for (int o = 0; o < 5; o++) UnitReset(&(map[i].unit[o]), 1);
			}
			break;
		case 3:
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
				if (map[i].unit[0].people > 0)
					for (int o = 0; o < 5; o++)
						UnitReset(&map[i].unit[o], 2);
			break;
		case 5:
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
				if (map[i].unit[0].sid == 1)
					for (int o = 0; o < 5; o++)
						UnitReset(&map[i].unit[o], 1);
			break;
		case 6:
		{
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
			{
				map[i].AXISReplenish = FALSE;
				map[i].USSRReplenish = FALSE;
			}
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
			{
				if (map[i].unit[0].people > 0)
					for (int o = 0; o < 5; o++)
					{
						map[i].unit[o].supply -= 1;
						map[i].unit[o].supply = max(map[i].unit[o].supply, 0);
					}
			}
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
				if (gamesupplypoint[i] > 0)
				{
					printf("ok\n");
					GameSupply(&map[i], gamesupplypoint[i], 30);
					UnitSupply(gamesupplypoint[i]);
				}
		}
		break;
		case 7:
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
				if (map[i].unit[0].sid == 2)
					for (int o = 0; o < 5; o++)
						if (map[i].unit[o].unit == TANK || map[i].unit[o].unit == MECHINF) map[i].unit[o].Mobility = 4;
						else map[i].unit[o].Mobility = 0;
			break;
		}
		if (phase == 2)
			for (int i = 0; i < MAPWIDTH * MAPHEIGHT; i++)
				for (int o = 0; o < 5; o++)
				{
					map[i].unit[o].battleemblem = FALSE;
					UnitReset(&map[i].unit[o], 1);
				}
		GamePhase(phase);
		BoxC(0, unitimg.hdc, 0, 5 * (PARENTWINDOWWIDTH + 5) + 100, PARENTWINDOWWIDTH, 18, 0xeeeeee);
		hexagonpointA.x = 0;
		hexagonpointA.y = 0;
	}
	if (KeyState(VK_DOWN))mapy = WINDOWHEIGHT - MAPIMGHEIGHT;
	if (KeyState(VK_UP))mapy = 0;
	if (KeyState(1))
	{
		if (MOUSEX >= 0 && MOUSEX < WINDOWWIDTH && MOUSEY >= 0 && MOUSEY < WINDOWHEIGHT)
		{
			NEWPOINT alpha = HexagonTransitionPoint(MOUSEX - mapx, MOUSEY - mapy, HEXAGONR);
			alpha.x = RANGE(alpha.x, 0, 32);
			alpha.y = RANGE(alpha.y, 0, 22);
			mousebufferpoint[0] = HexagonTurningPoint(alpha.x, alpha.y, HEXAGONR).x;
			mousebufferpoint[1] = HexagonTurningPoint(alpha.x, alpha.y, HEXAGONR).y;
			hexagonpointA = HexagonTransitionPoint(mousebufferpoint[0], mousebufferpoint[1], HEXAGONR);
			UnitCommandDrawing(map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], unitimg.hdc);
			if (map[alpha.x * MAPHEIGHT + alpha.y].unit[0].people > 0)unitselect[0] = TRUE;
			if (!map[alpha.x * MAPHEIGHT + alpha.y].unit[0].unit || map[alpha.x * MAPHEIGHT + alpha.y].unit[0].people <= 0)
				for (int i = 0; i < 5; i++)unitselect[i] = 0;
		}
		else if (MOUSEX >= WINDOWWIDTH && MOUSEX < WINDOWWIDTH + 17 + PARENTWINDOWWIDTH && MOUSEY >= 0 && MOUSEY < WINDOWHEIGHT)
		{
			UnitChoose(TRUE);
			UnitCommandDrawing(map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], unitimg.hdc);
		}
	}
	if (KeyState(2))
	{
		if (MOUSEX >= 0 && MOUSEX < WINDOWWIDTH && MOUSEY >= 0 && MOUSEY < WINDOWHEIGHT)
		{
			GamePhase(phase);
			mousebufferpoint[0] = -1; mousebufferpoint[1] = -1;
		}
		else if (MOUSEX >= WINDOWWIDTH && MOUSEX < WINDOWWIDTH + 17 + PARENTWINDOWWIDTH && MOUSEY >= 0 && MOUSEY < WINDOWHEIGHT)
		{
			if (phase % 8 == 0 || phase % 8 == 1)GamePhase(phase);
			UnitChoose(FALSE);
			UnitCommandDrawing(map[hexagonpointA.x * MAPHEIGHT + hexagonpointA.y], unitimg.hdc);
		}
	}
}

void GameDrawing(GAME* Game)
{
	BitBlt(Game->doublebuffer.hdc, mapx, mapy, MAPIMGWIDTH, MAPIMGHEIGHT, mapimg.hdc, 0, 0, SRCCOPY);
	BitBlt(Game->doublebuffer.hdc, MAPIMGWIDTH, 0, PARENTWINDOWWIDTH, MAPIMGHEIGHT, unitimg.hdc, 0, 0, SRCCOPY);
	if (!(mousebufferpoint[0] < 0 || mousebufferpoint[1] < 0))Hexagon(Game->doublebuffer.hdc, HEXAGONR - 2, mousebufferpoint[0] + mapx, mousebufferpoint[1] + mapy, 3, 0x006400);
	UnitMapDrawing(Game->doublebuffer.hdc);
	UnitReinforceA(unitimg.hdc);
	GamePhaseA(unitimg.hdc);
	NewDIGHT(Game, hexagonpointA.x, 0, 20, 0);
	NewDIGHT(Game, hexagonpointA.y, 0, 40, 0);

}
