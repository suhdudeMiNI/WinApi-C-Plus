// Lab1PwSG_PKT.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab1PwSG_PKT.h"
#include <commctrl.h>
#include <windowsx.h>
#include <time.h>
#include <Math.h>

#define MAX_LOADSTRING 100
//==============
//Colors
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define PINK RGB(255, 20, 147)
#define YELLOW RGB(255, 255, 0)
#define SKY RGB(135, 206, 235)
#define BLACK RGB(0, 0, 0)
#define OLIVE RGB(128, 128, 0)

#define NumCol 8


typedef struct SHAR
{
    int x;
    int y;
    int flag;
    int speedX;
    int speedY;
    HBRUSH cvet;  
} SHAR_T;

//===============
// Global Variables:
int size_SH[21] = {30, 15, 15, 15, 15,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}; //radius
int score;
HWND hProgress;
INITCOMMONCONTROLSEX icc;
DWORD nCounter;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
ATOM                MyRegisterClassBlack(HINSTANCE hInstance);
ATOM                MyRegisterClassWhite(HINSTANCE hInstance);
HBRUSH red = CreateSolidBrush(RED);
HBRUSH green = CreateSolidBrush(GREEN);
HBRUSH blue = CreateSolidBrush(BLUE);
HBRUSH yellow = CreateSolidBrush(YELLOW);
HBRUSH sky = CreateSolidBrush(SKY);
HBRUSH black = CreateSolidBrush(BLACK);
HBRUSH pink = CreateSolidBrush(PINK);
HBRUSH olive = CreateSolidBrush(OLIVE);

HPEN pen_black = CreatePen(PS_SOLID, 2, BLACK);
HPEN pen_red = CreatePen(PS_SOLID, 2, RED);
HPEN pen_green = CreatePen(PS_SOLID, 2, GREEN);
HPEN pen_blue = CreatePen(PS_SOLID, 2, BLUE);
HPEN pen_sky = CreatePen(PS_SOLID, 2, SKY);
HPEN pen_yellow = CreatePen(PS_SOLID, 2, YELLOW);
HPEN pen_pink = CreatePen(PS_SOLID, 2, PINK);
HPEN pen_olive = CreatePen(PS_SOLID, 2, OLIVE);

HBRUSH COLORS[NumCol] = {red, green, blue, yellow, sky, black, pink, olive};
HPEN pen[NumCol] = { pen_red, pen_green, pen_blue, pen_yellow, pen_sky, pen_black, pen_pink, pen_olive };
SHAR_T sharik[NumCol][21];

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1PWSGPKT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    MyRegisterClassBlack(hInstance);
    MyRegisterClassWhite(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1PWSGPKT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void UzupTab(HWND hWnd)
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < NumCol; j++)
        {
            sharik[j][i].cvet = COLORS[j];
        }
    }

    for (int i = 0; i < NumCol; i++)
    {
        sharik[i][0].y = rc.bottom - 20;
        sharik[i][0].x = rand() % (rc.right - rc.left);
        sharik[i][0].speedX = (rand() % 10) - 5;
        sharik[i][0].speedY = (rand() % 10);
        sharik[i][0].flag = 1;
    }

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < NumCol; j++)
        {
            sharik[j][i].flag = 0;
        }
    }

}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1PWSGPKT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

ATOM MyRegisterClassBlack(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB1PWSGPKT);
    wcex.lpszClassName = L"Black";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

ATOM MyRegisterClassWhite(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB1PWSGPKT);
    wcex.lpszClassName = L"White";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   RECT rt = { 0, 0, 400, 300 + 20 };

   int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
   int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;

   AdjustWindowRect(&rt, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, TRUE);

   HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, szWindowClass, L"FruitNinja", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN,
      centerX - (rt.right - rt.left)/2, centerY - (rt.bottom - rt.top)/2, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, hInstance, nullptr); 
   
   if (!hWnd)
   {
      return FALSE;
   }
   // ==========================================CHILD WINDOWS BLACK/WHITE=====================================================
   /*for (int i = 0; i < 16; i++)
   {
       for (int j = 0; j < 12; j++)
       {
           if (j % 2 == 0)
           {
               if (i % 2 == 0)
                   HWND hWndDziec = CreateWindow(_T("Black"), 0, WS_VISIBLE | WS_CHILD, 50 * i, 50*j, 50, 50, hWnd, nullptr, hInstance, nullptr);
               else
                   HWND hWndDziec2 = CreateWindow(_T("White"), 0, WS_VISIBLE | WS_CHILD, 50 * i, 50 * j, 50, 50, hWnd, nullptr, hInstance, nullptr);
           }

           else
           {
               if (i % 2 != 0)
                   HWND hWndDziec = CreateWindow(_T("Black"), 0, WS_VISIBLE | WS_CHILD, 50 * i, 50*j, 50, 50, hWnd, nullptr, hInstance, nullptr);
               else
                   HWND hWndDziec2 = CreateWindow(_T("White"), 0, WS_VISIBLE | WS_CHILD, 50* i, 50 * j, 50, 50, hWnd, nullptr, hInstance, nullptr);
           }             
       }       
   }*/
   //=========================================================================================================
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HCURSOR cursor = NULL;
    static HCURSOR cur = NULL;
    static HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
    static POINT ptFirst, ptLast;
    //HWND window_handle;
    HMENU hMenu = GetMenu(hWnd);
    
    POINT poin;
    RECT rt; 
    int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
    int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DeleteObject(pen_black);
                DeleteObject(pen_blue);
                DeleteObject(pen_yellow);
                DeleteObject(pen_green);
                DeleteObject(pen_red);
                DeleteObject(pen_olive);
                DeleteObject(pen_sky);
                DeleteObject(pen_pink);

                DeleteObject(black);
                DeleteObject(blue);
                DeleteObject(yellow);
                DeleteObject(green);
                DeleteObject(red);
                DeleteObject(olive);
                DeleteObject(sky);
                DeleteObject(pink);

                DestroyWindow(hWnd);
                break;

            case ID_GAME_NEWGAME:
                
                KillTimer(hWnd, 1); 
                DestroyWindow(hProgress);
                GetClientRect(hWnd, &rt);
                hProgress = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                    0, rt.bottom - 20, rt.right - rt.left, 20, hWnd, (HMENU)0, hInst, NULL);

                SendMessage(hProgress, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 3000));
                SendMessage(hProgress, PBM_SETSTEP, (WPARAM)10, 0);
                SetTimer(hWnd, 1, 100, 0);               
                nCounter = 0;
                score = 0;
                UzupTab(hWnd);
                UpdateWindow(hWnd);
                break;

            case ID_BOARD_SMALL:
                CheckMenuItem(hMenu, ID_BOARD_SMALL, MF_CHECKED);
                CheckMenuItem(hMenu, ID_BOARD_MEDIUM, MF_UNCHECKED);
                CheckMenuItem(hMenu, ID_BOARD_BIG, MF_UNCHECKED);
                
                rt = { 0, 0, 400, 300  + 20};
                KillTimer(hWnd, 1);
                DestroyWindow(hProgress);
                hProgress = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                    0, rt.bottom - 20, rt.right - rt.left, 20, hWnd, (HMENU)0, hInst, NULL);
                SendMessage(hProgress, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 3000));
                SendMessage(hProgress, PBM_SETSTEP, (WPARAM)10, 0);
                SetTimer(hWnd, 1, 100, 0);
                nCounter = 0;
                score = 0;
                AdjustWindowRect(&rt, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, TRUE);
                SetWindowPos(hWnd, HWND_TOPMOST, centerX - (rt.right - rt.left) / 2, centerY - (rt.bottom - rt.top) / 2, rt.right - rt.left, rt.bottom - rt.top, SWP_NOREPOSITION);
                UzupTab(hWnd);
                UpdateWindow(hWnd);
                break;

            case ID_BOARD_MEDIUM:
                CheckMenuItem(hMenu, ID_BOARD_SMALL, MF_UNCHECKED);
                CheckMenuItem(hMenu, ID_BOARD_MEDIUM, MF_CHECKED);
                CheckMenuItem(hMenu, ID_BOARD_BIG, MF_UNCHECKED);
                
                rt = { 0, 0, 600, 500 + 20 };
                KillTimer(hWnd, 1);
                DestroyWindow(hProgress);
                hProgress = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                    0, rt.bottom - 20, rt.right - rt.left, 20, hWnd, (HMENU)0, hInst, NULL);
                SendMessage(hProgress, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 3000));
                SendMessage(hProgress, PBM_SETSTEP, (WPARAM)10, 0);
                SetTimer(hWnd, 1, 100, 0);
                nCounter = 0;
                score = 0;
                AdjustWindowRect(&rt, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, TRUE);
                SetWindowPos(hWnd, HWND_TOPMOST, centerX - (rt.right - rt.left) / 2, centerY - (rt.bottom - rt.top) / 2, rt.right - rt.left, rt.bottom - rt.top, SWP_NOREPOSITION);
                UzupTab(hWnd);
                UpdateWindow(hWnd);
                break;

            case ID_BOARD_BIG:  
                CheckMenuItem(hMenu, ID_BOARD_SMALL, MF_UNCHECKED);
                CheckMenuItem(hMenu, ID_BOARD_MEDIUM, MF_UNCHECKED);
                CheckMenuItem(hMenu, ID_BOARD_BIG, MF_CHECKED);
                
                rt = { 0, 0, 800, 600 + 20 };
                KillTimer(hWnd, 1);
                DestroyWindow(hProgress);
                hProgress = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                    0, rt.bottom - 20, rt.right - rt.left, 20, hWnd, (HMENU)0, hInst, NULL);
                SendMessage(hProgress, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 3000));
                SendMessage(hProgress, PBM_SETSTEP, (WPARAM)10, 0);
                SetTimer(hWnd, 1, 100, 0);
                nCounter = 0;
                score = 0;
                AdjustWindowRect(&rt, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, TRUE);
                SetWindowPos(hWnd, HWND_TOPMOST, centerX - (rt.right - rt.left) / 2, centerY - (rt.bottom - rt.top) / 2, rt.right - rt.left, rt.bottom - rt.top, SWP_NOREPOSITION);
                UzupTab(hWnd);
                UpdateWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;


        //Source timer: https://delphiru.ru/visual-c/586-create-progressbar

     case WM_CREATE:
         srand(time(NULL));
         GetClientRect(hWnd, &rt );
         hProgress = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
             0, rt.bottom - 20, rt.right - rt.left, 20, hWnd, (HMENU)0, hInst, NULL);

         SendMessage(hProgress, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 3000));
         SendMessage(hProgress, PBM_SETSTEP, (WPARAM)10,0);
         SetTimer(hWnd, 1, 100, 0);
         nCounter = 0;

         UzupTab(hWnd);
         cursor = LoadCursor(hInst, (LPWSTR)IDC_CURSOR1);
         cur = LoadCursor(NULL, IDC_ARROW);
         
         SetTimer(hWnd, 3, 250, NULL);
         SetTimer(hWnd, 2, 100, NULL);

         break;

     case WM_SETCURSOR:
         //SetCursor();
     break;

     case WM_MOUSEMOVE:
         SetCursor(cursor);
         SetTimer(hWnd, 7, 3 * 1000, NULL);
         SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
         return TRUE;

     case WM_NCMOUSEMOVE:
         SetCursor(cur);
         SetTimer(hWnd, 7, 3 * 1000, NULL);
         SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
         return TRUE;

     case WM_WINDOWPOSCHANGING:
    {
         ReleaseCapture();
         break;                 
    }

    case WM_TIMER:
        if (wParam == 1)
        {
            nCounter++;
            SendMessage(hProgress, PBM_STEPIT, 0, 0);
            if (nCounter == 300)
            {
                KillTimer(hWnd, 1);
                UpdateWindow(hWnd);
            }
            if (nCounter < 301)
                InvalidateRect(hWnd, NULL, FALSE);
        }
        
        if (wParam == 7) {
            SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOPMOST);
            SetLayeredWindowAttributes(hWnd, 0, (255 * 50) / 100, LWA_ALPHA);
            UpdateWindow(hWnd);
        }

        if (wParam == 2)
        {
        
            if (nCounter < 300)
                InvalidateRect(hWnd, NULL, FALSE);
            GetCursorPos(&poin);
            ScreenToClient(hWnd, &poin);
            ptFirst.x = ptLast.x;
            ptFirst.y = ptLast.y;
            ptLast.x = poin.x;
            ptLast.y = poin.y;                    
        }
     break;

    case WM_PAINT:
    {
             PAINTSTRUCT ps;
             HDC hdc = BeginPaint(hWnd, &ps);
             RECT rc;
             GetClientRect(hWnd, &rc);
             HPEN pen_black = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
             HPEN pen_white = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
             HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,
                 (HBRUSH)GetStockObject(WHITE_BRUSH));
             HPEN oldpen = (HPEN)SelectObject(hdc, pen_white);
             HPEN newpen = CreatePen(PS_NULL,0, GREEN);

             for (int i = 0; i < 12; i++)
             {
                 for (int j = 0; j < 16; j++)
                 {
                     if (j % 2 == 0)
                     {
                         if (i % 2 == 0)
                         {
                             SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
                             SelectObject(hdc, pen_black);
                             Rectangle(hdc, 50 * j, 50 * i, 50 * (j+1), 50 * (i+1));                            
                         }
                         else
                         {
                             SelectObject(hdc, oldBrush);
                             SelectObject(hdc, pen_white);
                             Rectangle(hdc, 50 * j, 50 * i, 50 * (j + 1), 50 * (i + 1));
                         }
                     }
                     else
                     {
                         if (i % 2 != 0)
                         {
                             SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
                             SelectObject(hdc, pen_black);
                             Rectangle(hdc, 50 * j, 50 * i, 50 * (j + 1), 50 * (i + 1));
                         }
                         else
                         {
                             SelectObject(hdc, oldBrush);
                             SelectObject(hdc, pen_white);
                             Rectangle(hdc, 50 * j, 50 * i, 50 * (j + 1), 50 * (i + 1));
                         }

                     }
                 }
                
             }

             //DeleteObject(pen_black);
             DeleteObject(pen_white);
             //DeleteObject(oldBrush);
             WCHAR score2[5];
             HFONT hFont = CreateFont(30, 30, 0, 0, 700, 3, 4, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                 DEFAULT_PITCH | FF_DONTCARE, nullptr);
             _itow_s(score, score2, 10);
             
             WCHAR score3[15] =  L"SCORE:";
             if (nCounter < 300)
             {
                 SelectObject(hdc, hFont);

                 SetBkMode(hdc, TRANSPARENT);
                 SetTextColor(hdc, RGB(0, 255, 0));
                 DrawText(hdc, score2, -1, &rc, DT_TOP | DT_RIGHT);
             }

             else
             {
                 DeleteObject(hFont);
                 hFont = CreateFont(30, 30, 0, 0, 700, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                     DEFAULT_PITCH | FF_DONTCARE, nullptr);
                 SelectObject(hdc, hFont);
                 SetBkMode(hdc, TRANSPARENT);
                 SetTextColor(hdc, RGB(0, 255, 0));
                 DrawText(hdc, score3, -1, &rc, DT_CENTER);
                 rc.bottom -= 100;
                 rc.top += 100;
                 DrawText(hdc, score2, -1, &rc, DT_CENTER);
             }

             

             SelectObject(hdc, hPen);
             MoveToEx(hdc, ptFirst.x, ptFirst.y, NULL);
             LineTo(hdc, ptLast.x, ptLast.y);
             
             //Ellepse====================

             SelectObject(hdc, newpen);
             for (int i = 0; i < NumCol; i++)
             {
                 bool da = true;
                 for (int j = 0; j < 21; j++)
                 {
                     if (sharik[i][j].flag == 1)
                     {
                         da = false;
                         break;
                     }
                 }
                 if (da)
                 {
                     sharik[i][0].y = rc.bottom - 20;
                     sharik[i][0].x = rand() % (rc.right - rc.left);
                     sharik[i][0].speedX = (rand() % 10) - 5;
                     sharik[i][0].speedY = (rand() % 10);
                     sharik[i][0].flag = 1;
                 }
             }
             for (int i = 0; i < NumCol; i++)
             {
                 for (int j = 0; j < 21; j++)
                 {
                     if (sharik[i][j].flag == 1)
                     {
                         if (sharik[i][j].y < rc.top - size_SH[i] || sharik[i][j].y > rc.bottom + size_SH[i] || sharik[i][j].x < rc.left + size_SH[i] || sharik[i][j].x > rc.right - size_SH[i])
                         {
                             sharik[i][j].y = rc.bottom - 20;
                             sharik[i][j].x = rand() % (rc.right - rc.left);
                             sharik[i][j].speedX = (rand() % 10) - 5;
                             sharik[i][j].speedY = (rand() % 10);
                             sharik[i][j].flag = 0;
                         }
                         
                         GetCursorPos(&poin);
                         ScreenToClient(hWnd, &poin);
                         if (sqrt(pow(poin.x - sharik[i][j].x, 2) + pow(poin.y - sharik[i][j].y, 2)) <= size_SH[j])
                         {
                             score++;
                             int from = 0;
                             int to = 0;
                             if (j == 0)
                             {
                                 from = 1;
                                 to = 5;
                             }
                             else if (j < 5)
                             {
                                 from = 5 + (j - 1) * 4;
                                 to = from + 4;
                             }
                             sharik[i][j].flag = 0;
                             for (int k = from; k < to; k++)
                             {
                                 sharik[i][k].cvet = sharik[i][j].cvet;
                                 sharik[i][k].y = sharik[i][j].y;
                                 sharik[i][k].x = sharik[i][j].x;;
                                 sharik[i][k].speedX = sharik[i][j].speedX + (rand() % 20) - 10;
                                 sharik[i][k].speedY = sharik[i][j].speedY + (rand() % 20) - 10;
                                 sharik[i][k].flag = 1;
                             }
                             
                         }
                         sharik[i][j].x += sharik[i][j].speedX;
                         sharik[i][j].y -= sharik[i][j].speedY;
                         SelectObject(hdc, sharik[i][j].cvet);
                         Ellipse(hdc, sharik[i][j].x - size_SH[j], sharik[i][j].y - size_SH[j], sharik[i][j].x + size_SH[j], sharik[i][j].y + size_SH[j]);
                     }
                     
                 }
             }
                          
             //=======================
             
             EndPaint(hWnd, &ps);
    }
         break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


