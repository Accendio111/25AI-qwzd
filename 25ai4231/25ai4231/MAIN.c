#include <stdio.h>

void drawStar(int x, int y) {
    printf("\x1B[%d;%dH", y, x);
    printf("*");
    fflush(stdout);  // ��� ��� �ݿ�
}

int main() {
    int width = 6;
    int height = 5;

    printf("\x1B[2J");    // ȭ�� �����
    printf("\x1B[?25l");  // Ŀ�� �����

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

    printf("\x1B[?25h");              // Ŀ�� ���̱�
    printf("\x1B[%d;1H", height + 2); // Ŀ�� ��ġ ������ �� �Ʒ��� �̵�

    printf("������ ���۵ǰ� ����˴ϴ�.\n");

    return 0;
}
