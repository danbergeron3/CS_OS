#include <stdio.h>

int main(int argc, char* argv []){
    char* filepath = argv[1];
    
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {return -1;}
    char c;

    while (c != EOF) {
        c = (char) fgetc(fp);
        printf("%c", c);
    }
    fclose(fp);
    return 0;
}