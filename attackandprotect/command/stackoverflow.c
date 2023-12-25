#include "stdio.h"
#include "string.h"
#define BREAKPOINT __asm__ __volatile__("xchg %bx, %bx")
void cover_addr(){
    BREAKPOINT;
    char buf[8]="12345678";
    char payload[] = {
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
        0x41, 0x41, 0x41, 0x41, 0xb5, 0x10, 0x00};
    BREAKPOINT;
    strcpy(buf,payload);
    BREAKPOINT;
    printf("%s", buf);
    return;
}
void stackoverflow(){
    BREAKPOINT;
    printf("overflow!\n");
    int i = 10000;
    while (i--)
        ;
    exit(0);
}
int main(){
    BREAKPOINT;
    cover_addr();
    return 0;
}