/* NIP memory aligned macros */
#ifndef _NIP_ALIGNED_H_
#define _NIP_ALIGNED_H_

#define I386	0
#define PPC	1
#define BFIN	2
#define MIPS	3
#define ARM	4

#ifndef ARCH
#error no ARCH defined!
#endif

#if ARCH == BFIN
#define aligned_4  __attribute__((aligned(4)))
#define aligned_2  __attribute__((aligned(2)))
#define aligned_packed __attribute__((packed))

#elif ARCH == PPC
#define aligned_4
#define aligned_2
#define aligned_packed	__attribute__((packed))

#elif ARCH == MIPS
#define aligned_4
#define aligned_4
#define aligned_packed	__attribute__((packed))

#elif ARCH == ARM
#define aligned_4
#define aligned_4
#define aligned_packed	__attribute__((packed))

#elif ARCH == I386
#define aligned_4
#define aligned_4
#define aligned_packed	__attribute__((packed))

#else
#error ARCH defined error!
#endif

/* default align to 4 */
#define aligned_def aligned_4

#endif //end of _NIP_ALIGNED_H_
