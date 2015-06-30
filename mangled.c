#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define UPPERCASE 'C'
#define LOWERCASE 'c'

int isUpperCase(char);
int isLowerCase(char);
int compare(const void* a, const void* b);
void strToLower(char*);
char* getStringFormat(char*);
void reformatString(char*, char*);

int main(){
	/* Read from stdin line by line */
    int lineSize = 1024;
    int lineCount = 0;
    char* lines = (char*)malloc(1);
    char line[lineSize];
    while (fgets(line, lineSize, stdin) != NULL){
        if (*(line+strlen(line)-1) == '\n'){
            *(line+strlen(line)-1) = '\0';
        }
        lineCount++;
        lines = (char*)realloc(lines, lineSize*lineCount*sizeof(char));
        strcpy(lines + (lineCount-1)*lineSize, line);
    }

    /* Get the format of each string */
    int i;
    for (i = 0; i < lineCount; i++){
        printf("%s\n", lines + i*lineSize);
        char* word = strtok(lines + i*lineSize, " ");
        while (word != NULL){
            char* format = getStringFormat(word);

            strToLower(word);
            qsort(word, strlen(word), sizeof(char), compare);
            reformatString(word, format);
            printf("%s ", word);

            word = strtok(NULL, " ");
            free(format);
        }
        printf("\n");
        free(word);
    }

    free(lines);

	return 0;
}

int isUpperCase(char c){
    return c >= 'A' && c <= 'Z';
}
int isLowerCase(char c){
    return c >= 'a' && c <= 'z';
}

int compare(const void *a, const void *b){
    return *(const char *)a - *(const char *)b;
}

void strToLower(char* p){
    for ( ; *p; ++p){
        if (isalpha(*p))
            *p = tolower(*p);
    }
}

char* getStringFormat(char* line){
    char* format = (char*)malloc((strlen(line)+1)*sizeof(char));
    int i;
    for (i = 0; i < strlen(line); i++){
        char c = *(line+i);
        if (isUpperCase(c)){
            *(format+i) = UPPERCASE;
        }
        else if (isLowerCase(c)) {
            *(format+i) = LOWERCASE;
        }
        else {
            *(format+i) = c;
        }
    }
    *(format + strlen(line)) = '\0';
    return format;
}

/* Rearrange the string such that the cases and pucntiations ar ein their previos positions */
void reformatString(char* word, char* format){
    // Remove all not-letters from the string
    int len = (int)strlen(word);
    char trimmedWord[len];
    int i, j = 0;
    for (i = 0; i < len; i++){
        char c = *(word+i);
        if (isalpha(c)){
            trimmedWord[j++] = c;
        }
    }
    trimmedWord[j] = '\0';
    j = 0;

    // Reformat the word
    for (i = 0; i < len; i++){
        char c = *(format+i);
        switch (c){
            case UPPERCASE:
                *(word + i) = toupper(trimmedWord[j++]);
                break;
            case LOWERCASE:
                *(word + i) = tolower(trimmedWord[j++]);
                break;
            default:
                *(word + i) = c;
        }
    }
}