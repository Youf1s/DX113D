#pragma once

#define YOUSIF_ERROR_GFX(HRs)if(FAILED(hr =(HRs) ))throw Graphics::HrErrors(__LINE__,__FILE__,hr)
#define YOUSIF_DEVICE_ERROR_GFX(hr) Graphics::HrErrors(__LINE__,__FILE__,(hr))