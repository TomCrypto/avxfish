BITS 64

global avxfish

section .text

%ifidn __OUTPUT_FORMAT__, win64
  %define ARG0 rcx
  %define ARG1 rdx
  %define ARG2 r8
%elifidn __OUTPUT_FORMAT__, elf64
  %define ARG0 rdi
  %define ARG1 rsi
  %define ARG2 rdx
%else
  %error Unsupported output format
%endif

%define next 1
%define load 2
%define last 3

%macro MIX 2
  %if %2 == load
  vmovdqa64 zmm1 %+ %1, [vrotate %+ %1]
  %endif
  vpaddq    zmm0, zmm0, zmm1
  vprolvq   zmm1, zmm1, zmm1 %+ %1
  vpxorq    zmm1, zmm1, zmm0
%endmacro

%macro PERMUTE 1
  %if %1 == load
  vmovdqa64 zmm30, [permutea]
  vmovdqa64 zmm31, [permuteb]
  %endif
  vpermq    zmm0, zmm30, zmm0
  vpermq    zmm1, zmm31, zmm1
%endmacro

%macro ADDKEY 1
  vpaddq    zmm0, zmm0, [ARG1 + (%1) * 0x80 + 0x00]
  vpaddq    zmm1, zmm1, [ARG1 + (%1) * 0x80 + 0x40]
%endmacro

%macro ENC 2
  ADDKEY 2 * %1 + 0
  MIX 0, %2
  PERMUTE %2
  MIX 1, %2
  PERMUTE next
  MIX 2, %2
  PERMUTE next
  MIX 3, %2
  PERMUTE next
  ADDKEY 2 * %1 + 1
  MIX 4, %2
  PERMUTE next
  MIX 5, %2
  PERMUTE next
  MIX 6, %2
  PERMUTE next
  MIX 7, %2
  %if %2 != last
    PERMUTE next
  %endif
%endmacro

%macro VECTORIZE 0
  vmovdqa64 zmm0, [permveca]
  vmovdqa64 zmm1, [permvecb]
  vpermi2q  zmm0, zmm2, zmm3
  vpermi2q  zmm1, zmm2, zmm3
%endmacro

%macro DEVECTORIZE 0
  vmovdqa64 zmm2, [perminva]
  vmovdqa64 zmm3, [perminvb]
  vpermi2q zmm2, zmm0, zmm1
  vpermi2q zmm3, zmm0, zmm1
%endmacro

%macro ADDLASTKEY 0
  vpaddq zmm0, zmm2, [ARG1 + 0xA00]
  vpaddq zmm1, zmm3, [ARG1 + 0xA40]
%endmacro

avxfish:
  vmovdqa64 zmm2, [ARG0 + 0x00]
  vmovdqa64 zmm3, [ARG0 + 0x40]

  VECTORIZE
  ENC 0, load
  ENC 1, next
  ENC 2, next
  ENC 3, next
  ENC 4, next
  ENC 5, next
  ENC 6, next
  ENC 7, next
  ENC 8, next
  ENC 9, last
  DEVECTORIZE
  ADDLASTKEY

  vmovdqa64 [ARG0 + 0x00], zmm0
  vmovdqa64 [ARG0 + 0x40], zmm1
  ret

  align 64

  ; the vectorization permutation (interleave evens & odds)
  permveca dq 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E
  permvecb dq 0x01, 0x03, 0x05, 0x07, 0x09, 0x0B, 0x0D, 0x0F

  ; the Threefish permutation, accounting for vectorization
  permutea dq 0x00, 0x01, 0x03, 0x02, 0x05, 0x06, 0x07, 0x04
  permuteb dq 0x04, 0x06, 0x05, 0x07, 0x03, 0x01, 0x02, 0x00

  ; the opposite of the Threefish permutation+vectorization
  perminva dq 0x00, 0x0C, 0x01, 0x0E, 0x03, 0x0D, 0x02, 0x0F
  perminvb dq 0x05, 0x0B, 0x06, 0x09, 0x07, 0x0A, 0x04, 0x08

  ; the rotation constants from the Skein whitepaper (v1.3)
  vrotate0 dq 0x18, 0x0D, 0x08, 0x2F, 0x08, 0x11, 0x16, 0x25
  vrotate1 dq 0x26, 0x13, 0x0A, 0x37, 0x31, 0x12, 0x17, 0x34
  vrotate2 dq 0x21, 0x04, 0x33, 0x0D, 0x22, 0x29, 0x3B, 0x11
  vrotate3 dq 0x05, 0x14, 0x30, 0x29, 0x2F, 0x1C, 0x10, 0x19
  vrotate4 dq 0x29, 0x09, 0x25, 0x1F, 0x0C, 0x2F, 0x2C, 0x1E
  vrotate5 dq 0x10, 0x22, 0x38, 0x33, 0x04, 0x35, 0x2A, 0x29
  vrotate6 dq 0x1F, 0x2C, 0x2F, 0x2E, 0x13, 0x2A, 0x2C, 0x19
  vrotate7 dq 0x09, 0x30, 0x23, 0x34, 0x17, 0x1F, 0x25, 0x14
