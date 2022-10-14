#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE* FileIn1;
	FILE* FileIn2;
	FILE* FileOut;

	char Buf[512];

	if (argc < 4) {
		printf("Usage: merge_files.exe file_in_1.fen file_in_2.fen file_out.fen\n");

		return 0;
	}

	FileIn1 = fopen(argv[1], "r");

	if (FileIn1 == NULL) { // File open error
		printf("File '%s' open error!\n", argv[1]);

		return 0;
	}

	FileIn2 = fopen(argv[2], "r");

	if (FileIn2 == NULL) { // File open error
		printf("File '%s' open error!\n", argv[2]);

		return 0;
	}

	FileOut = fopen(argv[3], "w");

	if (FileOut == NULL) { // File open error
		printf("File '%s' open error!\n", argv[3]);

		return 0;
	}

	printf("Read file 1...\n");

	while (fgets(Buf, sizeof(Buf), FileIn1) != NULL) {
		fprintf(FileOut, "%s", Buf);
	}

	printf("Read file 1...DONE\n");

	printf("Read file 2...\n");

	while (fgets(Buf, sizeof(Buf), FileIn2) != NULL) {
		fprintf(FileOut, "%s", Buf);
	}

	printf("Read file 2...DONE\n");

	fclose(FileIn1);
	fclose(FileIn2);
	fclose(FileOut);

	return 0;
}