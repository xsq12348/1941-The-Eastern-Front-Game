//If the code comments are garbled, ignore them!
/*
����:xsq1234
����:1993346266@qq.com(����),c6668883535357a@163.com(������)
�汾��Ϣ
0.1 ���������Ļ������
0.11 �޸��˲���BUG
0.12 �޸��˲���BUG
0.13 �Ż��˻�������
0.2 ����˶���ģ��
0.21 �޸��˳�ʼ����Ϸ�Ĵ���bug
0.22 ������NPC�ṹ��
0.23 �����˶�����Դ�ؼ���
0.23 ���¿�ʼдnpcģ��
0.24 npc�ṹ���ѱ��ĳ�ENTITY�ṹ��
0.3 �����˶��߳�
0.4 ��ͼ������ֲ�ɹ�
0.5 ��д�˰�ť�ؼ�
0.51 �޸���MOUSE��
0.6 �޸�����Ⱦ�߼�
0.61 �������޸Ĵ�������
0.7 ��������Ե��߳��޷��رյ�BUG
0.71 �Ż������˲�������
0.72 ���������ܿ���
0.73 �Ż��˻����߼�
0.8 �����˰������
0.9 �Ż���֡����������
0.91 ���ڽ��ԭ����Ϸ����رմ��ں���Ϸ��Ȼ�����е�BUG(��Ϣѭ��)
1.0 �����ԭ����Ϸ����رմ��ں���Ϸ��Ȼ�����е�BUG
1.01 �����˲��ִ���
1.02 �޸��˲���BUG
1.1 ����˼�����
1.2 cpp��ֲ�ɹ�,����cpp�Ͷ�����ͬʱʹ�ø�����
1.3 �����OpenCL֧��
*/
#pragma once
#undef STARDLC
#include"star.h"
#if STARTOpenCL
#include<CL/opencl.h>
#pragma comment(lib,"OpenCL.lib")
#endif

#define VK_0 48
#define VK_1 49
#define VK_2 50
#define VK_3 51
#define VK_4 52
#define VK_5 53
#define VK_6 54
#define VK_7 55
#define VK_8 56
#define VK_9 57

#define VK_A 65
#define VK_B 66
#define VK_C 67
#define VK_D 68
#define VK_E 69
#define VK_F 70
#define VK_G 71
#define VK_H 72
#define VK_I 73
#define VK_J 74
#define VK_K 75
#define VK_L 76
#define VK_M 77
#define VK_N 78
#define VK_O 79
#define VK_P 80
#define VK_Q 81
#define VK_R 82
#define VK_S 83
#define VK_T 84
#define VK_U 85
#define VK_V 86
#define VK_W 87
#define VK_X 88
#define VK_Y 89
#define VK_Z 90

TIMELOAD fps;
int fpsmax = 0,
fpsmax2 = 0;

#define RANDOM(a,b) Random(a,b)
#define DEGRAD(a) DegRad(a)

int GAMEDEAD = 0;				//��Ϸ����
int GAMEINPUT;					//��Ϸ����
int MOUSEX = 0, MOUSEY = 0;
int GAMEPOWER = 0;
typedef LPCWSTR ANIMEIMG;		//������Դ�ؼ���
typedef POINT VELOCITY;			//�ٶȷ����ṹ��

//--------------------------------------------------------------------------------------��Ϸ�ṹ��----------------------------------------------------------------------------------------------------------//

//��Ϸ�ṹ��
typedef struct
{
	LPCWSTR Name;				//��������
	HWND Windowhwnd;			//���ھ��
	HWND Windowchildhwnd;		//�Ӵ��ھ��
	int Windowwidth;			//���ڿ��
	int Windowheight;			//���ڸ߶�
	BOOL CMDswitch;				//CMD����
	DOUBLEBUFFER doublebuffer;	//˫������Ⱦ
	TIMELOAD timeload;			//֡�ʿ���
	BOOL cuesor;				//�����
	BOOL escswitch;				//�Ƿ�����esc
}GAME;

//�����ṹ��
typedef struct
{
	LPCSTR Name;
	LPCWSTR* sequenceframes;	//����֡����
	int number;					//��ǰ����֡
	int totalnumber;			//����֡����
	BOOL animeswitch;			//�����������ſ���
	TIMELOAD timeload;			//��ʱ��
}ANIME;

//ʵ��ṹ��
typedef struct ENTITY
{
	LPCSTR Name;				//����
	POINT coor;					//λ��
	VELOCITY velocity;			//�ٶ�
	int hp;						//Ѫ��
	int sid;					//��Ӫ
	int mode;					//��Ϊģʽ
	BOOL crashboxswitch;		//��ײ�俪��
	struct ENTITY* parent;		//��ʵ��
	struct ENTITY* children;	//��ʵ��
}ENTITY;

typedef struct
{
	POINT coor;
	POINT lengths;
	BOOL buttonswitch;
	BOOL button;
	BOOL triggered;
}BUTTON;

typedef struct
{
	float x;
	float y;
	float z;
}POINT3D;
typedef struct
{
	float x;
	float y;
	float Z;
}POINT2D;
typedef struct
{
	POINT3D camerapoint;
	POINT3D cameravectorx;
	POINT3D cameravectory;
	float cameravectorxmo;
	float cameravectorymo;
	float focalLength;
	float matrixR[3][3];
	float matrix[3][3];
}CAMERA;

//--------------------------------------------------------------------------------------��ͼ����----------------------------------------------------------------------------------------------------------//

void PIX(GAME* Game, int x, int y, COLORREF color) { Pix(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, color); }
void LINE(GAME* Game, int x1, int y1, int x2, int y2, COLORREF color) { Line(Game->Windowhwnd, Game->doublebuffer.hdc, x1, y1, x2, y2, color); }
void APPIX(GAME* Game, int apx, int apy, int x, int y, double rad, COLORREF color) { ApPix(Game->Windowhwnd, Game->doublebuffer.hdc, apx, apy, x, y, rad, color); }
void APLINE(GAME* Game, int apx, int apy, int x1, int y1, int x2, int y2, double rad, COLORREF color) { ApLine(Game->Windowhwnd, Game->doublebuffer.hdc, apx, apy, x1, y1, x2, y2, rad, color); }
void BOX(GAME* Game, int x, int y, int width, int height, COLORREF color) { BoxC(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, width, height, color); }
void BOXA(GAME* Game, int x, int y, int width, int height, COLORREF color)
{
	LINE(Game, x, y, x + width, y, color);
	LINE(Game, x, y, x, y + height, color);
	LINE(Game, x, y + height, x + width, y + height, color);
	LINE(Game, x + width, y, x + width, y + height, color);
}
void CIRCLE(GAME* Game, int R, int x, int y, COLORREF color) { Circle(Game->Windowhwnd, Game->doublebuffer.hdc, R, x, y, color); }

//��ʾͼƬ
void IMG(GAME* Game, const wchar_t* File, int x, int y) { Img(Game->Windowhwnd, Game->doublebuffer.hdc, File, x, y); }
void IMGA(GAME* Game, const wchar_t* File, int x, int y, int widthbs, int heightbs, COLORREF color) { ImgA(Game->Windowhwnd, Game->doublebuffer.hdc, File, x, y, widthbs, heightbs, color); }

//����
void NewTEXT(GAME* Game, LPCWSTR text, int x, int y, COLORREF color) { Text(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, text, color); }
void NewDIGHT(GAME* Game, int number, int x, int y, COLORREF color) { Dight(Game->Windowhwnd, Game->doublebuffer.hdc, x, y, number, color); }

//--------------------------------------------------------------------------------------��Ϸ����----------------------------------------------------------------------------------------------------------//

//��ť�ؼ�

void InitialisationButton(BUTTON* button, int x, int y, int width, int height, int YESORNO)
{
	button->coor.x = x;
	button->coor.y = y;
	button->lengths.x = width;
	button->lengths.y = height;
	button->buttonswitch = YESORNO;
	button->button = 0;
	button->triggered = 0;
}

//����չʾ��ͬ״̬�İ�ť,��ͣʱ��ʾͼƬ2,����ʱ��ʾͼƬ3
int ButtonStart(GAME* Game, BUTTON* button, const wchar_t* File1, const wchar_t* File2, const wchar_t* File3)
{
	button->button = ButtonA(0, Game->doublebuffer.hdc, button->coor.x, button->coor.y, button->lengths.x, button->lengths.y, button->buttonswitch);
	switch (button->button)
	{
	case 0:Img(0, Game->doublebuffer.hdc, File1, button->coor.x, button->coor.y); break;
	case 1:Img(0, Game->doublebuffer.hdc, File3, button->coor.x, button->coor.y); break;
	case 2:Img(0, Game->doublebuffer.hdc, File2, button->coor.x, button->coor.y); break;
	}
	return button->button;
}

//�°�ť
int NewButton(GAME* Game, BUTTON* button)
{
	if (button->triggered) { button->button = 0; button->triggered = 1; }
	else if (GetAsyncKeyState(1))
	{
		if (MOUSEX > button->coor.x && MOUSEX  < button->coor.x + button->lengths.x && MOUSEY  > button->coor.y && MOUSEY < button->coor.y + button->lengths.y)
		{
			button->button = 1;
			button->triggered = 1;
		}
	}
	if (!GetAsyncKeyState(1))button->triggered = 0;
	if (button->buttonswitch)if (button->button)BOXA(Game, button->coor.x, button->coor.y, button->lengths.x, button->lengths.y, RGB(255, 0, 0));
	else BOXA(Game, button->coor.x, button->coor.y, button->lengths.x, button->lengths.y, RGB(255, 255, 255));
	return button->button;
}

//�������
int KEYSTATEbuffer[255];
int KeyState(int Key)
{
	int state = GetAsyncKeyState(Key);
	if (state & 0x8000)
	{
		if (KEYSTATEbuffer[Key] == 0) { KEYSTATEbuffer[Key] = 1; return 1; }
		return 0;
	}
	else { KEYSTATEbuffer[Key] = 0; return 0; }
}

//�����ؼ�

//��ʼ������
int InitialisationAnime(ANIME* anime, LPCSTR name, ANIMEIMG* sequenceframes[], int load, int totalnumber)
{
	anime->Name = name;
	Color(0x07);
	if (totalnumber <= 0) { printf("[InitialisationAnime��������]��������֡����������,������Ϊ[%s]�Ķ���!\n", name); return Error; }
	if (sequenceframes == NULL) { printf("[InitialisationAnime��������]��������֡������,������Ϊ[%s]�Ķ����Ƿ����!\n", name); return Error; }
	anime->animeswitch = 0;
	anime->sequenceframes = *sequenceframes;
	anime->totalnumber = totalnumber;
	anime->number = 0;
	SetTimeLoad(&(anime->timeload), load);		//���ö�ʱ��
	return YES;
}

//���ж���
int RunAnime(GAME* Game, ANIME* anime, int animeswitch, int x, int y)
{
	if (!animeswitch)return 0;
	else ImgA(0, Game->doublebuffer.hdc, anime->sequenceframes[anime->number % anime->totalnumber], x, y, 1, 1, RGB(1, 1, 1));
	if (TimeLoad(&(anime->timeload), 1)) ++anime->number;	//�����һ֡	
	return anime->number;
}

//������

typedef struct
{
	DOUBLEPOINT coor;
	DOUBLEPOINT vectory;
	int R;
	double mass;
}CIRCLEPHYSICS;
GAME Game;
CIRCLEPHYSICS circle[3];

void CirclePhysics(CIRCLEPHYSICS* a, CIRCLEPHYSICS* b)
{
	int R = a->R + b->R;
	int L = sqrt(pow(a->coor.x - b->coor.x, 2) + pow(a->coor.y - b->coor.y, 2));
	if ((L <= R))
	{
		double mass = a->mass + b->mass;
		double vectory[4];
		double vectorybuffer[2];
		DOUBLEPOINT vector[2];
		vector[0].x = (a->coor.x - b->coor.x) * 1. / L;
		vector[0].y = (a->coor.y - b->coor.y) * 1. / L;
		vector[1].x = (b->coor.x - a->coor.x) * 1. / L;
		vector[1].y = (b->coor.y - a->coor.y) * 1. / L;
		vectory[0] = sqrt(pow(a->vectory.x, 2) + pow(a->vectory.y, 2));
		vectory[1] = sqrt(pow(b->vectory.x, 2) + pow(b->vectory.y, 2));
		vectory[2] = ((a->mass - b->mass) * vectory[0] + 2 * b->mass * vectory[1]) / mass;
		vectory[3] = ((b->mass - a->mass) * vectory[1] + 2 * a->mass * vectory[0]) / mass;
		a->coor.x += vector[0].x * (R - L) / 2.;
		a->coor.y += vector[0].y * (R - L) / 2.;
		b->coor.x += vector[1].x * (R - L) / 2.;
		b->coor.y += vector[1].y * (R - L) / 2.;
		vectorybuffer[0] = a->vectory.x * vector[1].x + a->vectory.y * vector[1].y;
		vectorybuffer[1] = b->vectory.x * vector[0].x + b->vectory.y * vector[0].y;
		a->vectory.x -= vector[1].x * vectorybuffer[0];
		a->vectory.y -= vector[1].y * vectorybuffer[0];
		b->vectory.x -= vector[0].x * vectorybuffer[1];
		b->vectory.y -= vector[0].y * vectorybuffer[1];
		a->vectory.x += vector[0].x * vectory[2];
		a->vectory.y += vector[0].y * vectory[2];
		b->vectory.x += vector[1].x * vectory[3];
		b->vectory.y += vector[1].y * vectory[3];
	}
	a->coor.x += a->vectory.x;
	a->coor.y += a->vectory.y;
	b->coor.x += b->vectory.x;
	b->coor.y += b->vectory.y;
}

void InitialisationCircle(CIRCLEPHYSICS* circle, int x, int y, double m, double vx, double vy, int R)
{
	circle->coor.x = x;
	circle->coor.y = y;
	circle->vectory.x = vx;
	circle->vectory.y = vy;
	circle->R = R;
	circle->mass = m;
}

//-----------------------------------------------------------------------------------------3D-------------------------------------------------------------------------------------------------------------//
void CameraMatrix(CAMERA* camera, double Rx, double Ry, double Rz)
{

	/*
	The results of the math software calculations
	>> Announcement : Welcome to math procedure
	>> Read "matrix.txt"
	>> Var matrixR  = "matrix.txt"->A
	>> Var matrixRy = "matrix.txt"->B
	>> Var matrixRz = "matrix.txt"->C
	>> Var matrixRx = "matrix.txt"->D
	>> Var matrixRc
	>> JudgmentLogic matrixR
	>> No Logic
	>> Var rx="matrix.txt"->rx
	>> Var ry="matrix.txt"->ry
	>> Var rz="matrix.txt"->rz
	>> matrixRc = matrixRy * matrixRx
	>> Print Var matrixRc Standard
	>> matrixRc :
	{
		 cos(ry), sin(ry) * sin(rx), sin(ry) * cos(rx);
			   0,			cos(rx),		  -sin(rx);
		-sin(ry), cos(ry) * sin(rx), cos(ry) * cos(rx);
	}
	>> matrixR = matrixRc * matrixRz
	>> Print Var matrixR Standard
	>> matrixR :
	{
		 cos(ry) * cos(rz)+ sin(ry) * sin(rx) * sin(rz),cos(ry) * -sin(rz)+ sin(ry) * sin(rx) * cos(rz),sin(ry) * cos(rx);
									  cos(rx) * sin(rz),							  cos(rx) * cos(rz),		 -sin(rx);
		-sin(ry) * cos(rz)+ cos(ry) * sin(rx) * sin(rz),sin(ry) * sin(rz) + cos(ry) * sin(rx) * cos(rz),cos(ry) * cos(rx);
	}
	>> Write matrixR to "matrix.txt"->A
	>> Exit
	>> Announcement : Byebye

x and y are the spatial orientation vectors of the camera
Z vectors can be calculated by fork multiplication
	From the x and y directions of the camera, you can define a two-dimensional tensor space that opens up in space, and according to the following matrix transformation,
you can get an orthogonal projection, and then you can get the perspective effect by perspective division, although it is more troublesome than a homogeneous matrix, but it is easier to understand and write code

		matrixA =
		|x.x, y.x|
		|x.y, y.y|
		|x.z, y.z|

		matrixB =
		|x.x, x.y, x.z|
		|y.x, y.y, y.z|

		matrixC =(matrixB * matrixA)^-1

		(matrixB * matrixA)^-1 =
		|y.x * y.x + y.y * y.y + y.z * y.z, -(x.x * y.x + x.y * y.y + x.z * y.z)|
		|-(x.x * y.x + x.y * y.y + x.z * y.z), x.x * x.x + x.y * x.y + x.z * x.z|
		matrix = matrixA * (matrixB * matrixA)^-1 * matrixB

		p = matrix * a

	double matrixA[2][3] =
	{
		{ x.x, x.y, x.z},
		{ y.x, y.y, y.z}
	};

	double matrixB[3][2] =
	{
		{ x.x, y.x},
		{ x.y, y.y},
		{ x.z, y.z}
	};
	*/

	double
		rx = DegRad(Rx),
		ry = DegRad(Ry),
		rz = DegRad(Rz);
	double matrixR[3][3];

	matrixR[0][0] = cos(ry) * cos(rz) + sin(ry) * sin(rx) * sin(rz);
	matrixR[0][1] = -cos(ry) * sin(rz) + sin(ry) * sin(rx) * cos(rz);
	matrixR[0][2] = sin(ry) * cos(rx);
	matrixR[1][0] = cos(rx) * sin(rz);
	matrixR[1][1] = cos(rx) * cos(rz);
	matrixR[1][2] = -sin(rx);
	matrixR[2][0] = -sin(ry) * cos(rz) + cos(ry) * sin(rx) * sin(rz);
	matrixR[2][1] = sin(ry) * sin(rz) + cos(ry) * sin(rx) * cos(rz);
	matrixR[2][2] = cos(ry) * cos(rx);

	double
		buffera = camera->cameravectorx.x * camera->cameravectorx.x + camera->cameravectorx.y * camera->cameravectorx.y + camera->cameravectorx.z * camera->cameravectorx.z,
		bufferb = camera->cameravectory.x * camera->cameravectory.x + camera->cameravectory.y * camera->cameravectory.y + camera->cameravectory.z * camera->cameravectory.z,
		bufferc = -(camera->cameravectorx.x * camera->cameravectory.x + camera->cameravectorx.y * camera->cameravectory.y + camera->cameravectorx.z * camera->cameravectory.z);
	double matrix[3][3];
	matrix[0][0] = (camera->cameravectorx.x * bufferb + camera->cameravectory.x * bufferc) * camera->cameravectorx.x + (camera->cameravectorx.x * bufferc + camera->cameravectory.x * buffera) * camera->cameravectory.x;
	matrix[1][0] = (camera->cameravectorx.y * bufferb + camera->cameravectory.y * bufferc) * camera->cameravectorx.x + (camera->cameravectorx.y * bufferc + camera->cameravectory.y * buffera) * camera->cameravectory.x;
	matrix[2][0] = (camera->cameravectorx.z * bufferb + camera->cameravectory.z * bufferc) * camera->cameravectorx.x + (camera->cameravectorx.z * bufferc + camera->cameravectory.z * buffera) * camera->cameravectory.x;
	matrix[0][1] = (camera->cameravectorx.x * bufferb + camera->cameravectory.x * bufferc) * camera->cameravectorx.y + (camera->cameravectorx.x * bufferc + camera->cameravectory.x * buffera) * camera->cameravectory.y;
	matrix[1][1] = (camera->cameravectorx.y * bufferb + camera->cameravectory.y * bufferc) * camera->cameravectorx.y + (camera->cameravectorx.y * bufferc + camera->cameravectory.y * buffera) * camera->cameravectory.y;
	matrix[2][1] = (camera->cameravectorx.z * bufferb + camera->cameravectory.z * bufferc) * camera->cameravectorx.y + (camera->cameravectorx.z * bufferc + camera->cameravectory.z * buffera) * camera->cameravectory.y;
	matrix[0][2] = (camera->cameravectorx.x * bufferb + camera->cameravectory.x * bufferc) * camera->cameravectorx.z + (camera->cameravectorx.x * bufferc + camera->cameravectory.x * buffera) * camera->cameravectory.z;
	matrix[1][2] = (camera->cameravectorx.y * bufferb + camera->cameravectory.y * bufferc) * camera->cameravectorx.z + (camera->cameravectorx.y * bufferc + camera->cameravectory.y * buffera) * camera->cameravectory.z;
	matrix[2][2] = (camera->cameravectorx.z * bufferb + camera->cameravectory.z * bufferc) * camera->cameravectorx.z + (camera->cameravectorx.z * bufferc + camera->cameravectory.z * buffera) * camera->cameravectory.z;
	for (int i = 0; i < 3; i++)
		for (int o = 0; o < 3; o++)
		{
			camera->matrixR[o][i] = matrixR[o][i];
			camera->matrix[o][i] = matrix[o][i];
		}

}

void CameraCompute(CAMERA* camera, double Rx, double Ry, double Rz)
{
	CameraMatrix(camera, Rx, Ry, Rz);
	camera->cameravectorx.x = camera->matrixR[0][0] * camera->cameravectorxmo;
	camera->cameravectorx.y = camera->matrixR[1][0] * camera->cameravectorxmo;
	camera->cameravectorx.z = camera->matrixR[2][0] * camera->cameravectorxmo;

	camera->cameravectory.x = camera->matrixR[0][1] * camera->cameravectorymo;
	camera->cameravectory.y = camera->matrixR[1][1] * camera->cameravectorymo;
	camera->cameravectory.z = camera->matrixR[2][1] * camera->cameravectorymo;
}

POINT2D Point3DDrawing(POINT3D point, CAMERA camera, double L, BOOL orthogonal)
{

	POINT3D cameravectory =
	{
			camera.cameravectorx.y * camera.cameravectory.z - camera.cameravectorx.z * camera.cameravectory.y,
			camera.cameravectorx.z * camera.cameravectory.x - camera.cameravectorx.x * camera.cameravectory.z,
			camera.cameravectorx.x * camera.cameravectory.y - camera.cameravectorx.y * camera.cameravectory.x
	};
	POINT3D relativecoordinatespointbuffer =
	{
		-point.x + camera.camerapoint.x,
		-point.y + camera.camerapoint.y,
		-point.z + camera.camerapoint.z,
	};
	double direction = (relativecoordinatespointbuffer.x * cameravectory.x + relativecoordinatespointbuffer.y * cameravectory.y + relativecoordinatespointbuffer.z * cameravectory.z) / (sqrt(cameravectory.x * cameravectory.x + cameravectory.y * cameravectory.y + cameravectory.z * cameravectory.z) * sqrt(relativecoordinatespointbuffer.x * relativecoordinatespointbuffer.x + relativecoordinatespointbuffer.y * relativecoordinatespointbuffer.y + relativecoordinatespointbuffer.z * relativecoordinatespointbuffer.z));
	POINT2D EOR = { Error,Error,Error };
	if (direction >= -L)return EOR;

	POINT3D  relativecoordinatespoint = relativecoordinatespointbuffer;
	relativecoordinatespointbuffer.x = relativecoordinatespoint.x * camera.matrix[0][0] + relativecoordinatespoint.y * camera.matrix[1][0] + relativecoordinatespoint.z * camera.matrix[2][0];
	relativecoordinatespointbuffer.y = relativecoordinatespoint.x * camera.matrix[0][1] + relativecoordinatespoint.y * camera.matrix[1][1] + relativecoordinatespoint.z * camera.matrix[2][1];
	relativecoordinatespointbuffer.z = relativecoordinatespoint.x * camera.matrix[0][2] + relativecoordinatespoint.y * camera.matrix[1][2] + relativecoordinatespoint.z * camera.matrix[2][2];

	POINT2D returnpoint =
	{
		 relativecoordinatespointbuffer.x * camera.cameravectorx.x + relativecoordinatespointbuffer.y * camera.cameravectorx.y + relativecoordinatespointbuffer.z * camera.cameravectorx.z ,
		 relativecoordinatespointbuffer.x * camera.cameravectory.x + relativecoordinatespointbuffer.y * camera.cameravectory.y + relativecoordinatespointbuffer.z * camera.cameravectory.z ,
		 0
	};

	if (!orthogonal)
	{
		double pointmo[2] =
		{
			sqrt(relativecoordinatespointbuffer.x * relativecoordinatespointbuffer.x + relativecoordinatespointbuffer.y * relativecoordinatespointbuffer.y + relativecoordinatespointbuffer.z * relativecoordinatespointbuffer.z),
			sqrt(relativecoordinatespoint.x * relativecoordinatespoint.x + relativecoordinatespoint.y * relativecoordinatespoint.y + relativecoordinatespoint.z * relativecoordinatespoint.z)
		};

		returnpoint.Z = sqrt(pointmo[1] * pointmo[1] - pointmo[0] * pointmo[0]);
		returnpoint.x = returnpoint.x / returnpoint.Z * camera.focalLength;
		returnpoint.y = returnpoint.y / returnpoint.Z * camera.focalLength;
		if (returnpoint.Z > 5000)return EOR;
	}
	else returnpoint.Z = 1;
	return returnpoint;
}
#if STARTOpenCL

cl_platform_id platformid;
cl_device_id deviceid;
cl_context context;
cl_command_queue commandqueue;
cl_program program;
cl_kernel kernel;

char* STAROpenCL3D =
"__kernel void Point3DDrawing(__global float* pointx, __global float* pointy, __global float* pointz, __global float* cameravectorx, __global float* cameravectory, __global float* camerapoint, __global float* cameramatrix, __global float* returnpointx, __global float* returnpointy, __global float* returnpointz,__global float* focalLength)"
"{"
"	int number=get_global_id(0);"
"	float cameravectorZ[3];"
"	cameravectorZ[0] = cameravectorx[1] * cameravectory[2] - cameravectorx[2] * cameravectory[1];"
"	cameravectorZ[1] = cameravectorx[2] * cameravectory[0] - cameravectorx[0] * cameravectory[2];"
"	cameravectorZ[2] = cameravectorx[0] * cameravectory[1] - cameravectorx[1] * cameravectory[0];"
"	float relativecoordinatespointbuffer[3];"
"	relativecoordinatespointbuffer[0] = - pointx[number] + camerapoint[0];"
"	relativecoordinatespointbuffer[1] = - pointy[number] + camerapoint[1];"
"	relativecoordinatespointbuffer[2] = - pointz[number] + camerapoint[2];"
"	float direction = (relativecoordinatespointbuffer[0] * cameravectorZ[0] + relativecoordinatespointbuffer[1] * cameravectorZ[1] + relativecoordinatespointbuffer[2] * cameravectorZ[2]) / (sqrt(cameravectorZ[0] * cameravectorZ[0] + cameravectorZ[1] * cameravectorZ[1] + cameravectorZ[2] * cameravectorZ[2]) * sqrt(relativecoordinatespointbuffer[0] * relativecoordinatespointbuffer[0] + relativecoordinatespointbuffer[1] * relativecoordinatespointbuffer[1] + relativecoordinatespointbuffer[2] * relativecoordinatespointbuffer[2]));"
"	if(direction >= -.1f){returnpointz[number] = -1; return;}"
"	float relativecoordinatespoint[3];"
"	relativecoordinatespoint[0]= relativecoordinatespointbuffer[0];"
"	relativecoordinatespoint[1]= relativecoordinatespointbuffer[1];"
"	relativecoordinatespoint[2]= relativecoordinatespointbuffer[2];"
"	relativecoordinatespointbuffer[0] = relativecoordinatespoint[0] * cameramatrix[0] + relativecoordinatespoint[1] * cameramatrix[1] + relativecoordinatespoint[2] * cameramatrix[2];"
"	relativecoordinatespointbuffer[1] = relativecoordinatespoint[0] * cameramatrix[3] + relativecoordinatespoint[1] * cameramatrix[4] + relativecoordinatespoint[2] * cameramatrix[5];"
"	relativecoordinatespointbuffer[2] = relativecoordinatespoint[0] * cameramatrix[6] + relativecoordinatespoint[1] * cameramatrix[7] + relativecoordinatespoint[2] * cameramatrix[8];"
"	returnpointx[number] = relativecoordinatespointbuffer[0] * cameravectorx[0] + relativecoordinatespointbuffer[1] * cameravectorx[1] + relativecoordinatespointbuffer[2] * cameravectorx[2];"
"	returnpointy[number] = relativecoordinatespointbuffer[0] * cameravectory[0] + relativecoordinatespointbuffer[1] * cameravectory[1] + relativecoordinatespointbuffer[2] * cameravectory[2];"
"	returnpointz[number] = 0;"
"	float pointmo[2];"
"	pointmo[0] = sqrt(relativecoordinatespointbuffer[0] * relativecoordinatespointbuffer[0] + relativecoordinatespointbuffer[1] * relativecoordinatespointbuffer[1] + relativecoordinatespointbuffer[2] * relativecoordinatespointbuffer[2]);"
"	pointmo[1] = sqrt(relativecoordinatespoint[0] * relativecoordinatespoint[0] + relativecoordinatespoint[1] * relativecoordinatespoint[1] + relativecoordinatespoint[2] * relativecoordinatespoint[2]);"
"	returnpointz[number] = sqrt(pointmo[1] * pointmo[1] - pointmo[0] * pointmo[0]);"
"	returnpointx[number] = returnpointx[number] / returnpointz[number] * *focalLength;"
"	returnpointy[number] = returnpointy[number] / returnpointz[number] * *focalLength;"
"	if (returnpointz[number] > 5000){returnpointz[number] = -1;return;}"
"	return;"
"}"
;
#endif
//--------------------------------------------------------------------------------------��Ϸ����----------------------------------------------------------------------------------------------------------//

//��ʼ����Ϸ
void InitialisationGame(GAME* Game, LPCWSTR name, int x, int y, int width, int height, int timeload, int fullscreenmode, BOOL cmdswitch, BOOL cursor)
{
	//��ʼ���ṹ��
	if (y < 0) Game->Windowhwnd = Window((HWND)NULL, name, width, height, (nScreenWidth - width) / 2, (nScreenheight - height) / 2);		//��������	
	else Game->Windowhwnd = Window((HWND)NULL, name, width, height, x, y);
	Game->Name = name;						//��������
	switch (fullscreenmode)					//���ȫ���򲻱�
	{
	case 0:
		Game->Windowwidth = width;		//���ڿ��
		Game->Windowheight = height;	//���ڸ߶�
		break;
	case 1:
		Game->Windowwidth = nScreenWidth;	//���ڿ��
		Game->Windowheight = nScreenheight;	//���ڸ߶�
		TitleBar(Game->Windowhwnd);
		FullScreen(Game->Windowhwnd);
		break;
	case 2:
		Game->Windowwidth = nScreenWidth;	//���ڿ��
		Game->Windowheight = nScreenheight;	//���ڸ߶�
		FullScreen(Game->Windowhwnd);
		break;
	}
	for (int i = 0; i < 255; i++) KEYSTATEbuffer[i] = 0;	
	Game->CMDswitch = cmdswitch;			//�Ƿ���ʾ����̨����
	CMD(cmdswitch);
	Game->doublebuffer.hdc = DoubleBuffer(Game->Windowhwnd, Game->doublebuffer.hBitmap, Game->Windowwidth, Game->Windowheight);	//˫������Ⱦ
	SetTimeLoad(&(Game->timeload), 1000 / timeload);	//��ʼ����ʱ��,����֡�ʿ���
	Mouse(cursor);										//�������ʾ
	Game->escswitch = 0;								//�Ƿ�����esc�˳���Ϸ
	SetTimeLoad(&fps, 1000);
#if STARTOpenCL
	cl_int error;
	clGetPlatformIDs(1, &platformid, NULL);
	clGetDeviceIDs(platformid, CL_DEVICE_TYPE_GPU, 1, &deviceid, NULL);
	context = clCreateContext(NULL, 1, &deviceid, NULL, NULL, NULL);
	commandqueue = clCreateCommandQueue(context, deviceid, NULL, NULL);
	program = clCreateProgramWithSource(context, 1, (const char**)&STAROpenCL3D, NULL, &error);
	clBuildProgram(program, 1, &deviceid, NULL, NULL, NULL);
	kernel = clCreateKernel(program, "Point3DDrawing", NULL);
#endif
}

//��Ϸ�������
void GameDrawing(GAME* Game);

//��Ϸ�߼�����
void GameLogic(GAME* Game);

//�߼��߳�
CREATTHREAD GAMELOGIC;
GAME* GAMETHEARDLOGIC;

//��Ϸ�߼��߳�
THREAD GameThreadLogic(LPARAM lparam)
{
	printf("[star engine logic����ɹ�!]\n");
	while (!GAMEDEAD)
	{
		GameLogic(GAMETHEARDLOGIC);												//��Ϸ�߼�����
		GAMEINPUT = HardwareDetection();										//�������
		MOUSEX = MouseX(GAMETHEARDLOGIC->Windowhwnd);
		MOUSEY = MouseY(GAMETHEARDLOGIC->Windowhwnd);
		if (GAMETHEARDLOGIC->escswitch && GetAsyncKeyState(VK_ESCAPE))GAMEDEAD = 1;	//�Ƿ�����esc�˳���Ϸ
		if (!IsWindow(GAMETHEARDLOGIC->Windowhwnd))GAMEDEAD = 1;//��鴰���Ƿ���
	}
	return 0;
}
//��Ϸѭ��
void GameLoop(GAME* Game, BOOL esc)
{
	GAMEDEAD = 0;
	GAMETHEARDLOGIC = Game;
	Game->escswitch = esc;
	srand((unsigned)time(NULL));
	GetAsyncKeyState(VK_ESCAPE);
	RunThread((THREAD*)GameThreadLogic, GAMELOGIC.ID);
	HDC hdc = GetDC(Game->Windowhwnd);
	HDC hdcchild = GetDC(Game->Windowchildhwnd);
	while (!GAMEDEAD)
	{
		if (!TimeLoad(&fps, 1))fpsmax++;
		else { fpsmax2 = fpsmax; fpsmax = 0; }
		//if (!GAMEPOWER)Sleep(1);
		if (!GAMEPOWER)if(!TimeLoad(&(Game->timeload),1))Sleep(Game->timeload.timeload);
		BoxB(0, Game->doublebuffer.hdc, 0, 0, Game->Windowwidth, Game->Windowheight, RGB(0, 0, 0));		 //���˫������Ļ����
		GameDrawing(Game);
		Text(0, Game->doublebuffer.hdc, 0, 0, L"FPS:", RGB(0, 150, 0));
		NewDIGHT(Game, fpsmax2, 30, 0, RGB(0, 150, 0));
		BitBlt(hdc, 0, 0, Game->Windowwidth, Game->Windowheight, Game->doublebuffer.hdc, 0, 0, SRCCOPY); //ͨ��˫������Ƶ���Ļ��
		ClearWindow();								 //��Ϣѭ��
	}
	printf("[star Game Loop ����!]\n");
}

//��Ϸ����
void GameOver(GAME* Game, BOOL cmdswitch)
{
	printf("[star Game Over����ɹ�!]\n");
	DeletThread(GAMELOGIC.ThreadHwnd);									//�����߼��߳�
	DeletBuffer(Game->doublebuffer.hBitmap, Game->doublebuffer.hdc);	//����˫������Դ
	DeletWindow(Game->Windowhwnd);										//ɾ����Ϸ����
	if (cmdswitch)CMD(ON);												//�Ƿ�����Ϸ����ʱ�ָ�����̨����
#if STARTOpenCL
	clReleaseProgram(program);
	clReleaseDevice(deviceid);
	clReleaseContext(context);
#endif
	printf("��Ϸ��Դ�������!");
}