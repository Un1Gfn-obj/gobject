#ifndef __DEF_H__
#define __DEF_H__

#if defined(PLACEHOLDER)
#elif defined(F) && !defined(D) &&  defined(N) && !defined(P)
#pragma GCC warning "final, w/o private"
#elif defined(F) && !defined(D) && !defined(N) &&  defined(P)
#pragma GCC warning "final, w/ private"
#elif !defined(F) && defined(D) &&  defined(N) && !defined(P)
#pragma GCC warning "derivable, w/o private"
#elif !defined(F) && defined(D) && !defined(N) &&  defined(P)
#pragma GCC warning "derivable, w/ private"
#else
#pragma GCC error "conflict"
#endif

#endif
