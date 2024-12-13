# Keylogger - C Program (Using `GetAsyncKeyState`)

## Description

This is a simple **keylogger** written in C that uses the `GetAsyncKeyState` Windows API function to monitor and log keystrokes typed on the system. It captures key events by continuously checking the state of keys using `GetAsyncKeyState`. The program stores the captured keystrokes in a buffer and outputs them to a file.

> **Important**: This program is **malicious in nature** and should **only be used with full consent** from all parties involved. Unauthorized use of this software is **illegal** and could result in severe legal consequences.

This program is intended purely for educational purposes. I plan to release a more advanced version using the `SetWindowsHookEx` API for a more efficient and comprehensive keylogging solution.

## Features
- **Keylogging**: Captures every keystroke on the system.
- **Log to File**: Logs the captured keystrokes into a text file (`Keylogger.log`).
- **Real-time Keystroke Capture**: Displays typed keys on the console as they are pressed.
- **Forground Window Capture**: Displays the current tab user is in
  
## Disclaimer 

By downloading and running this program, you acknowledge and accept the following:
- **Only use this software with explicit consent** from the user whose keyboard activity you are monitoring.
- **This program should only be used in controlled, ethical environments** such as personal testing on your own system or educational purposes.
- **Unauthorized use or deployment of this keylogger is illegal**, and you are fully responsible for any consequences arising from its misuse.
- The author of this program does not encourage or condone any illegal activities involving this software.

## How It Works

### Overview:
This keylogger uses `GetAsyncKeyState` to continuously check the state of each key on the keyboard. If a key is pressed (detected by `GetAsyncKeyState`), the key's virtual key code is converted into a character and stored. The program writes these keystrokes to a file named `Keylogger.log`.

### Keylogging Process:
1. The program starts and continuously checks the state of every key on the system using `GetAsyncKeyState`.
2. When a key is pressed, it is logged in real time and printed to the console.
3. The keystrokes are also written into a buffer.
4. Once a key is released, the program resets the state for that key.
5. The program writes the captured keys to the log file every 10 keystrokes or when the buffer is full.

### Keystroke Logging:
- The program checks the state of common keys (letters, numbers, and special characters) using their virtual key codes.
- It handles backspaces and will remove the last logged character if the Backspace key is pressed.
- The keystrokes are saved in a log file called `Keylogger.log`.

## Usage

### 1. **Compilation**:
To compile the program, use a C compiler that supports the Windows API, such as **MinGW** or **Microsoft Visual Studio**.

Example using GCC (MinGW):
```bash
gcc keylogger.c -o keylogger.exe
```

### 2. **Running the Program**:
Run the program using the command prompt. The keylogger will start capturing keystrokes and saving them in the `Keylogger.log` file.

```bash
keylogger.exe
```

### 3. **Log File**:
After the program has been running for a while, you can open the `Keylogger.log` file to view the captured keystrokes.

> **Important**: The file will store sensitive information (such as typed passwords), so handle the log file with care.

## Future Version with `SetWindowsHookEx`

In the next version of this keylogger, I plan to switch from using `GetAsyncKeyState` to `SetWindowsHookEx`. 

The reasons for this transition are:
- **Global Keylogging**: `SetWindowsHookEx` provides a more efficient and reliable way to capture keystrokes across all applications, even when the program isn't the foreground application.
- **Event-based Capturing**: `SetWindowsHookEx` works by hooking into system events, making it more resource-efficient than continuously polling the state of all keys.
- **Better Performance**: With `SetWindowsHookEx`, we will be able to handle keystrokes as events, reducing CPU load and improving performance.

The new version will be more advanced and allow for more robust keylogging, but will also continue to prioritize the **ethical use of the software**.

## Code License and Acknowledgements

- This keylogger was written by Qwerty for educational purposes only.
- If you intend to use this program in any other way, you must first obtain explicit permission from the user whose system you are logging.

---

### Final Reminder

Please **use this program responsibly**. Always ensure that you have the necessary permissions and are abiding by all applicable laws and ethical guidelines.
