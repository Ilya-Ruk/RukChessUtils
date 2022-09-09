#include <stdio.h>

#define N_INPUT 768
#define N_HIDDEN 512
#define N_OUTPUT 1

int main(int argc, char* argv[])
{
	FILE* FileIn;
	FILE* FileOut;

	int Magic;
	uint64_t Hash;

	float InputWeights[N_INPUT * N_HIDDEN];
	float InputBiases[N_HIDDEN];

	float OutputWeights[N_HIDDEN * 2];
	float OutputBias;

	if (argc < 3) {
		printf("Usage: hidden_weights.exe berserk.nn hidden_weights.txt\n");

		return 0;
	}

	FileIn = fopen(argv[1], "rb");

	if (FileIn == NULL) { // File open error
		printf("File '%s' open error!\n", argv[1]);

		return 0;
	}

	FileOut = fopen(argv[2], "w");

	if (FileOut == NULL) { // File open error
		printf("File '%s' open error!\n", argv[2]);

		return 0;
	}

	fread(&Magic, 4, 1, FileIn);
	fread(&Hash, sizeof(uint64_t), 1, FileIn);

	fread(InputWeights, sizeof(float), N_INPUT * N_HIDDEN, FileIn);
	fread(InputBiases, sizeof(float), N_HIDDEN, FileIn);
	fread(OutputWeights, sizeof(float), N_HIDDEN * 2, FileIn);
	fread(&OutputBias, sizeof(float), N_OUTPUT, FileIn);

	for (int i = 0; i < N_HIDDEN * 2; ++i) {
		fprintf(FileOut, "%f\n", OutputWeights[i]);
	}

	fclose(FileOut);
	fclose(FileIn);

	return 0;
}