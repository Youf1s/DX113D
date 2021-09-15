#pragma once

#define YOUSIF_ERROR(HR) Window::Errors(__LINE__,__FILE__,HR)
#define YOUSIF_LAST_ERROR() Window::Errors(__LINE__,__FILE__,GetLastError())