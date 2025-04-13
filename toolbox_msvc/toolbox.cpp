// toolbox_msvc.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "toolbox.h"

TOOLBOX_API void GetProfile(NIImageHandle imageHandle, TD_RectCoords_Hdl RectCoords, int32_t UpSampling, TD_Profile_Hdl Profile)
{
	Point start1, start2, end1, end2, start, end;
	Point* line1, * line2, * line90, meas;
	int numPoints1, numPoints2, numPoints90;

	unsigned short* _pixelPtr;
	int _type;
	int _width, _height;
	size_t _stepInBytes;
	unsigned short value;
	float sum, average;

	NIGetImageInfo(imageHandle, (unsigned char**)&_pixelPtr, &_type, &_width, &_height, &_stepInBytes);

	start1.x = (int)trunc((*RectCoords)->elt[3].X * UpSampling);
	start1.y = (int)trunc((*RectCoords)->elt[3].Y * UpSampling);
	end1.x = (int)trunc((*RectCoords)->elt[2].X * UpSampling);
	end1.y = (int)trunc((*RectCoords)->elt[2].Y * UpSampling);
	start2.x = (int)trunc((*RectCoords)->elt[0].X * UpSampling);
	start2.y = (int)trunc((*RectCoords)->elt[0].Y * UpSampling);
	end2.x = (int)trunc((*RectCoords)->elt[1].X * UpSampling);
	end2.y = (int)trunc((*RectCoords)->elt[1].Y * UpSampling);

	line1 = imaqGetPointsOnLine(start1, end1, &numPoints1);
	line2 = imaqGetPointsOnLine(start2, end2, &numPoints2);

	NIResizeArray1D((NIArrayHandle)Profile, sizeof(float), numPoints1);

	for (int i = 0; i < numPoints1; i++) {
		start.x = line1[i].x;
		start.y = line1[i].y;
		end.x = line2[i].x;
		end.y = line2[i].y;
		line90 = imaqGetPointsOnLine(start, end, &numPoints90);
		sum = 0;
		for (int j = 0; j < numPoints90; j++) {
			meas.x = line90[j].x / UpSampling;
			meas.y = line90[j].y / UpSampling;

			value = (unsigned short)*(_pixelPtr + meas.x + meas.y * _stepInBytes / 2);
			sum += value;
		}
		average = sum / numPoints90;
		(*Profile)->mean[i] = average;
		imaqDispose(line90);
	}
	imaqDispose(line1);
	imaqDispose(line2);
}
