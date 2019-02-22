#ifndef FLAGS
#define FLAGS

#define SET_FLAG(VAR,BIT) (VAR|= (1 << BIT))
#define CLEAR_FLAG(VAR,BIT) (VAR &= ~(1 << BIT))
#define CHECK_FLAG(VAR,BIT) (VAR & 1<< BIT)
#endif
