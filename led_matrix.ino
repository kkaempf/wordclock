#define NUM_LEDS     121

/*
 *    1   2   3   4   5   6   7   8   9  10  11
 *   Neu  E   s   r   i   s   t   a   ¢   k  ab
 *   22  21  20  19  18  17  16  15  14  13  12
 *    2   0   f   ü   n   f   z   e   h   n   e
 *   23  24  25  26  27  28  29  30  31  32  33
 *    d   r   e   i   v   i   e   r   t   e   l
 *   44  43  42  41  40  39  38  37  36  35  34
 *    z   w   a   n   z   i   g   t   v   o   r
 *   45  46  47  48  49  50  51  52  53  54  55
 *    n   a   c   h   1   6   h   a   l   b   k
 *   66  65  64  63  62  61  60  59  58  57  56
 *    a   s   e   c   h   s   i   e   b   e   n
 *   67  68  69  70  71  72  73  74  75  76  77
 *    z   w   e   i   e   l   f   d   r   e   i
 *   88  87  86  85  84  83  82  81  80  79  78
 *    v   i   e   r   b   y   t   f   ü   n   f
 *   89  90  91  92  93  94  95  96  97  98  99
 *    k   a   c   h   t   K   l   a   u   s   w
 *  110 109 108 107 106 105 104 103 102 101 100
 *    z   e   h   n   e   u   n   e   i   n   s
 *  111 112 113 114 115 116 117 118 119 120 121
 *   zu   z   w   ö   l   f   k   U   h   r Vol 
 */

byte w_es[] = {1, 2};
byte w_ist[] = {4, 3};
byte w_fuenf_m[] = {16, 4};
byte w_zehn_m[] = {12, 4};
byte w_dreiviertel[] = {22, 11};
byte w_viertel[] = {26, 7};
byte w_zwanzig[] = {37, 7};
byte w_vor[] = {33, 3};
byte w_nach[] = {44, 4};
byte w_halb[] = {50, 4};
byte w_sechs[] = {60, 5};
byte w_sieben[] = {55, 6};
byte w_zwei[] = {66, 4};
byte w_elf[] = {70, 3};
byte w_drei[] = {73, 4};
byte w_vier[] = {84, 4};
byte w_fuenf_s[] = {77, 4};
byte w_acht[] = {89, 4};
byte w_klaus[] = {93, 5};
byte w_zehn_s[] = {106, 4};
byte w_neun[] = {103, 4};
byte w_eins[] = {99, 4};
byte w_zwoelf[] = {111, 5};
byte w_uhr[] = {117, 3};
byte w_2016[] = {19, 4};
byte w_by[] = {82, 2};

byte *a_stunden[] = {w_zwoelf, w_eins, w_zwei, w_drei, w_vier, w_fuenf_s, w_sechs, w_sieben, w_acht, w_neun, w_zehn_s, w_elf};
/* 5-minute chunks   0      5          10        15         20         25         30      35         40         45         50        55 */
byte *a_minuten[] = {w_uhr, w_fuenf_m, w_zehn_m, w_viertel, w_zwanzig, w_fuenf_m, w_halb, w_fuenf_m, w_zwanzig, w_viertel, w_zehn_m, w_fuenf_m};

