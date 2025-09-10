#include <stdio.h>

void drawStar(int x, int y) {
    printf("\x1B[%d;%dH", y, x);
    printf("*");
    fflush(stdout);  // 즉시 출력 반영
}

int main() {
    int width = 6;
    int height = 5;

    printf("\x1B[2J");    // 화면 지우기
    printf("\x1B[?25l");  // 커서 숨기기

    for (int row = 1; row <= height; row++) {
        for (int col = 1; col <= width; col++) {
            if (row == 1 || row == height) {
                drawStar(col, row);
            }
            else {
                if (col == 1 || col == width) {
                    drawStar(col, row);
                }
            }
        }
    }

    printf("\x1B[?25h");              // 커서 보이기
    printf("\x1B[%d;1H", height + 2); // 커서 위치 마지막 줄 아래로 이동

    printf("실행이 시작되고 종료됩니다.\n");

    return 0;
}
