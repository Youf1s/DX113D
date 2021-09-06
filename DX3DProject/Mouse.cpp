#include "Mouse.h"

std::pair<int, int> Mouse::GetPos() const noexcept
{
    return{X,Y};
}

int Mouse::GetPosX() const noexcept
{
    return X;
}

int Mouse::GetPosY() const noexcept
{
    return Y;
}

bool Mouse::LeftIsPressed() const noexcept
{
    return leftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
    return rightIsPressed;
}

bool Mouse::IsInWindow() const noexcept
{
    return isInWindow;
}

Mouse::Event Mouse::Read() noexcept
{
    if (Buf.size() > 0u)
    {
        Mouse::Event Y = Buf.front();
        Buf.pop();
        return Y;
    }
    else
    {
        return Mouse::Event();
    }
}

void Mouse::EmptyAll() noexcept
{
    Buf = std::queue<Event>();
}

void Mouse::OnMouseMove(int NewX, int NewY) noexcept
{
    X = NewX;
    Y = NewY;
    Buf.push(Mouse::Event (Mouse::Event::type::Move, *this));
    TrimBuffer();
}

void Mouse::OnLeftPressed(int X, int Y) noexcept
{
    leftIsPressed = true;
    Buf.push(Mouse::Event(Mouse::Event::type::LPress, *this));
    TrimBuffer();
}

void Mouse::OnLeftReleased(int X, int Y) noexcept
{
    leftIsPressed = false;
    Buf.push(Mouse::Event(Mouse::Event::type::LRelease, *this));
}

void Mouse::OnWheelUp(int X, int Y) noexcept
{
    Buf.push(Mouse::Event(Mouse::Event::type::WheelUp, *this));
    TrimBuffer();
}

void Mouse::OnWheelDown(int X, int Y) noexcept
{
    Buf.push(Mouse::Event(Mouse::Event::type::WheelDown, *this));
    TrimBuffer();
}

void Mouse::OnRightPressed(int X, int Y) noexcept
{
    rightIsPressed = true;
    Buf.push(Mouse::Event(Mouse::Event::type::RPress, *this));
    TrimBuffer();
}

void Mouse::OnRightReleased(int X, int Y) noexcept
{
    rightIsPressed = false;
    Buf.push(Mouse::Event(Mouse::Event::type::RRelease, *this));
    TrimBuffer();
}

void Mouse::OnMiddlePressed(int X, int Y) noexcept
{
    middleIsPressed = true;
    Buf.push(Mouse::Event(Mouse::Event::type::MPress, *this));
    TrimBuffer();
}

void Mouse::OnMiddleReleased(int X, int Y) noexcept
{
    middleIsPressed = false;
    Buf.push(Mouse::Event(Mouse::Event::type::MRelease, *this));
    TrimBuffer();
}

void Mouse::OnMouseLeave() noexcept
{
    isInWindow = false;
    Buf.push(Mouse::Event(Mouse::Event::type::Leave, *this));
    TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
    isInWindow = true;
    Buf.push(Mouse::Event(Mouse::Event::type::Enter, *this));
    TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
    while (Buf.size() > BufSize)
    {
        Buf.pop();
    }
}
