#include <stdio.h>

#define N_INPUT 768
#define N_HIDDEN 512
#define N_OUTPUT 1

#define INPUT_WEIGHTS_FILE_NAME "input_weights.txt"
#define INPUT_BIASES_FILE_NAME "input_biases.txt"

#define OUTPUT_WEIGHTS_FILE_NAME "output_weights.txt"
#define OUTPUT_BIASES_FILE_NAME "output_biases.txt"

int main(int argc, char* argv[])
{
  FILE* FileIn;

  FILE* FileInputWeights;
  FILE* FileInputBiases;

  FILE* FileOutputWeights;
  FILE* FileOutputBiases;

  int Magic;
  uint64_t Hash;

  float InputWeights[N_INPUT * N_HIDDEN];
  float InputBiases[N_HIDDEN];

  float OutputWeights[N_HIDDEN * 2];
  float OutputBias;

  if (argc < 2) {
    printf("Usage: hidden_weights.exe rukchess.nnue\n");

    return 0;
  }

  FileIn = fopen(argv[1], "rb");

  if (FileIn == NULL) { // File open error
    printf("File '%s' open error!\n", argv[1]);

    return 0;
  }

  FileInputWeights = fopen(INPUT_WEIGHTS_FILE_NAME, "w");

  if (FileInputWeights == NULL) { // File open error
    printf("File '%s' open error!\n", INPUT_WEIGHTS_FILE_NAME);

    return 0;
  }

  FileInputBiases = fopen(INPUT_BIASES_FILE_NAME, "w");

  if (FileInputBiases == NULL) { // File open error
    printf("File '%s' open error!\n", INPUT_BIASES_FILE_NAME);

    return 0;
  }

  FileOutputWeights = fopen(OUTPUT_WEIGHTS_FILE_NAME, "w");

  if (FileOutputWeights == NULL) { // File open error
    printf("File '%s' open error!\n", OUTPUT_WEIGHTS_FILE_NAME);

    return 0;
  }

  FileOutputBiases = fopen(OUTPUT_BIASES_FILE_NAME, "w");

  if (FileOutputBiases == NULL) { // File open error
    printf("File '%s' open error!\n", OUTPUT_BIASES_FILE_NAME);

    return 0;
  }

  fread(&Magic, 4, 1, FileIn);
  fread(&Hash, sizeof(uint64_t), 1, FileIn);

  fread(InputWeights, sizeof(float), N_INPUT * N_HIDDEN, FileIn);
  fread(InputBiases, sizeof(float), N_HIDDEN, FileIn);
  fread(OutputWeights, sizeof(float), N_HIDDEN * 2, FileIn);
  fread(&OutputBias, sizeof(float), N_OUTPUT, FileIn);

  for (int i = 0; i < N_INPUT * N_HIDDEN; ++i) {
    fprintf(FileInputWeights, "%f\n", InputWeights[i]);
  }

  for (int i = 0; i < N_HIDDEN; ++i) {
    fprintf(FileInputBiases, "%f\n", InputBiases[i]);
  }

  for (int i = 0; i < N_HIDDEN * 2; ++i) {
    fprintf(FileOutputWeights, "%f\n", OutputWeights[i]);
  }

  fprintf(FileOutputBiases, "%f\n", OutputBias);

  fclose(FileOutputBiases);
  fclose(FileOutputWeights);

  fclose(FileInputBiases);
  fclose(FileInputWeights);

  fclose(FileIn);

  return 0;
}