#include <stdio.h>
#include <time.h>   // �����̿� (sleep ���)

void drawStar(int x, int y) {
    printf("\x1B[%d;%dH", y, x);
    printf("*");
    fflush(stdout);
}

void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

int main() {
    int width = 6;
    int height = 5;

    printf("\x1B[2J");    // ȭ�� Ŭ����
    printf("\x1B[?25l");  // Ŀ�� �����

    int row = 1;
    int col = 1;

    while (row <= height) {
        if (row == 1 || row == height) {
            // ù ��, ������ ��: ��� ĭ�� ��
            drawStar(col, row);
            delay(200);  // 0.2�� ������
            col++;
            if (col > width) {
                col = 1;
                row++;
            }
        }
        else {
            // �߰� ��: �糡�� ��
            if (col == 1 || col == width) {
                drawStar(col, row);
                delay(200);
            }
            col++;
            if (col > width) {
                col = 1;
                row++;
            }
        }
    }

    printf("\x1B[?25h");              // Ŀ�� ���̱�
    printf("\x1B[%d;1H", height + 2); // Ŀ�� ��ġ ������ �� �Ʒ��� �̵�

    printf("������ ���۵ǰ� ����˴ϴ�.\n");

    return 0;
}
