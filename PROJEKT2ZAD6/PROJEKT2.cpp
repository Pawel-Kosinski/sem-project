#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_chars 30

void sterowanie(char* tekst, char instrukcja)
{
	int maxdlugosc = max_chars;
	int txtdlugosc = (int)strlen(tekst);
	int spacje = maxdlugosc - txtdlugosc;
		if (instrukcja == 'P') printf("%*s%s\n", spacje, "", tekst);
		else if (instrukcja == 'L') printf("%s%*s\n", tekst, spacje, "");
		else if (instrukcja == 'S')
		{
			int lewospacje = spacje / 2;
			int prawospacje = spacje - lewospacje;
			printf("%*s%s%*s\n", lewospacje, "", tekst, prawospacje, "");
		}
		else
			printf("Zla instrukcja linii\n");
}

void longtxt(char* tekst1, char instrukcja)
{
	int n = (int)strlen(tekst1) / max_chars;
	for (int i = 0; i < n; i++)
	{
		for (int j = i * max_chars; j < (i + 1) * max_chars; j++) printf("%c", tekst1[j]);
		printf("\n");
	}
	size_t dlugosctxt = strlen(tekst1)-1 - n * max_chars;
	char tekst2[max_chars];
	strncpy_s(tekst2, sizeof(tekst2), tekst1 + max_chars * n, dlugosctxt);
	sterowanie(tekst2, instrukcja);
}

int main()
{
	FILE* plik;
	if (fopen_s(&plik, "tekst.txt", "r") != 0)
	{
		printf("Blad odczytu pliku. \n");
		return 1;
	}
	char line[1024];
	while (fgets(line, sizeof(line), plik))
	{
		char instrukcja = line[0];
		if (strlen(line) > max_chars)
		{
			size_t copyLength1 = strlen(line) - 1;
			int rozmiar = (int)strlen(line);
			char *tekst1;
			tekst1 = (char*)malloc(rozmiar * sizeof(char));
			if (tekst1 == NULL) {
				printf("B³¹d alokacji pamiêci.\n");
				return 1;
			}
			strncpy_s(tekst1, rozmiar, line + 1, copyLength1);
			char* enter = strchr(tekst1, '\n');
			if (enter != NULL) *enter = '\0';
			longtxt(tekst1, instrukcja);
			free(tekst1);
		}
		else
		{
			char tekst[max_chars];
			size_t copyLength = strlen(line) - 1;
			strncpy_s(tekst, sizeof(tekst), line + 1, copyLength);
			char* enter = strchr(tekst, '\n');
			if (enter != NULL) *enter = '\0';
			sterowanie(tekst, instrukcja);
		}
	}
	fclose(plik);
	return 0;
}
