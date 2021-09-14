#pragma once

#include<exception>
#include<string>
#include<sstream>

class YousifError : public std::exception
{
public:
	YousifError(int Line, const char* File) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string GetFile() const noexcept;
	std::string GetOrSt() const noexcept;
	
private:
	int Line;
	std::string File;
protected:
	mutable std::string WtBuf;
};

