#pragma once
#include "SDL3/SDL.h"
#include "KeyCode.h"
#include <string_view>
#include "../../Utilities/GLMath.h"
namespace Fig
{
	enum KeyState : char
	{
		KeyState_None = 0,
		KeyState_Pressed = 1,
		KeyState_Holding = 2,
		KeyState_Released = 3,

	};

	class Input
	{
	public:
		static void Init();
		static bool HandleEvent(SDL_Event& event);
		static void Update(float delta);


		static bool GetKeyDown(KeyCode keycode, int user = -1);
		static bool GetKey(KeyCode keycode, int user = -1);
		static bool GetKeyUp(KeyCode keycode, int user = -1);
		static float GetHoldTime(KeyCode keycode, int user = -1);

		static bool GetKeyDown(::std::string_view keyname, int user = -1);
		static bool GetKey(::std::string_view keyname, int user = -1);
		static bool GetKeyUp(::std::string_view keyname, int user = -1);
		static float GetHoldTime(::std::string_view keyname, int user = -1);

		static float GetAxis(InputAxis axis, int user = -1);
		static float GetAxis(::std::string_view axisname, int user = -1);

		static KeyCode GetKeyCode(::std::string_view keyname);
		static InputAxis GetInputAxis(::std::string_view axisname);

		static Vector2 GetMousePosition();
		static void GetMousePosition(int& x, int& y);
	private:
		static void KeyDown(KeyCode scancode);
		static void KeyUp(KeyCode scancode);
		
		static void AxisValueChanged(InputAxis axis,float value);

	private:


		static KeyState* KeyStates;
		//static KeyState* GamepadKeyStates;

		static float* KeyHoldTimes;
		//static float* GamepadKeyHoldTimes;

		static float* AxisValues;
		//static float* GamepadAxisValues;

		static int mouseX, mouseY;
		


	};
}

