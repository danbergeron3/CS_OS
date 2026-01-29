#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"



// Given characters
// Returns 1 true if key value 
// Returns 0 false if not a key value
int check_key_value(char value);

// Takes a char buffer and buffer size
// and fills it with null terminators
// returns void
void flush_buffer(char buffer[], int buffer_size);

// converts a character buffer to an interger value
// Returns int value
void process_buffer(char buffer[]);

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        int SIZE_OF_BUFFER = 100;
        char number_buffer[SIZE_OF_BUFFER];
        int index = 0;
        for(int j = 0; j < SIZE_OF_BUFFER; j++) {
            number_buffer[j] = '\0';
        }

        int fd = open(argv[1], O_RDONLY);

        char buf[1];
        while (read(fd, buf, 1)!=0) {
            if (buf[0] <= '9' && buf[0] >= '0') {
                number_buffer[index] = *buf;
                index++;
                // check if buffer is full
                if (index > SIZE_OF_BUFFER) { // error
                    flush_buffer(number_buffer, SIZE_OF_BUFFER);
                    index = 0;
                    printf("Error buffer is overflowing.\n");
                }
                // printf("Buffer: %s\n", number_buffer);
            } else {
                if (check_key_value(buf[0])) {
                    process_buffer(number_buffer);
                    flush_buffer(number_buffer, SIZE_OF_BUFFER);
                    index = 0;
                } else {
                    flush_buffer(number_buffer, SIZE_OF_BUFFER);
                    index = 0;
                    // printf("Flushing\n");
                }
                
            }
        }
        process_buffer(number_buffer);
        exit(0);
    }
}

int check_key_value(char value) {
    int KEY_BUFFER_SIZE = 7;
    char char_key[] = {'-','\r','\t','\n','.','/',','};
    
    for (int i = 0; i < KEY_BUFFER_SIZE; i++){
        // printf("CHECKKEYVALUE: VALUE=%c, KEY= %c\n", value, char_key[i]);
        if (value == char_key[i]) {
            return 1; // key value
        }
    }
    return 0; // not a key value
    
}

void flush_buffer(char buffer[], int buffer_size){
    // printf("Flushing\n");
    for (int i = 0; i < buffer_size; i++){
        buffer[i] = '\0';
    }
    return;
}

void process_buffer(char buffer[]) {
    int value = 0;
    value = atoi(buffer);
    if (value % 5 == 0 || value % 6 == 0) {
        printf("%d\n", value);
    }
    return;
}