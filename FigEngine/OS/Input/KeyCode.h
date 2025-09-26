#pragma once
#include <SDL3/SDL.h>
#include "../../Utilities/HashMap/ankerl/unordered_dense.h"
namespace Fig
{

    enum KeyCode
    {
        KeyCode_Unknown = SDL_SCANCODE_UNKNOWN,

        KeyCode_A = SDL_SCANCODE_A,
        KeyCode_B = SDL_SCANCODE_B,
        KeyCode_C = SDL_SCANCODE_C,
        KeyCode_D = SDL_SCANCODE_D,
        KeyCode_E = SDL_SCANCODE_E,
        KeyCode_F = SDL_SCANCODE_F,
        KeyCode_G = SDL_SCANCODE_G,
        KeyCode_H = SDL_SCANCODE_H,
        KeyCode_I = SDL_SCANCODE_I,
        KeyCode_J = SDL_SCANCODE_J,
        KeyCode_K = SDL_SCANCODE_K,
        KeyCode_L = SDL_SCANCODE_L,
        KeyCode_M = SDL_SCANCODE_M,
        KeyCode_N = SDL_SCANCODE_N,
        KeyCode_O = SDL_SCANCODE_O,
        KeyCode_P = SDL_SCANCODE_P,
        KeyCode_Q = SDL_SCANCODE_Q,
        KeyCode_R = SDL_SCANCODE_R,
        KeyCode_S = SDL_SCANCODE_S,
        KeyCode_T = SDL_SCANCODE_T,
        KeyCode_U = SDL_SCANCODE_U,
        KeyCode_V = SDL_SCANCODE_V,
        KeyCode_W = SDL_SCANCODE_W,
        KeyCode_X = SDL_SCANCODE_X,
        KeyCode_Y = SDL_SCANCODE_Y,
        KeyCode_Z = SDL_SCANCODE_Z,

        KeyCode_1 = SDL_SCANCODE_1,
        KeyCode_2 = SDL_SCANCODE_2,
        KeyCode_3 = SDL_SCANCODE_3,
        KeyCode_4 = SDL_SCANCODE_4,
        KeyCode_5 = SDL_SCANCODE_5,
        KeyCode_6 = SDL_SCANCODE_6,
        KeyCode_7 = SDL_SCANCODE_7,
        KeyCode_8 = SDL_SCANCODE_8,
        KeyCode_9 = SDL_SCANCODE_9,
        KeyCode_0 = SDL_SCANCODE_0,

        KeyCode_RETURN = SDL_SCANCODE_RETURN,
        KeyCode_ESCAPE = SDL_SCANCODE_ESCAPE,
        KeyCode_BACKSPACE = SDL_SCANCODE_BACKSPACE,
        KeyCode_TAB = SDL_SCANCODE_TAB,
        KeyCode_SPACE = SDL_SCANCODE_SPACE,

        KeyCode_MINUS = SDL_SCANCODE_MINUS,
        KeyCode_EQUALS = SDL_SCANCODE_EQUALS,
        KeyCode_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET,
        KeyCode_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET,
        KeyCode_BACKSLASH = SDL_SCANCODE_BACKSLASH,
        KeyCode_NONUSHASH = SDL_SCANCODE_NONUSHASH,
        KeyCode_SEMICOLON = SDL_SCANCODE_SEMICOLON,
        KeyCode_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
        KeyCode_GRAVE = SDL_SCANCODE_GRAVE,
        KeyCode_COMMA = SDL_SCANCODE_COMMA,
        KeyCode_PERIOD = SDL_SCANCODE_PERIOD,
        KeyCode_SLASH = SDL_SCANCODE_SLASH,

        KeyCode_CAPSLOCK = SDL_SCANCODE_CAPSLOCK,

        KeyCode_F1 = SDL_SCANCODE_F1,
        KeyCode_F2 = SDL_SCANCODE_F2,
        KeyCode_F3 = SDL_SCANCODE_F3,
        KeyCode_F4 = SDL_SCANCODE_F4,
        KeyCode_F5 = SDL_SCANCODE_F5,
        KeyCode_F6 = SDL_SCANCODE_F6,
        KeyCode_F7 = SDL_SCANCODE_F7,
        KeyCode_F8 = SDL_SCANCODE_F8,
        KeyCode_F9 = SDL_SCANCODE_F9,
        KeyCode_F10 = SDL_SCANCODE_F10,
        KeyCode_F11 = SDL_SCANCODE_F11,
        KeyCode_F12 = SDL_SCANCODE_F12,

        KeyCode_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN,
        KeyCode_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK,
        KeyCode_PAUSE = SDL_SCANCODE_PAUSE,
        KeyCode_INSERT = SDL_SCANCODE_INSERT,
        KeyCode_HOME = SDL_SCANCODE_HOME,
        KeyCode_PAGEUP = SDL_SCANCODE_PAGEUP,
        KeyCode_DELETE = SDL_SCANCODE_DELETE,
        KeyCode_END = SDL_SCANCODE_END,
        KeyCode_PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
        KeyCode_RIGHT = SDL_SCANCODE_RIGHT,
        KeyCode_LEFT = SDL_SCANCODE_LEFT,
        KeyCode_DOWN = SDL_SCANCODE_DOWN,
        KeyCode_UP = SDL_SCANCODE_UP,

        KeyCode_NUMLOCKCLEAR = SDL_SCANCODE_NUMLOCKCLEAR,
        KeyCode_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
        KeyCode_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,
        KeyCode_KP_MINUS = SDL_SCANCODE_KP_MINUS,
        KeyCode_KP_PLUS = SDL_SCANCODE_KP_PLUS,
        KeyCode_KP_ENTER = SDL_SCANCODE_KP_ENTER,
        KeyCode_KP_1 = SDL_SCANCODE_KP_1,
        KeyCode_KP_2 = SDL_SCANCODE_KP_2,
        KeyCode_KP_3 = SDL_SCANCODE_KP_3,
        KeyCode_KP_4 = SDL_SCANCODE_KP_4,
        KeyCode_KP_5 = SDL_SCANCODE_KP_5,
        KeyCode_KP_6 = SDL_SCANCODE_KP_6,
        KeyCode_KP_7 = SDL_SCANCODE_KP_7,
        KeyCode_KP_8 = SDL_SCANCODE_KP_8,
        KeyCode_KP_9 = SDL_SCANCODE_KP_9,
        KeyCode_KP_0 = SDL_SCANCODE_KP_0,
        KeyCode_KP_PERIOD = SDL_SCANCODE_KP_PERIOD,

        KeyCode_NONUSBACKSLASH = SDL_SCANCODE_NONUSBACKSLASH,
        KeyCode_APPLICATION = SDL_SCANCODE_APPLICATION,
        KeyCode_POWER = SDL_SCANCODE_POWER,
        KeyCode_KP_EQUALS = SDL_SCANCODE_KP_EQUALS,
        KeyCode_F13 = SDL_SCANCODE_F13,
        KeyCode_F14 = SDL_SCANCODE_F14,
        KeyCode_F15 = SDL_SCANCODE_F15,
        KeyCode_F16 = SDL_SCANCODE_F16,
        KeyCode_F17 = SDL_SCANCODE_F17,
        KeyCode_F18 = SDL_SCANCODE_F18,
        KeyCode_F19 = SDL_SCANCODE_F19,
        KeyCode_F20 = SDL_SCANCODE_F20,
        KeyCode_F21 = SDL_SCANCODE_F21,
        KeyCode_F22 = SDL_SCANCODE_F22,
        KeyCode_F23 = SDL_SCANCODE_F23,
        KeyCode_F24 = SDL_SCANCODE_F24,
        KeyCode_EXECUTE = SDL_SCANCODE_EXECUTE,
        KeyCode_HELP = SDL_SCANCODE_HELP,
        KeyCode_MENU = SDL_SCANCODE_MENU,
        KeyCode_SELECT = SDL_SCANCODE_SELECT,
        KeyCode_STOP = SDL_SCANCODE_STOP,
        KeyCode_AGAIN = SDL_SCANCODE_AGAIN,
        KeyCode_UNDO = SDL_SCANCODE_UNDO,
        KeyCode_CUT = SDL_SCANCODE_CUT,
        KeyCode_COPY = SDL_SCANCODE_COPY,
        KeyCode_PASTE = SDL_SCANCODE_PASTE,
        KeyCode_FIND = SDL_SCANCODE_FIND,
        KeyCode_MUTE = SDL_SCANCODE_MUTE,
        KeyCode_VOLUMEUP = SDL_SCANCODE_VOLUMEUP,
        KeyCode_VOLUMEDOWN = SDL_SCANCODE_VOLUMEDOWN,
        KeyCode_KP_COMMA = SDL_SCANCODE_KP_COMMA,
        KeyCode_KP_EQUALSAS400 = SDL_SCANCODE_KP_EQUALSAS400,

        KeyCode_INTERNATIONAL1 = SDL_SCANCODE_INTERNATIONAL1,
        KeyCode_INTERNATIONAL2 = SDL_SCANCODE_INTERNATIONAL2,
        KeyCode_INTERNATIONAL3 = SDL_SCANCODE_INTERNATIONAL3,
        KeyCode_INTERNATIONAL4 = SDL_SCANCODE_INTERNATIONAL4,
        KeyCode_INTERNATIONAL5 = SDL_SCANCODE_INTERNATIONAL5,
        KeyCode_INTERNATIONAL6 = SDL_SCANCODE_INTERNATIONAL6,
        KeyCode_INTERNATIONAL7 = SDL_SCANCODE_INTERNATIONAL7,
        KeyCode_INTERNATIONAL8 = SDL_SCANCODE_INTERNATIONAL8,
        KeyCode_INTERNATIONAL9 = SDL_SCANCODE_INTERNATIONAL9,
        KeyCode_LANG1 = SDL_SCANCODE_LANG1,
        KeyCode_LANG2 = SDL_SCANCODE_LANG2,
        KeyCode_LANG3 = SDL_SCANCODE_LANG3,
        KeyCode_LANG4 = SDL_SCANCODE_LANG4,
        KeyCode_LANG5 = SDL_SCANCODE_LANG5,
        KeyCode_LANG6 = SDL_SCANCODE_LANG6,
        KeyCode_LANG7 = SDL_SCANCODE_LANG7,
        KeyCode_LANG8 = SDL_SCANCODE_LANG8,
        KeyCode_LANG9 = SDL_SCANCODE_LANG9,

        KeyCode_ALTERASE = SDL_SCANCODE_ALTERASE,
        KeyCode_SYSREQ = SDL_SCANCODE_SYSREQ,
        KeyCode_CANCEL = SDL_SCANCODE_CANCEL,
        KeyCode_CLEAR = SDL_SCANCODE_CLEAR,
        KeyCode_PRIOR = SDL_SCANCODE_PRIOR,
        KeyCode_RETURN2 = SDL_SCANCODE_RETURN2,
        KeyCode_SEPARATOR = SDL_SCANCODE_SEPARATOR,
        KeyCode_OUT = SDL_SCANCODE_OUT,
        KeyCode_OPER = SDL_SCANCODE_OPER,
        KeyCode_CLEARAGAIN = SDL_SCANCODE_CLEARAGAIN,
        KeyCode_CRSEL = SDL_SCANCODE_CRSEL,
        KeyCode_EXSEL = SDL_SCANCODE_EXSEL,

        KeyCode_KP_00 = SDL_SCANCODE_KP_00,
        KeyCode_KP_000 = SDL_SCANCODE_KP_000,
        KeyCode_THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR,
        KeyCode_DECIMALSEPARATOR = SDL_SCANCODE_DECIMALSEPARATOR,
        KeyCode_CURRENCYUNIT = SDL_SCANCODE_CURRENCYUNIT,
        KeyCode_CURRENCYSUBUNIT = SDL_SCANCODE_CURRENCYSUBUNIT,
        KeyCode_KP_LEFTPAREN = SDL_SCANCODE_KP_LEFTPAREN,
        KeyCode_KP_RIGHTPAREN = SDL_SCANCODE_KP_RIGHTPAREN,
        KeyCode_KP_LEFTBRACE = SDL_SCANCODE_KP_LEFTBRACE,
        KeyCode_KP_RIGHTBRACE = SDL_SCANCODE_KP_RIGHTBRACE,
        KeyCode_KP_TAB = SDL_SCANCODE_KP_TAB,
        KeyCode_KP_BACKSPACE = SDL_SCANCODE_KP_BACKSPACE,
        KeyCode_KP_A = SDL_SCANCODE_KP_A,
        KeyCode_KP_B = SDL_SCANCODE_KP_B,
        KeyCode_KP_C = SDL_SCANCODE_KP_C,
        KeyCode_KP_D = SDL_SCANCODE_KP_D,
        KeyCode_KP_E = SDL_SCANCODE_KP_E,
        KeyCode_KP_F = SDL_SCANCODE_KP_F,
        KeyCode_KP_XOR = SDL_SCANCODE_KP_XOR,
        KeyCode_KP_POWER = SDL_SCANCODE_KP_POWER,
        KeyCode_KP_PERCENT = SDL_SCANCODE_KP_PERCENT,
        KeyCode_KP_LESS = SDL_SCANCODE_KP_LESS,
        KeyCode_KP_GREATER = SDL_SCANCODE_KP_GREATER,
        KeyCode_KP_AMPERSAND = SDL_SCANCODE_KP_AMPERSAND,
        KeyCode_KP_DBLAMPERSAND = SDL_SCANCODE_KP_DBLAMPERSAND,
        KeyCode_KP_VERTICALBAR = SDL_SCANCODE_KP_VERTICALBAR,

        KeyCode_LCTRL = SDL_SCANCODE_LCTRL,
        KeyCode_LSHIFT = SDL_SCANCODE_LSHIFT,
        KeyCode_LALT = SDL_SCANCODE_LALT,
        KeyCode_LGUI = SDL_SCANCODE_LGUI,
        KeyCode_RCTRL = SDL_SCANCODE_RCTRL,
        KeyCode_RSHIFT = SDL_SCANCODE_RSHIFT,
        KeyCode_RALT = SDL_SCANCODE_RALT,
        KeyCode_RGUI = SDL_SCANCODE_RGUI,
        KeyCode_MODE = SDL_SCANCODE_MODE,

        KeyCode_SLEEP = SDL_SCANCODE_SLEEP,
        KeyCode_WAKE = SDL_SCANCODE_WAKE,
        KeyCode_CHANNEL_INCREMENT = SDL_SCANCODE_CHANNEL_INCREMENT,
        KeyCode_CHANNEL_DECREMENT = SDL_SCANCODE_CHANNEL_DECREMENT,
        KeyCode_MEDIA_PLAY = SDL_SCANCODE_MEDIA_PLAY,
        KeyCode_MEDIA_PAUSE = SDL_SCANCODE_MEDIA_PAUSE,
        KeyCode_MEDIA_RECORD = SDL_SCANCODE_MEDIA_RECORD,
        KeyCode_MEDIA_FAST_FORWARD = SDL_SCANCODE_MEDIA_FAST_FORWARD,
        KeyCode_MEDIA_REWIND = SDL_SCANCODE_MEDIA_REWIND,
        KeyCode_MEDIA_NEXT_TRACK = SDL_SCANCODE_MEDIA_NEXT_TRACK,
        KeyCode_MEDIA_PREVIOUS_TRACK = SDL_SCANCODE_MEDIA_PREVIOUS_TRACK,
        KeyCode_MEDIA_STOP = SDL_SCANCODE_MEDIA_STOP,
        KeyCode_MEDIA_EJECT = SDL_SCANCODE_MEDIA_EJECT,
        KeyCode_MEDIA_PLAY_PAUSE = SDL_SCANCODE_MEDIA_PLAY_PAUSE,
        KeyCode_MEDIA_SELECT = SDL_SCANCODE_MEDIA_SELECT,
        KeyCode_AC_NEW = SDL_SCANCODE_AC_NEW,
        KeyCode_AC_OPEN = SDL_SCANCODE_AC_OPEN,
        KeyCode_AC_CLOSE = SDL_SCANCODE_AC_CLOSE,
        KeyCode_AC_EXIT = SDL_SCANCODE_AC_EXIT,
        KeyCode_AC_SAVE = SDL_SCANCODE_AC_SAVE,
        KeyCode_AC_PRINT = SDL_SCANCODE_AC_PRINT,
        KeyCode_AC_PROPERTIES = SDL_SCANCODE_AC_PROPERTIES,
        KeyCode_AC_SEARCH = SDL_SCANCODE_AC_SEARCH,
        KeyCode_AC_HOME = SDL_SCANCODE_AC_HOME,
        KeyCode_AC_BACK = SDL_SCANCODE_AC_BACK,
        KeyCode_AC_FORWARD = SDL_SCANCODE_AC_FORWARD,
        KeyCode_AC_STOP = SDL_SCANCODE_AC_STOP,
        KeyCode_AC_REFRESH = SDL_SCANCODE_AC_REFRESH,
        KeyCode_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS,
        KeyCode_SOFTLEFT = SDL_SCANCODE_SOFTLEFT,
        KeyCode_SOFTRIGHT = SDL_SCANCODE_SOFTRIGHT,
        KeyCode_CALL = SDL_SCANCODE_CALL,
        KeyCode_ENDCALL = SDL_SCANCODE_ENDCALL,
        KeyCode_RESERVED = SDL_SCANCODE_RESERVED,

        KeyCode_GAMEPAD_START_INDEX = KeyCode_RESERVED,

        KeyCode_GAMEPAD_SOUTH = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_SOUTH,           /**< Bottom face button (e.g. Xbox A button) */
        KeyCode_GAMEPAD_EAST = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_EAST,            /**< Right face button (e.g. Xbox B button) */
        KeyCode_GAMEPAD_WEST = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_WEST,            /**< Left face button (e.g. Xbox X button) */
        KeyCode_GAMEPAD_NORTH = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_NORTH,           /**< Top face button (e.g. Xbox Y button) */
        KeyCode_GAMEPAD_BACK = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_BACK,
        KeyCode_GAMEPAD_GUIDE = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_GUIDE,
        KeyCode_GAMEPAD_START = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_START,
        KeyCode_GAMEPAD_LEFT_STICK = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_LEFT_STICK,
        KeyCode_GAMEPAD_RIGHT_STICK = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_RIGHT_STICK,
        KeyCode_GAMEPAD_LEFT_SHOULDER = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_LEFT_SHOULDER,
        KeyCode_GAMEPAD_RIGHT_SHOULDER = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER,
        KeyCode_GAMEPAD_DPAD_UP = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_DPAD_UP,
        KeyCode_GAMEPAD_DPAD_DOWN = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_DPAD_DOWN,
        KeyCode_GAMEPAD_DPAD_LEFT = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_DPAD_LEFT,
        KeyCode_GAMEPAD_DPAD_RIGHT = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_DPAD_RIGHT,
        KeyCode_GAMEPAD_MISC1 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_MISC1,           /**< Additional button (e.g. Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button, Google Stadia capture button) */
        KeyCode_GAMEPAD_RIGHT_PADDLE1 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1,   /**< Upper or primary paddle, under your right hand (e.g. Xbox Elite paddle P1) */
        KeyCode_GAMEPAD_LEFT_PADDLE1 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_LEFT_PADDLE1,    /**< Upper or primary paddle, under your left hand (e.g. Xbox Elite paddle P3) */
        KeyCode_GAMEPAD_RIGHT_PADDLE2 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2,   /**< Lower or secondary paddle, under your right hand (e.g. Xbox Elite paddle P2) */
        KeyCode_GAMEPAD_LEFT_PADDLE2 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_LEFT_PADDLE2,    /**< Lower or secondary paddle, under your left hand (e.g. Xbox Elite paddle P4) */
        KeyCode_GAMEPAD_TOUCHPAD = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_TOUCHPAD,        /**< PS4/PS5 touchpad button */
        KeyCode_GAMEPAD_MISC2 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_MISC2,           /**< Additional button */
        KeyCode_GAMEPAD_MISC3 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_MISC3,           /**< Additional button */
        KeyCode_GAMEPAD_MISC4 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_MISC4,           /**< Additional button */
        KeyCode_GAMEPAD_MISC5 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_MISC5,           /**< Additional button */
        KeyCode_GAMEPAD_MISC6 = SDL_SCANCODE_RESERVED + 1 + SDL_GAMEPAD_BUTTON_MISC6,           /**< Additional button */
        KeyCode_GAMEPAD_END_INDEX = KeyCode_RESERVED + 1 + SDL_GAMEPAD_BUTTON_COUNT,

        KeyCode_MOUSE_START = KeyCode_GAMEPAD_END_INDEX,
        KeyCode_MOUSE_LEFT = KeyCode_MOUSE_START + SDL_BUTTON_LEFT,   // SDL_BUTTON_LEFT
        KeyCode_MOUSE_MIDDLE = KeyCode_MOUSE_START + SDL_BUTTON_MIDDLE, // SDL_BUTTON_MIDDLE
        KeyCode_MOUSE_RIGHT = KeyCode_MOUSE_START + SDL_BUTTON_RIGHT,  // SDL_BUTTON_RIGHT
        KeyCode_MOUSE_X1 = KeyCode_MOUSE_START + SDL_BUTTON_X1,     // SDL_BUTTON_X1
        KeyCode_MOUSE_X2 = KeyCode_MOUSE_START + SDL_BUTTON_X2,     // SDL_BUTTON_X2
        KeyCode_MOUSE_END = KeyCode_MOUSE_X2 + 1,


        KeyCode_COUNT = SDL_SCANCODE_COUNT
    };

    enum InputAxis
    {
        InputAxis_None = 0,
        InputAxis_MOUSE_X = 1,
        InputAxis_MOUSE_Y = 2,
        InputAxis_MOUSE_WHEEL_X = 3,
        InputAxis_MOUSE_WHEEL_Y = 4,
        InputAxis_MOUSE_END = 5,

        InputAxis_GAMEPAD_START = InputAxis_MOUSE_END,
        InputAxis_GAMEPAD_LEFTX = InputAxis_GAMEPAD_START + SDL_GAMEPAD_AXIS_LEFTX + 1,
        InputAxis_GAMEPAD_LEFTY = InputAxis_GAMEPAD_START + SDL_GAMEPAD_AXIS_LEFTY + 1,
        InputAxis_GAMEPAD_RIGHTX = InputAxis_GAMEPAD_START + SDL_GAMEPAD_AXIS_RIGHTX + 1,
        InputAxis_GAMEPAD_RIGHTY = InputAxis_GAMEPAD_START + SDL_GAMEPAD_AXIS_RIGHTY + 1,
        InputAxis_GAMEPAD_LEFT_TRIGGER = InputAxis_GAMEPAD_START + SDL_GAMEPAD_AXIS_LEFT_TRIGGER + 1,
        InputAxis_GAMEPAD_RIGHT_TRIGGER = InputAxis_GAMEPAD_START + SDL_GAMEPAD_AXIS_RIGHT_TRIGGER + 1,
        InputAxis_GAMEPAD_END = InputAxis_GAMEPAD_START + SDL_GAMEPAD_AXIS_COUNT + 1,
        InputAxis_COUNT = InputAxis_GAMEPAD_END


    };

    static const ankerl::unordered_dense::map<
        std::string_view, InputAxis
    >AxisNames =
    {
        {"none", InputAxis_None},
        {"mouse x", InputAxis_MOUSE_X}, {"mouse y", InputAxis_MOUSE_Y},
        {"mouse wheel x", InputAxis_MOUSE_WHEEL_X}, {"mouse wheel y", InputAxis_MOUSE_WHEEL_Y},
        {"gamepad left x", InputAxis_GAMEPAD_LEFTX}, {"gamepad left y", InputAxis_GAMEPAD_LEFTY},
        {"gamepad right x", InputAxis_GAMEPAD_RIGHTX}, {"gamepad right y", InputAxis_GAMEPAD_RIGHTY},
        {"gamepad left trigger", InputAxis_GAMEPAD_LEFT_TRIGGER}, { "gamepad right trigger", InputAxis_GAMEPAD_RIGHT_TRIGGER },
    };

    static const ankerl::unordered_dense::map<
        std::string_view, KeyCode
    >KeyNames =
    {
        {"unknown", KeyCode_Unknown},

        /* letters */
        {"a", KeyCode_A}, {"b", KeyCode_B}, {"c", KeyCode_C}, {"d", KeyCode_D},
        {"e", KeyCode_E}, {"f", KeyCode_F}, {"g", KeyCode_G}, {"h", KeyCode_H},
        {"i", KeyCode_I}, {"j", KeyCode_J}, {"k", KeyCode_K}, {"l", KeyCode_L},
        {"m", KeyCode_M}, {"n", KeyCode_N}, {"o", KeyCode_O}, {"p", KeyCode_P},
        {"q", KeyCode_Q}, {"r", KeyCode_R}, {"s", KeyCode_S}, {"t", KeyCode_T},
        {"u", KeyCode_U}, {"v", KeyCode_V}, {"w", KeyCode_W}, {"x", KeyCode_X},
        {"y", KeyCode_Y}, {"z", KeyCode_Z},

        /* numbers */
        {"1", KeyCode_1}, {"2", KeyCode_2}, {"3", KeyCode_3}, {"4", KeyCode_4},
        {"5", KeyCode_5}, {"6", KeyCode_6}, {"7", KeyCode_7}, {"8", KeyCode_8},
        {"9", KeyCode_9}, {"0", KeyCode_0},

        /* common controls */
        {"return", KeyCode_RETURN}, {"escape", KeyCode_ESCAPE}, {"backspace", KeyCode_BACKSPACE},
        {"tab", KeyCode_TAB}, {"space", KeyCode_SPACE},

        /* punctuation */
        {"minus", KeyCode_MINUS}, {"equals", KeyCode_EQUALS},
        {"left bracket", KeyCode_LEFTBRACKET}, {"right bracket", KeyCode_RIGHTBRACKET},
        {"backslash", KeyCode_BACKSLASH}, {"non us hash", KeyCode_NONUSHASH},
        {"semicolon", KeyCode_SEMICOLON}, {"apostrophe", KeyCode_APOSTROPHE},
        {"grave", KeyCode_GRAVE}, {"comma", KeyCode_COMMA}, {"period", KeyCode_PERIOD},
        {"slash", KeyCode_SLASH},

        {"caps lock", KeyCode_CAPSLOCK},

        /* function keys */
        {"f1", KeyCode_F1}, {"f2", KeyCode_F2}, {"f3", KeyCode_F3}, {"f4", KeyCode_F4},
        {"f5", KeyCode_F5}, {"f6", KeyCode_F6}, {"f7", KeyCode_F7}, {"f8", KeyCode_F8},
        {"f9", KeyCode_F9}, {"f10", KeyCode_F10}, {"f11", KeyCode_F11}, {"f12", KeyCode_F12},
        {"f13", KeyCode_F13}, {"f14", KeyCode_F14}, {"f15", KeyCode_F15}, {"f16", KeyCode_F16},
        {"f17", KeyCode_F17}, {"f18", KeyCode_F18}, {"f19", KeyCode_F19}, {"f20", KeyCode_F20},
        {"f21", KeyCode_F21}, {"f22", KeyCode_F22}, {"f23", KeyCode_F23}, {"f24", KeyCode_F24},

        /* navigation */
        {"print screen", KeyCode_PRINTSCREEN}, {"scroll lock", KeyCode_SCROLLLOCK}, {"pause", KeyCode_PAUSE},
        {"insert", KeyCode_INSERT}, {"home", KeyCode_HOME}, {"page up", KeyCode_PAGEUP},
        {"delete", KeyCode_DELETE}, {"end", KeyCode_END}, {"page down", KeyCode_PAGEDOWN},
        {"right", KeyCode_RIGHT}, {"left", KeyCode_LEFT}, {"down", KeyCode_DOWN}, {"up", KeyCode_UP},

        /* numpad / keypad */
        {"num lock", KeyCode_NUMLOCKCLEAR},
        {"numpad divide", KeyCode_KP_DIVIDE}, {"numpad multiply", KeyCode_KP_MULTIPLY},
        {"numpad minus", KeyCode_KP_MINUS}, {"numpad plus", KeyCode_KP_PLUS},
        {"numpad enter", KeyCode_KP_ENTER},
        {"numpad 1", KeyCode_KP_1}, {"numpad 2", KeyCode_KP_2}, {"numpad 3", KeyCode_KP_3},
        {"numpad 4", KeyCode_KP_4}, {"numpad 5", KeyCode_KP_5}, {"numpad 6", KeyCode_KP_6},
        {"numpad 7", KeyCode_KP_7}, {"numpad 8", KeyCode_KP_8}, {"numpad 9", KeyCode_KP_9},
        {"numpad 0", KeyCode_KP_0}, {"numpad period", KeyCode_KP_PERIOD},
        {"non us backslash", KeyCode_NONUSBACKSLASH}, {"application", KeyCode_APPLICATION},
        {"power", KeyCode_POWER}, {"numpad equals", KeyCode_KP_EQUALS},

        /* editing / special */
        {"execute", KeyCode_EXECUTE}, {"help", KeyCode_HELP}, {"menu", KeyCode_MENU},
        {"select", KeyCode_SELECT}, {"stop", KeyCode_STOP}, {"again", KeyCode_AGAIN},
        {"undo", KeyCode_UNDO}, {"cut", KeyCode_CUT}, {"copy", KeyCode_COPY}, {"paste", KeyCode_PASTE},
        {"find", KeyCode_FIND}, {"mute", KeyCode_MUTE}, {"volume up", KeyCode_VOLUMEUP},
        {"volume down", KeyCode_VOLUMEDOWN}, {"numpad comma", KeyCode_KP_COMMA},
        {"numpad equals as400", KeyCode_KP_EQUALSAS400},

        /* international / language */
        {"international 1", KeyCode_INTERNATIONAL1}, {"international 2", KeyCode_INTERNATIONAL2},
        {"international 3", KeyCode_INTERNATIONAL3}, {"international 4", KeyCode_INTERNATIONAL4},
        {"international 5", KeyCode_INTERNATIONAL5}, {"international 6", KeyCode_INTERNATIONAL6},
        {"international 7", KeyCode_INTERNATIONAL7}, {"international 8", KeyCode_INTERNATIONAL8},
        {"international 9", KeyCode_INTERNATIONAL9},
        {"lang 1", KeyCode_LANG1}, {"lang 2", KeyCode_LANG2}, {"lang 3", KeyCode_LANG3},
        {"lang 4", KeyCode_LANG4}, {"lang 5", KeyCode_LANG5}, {"lang 6", KeyCode_LANG6},
        {"lang 7", KeyCode_LANG7}, {"lang 8", KeyCode_LANG8}, {"lang 9", KeyCode_LANG9},

        {"alt erase", KeyCode_ALTERASE}, {"sys req", KeyCode_SYSREQ}, {"cancel", KeyCode_CANCEL},
        {"clear", KeyCode_CLEAR}, {"prior", KeyCode_PRIOR}, {"return2", KeyCode_RETURN2},
        {"separator", KeyCode_SEPARATOR}, {"out", KeyCode_OUT}, {"oper", KeyCode_OPER},
        {"clear again", KeyCode_CLEARAGAIN}, {"cr sel", KeyCode_CRSEL}, {"ex sel", KeyCode_EXSEL},

        {"numpad 00", KeyCode_KP_00}, {"numpad 000", KeyCode_KP_000},
        {"thousands separator", KeyCode_THOUSANDSSEPARATOR}, {"decimal separator", KeyCode_DECIMALSEPARATOR},
        {"currency unit", KeyCode_CURRENCYUNIT}, {"currency subunit", KeyCode_CURRENCYSUBUNIT},
        {"numpad left parenthesis", KeyCode_KP_LEFTPAREN}, {"numpad right parenthesis", KeyCode_KP_RIGHTPAREN},
        {"numpad left brace", KeyCode_KP_LEFTBRACE}, {"numpad right brace", KeyCode_KP_RIGHTBRACE},
        {"numpad tab", KeyCode_KP_TAB}, {"numpad backspace", KeyCode_KP_BACKSPACE},
        {"numpad a", KeyCode_KP_A}, {"numpad b", KeyCode_KP_B}, {"numpad c", KeyCode_KP_C},
        {"numpad d", KeyCode_KP_D}, {"numpad e", KeyCode_KP_E}, {"numpad f", KeyCode_KP_F},
        {"numpad xor", KeyCode_KP_XOR}, {"numpad power", KeyCode_KP_POWER}, {"numpad percent", KeyCode_KP_PERCENT},
        {"numpad less", KeyCode_KP_LESS}, {"numpad greater", KeyCode_KP_GREATER},
        {"numpad ampersand", KeyCode_KP_AMPERSAND}, {"numpad dbl ampersand", KeyCode_KP_DBLAMPERSAND},
        {"numpad vertical bar", KeyCode_KP_VERTICALBAR},

        /* modifiers */
        {"left ctrl", KeyCode_LCTRL}, {"left shift", KeyCode_LSHIFT}, {"left alt", KeyCode_LALT},
        {"left gui", KeyCode_LGUI}, {"right ctrl", KeyCode_RCTRL}, {"right shift", KeyCode_RSHIFT},
        {"right alt", KeyCode_RALT}, {"right gui", KeyCode_RGUI}, {"mode", KeyCode_MODE},

        /* system / media / channels */
        {"sleep", KeyCode_SLEEP}, {"wake", KeyCode_WAKE},
        {"channel increment", KeyCode_CHANNEL_INCREMENT}, {"channel decrement", KeyCode_CHANNEL_DECREMENT},
        {"media play", KeyCode_MEDIA_PLAY}, {"media pause", KeyCode_MEDIA_PAUSE},
        {"media record", KeyCode_MEDIA_RECORD}, {"media fast forward", KeyCode_MEDIA_FAST_FORWARD},
        {"media rewind", KeyCode_MEDIA_REWIND}, {"media next track", KeyCode_MEDIA_NEXT_TRACK},
        {"media previous track", KeyCode_MEDIA_PREVIOUS_TRACK}, {"media stop", KeyCode_MEDIA_STOP},
        {"media eject", KeyCode_MEDIA_EJECT}, {"media play pause", KeyCode_MEDIA_PLAY_PAUSE},
        {"media select", KeyCode_MEDIA_SELECT},

        /* application control */
        {"ac new", KeyCode_AC_NEW}, {"ac open", KeyCode_AC_OPEN}, {"ac close", KeyCode_AC_CLOSE},
        {"ac exit", KeyCode_AC_EXIT}, {"ac save", KeyCode_AC_SAVE}, {"ac print", KeyCode_AC_PRINT},
        {"ac properties", KeyCode_AC_PROPERTIES}, {"ac search", KeyCode_AC_SEARCH}, {"ac home", KeyCode_AC_HOME},
        {"ac back", KeyCode_AC_BACK}, {"ac forward", KeyCode_AC_FORWARD}, {"ac stop", KeyCode_AC_STOP},
        {"ac refresh", KeyCode_AC_REFRESH}, {"ac bookmarks", KeyCode_AC_BOOKMARKS},

        {"soft left", KeyCode_SOFTLEFT}, {"soft right", KeyCode_SOFTRIGHT}, {"call", KeyCode_CALL},
        {"end call", KeyCode_ENDCALL}, {"reserved", KeyCode_RESERVED},

        /* gamepad buttons */
        {"gamepad south", KeyCode_GAMEPAD_SOUTH}, {"gamepad east", KeyCode_GAMEPAD_EAST},
        {"gamepad west", KeyCode_GAMEPAD_WEST}, {"gamepad north", KeyCode_GAMEPAD_NORTH},
        {"gamepad back", KeyCode_GAMEPAD_BACK}, {"gamepad guide", KeyCode_GAMEPAD_GUIDE},
        {"gamepad start", KeyCode_GAMEPAD_START}, {"gamepad left stick", KeyCode_GAMEPAD_LEFT_STICK},
        {"gamepad right stick", KeyCode_GAMEPAD_RIGHT_STICK}, {"gamepad left shoulder", KeyCode_GAMEPAD_LEFT_SHOULDER},
        {"gamepad right shoulder", KeyCode_GAMEPAD_RIGHT_SHOULDER}, {"gamepad dpad up", KeyCode_GAMEPAD_DPAD_UP},
        {"gamepad dpad down", KeyCode_GAMEPAD_DPAD_DOWN}, {"gamepad dpad left", KeyCode_GAMEPAD_DPAD_LEFT},
        {"gamepad dpad right", KeyCode_GAMEPAD_DPAD_RIGHT}, {"gamepad misc1", KeyCode_GAMEPAD_MISC1},
        {"gamepad right paddle1", KeyCode_GAMEPAD_RIGHT_PADDLE1}, {"gamepad left paddle1", KeyCode_GAMEPAD_LEFT_PADDLE1},
        {"gamepad right paddle2", KeyCode_GAMEPAD_RIGHT_PADDLE2}, {"gamepad left paddle2", KeyCode_GAMEPAD_LEFT_PADDLE2},
        {"gamepad touchpad", KeyCode_GAMEPAD_TOUCHPAD}, {"gamepad misc2", KeyCode_GAMEPAD_MISC2},
        {"gamepad misc3", KeyCode_GAMEPAD_MISC3}, {"gamepad misc4", KeyCode_GAMEPAD_MISC4},
        {"gamepad misc5", KeyCode_GAMEPAD_MISC5}, {"gamepad misc6", KeyCode_GAMEPAD_MISC6},

        /* mouse buttons */
        {"mouse left", KeyCode_MOUSE_LEFT}, {"mouse middle", KeyCode_MOUSE_MIDDLE},
        {"mouse right", KeyCode_MOUSE_RIGHT}, {"mouse x1", KeyCode_MOUSE_X1}, {"mouse x2", KeyCode_MOUSE_X2},
    };
}