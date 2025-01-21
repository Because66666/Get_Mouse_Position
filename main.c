#include <stdio.h>
#include <windows.h>

void ResizeConsole(int width, int height) {
    // ���ÿ���̨��Ļ��������С
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) return;

    COORD newSize = { (SHORT)width, (SHORT)height };
    if (!SetConsoleScreenBufferSize(hStdout, newSize)) return;

    // ��ȡ����̨���ھ��
    HWND hwnd = GetConsoleWindow();
    if (!hwnd) return;

    // �������ڴ�С����Ӧ�µĻ�������С
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

    // ���ô��ڴ�СΪ240x70
    ResizeConsole(270, 70);

    // ��ȡ��ǰ����̨���ھ��
    hwnd = GetConsoleWindow();

    // ���ô���Ϊ�ö�
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    while (1) {
        // ��ȡ���λ��
        if (GetCursorPos(&pt)) {
            ClearLine(); // ���֮ǰ��һ��

            // ����������
            printf("Mouse position: (%d, %d)", pt.x, pt.y);

            // ˢ�¿���̨���
            fflush(stdout);
        }

        // ��΢��Ϣһ���Ա���ռ�ù���CPU��Դ
        Sleep(100);
    }

    return 0;
}