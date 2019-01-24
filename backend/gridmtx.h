/*  gridmtx.h - definitions for Grid Matrix

    libzint - the open source barcode library
    Copyright (C) 2009-2017 Robin Stuart <rstuart114@gmail.com>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the project nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
 */

#define GM_NUMBER	1
#define GM_LOWER	2
#define GM_UPPER	3
#define GM_MIXED	4
#define GM_CONTROL	5
#define GM_BYTE		6
#define GM_CHINESE	7

#define EUROPIUM	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz "

static const char shift_set[] = {
    /* From Table 7 - Encoding of control characters */
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, /* NULL -> SI */
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, /* DLE -> US */
    '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':',
    ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'
};

static const unsigned short int gm_recommend_cw[] = {
    9, 30, 59, 114, 170, 237, 315, 405, 506, 618, 741, 875, 1021
};

static const unsigned short int gm_max_cw[] = {
    11, 40, 79, 146, 218, 305, 405, 521, 650, 794, 953, 1125, 1313
};

static const unsigned short int gm_data_codewords[] = {
    0, 15, 13, 11, 9,
    45, 40, 35, 30, 25,
    89, 79, 69, 59, 49,
    146, 130, 114, 98, 81,
    218, 194, 170, 146, 121,
    305, 271, 237, 203, 169,
    405, 360, 315, 270, 225,
    521, 463, 405, 347, 289,
    650, 578, 506, 434, 361,
    794, 706, 618, 530, 441,
    953, 847, 741, 635, 529,
    1125, 1000, 875, 750, 625,
    1313, 1167, 1021, 875, 729
};

static const char gm_n1[] = {
    18, 50, 98, 81, 121, 113, 113, 116, 121, 126, 118, 125, 122
};

static const char gm_b1[] = {
    1, 1, 1, 2, 2, 2, 2, 3, 2, 7, 5, 10, 6
};

static const char gm_b2[] = {
    0, 0, 0, 0, 0, 1, 2, 2, 4, 0, 4, 0, 6
};

/* Values from table A.1 */
static const char gm_ebeb[] = {
    /* E1 B3 E2 B4 */
    0, 0, 0, 0, // version 1
    3, 1, 0, 0,
    5, 1, 0, 0,
    7, 1, 0, 0,
    9, 1, 0, 0,
    5, 1, 0, 0, // version 2
    10, 1, 0, 0,
    15, 1, 0, 0,
    20, 1, 0, 0,
    25, 1, 0, 0,
    9, 1, 0, 0, // version 3
    19, 1, 0, 0,
    29, 1, 0, 0,
    39, 1, 0, 0,
    49, 1, 0, 0,
    8, 2, 0, 0, // version 4
    16, 2, 0, 0,
    24, 2, 0, 0,
    32, 2, 0, 0,
    41, 1, 40, 1,
    12, 2, 0, 0, // version 5
    24, 2, 0, 0,
    36, 2, 0, 0,
    48, 2, 0, 0,
    61, 1, 60, 1,
    11, 3, 0, 0, // version 6
    23, 1, 22, 2,
    34, 2, 33, 1,
    45, 3, 0, 0,
    57, 1, 56, 2,
    12, 1, 11, 3, // version 7
    23, 2, 22, 2,
    34, 3, 33, 1,
    45, 4, 0, 0,
    57, 1, 56, 3,
    12, 2, 11, 3, // version 8
    23, 5, 0, 0,
    35, 3, 34, 2,
    47, 1, 46, 4,
    58, 4, 57, 1,
    12, 6, 0, 0, // version 9
    24, 6, 0, 0,
    36, 6, 0, 0,
    48, 6, 0, 0,
    61, 1, 60, 5,
    13, 4, 12, 3, // version 10
    26, 1, 25, 6,
    38, 5, 37, 2,
    51, 2, 50, 5,
    63, 7, 0, 0,
    12, 6, 11, 3, // version 11
    24, 4, 23, 5,
    36, 2, 35, 7,
    47, 9, 0, 0,
    59, 7, 58, 2,
    13, 5, 12, 5, // version 12
    25, 10, 0, 0,
    38, 5, 37, 5,
    50, 10, 0, 0,
    63, 5, 62, 5,
    13, 1, 12, 11, //version 13
    25, 3, 24, 9,
    37, 5, 36, 7,
    49, 7, 48, 5,
    61, 9, 60, 3
};

static const unsigned short int gm_macro_matrix[] = {
    728, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645, 646, 647, 648, 649, 650,
    727, 624, 529, 530, 531, 532, 533, 534, 535, 536, 537, 538, 539, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 651,
    726, 623, 528, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 553, 652,
    725, 622, 527, 440, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 463, 554, 653,
    724, 621, 526, 439, 360, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 381, 464, 555, 654,
    723, 620, 525, 438, 359, 288, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 307, 382, 465, 556, 655,
    722, 619, 524, 437, 358, 287, 224, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 241, 308, 383, 466, 557, 656,
    721, 618, 523, 436, 357, 286, 223, 168, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 183, 242, 309, 384, 467, 558, 657,
    720, 617, 522, 435, 356, 285, 222, 167, 120, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 133, 184, 243, 310, 385, 468, 559, 658,
    719, 616, 521, 434, 355, 284, 221, 166, 119, 80, 49, 50, 51, 52, 53, 54, 55, 56, 91, 134, 185, 244, 311, 386, 469, 560, 659,
    718, 615, 520, 433, 354, 283, 220, 165, 118, 79, 48, 25, 26, 27, 28, 29, 30, 57, 92, 135, 186, 245, 312, 387, 470, 561, 660,
    717, 614, 519, 432, 353, 282, 219, 164, 117, 78, 47, 24, 9, 10, 11, 12, 31, 58, 93, 136, 187, 246, 313, 388, 471, 562, 661,
    716, 613, 518, 431, 352, 281, 218, 163, 116, 77, 46, 23, 8, 1, 2, 13, 32, 59, 94, 137, 188, 247, 314, 389, 472, 563, 662,
    715, 612, 517, 430, 351, 280, 217, 162, 115, 76, 45, 22, 7, 0, 3, 14, 33, 60, 95, 138, 189, 248, 315, 390, 473, 564, 663,
    714, 611, 516, 429, 350, 279, 216, 161, 114, 75, 44, 21, 6, 5, 4, 15, 34, 61, 96, 139, 190, 249, 316, 391, 474, 565, 664,
    713, 610, 515, 428, 349, 278, 215, 160, 113, 74, 43, 20, 19, 18, 17, 16, 35, 62, 97, 140, 191, 250, 317, 392, 475, 566, 665,
    712, 609, 514, 427, 348, 277, 214, 159, 112, 73, 42, 41, 40, 39, 38, 37, 36, 63, 98, 141, 192, 251, 318, 393, 476, 567, 666,
    711, 608, 513, 426, 347, 276, 213, 158, 111, 72, 71, 70, 69, 68, 67, 66, 65, 64, 99, 142, 193, 252, 319, 394, 477, 568, 667,
    710, 607, 512, 425, 346, 275, 212, 157, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 143, 194, 253, 320, 395, 478, 569, 668,
    709, 606, 511, 424, 345, 274, 211, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 195, 254, 321, 396, 479, 570, 669,
    708, 605, 510, 423, 344, 273, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 255, 322, 397, 480, 571, 670,
    707, 604, 509, 422, 343, 272, 271, 270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257, 256, 323, 398, 481, 572, 671,
    706, 603, 508, 421, 342, 341, 340, 339, 338, 337, 336, 335, 334, 333, 332, 331, 330, 329, 328, 327, 326, 325, 324, 399, 482, 573, 672,
    705, 602, 507, 420, 419, 418, 417, 416, 415, 414, 413, 412, 411, 410, 409, 408, 407, 406, 405, 404, 403, 402, 401, 400, 483, 574, 673,
    704, 601, 506, 505, 504, 503, 502, 501, 500, 499, 498, 497, 496, 495, 494, 493, 492, 491, 490, 489, 488, 487, 486, 485, 484, 575, 674,
    703, 600, 599, 598, 597, 596, 595, 594, 593, 592, 591, 590, 589, 588, 587, 586, 585, 584, 583, 582, 581, 580, 579, 578, 577, 576, 675,
    702, 701, 700, 699, 698, 697, 696, 695, 694, 693, 692, 691, 690, 689, 688, 687, 686, 685, 684, 683, 682, 681, 680, 679, 678, 677, 676,
};
