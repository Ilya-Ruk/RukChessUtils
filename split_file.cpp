#include <stdio.h>
#include <stdlib.h>

#define VALID_DATA 10 // %

typedef unsigned long long U64;

int main(int argc, char* argv[])
{
	FILE* FileIn;
	FILE* FileValid;
	FILE* FileTrain;

	char Buf[512];

	U64 TotalPositions;

	U64 PositionNumber;

	if (argc < 4) {
		printf("Usage: split_file.exe file_in.fen file_valid.fen file_train.fen\n");

		return 0;
	}

	FileIn = fopen(argv[1], "r");

	if (FileIn == NULL) { // File open error
		printf("File '%s' open error!\n", argv[1]);

		return 0;
	}

	FileValid = fopen(argv[2], "w");

	if (FileValid == NULL) { // File open error
		printf("File '%s' open error!\n", argv[2]);

		return 0;
	}

	FileTrain = fopen(argv[3], "w");

	if (FileTrain == NULL) { // File open error
		printf("File '%s' open error!\n", argv[3]);

		return 0;
	}

	// The first cycle to get the number of positions

	printf("Read file (first cycle)...\n");

	TotalPositions = 0;

	while (fgets(Buf, sizeof(Buf), FileIn) != NULL) {
		++TotalPositions;
	}

	printf("Read file (first cycle)...DONE\n");

	printf("Total positions = %llu\n", TotalPositions);

	// Set the pointer to the beginning of the file

	fseek(FileIn, 0, SEEK_SET);

	// The second cycle for reading positions

	printf("Read file (second cycle)...\n");

	PositionNumber = 0;

	while (fgets(Buf, sizeof(Buf), FileIn) != NULL) {
		if ((PositionNumber % VALID_DATA) == 0) { // Valid data
			fprintf(FileValid, "%s", Buf);
		}
		else { // Train data
			fprintf(FileTrain, "%s", Buf);
		}

		++PositionNumber;
	}

	printf("Read file (second cycle)...DONE\n");

	fclose(FileIn);
	fclose(FileValid);
	fclose(FileTrain);

	return 0;
}