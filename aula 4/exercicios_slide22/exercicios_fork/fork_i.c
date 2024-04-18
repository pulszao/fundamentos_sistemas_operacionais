#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

/*

          s1
       /  |  \
     s2   s3  s4
      \  /     |
       s5      |
        \     /
          \  / 
           s6
*/

void S1() {printf("S1\n");}
void S2() {printf("S2\n");}
void S3() {printf("S3\n");}
void S4() {printf("S4\n");}
void S5() {printf("S5\n");}
void S6() {printf("S6\n");}

void main() {
    pid_t pid1, pid2;

    S1();
    pid1 = fork();

    if (pid1 > 0) {
        pid2 = fork();
        if (pid2 > 0) {
            S2();
            wait(NULL);
            wait(NULL);
            S5();
            S6();
        } else {
            S3();
        }
    } else {
        S4();
    }
}