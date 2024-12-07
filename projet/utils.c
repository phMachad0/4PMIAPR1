#include "utils.h"

int lecture(FILE* fp, char* mot) {
	char inter[512];
	int j,c;
	j=0;
	do {
		c=fgetc(fp);
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