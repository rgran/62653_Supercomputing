CC      ?= gcc
CFLAGS  := -std=gnu11 -Wall
LEN     ?= 1024
SRC     ?= main.c
OPT     := -DLEN=$(LEN)
ifdef REPS
OPT     += -DREPS=$(REPS)   # calls per trial (default in main.c)
endif

VERS := esc.sse vec.sse vec.avx vec.avxfma
INTR := intr.avx

# Per-version flags for the triad() kernel
F_esc.sse    := -O3 -fno-tree-vectorize -msse2
F_vec.sse    := -O3 -msse2 -fopt-info-vec-optimized
F_vec.avx    := -O3 -mavx -fopt-info-vec-optimized
F_vec.avxfma := -O3 -mavx2 -mfma -fopt-info-vec-optimized

# Flags for the intrinsics binary. -ffp-contract=off stops GCC from fusing a
# mul+add written with separate intrinsics into an FMA: only an explicit
# _mm256_fmadd_ps produces vfmadd.
F_INTR := -O3 -mavx2 -mfma -ffp-contract=off -DWITH_INTR

all: $(VERS) $(INTR) asm

# Single source: $(SRC) holds the kernels and the driver
$(VERS): %: $(SRC)
	$(CC) $(CFLAGS) $(OPT) $(F_$@) $(SRC) -lm -o $@

# Intrinsics (SSE + AVX) in one binary
intr.avx: $(SRC)
	$(CC) $(CFLAGS) $(OPT) $(F_INTR) $(SRC) -lm -o $@

# Assembly listings for the instruction-count / loop analysis
asm: $(addsuffix .s,$(VERS)) intr.s
$(addsuffix .s,$(VERS)): %.s: $(SRC)
	$(CC) $(CFLAGS) $(OPT) $(F_$*) -S -fno-asynchronous-unwind-tables $(SRC) -o $@
intr.s: $(SRC)
	$(CC) $(CFLAGS) $(OPT) $(F_INTR) -S -fno-asynchronous-unwind-tables $(SRC) -o $@

run: all
	@for v in $(VERS); do ./$$v triad | sed "s/^triad/$$v/"; done
	@for k in triad sse avx avx_fma aligned; do ./intr.avx $$k; done
	@./intr.avx tail; ./intr.avx mask
	@echo "-- misaligned (offset 4 B), loadu kernels:"; ./intr.avx avx 4
	@echo "-- aligned load on misaligned data (expected crash):"; ./intr.avx aligned 4 || true

clean:
	rm -f $(VERS) $(INTR) *.o *.s
.PHONY: all asm run clean
