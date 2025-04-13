
#define TOOLBOX_API extern "C" __declspec(dllexport)

#include <inttypes.h>
#include "include\NIVision.h"
#include "include\NIVisionExtExports.h"

typedef struct {
	float X;
	float Y;
} TD_Point;

typedef struct {
	int32_t dimSize;
	TD_Point elt[1];
} TD_RectCoords;
typedef TD_RectCoords** TD_RectCoords_Hdl;

typedef struct {
	int32_t dimSize;
	int elt[1];
} TD_Rect;
typedef TD_Rect** TD_Rect_Hdl;


typedef struct {
	int32_t dimSize;
	float mean[1];
} TD_Profile;
typedef TD_Profile** TD_Profile_Hdl;

TOOLBOX_API void GetProfile(NIImageHandle imageHandle, TD_RectCoords_Hdl RectCoords, int32_t UpSampling, TD_Profile_Hdl Profile);
