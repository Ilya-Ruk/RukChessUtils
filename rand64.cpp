#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// https://prng.di.unimi.it/splitmix64.c

static uint64_t state; /* The state can be seeded with any value. */

uint64_t SplitMix64(void) {
  uint64_t z = (state += 0x9e3779b97f4a7c15);

  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;

  return z ^ (z >> 31);
}

// https://prng.di.unimi.it/xoshiro256plusplus.c

static uint64_t s[4];

inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

uint64_t RandomUInt64_1(void) {
  const uint64_t result = rotl(s[0] + s[3], 23) + s[0];

  const uint64_t t = s[1] << 17;

  s[2] ^= s[0];
  s[3] ^= s[1];
  s[1] ^= s[2];
  s[0] ^= s[3];

  s[2] ^= t;

  s[3] = rotl(s[3], 45);

  return result;
}

// http://www.vlasak.biz/cheng/

static uint64_t keys[2];

inline uint64_t rotate(uint64_t v, uint8_t n) {
  return (v >> n) | (v << (64 - n));
}

uint64_t RandomUInt64_2(void) {
  uint64_t tmp = keys[0];

  keys[0] += rotate(keys[1] ^ 0xc5462216u ^ ((uint64_t)0xcf14f4ebu << 32), 1);

  return keys[1] += rotate(tmp ^ 0x75ecfc58u ^ ((uint64_t)0x9576080cu << 32), 9);
}

// https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/

float RandomGaussian(float mu, float sigma) {
  float U1, U2, W, mult;

  static float X1, X2;
  static int call = 0;

  if (call == 1) {
    call = !call;

    return (mu + sigma * X2);
  }

  do {
    U1 = -1.0f + ((float)rand() / RAND_MAX) * 2.0f;
    U2 = -1.0f + ((float)rand() / RAND_MAX) * 2.0f;

    W = powf(U1, 2) + powf(U2, 2);
  } while (W == 0.0f || W >= 1.0f);

  mult = sqrtf((-2.0f * logf(W)) / W);

  X1 = U1 * mult;
  X2 = U2 * mult;

  call = !call;

  return (mu + sigma * X1);
}

void SeedRandom(void)
{
  state = time(NULL);

  s[0] = SplitMix64();
  s[1] = SplitMix64();
  s[2] = SplitMix64();
  s[3] = SplitMix64();

  keys[0] = time(NULL);
  keys[1] = time(NULL);

  for (int i = 0; i < 64; i++) {
    RandomUInt64_2();
  }

  srand(time(NULL));
}

int main(void)
{
  float min = -2.0;
  float max = 2.0;

  int intervals = 20;

  int samples = 10000;

  int max_width = 60;

  int plot[intervals + 1];
  float range[intervals + 1];

  SeedRandom();

  memset(plot, 0, sizeof(plot));

  range[0] = min;

  for (int i = 1; i <= intervals; ++i) {
    range[i] = range[0] + (max - min) / intervals * i;
  }

  int range_out = 0;

  for (int i = 0; i < samples; ++i) {
//    float value = ((float)rand() / RAND_MAX) - 0.5;
//    float value = ((float)SplitMix64() / ULONG_MAX) - 0.5;
//    float value = ((float)RandomUInt64_1() / ULONG_MAX) - 0.5;
//    float value = ((float)RandomUInt64_2() / ULONG_MAX) - 0.5;
    float value = RandomGaussian(0.0f, 0.5);

    int found = 0;

    for (int j = 0; j < intervals; ++j) {
      if (value >= range[j] && value < range[j + 1]) {
        ++plot[j];

        found = 1;

        break;
      }
    }

    if (found == 0) {
      range_out = 1;
    }
  }

  int max_plot = 0;

  for (int i = 0; i <= intervals; ++i) {
    if (plot[i] > max_plot) {
      max_plot = plot[i];
    }
  }

  float m = (float)max_plot / max_width;

  for (int i = 0; i <= intervals; ++i) {
    plot[i] = (float)plot[i] / m;
  }

  for (int i = 0; i < intervals; ++i) {
    printf("[%+.3f - %+.3f]: ", range[i], range[i + 1]);

    for (int j = 0; j < plot[i]; ++j) {
      printf("*");
    }

    printf("\n");
  }

  if (range_out == 1) {
    printf("WARNING: Plotting out of range!\n");
  }

  return 0;
}