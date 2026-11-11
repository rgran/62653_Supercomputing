/*
 * Lab: Fundamentals of Vecotirzation on AMD64
 *
 * @Author: Navarro-Torres, Agustín.
 *
 * Heavly inspired by the same lab from: Jesús Alastruey Benedé
 */

#include <immintrin.h> /* only used when WITH_INTR (needs -mavx2 -mfma) */
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef LEN
#define LEN 1024 /* elements per array */
#endif
#define NOINLINE                                                               \
  __attribute__((noinline, noclone)) /* keep each kernel visible in the .s */

/* ---- Part 1: scalar / auto-vectorized depending on compiler flags ---- */
NOINLINE void triad(float *a, const float *b, const float *c, float scalar) {
  for (unsigned int i = 1; i < LEN; i++)
    a[i] = b[i] + scalar * c[i];
}

#ifdef WITH_INTR
/* ---- Part 2: SSE / AVX intrinsics (TODO) ---- */

/* Q1 (a): a[i] = b[i] + scalar*c[i] with 128-bit SSE intrinsics
 * (_mm_mul_ps + _mm_add_ps). */
NOINLINE void triad_intr_SSE(float *a, const float *b, const float *c,
                             float scalar) {
  /* TODO */
}

/* Q1 (b): same with 256-bit AVX intrinsics (_mm256_mul_ps + _mm256_add_ps). */
NOINLINE void triad_intr_AVX(float *a, const float *b, const float *c,
                             float scalar) {
  /* TODO */
}

/* Q2: AVX version with _mm256_fmadd_ps. */
NOINLINE void triad_intr_AVX_fma(float *a, const float *b, const float *c,
                                 float scalar) {
  /* TODO */
}

/* Q3 (a): any n, remaining (n-1) % 8 elements with a scalar loop. */
NOINLINE void triad_intr_AVX_tail(float *a, const float *b, const float *c,
                                  float scalar, size_t n) {
  /* TODO */
}

/* Q3 (b): any n, remaining elements with _mm256_maskload_ps /
 * _mm256_maskstore_ps (vector mask: sign bit of each 32-bit lane). */
NOINLINE void triad_intr_AVX_mask(float *a, const float *b, const float *c,
                                  float scalar, size_t n) {
  /* TODO */
}

/* Q4: use _mm256_load_ps/_mm256_store_ps (32-byte aligned). Since the loop
 * starts at i = 1, peel the first iterations first. */
NOINLINE void triad_intr_AVX_aligned(float *a, const float *b, const float *c,
                                     float scalar) {
  /* TODO */
}
#endif

#ifndef REPS
#define REPS 20000
#endif
#define TRIALS 15

static double now_ns(void) {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return t.tv_sec * 1e9 + t.tv_nsec;
}

int main(int argc, char **argv) {
  const char *k = argc > 1 ? argv[1] : "triad";
  size_t off = argc > 2 ? strtoul(argv[2], 0, 0) : 0;
  size_t n = argc > 3 ? strtoul(argv[3], 0, 0) : LEN + 5;
  int use_n = !strcmp(k, "tail") || !strcmp(k, "mask");
  size_t len = use_n ? n : LEN;
  const float s = 3.0f;

  size_t bytes = ((len + 32) * sizeof(float) + 63) & ~(size_t)63;
  char *pa = aligned_alloc(64, bytes + 64), *pb = aligned_alloc(64, bytes + 64),
       *pc = aligned_alloc(64, bytes + 64);
  float *a = (float *)(pa + off), *b = (float *)(pb + off),
        *c = (float *)(pc + off);
  float *ref = malloc(len * sizeof(float));
  for (size_t i = 0; i < len; i++) {
    b[i] = 1.0f + (i % 7);
    c[i] = 0.5f * (i % 5);
    a[i] = 0.0f;
    ref[i] = b[i] + s * c[i];
  }

  double best = 1e30;
  for (int t = 0; t < TRIALS; t++) {
    double t0 = now_ns();
    for (int r = 0; r < REPS; r++) {
      if (!strcmp(k, "triad"))
        triad(a, b, c, s);
#ifdef WITH_INTR
      else if (!strcmp(k, "sse"))
        triad_intr_SSE(a, b, c, s);
      else if (!strcmp(k, "avx"))
        triad_intr_AVX(a, b, c, s);
      else if (!strcmp(k, "avx_fma"))
        triad_intr_AVX_fma(a, b, c, s);
      else if (!strcmp(k, "tail"))
        triad_intr_AVX_tail(a, b, c, s, n);
      else if (!strcmp(k, "mask"))
        triad_intr_AVX_mask(a, b, c, s, n);
      else if (!strcmp(k, "aligned"))
        triad_intr_AVX_aligned(a, b, c, s);
#endif
      else {
        fprintf(stderr, "unknown/unavailable kernel %s\n", k);
        return 1;
      }
      __asm__ volatile("" ::: "memory"); /* keep the calls */
    }
    double dt = (now_ns() - t0) / REPS;
    if (dt < best)
      best = dt;
  }

  int ok = 1;
  for (size_t i = 1; i < len; i++) /* iteration space starts at 1 */
    if (fabsf(a[i] - ref[i]) > 1e-4f) {
      ok = 0;
      break;
    }
  printf("%-10s len=%zu off=%zu  %10.1f ns  %7.2f GFLOPS  %s\n", k, len, off,
         best, 2.0 * (len - 1) / best, ok ? "OK" : "WRONG");
  return !ok;
}
