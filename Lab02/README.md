# Fundamentals of Vectorization on AMD64

*Agustín Navarro Torres*

> The assessment consists of several questions related to the lab handout.
> Times and metrics must be obtained from runs on a DIIS machine that you
> must specify (L0.03, L0.04, L0.06, L1.02, lab000…). Be concise in your
> answers. The references used will be taken into account.

## General notes

The work may be submitted individually or in groups of at most two people.
You may work in larger groups, but each group must prepare the deliverable
independently. Send me your work in **pdf** format through the submission
link on the course website (moodle). Include your NIP in the file name
(`vector_NIP.pdf`). The document must contain the full names of the authors
in its header and must not exceed 4 pages.

**Submission deadline:** XXXX, XXhXXm.

## Part 1. Automatic vectorization

1. How many instructions are executed in the inner loop (`esc.sse`,
   `vec.sse`, `vec.avx` and `vec.avxfma`)?

   ```c
   for (unsigned int i = 1; i < LEN; i++)
       a[i] = b[i] + scalar*c[i];
   ```

   Compute the reduction in the number of instructions with respect to the
   `esc.sse` version.

   | version      | icount | reduction (%) | reduction (factor) |
   |--------------|-------:|--------------:|-------------------:|
   | `esc.sse`    |        |               |                    |
   | `vec.sse`    |        |               |                    |
   | `vec.avx`    |        |               |                    |
   | `vec.avxfma` |        |               |                    |

   Briefly state how you computed the values above.

2. Using the execution times obtained […], compute the following metrics
   for all the versions run:

   - Speedups of the vector versions over their scalar counterparts
     (`vec.sse`, `vec.avx` and `vec.avxfma` with respect to `esc.sse`).
   - Performance ($R$) in GFLOPS.
   - Theoretical peak performance ($R_{peak}$) of a single core, in GFLOPS.
     For the scalar version, assume that the functional units work in scalar
     mode. Also, take the FMA capability of the functional units into account
     only for the version compiled with FMA support.
   - Instruction execution rate ($VI$), in Ginstructions per second (GIPS).

   Briefly explain how you did the calculations.

   | version      | time (ns) | speed-up | $R$ (GFLOPS) | $R_{peak}$ (GFLOPS) | $VI$ (GIPS) |
   |--------------|----------:|---------:|-------------:|--------------------:|------------:|
   | `esc.sse`    |           | 1.0      |              |                     |             |
   | `vec.sse`    |           |          |              |                     |             |
   | `vec.avx`    |           |          |              |                     |             |
   | `vec.avxfma` |           |          |              |                     |             |

   *Note:* GFLOPS $= 10^9$ FLOPS. GIPS $= 10^9$ IPS.

   Is the instruction execution rate a good performance indicator?

3. Compare the speedup you measured for `vec.sse` and `vec.avx` with the
   ideal ones (number of lanes: 4 single-precision elements per 128-bit
   register, 8 per 256-bit register). Why are they lower? Repeat the
   measurement with an array size that fits in the L1/L2 cache and another
   that only fits in main memory, and relate the results to the memory
   bandwidth. Also state whether the compiler really emitted `xmm` and `ymm`
   registers (use `-fopt-info-vec-optimized` or `objdump -d`).

## Part 2. Manual vectorization using intrinsics

1. Write two new versions of the loop, `triad_intr_SSE()` and
   `triad_intr_AVX()`, vectorizing manually with SSE (`immintrin.h`,
   `__m128`, `_mm_*`) and AVX (`__m256`, `_mm256_*`; compile with `-mavx2`)
   intrinsics, using separate multiply and add intrinsics. List the code of
   the functions.

   Analyze the file containing the assembly of those functions and find the
   instructions corresponding to the loops in `triad_intr_SSE()` and
   `triad_intr_AVX()`.

   Are there any differences from the instructions corresponding to the loops
   in `triad()` (`vec.sse` and `vec.avx` versions)?

   Is there a noticeable difference in the performance of the `triad()`
   function and of the intrinsics versions?

2. Write a second AVX version, `triad_intr_AVX_fma()`, using
   `_mm256_fmadd_ps`. Does the compiler generate a `vfmadd` instruction?
   Compare its performance with the previous version and with `vec.avxfma`.

3. Make your AVX intrinsics version work for any `LEN`, not only multiples
   of 8. Handle the remaining `(LEN-1) % 8` elements with (a) a scalar tail
   loop and (b) a masked operation (`_mm256_maskload_ps`,
   `_mm256_maskstore_ps`; AVX masks are vectors whose lanes have the sign bit
   set when active). Check the result against the scalar version and discuss
   the cost of each approach.

## How to run the code and obtain the assembly

All the code is in [`code/main.c`](code/main.c) (complete the `TODO`
functions for Part 2). The [`Makefile`](code/Makefile) builds every version
from that single file.

### Build and run

```sh
cd code
make           # esc.sse vec.sse vec.avx vec.avxfma intr.avx + .s files
make run       # run every version and kernel
make LEN=65537 # change the array size (LEN-1 multiple of 8)
make clean
```

Each binary prints the kernel, the time per call in ns (minimum of several
trials), the GFLOPS and whether the result matches the scalar reference
(`OK`/`WRONG`). Run a single one with `./vec.avx triad`, or, for the
intrinsics, `./intr.avx <kernel> [offset_bytes] [n]` with kernel one of
`triad`, `sse`, `avx`, `avx_fma`, `tail`, `mask` or `aligned`.
`offset_bytes` shifts the arrays away from a 64-byte boundary and `n` is the
number of elements for `tail` and `mask`.

| version      | flags for `triad()`                                  |
|--------------|------------------------------------------------------|
| `esc.sse`    | `-O3 -fno-tree-vectorize -msse2`                     |
| `vec.sse`    | `-O3 -msse2`                                         |
| `vec.avx`    | `-O3 -mavx`                                          |
| `vec.avxfma` | `-O3 -mavx2 -mfma`                                   |
| `intr.avx`   | `-O3 -mavx2 -mfma -ffp-contract=off -DWITH_INTR`     |

To check the machine supports the instruction sets:

```sh
grep -o -w -E 'avx|avx2|fma' /proc/cpuinfo | sort -u
```

Run the measurements on the DIIS machine you report, with no other heavy
jobs running, and repeat them a few times.

### Assembly

`make` also writes one listing per version (`esc.sse.s`, `vec.sse.s`,
`vec.avx.s`, `vec.avxfma.s` and `intr.s`); they come from `gcc -S`. Every
kernel is marked `noinline`, so each one appears as its own function
(`triad:`, `triad_intr_AVX:`…). You can also disassemble a binary:

```sh
# listing of one function from the .s file
sed -n '/^triad:/,/\.size.*triad/p' vec.avx.s

# or from the executable
objdump -d --no-show-raw-insn vec.avx | sed -n '/<triad>:/,/ret/p'

# which compiler report says the loop was vectorized (shown by make)
gcc -O3 -mavx2 -mfma -fopt-info-vec-optimized -c main.c
```
