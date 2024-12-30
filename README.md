# Keylogger by Qwerty

This program is a **Windows-based keylogger** that captures every keystroke typed on the system by hooking into low-level keyboard events. The keylogger records the pressed keys and can save them to a log file or transmit them to a remote server. It works by utilizing Windows API functions like `SetWindowsHookEx` to intercept keyboard input events.

## Features

- Captures every keystroke typed on the system.
- Records keypresses in real-time to a log file (`Keylogger.log`).
- Logs the active window's title to associate key presses with the corresponding application.
- Supports basic text input (does **not** yet support special characters).
- Logs activity with timestamps.

## How It Works

1. **Keyboard Hooking**: 
   - The program hooks into the system's keyboard events using `SetWindowsHookEx`, which intercepts low-level keyboard events such as key presses and releases.
   
2. **Buffer Management**: 
   - Keystrokes are stored in a buffer, which is periodically written to a log file. The buffer is reset once the log is saved.

3. **Window Title Tracking**: 
   - The program logs the title of the currently active window (foreground process) when keystrokes are recorded, so you know which application was active when the keys were pressed.

4. **Logging Format**:
   - Timestamps and the foreground window's title are logged along with the keystrokes in `Keylogger.log`.

## Limitations

- Special characters (e.g., `@`, `#`, `$`, etc.) may not be captured correctly. This is an ongoing issue and will need additional handling to fix.
- The program works only on **Windows**.

## Usage

### Running the Keylogger
To run the program, compile and execute it on a Windows machine. When launched, it will:

- Start a listener thread that captures keystrokes.
- Start a writer thread that writes captured keystrokes to a log file.
- Continuously log keypresses and active window titles to `Keylogger.log`.

The program will create a log file in the same directory with the following format:

```
*************************************
Started on 12/30/2024 at 12:30:00
[ Notepad ] : Hello World!
[ Chrome ] : This is a test.
```

### Log File Location
The log file will be saved as `Keylogger.log` in the current working directory where the program is executed.

### Important Notes
- **Use Responsibly**: This program is meant for educational purposes only. Unauthorized use of keyloggers is illegal and unethical.
- **Run with Consent**: Make sure you have the consent of the user or owner of the machine on which this software is running.
- **Not for Malicious Use**: The author does **not** endorse the use of this software for malicious purposes.

## Known Issues
- **Special Character Handling**: The keylogger may fail to capture special characters correctly. This is a known limitation in the current version of the program.
  
## License

This code is for educational purposes only. Use responsibly and ensure that you have proper authorization before running this software on any system. Unauthorized use is illegal and punishable by law.

---

**Created by**: Qwerty  
**Date**: 12/30/2024
