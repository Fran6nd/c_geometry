#ifndef MACROS_H
#define MACROS_H
#define KEEP_2_ZEROS(n) ((double)((int) (n*100))/100)
#define ACCURACY 100
#define ALMOST_EQ(a, b) (a * ACCURACY - b* ACCURACY) * (a * ACCURACY - b* ACCURACY)  < ACCURACY * ACCURACY
#endif