//printf("\033[38;2;%d;%d;%dm%s\033[0m\n", r, g, b, text);
//NOTE:  TERM_COLORS FOR STRING LITERALS
#ifndef TERM_COLORS_HPP
#define TERM_COLORS_HPP

#define TERM_NRM "\x1B[0m"
#define TERM_RED(x) "\x1B[31m" x TERM_NRM
#define TERM_BLU(x) "\x1B[34m" x TERM_NRM
#define TERM_GRN(x) "\x1B[32m" x TERM_NRM
#define TERM_YEL(x) "\x1B[33m" x TERM_NRM
#define TERM_MAG(x) "\x1B[35m" x TERM_NRM
#define TERM_CYN(x) "\x1B[36m" x TERM_NRM
#define TERM_WHT(x) "\x1B[37m" x TERM_NRM

#endif // TERM_COLORS_HPP