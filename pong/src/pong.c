// [2022] <toshikov/-/-> [legal/copyright]

#include <stdio.h>

int i, j, ball, x, y, k;
int scoreA, scoreB;
int  msideA, msideB, msideA2, msideB2;
double Div;
char space, enter;
char movement;
int playerA, playerB;

void pole() {
    for (i = 1; i < 26; i++) {
        for (j = 1; j < 81; j++) {
            if (i == 1 || i == 25) {
            printf("=");
            } else {
            if (x == j && y == i) {
                printf("*");
            } else if ((j == 2 && msideA2 == i) || (j == 2 && msideA2-1 == i) || (j == 2 && msideA2+1 == i)) {
                printf("|");
            } else if (j == 79 && ((msideB2 == i) || (msideB2-1 == i) || (msideB2+1 == i))) {
                printf("|");
            } else {
            printf(" ");
            }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int rocketposition(char position) {
        if (position == 'a') {
            msideA2--;
        }
        if (position == 'z') {
            msideA2++;
        }
        if (position == 'k') {
            msideB2--;
        }
        if (position == 'm') {
            msideB2++;
        }
        return 0;
    }

void left() {
    while (x < 79) {
        scanf("%c", &movement);
        rocketposition(movement);
        pole();
        printf("Score 1: %d Score2: %d\n", playerA, playerB);
        x++;
    }
}

void right() {
    while (x > 2) {
        scanf("%c", &movement);
        rocketposition(movement);
        pole();
        printf("Score 1: %d Score2: %d\n", playerA, playerB);
        x--;
    }
}

void upleft() {
    while (x < 79 && y > 0) {
        scanf("%c", &movement);
        rocketposition(movement);
        pole();
        printf("Score 1: %d Score2: %d\n", playerA, playerB);
        x++;
        y--;
    }
    y++;
    x--;
}

void downleft() {
    while (x < 79 && y > 0 && y < 26) {
        scanf("%c", &movement);
        rocketposition(movement);
        pole();
        printf("Score 1: %d Score2: %d\n", playerA, playerB);
        x++;
        y++;
    }
    x--;
    y--;
}

void upright() {
    while (x > 2 && y > 0) {
        scanf("%c", &movement);
        rocketposition(movement);
        pole();
        printf("Score 1: %d Score2: %d\n", playerA, playerB);
        x--;
        y--;
        }
    y++;
    x++;
}

void downright() {
    while (x > 2 && y > 0 && y < 26) {
        scanf("%c", &movement);
        rocketposition(movement);
        pole();
        printf("Score 1: %d Score2: %d\n", playerA, playerB);
        x--;
        y++;
    }
    y--;
    x++;
}


int main() {
    printf("Start game\n");
    x = 79;
    y = 13;
    msideA2 = 13;
    msideB2 = 13;

    while (playerA < 21 || playerB < 21) {
        if (msideA2 == y && x == 2)
            left();
        if (msideB2 == y && x == 79)
            right();
        if (msideA2 - 1 == y && x == 2) {
            upleft();
            downleft();
            upleft();
            downleft();
            upleft();
            y--;
            x++;
        }
        if (msideA2 + 1 == y && x == 2) {
            downleft();
            upleft();
            downleft();
            upleft();
            downleft();
            x++;
            y++;
        }
        if (msideB2 - 1 == y && x == 79) {
            upright();
            downright();
            upright();
            downright();
            upright();
            y--;
            x--;
        }
        if (msideB2 + 1 == y && x == 79) {
            downright();
            upright();
            downright();
            upright();
            downright();
            y++;
            x--;
        }
        if ((msideA2 != y) && (msideA2 + 1 != y) && (msideA2 - 1 != y) && x == 2) {
            playerB++;
            x = 2;
            y = 13;
            msideA2 = 13;
            msideB2 = 13;
        }
        if ((msideB2 != y) && (msideB2 + 1 != y) && (msideB2 - 1 != y) && x == 79) {
            playerA++;
            x = 79;
            y = 13;
            msideA2 = 13;
            msideB2 = 13;
        }
    }
printf("GAME OVER!");
return 0;
}
