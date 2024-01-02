#include "stdio.h"
#include "string.h"
#define BREAKPOINT __asm__ __volatile__("xchg %bx, %bx")
void cover_addr(){//在本代码中其返回地址为0x7:0x01b1
    //BREAKPOINT;
    char buf[8]="12345678";
    char payload[] = {//在buf头与返回地址间，存在着ebp ebx 8个buf数据，共4*6=24位
        'T','h','i','s',' ','i','s',' ','p','a','y','l','o','a','d','.',
        ' ',' ',' ',' ',0xb1, 0x10, 0x00};
    BREAKPOINT;
    strcpy(buf,payload);
    BREAKPOINT;
    printf("%s", buf);
    return;
}
void stackoverflow(){
    BREAKPOINT;
    int num=0x12345678;
    BREAKPOINT;
    printf("overflow!\n");
    for (;;);
    exit(0);
}

int main(){
    BREAKPOINT;
    //stackoverflow();
    cover_addr();
    return 0;
}