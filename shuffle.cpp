#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned long long U64;

typedef struct {
  char Line[512];
} PositionItem;

struct {
  int Count;

  PositionItem** Positions;
} PositionStore;

U64 RandState = 0ULL; // The state can be seeded with any value

/*
  https://prng.di.unimi.it/splitmix64.c
*/
U64 Rand64(void)
{
  U64 Result = (RandState += 0x9E3779B97F4A7C15);

  Result = (Result ^ (Result >> 30)) * 0xBF58476D1CE4E5B9;
  Result = (Result ^ (Result >> 27)) * 0x94D049BB133111EB;

  return Result ^ (Result >> 31);
}

void SetRandState(const U64 NewRandState)
{
  RandState = NewRandState;
}

void ShufflePositions(void)
{
  PositionItem** PositionPointer1;
  PositionItem** PositionPointer2;

  PositionItem* TempItemPointer;

  U64 RandomValue;

  for (int PositionNumber = 0; PositionNumber < PositionStore.Count; ++PositionNumber) {
    PositionPointer1 = &PositionStore.Positions[PositionNumber];

    RandomValue = Rand64();

    PositionPointer2 = &PositionStore.Positions[RandomValue % PositionStore.Count];

    TempItemPointer = *PositionPointer1;
    *PositionPointer1 = *PositionPointer2;
    *PositionPointer2 = TempItemPointer;
  }
}

int main(int argc, char* argv[])
{
  FILE* FileIn;
  FILE* FileOut;

  char Buf[512];

  int PositionNumber;

  PositionItem** PositionPointer;
  PositionItem* PositionItemPointer;

  if (argc < 3) {
    printf("Usage: shuffle.exe games_in.fen games_out.fen\n");

    return 0;
  }

  SetRandState(time(NULL));

  FileIn = fopen(argv[1], "r");

  if (FileIn == NULL) { // File open error
    printf("File 'games_in.fen' open error!\n");

    exit(0);
  }

  FileOut = fopen(argv[2], "w");

  if (FileOut == NULL) { // File open error
    printf("File 'games_out.fen' open error!\n");

    exit(0);
  }

  // The first cycle to get the number of positions

  printf("Read file (first cycle)...\n");

  PositionStore.Count = 0;

  while (fgets(Buf, sizeof(Buf), FileIn) != NULL) {
    ++PositionStore.Count;
  }

  printf("Read file (first cycle)...DONE\n");

  printf("Positions = %d\n", PositionStore.Count);

  // Allocate memory to store pointers to positions

  printf("Allocate memory...\n");

  PositionStore.Positions = (PositionItem**)malloc(PositionStore.Count * sizeof(PositionItem*));

  if (PositionStore.Positions == NULL) { // Allocate memory error
    printf("Allocate memory to store pointers to positions error!\n");

    exit(0);
  }

  printf("Allocate memory...DONE\n");

  // Set the pointer to the beginning of the file

  fseek(FileIn, 0, SEEK_SET);

  // The second cycle for reading positions

  printf("Read file (second cycle)...\n");

  PositionNumber = 0;

  while (fgets(Buf, sizeof(Buf), FileIn) != NULL) {
    // Allocate memory to store position

    PositionItemPointer = (PositionItem*)malloc(sizeof(PositionItem));

    if (PositionItemPointer == NULL) { // Allocates memory error
      printf("Allocate memory to store position error!\n");

      exit(0);
    }

    PositionPointer = &PositionStore.Positions[PositionNumber];

    *PositionPointer = PositionItemPointer;

    memcpy(PositionItemPointer->Line, Buf, sizeof(Buf));

    ++PositionNumber;
  }

  printf("Read file (second cycle)...DONE\n");

  printf("Shuffle...\n");

  ShufflePositions();

  printf("Shuffle...DONE\n");

  printf("Save file...\n");

  for (PositionNumber = 0; PositionNumber < PositionStore.Count; ++PositionNumber) {
    PositionItemPointer = PositionStore.Positions[PositionNumber];

    fprintf(FileOut, "%s", PositionItemPointer->Line);
  }

  printf("Save file...DONE\n");

  printf("Free memory...\n");

  for (PositionNumber = 0; PositionNumber < PositionStore.Count; ++PositionNumber) {
    PositionItemPointer = PositionStore.Positions[PositionNumber];

    free(PositionItemPointer);
  }

  free(PositionStore.Positions);

  printf("Free memory...DONE\n");

  fclose(FileIn);
  fclose(FileOut);

  return 0;
}