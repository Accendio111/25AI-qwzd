#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10
#define LINE_BUF 256

typedef struct {
    char name[64];
    int atk;
    int def;
    int hp;
} Student;

int max_int(int a, int b) { return a > b ? a : b; }

int main(void) {
    char id[64];
    char me[64];
    Student s[MAX_STUDENTS];

    /* 입력 (spec 요구대로 scanf 사용) */
    printf("학번을 입력하세요: ");
    if (scanf("%63s", id) != 1) return 1;
    printf("이름을 입력하세요: ");
    if (scanf("%63s", me) != 1) return 1;

    /* CSV 파일 열기 */
    FILE* fin = fopen("students.csv", "r");
    if (!fin) {
        perror("students.csv 열기 실패");
        return 1;
    }

    char line[LINE_BUF];
    int idx = 0;

    /* --- 헤더 한 줄 건너뛰기 --- */
    fgets(line, sizeof(line), fin);

    /* 데이터 읽기 */
    while (idx < MAX_STUDENTS && fgets(line, sizeof(line), fin)) {
        /* 줄 끝 개행 제거 */
        char* p = line;
        while (*p) {
            if (*p == '\r' || *p == '\n') {
                *p = '\0';
                break;
            }
            p++;
        }

        /* 토큰 분리: 이름,공격력,방어력,HP */
        char* tok = strtok(line, ",");
        if (!tok) break;
        strncpy(s[idx].name, tok, sizeof(s[idx].name) - 1);
        s[idx].name[sizeof(s[idx].name) - 1] = '\0';

        tok = strtok(NULL, ","); if (!tok) break; s[idx].atk = atoi(tok);
        tok = strtok(NULL, ","); if (!tok) break; s[idx].def = atoi(tok);
        tok = strtok(NULL, ","); if (!tok) break; s[idx].hp = atoi(tok);

        idx++;
    }
    fclose(fin);

    if (idx != MAX_STUDENTS) {
        fprintf(stderr, "students.csv에 %d명의 데이터가 있어야 합니다 (발견: %d)\n", MAX_STUDENTS, idx);
        return 1;
    }

    /* 출력 파일 열기 */
    FILE* fout = fopen("Test.txt", "w");
    if (!fout) {
        perror("Test.txt 생성 실패");
        return 1;
    }

    /* (1) 첫 번째 줄: 학번 : 이름 */
    fprintf(fout, "%s : %s\n", id, me);

    /* (2) 가장 공격력이 높은 사람 (같으면 먼저 등장한 사람) */
    int max_idx = 0;
    for (int i = 1; i < MAX_STUDENTS; i++) {
        if (s[i].atk > s[max_idx].atk)
            max_idx = i;
    }
    fprintf(fout, "가장 공격력이 높은 사람: %s (ATK=%d)\n", s[max_idx].name, s[max_idx].atk);

    /* (3) 3번째 사람 (인덱스 2) */
    fprintf(fout, "3번째 : %s HP=%d\n", s[2].name, s[2].hp);

    /* (4) 8번째 사람 (인덱스 7) */
    fprintf(fout, "8번째 : %s HP=%d\n", s[7].name, s[7].hp);

    /* (5) 3번째 vs 8번째 전투 */
    int atk3 = s[2].atk, def3 = s[2].def, hp3 = s[2].hp;
    int atk8 = s[7].atk, def8 = s[7].def, hp8 = s[7].hp;

    int dmg_to_3 = max_int(0, atk8 - def3);
    int dmg_to_8 = max_int(0, atk3 - def8);

    if (dmg_to_3 == 0 && dmg_to_8 == 0) {
        fprintf(fout, "3번째 vs 8번째 : 무승부\n");
    }
    else {
        while (hp3 > 0 && hp8 > 0) {
            hp3 -= dmg_to_3;
            hp8 -= dmg_to_8;

            if (hp3 <= 0 && hp8 <= 0) {
                fprintf(fout, "3번째 vs 8번째 : 무승부\n");
                break;
            }
            else if (hp3 <= 0) {
                fprintf(fout, "3번째 vs 8번째 승자: %s\n", s[7].name);
                break;
            }
            else if (hp8 <= 0) {
                fprintf(fout, "3번째 vs 8번째 승자: %s\n", s[2].name);
                break;
            }
        }
    }

    /* (6) 마지막 줄 */
    fprintf(fout, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요\n");

    fclose(fout);

    return 0;
}
