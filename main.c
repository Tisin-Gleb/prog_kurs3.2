#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef struct {
    unsigned char current_state;
	signed char read_char; 
	unsigned char next_state;
} State;

int FileLength(FILE *input)
{
    fseek(input, 0, SEEK_END);
    int file_length = ftell(input);
    fseek(input, 0, SEEK_SET);
    return file_length;
}

char* FileTextInArray(FILE *input, char *file_text)
{
    int file_length = FileLength(input);
    file_text = malloc(file_length);
    if (file_text == NULL) exit(1);

    int i = 0;
    char ch;
    while ( (ch = fgetc(input) ) != EOF){
        file_text[i] = ch;
        ++i;
    }

    return file_text;
}

void FileFree(char *file_text)
{
    free(file_text);
}

int main()
{
    FILE *input;
    if ( (input = fopen("input.le", "r")) == NULL) return 0;
    printf("Введите строку для поиска: ");

    char *file_text = NULL;
    int file_length = FileLength(input);
    file_text = FileTextInArray(input, file_text);
    for (int i = 0; i < file_length; i++)
    {
        printf("%c", file_text[i]);
    }
    
    FileFree(file_text);
    fclose(input);
    puts("Okay");
}