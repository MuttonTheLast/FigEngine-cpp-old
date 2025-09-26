#include "pch.h"
#include "Input.h"
#include <iostream>
#include "../../Utilities/Log/Logger.h"
namespace Fig
{
	KeyState* Input::KeyStates = new KeyState[KeyCode_COUNT]();
	//KeyState* Input::GamepadKeyStates = new KeyState[SDL_GAMEPAD_BUTTON_COUNT * 4]();

	float* Input::KeyHoldTimes = new float[KeyCode_COUNT]();
	//float* Input::GamepadKeyHoldTimes = new float[SDL_GAMEPAD_BUTTON_COUNT * 4]();

	float* Input::AxisValues = new float[InputAxis_COUNT]();
	//float* Input::GamepadAxisValues = new float[SDL_GAMEPAD_AXIS_COUNT * 4]();

	int Input::mouseX = 0;
	int Input::mouseY = 0;

	bool Input::HandleEvent(SDL_Event& event)
	{
		switch (event.type)
		{
		case SDL_EVENT_TEXT_INPUT:
			break;
		case SDL_EVENT_KEY_DOWN:
			if (!event.key.repeat)
			{
				KeyDown((KeyCode)event.key.scancode);
			}
			break;
		case SDL_EVENT_KEY_UP:
			KeyUp((KeyCode)event.key.scancode);
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			KeyDown((KeyCode)(event.button.button + KeyCode_MOUSE_START));
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			KeyUp((KeyCode)(event.button.button + KeyCode_MOUSE_START));
			break;
		case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
			KeyDown((KeyCode)(event.gbutton.button + KeyCode_GAMEPAD_START_INDEX + 1));
			// TODO:  Add multiple  gamepad
			// GamepadKeyStates[event.gbutton.which * SDL_GAMEPAD_BUTTON_COUNT + event.gbutton.button] = KeyState_Pressed;
			// std::cout << "Gamepad Button Down: " << (int)event.gbutton.button + KeyCode_GAMEPAD_START_INDEX + 1 << " on device " << event.gbutton.which << "\n";
			break;
		case SDL_EVENT_GAMEPAD_BUTTON_UP:
			KeyUp((KeyCode)(event.gbutton.button + KeyCode_GAMEPAD_START_INDEX + 1));
			// TODO:  Add multiple  gamepad
			//GamepadKeyStates[event.gbutton.which * SDL_GAMEPAD_BUTTON_COUNT + event.gbutton.button] = KeyState_Released;  
			break;
		case SDL_EVENT_GAMEPAD_AXIS_MOTION:
			if (event.gaxis.value <=  100 && event.gaxis.value >=  -100)
			{
				event.gaxis.value = 0;
			}
			AxisValueChanged( (InputAxis)(InputAxis_GAMEPAD_START + event.gaxis.axis + 1), event.gaxis.value / 32767.0f);
			// TODO:  Add multiple  gamepad
			// GamepadAxisValues[event.gaxis.which * SDL_GAMEPAD_AXIS_COUNT + event.gaxis.axis] = event.gaxis.value / 32767.0f;
			break;
		case SDL_EVENT_GAMEPAD_ADDED:
		{
			SDL_Gamepad* pad = SDL_OpenGamepad(event.gdevice.which);
			if (!pad) {
				
				Logger::Warn(std::string("Could not open gamepad: ") + SDL_GetError(), "App", true);
			}
		}
			break;
		case SDL_EVENT_GAMEPAD_REMOVED:
			SDL_CloseGamepad(SDL_GetGamepadFromID(event.gdevice.which));
			break;
		case SDL_EVENT_MOUSE_MOTION:
			AxisValueChanged(InputAxis_MOUSE_X, event.motion.xrel);
			AxisValueChanged(InputAxis_MOUSE_Y, event.motion.yrel);
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			break;
		default:
			return false;
		}
		return true;
	}

	void Input::Update(float delta)
	{

		for (int i = 0; i < InputAxis_MOUSE_END; i++)
		{
			AxisValues[i] = 0.0f;
		}

		//for (int i = 0; i < SDL_GAMEPAD_AXIS_COUNT * 4; i++)
		//{
			//GamepadAxisValues[i] = 0.0f;
		//}
		for (int i = 0; i < KeyCode_COUNT; i++)
		{
			if (KeyStates[i] == KeyState_Pressed)
			{
				KeyStates[i] = KeyState_Holding;
			}
			else if (KeyStates[i] == KeyState_Released)
			{
				KeyHoldTimes[i] = 0.0f;
				KeyStates[i] = KeyState_None;
			}
			if (KeyStates[i] == KeyState_Holding)
			{
				KeyHoldTimes[i] += delta;
			}
		}
		//for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT * 4; i++)
		//{
			//if (GamepadKeyStates[i] == KeyState_Pressed)
			//{
				//GamepadKeyStates[i] = KeyState_Holding;
			//}
			//else if (GamepadKeyStates[i] == KeyState_Released)
			//{
				//GamepadKeyHoldTimes[i] = 0.0f;
				//GamepadKeyStates[i] = KeyState_None;
			//}
			//if (GamepadKeyStates[i] == KeyState_Holding)
			//{
				//GamepadKeyHoldTimes[i] += delta;
			//}
		//}
	}
	//TODO: Add multiple gamepad support (currently it is bug but its ok for pc games and engine for now)


	bool Input::GetKeyDown(KeyCode keycode, int user)
	{
		//if (user > -1 && keycode > KeyCode_GAMEPAD_START_INDEX && keycode < KeyCode_GAMEPAD_END_INDEX)
		//{
			//return GamepadKeyStates[user * SDL_GAMEPAD_BUTTON_COUNT + keycode - KeyCode_GAMEPAD_START_INDEX - 1] == KeyState_Pressed;
		//}
		return KeyStates[keycode] == KeyState_Pressed;
	}
	bool Input::GetKey(KeyCode keycode, int user)
	{
		//if (user > -1 && keycode > KeyCode_GAMEPAD_START_INDEX && keycode < KeyCode_GAMEPAD_END_INDEX)
		//{
			//KeyState state = GamepadKeyStates[user * SDL_GAMEPAD_BUTTON_COUNT + keycode - KeyCode_GAMEPAD_START_INDEX - 1];
			//return state == KeyState_Holding || state == KeyState_Pressed;
		//}
		return KeyStates[keycode] == KeyState_Holding || KeyStates[keycode] == KeyState_Pressed;
	}
	bool Input::GetKeyUp(KeyCode keycode, int user)
	{
		//if (user > -1 && keycode > KeyCode_GAMEPAD_START_INDEX && keycode < KeyCode_GAMEPAD_END_INDEX)
		//{
			//return GamepadKeyStates[user * SDL_GAMEPAD_BUTTON_COUNT + keycode - KeyCode_GAMEPAD_START_INDEX - 1] == KeyState_Released;
		//}
		return KeyStates[keycode] == KeyState_Released;
	}
	float Input::GetHoldTime(KeyCode keycode, int user)
	{
		//if (user > -1 && keycode > KeyCode_GAMEPAD_START_INDEX && keycode < KeyCode_GAMEPAD_END_INDEX)
		//{
			//return KeyHoldTimes[user * SDL_GAMEPAD_BUTTON_COUNT + keycode - KeyCode_GAMEPAD_START_INDEX - 1];
		//}
		return KeyHoldTimes[keycode];
	}
	bool Input::GetKeyDown(::std::string_view keyname, int user)
	{
		return GetKeyDown(GetKeyCode(keyname), user);
	}
	bool Input::GetKey(::std::string_view keyname, int user)
	{
		return GetKey(GetKeyCode(keyname), user);
	}
	bool Input::GetKeyUp(::std::string_view keyname, int user)
	{
		return GetKeyUp(GetKeyCode(keyname), user);
	}
	float Input::GetHoldTime(::std::string_view keyname, int user)
	{
		return GetHoldTime(GetKeyCode(keyname), user);
	}
	float Input::GetAxis(InputAxis axis, int user)
	{
		//if (user > -1 && axis > InputAxis_GAMEPAD_START && axis < InputAxis_GAMEPAD_END)
		//{
			//return GamepadAxisValues[user * SDL_GAMEPAD_AXIS_COUNT + axis - InputAxis_GAMEPAD_START - 1];
		//}
		return AxisValues[axis];
	}
	float Input::GetAxis(::std::string_view axisname, int user)
	{
		return GetAxis(GetInputAxis(axisname), user);
	}
	KeyCode Input::GetKeyCode(::std::string_view keyname)
	{
		if (auto it = KeyNames.find(keyname); it != KeyNames.end()) {
			return it->second;
		}
		return KeyCode_Unknown;
	}
	InputAxis Input::GetInputAxis(::std::string_view axisname)
	{
		if (auto it = AxisNames.find(axisname); it != AxisNames.end()) {
			return it->second;
		}
		return InputAxis_None;
	}
	Vector2 Input::GetMousePosition()
	{
		return Vector2(mouseX, mouseY);
	}
	void Input::GetMousePosition(int& x, int& y)
	{
		x = mouseX;
		y = mouseY;
	}
	void Input::KeyDown(KeyCode scancode)
	{
		KeyStates[scancode] = KeyState_Pressed;
	}
	void Input::KeyUp(KeyCode scancode)
	{
		KeyStates[scancode] = KeyState_Released;
	}

	void Input::AxisValueChanged(InputAxis axis, float value)
	{
		AxisValues[axis] = value;
	}
	


}