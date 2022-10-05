// win01.cpp

#define stockPriceChartGraphPointNumber 10

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
void Ftime(int, RECT, HDC);

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

//���ꂼ��̊�Ƃ̊��� �ꎟ���ڂŊ�Ƃ��w��A�񎟌��ڂŊ��Ԃ��w��
static int stockPrices[5][stockPriceChartGraphPointNumber + 1];

//��ʂɕ\��������Ԃ̐�
const int his = stockPriceChartGraphPointNumber;
static int EV = 0;
TCHAR messageEventTitle[100];
TCHAR messageEventNumber[30];
const static int number = 6;/*�����̐�*/
int spread[5] = { 10, 20, 30, 40, 50 };
static POINT stockPriceChartGraphPoint[5][stockPriceChartGraphPointNumber];
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
TCHAR eachCompanyMaxStockPriceInPeriod[10][10];
TCHAR messageWaitForMinute[] = TEXT("\n������̎���͂ł��܂���B\n���X���҂����������B");
TCHAR messageNextLimitTime[] = TEXT("\n\n\n\n\n����̐������ԁG%d�b");
TCHAR messageCompanyBankruptcy[] = TEXT("\n���̉�Ђ͓|�Y���܂����B\n���̃J�[�h���{�[�h�ɖ߂��Ă��������B");
TCHAR messageLoadingPleaseWait[] = TEXT("\n�ǂݍ��ݒ��ł��B\n���X���҂����������B");
TCHAR messageLoadProgress[] = TEXT("\n\n\n\n\n%d����");

const int nD = 98;
bool nLOOP[130];

bool XO;
HPEN hPen4, hPen5;
int Qw;

static int AS[5];

static HBITMAP hBmp;
BITMAP bmp_info;
static HDC hdc_mem;
int bmpw, bmph;
HPEN hPen10;

//�E�B���h�E�v���V�[�W��
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
			nLOOP[o] = false;
		}
		hPen10 = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		hPen5 = (HPEN)GetStockObject(BLACK_PEN);
		hPen4 = (HPEN)GetStockObject(NULL_PEN);
		hBrushw = (HBRUSH)GetStockObject(WHITE_BRUSH);
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		limitedTime = 10000;
		currentRemainingTime = limitedTime;
		XO = true;
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
		for (o = 0; o < stockPriceChartGraphPointNumber; o++) {
			stockPrices[0][o] = 15000;
		}
		for (o = 0; o < stockPriceChartGraphPointNumber; o++) {
			stockPrices[1][o] = 15000;
		}
		for (o = 0; o < stockPriceChartGraphPointNumber; o++) {
			stockPrices[2][o] = 15000;
		}
		for (o = 0; o < stockPriceChartGraphPointNumber; o++) {
			stockPrices[3][o] = 15000;
		}
		for (o = 0; o < stockPriceChartGraphPointNumber; o++) {
			stockPrices[4][o] = 15000;
		}
		SetTimer(hWnd, ID_MYTIMER, 200, NULL);

		srand((unsigned)time(NULL));

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
		hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, hPen4);
		SelectObject(hdc, hBrushw);
		Rectangle(hdc, clientRectangle.left, clientRectangle.top, clientRectangle.right, clientRectangle.bottom);

		if (!(EV < his + 3)) {
			if (XO) {
				Ftime(1, clientRectangle, hdc);
				Ftime(2, clientRectangle, hdc);
				Ftime(3, clientRectangle, hdc);
				Ftime(5, clientRectangle, hdc);
				Ftime(4, clientRectangle, hdc);
				Ftime(6, clientRectangle, hdc);
			}

			if (!XO) {
				bmph = clientRectangle.bottom / 9;
				bmpw = bmph;
				SelectObject(hdc, hBrushw);
				Rectangle(hdc, clientRectangle.left, clientRectangle.top, clientRectangle.right, clientRectangle.bottom);
				SelectObject(hdc, hFont5);
				wsprintf((LPWSTR)messageWaitForMinute, TEXT("\n������̎���͂ł��܂���B\n���X���҂����������B"));
				DrawText(hdc, messageWaitForMinute, -1, &clientRectangle, DT_CENTER);
				wsprintf((LPWSTR)messageNextLimitTime, TEXT("\n\n\n\n\n����̐������ԁG%d�b"), limitedTime / 1000);
				DrawText(hdc, messageNextLimitTime, -1, &clientRectangle, DT_CENTER);

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
			}
		}
		SelectObject(hdc, hBrush);

		if (EV < his + 3) {
			SelectObject(hdc, hBrushw);

			Rectangle(hdc, clientRectangle.left, clientRectangle.top, clientRectangle.right, clientRectangle.bottom);
			SelectObject(hdc, hPen5);
			SelectObject(hdc, hFont5);
			wsprintf((LPWSTR)messageLoadingPleaseWait, TEXT("\n�ǂݍ��ݒ��ł��B\n���X���҂����������B"));
			DrawText(hdc, messageLoadingPleaseWait, -1, &clientRectangle, DT_CENTER);
			wsprintf((LPWSTR)messageLoadProgress, TEXT("\n\n\n\n\n%d������"), Qw * 100 / (his + 1 + limitedTime / 1000));
			DrawText(hdc, messageLoadProgress, -1, &clientRectangle, DT_CENTER);
		}
		EndPaint(hWnd, &ps);

		break;
	case WM_TIMER:
		if (EV == his + 3) {
			KillTimer(hWnd, ID_MYTIMER);
			SetTimer(hWnd, ID_MYTIMER2, 1000, NULL);
		}
		Qw++;

		if (XO) {

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
					XO = false;
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

			loop:
				XX = rand() % nD;

				/*if (XX == 108) {
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
				}*/


				if (nLOOP[XX] == true) {
					o++;
					if (o == 1000000) {
						Data(1000);
						goto out;
					}
					goto loop;
				}
				if (!(EV < his + 3)) {
					nLOOP[XX] = true;
					if (NE == 36) {
						Data(34);
						nLOOP[34] = true;
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
				/**goto�����g���Ă��܂��B���ӁI**/

				/////////////////////////////////////////////////////////////

				for (q = 0; q < 5; q++) {

					for (o = 0; o < his; o++) {
						stockPrices[q][o] = stockPrices[q][o + 1];
					}

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

					wsprintf(eachCompanyMaxStockPriceInPeriod[q * 2], TEXT("%d"), maxStockPriceInPeriod);
					wsprintf(eachCompanyMaxStockPriceInPeriod[q * 2], TEXT("%d"), minStockPriceInPeriod);

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
					q = stockPrices[o][stockPriceChartGraphPointNumber] % 1000;
					if (q >= 500) {
						stockPrices[o][stockPriceChartGraphPointNumber] += 1000;
					}
					stockPrices[o][stockPriceChartGraphPointNumber] -= q;
				}

				if (EV < his + 3) {
					for (o = 0; o < 5; o++) {
						if (stockPrices[o][stockPriceChartGraphPointNumber] < 12000) {
							stockPrices[o][stockPriceChartGraphPointNumber] = 12000;
						}
					}

					for (o = 0; o < 5; o++) {
						if (stockPrices[o][stockPriceChartGraphPointNumber] > 18000) {
							stockPrices[o][stockPriceChartGraphPointNumber] = 18000;
						}
					}

				}
				if (EV > stockPriceChartGraphPointNumber - 2) {
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
						for (o = 0; o < stockPriceChartGraphPointNumber + 1; o++) {
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
			if (!XO) XO = true; InvalidateRect(hWnd, &clientRectangle, 0); break;
			XO = false;
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

void Data(const int XX) {
	if (EV < his + 3) {
		companyAStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyBStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyCStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyDStockPriceChangeAmount = (rand() % 7 - 3) * 700;
		companyEStockPriceChangeAmount = (rand() % 7 - 3) * 700;


	}
	else {
		if (XX == 0) {
			wsprintf(messageEventTitle, TEXT("�{�B�Ƌ�B�����ԐV������������"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 1) {
			wsprintf(messageEventTitle, TEXT("��C�g���t�n�k������"));
			companyAStockPriceChangeAmount = -0;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -4000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 2) {
			wsprintf(messageEventTitle, TEXT("�^�C�ő�^��������"));
			companyAStockPriceChangeAmount = -4000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 3) {
			wsprintf(messageEventTitle, TEXT("���{�S���ŕĂ��s��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 4) {
			wsprintf(messageEventTitle, TEXT("���m���ɋ���䕗���㗤"));
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 5) {
			wsprintf(messageEventTitle, TEXT("�n���C�ő�K�͂ȉΎR����"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 6) {
			wsprintf(messageEventTitle, TEXT("��B�n���Œn�k������"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 7) {
			wsprintf(messageEventTitle, TEXT("���s���W�����J�ő傫�Ȕ�Q"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 8) {
			wsprintf(messageEventTitle, TEXT("���q�����E��Y��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 9) {
			wsprintf(messageEventTitle, TEXT("�x�m�R�����E��Y��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 10) {
			wsprintf(messageEventTitle, TEXT("���{��K���O���l��3000���l�𒴂���"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 6000;
		}
		if (XX == 11) {
			wsprintf(messageEventTitle, TEXT("�ɐ��u���T�~�b�g���J��"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 12) {
			wsprintf(messageEventTitle, TEXT("�t�����X�Ńe��"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -4000;
		}
		if (XX == 13) {
			wsprintf(messageEventTitle, TEXT("�d�C�������l�グ"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 14) {
			wsprintf(messageEventTitle, TEXT("�Ζ��̒l�i���オ��"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 15) {
			wsprintf(messageEventTitle, TEXT("�Ζ��̒l�i��������"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 16) {
			wsprintf(messageEventTitle, TEXT("�S�̒l�i���オ��"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 17) {
			wsprintf(messageEventTitle, TEXT("�S�̒l�i��������"));
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 18) {
			wsprintf(messageEventTitle, TEXT("���N�̓~�͒g�~�ɂȂ�Ɨ\�z"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 19) {
			wsprintf(messageEventTitle, TEXT("���N�̉Ă͉ߋ��ō��̖ҏ��ɂȂ�Ɨ\�z"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 2000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 20) {
			wsprintf(messageEventTitle, TEXT("�k���V�������J��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 21) {
			wsprintf(messageEventTitle, TEXT("�C�O�œ��{�H�u�[��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 22) {
			wsprintf(messageEventTitle, TEXT("���{�𕑑�ɂ����f�B�Y�j�[�f�悪��q�b�g"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 23) {
			wsprintf(messageEventTitle, TEXT("�n���C�Ńe��"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 24) {
			wsprintf(messageEventTitle, TEXT("�h���[���̐V�Z�p���J��"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 25) {
			wsprintf(messageEventTitle, TEXT("�ѐD�\���I�����s�b�N�ŋ����_��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 5000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 26) {
			wsprintf(messageEventTitle, TEXT("�����̌R�͂Ɠ��{�̋��D���Փ�"));
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 27) {
			wsprintf(messageEventTitle, TEXT("���{�C�ő�ʂ̐Ζ�������"));
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 2000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 28) {
			wsprintf(messageEventTitle, TEXT("�x�m�R���΂̊댯�����܂�"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 29) {
			wsprintf(messageEventTitle, TEXT("�����œ��{���i����u�[��"));
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 4000;
			companyCStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 30) {
			wsprintf(messageEventTitle, TEXT("�����l�̔����������s"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 3000;
			companyEStockPriceChangeAmount = 5000;
		}
		if (XX == 31) {
			wsprintf(messageEventTitle, TEXT("�񑊂������_�ЎQ�q"));
			companyAStockPriceChangeAmount = -4000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 32) {
			wsprintf(messageEventTitle, TEXT("�u�Ζ���20�N��ɖ����Ȃ�v�ƍ��A�����\"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -5000;
		}
		if (XX == 33) {
			wsprintf(messageEventTitle, TEXT("���������j���𗝗R�ɓ����Ԃ̉����𐧌�"));
			companyAStockPriceChangeAmount = -4000;
			companyBStockPriceChangeAmount = -4000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -6000;
		}
		if (XX == 34) {
			wsprintf(messageEventTitle, TEXT("���{�Œ��ؗ�������u�[��"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 35) {
			wsprintf(messageEventTitle, TEXT("�C�^���A�ő�n�k������"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 36) {
			wsprintf(messageEventTitle, TEXT("����ł�15���ɑ���"));
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 37) {
			wsprintf(messageEventTitle, TEXT("�؍��ŐV�^�C���t���G���U���嗬�s"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 38) {
			wsprintf(messageEventTitle, TEXT("�{�B�ő�K�͂Ȓ�d"));
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -3000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 39) {
			wsprintf(messageEventTitle, TEXT("�T�b�J�[���[���h�J�b�v�����ŊJ��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 40) {
			wsprintf(messageEventTitle, TEXT("�L���œy���ЊQ"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 41) {
			wsprintf(messageEventTitle, TEXT("�G�{���o���M�����[���b�p�ő嗬�s"));
			companyAStockPriceChangeAmount = -5000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -7000;
		}
		if (XX == 42) {
			wsprintf(messageEventTitle, TEXT("�������H������������"));
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 43) {
			wsprintf(messageEventTitle, TEXT("�V�����̎��̂�������"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 44) {
			wsprintf(messageEventTitle, TEXT("�k���N�̃~�T�C�����_�ސ쌧���ɗ���"));
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -3000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 45) {
			wsprintf(messageEventTitle, TEXT("��쓮�����Ńp���_�̐Ԃ���񂪐��܂��"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 46) {
			wsprintf(messageEventTitle, TEXT("�x�������ꂪ���E��Y��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 47) {
			wsprintf(messageEventTitle, TEXT("���j�A���[�^�[�J�[���J��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 48) {
			wsprintf(messageEventTitle, TEXT("���c���ۋ�`�̍��ې���2�{�ɑ�����"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 5000;
		}
		if (XX == 49) {
			wsprintf(messageEventTitle, TEXT("�����ő�K�͂Ȕ����{�f��"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 50) {
			wsprintf(messageEventTitle, TEXT("�C���h�̓��H�����������"));
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 2000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 51) {
			wsprintf(messageEventTitle, TEXT("�A�����J���u30�N��CO2�r�o�ʂ𔼕��ɂ���v�Ɣ��\"));
			companyAStockPriceChangeAmount = 7000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 52) {
			wsprintf(messageEventTitle, TEXT("��؂̉��i����N��2�{��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 53) {
			wsprintf(messageEventTitle, TEXT("�f���O�M�̑嗬�s�ɂ�蓌��A�W�A�ւ̓n�q������"));
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 54) {
			wsprintf(messageEventTitle, TEXT("�\�}���A�̊C��������"));
			companyAStockPriceChangeAmount = 2000;
			companyBStockPriceChangeAmount = 2000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 55) {
			wsprintf(messageEventTitle, TEXT("���{�̐l��������"));
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 4000;
			companyCStockPriceChangeAmount = 4000;
			companyDStockPriceChangeAmount = 3000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 56) {
			wsprintf(messageEventTitle, TEXT("�D�y�I�����s�b�N�J�Â�����"));
			companyAStockPriceChangeAmount = 4000;
			companyBStockPriceChangeAmount = 3000;
			companyCStockPriceChangeAmount = 2000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 57) {
			wsprintf(messageEventTitle, TEXT("�����X�J�C�c���[�����̂ɂ��c�Ƃ��~"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 58) {
			wsprintf(messageEventTitle, TEXT("�K�\�����ł��p�~"));
			companyAStockPriceChangeAmount = 4000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 4000;
		}
		if (XX == 59) {
			wsprintf(messageEventTitle, TEXT("�f�B�Y�j�[�����h�Ƀ��j���[�A���I�[�v��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 0000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 60) {
			wsprintf(messageEventTitle, TEXT("�Ζ��̐V�����̌@���@���J��"));
			companyAStockPriceChangeAmount = 3000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 61) {
			wsprintf(messageEventTitle, TEXT("�R��s�����Ń��[���b�p�̑�莩���ԃ��[�J�[���|�Y"));
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 62) {
			wsprintf(messageEventTitle, TEXT("�A�����J�̑哝�̂��L���K��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 63) {
			wsprintf(messageEventTitle, TEXT("�R�[�q�[���̒l�i��������"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 2000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 64) {
			wsprintf(messageEventTitle, TEXT("���A���u�r�C�K�X��40�N�Ԃ�50���팸����v�Ɣ��\"));
			companyAStockPriceChangeAmount = 6000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 65) {
			wsprintf(messageEventTitle, TEXT("�A�����J�ŔE�҃u�[��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 66) {
			wsprintf(messageEventTitle, TEXT("�����ő�K�͂Ȕ����f��"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 67) {
			wsprintf(messageEventTitle, TEXT("���[���b�p�œ��{�̃t�@�b�V����������"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 5000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 68) {
			wsprintf(messageEventTitle, TEXT("�V�������Z�ꂪ����"));
			companyAStockPriceChangeAmount = 5000;
			companyBStockPriceChangeAmount = 5000;
			companyCStockPriceChangeAmount = 5000;
			companyDStockPriceChangeAmount = 5000;
			companyEStockPriceChangeAmount = 5000;
		}
		if (XX == 69) {
			wsprintf(messageEventTitle, TEXT("���{���u50�N�Ԃœ��{�̎Ԃ̔������G�R�J�[�ɂ���v�Ɣ��\"));
			companyAStockPriceChangeAmount = 7000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 70) {
			wsprintf(messageEventTitle, TEXT("����A�W�A�Œቿ�i�̗m�������s"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 4000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 71) {
			wsprintf(messageEventTitle, TEXT("�u�`���R���[�g������\�h�ɂȂ�v�Ƃ����������ʂ����\"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 72) {
			wsprintf(messageEventTitle, TEXT("�A�����J�łƂ񂱂��[��������q�b�g"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 73) {
			wsprintf(messageEventTitle, TEXT("�Ⓚ�H�i�ɂ��H���ł�����"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 74) {
			wsprintf(messageEventTitle, TEXT("�X�^�[�E�H�[�Y�̐V�삪���J"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 75) {
			wsprintf(messageEventTitle, TEXT("����Ƃ�����̌l���𗬏o"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -2000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 76) {
			wsprintf(messageEventTitle, TEXT("���{�̉��ϕi�̐V���i���A�W�A�Ńq�b�g"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 77) {
			wsprintf(messageEventTitle, TEXT("�T�E�W�A���r�A�Ŏ����e��������"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -2000;
		}
		if (XX == 78) {
			wsprintf(messageEventTitle, TEXT("�����̐l����オ��"));
			companyAStockPriceChangeAmount = -2000;
			companyBStockPriceChangeAmount = -3000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 79) {
			wsprintf(messageEventTitle, TEXT("�ʉَq���[�J�[�̏ܖ������U�������o"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = -5000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 80) {
			wsprintf(messageEventTitle, TEXT("���{�̃I�����s�b�N�I�肪�����h�_��"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 1000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 81) {
			wsprintf(messageEventTitle, TEXT("�l�H�m�\�̊J���������Ƃւ̕⏕�����x������"));
			companyAStockPriceChangeAmount = 4000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 82) {
			wsprintf(messageEventTitle, TEXT("�A�����J���{���C�O����̗A����啝�ɐ���"));
			companyAStockPriceChangeAmount = -7000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 83) {
			wsprintf(messageEventTitle, TEXT("�K�\�������啝�ɒl�グ"));
			companyAStockPriceChangeAmount = -3000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -2000;
			companyDStockPriceChangeAmount = -3000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 84) {
			wsprintf(messageEventTitle, TEXT("�����ɏ�蕨�����ق��I�[�v��"));
			companyAStockPriceChangeAmount = 1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 1000;
		}
		if (XX == 85) {
			wsprintf(messageEventTitle, TEXT("�����Ńs�J�\�W���J��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 86) {
			wsprintf(messageEventTitle, TEXT("���S��̖�肩��h���[���̎g�p���֎~��"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 87) {
			wsprintf(messageEventTitle, TEXT("���Ő��c��`�̔�s�@��1�������q"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -4000;
		}
		if (XX == 88) {
			wsprintf(messageEventTitle, TEXT("�����ŉΎR������"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -4000;
		}
		if (XX == 89) {
			wsprintf(messageEventTitle, TEXT("�؍��̑哝�̂��|���ɏ㗤"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -1000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = -3000;
		}
		if (XX == 90) {
			wsprintf(messageEventTitle, TEXT("�k�C���V�������J��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 3000;
		}
		if (XX == 91) {
			wsprintf(messageEventTitle, TEXT("�}�O������N��2�{����"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 92) {
			wsprintf(messageEventTitle, TEXT("�t�B���s���ŌR���N�[�f�^�[������"));
			companyAStockPriceChangeAmount = -1000;
			companyBStockPriceChangeAmount = -2000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = -1000;
		}
		if (XX == 93) {
			wsprintf(messageEventTitle, TEXT("�{�B�ɂ��E�i�M�̑�ʐ��Y���n�܂�"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 2000;
		}
		if (XX == 94) {
			wsprintf(messageEventTitle, TEXT("���É��`��2�{�ɍL����"));
			companyAStockPriceChangeAmount = 6000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 000;
			companyDStockPriceChangeAmount = 000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 95) {
			wsprintf(messageEventTitle, TEXT("�����̓o�����^�C���f�[��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 3000;
			companyDStockPriceChangeAmount = 2000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 96) {
			wsprintf(messageEventTitle, TEXT("�����̉��i��������"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 97) {
			wsprintf(messageEventTitle, TEXT("�����̉��i���オ��"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = -1000;
			companyDStockPriceChangeAmount = -1000;
			companyEStockPriceChangeAmount = 000;
		}
		if (XX == 98) {
			wsprintf(messageEventTitle, TEXT("�{�B�Ƌ�B�����ԐV������������"));
			companyAStockPriceChangeAmount = 000;
			companyBStockPriceChangeAmount = 000;
			companyCStockPriceChangeAmount = 1000;
			companyDStockPriceChangeAmount = 1000;
			companyEStockPriceChangeAmount = 3000;
		}
		NE = XX;

		if (XX == 1000) {
			wsprintf(messageEventTitle, TEXT("�Ō�̊�����\�����Ă��܂��B"));
		}
		wsprintf(messageEventNumber, TEXT("\n\n\n\n\n\n�C�x���g�ԍ��G%d"), XX);
	}



	return;
}

/**
* ���ꂼ��̊����̕\����S���֐�
* param@ A:��Ƃ̔ԍ�(1~5), hWnd:�E�B���h�E�n���h��, rc:��ʑS�̂̃r�b�g�}�b�v�����`, hdc:�E�B���h�E�R���e�N�X�g
*/

void Ftime(const int A, const RECT rc, const HDC hdc) {

	HPEN hPen, hPen2, hPen3;
	HBRUSH hBrush, hBrushW, hBrushT;
	RECT rc0{}, rc1{}, rc2{}, rc3{}, rc4{}, rc6{};
	TCHAR companyName[10]{};
	TCHAR companyStockPrice[10]{};
	TCHAR maxCompanyStockPrice[10]{};
	TCHAR minCompanyStockPrice[10]{};

	hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hBrushW = (HBRUSH)GetStockObject(WHITE_BRUSH);
	hBrushT = (HBRUSH)GetStockObject(DC_BRUSH);
	hPen3 = (HPEN)GetStockObject(NULL_PEN);
	hPen2 = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	int companyNameTitleColorRed = 0, companyNameTitleColorGreen = 0, companyNameTitleColorBlue = 0;

	if (A != 6) {
		SelectObject(hdc, hBrush);
		if (A == 1) {
			rc0.left = 0;
			rc0.top = rc.bottom / 16;
			rc0.right = rc.right / number;
			rc0.bottom = rc.bottom / 9;
			rc1.left = rc0.right;
			rc1.top = rc0.top;
			rc1.right = rc.right / number * 2;
			rc1.bottom = rc0.bottom;
			rc2.top = 2;
			rc2.left = 2;
			rc2.bottom = rc0.top - rc.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + rc.bottom / 40;
			rc3.left = rc0.left + rc.right / 40;
			rc3.bottom = rc.bottom / 2 - rc.bottom / 40;
			rc3.right = rc1.right - rc.right / 40;
			wsprintf((LPWSTR)companyName, TEXT("�g���^������"));
			companyNameTitleColorRed = 204;
		}
		if (A == 2) {

			rc0.left = rc.right * 2 / 3;
			rc0.top = rc.bottom / 16;
			rc0.right = rc.right * 2 / 3 + rc.right / number;
			rc0.bottom = rc.bottom / 9;
			rc1.left = rc.right * 2 / 3 + rc.right / number;
			rc1.top = rc.bottom / 16;
			rc1.right = rc.right * 2 / 3 + rc.right / number * 2;
			rc1.bottom = rc0.bottom;
			rc2.top = 2;
			rc2.left = 2 + rc.right * 2 / 3;
			rc2.bottom = rc0.top - rc.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + rc.bottom / 40;
			rc3.left = rc0.left + rc.right / 40;
			rc3.bottom = rc.bottom / 2 - rc.bottom / 40;
			rc3.right = rc1.right - rc.right / 40;
			wsprintf((LPWSTR)companyName, TEXT("���j�N��"));
			companyNameTitleColorRed = 255;
			companyNameTitleColorGreen = 255;
		}
		if (A == 3) {
			rc0.left = 0;
			rc0.top = rc.bottom / 16 + rc.bottom / 2;
			rc0.right = rc.right / number;
			rc0.bottom = rc.bottom / 9 + rc.bottom / 2;
			rc1.left = rc0.right;
			rc1.top = rc.bottom / 16 + rc.bottom / 2;
			rc1.right = rc.right / number * 2;
			rc1.bottom = rc.bottom / 9 + rc.bottom / 2;
			rc2.top = 2 + rc.bottom / 2;
			rc2.left = 2;
			rc2.bottom = rc0.top - rc.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + rc.bottom / 40;
			rc3.left = rc0.left + rc.right / 40;
			rc3.bottom = rc.bottom / 2 - rc.bottom / 40 + rc.bottom / 2;
			rc3.right = rc1.right - rc.right / 40;
			wsprintf((LPWSTR)companyName, TEXT("�X�i����"));

			companyNameTitleColorRed = 102;
			companyNameTitleColorGreen = 255;
			companyNameTitleColorBlue = 255;
		}
		if (A == 4) {
			rc0.left = 0 + rc.right / 3;
			rc0.top = rc.bottom / 16 + rc.bottom / 2;
			rc0.right = rc.right / number + rc.right / 3;
			rc0.bottom = rc.bottom / 9 + rc.bottom / 2;
			rc1.left = rc0.right;
			rc1.top = rc0.top;
			rc1.right = rc.right / number * 2 + rc.right / 3;
			rc1.bottom = rc0.bottom;
			rc2.top = 2 + rc.bottom / 2;
			rc2.left = 2 + rc.right / 3;
			rc2.bottom = rc0.top - rc.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + rc.bottom / 40;
			rc3.left = rc0.left + rc.right / 40;
			rc3.bottom = rc.bottom / 2 - rc.bottom / 40 + rc.bottom / 2;
			rc3.right = rc1.right - rc.right / 40;
			wsprintf((LPWSTR)companyName, TEXT("�C�g�[���[�J�h�["));
			companyNameTitleColorRed = 51;
			companyNameTitleColorGreen = 204;
		}
		if (A == 5) {
			rc0.left = rc.right * 2 / 3;
			rc0.top = rc.bottom / 16 + rc.bottom / 2;
			rc0.right = rc.right * 2 / 3 + rc.right / number;
			rc0.bottom = rc.bottom / 9 + rc.bottom / 2;
			rc1.left = rc.right * 2 / 3 + rc.right / number;
			rc1.top = rc0.top;
			rc1.right = rc.right * 2 / 3 + rc.right / number * 2;
			rc1.bottom = rc0.bottom;
			rc2.top = 2 + rc.bottom / 2;
			rc2.left = 2 + rc.right * 2 / 3;
			rc2.bottom = rc0.top - rc.bottom / 80;
			rc2.right = rc1.right;
			rc3.top = rc0.bottom + rc.bottom / 40;
			rc3.left = rc0.left + rc.right / 40;
			rc3.bottom = rc.bottom / 2 - rc.bottom / 40 + rc.bottom / 2;
			rc3.right = rc1.right - rc.right / 40;
			wsprintf((LPWSTR)companyName, TEXT("�i�s�a"));
			companyNameTitleColorRed = 211;
			companyNameTitleColorGreen = 211;
			companyNameTitleColorBlue = 211;
		}
		SetDCBrushColor(hdc, RGB(companyNameTitleColorRed, companyNameTitleColorGreen, companyNameTitleColorBlue));

		rc2.left += rc.right / 15;
		rc2.right -= rc.right / 15;
		rc2.top += rc.bottom / 200;
		rc2.top += rc.bottom / 200;
		rc2.bottom += rc.bottom / 200;
		wsprintf((LPWSTR)companyStockPrice, TEXT("�����F%d"), stockPrices[A - 1][his - 1]);
		wsprintf((LPWSTR)maxCompanyStockPrice, eachCompanyMaxStockPriceInPeriod[A * 2 - 2]);	//maxStockPriceInPeriod
		wsprintf((LPWSTR)minCompanyStockPrice, eachCompanyMaxStockPriceInPeriod[A * 2 - 2]);	//minStockPriceInPeriod

		/*�����̘g�����X�N���v�g�J�n*/

		for (int i = 0; i < his; i++) {
			stockPriceChartGraphPoint[A - 1][i].x = (rc3.right - rc3.left) / (his) * (i + 1) + rc3.left - rc.right / 300;
		}

		SelectObject(hdc, hPen);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < number / 2; j++) {
				Rectangle(hdc, rc.right * j * 2 / number, rc.bottom * i / 2, rc.right * (j + 1) * 2 / number, rc.bottom * (i + 1) / 2);
			}
		}

		/*�����̘g�����X�N���v�g�I��*/
		/*��������start*/

		SelectObject(hdc, hBrushW);
		SelectObject(hdc, hPen3);

		RECT rc40{};
		rc40.left = (rc0.left + rc1.left) / 2;
		rc40.right = (rc0.right + rc1.right) / 2;
		rc40.bottom = (rc0.bottom + rc1.bottom) / 2;
		rc40.top = (rc0.top + rc1.top) / 2;

		RECT rc41{};
		rc41.left = rc40.left;
		rc41.right = rc40.right;
		rc41.bottom = rc40.bottom;
		rc41.top = rc40.top + rc.bottom / 100;

		SelectObject(hdc, hBrushT);

		RoundRect(hdc, rc2.left, rc2.top - rc.bottom / 200, rc2.right, rc2.bottom, (rc.right + rc.bottom) / 50, (rc.right + rc.bottom) / 50);

		SelectObject(hdc, hPen);

		SelectObject(hdc, hFont6);

		SelectObject(hdc, hBrush);

		SetTextColor(hdc, RGB(0, 0, 0));

		DrawText(hdc, companyName, -1, &rc2, DT_CENTER);


		SelectObject(hdc, hBrushW);

		SelectObject(hdc, hPen);

		Rectangle(hdc, rc3.left, rc3.top, rc3.right, rc3.bottom);

		SetTextColor(hdc, RGB(0, 0, 255));
		DrawText(hdc, companyStockPrice, -1, &rc41, DT_CENTER);

		/*��������end*/

		SelectObject(hdc, hPen2);

		Polyline(hdc, stockPriceChartGraphPoint[A - 1], stockPriceChartGraphPointNumber);
		SelectObject(hdc, hFont3);
		SetTextColor(hdc, RGB(255, 102, 51));
		TextOut(hdc, rc3.right, rc3.top, maxCompanyStockPrice, lstrlen(maxCompanyStockPrice));
		SetTextColor(hdc, RGB(102, 102, 255));
		TextOut(hdc, rc3.right, rc3.bottom - 20, minCompanyStockPrice, lstrlen(minCompanyStockPrice));

	}
	if (A == 6) {
		rc0.left = 0;
		rc0.top = rc.bottom / 16;
		rc0.right = rc.right / number;
		rc0.bottom = rc.bottom / 9;
		rc1.left = rc0.right;
		rc1.top = rc0.top;
		rc1.right = rc.right / number * 2;
		rc1.bottom = rc0.bottom;
		rc2.top = 2;
		rc2.left = 2;
		rc2.bottom = rc0.top - rc.bottom / 80;
		rc2.right = rc1.right;
		rc3.top = rc0.bottom + rc.bottom / 40;
		rc3.left = rc0.left + rc.right / 80;
		rc3.bottom = rc.bottom / 2 - rc.bottom / 40;
		rc3.right = rc1.right - rc.right / 80;
		rc4.left = rc1.right + rc.right / 20;
		rc4.top = rc.bottom / 60;
		rc4.bottom = rc0.top;
		rc4.right = rc.right / number * 2 * 2 - rc.right / 100;
		/*���v����start*/
		TCHAR sur[10];
		SelectObject(hdc, hFont2);
		wsprintf(sur, TEXT("%3d"), currentRemainingTime / 1000);

		SetTextColor(hdc, RGB(0, 51, 0));
		TextOut(hdc, rc1.right + rc.right / 50, rc4.top + rc4.top * 3 / 4, sur, lstrlen(sur));
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
		TextOut(hdc, rc1.right + rc.right / 50, rc4.top + rc4.top * 3, TEXT("�`�j���[�X�`"), lstrlen(TEXT("�`�j���[�X�`")));

		rc6.top = rc0.bottom + rc.bottom / 40;
		rc6.left = rc0.left + rc.right / 160 + rc.right / 3;
		rc6.bottom = rc.bottom / 2 - rc.bottom / 10;
		rc6.right = rc1.right - rc.right / 32 + rc.right / 3;

		SelectObject(hdc, hFont6);
		DrawText(hdc, messageEventTitle, lstrlen(messageEventTitle), &rc6, DT_CENTER | DT_WORDBREAK);

		SelectObject(hdc, hFont3);
		DrawText(hdc, messageEventNumber, lstrlen(messageEventNumber), &rc6, DT_CENTER | DT_WORDBREAK);
	}
	if (A != 6) {
		if (AS[A - 1] > 0) {
			SelectObject(hdc, hBrushw);
			Rectangle(hdc, rc0.left, rc0.top, rc1.right, rc3.bottom);
			SelectObject(hdc, hFont2);
			wsprintf((LPWSTR)messageCompanyBankruptcy, TEXT("\n���̉�Ђ͓|�Y���܂����B\n���̃J�[�h���{�[�h�ɖ߂��Ă��������B"));
			DrawText(hdc, messageCompanyBankruptcy, -1, &rc3, DT_CENTER);
		}
	}

	DeleteObject(hBrush);
	DeleteObject(hBrushW);
	DeleteObject(hPen);
	DeleteObject(hPen2);
	return;
}
