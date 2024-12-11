#include "utils.h"

int lecture(FILE* fp, char* mot) {
	char inter[512];
	int j,c;
	j=0;
	do {
		c=remove_accent(fgetwc(fp));
		if (c==EOF) return 0;
		if (c=='\n' || c=='\r') break;
		if (!ispunct(c) && !isspace(c)) inter[j++]=c;
		else if (c=='\'') j=0;
		else if (c=='-' && j) inter[j++]=c;
		else if (c==' ') {
			if (j && ispunct(inter[j-1])) j--;
			else break;
		}
		else break;
	} while (1);
	if (j && inter[j-1]=='-') j--;
	inter[j]=0;
	strcpy(mot,inter);
	return 1;
}

char remove_accent(wchar_t c) {
    switch (c) {
        case L'é':
        case L'è':
        case L'ê':
        case L'ë':
        case L'É':
        case L'È':
        case L'Ê':
        case L'Ë':
            return 'e';

        case L'à':
        case L'â':
        case L'ä':
        case L'À':
        case L'Â':
        case L'Ä':
            return 'a';

        case L'î':
        case L'ï':
        case L'Î':
        case L'Ï':
            return 'i';

        case L'ô':
        case L'ö':
        case L'Ô':
        case L'Ö':
            return 'o';

        case L'ù':
        case L'û':
        case L'ü':
        case L'Ù':
        case L'Û':
        case L'Ü':
            return 'u';

        case L'ç':
        case L'Ç':
            return 'c';

        default:
            return c;
    }
}