#include "opencv2/opencv.hpp"
#include <Windows.h>

/*
éQçl
http://eternalwindows.jp/graphics/bitmap/bitmap00.html
*/

class CVSS{
private:
	cv::Mat mat;

	HBITMAP CreateBackbuffer(int nWidth, int nHeight){
		LPVOID           lp;
		BITMAPINFO       bmi;
		BITMAPINFOHEADER bmiHeader;
		ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
		bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmiHeader.biWidth = nWidth;
		bmiHeader.biHeight = nHeight;
		bmiHeader.biPlanes = 1;
		bmiHeader.biBitCount = 24;
		bmi.bmiHeader = bmiHeader;
		return CreateDIBSection(NULL, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &lp, NULL, 0);
	}

public:
	cv::Mat Get(){
		HDC     hdc;
		HWND    hwndDesk;
		RECT    rc;
		BITMAP  bm;
		HBITMAP hbmp;
		HBITMAP hbmpPrev;
		
		hwndDesk = GetDesktopWindow();
		GetWindowRect(hwndDesk, &rc);
		hdc = CreateCompatibleDC(NULL);
		hbmp = CreateBackbuffer(rc.right, rc.bottom);
		hbmpPrev = (HBITMAP)SelectObject(hdc, hbmp);

		BitBlt(hdc, 0, 0, rc.right, rc.bottom, GetWindowDC(hwndDesk), 0, 0, SRCCOPY);
		
		GetObject(hbmp, sizeof(BITMAP), &bm);

		mat = cv::Mat(bm.bmHeight, bm.bmWidth, CV_8UC3);
		for (int y = 0; y < bm.bmHeight; y++){
			LPBYTE lp = (LPBYTE)bm.bmBits + (y*bm.bmWidth * 3);
			for (int x = 0; x < bm.bmWidth; x++){
				for (int i = 0; i < mat.channels();i++){
					mat.data[(bm.bmHeight - y - 1)*mat.step + x*mat.elemSize() + i] = lp[i];	
				}
				lp += 3;
			}
		}

		SelectObject(hdc, hbmpPrev);
		DeleteObject(hbmp);
		DeleteDC(hdc);

		return mat;
	}

};

