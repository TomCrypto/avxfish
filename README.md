avxfish
=======

This repository contains an assembly AVX-512 implementation of the Threefish-1024 block cipher (forward direction only). Threefish-1024 is the widest variant of the Threefish family of block ciphers. It is not intended to be used directly, but instead used as a reference to integrate into other libraries as needed, or from which to implement more Threefish variants.

# Performance

This implementation is optimized for the AVX-512 instruction set, and requires the AVX-512F and AVX-512VL instructions. On an Intel(R) Xeon(R) Platinum 8124M (vCPU) processor, it is capable of processing 853 mebibytes of data from main memory per second per core at 3.0GHz, representing a performance of 3.35 cycles per byte which is very respectable for a software implementation. This speed was measured using a load-process-store loop through a 1GB memory buffer, averaged over several runs each with a random key and tweak and a randomized input buffer. In certain conditions, such as CTR mode encryption, it is not necessary to round-trip through memory as the counter block can be kept in ZMM registers and XORed with the plaintext/ciphertext stream. This can result in slightly improved performance if the implementation is suitably modified for this purpose, in the event that theoretical peak throughput needs to be attained.

# Usage Notes

The implementation in `src/avxfish.asm` is written in NASM and exposes a single function `avxfish` which takes two arguments, a pointer to the 1024-bit block to process, and a (const) pointer to 21 1024-bit subkeys obtained through the key schedule algorithm. Both pointers must be 64-byte aligned, although this restriction can be relaxed by changing the appropriate `vmovdqa64` instructions to `vmovdqu64` with a minimal performance penalty. The assembly implementation makes heavy use of macros for readability.

The key schedule algorithm is implemented in `src/avxfish.h` in plain C. It does not lend itself well to an SIMD implementation, unfortunately, as the key schedule involves rotating 17 key words and 3 tweak words cyclically to form 21 subkeys. It might still be possible to get some speedup out of AVX-512 but I suspect the compiler would be able to do a better job here. The subkeys are generated as per the Skein 1.3 specification, with one difference: all subkeys except the last one have their words permuted (to be able to be used by the vectorized AVX-512 implementation) with the following permutation:

    (0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5, 7, 9, 11, 13, 15)

There are two accompanying programs, a benchmark tool and a test program, accessible through `make bench` and `make test`. If the programs crash with an illegal instruction signal, your system does not support AVX-512. Check with `/proc/cpuinfo` or similar. If you do not have a compatible processor, Amazon Web Services provide access to some AVX-512 capable processors through their C5 or M5 instances, they are pretty cheap if you only need them for an hour or two.

For the test vectors, I used the few that I could find in the Skein 1.3 NIST SHA3 submission package (most of them are for Skein rather than Threefish) and used the reference implementation in the package to generate some more test vectors, by running the reference implementation against a set of random (plaintext, key, tweak) tuples.

# Implementation

The basic idea behind this implementation is to observe that with appropriate swizzling of the input, the MIX operations and subkey additions can be expressed as a vector operation on two 512-bit registers. The correct approach is to interleave even and odd elements in the input array so that every other item is in the first 512 bits and the rest are in the last 512 bits. Four Threefish-1024 rounds originally look like this:

<p align="center">
<img src="https://github.com/TomCrypto/avxfish/blob/master/media/diagram-standard.png?raw=true" alt="Standard Threefish-1024 round structure"/>
</p>

After doing some input swizzling and working through the permutations, the rounds can now be viewed like this:

<p align="center">
<img src="https://github.com/TomCrypto/avxfish/blob/master/media/diagram-vectorized.png?raw=true" alt="Vectorized Threefish-1024 round structure"/>
</p>

This is easily seen to be trivially vectorizable by treating each half of the input as an 8-word vector. Furthermore, as shown in the diagram above, the resulting round permutation actually turns out to be equal to

    (0, 1, 3, 2, 5, 6, 7, 4, 12, 14, 13, 15, 11, 9, 10, 8)

which happens to be separable into two permutations of the two 512-bit halves, allowing for the use of the efficient `vpermq` instruction instead of the rather slow `vpermi2q`. It is unclear whether this was intended by the Skein team; I did not find hard evidence one way or the other but I suspect the permutation was designed specifically to have this property. The end result is a fully vectorized Threefish implementation, with some bookkeeping at the beginning and end to account for the necessary data shuffling.

One limitation of this implementation is that it requires each subkey to be calculated ahead of time. While it is quite common in non-vectorized implementations to just compute the subkeys on-demand - as it is essentially free to do so in their case - it is unfortunately not possible for the vectorized implementation to compute the subkeys on the fly, as the Threefish key schedule is relatively SIMD-unfriendly, as explained earlier. In addition, all precomputed subkeys except the last one should be shuffled in the same way as the input block to avoid having to unnecessarily unvectorize and revectorize the input just to add the subkeys.

# License

This implementation is licensed under the MIT license. See the LICENSE file for details.
