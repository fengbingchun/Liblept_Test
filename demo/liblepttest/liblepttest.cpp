// liblepttest.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "zlib.h"
#include "png.h"
#include "jpeglib.h"
#include "tiff.h"
#include "gif_lib.h"
#include "allheaders.h"

using namespace std;

static const l_float32  ANGLE1 = 3.14159265 / 12.;

void test_giflib();

void RotateTest()
{
	string strSrc = "../../../images/weasel.png";
	string strDst = "../../../images/dst.gif";

	PIX* pixs = pixRead(strSrc.c_str());
	if (pixs == NULL) {
		cout<<" read image error "<<endl;
		return;
	}

	l_int32 w, h, d;
	pixGetDimensions(pixs, &w, &h, &d);
	PIX* pixd = pixRotate(pixs, ANGLE1, L_ROTATE_SHEAR, L_BRING_IN_WHITE, w, h);
	pixWrite(strDst.c_str(), pixd, IFF_GIF);

	pixDestroy(&pixs);
	pixDestroy(&pixd);
}

void EdgeTest()
{
	string strSrc = "../../../images/marge.jpg";
	string strDst = "../../../images/dst.bmp";

	PIX* pixs = pixRead(strSrc.c_str());
	if (pixs == NULL) {
		cout<<" read image error "<<endl;
		return;
	}

	l_int32 w, h, d;
	pixGetDimensions(pixs, &w, &h, &d);
	if (d != 8) {
		cout<<"pixs not 8 bpp"<<endl;
		return;
	}

	PIX* pixf = pixSobelEdgeFilter(pixs, L_HORIZONTAL_EDGES);
	PIX* pixd = pixThresholdToBinary(pixf, 10);
	pixInvert(pixd, pixd);
	pixWrite(strDst.c_str(), pixd, IFF_BMP);

	pixDestroy(&pixs);
	pixDestroy(&pixf);
	pixDestroy(&pixd);
}

int main(int argc, char* argv[])
{
	RotateTest();
	EdgeTest();

	cout<<"ok!"<<endl;

	return 0;
}

