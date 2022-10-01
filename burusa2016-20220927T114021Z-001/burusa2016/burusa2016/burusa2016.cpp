// win01.cpp

#define HH 10

#include <Windows.h>
#include <iostream>

#include <time.h>


#define ID_MYTIMER 100
#define ID_MYTIMER2 200

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HFONT MyCreateFont(int, DWORD, LPCTSTR);
void Data(int);
void EData(int);
void Ftime(int, HWND, RECT, HDC);

LPCTSTR lpszClassName = TEXT("win01");	//�E�B���h�E�N���X


HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
	LPSTR lpsCmdLine, int nCmdShow)
{

	hInst = hCurInst;


	MSG msg;
	BOOL bRet;

	if (!InitApp(hCurInst))
		return FALSE;
	if (!InitInstance(hCurInst, nCmdShow))
		return FALSE;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

//�E�B���h�E�E�N���X�̓o�^

ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	//�v���V�[�W����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;//�C���X�^���X
	wc.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = TEXT("MYMENU");	//���j���[��
	wc.lpszClassName = lpszClassName;
	wc.hIconSm = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));
}

//�E�B���h�E�̐���
HWND hWnd;
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{

	int dispx = GetSystemMetrics(SM_CXSCREEN);
	int dispy = GetSystemMetrics(SM_CYSCREEN);



	hWnd = CreateWindow(lpszClassName,
		TEXT("�Љ�@�����ՓW���@�����i����"), //�^�C�g���o�[�ɕ\������܂�
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //�E�B���h�E�̎��
		CW_USEDEFAULT,	//�w���W
		CW_USEDEFAULT,	//�x���W
		dispx,	//��
		dispy,	//����
		NULL, //�e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL
		NULL, //���j���[�n���h���A�N���X���j���[���g���Ƃ���NULL
		hInst, //�C���X�^���X�n���h��
		NULL);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
//���ꂼ��̊�Ƃ̊����̑�����
static int companyAStockPriceChangeAmount, companyBStockPriceChangeAmount, companyCStockPriceChangeAmount, companyDStockPriceChangeAmount, companyEStockPriceChangeAmount;

//�E�B���h�E�v���V�[�W��
//���ꂼ��̊�Ƃ̊��� �ꎟ���ڂŊ�Ƃ��w��A�񎟌��ڂŊ��Ԃ��w��
static int stockPrices[5][HH + 1];

//��ʂɕ\��������Ԃ̐�
const int his = HH;
static int EV = 0;
TCHAR S[100];
TCHAR Sb[30];
static int number = 6;/*�����̐�*/
int spread[5] = { 10, 20, 30, 40, 50 };
static POINT stockPriceChartGraphPoint[5][HH];
//�����F�ɂ��Ĉ����O���[�o���ϐ�
int rR, rG, rB;
//nNE�͈Ӗ��̂Ȃ��H
int NE, nNE;
HBRUSH hBrushw, hBrush;
static HFONT hFont1, hFont2, hFont3;
static HFONT hFont4, hFont5, hFont6;
PAINTSTRUCT ps;
HDC hdc;
int currentRemainingTime, limitedTime;
static TCHAR lpOut[10];
TCHAR szPR[25][10];
TCHAR Rate[15], Yrate[4];
TCHAR Urate[] = TEXT("�בփ��[�g\n����\��");
TCHAR CON[] = TEXT("\n������̎���͂ł��܂���B\n���X���҂����������B");
TCHAR YOM[] = TEXT("\n�ǂݍ��ݒ��ł��B\n���X���҂����������B");
int TEST = 1;

int Rmax = 135;
int Rmin = 85;
int Rpr = 110;
int nD = 98;
int nLOOP[130];

RECT rc23, rc24, rc25, rc26;
int CT;
static int AAB, XO;
HPEN hPen4, hPen5;
int Qw;
int DQ = 0;
int EnD = 10;
static int AS[5];

static HBITMAP hBmp;
BITMAP bmp_info;
static HDC hdc_mem;
int bmpw, bmph;
HPEN hPen10;
int YXO;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	RECT clientRectangle;
	RECT rc0, rc1, rc2, rc3;
	RECT rc4;

	int i, q;
	i = 0;
	int o;
	int id;

	static int maxStockPriceInPeriod, minStockPriceInPeriod;

	static int XX;

	/*��������start*/

	GetClientRect(hWnd, &clientRectangle);

	/*��������end*/

	switch (msg) {
	case WM_CREATE:
		for (o = 0; o < nD; o++) {
			nLOOP[o] = 0;
		}
		hPen10 = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		hPen5 = (HPEN)GetStockObject(BLACK_PEN);
		hPen4 = (HPEN)GetStockObject(NULL_PEN);
		hBrushw = (HBRUSH)GetStockObject(WHITE_BRUSH);
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		limitedTime = 10000;
		currentRemainingTime = limitedTime;
		XO = 1;
		TEST = 0;
		Rpr = 110;
		rc0.left = 0;
		rc0.top = clientRectangle.bottom / 16;
		rc0.right = clientRectangle.right / number;
		rc0.bottom = clientRectangle.bottom / 9;
		rc1.left = rc0.right;
		rc1.top = rc0.top;
		rc1.right = clientRectangle.right / number * 2;
		rc1.bottom = rc0.bottom;
		rc2.top = 2;
		rc2.left = 2;
		rc2.bottom = rc0.top - clientRectangle.bottom / 80;
		rc2.right = rc1.right;
		rc3.top = rc0.bottom + clientRectangle.bottom / 40;
		rc3.left = rc0.left + clientRectangle.right / 160;
		rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40;
		rc3.right = rc1.right - clientRectangle.right / 35;

		/*���ꂼ��̑S���Ԃł̊����̏�����*/
		for (o = 0; o < HH; o++) {
			stockPrices[0][o] = 15000;
		}
		for (o = 0; o < HH; o++) {
			stockPrices[1][o] = 15000;
		}
		for (o = 0; o < HH; o++) {
			stockPrices[2][o] = 15000;
		}
		for (o = 0; o < HH; o++) {
			stockPrices[3][o] = 15000;
		}
		for (o = 0; o < HH; o++) {
			stockPrices[4][o] = 15000;
		}
		SetTimer(hWnd, ID_MYTIMER, 200, NULL);

		srand((unsigned)time(NULL));
		for (o = 0; o < 5; o++) {
			wsprintf((LPWSTR)szPR[0 + o * 2], TEXT("���G%d"), stockPrices[0 + o][his - 1] - spread[o]);
			wsprintf((LPWSTR)szPR[1 + o * 2], TEXT("���G%d"), stockPrices[0 + o][his - 1] + spread[o]);
		}
		wsprintf((LPWSTR)szPR[10], TEXT("�g���^������"));
		wsprintf((LPWSTR)szPR[11], TEXT("���j�N��"));
		wsprintf((LPWSTR)szPR[12], TEXT("�X�i����"));
		wsprintf((LPWSTR)szPR[13], TEXT("�C�g�[���[�J�h�["));
		wsprintf((LPWSTR)szPR[14], TEXT("�i�s�a"));

		hFont1 = MyCreateFont(36, SHIFTJIS_CHARSET, TEXT("�l�r ����"));
		hFont2 = MyCreateFont(15, SHIFTJIS_CHARSET, TEXT("�l�r ����"));
		hFont3 = MyCreateFont(10, SHIFTJIS_CHARSET, TEXT("�l�r ����"));
		hFont4 = MyCreateFont(40, SHIFTJIS_CHARSET, TEXT("�l�r ����"));
		hFont5 = MyCreateFont(50, SHIFTJIS_CHARSET, TEXT("�l�r ����"));
		hFont6 = MyCreateFont(25, SHIFTJIS_CHARSET, TEXT("�l�r ����"));

		for (o = 0; o < his; o++) {
			stockPriceChartGraphPoint[0][o].y = (rc3.bottom - rc3.top) / 2 + rc3.top;
			stockPriceChartGraphPoint[0][o].x = (rc3.right - rc3.left) / (his) * (o + 1) + rc3.left;
			stockPriceChartGraphPoint[1][o].y = (rc3.bottom - rc3.top) / 2 + rc3.top;
			stockPriceChartGraphPoint[1][o].x = (rc3.right - rc3.left) / (his) * (o + 1) + rc3.left + clientRectangle.right * 2 / 3;
			stockPriceChartGraphPoint[2][o].y = (rc3.bottom - rc3.top) / 2 + rc3.top + clientRectangle.bottom / 2;
			stockPriceChartGraphPoint[2][o].x = (rc3.right - rc3.left) / (his) * (o + 1) + rc3.left;
			stockPriceChartGraphPoint[3][o].y = (rc3.bottom - rc3.top) / 2 + rc3.top + clientRectangle.bottom / 2;
			stockPriceChartGraphPoint[3][o].x = (rc3.right - rc3.left) / (his) * (o + 1) + rc3.left + clientRectangle.right / 3;
			stockPriceChartGraphPoint[4][o].y = (rc3.bottom - rc3.top) / 2 + rc3.top + clientRectangle.bottom / 2;
			stockPriceChartGraphPoint[4][o].x = (rc3.right - rc3.left) / (his) * (o + 1) + rc3.left + clientRectangle.right * 2 / 3;
		}
		hBmp = (HBITMAP)LoadImage(hInst,	//�C���X�^���X�n���h��
			TEXT("ReSt.bmp"),						//�C���[�W�̖��O
			IMAGE_BITMAP,					//�C���[�W�^�C�v
			150,								//��
			150,								//����
			LR_LOADFROMFILE);				//���[�h�I�v�V����

		GetObject(hBmp, (int)sizeof(bmp_info), &bmp_info);
		bmpw = bmp_info.bmWidth;
		bmph = bmp_info.bmHeight;

		hdc_mem = CreateCompatibleDC(hdc);
		SelectObject(hdc_mem, hBmp);

		break;
	case WM_CLOSE:
		id = MessageBox(hWnd,
			TEXT("�I�����Ă���낵���ł���"),
			TEXT("�m�F"),
			MB_YESNO | MB_ICONQUESTION);
		if (id == IDYES) {
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, ID_MYTIMER);
		KillTimer(hWnd, ID_MYTIMER2);
		DeleteObject(hFont1);
		DeleteObject(hFont2);
		DeleteObject(hFont3);
		DeleteObject(hFont4);
		DeleteObject(hFont5);
		DeleteObject(hPen4);
		DeleteObject(hBrushw);
		DeleteObject(hBmp);
		DeleteDC(hdc_mem);
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		YXO = 0;
		hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, hPen4);
		SelectObject(hdc, hBrushw);
		Rectangle(hdc, clientRectangle.left, clientRectangle.top, clientRectangle.right, clientRectangle.bottom);

		if (!(EV < his + 3)) {
			if (XO == 1) {
				Ftime(1, hWnd, clientRectangle, hdc);
				Ftime(2, hWnd, clientRectangle, hdc);
				if (DQ != 1) {
					Ftime(3, hWnd, clientRectangle, hdc);
					Ftime(5, hWnd, clientRectangle, hdc);
				}
				Ftime(4, hWnd, clientRectangle, hdc);
				Ftime(6, hWnd, clientRectangle, hdc);
			}

			if (XO == 0) {
				bmph = clientRectangle.bottom / 9;
				bmpw = bmph;
				SelectObject(hdc, hBrushw);
				Rectangle(hdc, clientRectangle.left, clientRectangle.top, clientRectangle.right, clientRectangle.bottom);
				SelectObject(hdc, hFont5);
				wsprintf((LPWSTR)CON, TEXT("\n������̎���͂ł��܂���B\n���X���҂����������B"));
				DrawText(hdc, CON, -1, &clientRectangle, DT_CENTER);
				wsprintf((LPWSTR)CON, TEXT("\n\n\n\n\n����̐������ԁG%d�b"), limitedTime / 1000);
				DrawText(hdc, CON, -1, &clientRectangle, DT_CENTER);

				SelectObject(hdc_mem, hBmp);

				Rectangle(hdc, clientRectangle.right / 2 - bmpw / 2, clientRectangle.bottom * 3 / 4 - bmph, clientRectangle.right / 2 + bmpw / 2, clientRectangle.bottom * 3 / 4);
				StretchBlt(hdc,		//�]����
					clientRectangle.right / 2 - bmpw / 2,	//�]����x���W
					clientRectangle.bottom * 3 / 4 - bmph,	//�]����y���W
					bmpw,		//�]���撷���`�̕� 
					bmph,		//�]���撷���`�̍��� 
					hdc_mem,	//�]����
					0,			//�]����x���W
					0,
					150,
					150,//�]����y���W
					SRCCOPY);	//���X�^�[�I�y���[�V�����R�[�h
				YXO = 1;
			}
		}
		SelectObject(hdc, hBrush);

		if (EV < his + 3) {
			SelectObject(hdc, hBrushw);

			Rectangle(hdc, clientRectangle.left, clientRectangle.top, clientRectangle.right, clientRectangle.bottom);
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hFont5);
			wsprintf((LPWSTR)YOM, TEXT("\n�ǂݍ��ݒ��ł��B\n���X���҂����������B"));
			DrawText(hdc, YOM, -1, &clientRectangle, DT_CENTER);
			wsprintf((LPWSTR)YOM, TEXT("\n\n\n\n\n%d������"), Qw * 100 / (his + 1 + limitedTime / 1000));
			DrawText(hdc, YOM, -1, &clientRectangle, DT_CENTER);
		}
		EndPaint(hWnd, &ps);

		break;
	case WM_TIMER:
		if (EV == his + 3) {
			KillTimer(hWnd, ID_MYTIMER);
			SetTimer(hWnd, ID_MYTIMER2, 1000, NULL);
		}
		Qw++;

		if (XO == 1) {

			rc0.left = 0;
			rc0.top = clientRectangle.bottom / 16;
			rc0.right = clientRectangle.right / number;
			rc0.bottom = clientRectangle.bottom / 9;
			rc1.left = rc0.right;
			rc1.top = rc0.top;
			rc1.right = clientRectangle.right / number * 2;
			rc1.bottom = rc0.bottom;
			rc2.top = 2;
			rc2.left = 2;
			rc2.bottom = rc0.top - clientRectangle.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + clientRectangle.bottom / 40;
			rc3.left = rc0.left + clientRectangle.right / 80;
			rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40;
			rc3.right = rc1.right - clientRectangle.right / 80;

			rc4.left = rc1.right + clientRectangle.right / 20;
			rc4.top = clientRectangle.bottom / 60;
			rc4.bottom = rc0.top;
			rc4.right = clientRectangle.right / number * 2 * 2 - clientRectangle.right / 100;

			if (EV < his + 2) {
				currentRemainingTime -= limitedTime - 1000;

			}

			currentRemainingTime -= 1000;

			RECT rc5;
			rc5.left = clientRectangle.right / 3;
			rc5.right = rc4.right;
			rc5.top = rc4.top;
			rc5.bottom = rc4.bottom;


			InvalidateRect(hWnd, &rc5, 0);

			if (EV < his + 3) {
				InvalidateRect(hWnd, NULL, 0);
			}

			if (currentRemainingTime == 0) {

				if (!(EV < his + 2)) {
					XO = 0;
					TEST = 1;
				}
				/*�����E�`���[�g�ړ��̂��߂̃X�N���v�gstart*/

				EV++;

				if (EV == 2) {
					stockPrices[0][his] = 15000;
					stockPrices[1][his] = 15000;
					stockPrices[2][his] = 15000;
					stockPrices[3][his] = 15000;
					stockPrices[4][his] = 15000;
				}

				o = 0;

				/**goto�����g���Ă��܂��B���ӁI**/
				if (DQ != 1) {
				loop:
					XX = rand() % nD;

					if (XX == 108) {
						goto loop;
					}
					if (XX == 110) {
						goto loop;
					}
					if (XX == 111) {
						goto loop;
					}
					if (XX == 112) {
						goto loop;
					}
					if (XX >= 123 && XX <= 130) {
						goto loop;
					}


					if (nLOOP[XX] == 1) {
						o++;
						if (o == 1000000) {
							Data(1000);
							goto out;
						}
						goto loop;
					}
					if (!(EV < his + 3)) {
						nLOOP[XX] = 1;
					}
					if (!(EV < his + 3)) {
						if (NE == 36) {
							Data(34);
							nLOOP[34] = 1;
							NE = 0;
						}
						else {
							Data(XX);
						}
					}
				out:
					/*
					try {
						while (true) {
							XX = rand() % nD;
							if (XX == 108) {
								throw std::string(std::to_string(XX));
								continue;
							}
							if (XX == 110) {
								throw std::string(std::to_string(XX));
								continue;
							}
							if (XX == 111) {
								throw std::string(std::to_string(XX));
								continue;
							}
							if (XX == 112) {
								throw std::string(std::to_string(XX));
								continue;
							}
							if (XX >= 123 && XX <= 130) {
								throw std::string(std::to_string(XX));
								continue;
							}


							if (nLOOP[XX] == 1) {
								o++;
								if (o == 1000000) {
									Data(1000);
									break;
								}
								continue;
							}
							if (!(EV < his + 3)) {
								nLOOP[XX] = 1;
							}
							if (!(EV < his + 3)) {
								if (NE == 36) {
									Data(34);
									nLOOP[34] = 1;
									NE = 0;
								}
								else {
									Data(XX);
								}
							}
						}
					}
					catch (std::string errorMessage) {
						std::cout << errorMessage << std::endl;
					}*/
					o = 1;
				}

				if (DQ == 1) {
				Eloop:
					XX = rand() % EnD;
					if (nLOOP[XX] == 1) {
						o++;
						if (o == 100000000) {
							EData(1000);
							goto Eout;
						}
						goto Eloop;
					}
					if (!(EV < his + 3)) {
						nLOOP[XX] = 1;
					}
					EData(XX);
				Eout:
					o = 1;
				}

				/**goto�����g���Ă��܂��B���ӁI**/

				/////////////////////////////////////////////////////////////

				for (q = 0; q < 5; q++) {

					for (o = 0; o < his; o++) {
						stockPrices[q][o] = stockPrices[q][o + 1];
					}

					wsprintf((LPWSTR)szPR[0], TEXT("�����G%d"), stockPrices[q][his - 1] - spread[q]);

					for (o = 0; o < his; o++) {
						if (o == 0) {
							maxStockPriceInPeriod = stockPrices[q][o];
						}
						else if (stockPrices[q][o] > maxStockPriceInPeriod) {
							maxStockPriceInPeriod = stockPrices[q][o];
						}
					}

					for (o = 0; o < his; o++) {
						if (o == 0) {
							minStockPriceInPeriod = stockPrices[q][o];
						}
						else if (stockPrices[q][o] < minStockPriceInPeriod) {
							minStockPriceInPeriod = stockPrices[q][o];
						}
					}

					if (maxStockPriceInPeriod != minStockPriceInPeriod) {
						if (q < 2) {
							for (o = 0; o < his; o++) {
								i = (stockPrices[q][o] - minStockPriceInPeriod) * 100 / (maxStockPriceInPeriod - minStockPriceInPeriod) * ((clientRectangle.bottom / 2 - clientRectangle.bottom / 30) - (rc0.bottom + clientRectangle.bottom / 30));
								stockPriceChartGraphPoint[q][o].y = clientRectangle.bottom / 2 - clientRectangle.bottom / 30 - i / 100;
							}
						}
						else {
							for (o = 0; o < his; o++) {
								i = (stockPrices[q][o] - minStockPriceInPeriod) * 100 / (maxStockPriceInPeriod - minStockPriceInPeriod) * ((clientRectangle.bottom / 2 - clientRectangle.bottom / 30) - (rc0.bottom + clientRectangle.bottom / 30));
								stockPriceChartGraphPoint[q][o].y = clientRectangle.bottom / 2 - clientRectangle.bottom / 30 - i / 100 + clientRectangle.bottom / 2;
							}
						}
					}
					else {
						if (q < 2) {
							for (o = 0; o < his; o++) {
								stockPriceChartGraphPoint[q][o].y = (rc3.bottom - rc3.top) / 2 + rc3.top;
							}
						}
						else {
							for (o = 0; o < his; o++) {
								stockPriceChartGraphPoint[q][o].y = (rc3.bottom - rc3.top) / 2 + rc3.top + clientRectangle.bottom / 2;
							}
						}
					}

					wsprintf(szPR[q * 2 + 15], TEXT("%d"), maxStockPriceInPeriod);
					wsprintf(szPR[q * 2 + 16], TEXT("%d"), minStockPriceInPeriod);

				}

				currentRemainingTime = limitedTime;

				/*Unknown*/
				stockPrices[0][his] = stockPrices[0][his - 1] + companyAStockPriceChangeAmount;
				stockPrices[1][his] = stockPrices[1][his - 1] + companyBStockPriceChangeAmount;
				stockPrices[2][his] = stockPrices[2][his - 1] + companyCStockPriceChangeAmount;
				stockPrices[3][his] = stockPrices[3][his - 1] + companyDStockPriceChangeAmount;
				stockPrices[4][his] = stockPrices[4][his - 1] + companyEStockPriceChangeAmount;

				/*Unknown*/

				/*�ב�+�j���[�X�܂Ƃ�start*/

				for (o = 0; o < 5; o++) {
					q = stockPrices[o][HH] % 1000;
					if (q >= 500) {
						stockPrices[o][HH] += 1000;
					}
					stockPrices[o][HH] -= q;
				}

				if (EV < his + 3) {
					for (o = 0; o < 5; o++) {
						if (stockPrices[o][HH] < 12000) {
							stockPrices[o][HH] = 12000;
						}
					}

					for (o = 0; o < 5; o++) {
						if (stockPrices[o][HH] > 18000) {
							stockPrices[o][HH] = 18000;
						}
					}

				}
				if (EV > HH - 2) {
					for (o = 0; o < 5; o++) {
						if (stockPrices[o][his - 1] < 100) {
							AS[o] = 2;
						}
						if (AS[o] > 0) { AS[o]--; }
					}
				}
				int r;
				for (int w = 0; w < 5; w++) {
					if (AS[w] > 0) {
						for (o = 0; o < HH + 1; o++) {
							r = rand() % 4001 - 2000;
							stockPrices[w][o] = 15000 + r;

							q = stockPrices[w][o] % 1000;
							if (q >= 500) {
								stockPrices[w][o] += 1000;
							}
							stockPrices[w][o] -= q;
						}
					}
				}
				/*�ב�+�j���[�X�܂Ƃ�end*/
				/*�ב�end*/
				InvalidateRect(hWnd, NULL, 0);
			}/**currentRemainingTime==0**/
			/*�����E�`���[�g�ړ��̂��߂̃X�N���v�gend*/
		}
		break;
	case WM_CHAR:
		if (wp == VK_ESCAPE) {
			if (XO == 0) XO = 1; InvalidateRect(hWnd, &clientRectangle, 0); break;
			XO = 0;
		}
		if (wp == VK_RETURN) {
			if (limitedTime == 1000) limitedTime -= 1000;
			limitedTime += 10000;
			currentRemainingTime = limitedTime;
			InvalidateRect(hWnd, NULL, 0);

		}
		if (wp == VK_SPACE) {
			limitedTime -= 10000;
			if (limitedTime < 1000) {
				limitedTime = 1000;
			}
			InvalidateRect(hWnd, NULL, 0);
			currentRemainingTime = limitedTime;
		}
		break;
	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}

HFONT MyCreateFont(int nHeight, DWORD dwCharSet, LPCTSTR lpName)
{
	return(CreateFont(nHeight, 0, 0, 0,
		FW_DONTCARE,
		FALSE, FALSE, FALSE,
		dwCharSet,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		lpName));
}

void Data(int XX) {
	if (EV < his + 3) {
		companyAStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyBStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyCStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyDStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyEStockPriceChangeAmount = (rand() % 7 - 3) * 700;


	}
	else {
		if (XX == 0) {
			wsprintf(S, TEXT("�{�B�Ƌ�B�����ԐV������������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 1) {
			wsprintf(S, TEXT("��C�g���t�n�k������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -0;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -4000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 2) {
			wsprintf(S, TEXT("�^�C�ő�^��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -4000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 3) {
			wsprintf(S, TEXT("���{�S���ŕĂ��s��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 4) {
			wsprintf(S, TEXT("���m���ɋ���䕗���㗤"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 5) {
			wsprintf(S, TEXT("�n���C�ő�K�͂ȉΎR����"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 6) {
			wsprintf(S, TEXT("��B�n���Œn�k������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 7) {
			wsprintf(S, TEXT("���s���W�����J�ő傫�Ȕ�Q"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 8) {
			wsprintf(S, TEXT("���q�����E��Y��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 9) {
			wsprintf(S, TEXT("�x�m�R�����E��Y��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 10) {
			wsprintf(S, TEXT("���{��K���O���l��3000���l�𒴂���"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 6000;
		}
		if (XX == 11) {
			wsprintf(S, TEXT("�ɐ��u���T�~�b�g���J��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 12) {
			wsprintf(S, TEXT("�t�����X�Ńe��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -4000;
		}
		if (XX == 13) {
			wsprintf(S, TEXT("�d�C�������l�グ"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 14) {
			wsprintf(S, TEXT("�Ζ��̒l�i���オ��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 15) {
			wsprintf(S, TEXT("�Ζ��̒l�i��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 16) {
			wsprintf(S, TEXT("�S�̒l�i���オ��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 17) {
			wsprintf(S, TEXT("�S�̒l�i��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 18) {
			wsprintf(S, TEXT("���N�̓~�͒g�~�ɂȂ�Ɨ\�z"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 19) {
			wsprintf(S, TEXT("���N�̉Ă͉ߋ��ō��̖ҏ��ɂȂ�Ɨ\�z"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 2000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 20) {
			wsprintf(S, TEXT("�k���V�������J��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 21) {
			wsprintf(S, TEXT("�C�O�œ��{�H�u�[��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 22) {
			wsprintf(S, TEXT("���{�𕑑�ɂ����f�B�Y�j�[�f�悪��q�b�g"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 23) {
			wsprintf(S, TEXT("�n���C�Ńe��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 24) {
			wsprintf(S, TEXT("�h���[���̐V�Z�p���J��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 25) {
			wsprintf(S, TEXT("�ѐD�\���I�����s�b�N�ŋ����_��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 5000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 26) {
			wsprintf(S, TEXT("�����̌R�͂Ɠ��{�̋��D���Փ�"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 27) {
			wsprintf(S, TEXT("���{�C�ő�ʂ̐Ζ�������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 2000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 28) {
			wsprintf(S, TEXT("�x�m�R���΂̊댯�����܂�"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 29) {
			wsprintf(S, TEXT("�����œ��{���i����u�[��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 4000;
			companyCStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 30) {
			wsprintf(S, TEXT("�����l�̔����������s"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 3000;
			companyEStockPriceChangeAmount = 5000;
		}
		if (XX == 31) {
			wsprintf(S, TEXT("�񑊂������_�ЎQ�q"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -4000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 32) {
			wsprintf(S, TEXT("�u�Ζ���20�N��ɖ����Ȃ�v�ƍ��A�����\"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 33) {
			wsprintf(S, TEXT("���������j���𗝗R�ɓ����Ԃ̉����𐧌�"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -4000;
			companyBStockPriceChangeAmount = -4000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -6000;
		}
		if (XX == 34) {
			wsprintf(S, TEXT("���{�Œ��ؗ�������u�[��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 35) {
			wsprintf(S, TEXT("�C�^���A�ő�n�k������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 36) {
			wsprintf(S, TEXT("����ł�15���ɑ���"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 37) {
			wsprintf(S, TEXT("�؍��ŐV�^�C���t���G���U���嗬�s"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 38) {
			wsprintf(S, TEXT("�{�B�ő�K�͂Ȓ�d"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -3000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 39) {
			wsprintf(S, TEXT("�T�b�J�[���[���h�J�b�v�����ŊJ��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 40) {
			wsprintf(S, TEXT("�L���œy���ЊQ"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 41) {
			wsprintf(S, TEXT("�G�{���o���M�����[���b�p�ő嗬�s"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -5000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -7000;
		}
		if (XX == 42) {
			wsprintf(S, TEXT("�������H������������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 43) {
			wsprintf(S, TEXT("�V�����̎��̂�������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 44) {
			wsprintf(S, TEXT("�k���N�̃~�T�C�����_�ސ쌧���ɗ���"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -3000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 45) {
			wsprintf(S, TEXT("��쓮�����Ńp���_�̐Ԃ���񂪐��܂��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 46) {
			wsprintf(S, TEXT("�x�������ꂪ���E��Y��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 47) {
			wsprintf(S, TEXT("���j�A���[�^�[�J�[���J��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 48) {
			wsprintf(S, TEXT("���c���ۋ�`�̍��ې���2�{�ɑ�����"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 5000;
		}
		if (XX == 49) {
			wsprintf(S, TEXT("�����ő�K�͂Ȕ����{�f��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 50) {
			wsprintf(S, TEXT("�C���h�̓��H�����������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 2000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 51) {
			wsprintf(S, TEXT("�A�����J���u30�N��CO2�r�o�ʂ𔼕��ɂ���v�Ɣ��\"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 7000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 52) {
			wsprintf(S, TEXT("��؂̉��i����N��2�{��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 53) {
			wsprintf(S, TEXT("�f���O�M�̑嗬�s�ɂ�蓌��A�W�A�ւ̓n�q������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 54) {
			wsprintf(S, TEXT("�\�}���A�̊C��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 2000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 55) {
			wsprintf(S, TEXT("���{�̐l��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 4000;
			companyCStockPriceChangeAmount = 4000;
			companyDStockPriceChangeAmount = 3000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 56) {
			wsprintf(S, TEXT("�D�y�I�����s�b�N�J�Â�����"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 4000;
			companyBStockPriceChangeAmount = 3000;
			companyCStockPriceChangeAmount = 2000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 57) {
			wsprintf(S, TEXT("�����X�J�C�c���[�����̂ɂ��c�Ƃ��~"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 58) {
			wsprintf(S, TEXT("�K�\�����ł��p�~"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 4000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 59) {
			wsprintf(S, TEXT("�f�B�Y�j�[�����h�Ƀ��j���[�A���I�[�v��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 0000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 60) {
			wsprintf(S, TEXT("�Ζ��̐V�����̌@���@���J��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 3000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 61) {
			wsprintf(S, TEXT("�R��s�����Ń��[���b�p�̑�莩���ԃ��[�J�[���|�Y"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 62) {
			wsprintf(S, TEXT("�A�����J�̑哝�̂��L���K��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 63) {
			wsprintf(S, TEXT("�R�[�q�[���̒l�i��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 2000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 64) {
			wsprintf(S, TEXT("���A���u�r�C�K�X��40�N�Ԃ�50���팸����v�Ɣ��\"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 6000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 65) {
			wsprintf(S, TEXT("�A�����J�ŔE�҃u�[��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 66) {
			wsprintf(S, TEXT("�����ő�K�͂Ȕ����f��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 67) {
			wsprintf(S, TEXT("���[���b�p�œ��{�̃t�@�b�V����������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 5000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 68) {
			wsprintf(S, TEXT("�V�������Z�ꂪ����"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 5000;
			companyCStockPriceChangeAmount = 5000;
			companyDStockPriceChangeAmount = 5000;
			companyEStockPriceChangeAmount = 5000;
		}
		if (XX == 69) {
			wsprintf(S, TEXT("���{���u50�N�Ԃœ��{�̎Ԃ̔������G�R�J�[�ɂ���v�Ɣ��\"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 7000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 70) {
			wsprintf(S, TEXT("����A�W�A�Œቿ�i�̗m�������s"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 4000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 71) {
			wsprintf(S, TEXT("�u�`���R���[�g������\�h�ɂȂ�v�Ƃ����������ʂ����\"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 72) {
			wsprintf(S, TEXT("�A�����J�łƂ񂱂��[��������q�b�g"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 73) {
			wsprintf(S, TEXT("�Ⓚ�H�i�ɂ��H���ł�����"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 74) {
			wsprintf(S, TEXT("�X�^�[�E�H�[�Y�̐V�삪���J"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 75) {
			wsprintf(S, TEXT("����Ƃ�����̌l���𗬏o"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 76) {
			wsprintf(S, TEXT("���{�̉��ϕi�̐V���i���A�W�A�Ńq�b�g"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 77) {
			wsprintf(S, TEXT("�T�E�W�A���r�A�Ŏ����e��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 78) {
			wsprintf(S, TEXT("�����̐l����オ��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 79) {
			wsprintf(S, TEXT("�ʉَq���[�J�[�̏ܖ������U�������o"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = -5000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 80) {
			wsprintf(S, TEXT("���{�̃I�����s�b�N�I�肪�����h�_��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 81) {
			wsprintf(S, TEXT("�l�H�m�\�̊J���������Ƃւ̕⏕�����x������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 4000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 82) {
			wsprintf(S, TEXT("�A�����J���{���C�O����̗A����啝�ɐ���"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -7000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 83) {
			wsprintf(S, TEXT("�K�\�������啝�ɒl�グ"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 84) {
			wsprintf(S, TEXT("�����ɏ�蕨�����ق��I�[�v��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 85) {
			wsprintf(S, TEXT("�����Ńs�J�\�W���J��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 86) {
			wsprintf(S, TEXT("���S��̖�肩��h���[���̎g�p���֎~��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 87) {
			wsprintf(S, TEXT("���Ő��c��`�̔�s�@��1�������q"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -4000;
		}
		if (XX == 88) {
			wsprintf(S, TEXT("�����ŉΎR������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -4000;
		}
		if (XX == 89) {
			wsprintf(S, TEXT("�؍��̑哝�̂��|���ɏ㗤"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 90) {
			wsprintf(S, TEXT("�k�C���V�������J��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 91) {
			wsprintf(S, TEXT("�}�O������N��2�{����"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 92) {
			wsprintf(S, TEXT("�t�B���s���ŌR���N�[�f�^�[������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 93) {
			wsprintf(S, TEXT("�{�B�ɂ��E�i�M�̑�ʐ��Y���n�܂�"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 94) {
			wsprintf(S, TEXT("���É��`��2�{�ɍL����"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 6000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 95) {
			wsprintf(S, TEXT("�����̓o�����^�C���f�[��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 96) {
			wsprintf(S, TEXT("�����̉��i��������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 97) {
			wsprintf(S, TEXT("�����̉��i���オ��"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 98) {
			wsprintf(S, TEXT("�{�B�Ƌ�B�����ԐV������������"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		NE = XX;

		if (XX == 1000) {
			wsprintf(S, TEXT("�Ō�̊�����\�����Ă��܂��B"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			//KillTimer(hWnd,ID_MYTIMER2);
		}

	}



	return;
}

void EData(int XX) {
	if (EV < his + 3) {
		companyAStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyBStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyCStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyDStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyEStockPriceChangeAmount = (rand() % 7 - 3) * 700;


	}
	else {
		companyAStockPriceChangeAmount = 0;
		companyBStockPriceChangeAmount = 0;
		companyDStockPriceChangeAmount = 0;
		if (XX == 0) {
			wsprintf(S, TEXT("�X�[�p�[�n�C�u���b�h�Ԃ��J�����ꂽ�I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 2000;
		}
		if (XX == 1) {
			wsprintf(S, TEXT("���������Ɨ₽���Ȃ�u�X�[�p�[�N�[���V���c�v���J�����ꂽ�I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyDStockPriceChangeAmount = 2000;

		}
		if (XX == 2) {
			wsprintf(S, TEXT("���ׂĂ̍��w�r���ɐk�x7�ɑς���ϐk�H�����`���t����@�����ł����I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyBStockPriceChangeAmount = 2000;
		}
		if (XX == 3) {
			wsprintf(S, TEXT("����C��n�k���N���Ė��É����S�̉��ݕ�����œI�Ȕ�Q���󂯂��I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -4000;
			companyBStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
		}
		if (XX == 4) {
			wsprintf(S, TEXT("���z���œ����\�[���[�����Ԃ��������ꂽ�I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 2000;
		}
		if (XX == 5) {
			wsprintf(S, TEXT("���E�I�Ɍi�C���ǂ��Ȃ����I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 3000;
			companyBStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = -1000;
		}
		if (XX == 6) {
			wsprintf(S, TEXT("�~���ɂȂ����I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = -2000;
		}
		if (XX == 7) {
			wsprintf(S, TEXT("�����Ɠ��{�̊֌W���������A��؂̖f�Ղ���~�����I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -8000;
		}
		if (XX == 8) {
			wsprintf(S, TEXT("�����ł��オ�����I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
		}
		if (XX == 9) {
			wsprintf(S, TEXT("�}���ȉ~���ɂȂ����I"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = 0;
			companyDStockPriceChangeAmount = 2000;
		}
		if (XX == 1000) {
			wsprintf(S, TEXT("�Ō�̊�����\�����Ă��܂��B"), XX);
			wsprintf(Sb, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
			KillTimer(hWnd, ID_MYTIMER2);
		}
	}
	return;
}

void Ftime(int companyAStockPriceChangeAmount, HWND hWnd, RECT clientRectangle, HDC hdc) {

	HPEN hPen, hPen2, hPen3;
	HBRUSH hBrush, hBrushW, hBrushT;
	RECT rc0, rc1, rc2, rc3, rc4, rc6;
	TCHAR szPRL[5][10];
	int o, i, q;

	hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hBrushW = (HBRUSH)GetStockObject(WHITE_BRUSH);
	hBrushT = (HBRUSH)GetStockObject(DC_BRUSH);
	hPen3 = (HPEN)GetStockObject(NULL_PEN);
	hPen2 = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	int Tr = 0, Tg = 0, Tb = 0;

	if (companyAStockPriceChangeAmount != 6) {
		SelectObject(hdc, hBrush);

		if (companyAStockPriceChangeAmount == 1) {
			rc0.left = 0;
			rc0.top = clientRectangle.bottom / 16;
			rc0.right = clientRectangle.right / number;
			rc0.bottom = clientRectangle.bottom / 9;
			rc1.left = rc0.right;
			rc1.top = rc0.top;
			rc1.right = clientRectangle.right / number * 2;
			rc1.bottom = rc0.bottom;
			rc2.top = 2;
			rc2.left = 2;
			rc2.bottom = rc0.top - clientRectangle.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + clientRectangle.bottom / 40;
			rc3.left = rc0.left + clientRectangle.right / 40;
			rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40;
			rc3.right = rc1.right - clientRectangle.right / 40;
			wsprintf((LPWSTR)szPRL[2], TEXT("�g���^������"));
			Tr = 204;
		}
		if (companyAStockPriceChangeAmount == 2) {

			rc0.left = clientRectangle.right * 2 / 3;
			rc0.top = clientRectangle.bottom / 16;
			rc0.right = clientRectangle.right * 2 / 3 + clientRectangle.right / number;
			rc0.bottom = clientRectangle.bottom / 9;
			rc1.left = clientRectangle.right * 2 / 3 + clientRectangle.right / number;
			rc1.top = clientRectangle.bottom / 16;
			rc1.right = clientRectangle.right * 2 / 3 + clientRectangle.right / number * 2;
			rc1.bottom = rc0.bottom;
			rc2.top = 2;
			rc2.left = 2 + clientRectangle.right * 2 / 3;
			rc2.bottom = rc0.top - clientRectangle.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + clientRectangle.bottom / 40;
			rc3.left = rc0.left + clientRectangle.right / 40;
			rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40;
			rc3.right = rc1.right - clientRectangle.right / 40;
			wsprintf((LPWSTR)szPRL[2], TEXT("���j�N��"));
			if (DQ == 1) { wsprintf((LPWSTR)szPRL[2], TEXT("��������")); }
			Tr = 255;
			Tg = 255;
		}
		if (companyAStockPriceChangeAmount == 3) {
			rc0.left = 0;
			rc0.top = clientRectangle.bottom / 16 + clientRectangle.bottom / 2;
			rc0.right = clientRectangle.right / number;
			rc0.bottom = clientRectangle.bottom / 9 + clientRectangle.bottom / 2;
			rc1.left = rc0.right;
			rc1.top = clientRectangle.bottom / 16 + clientRectangle.bottom / 2;
			rc1.right = clientRectangle.right / number * 2;
			rc1.bottom = clientRectangle.bottom / 9 + clientRectangle.bottom / 2;
			rc2.top = 2 + clientRectangle.bottom / 2;
			rc2.left = 2;
			rc2.bottom = rc0.top - clientRectangle.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + clientRectangle.bottom / 40;
			rc3.left = rc0.left + clientRectangle.right / 40;
			rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40 + clientRectangle.bottom / 2;
			rc3.right = rc1.right - clientRectangle.right / 40;
			wsprintf((LPWSTR)szPRL[2], TEXT("�X�i����"));

			Tr = 102;
			Tg = 255;
			Tb = 255;
		}
		if (companyAStockPriceChangeAmount == 4) {
			rc0.left = 0 + clientRectangle.right / 3;
			rc0.top = clientRectangle.bottom / 16 + clientRectangle.bottom / 2;
			rc0.right = clientRectangle.right / number + clientRectangle.right / 3;
			rc0.bottom = clientRectangle.bottom / 9 + clientRectangle.bottom / 2;
			rc1.left = rc0.right;
			rc1.top = rc0.top;
			rc1.right = clientRectangle.right / number * 2 + clientRectangle.right / 3;
			rc1.bottom = rc0.bottom;
			rc2.top = 2 + clientRectangle.bottom / 2;
			rc2.left = 2 + clientRectangle.right / 3;
			rc2.bottom = rc0.top - clientRectangle.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + clientRectangle.bottom / 40;
			rc3.left = rc0.left + clientRectangle.right / 40;
			rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40 + clientRectangle.bottom / 2;
			rc3.right = rc1.right - clientRectangle.right / 40;
			wsprintf((LPWSTR)szPRL[2], TEXT("�C�g�[���[�J�h�["));
			if (DQ == 1) { wsprintf((LPWSTR)szPRL[2], TEXT("���j�N��")); }
			Tr = 51;
			Tg = 204;
		}
		if (companyAStockPriceChangeAmount == 5) {
			rc0.left = clientRectangle.right * 2 / 3;
			rc0.top = clientRectangle.bottom / 16 + clientRectangle.bottom / 2;
			rc0.right = clientRectangle.right * 2 / 3 + clientRectangle.right / number;
			rc0.bottom = clientRectangle.bottom / 9 + clientRectangle.bottom / 2;
			rc1.left = clientRectangle.right * 2 / 3 + clientRectangle.right / number;
			rc1.top = rc0.top;
			rc1.right = clientRectangle.right * 2 / 3 + clientRectangle.right / number * 2;
			rc1.bottom = rc0.bottom;
			rc2.top = 2 + clientRectangle.bottom / 2;
			rc2.left = 2 + clientRectangle.right * 2 / 3;
			rc2.bottom = rc0.top - clientRectangle.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + clientRectangle.bottom / 40;
			rc3.left = rc0.left + clientRectangle.right / 40;
			rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40 + clientRectangle.bottom / 2;
			rc3.right = rc1.right - clientRectangle.right / 40;
			wsprintf((LPWSTR)szPRL[2], TEXT("�i�s�a"));
			Tr = 211;
			Tg = 211;
			Tb = 211;
		}
		SetDCBrushColor(hdc, RGB(Tr, Tg, Tb));

		rc2.left += clientRectangle.right / 15;
		rc2.right -= clientRectangle.right / 15;
		rc2.top += clientRectangle.bottom / 200;
		rc2.top += clientRectangle.bottom / 200;
		rc2.bottom += clientRectangle.bottom / 200;
		wsprintf((LPWSTR)szPRL[0], TEXT("�����G%d"), stockPrices[companyAStockPriceChangeAmount - 1][his - 1]);
		wsprintf((LPWSTR)szPRL[3], szPR[companyAStockPriceChangeAmount * 2 + 13]);
		wsprintf((LPWSTR)szPRL[4], szPR[companyAStockPriceChangeAmount * 2 + 14]);

		/*�����̘g�����X�N���v�g�J�n*/

		for (o = 0; o < his; o++) {
			stockPriceChartGraphPoint[companyAStockPriceChangeAmount - 1][o].x = (rc3.right - rc3.left) / (his) * (o + 1) + rc3.left - clientRectangle.right / 300;
		}

		SelectObject(hdc, hPen);
		for (i = 0; i < 2; i++) {
			for (q = 0; q < number / 2; q++) {
				Rectangle(hdc, clientRectangle.right * q * 2 / number, clientRectangle.bottom * i / 2, clientRectangle.right * (q + 1) * 2 / number, clientRectangle.bottom * (i + 1) / 2);
			}
		}

		/*�����̘g�����X�N���v�g�I��*/
		/*��������start*/

		SelectObject(hdc, hBrushW);
		SelectObject(hdc, hPen3);
		Rectangle(hdc, rc0.left, rc0.top, rc0.right, rc0.bottom);
		Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);

		RECT rc40;
		rc40.left = (rc0.left + rc1.left) / 2;
		rc40.right = (rc0.right + rc1.right) / 2;
		rc40.bottom = (rc0.bottom + rc1.bottom) / 2;
		rc40.top = (rc0.top + rc1.top) / 2;

		RECT rc41;
		rc41.left = rc40.left;
		rc41.right = rc40.right;
		rc41.bottom = rc40.bottom;
		rc41.top = rc40.top + clientRectangle.bottom / 100;

		SelectObject(hdc, hBrushT);

		RoundRect(hdc, rc2.left, rc2.top - clientRectangle.bottom / 200, rc2.right, rc2.bottom, (clientRectangle.right + clientRectangle.bottom) / 50, (clientRectangle.right + clientRectangle.bottom) / 50);

		SelectObject(hdc, hPen);

		SelectObject(hdc, hFont6);

		SelectObject(hdc, hBrush);

		SetTextColor(hdc, RGB(0, 0, 0));

		DrawText(hdc, szPRL[2], -1, &rc2, DT_CENTER);


		SelectObject(hdc, hBrushW);

		SelectObject(hdc, hPen);

		Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);

		SetTextColor(hdc, RGB(0, 0, 255));
		DrawText(hdc, szPRL[0], -1, &rc41, DT_CENTER);

		/*��������end*/

		SelectObject(hdc, hPen2);

		Polyline(hdc, stockPriceChartGraphPoint[companyAStockPriceChangeAmount - 1], HH);
		SelectObject(hdc, hFont3);
		SetTextColor(hdc, RGB(255, 102, 51));
		TextOut(hdc, rc3.right, rc3.top, szPRL[3], lstrlen(szPRL[3]));
		SetTextColor(hdc, RGB(102, 102, 255));
		TextOut(hdc, rc3.right, rc3.bottom - 20, szPRL[4], lstrlen(szPRL[4]));

	}
	if (companyAStockPriceChangeAmount == 6) {
		rc0.left = 0;
		rc0.top = clientRectangle.bottom / 16;
		rc0.right = clientRectangle.right / number;
		rc0.bottom = clientRectangle.bottom / 9;
		rc1.left = rc0.right;
		rc1.top = rc0.top;
		rc1.right = clientRectangle.right / number * 2;
		rc1.bottom = rc0.bottom;
		rc2.top = 2;
		rc2.left = 2;
		rc2.bottom = rc0.top - clientRectangle.bottom / 80;
		rc2.right = rc1.right;
		rc3.top = rc0.bottom + clientRectangle.bottom / 40;
		rc3.left = rc0.left + clientRectangle.right / 80;
		rc3.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 40;
		rc3.right = rc1.right - clientRectangle.right / 80;
		rc4.left = rc1.right + clientRectangle.right / 20;
		rc4.top = clientRectangle.bottom / 60;
		rc4.bottom = rc0.top;
		rc4.right = clientRectangle.right / number * 2 * 2 - clientRectangle.right / 100;
		/*���v����start*/
		TCHAR sur[10];
		SelectObject(hdc, hFont2);
		wsprintf(sur, TEXT("%3d"), currentRemainingTime / 1000);

		SetTextColor(hdc, RGB(0, 51, 0));
		TextOut(hdc, rc1.right + clientRectangle.right / 50, rc4.top + rc4.top * 3 / 4, sur, lstrlen(sur));
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrushW);
		Rectangle(hdc, rc4.left, rc4.top, rc4.right, rc4.bottom);
		hBrush = CreateSolidBrush(RGB(204, 255, 102));
		SelectObject(hdc, hBrush);

		Rectangle(hdc, rc4.left, rc4.top, rc4.right, rc4.bottom);

		SelectObject(hdc, hBrushW);

		Rectangle(hdc, rc4.right - (limitedTime - currentRemainingTime) * (rc4.right - rc4.left) / limitedTime, rc4.top, rc4.right, rc4.bottom);

		/*���v����end*/
		/*�j���[�X����start*/
		SelectObject(hdc, hFont1);
		SetTextColor(hdc, RGB(153, 102, 0));
		TextOut(hdc, rc1.right + clientRectangle.right / 50, rc4.top + rc4.top * 3, TEXT("�`�j���[�X�`"), lstrlen(TEXT("�`�j���[�X�`")));

		rc6.top = rc0.bottom + clientRectangle.bottom / 40;
		rc6.left = rc0.left + clientRectangle.right / 160 + clientRectangle.right / 3;
		rc6.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 10;
		rc6.right = rc1.right - clientRectangle.right / 32 + clientRectangle.right / 3;

		SelectObject(hdc, hFont6);
		DrawText(hdc, S, lstrlen(S), &rc6, DT_CENTER | DT_WORDBREAK);

		SelectObject(hdc, hFont3);
		DrawText(hdc, Sb, lstrlen(Sb), &rc6, DT_CENTER | DT_WORDBREAK);

		rc23.left = clientRectangle.right / 2 + clientRectangle.right / 10;
		rc23.right = clientRectangle.right * 2 / 3 - clientRectangle.right / 30;
		rc23.top = clientRectangle.bottom * 2 / 7;
		rc23.bottom = clientRectangle.bottom / 2 - clientRectangle.bottom / 10;

		rc24.left = clientRectangle.right / 3;
		rc24.right = clientRectangle.right * 3 / 5 - clientRectangle.right / 10;
		rc24.top = clientRectangle.bottom * 2 / 7;
		rc24.bottom = clientRectangle.bottom / 2;

		rc25.left = clientRectangle.right / 2 + clientRectangle.right / 20;
		rc25.right = clientRectangle.right * 2 / 3 + clientRectangle.right / 50;
		rc25.top = clientRectangle.bottom / 2 - clientRectangle.bottom / 10;
		rc25.bottom = clientRectangle.bottom / 2;

		if (DQ != 1) {

			SelectObject(hdc, hBrushW);
			SelectObject(hdc, hPen3);

			Rectangle(hdc, rc23.left, rc23.top, rc23.right, rc23.bottom);

			Rectangle(hdc, rc24.left, rc24.top, rc24.right, rc24.bottom);

			SelectObject(hdc, hPen);
			Ellipse(hdc, rc23.left + (rc23.right - rc23.left) / 2 - ((rc23.bottom - clientRectangle.bottom / 23) - (rc23.top - clientRectangle.bottom / 100)) / 2 - clientRectangle.bottom / 100, rc23.top - clientRectangle.bottom / 100 - clientRectangle.bottom / 100, (rc23.right - rc23.left) / 2 + ((rc23.bottom - clientRectangle.bottom / 23) - (rc23.top - clientRectangle.bottom / 100)) / 2 + rc23.left + clientRectangle.bottom / 100, rc23.bottom - clientRectangle.bottom / 23 + clientRectangle.bottom / 100);

			SelectObject(hdc, hFont5);
			SelectObject(hdc, hPen);

			SetTextColor(hdc, RGB(rR, rG, rB));

			DrawText(hdc, Yrate, lstrlen(Yrate), &rc23, DT_CENTER | DT_WORDBREAK);

			SelectObject(hdc, hFont6);
			SetTextColor(hdc, RGB(102, 51, 255));

			DrawText(hdc, Rate, lstrlen(Rate), &rc24, DT_CENTER | DT_WORDBREAK);

			SetTextColor(hdc, RGB(51, 102, 0));
			SelectObject(hdc, hFont6);

			DrawText(hdc, Urate, lstrlen(Urate), &rc25, DT_CENTER | DT_WORDBREAK);
		}
	}
	if (companyAStockPriceChangeAmount != 6) {
		if (AS[companyAStockPriceChangeAmount - 1] > 0) {
			SelectObject(hdc, hBrushw);
			Rectangle(hdc, rc0.left, rc0.top, rc1.right, rc3.bottom);
			SelectObject(hdc, hFont3);
			wsprintf((LPWSTR)CON, TEXT("\n���̉�Ђ͓|�Y���܂����B\n���̃J�[�h���{�[�h�ɖ߂��Ă��������B"));
			DrawText(hdc, CON, -1, &rc3, DT_CENTER);
		}
	}

	DeleteObject(hBrush);
	DeleteObject(hBrushW);
	DeleteObject(hPen);
	DeleteObject(hPen2);
	return;
}
