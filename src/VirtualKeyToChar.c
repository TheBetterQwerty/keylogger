#include <ctype.h>
#include "VirtualKeyToChar.h"

char VirtualKeyToChar(DWORD vKey) {
    int is_SHIFT_down = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    int is_CAPS_down  = (GetAsyncKeyState(VK_CAPITAL) & 0x8000) != 0; 
    int is_CTRL_down  = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0; 

    // Map the vkeys into chars
    UINT vkey = MapVirtualKey(vKey, MAPVK_VK_TO_CHAR);
    char VKCODE = (char) vkey;

    // Shift is pressed
    if (is_SHIFT_down) {
        switch (vKey) {
        // Digits 1 to 9
            case 0x31: return '!';  // 1S
            case 0x32: return '@';  // 2
            case 0x33: return '#';  // 3
            case 0x34: return '$';  // 4
            case 0x35: return '%';  // 5
            case 0x36: return '^';  // 6
            case 0x37: return '&';  // 7
            case 0x38: return '*';  // 8
            case 0x39: return '(';  // 9
            case 0x30: return ')';  // 0

            // Punctuation
            case 0x5f: return '_';
            case 0x2d: return '-';  // - -> _
            case 0x3d: return '+';  // = -> +
            case 0x5b: return '{';  // [ -> {
            case 0x5d: return '}';  // ] -> }
            case 0x5c: return '|';  // \ -> |
            case 0x3b: return ':';  // ; -> :
            case 0x27: return '"';  // ' -> "
            case 0x2c: return '<';  // , -> <
            case 0x2e: return '>';  // . -> >
            case 0x2f: return '?';  // / -> ?
            case 0x60: return '~';  // ` -> ~
        }
    }

    if (vkey && !is_CTRL_down) {
        if ((is_CAPS_down) || (is_SHIFT_down)) {
            return toupper(VKCODE);
        }
        return tolower(VKCODE);
    }

    return '\0';
}
