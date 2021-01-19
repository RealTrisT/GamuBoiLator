#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <subauth.h>

#include <iostream>
#include <stdlib.h>
//#include "LR35902.h"
#include "GameBoy.h"
#include "TristGraphics.h"

/*
void printHex8(unsigned char* loc, int amount) {
	for (size_t i = 0; i < amount; i++){
		printf("%.2X ", loc[i]);
	}
}
void printHex16(unsigned short* loc, int amount) {
	for (size_t i = 0; i < amount; i++) {
		printf("%.4X ", loc[i]);
	}
}*/





#pragma pack(push, 1)
struct rgb {
	unsigned char r, g, b;
};
#pragma pack(pop)

UD* tg_p = 0;
PIXEL_VERTEX* screen = 0;
unsigned int width, height;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_PAINT:
		tg_p->PresentFrame();
		break;
	case WM_MOUSEMOVE:
		screen[(lParam >> 16)*width + (lParam & 0xFFFF)] = { 1, 0, 0, 1 };
		tg_p->ShitImage(screen); tg_p->PresentFrame();
		break;
	} return DefWindowProc(hWnd, message, wParam, lParam);
};

int main() {
	//-----------------------------read bmp
	
	FILE* yeet = 0;	unsigned int lSize;
	if (fopen_s(&yeet, "C:\\Users\\TrisT\\Pictures\\cock.bmp", "rb")) { puts("failed to open"); getchar(); return 0; }
	fseek(yeet, 0, SEEK_END);lSize = ftell(yeet);rewind(yeet);	//get file size
	unsigned char* file = (unsigned char*)malloc(lSize);		//allocate file size	 
	if(fread_s(file, lSize, 1, lSize, yeet) != lSize) { puts("failed to read"); getchar(); return 0; }
	fclose(yeet);


	b3icolor* image = (b3icolor*)(file + *(unsigned int*)(file + 0xA));
	width = *(unsigned int*)(file + 0x12); height = *(unsigned int*)(file + 0x16);
	screen = (PIXEL_VERTEX*)malloc(width*height*sizeof(PIXEL_VERTEX));

	unsigned int i = 0;
	for (size_t y = 0; y < height; y++){
		for (size_t x = 0; x < width; x++) {
			screen[i++] = { float(x + 1), float(y + 1), 0.f, { image[(height - 1 - y)*width + x], 1.f} };
	}	}

	printf("size: %ux%u\n", width, height);

	//-----------------------------window and dx shit

	UD tg(width, height);
	tg_p = &tg;

	tg.SetWindowInitCallback ([] (UD* elUD) -> void { elUD->InitD3D();});
	tg.InitWindow(WindowProc);

	tg.ShitImage(screen); tg.PresentFrame();

	puts("started");
	getchar();

	tg.TermD3D();
	tg.TermWindow();
	return 0;
}
