#include <stdio.h>
#include <windows.h>

void ResizeConsole(int width, int height) {
    // 设置控制台屏幕缓冲区大小
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) return;

    COORD newSize = { (SHORT)width, (SHORT)height };
    if (!SetConsoleScreenBufferSize(hStdout, newSize)) return;

    // 获取控制台窗口句柄
    HWND hwnd = GetConsoleWindow();
    if (!hwnd) return;

    // 调整窗口大小以适应新的缓冲区大小
    MoveWindow(hwnd, 0, 0, width, height, TRUE); 
}

void ClearLine() {
    COORD cursorPosition = { 0, 0 };
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', csbi.dwSize.X, cursorPosition, &written);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

int main() {
    POINT pt;
    HWND hwnd;

    // 设置窗口大小为240x70
    ResizeConsole(270, 70);

    // 获取当前控制台窗口句柄
    hwnd = GetConsoleWindow();

    // 设置窗口为置顶
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    while (1) {
        // 获取鼠标位置
        if (GetCursorPos(&pt)) {
            ClearLine(); // 清除之前的一行

            // 输出鼠标坐标
            printf("Mouse position: (%d, %d)", pt.x, pt.y);

            // 刷新控制台输出
            fflush(stdout);
        }

        // 稍微休息一下以避免占用过多CPU资源
        Sleep(100);
    }

    return 0;
}