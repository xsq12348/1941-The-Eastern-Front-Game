//����죬����ʽ��,star��������汾��ʼ��ʽ��������룬������ɼ������⣬����ɼ������⣬���Ʋ�9.11��ʽ�汾

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mmsystem.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include <xkeycheck.h>
#include <commctrl.h> 
#include <gl/GL.h>
#include <gl/GLU.h>

#define ON  1
#define OFF 0
#define YES TRUE
#define NO  FALSE
#define Error -1
#define Pi 3.1415926
#define CMDHWND GetConsoleWindow()
#define nScreenWidth GetSystemMetrics(SM_CXSCREEN)
#define nScreenheight GetSystemMetrics(SM_CYSCREEN)
#pragma comment( lib,"Winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

/*
��ɫ����������ʮ����������ָ��, ��һ��Ϊ����ɫ, �ڶ���Ϊǰ��ɫ��
ÿ�����ֿ���Ϊ����ֵ֮һ��
��ɫ = 0 ��ɫ = 1 ��ɫ = 2 ����ɫ = 3
��ɫ = 4 ��ɫ = 5 ��ɫ = 6 ��ɫ = 7
��ɫ = 8 ����ɫ=9 ����ɫ=A ����ɫ=C
����ɫ=D ����ɫ=E ����ɫ=F
���� 0x67 ���ǻ�ɫ�װ�ɫ��
������뼸�����ǵ��������е�������
�������		��Ӧֵ	��Ӧ��
VK_LBUTTON		1	    ������
VK_RBUTTON		2	    ����Ҽ�
VK_CANCEL		3	    Cancel
VK_MBUTTON		4	    ����м�
VK_XBUTTON1		5
VK_XBUTTON2		6
VK_BACK			8   	Backspace
VK_TAB			9   	Tab
VK_CLEAR		12	    Clear
VK_RETURN		13  	Enter
VK_SHIFT		16	    Shift
VK_CONTROL		17  	Ctrl
VK_MENU	        18	    Alt
VK_PAUSE		19  	Pause
VK_CAPITAL		20	    Caps Lock
VK_KANA			21
VK_HANGUL		21
VK_JUNJA		23
VK_FINAL		24
VK_HANJA		25
VK_KANJI		25  	*
VK_ESCAPE		27	    Esc
VK_CONVERT		28
VK_NONCONVERT	29
VK_ACCEPT		30
VK_MODECHANGE	31
VK_SPACE		32  	Space
VK_PRIOR		33	    Page Up
VK_NEXT			34  	Page Down
VK_END			35	    End
VK_HOME			36  	Home
VK_LEFT			37	    Left Arrow
VK_UP			38  	Up Arrow
VK_RIGHT		39	    Right Arrow
VK_DOWN			40  	Down Arrow
VK_SELECT		41	    Select
VK_PRINT		42  	Print
VK_EXECUTE		43	    Execute
VK_SNAPSHOT		44  	Snapshot
VK_INSERT		45  	Insert
VK_DELETE		46  	Delete
VK_HELP			47  	Help
                48  	0
                49	    1
                50  	2
                51	    3
                52  	4
                53  	5
                54  	6
                55  	7
                56  	8
                57  	9
                65  	A
                66  	B
                67  	C
                68  	D
                69  	E
                70  	F
                71  	G
                72  	H
                73     	I
                74  	J
                75  	K
                76  	L
                77  	M
                78	    N
                79  	O
                80	    P
                81  	Q
                82	    R
                83  	S
                84	    T
                85  	U
                86	    V
                87  	W
                88	    X
                89  	Y
                90	    Z
VK_LWIN			91
VK_RWIN			92
VK_APPS			93
VK_SLEEP		95
VK_NUMPAD0		96  	С���� 0
VK_NUMPAD1		97	    С���� 1
VK_NUMPAD2		98  	С���� 2
VK_NUMPAD3		99	    С���� 3
VK_NUMPAD4		100	    С���� 4
VK_NUMPAD5		101 	С���� 5
VK_NUMPAD6		102 	    С���� 6
VK_NUMPAD7		103	    С���� 7
VK_NUMPAD8		104 	С���� 8
VK_NUMPAD9		105	    С���� 9
VK_MULTIPLY		106 	С���� *
VK_ADD			107	    С���� +
VK_SEPARATOR	108 	С���� Enter
VK_SUBTRACT		109	    С���� -
VK_DECIMAL		110 	С���� .
VK_DIVIDE		111	    С���� /
VK_F1			112	    F1
VK_F2			113	    F2
VK_F3			114	    F3
VK_F4			115	    F4
VK_F5			116	    F5
VK_F6			117	    F6
VK_F7			118	    F7
VK_F8			119	    F8
VK_F9			120	    F9
VK_F10			121  	F10
VK_F11			122	    F11
VK_F12			123 	F12
VK_F13			124
VK_F14			125
VK_F15			126
VK_F16			127
VK_F17			128
VK_F18			129
VK_F19			130
VK_F20			131
VK_F21			132
VK_F22			133
VK_F23			134
VK_F24			135
VK_NUMLOCK		144	    Num Lock
VK_SCROLL		145 	Scroll
VK_LSHIFT		160
VK_RSHIFT		161
VK_LCONTROL		162
VK_RCONTROL		163
VK_LMENU		164
VK_RMENU		165
VK_BROWSER_BACK		166
VK_BROWSER_FORWARD	167
VK_BROWSER_REFRESH	168
VK_BROWSER_STOP		169
VK_BROWSER_SEARCH	170
VK_BROWSER_FAVORITES	171
VK_BROWSER_HOME		172
VK_VOLUME_MUTE		173	VolumeMute
VK_VOLUME_DOWN		174	VolumeDown
VK_VOLUME_UP		175	VolumeUp
VK_MEDIA_NEXT_TRACK	176
VK_MEDIA_PREV_TRACK	177
VK_MEDIA_STOP		178
VK_MEDIA_PLAY_PAUSE	179
VK_LAUNCH_MAIL		180
VK_LAUNCH_MEDIA_SELECT	181
VK_LAUNCH_APP1		182
VK_LAUNCH_APP2		183
VK_OEM_1		186	; :
VK_OEM_PLUS		187	= +
VK_OEM_COMMA		188
VK_OEM_MINUS		189	- _
VK_OEM_PERIOD		190
VK_OEM_2		191	/ ?
VK_OEM_3		192	` ~
VK_OEM_4		219	[ {
VK_OEM_5		220	\
VK_OEM_6		221	] }
VK_OEM_7		222	' "
VK_OEM_8		223
VK_OEM_102		226
VK_PACKET		231
VK_PROCESSKEY		229
VK_ATTN			246
VK_CRSEL		247
VK_EXSEL		248
VK_EREOF		249
VK_PLAY			250
VK_ZOOM			251
VK_NONAME		252
VK_PA1			253
VK_OEM_CLEAR		254
*/

static int Vsn(int A)
{
    //����: xsq1234
    //δ��������Ȩ����ֹת��
    // 
    //���䣺c6668883535357a@163.com |1993346266@qq.com 
    // 
    //�汾��Ϣ��1.2.1
    /*
    *     �汾��������
    * 0.1 ʵ���˴��ڴ�������
    * 0.2 �����˴��ڴ���������ʵ�����ض�λ��������ֺ���
    * 0.3 ʵ���˻��ߺ������ƶ���꺯������������
    * 0.4 ʵ������ɫ����
    * 0.5 ʵ����������;��κ���
    * 0.6 ʵ�������ع�꺯��
    * 0.7 ���������ֱ༭������
    * 0.8 �������ַ�����ʾ����
    * 0.9 ���������ֱ༭������,ʹ���ܶ�ȡ����
    * 1.0 �������ֱ༭������Ϊ���ֲ��ź���,�����˼ӷ�������
    * 1.01 ����ɫѡ���Gotoxy�����з��룬ʹ֮��Ϊ�����ĺ�����Music����ά����
    * 1.02 �޸��˲��ִ���
    * 1.03 ������Line����
    * 1.04 �����˲�������,�Բ��ֺ�������������
    * 1.05 �����Line������bug
    * 1.1 ������������뿪�غ��������������Բ���ѡ��cmd����
    * 1.11 �����˵�ɫ��
    * 1.2  �����˻�ȡ�����Cmd����������ĺ���
    * 1.21 �޸���Line������ĳЩ�ǶȲ��ܻ��Ƶ�����
    * 1.22 �޸���Line�����ڴ�������Ƶ�bug
    * 1.3 ʵ������ͣ����
    * 1.31 ɾ����һЩ��������ʹ�õĺ������޸���һЩbug
    * 1.32 �޸���һЩ��ֲʱ�����bug
    * 1.4 ������YES/NO����
    * 1.41 �����˲����Ͼɺ���
    * 1.42 ����Error����,������FALSE
    * 1.5 ������ȡ����ɫ����
    * 1.6 ������ȡǰ��ɫ����
    * 1.7 ������ȡ����������
    * 1.71 �ѽ�����ɫ����,ǰ��ɫ����,����������������atcg��չ��
    * 1.8 �����˰�ť����
    * 1.81 ������Mouse_x,Mouse_y����
    * 1.82 �޸���Button������BUG
    * 1.83 �޸���Button������BUG
    * 1.84 �޸���Button������BUG
    * 1.85 �޸���Button������BUG
    * 1.9 ʵ����ȫ������
    * 2.0 ������ɫ����,ǰ��ɫ����,��������������������star.h���ϲ�Ϊһ������
    * 2.1 ������ColorImg����
    * 3.0 ��ʽ��ʼwin32��������
    * 4.0 win32�������,��ʽ��ʼ����win32����
    * 4.1 ����win32�����л�ȡ�����ֱλ�ú���
    * 4.2 ����win32�����л�ȡ���ˮƽλ�ú���
    * 4.3 ����win32����꿪�غ���
    * 4.4 ����win32�������߶κ���
    * 4.5 ����win32�����л������ص㺯��
    * 4.51 ������Text����
    * 4.6 ����win32�ı��������
    * 4.7 �����˷�����ʽ��Ϣѭ������
    * 4.71 �汾���º�������ӵ���������
    * 4.8 ������win32���κ���
    * 4.85 ���ڽ�����ڴ�й¶������
    * 4.86 �޸��˲��ֱ���
    * 4.9 ������win32��ʾ���ֺ���
    * 4.91 �޸���WinMouseX��WinMouseY��bug
    * 5.0 win32������Ĭ�Ϲ��
    * 5.1 win32������Win32��ȡĳһλ��������ɫ
    * 5.2 win32������Win32��ʾͼƬ����
    * 5.3 win32������Win32ɾ�����ں���
    * 5.4 win32������WinImgA�������֣����ڿ�����ʾ͸��λͼ�ˣ������Ըı�λͼ�Ŵ���
    * 5.5 win32������ȫ������
    * 5.6 win32������ȥ������������
    * 5.61 win32��������괦����Ϣ
    * 5.62 �޸���һЩСbug
    * 5.63 �Բ��ֺ���������С�Ķ�
    * 5.7 �����˴�txt����һ�ж�ȡ���ݵĺ���
    * 5.71  �����˲����Ͼɺ���
    * 5.72  �����˲����Ͼɺ���
    * 5.73 ������CMDwindow����
    * 5.8 �����˴���͸�����ں���
    * 5.9 �����˽Ƕ�ת���Ⱥ���
    * 5.91 �Ż��˲��ֺ���
    * 6.0 �������ö����ں���
    * 6.1 ������CMD�������غ���
    * 6.2 ������Ӳ����⺯��
    * 7.0 �������̺߳���,���ڿ���ʹ�ö��̱߳�д��Ϸ��
    * 7.1 �����̺߳���
    * 7.2 ����˫���庯��
    * 8.0 ˫������ú����������
    * 8.1 �������̲߳��֣����ڴ����̸߳�������
    * 8.2 ���ֲ��ź����ع�
    * 8.21 �����˿���̨�����
    * 8.3 �������Ӵ��ں��������ڿ����ڴ����д����Ӵ�����
    * 8.4 ����͸�����ڣ��ô���͸�����������ݲ�͸��
    * 8.5 ������ť��⺯��WinButtonA,�ú����������������ֵ
    * 8.6 �������˱任���Ƶ㺯��
    * 8.7 �������˱任�����ߺ���
    * 8.8 ��������˫����任���Ƶ㺯��
    * 8.9 ��������˫����任�����ߺ���
    * 9.0 �޸������ֺ��������ظ��������ֵ�bug
    * 9.1 ������˫����BoxB����
    * 9.11 �޸���WinBox��huizhiBUG
    * 1.0.0 ����������
    * 1.0.01 CMDOFF�����޸ĳ���CMD�����������޸���CMDOFF��BUG
    * 1.0.02 �޸���HardwareDetection�Ŀ����޷���ֵ��BUG
    * 1.1.0 �����˶�ʱ��ģ��;
    * 1.1.1 �������ϴ������޸ĵĺ���
    * 1.1.2 ������BoxC����
    * 1.1.21 ������HardwareDetection����
    * 1.1.23 �޸��˻�ȡ����������б�����������¶Բ����BUG
    * 1.1.3 �������˻�ȡ����ˮƽ����ĺ���
    * 1.1.4 �������˻�ȡ���ڴ�ֱ����ĺ���
    * 1.1.41 �����������һЩ
    * 1.1.42 �޸���HardwareDetection��һЩbug
    * 1.1.43 ������CMDGetColor����
    * 1.1.5 �����˻���Բ����
    * 1.1.51 ����������͸������
    * 1.1.6 ������LPCSTR����ת����LPCWSTR����
    * 1.1.61 �޸�����C++�����µĲ��ֱ���
    * 1.2.0 ������OpenGL��ͼ
    * 1.2.01 �޸������������BUG
    * 1.2.02 ���ڿ����ڶ��ļ���ʹ�øö๦�ܿ�
    * 1.2.1 ������lerp����
    * 1.2.2 ��������������ײ��⺯��
    * 1.2.01 �����˲����������Ͳ���Ҫ�Ĺ��ܣ����ڻ�ͼʱ��Ҫͬʱ���������豸�������������ڴ�й¶����,��֮ǰ��ֻ�ܴ���һ��������ͬ����Ȼ����֮ǰʹ�øÿ�Ĵ���û�м����Է���
    * 1.2.02 ɾ���˲��ֲ���Ҫ�Ĵ���
    * 1.2.1 cpp��ֲ�ɹ�,����cpp�Ͷ�����ͬʱʹ�ø�����
    * 1.2.2 ������RunProgram����
    */
    return A;
}

static void CMDwindow(LPCWSTR name, unsigned int width, unsigned int height, int Character_width, int Character_height)
{
    //name ��������
    // x:���ں�����
    // y������������ 
    // width height ���ڴ�С
    // Character_width Character_height �ַ������
    //��ȡ��ǰ����̨�ľ��
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //�ַ���С
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = Character_width;
    cfi.dwFontSize.Y = Character_height;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    //���ô��ڴ�С   
    char command[256];
    snprintf(command, sizeof(command), "mode con: cols=%d lines=%d", width, height);
    int result = system(command);
    SetConsoleTitle(name);                                      //���Ĵ��ڱ���    
    LONG style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);  // ��ֹ�ı䴰�ڴ�С    
    style &= ~WS_SIZEBOX;                                       // �Ƴ��ɵ�����С����ʽ
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, style);
    //���ع�����
    ShowScrollBar(GetConsoleWindow(), SB_VERT, FALSE);
    ShowScrollBar(GetConsoleWindow(), SB_HORZ, FALSE);
}

//�ƶ����
static void Gotoxy(int x, int y)
{
    COORD lightb = { x,y };
    HANDLE CMD = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(CMD, lightb);
}

//��ɫ����
static void Color(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//�������ֳ��ֵ�����
static void CMDText(LPCSTR text, int x, int y, int color)
{
    Gotoxy(x, y);
    Color(color);
    printf(text);
    Color(0x07);
}

//����
static void CMDClear() { system("cls"); }
//-------------------------------------------------------------------------------------------���߳���Ϸ����---------------------------------------------------------------------------------------------------------------------------------------//

//�����̺߳����ؼ���
typedef DWORD THREAD;

//���̺߳����ṹ��
typedef struct
{
    DWORD* ID;
    HANDLE ThreadHwnd;
}CREATTHREAD;

//�����߳�
static HANDLE RunThread(THREAD* function, THREAD* ID) { return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function, (LPVOID)2, 0, ID); }

//ɾ���߳�
static void DeletThread(HANDLE Threadhwnd)
{
    WaitForSingleObject(Threadhwnd, INFINITE);
    CloseHandle(Threadhwnd);
}

//-------------------------------------------------------------------------------------------˫�����ͼ�����ڻ������ڻ�ͼ�ĺ���---------------------------------------------------------------------------------------------------------------------------------------//

//˫�����ͼ
typedef struct
{
    HDC hdc;
    HBITMAP hBitmap;
}DOUBLEBUFFER;

//����˫�����ͼ��ͼ��
static HDC DoubleBuffer(HWND hwnd, HBITMAP hBitmap, int windowwidth, int windowheight)
{
    HDC hdcMem = CreateCompatibleDC(GetDC(hwnd));
    hBitmap = CreateCompatibleBitmap(GetDC(hwnd), windowwidth, windowheight);
    SelectObject(hdcMem, hBitmap);
    return hdcMem;
}

//����˫�����ͼ
static void RUNDoubleBuffer(HWND hwnd, HDC hdc, int windowwidth, int windowheight) { BitBlt(GetDC(hwnd), 0, 0, windowwidth, windowheight, hdc, 0, 0, SRCCOPY); }

//ɾ��˫�����ͼ��ͼ��
static void DeletBuffer(HBITMAP hBitmap, HDC hdcMem)
{
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
}

//---------------------------------------------------------------------------------------------����Ϊwin32����------------------------------------------------------------------------------------------------------//

//�ڴ����л����߶�
static void Line(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    HDC hDc = hdc;
    HPEN hpen = CreatePen(PS_SOLID, 1, color);
    HPEN holdpen = (HPEN)SelectObject(hDc, hpen);
    MoveToEx(hDc, x2, y2, NULL);
    LineTo(hDc, x1, y1);
    SelectObject(hDc, holdpen);
    DeleteObject(hpen);
    ReleaseDC(hwnd, hDc);
}

//�������ص�
static void Pix(HWND hwnd, HDC hdc, int x, int y, COLORREF color)
{
    HDC hDc = hdc;
    SetPixel(hDc, x, y, color);
    ReleaseDC(hwnd, hDc);
}

//ê���
static void ApPix(HWND hwnd, HDC hdc, int apx, int apy, int x, int y, double rad, COLORREF color)
{
    int newx, newy;
    double Rot2Dmax[2][2] =
    {
        {cos(rad),-sin(rad)},
        {sin(rad),cos(rad)}
    };
    newx = Rot2Dmax[0][0] * x + Rot2Dmax[0][1] * y + apx;
    newy = Rot2Dmax[1][0] * x + Rot2Dmax[1][1] * y + apy;
    Pix(hwnd, hdc, newx, newy, color);
}

//ê����
static void ApLine(HWND hwnd, HDC hdc, int apx, int apy, int x1, int y1, int x2, int y2, double rad, COLORREF color)
{
    int newx1, newy1, newx2, newy2;
    double Rot2Dmax[2][2] =
    {
        {cos(rad),-sin(rad)},
        {sin(rad),cos(rad)}
    };
    newx1 = Rot2Dmax[0][0] * x1 + Rot2Dmax[0][1] * y1 + apx;
    newy1 = Rot2Dmax[1][0] * x1 + Rot2Dmax[1][1] * y1 + apy;
    newx2 = Rot2Dmax[0][0] * x2 + Rot2Dmax[0][1] * y2 + apx;
    newy2 = Rot2Dmax[1][0] * x2 + Rot2Dmax[1][1] * y2 + apy;
    Line(hwnd, hdc, newx1, newy1, newx2, newy2, color);
}

//���κ���
static void BoxA(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    HDC hDc = hdc;
    HPEN hpen = CreatePen(PS_SOLID, 1, color);
    HPEN holdpen = (HPEN)SelectObject(hDc, hpen);
    Rectangle(hDc, x1, y1, x2, y2);
    SelectObject(hDc, holdpen);
    DeleteObject(hpen);
    ReleaseDC(hwnd, hDc);
}

static void BoxB(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    HDC hDc = hdc;
    PAINTSTRUCT ps;
    HBRUSH hbs = CreateSolidBrush(color);
    RECT rect = { x1,y1,x2,y2 };
    FillRect(hDc, &rect, hbs);
    DeleteObject(hbs);
    EndPaint(hwnd, &ps);
    ReleaseDC(hwnd, hDc);
}

static void BoxC(HWND hwnd, HDC hdc, int x, int y, int width, int height, COLORREF color)
{
    HDC hDc = hdc;
    PAINTSTRUCT ps;
    HBRUSH hbs = CreateSolidBrush(color);
    RECT rect = { x,y,x + width,y + height };
    FillRect(hDc, &rect, hbs);
    DeleteObject(hbs);
    EndPaint(hwnd, &ps);
    ReleaseDC(hwnd, hDc);
}

//����Բ
static void Circle(HWND hwnd, HDC hdc, int R, int x, int y, COLORREF color)
{
    HDC hDc = hdc;
    HPEN hpen = CreatePen(PS_SOLID, 1, color);
    HPEN holdpen = (HPEN)SelectObject(hDc, hpen);
    Ellipse(hDc, x - R, y - R, x + R, y + R);
    SelectObject(hDc, holdpen);
    DeleteObject(hpen);
    ReleaseDC(hwnd, hDc);
}

//��ʾͼƬ
static void Img(HWND hwnd, HDC hdc, const wchar_t* File, int x, int y)
{
    HDC hDc = hdc;
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, File, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap)
    {
        HDC hdcMem = CreateCompatibleDC(hDc);
        SelectObject(hdcMem, hBitmap);
        BITMAP bitmap;
        GetObject(hBitmap, sizeof(BITMAP), &bitmap);
        BitBlt(hDc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);
        DeleteObject(hBitmap); // �ͷ�λͼ��Դ
    }
    else printf("[WinImg��������][%s]�ļ���ʧ�ܣ������ļ��Ƿ���Ŀ¼��.[Enter]�˳�\n", *File);
}

//��ʾͼƬ�ı��֣�����ѡ���Բ���ʾĳ����ɫ�������Ըı�ͼƬ�Ŵ���
static void ImgA(HWND hwnd, HDC hdc, const wchar_t* File, int x, int y, double widthbs, double heightbs, COLORREF color)
{
    HDC hDc = hdc;
    if (widthbs <= 0) { widthbs = 1; }
    if (heightbs <= 0) { heightbs = 1; }
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, File, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap)
    {
        HDC hdcMem = CreateCompatibleDC(hDc);
        SelectObject(hdcMem, hBitmap);
        BITMAP bitmap;
        GetObject(hBitmap, sizeof(BITMAP), &bitmap);
        TransparentBlt(hDc, x, y, bitmap.bmWidth * widthbs, bitmap.bmHeight * heightbs, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, color);
        DeleteDC(hdcMem);
        DeleteObject(hBitmap); // �ͷ�λͼ��Դ
    }
    else printf("[WinImgA��������][%s]�ļ���ʧ�ܣ������ļ��Ƿ���Ŀ¼��.[Enter]�˳�\n", *File);
}

//---------------------------------------------------------------------------------------------����ΪOpenGL����------------------------------------------------------------------------------------------------------//

typedef struct
{
    HDC hdc;
    HWND hwnd;
    HGLRC hrc;
}OPENGL;

//��ʼ�� OpenGL
static void SetOpenGL(HWND hwnd,OPENGL* opengl)
{
    HDC hdc;
    HGLRC hrc;
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32, // ��ɫ���
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        24, // ��Ȼ�����
        8,  // ģ�建����
        0, 0, 0, 0, 0
    };

    hdc = GetDC(hwnd);
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);
    hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);

    // �����ӿں�����ͶӰ
    RECT rect;
    GetClientRect(hwnd, &rect);//��ȡ���ڴ�С
    glViewport(0, 0, rect.right, rect.bottom);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, rect.right, rect.bottom, 0, -1.0, 1.0); // ��������ͶӰ
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    opengl->hdc = hdc;
    opengl->hrc = hrc;
}

//���ƻ���
static void RunOpenGL(HDC hdc)
{
    SwapBuffers(hdc);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void DeletOPENGL(OPENGL opengl)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(opengl.hrc);
    ReleaseDC(opengl.hwnd, opengl.hdc);
    DestroyWindow(opengl.hwnd);
}

// ���������ĺ���
static void GLine(float x, float y, float x2, float y2, float width, int alpha, COLORREF color)
{
    glColor4ub(GetRValue(color), GetGValue(color), GetBValue(color), alpha);
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x2, y2);
    glEnd();
}

static void GPolygon(POINT* point, int n, int x, int y, int alpha, COLORREF color, BOOL line, int width, COLORREF color2)
{
    glColor4ub(GetRValue(color), GetGValue(color), GetBValue(color), alpha);
    glLineWidth((float)width);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)glVertex2f((float)(point[i].x + x), (float)(point[i].y + y));
    glEnd();
    // ���Ʊ߿�
    if (line)
    {
        glColor3ub(GetRValue(color2), GetGValue(color2), GetBValue(color2));
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; i++) glVertex2f(point[i].x + x, point[i].y + y);
        glEnd();
    }
}

static void GBox(int mode, int x, int y, int width, int height, int alpha, COLORREF color, int linewidth, COLORREF color2)
{
    POINT point[4] =
    {
        {0,0},
        {width,0},
        {width,height},
        {0,height},
    };
    switch (mode)
    {
    case 1: GPolygon(point, 4, x, y, alpha, color, 0, 0, 0); break;
    case 2: GPolygon(point, 4, x, y, alpha, color, 1, linewidth, color2); break;
    }
}

static void GPix(HDC hdc, int x, int y, int alpha, COLORREF color)
{
    glColor4ub(GetRValue(color), GetGValue(color), GetBValue(color), alpha);
    glBegin(GL_POINTS);
    //glPixelZoom((GLfloat)x, (GLfloat)y);
    //glDrawPixels(10,10,)
    glVertex2f(x, y);
    glEnd();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//��Ϣ������,�벻Ҫ�Ҷ��˺���!!!
static LRESULT WINAPI WndPorc(HWND hwnd, UINT msgid, WPARAM wparam, LPARAM lparam)
{
    switch (msgid)
    {
    case WM_DESTROY: PostQuitMessage(0); break;
    case WM_PAINT: break;
    case WM_SETCURSOR:
    switch (LOWORD(lparam)) { default:SetCursor(LoadCursor(NULL, IDC_ARROW)); break; }
    }
    return DefWindowProc(hwnd, msgid, wparam, lparam);
}

//��������
static HWND Window(
    HWND hwnd	 /*���*/,
    LPCWSTR name /*��������*/,
    int w		 /*���ڿ��*/,
    int h		 /*���ڸ߶�*/,
    int x		 /*����ˮƽ����*/,
    int y		 /*������ֱ����*/
)
{
    HINSTANCE hinstance = GetModuleHandle(NULL);
    //ע�ᴰ����
    WNDCLASS wndclass = { 0 };
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(4);    //��ȡ��ˢ ��䱳��
    wndclass.hCursor = NULL;                               //���ָ��
    wndclass.hIcon = NULL;                                 //ϵͳĬ��ͼ��
    //������
    wndclass.hInstance = hinstance;
    wndclass.lpfnWndProc = WndPorc;
    wndclass.lpszClassName = TEXT("main");                 //����
    wndclass.lpszMenuName = NULL;                          //�˵�
    //������ʽ
    wndclass.style = CS_HREDRAW | CS_CLASSDC;
    RegisterClass(&wndclass);
    hwnd = CreateWindow(TEXT("main"), name/*����*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, x, y, w, h, NULL, NULL, hinstance, NULL);    //��������
    //��ʾ����
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}

//����͸������
static HWND WindowA(
    HWND hwnd	      /*���*/,
    LPCWSTR name      /*��������*/,
    int w		      /*���ڿ��*/,
    int h		      /*���ڸ߶�*/,
    int x		      /*����ˮƽ����*/,
    int y			  /*������ֱ����*/,
    int transparency  /*����͸����*/
)
{
    HINSTANCE hinstance = GetModuleHandle(NULL);
    //ע�ᴰ����
    WNDCLASS wndclass = { 0 };
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(4);    //��ȡ��ˢ ��䱳��
    wndclass.hCursor = NULL;                               //���ָ��
    wndclass.hIcon = NULL;                                 //ϵͳĬ��ͼ��
    //������
    wndclass.hInstance = hinstance;
    wndclass.lpfnWndProc = WndPorc;
    wndclass.lpszClassName = TEXT("main");                 //����
    wndclass.lpszMenuName = NULL;                          //�˵�
    //������ʽ
    wndclass.style = CS_HREDRAW | CS_CLASSDC;
    RegisterClass(&wndclass);
    hwnd = CreateWindowEx(WS_EX_LAYERED, TEXT("main"), name/*����*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME & WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hinstance, NULL);    //��������
    //��ʾ����
    SetLayeredWindowAttributes(hwnd, 0, (BYTE)transparency, LWA_ALPHA);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}

//����͸������2
static HWND WindowB(
    HWND hwnd	      /*���*/,
    LPCWSTR name      /*��������*/,
    int w		      /*���ڿ��*/,
    int h		      /*���ڸ߶�*/,
    int x		      /*����ˮƽ����*/,
    int y			  /*������ֱ����*/
)
{
    HINSTANCE hinstance = GetModuleHandle(NULL);
    //ע�ᴰ����
    WNDCLASS wndclass = { 0 };
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(4);    //��ȡ��ˢ ��䱳��
    wndclass.hCursor = NULL;                               //���ָ��
    wndclass.hIcon = NULL;                                 //ϵͳĬ��ͼ��
    //������
    wndclass.hInstance = hinstance;
    wndclass.lpfnWndProc = WndPorc;
    wndclass.lpszClassName = TEXT("main");                 //����
    wndclass.lpszMenuName = NULL;                          //�˵�
    //������ʽ
    wndclass.style = CS_HREDRAW | CS_CLASSDC;
    RegisterClass(&wndclass);
    hwnd = CreateWindowEx(WS_EX_LAYERED, TEXT("main"), name/*����*/, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME & WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hinstance, NULL);    //��������
    //��ʾ����
    SetLayeredWindowAttributes(hwnd, 0, 0, ULW_COLORKEY);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return hwnd;
}

//����ʽ��Ϣѭ����win32���þ����,�����ڶ��߳���Ϸ
static void RunWindow()
{
    //��Ϣѭ��
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (GetAsyncKeyState(VK_ESCAPE))  printf("�������˳�\n"); return;
    }
}

//������ʽ��Ϣѭ����win32���þ����,�����ڵ��߳���Ϸ
static void ClearWindow()
{
    MSG msg = { 0 };
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//-------------------------------------------------------------------------������-------------------------------------------------------------------------------------------------------------------------------------------------------//

//����/��ʾ���
static void CMDHide(BOOL A)
{
    CONSOLE_CURSOR_INFO curInfo = { 1,A };
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &curInfo);
}

//������뿪�غ���(�رտ��ٱ༭ģʽ)
static void CMDMouse(int NO_or_OFF)
{
    DWORD mode;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    switch (NO_or_OFF)
    {
    case ON: return; break;
    case OFF:
        GetConsoleMode(hStdin, &mode);
        mode &= ~ENABLE_QUICK_EDIT_MODE;
        mode &= ~ENABLE_INSERT_MODE;
        mode &= ~ENABLE_MOUSE_INPUT;
        SetConsoleMode(hStdin, mode);
        break;
    }
}

//��ͣ����
static void TimeOut() { getchar(); }

//ȫ������
static void CMDFullScreen()
{
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_F11;
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

//�����
static int Random(int A, int B) { return rand() % (B - A) + A; }

//�Ƕ�ת����
static double DegRad(double a) { return Pi * a * 1.0 / 180; }

//���ؿ���̨
static BOOL CMD(BOOL YESORNO)
{
    if (YESORNO)ShowWindow(CMDHWND, SW_SHOW);
    else ShowWindow(CMDHWND, SW_HIDE);
    return 0;
}

//Ӳ����⺯��
static int HardwareDetection()
{
    if (GetAsyncKeyState(1)) return 1;              //���
    if (GetAsyncKeyState(2)) return 2;              //�Ҽ�
    if (GetAsyncKeyState(4)) return 4;              //�м�
    if (GetAsyncKeyState(VK_F11)) return VK_F11;    //F11
    if (GetAsyncKeyState(20)) return 20;            //caps lock
    if (GetAsyncKeyState(18)) return 18;            //alt
    if (GetAsyncKeyState(17)) return 17;            //ctrl
    if (GetAsyncKeyState(16)) return 16;            //shift
    if (_kbhit()) return 0;
    else for (int i = 2; i < 254; i++) if (i == 10 || i == 11 || i == 14 || i == 15 || i == 58 || i == 59 || i == 60 || i == 61 || i == 62 || i == 63 || i == 64 || i == 136 || i == 137 || i == 138 || i == 139 || i == 140 || i == 141 || i == 142 || i == 143 || i == 146 || i == 147 || i == 148 || i == 149 || i == 150 || i == 151 || i == 152 || i == 153 || i == 154 || i == 155 || i == 156 || i == 157 || i == 158 || i == 159 || i == 184 || i == 185 || i == 193 || i == 194 || i == 195 || i == 196 || i == 197 || i == 198 || i == 199 || i == 200 || i == 201 || i == 202 || i == 203 || i == 204 || i == 205 || i == 206 || i == 207 || i == 208 || i == 209 || i == 210 || i == 211 || i == 212 || i == 213 || i == 214 || i == 215 || i == 216 || i == 217 || i == 218 || i == 224 || i == 225 || i == 227 || i == 228 || i == 232 || i == 230 || i == 233 || i == 234 || i == 235 || i == 236 || i == 237 || i == 238 || i == 239 || i == 240 || i == 241 || i == 242 || i == 243 || i == 244 || i == 245 || i == 7 || i == 26) continue;
    else if (GetAsyncKeyState(i))  return i;
}

//���ֺ���
static void Music(LPCWSTR File)
{
    TCHAR cmd[255];
    wsprintf(cmd, TEXT("open \%s\ alias music"), File);
    mciSendString(TEXT("close music"), 0, 0, 0);
    mciSendString(cmd, NULL, 0, NULL);
    mciSendString(TEXT("play music"), NULL, 0, NULL);
}

//�Ӵ��ں���
static void Parent(HWND parent, HWND child) { SetParent(child, parent); }

//��ȡ���ˮƽλ��
static int MouseX(HWND hwnd)
{
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);
    return p.x;
}

//��ȡ�����ֱλ��
static int MouseY(HWND hwnd)
{
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);
    return p.y;
}

//��ȡ����ˮƽ����
static int WindowcoordinatesX(HWND hwnd)
{
    RECT windowcoordinates;
    GetWindowRect(hwnd, &windowcoordinates);
    return windowcoordinates.left;
}

//��ȡ���ڴ�ֱ����
static int WindowcoordinatesY(HWND hwnd)
{
    RECT windowcoordinates;
    GetWindowRect(hwnd, &windowcoordinates);
    return windowcoordinates.top;
}

//win32����꿪��
static void Mouse(BOOL ON_OR_OFF) { ShowCursor(ON_OR_OFF); }

//��ȡ����̨ĳһ����ɫ,A==1ʱΪǰ��ɫ��A==2ʱΪ����ɫ
static int CMDGetColor(int x, int y, int A)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD coord = { x,y };
    DWORD count;
    WORD wa;
    ReadConsoleOutputAttribute(hConsole, &wa, 1, coord, &count);
    int f = wa & 0x0f;
    int b = (wa >> 4) & 0x0f;
    return (A - 1) ? b : f;
}

//��txt����һ�ж�ȡ���ݵĺ���
static int FILEFP(FILE* fp, int nLine)
{
    char buffer[1024 + 1];
    fpos_t pos;
    rewind(fp);
    for (int i = 0; i < nLine; i++)fgets(buffer, 1024, fp);
    fgetpos(fp, &pos);
    return 0;
}

//ɾ������
static void DeletWindow(HWND hwnd) { DestroyWindow(hwnd); }

//ȫ��
static void FullScreen(HWND hwnd) { ShowWindow(hwnd, 3); }

//win32���ر�����
static void TitleBar(HWND hwnd) { SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION); }

//�ö�����
static void FirstWindow(HWND hwnd)
{
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

//��������
static void Clear(HWND hwnd) { InvalidateRect(hwnd, NULL, TRUE); }

//�ı����
static void Text(HWND hwnd, HDC hdc, int x, int y, LPCWSTR text, COLORREF color)
{
    HDC hDc = hdc;
    SetBkMode(hDc, TRANSPARENT);//�������屳��͸��
    SetTextColor(hDc, color);
    TextOut(hDc, x, y, text, wcslen(text));
    ReleaseDC(hwnd, hDc);
}

//��ʾ����
static void Dight(HWND hwnd, HDC hdc, int x, int y, int dight, COLORREF color)
{
    HDC hDc = hdc;
    SetBkMode(hDc, TRANSPARENT);//�������屳��͸��
    int size;
    TCHAR szText[256];
    size = wsprintf(szText, TEXT("%d"), dight);
    SetTextColor(hDc, color);
    TextOut(hDc, x, y, szText, size);
    ReleaseDC(hwnd, hDc);
}

//��ȡĳһλ��������ɫ
static int GetColor(HWND hwnd, int x, int y) { return GetPixel(GetDC(hwnd), x, y); }

//��ť����
static int Button(HWND hwnd, HDC hdc, int x, int y, int width, int height, int ON_OFF)
{
    int c = 0;
    if (ON_OFF == ON)
    {
        if (x < MouseX(hwnd) && MouseX(hwnd) <= x + width && y < MouseY(hwnd) && MouseY(hwnd) <= y + height && GetAsyncKeyState(1) & 0x8000)
        {
            Line(hwnd, hdc, x, y, x + width, y, RGB(255, 0, 0));
            Line(hwnd, hdc, x, y + height, x + width, y + height, RGB(255, 0, 0));
            Line(hwnd, hdc, x, y, x, y + height, RGB(255, 0, 0));
            Line(hwnd, hdc, x + width, y, x + width, y + height, RGB(255, 0, 0));
            c = YES;
        }
        else
        {
            Line(hwnd, hdc, x, y, x + width, y, RGB(255, 255, 255));
            Line(hwnd, hdc, x, y + height, x + width, y + height, RGB(255, 255, 255));
            Line(hwnd, hdc, x, y, x, y + height, RGB(255, 255, 255));
            Line(hwnd, hdc, x + width, y, x + width, y + height, RGB(255, 255, 255));
            c = NO;
        }
    }
    else
        if (ON_OFF == OFF)
        {
            if (x < MouseX(hwnd) && MouseX(hwnd) <= x + width && y < MouseY(hwnd) && MouseY(hwnd) <= y + height && GetAsyncKeyState(1) & 0x8000) { c = YES; }
            else { c = NO; }
        }
    return c;
}

static int ButtonA(HWND hwnd, HDC hdc, int x, int y, int width, int height, BOOL YESORNO)
{
    int button = 0; GetAsyncKeyState(1);
    if (MouseX(hwnd) > x && MouseY(hwnd) > y && MouseX(hwnd) <= x + width && MouseY(hwnd) <= y + height && GetAsyncKeyState(1))button = 1;
    else if (MouseX(hwnd) > x && MouseY(hwnd) > y && MouseX(hwnd) <= x + width && MouseY(hwnd) <= y + height && !GetAsyncKeyState(1))button = 2;
    else button = 0;
    if (YESORNO == TRUE)
    {
        switch (button)
        {
        case 1:
        {
            Line(hwnd, hdc, x, y, x + width, y, RGB(255, 0, 0));
            Line(hwnd, hdc, x, y, x, y + height, RGB(255, 0, 0));
            Line(hwnd, hdc, x + width, y, x + width, y + height, RGB(255, 0, 0));
            Line(hwnd, hdc, x, y + height, x + width, y + height, RGB(255, 0, 0));
        }
        break;
        case 0:
        {
            Line(hwnd, hdc, x, y, x + width, y, RGB(255, 255, 255));
            Line(hwnd, hdc, x, y, x, y + height, RGB(255, 255, 255));
            Line(hwnd, hdc, x + width, y, x + width, y + height, RGB(255, 255, 255));
            Line(hwnd, hdc, x, y + height, x + width, y + height, RGB(255, 255, 255));
        }
        break;
        case 2:
            Line(hwnd, hdc, x, y, x + width, y, RGB(0, 255, 0));
            Line(hwnd, hdc, x, y, x, y + height, RGB(0, 255, 0));
            Line(hwnd, hdc, x + width, y, x + width, y + height, RGB(0, 255, 0));
            Line(hwnd, hdc, x, y + height, x + width, y + height, RGB(0, 255, 0));
            break;
        }
    }
    return button;
}

//��ʱ��ģ��
typedef struct
{
    int time1;
    int time2;
    int timeload;
    BOOL timeswitch;
}TIMELOAD;

static void SetTimeLoad(TIMELOAD* Timeload, int load)
{
    Timeload->time1 = NULL;
    Timeload->time2 = NULL;
    Timeload->timeload = load;
    Timeload->timeswitch = 0;
}

static int TimeLoad(TIMELOAD* Timeload, int mode)
{
    if (!mode)return 0;
    else
    {
        if (Timeload == NULL)
        {
            printf("[TimeLoad��������!]���ڿ�ָ��");
            return 0;
        }
        if (!Timeload->timeswitch)
        {
            Timeload->time1 = clock();
            if (Timeload->time1 > Timeload->time2 + Timeload->timeload)
            {
                Timeload->time2 = clock();
                Timeload->timeswitch = TRUE;
            }
        }
        else
        {
            Timeload->time2 = clock();
            Timeload->timeswitch = FALSE;
        }
        return Timeload->timeswitch;
    }
}

//LPCSTR����ת����LPCWSTR
static LPCWSTR CharToLPCWSTR(const char* str)
{
    wchar_t* wideStr = (wchar_t*)malloc(strlen(str) * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wideStr, strlen(str));
    return wideStr;
}

typedef struct
{
    double x;
    double y;
}DOUBLEPOINT;

static double Lerp(double a, double b, double t)
{
    t = (t < 1 ? t : 1);
    int c = (1. - t) * a + t * b;
    return c;
}

//��������ײ���
static BOOL TriangleDetection(POINT a, POINT b, POINT c, POINT p)
{
    double d1 = (p.x - b.x) * (a.y - b.y) - (a.x - b.x) * (p.y - b.y);
    double d2 = (p.x - c.x) * (b.y - c.y) - (b.x - c.x) * (p.y - c.y);
    double d3 = (p.x - a.x) * (c.y - a.y) - (c.x - a.x) * (p.y - a.y);
    return (d1 * d2 > 0) && (d2 * d3 > 0);
}

void RunProgram(LPCWSTR name) { ShellExecute(NULL, L"open", name, NULL, NULL, SW_SHOW); }