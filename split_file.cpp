#include <stdio.h>
#include <stdlib.h>

#define VALID_DATA (100 / 10) // 10%

typedef unsigned long long U64;

int main(int argc, char* argv[])
{
	FILE* FileIn;
	FILE* FileValid;
	FILE* FileTrain;

	char Buf[512];

	U64 PositionNumber;

	U64 ValidPositions;
  U64 TrainPositions;

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

	printf("Read file...\n");

	PositionNumber = 0;

  ValidPositions = 0;
  TrainPositions = 0;

	while (fgets(Buf, sizeof(Buf), FileIn) != NULL) {
		if ((PositionNumber % VALID_DATA) == 0) { // Valid data
			fprintf(FileValid, "%s", Buf);

      ValidPositions++;
		}
		else { // Train data
			fprintf(FileTrain, "%s", Buf);

      TrainPositions++;
		}

		PositionNumber++;
	}

	printf("Read file...DONE\n");

  printf("Valid positions: %llu\n", ValidPositions);
  printf("Train positions: %llu\n", TrainPositions);

  printf("Total positions: %llu\n", ValidPositions + TrainPositions);

	fclose(FileIn);
	fclose(FileValid);
	fclose(FileTrain);

	return 0;
}