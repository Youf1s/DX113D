#pragma once
#include <queue>
#include <bitset>
class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class type {
			Press,
			Release,
			Invalid
		};
	private:
		type Type;
		unsigned char Code;
	public:
		Event() noexcept
			:
			Type(type::Invalid),
			Code(0u)


		{}
		Event(type Type, unsigned char code) noexcept
			:
			Type(Type),
			Code(Code)
		{}

		bool IsPress()const {
			return Type == type::Press;
		}
		bool IsRelease()const {
			return Type == type::Release;
		}
		bool IsValid()const {
			return Type == type::Invalid;
		}
		unsigned char GetCode() const {
			return Code;
		}
	};

public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	bool KeyIsPressed(unsigned int Code) const noexcept;
	bool KeyIsEmpty() const noexcept;
	void EmptyKey() noexcept;
	Event ReadKey() noexcept;

	char ReadChar() noexcept;
	bool CharIsEmpty()const noexcept;
	void EmptyChar() noexcept;
	void EmptyAll() noexcept;

	void ActivateAutoRepeat() noexcept;
	void DisableAutoRepeat() noexcept;
	bool IsAutoRepeatActive() noexcept;

private:
	void OnKeyPressed(unsigned char Code) noexcept;
	void OnKeyReleased(unsigned char Code) noexcept;
	void OnChar(char Character) noexcept;
	void ClearSt() noexcept;
	template<typename T>
	static void CutBuf(std::queue<T>& Buffer) noexcept;
private:
	static constexpr unsigned int NKeys = 256u;
	static constexpr unsigned int BufSize = 16u;
	bool AutoRepeatActive = false;
	std::bitset<NKeys> KeyStates;
	std::queue<char> CharBuf;
	std::queue<Event> KeyBuf;
};


