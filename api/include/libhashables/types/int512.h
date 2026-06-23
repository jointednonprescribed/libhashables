
#ifndef _LIBHASHABLES__types_INT512_H_
#define _LIBHASHABLES__types_INT512_H_ 1

#ifndef _LIBHASHABLES__INCLUDES_H_
#   include "../includes.h"
#endif



LHASH_EXTERN_C


/*
 * 128-bit integer type
 */
typedef struct _lhashint512_t
{
    unsigned long long v[8];
} lhashint512_t, lhashuint512_t;

#define lhashint512_0 (lhashint512_t){.v={0}}

typedef struct _lhashint512_pair_t
{
    lhashuint512_t v[2];
} lhashint512_pair_t, lhashuint512_pair_t;

LHASH_API lhashint512_t  lhashint512(long long int);
LHASH_API lhashuint512_t lhashuint512(unsigned long long int);
LHASH_API lhashint512_t  lhashint512l(long int);
LHASH_API lhashuint512_t lhashuint512l(unsigned long int);

LHASH_API lhashint512_t  lhashint512_pair(lhashint512_t a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_pair(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashint512_t  lhashint512_pairll(long long a, long long b);
LHASH_API lhashuint512_t lhashuint512_pairll(unsigned long long a, unsigned long long b);
LHASH_API lhashint512_t  lhashint512_pairl(long a, long b);
LHASH_API lhashuint512_t lhashuint512_pairl(unsigned long a, unsigned long b);

LHASH_API lhashint512_t  lhashint512_add(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_addll(lhashint512_t a, long long b);
LHASH_API lhashint512_t  lhashint512_addl(lhashint512_t a, long b);
LHASH_API lhashuint512_t lhashuint512_add(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_t lhashuint512_addll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_t lhashuint512_addl(lhashuint512_t a, long b);
LHASH_API lhashint512_t  lhashint512_addeq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_addlleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_t  lhashint512_addleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_t lhashuint512_addeq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_addlleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_t lhashuint512_addleq(lhashuint512_t *a, long b);

LHASH_API lhashint512_t  lhashint512_sub(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_subll(lhashint512_t a, long long b);
LHASH_API lhashint512_t  lhashint512_subl(lhashint512_t a, long b);
LHASH_API lhashuint512_t lhashuint512_sub(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_t lhashuint512_subll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_t lhashuint512_subl(lhashuint512_t a, long b);
LHASH_API lhashint512_t  lhashint512_subeq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_sublleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_t  lhashint512_subleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_t lhashuint512_subeq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_sublleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_t lhashuint512_subleq(lhashuint512_t *a, long b);

LHASH_API lhashint512_t  lhashint512_mult(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_multll(lhashint512_t a, long long b);
LHASH_API lhashint512_t  lhashint512_multl(lhashint512_t a, long b);
LHASH_API lhashuint512_t lhashuint512_mult(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_t lhashuint512_multll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_t lhashuint512_multl(lhashuint512_t a, long b);
LHASH_API lhashint512_t  lhashint512_multeq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_multlleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_t  lhashint512_multleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_t lhashuint512_multeq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_multlleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_t lhashuint512_multleq(lhashuint512_t *a, long b);

LHASH_API lhashint512_t  lhashint512_div(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_divll(lhashint512_t a, long long b);
LHASH_API lhashint512_t  lhashint512_divl(lhashint512_t a, long b);
LHASH_API lhashuint512_t lhashuint512_div(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_t lhashuint512_divll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_t lhashuint512_divl(lhashuint512_t a, long b);
LHASH_API lhashint512_t  lhashint512_diveq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_divlleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_t  lhashint512_divleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_t lhashuint512_diveq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_divlleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_t lhashuint512_divleq(lhashuint512_t *a, long b);

LHASH_API lhashint512_t  lhashint512_mod(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_modll(lhashint512_t a, long long b);
LHASH_API lhashint512_t  lhashint512_modl(lhashint512_t a, long b);
LHASH_API lhashuint512_t lhashuint512_mod(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_t lhashuint512_modll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_t lhashuint512_modl(lhashuint512_t a, long b);
LHASH_API lhashint512_t  lhashint512_modeq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_modlleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_t  lhashint512_modleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_t lhashuint512_modeq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_modlleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_t lhashuint512_modleq(lhashuint512_t *a, long b);

LHASH_API lhashint512_pair_t  lhashint512_syndiv(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_pair_t  lhashint512_syndivll(lhashint512_t a, long long b);
LHASH_API lhashint512_pair_t  lhashint512_syndivl(lhashint512_t a, long b);
LHASH_API lhashuint512_pair_t lhashuint512_syndiv(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_pair_t lhashuint512_syndivll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_pair_t lhashuint512_syndivl(lhashuint512_t a, long b);
LHASH_API lhashint512_pair_t  lhashint512_syndiveq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_pair_t  lhashint512_syndivlleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_pair_t  lhashint512_syndivleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_pair_t lhashuint512_syndiveq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_pair_t lhashuint512_syndivlleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_pair_t lhashuint512_syndivleq(lhashuint512_t *a, long b);

LHASH_API lhashint512_t  lhashint512_shr(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_shrll(lhashint512_t a, long long b);
LHASH_API lhashint512_t  lhashint512_shrl(lhashint512_t a, long b);
LHASH_API lhashuint512_t lhashuint512_shr(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_t lhashuint512_shrll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_t lhashuint512_shrl(lhashuint512_t a, long b);
LHASH_API lhashint512_t  lhashint512_shreq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_shrlleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_t  lhashint512_shrleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_t lhashuint512_shreq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_shrlleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_t lhashuint512_shrleq(lhashuint512_t *a, long b);

LHASH_API lhashint512_t  lhashint512_shl(lhashint512_t a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_shlll(lhashint512_t a, long long b);
LHASH_API lhashint512_t  lhashint512_shll(lhashint512_t a, long b);
LHASH_API lhashuint512_t lhashuint512_shl(lhashuint512_t a, lhashuint512_t b);
LHASH_API lhashuint512_t lhashuint512_shlll(lhashuint512_t a, long long b);
LHASH_API lhashuint512_t lhashuint512_shll(lhashuint512_t a, long b);
LHASH_API lhashint512_t  lhashint512_shleq(lhashint512_t *a, lhashint512_t b);
LHASH_API lhashint512_t  lhashint512_shllleq(lhashint512_t *a, long long b);
LHASH_API lhashint512_t  lhashint512_shlleq(lhashint512_t *a, long b);
LHASH_API lhashuint512_t lhashuint512_shleq(lhashuint512_t *a, lhashint512_t b);
LHASH_API lhashuint512_t lhashuint512_shllleq(lhashuint512_t *a, long long b);
LHASH_API lhashuint512_t lhashuint512_shlleq(lhashuint512_t *a, long b);

LHASH_API int            lhashint512_cmp(lhashint512_t a, lhashint512_t b);
LHASH_API int            lhashint512_cmpll(lhashint512_t a, long long b);
LHASH_API int            lhashint512_cmpl(lhashint512_t a, long b);
LHASH_API int            lhashuint512_cmp(lhashuint512_t a, lhashuint512_t b);
LHASH_API int            lhashuint512_cmpll(lhashuint512_t a, long long b);
LHASH_API int            lhashuint512_cmpl(lhashuint512_t a, long b);

LHASH_API bool           lhashint512_cmple(lhashint512_t a, lhashint512_t b);
LHASH_API bool           lhashint512_cmplell(lhashint512_t a, long long b);
LHASH_API bool           lhashint512_cmplel(lhashint512_t a, long b);
LHASH_API bool           lhashuint512_cmple(lhashuint512_t a, lhashuint512_t b);
LHASH_API bool           lhashuint512_cmplell(lhashuint512_t a, long long b);
LHASH_API bool           lhashuint512_cmplel(lhashuint512_t a, long b);

LHASH_API bool           lhashint512_cmplt(lhashint512_t a, lhashint512_t b);
LHASH_API bool           lhashint512_cmpltll(lhashint512_t a, long long b);
LHASH_API bool           lhashint512_cmpltl(lhashint512_t a, long b);
LHASH_API bool           lhashuint512_cmplt(lhashuint512_t a, lhashuint512_t b);
LHASH_API bool           lhashuint512_cmpltll(lhashuint512_t a, long long b);
LHASH_API bool           lhashuint512_cmpltl(lhashuint512_t a, long b);

LHASH_API bool           lhashint512_cmpge(lhashint512_t a, lhashint512_t b);
LHASH_API bool           lhashint512_cmpgell(lhashint512_t a, long long b);
LHASH_API bool           lhashint512_cmpgel(lhashint512_t a, long b);
LHASH_API bool           lhashuint512_cmpge(lhashuint512_t a, lhashuint512_t b);
LHASH_API bool           lhashuint512_cmpgell(lhashuint512_t a, long long b);
LHASH_API bool           lhashuint512_cmpgel(lhashuint512_t a, long b);

LHASH_API bool           lhashint512_cmpgt(lhashint512_t a, lhashint512_t b);
LHASH_API bool           lhashint512_cmpgtll(lhashint512_t a, long long b);
LHASH_API bool           lhashint512_cmpgtl(lhashint512_t a, long b);
LHASH_API bool           lhashuint512_cmpgt(lhashuint512_t a, lhashuint512_t b);
LHASH_API bool           lhashuint512_cmpgtll(lhashuint512_t a, long long b);
LHASH_API bool           lhashuint512_cmpgtl(lhashuint512_t a, long b);

LHASH_API bool           lhashint512_cmpeq(lhashint512_t a, lhashint512_t b);
LHASH_API bool           lhashint512_cmpeqll(lhashint512_t a, long long b);
LHASH_API bool           lhashint512_cmpeql(lhashint512_t a, long b);
LHASH_API bool           lhashuint512_cmpeq(lhashuint512_t a, lhashuint512_t b);
LHASH_API bool           lhashuint512_cmpeqll(lhashuint512_t a, long long b);
LHASH_API bool           lhashuint512_cmpeql(lhashuint512_t a, long b);

LHASH_API bool           lhashint512_cmpne(lhashint512_t a, lhashint512_t b);
LHASH_API bool           lhashint512_cmpnell(lhashint512_t a, long long b);
LHASH_API bool           lhashint512_cmpnel(lhashint512_t a, long b);
LHASH_API bool           lhashuint512_cmpne(lhashuint512_t a, lhashuint512_t b);
LHASH_API bool           lhashuint512_cmpnell(lhashuint512_t a, long long b);
LHASH_API bool           lhashuint512_cmpnel(lhashuint512_t a, long b);


LHASH_END_EXTERN_C



#endif // _LIBHASHABLES__types_INT512_H_
