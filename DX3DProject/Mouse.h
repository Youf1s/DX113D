#pragma once
#include <queue>
class Mouse
{
	friend class Window;

public:
	class Event
	{
	public:
		enum class type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			MPress,
			MRelease,
			WheelUp,
			WheelDown,
			Enter,
			Leave,
			Move,
			Invalid
		};

	private:
		type Type;
		bool IsLeftPressed;
		bool IsRightPressed;
		bool IsMiddlePressed;
		bool IsInWindow;
		int X;
		int Y;

	public:
		Event() noexcept 
			:
			Type(type::Invalid),
			IsLeftPressed(false),
			IsRightPressed(false),
			IsMiddlePressed(false),
			IsInWindow(true),
			X(0),
			Y(0)
		
		{}
		Event(type Type, const Mouse& MouseIn) noexcept
			:
			Type(Type),
			IsLeftPressed(MouseIn.leftIsPressed),
			IsRightPressed(MouseIn.rightIsPressed),
			X(MouseIn.X),
			Y(MouseIn.Y)

		{}

		bool IsValid()const noexcept {
			return Type != type::Invalid;
		}
		bool LeftIsPressed() const noexcept {
			return IsLeftPressed;
		}
		bool RightIsPressed() const noexcept {
			return IsRightPressed;
		}
		bool MiddleIsPressed()const noexcept {
			return IsMiddlePressed;
		}
		type GetType() const noexcept {
			return Type;
		}
		std::pair<int, int>GetPos() const noexcept {
			return{ X, Y };
		}
		int GetPosX() const noexcept {
			return X;
		}
		int GetPosY() const noexcept {
			return Y;
		}
	};

public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	std::pair<int, int>GetPos()const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	bool IsInWindow() const noexcept;
	Mouse::Event Read() noexcept;
	bool IsEmpty() const noexcept
	{
		return Buf.empty();
	}
	void EmptyAll()  noexcept;
private:
	void OnMouseMove(int X, int Y) noexcept;
	void OnLeftPressed(int X, int Y) noexcept;
	void OnLeftReleased(int X, int Y) noexcept;
	void OnWheelUp(int X, int Y) noexcept;
	void OnWheelDown(int X, int Y) noexcept;
	void OnRightPressed(int X, int Y) noexcept;
	void OnRightReleased(int X, int Y) noexcept;
	void OnMiddlePressed(int X, int Y) noexcept;
	void OnMiddleReleased(int X, int Y) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void TrimBuffer() noexcept;
private:
	static constexpr unsigned int BufSize = 16u;
	int X;
	int Y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool middleIsPressed = false;
	bool isInWindow = false;
	std::queue<Event> Buf;
	
};

