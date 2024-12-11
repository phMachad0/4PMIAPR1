#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

int lecture(FILE* fp, char* mot);
char remove_accent(wchar_t c);