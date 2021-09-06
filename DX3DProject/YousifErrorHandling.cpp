#include "YousifErrorHandling.h"
#include <sstream>





YousifError::YousifError(int Line, const char* File) noexcept
    :
    Line(Line),
    File(File)
{}

const char* YousifError::what() const noexcept
{

    std::ostringstream OS;
    OS << GetType() << std::endl << GetOrSt();
    WtBuf = OS.str();
    return WtBuf.c_str();
}

const char* YousifError::GetType() const noexcept
{
    return "Yousif Error";
}

int YousifError::GetLine() const noexcept
{
    return Line;
}

const std::string YousifError::GetFile() const noexcept
{
    return File;
}

std::string YousifError::GetOrSt() const noexcept
{
    std::ostringstream OS;
    OS << "File : " << File << std::endl << "Line : " << Line;
    return OS.str();
}
