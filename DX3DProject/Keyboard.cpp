#include "Keyboard.h"





bool Keyboard::KeyIsPressed(unsigned int Code) const noexcept
{
	return KeyStates[Code];
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return KeyBuf.empty();
}

void Keyboard::EmptyKey() noexcept
{
	KeyBuf = std::queue<Event>();
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
	if (KeyBuf.size() > 0)
	{
		Keyboard::Event Y = KeyBuf.front();
		KeyBuf.pop();
		return Y;
	}
	else
	{
		return Keyboard::Event();
	}
}

char Keyboard::ReadChar() noexcept
{
	if (CharBuf.size() > 0)
	{
		unsigned char CharCode = CharBuf.front();
	}
	else 
	{
		if (CharIsEmpty())
		{
			return 0;
		}
		return 0;
	}
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return CharBuf.empty();
}

void Keyboard::EmptyChar() noexcept
{
	CharBuf = std::queue<char>();
}

void Keyboard::EmptyAll() noexcept
{
	EmptyChar();
	EmptyKey();
}

void Keyboard::ActivateAutoRepeat() noexcept
{
	AutoRepeatActive = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	AutoRepeatActive = false;
}

bool Keyboard::IsAutoRepeatActive() noexcept
{
	return AutoRepeatActive;
}



void Keyboard::OnKeyPressed(unsigned char Code) noexcept
{
	KeyStates[Code] = true;
	KeyBuf.push(Keyboard::Event(Keyboard::Event::type::Press, Code));
	CutBuf(KeyBuf);
}

void Keyboard::OnKeyReleased(unsigned char Code) noexcept
{
	KeyStates[Code] = false;
	KeyBuf.push(Keyboard::Event(Keyboard::Event::type::Release, Code));
	CutBuf(KeyBuf);
}

void Keyboard::OnChar(char Character) noexcept
{
	CharBuf.push(Character);
	CutBuf(CharBuf);
}

void Keyboard::ClearSt() noexcept
{
	KeyStates.reset();
}

template<typename T>
void Keyboard::CutBuf(std::queue<T>& Buffer) noexcept
{
	while (Buffer.size() > BufSize)
	{
		Buffer.pop();
	}
}