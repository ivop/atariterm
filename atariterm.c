//
// Atari 800 emulator in xterm or Linux console
//
// Copyright © 2023 Ivo van Poorten
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <string.h>
#include <stdbool.h>
#include "libatari800.h"
#include "raw.h"

struct timespec ts = { 0, 20000000 };
struct termios orig_termios;

emulator_state_t state;

// the unicode strings

// Σ instead of the unreadable ␛

// left, top, bottom and right are 1/8th instead of 1/4 because there is no
// right 1/4.

const char *characters[128] = {
    "♥", "┣", "▕", "┛", "┫", "┓", "╱", "╲",
    "◢", "▗", "◣", "▝", "▘", "▔", "▁", "▖",
    "♣", "┏", "━", "╋", "●", "▄", "▏", "┳",
    "┻", "▌", "┗", "ϵ", "🠉", "🠋", "🠈", "🠊",
    " ", "!", "\"","#", "$", "%", "&", "'",
    "(", ")", "*", "+", ",", "-", ".", "/",
    "0", "1", "2", "3", "4", "5", "6", "7",
    "8", "9", ":", ";", "<", "=", ">", "?",
    "@", "A", "B", "C", "D", "E", "F", "G",
    "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W",
    "X", "Y", "Z", "[", "\\","]", "^", "▁",
    "♦", "a", "b", "c", "d", "e", "f", "g",
    "h", "i", "j", "k", "l", "m", "n", "o",
    "p", "q", "r", "s", "t", "u", "v", "w",
    "x", "y", "z", "♠", "┃", "🡴", "◀", "▶"
};

// xterm/vt100/ansi codes

char *CLEAR     = "c";
char *HOME      = "[H";
char *INVERSE   = "[7m";
char *NORMAL    = "[0m";
char *CURSOROFF = "[?25l";
char *CURSORON  = "[?25h";
char *RESET     = "c";

#define FG_BLACK    "[30m"
#define FG_RED      "[31m"
#define FG_GREEN    "[32m"
#define FG_YELLOW   "[33m"
#define FG_BLUE     "[34m"
#define FG_MAGENTA  "[35m"
#define FG_CYAN     "[36m"
#define FG_WHITE    "[37m"
#define FG_BBLACK   "[90m"
#define FG_BRED     "[91m"
#define FG_BGREEN   "[92m"
#define FG_BYELLOW  "[93m"
#define FG_BBLUE    "[94m"
#define FG_BMAGENTA "[95m"
#define FG_BCYAN    "[96m"
#define FG_BWHITE   "[97m"

#define BG_BLACK    "[40m"
#define BG_RED      "[41m"
#define BG_GREEN    "[42m"
#define BG_YELLOW   "[43m"
#define BG_BLUE     "[44m"
#define BG_MAGENTA  "[45m"
#define BG_CYAN     "[46m"
#define BG_WHITE    "[47m"
#define BG_BBLACK   "[100m"
#define BG_BRED     "[101m"
#define BG_BGREEN   "[102m"
#define BG_BYELLOW  "[103m"
#define BG_BBLUE    "[104m"
#define BG_BMAGENTA "[105m"
#define BG_BCYAN    "[106m"
#define BG_BWHITE   "[107m"

// xterm keycodes

char *KEY_F1    = "OP";
char *KEY_F2    = "OQ";
char *KEY_F3    = "OR";
char *KEY_F4    = "OS";
char *KEY_F5    = "[15~";
char *KEY_F6    = "[17~";
char *KEY_F7    = "[18~";
char *KEY_F8    = "[19~";
char *KEY_F9    = "[20~";

char *KEY_SHIFT_F5 = "[15;2~";

char *KEY_UP    = "[A";
char *KEY_DOWN  = "[B";
char *KEY_RIGHT = "[C";
char *KEY_LEFT  = "[D";

char *KEY_LALT_COMMA    = ",";
char *KEY_LALT_FULLSTOP = ".";
char *KEY_LALT_SEMI     = ";";

char *KEY_LALT_H = "h";
char *KEY_LALT_I = "i";
char *KEY_LALT_M = "m";

char *KEY_LALT_LBRACKET  = "[";
char *KEY_LALT_RBRACKET  = "]";
char *KEY_LALT_BACKSLASH = "\\";

char *KEY_HOME = "[H";
char *KEY_DEL  = "[3~";
char *KEY_INS  = "[2~";

char *KEY_SHIFT_DEL = "[3;2~";
char *KEY_SHIFT_INS = "RAW_AKEY_DELETE_LINE";

char alphabet[26] = {
    RAW_AKEY_a, RAW_AKEY_b, RAW_AKEY_c, RAW_AKEY_d, RAW_AKEY_e, RAW_AKEY_f,
    RAW_AKEY_g, RAW_AKEY_h, RAW_AKEY_i, RAW_AKEY_j, RAW_AKEY_k, RAW_AKEY_l,
    RAW_AKEY_m, RAW_AKEY_n, RAW_AKEY_o, RAW_AKEY_p, RAW_AKEY_q, RAW_AKEY_r,
    RAW_AKEY_s, RAW_AKEY_t, RAW_AKEY_u, RAW_AKEY_v, RAW_AKEY_w, RAW_AKEY_x,
    RAW_AKEY_y, RAW_AKEY_z
};

static int scr_to_atascii(int v) {
    if (           v<=0x3f)
        return v+0x20;
    if (v>=0x40 && v<=0x5f)
        return v-0x40;
    return v;
}

static const char const *fgdark[16] = {
    FG_BLACK, FG_RED, FG_RED, FG_RED, FG_MAGENTA, FG_MAGENTA, FG_MAGENTA,
    FG_BLUE, FG_BLUE, FG_BLUE, FG_GREEN, FG_GREEN, FG_GREEN, FG_GREEN, FG_RED,
    FG_RED
};

static const char const *fgbright[16] = {
    FG_WHITE, FG_BRED, FG_BRED, FG_BRED, FG_BMAGENTA, FG_BMAGENTA,
    FG_BMAGENTA, FG_BBLUE, FG_BBLUE, FG_BBLUE, FG_BGREEN, FG_BGREEN, FG_BGREEN,
    FG_BGREEN, FG_BRED, FG_BRED
};

static const char const *bgdark[16] = {
    BG_BLACK, BG_RED, BG_RED, BG_RED, BG_MAGENTA, BG_MAGENTA, BG_MAGENTA,
    BG_BLUE, BG_BLUE, BG_BLUE, BG_GREEN, BG_GREEN, BG_GREEN, BG_GREEN, BG_RED,
    BG_RED
};

static const char const *bgbright[16] = {
    BG_WHITE, BG_BRED, BG_BRED, BG_BRED, BG_BMAGENTA, BG_BMAGENTA,
    BG_BMAGENTA, BG_BBLUE, BG_BBLUE, BG_BBLUE, BG_BGREEN, BG_BGREEN,
    BG_BYELLOW, BG_BYELLOW, BG_BRED, BG_BRED
};

static void print_lms(unsigned char *lms, int wid, const char *color0,
        const char *color1, const char *color2, const char *color3,
        const char *bgcolor, const char *bkcolor) {
    int i;
    fputs(NORMAL, stdout);
    for (i=0; i<wid; i++) {
        int v,c;
        if (wid < 32) {
            v = lms[i];
            c = scr_to_atascii(v & 0x3f);
            switch(v>>6) {
                case 0: fputs(color0, stdout); break;
                case 1: fputs(color1, stdout); break;
                case 2: fputs(color2, stdout); break;
                case 3: fputs(color3, stdout); break;
            }
            fputs(bkcolor, stdout);
            c -= 32;
            c &= 0x3f;
            fputs(characters[c+32], stdout);
//            if (c >= 32 && c < 127) {
//                fputc(c, stdout);
//            } else {
//                fputc('.', stdout);
//            }
            fputc(' ', stdout);
        } else {
            v = lms[i];
            c = scr_to_atascii(v & 0x7f);
            if (v & 0x80)
                fputs(INVERSE, stdout);
            else
                fputs(NORMAL, stdout);
            fputs(bgcolor, stdout);
            fputs(color1, stdout);
            fputs(characters[c], stdout);
        }
    }
}

int widths40[4] = { 0, 32, 40, 48 };
int widths20[4] = { 0, 16, 20, 24 };

static void fake_antic() {
    unsigned char *dl;
    unsigned char *lms = 0;
    int h = 0;
    static int prevdlist = 0;

    fputs(HOME, stdout);
    fputs(CURSOROFF, stdout);

    libatari800_get_current_state(&state);
    unsigned char *mem = libatari800_get_main_memory_ptr();

    int dlist = ((antic_state_t *)&state.state[state.tags.antic])->dlist;
    int dmactl = ((antic_state_t *)&state.state[state.tags.antic])->DMACTL;

    if (!mem || !dlist) {
        fputs(CLEAR, stdout);
        return;
    }

    if (!dmactl&0x20)
        return;

    int c0 = ((gtia_state_t *)&state.state[state.tags.gtia])->COLPF0;
    int c1 = ((gtia_state_t *)&state.state[state.tags.gtia])->COLPF1;
    int c2 = ((gtia_state_t *)&state.state[state.tags.gtia])->COLPF2;
    int c3 = ((gtia_state_t *)&state.state[state.tags.gtia])->COLPF3;
    int bk = ((gtia_state_t *)&state.state[state.tags.gtia])->COLBK;
    const char *color0;
    const char *color1;
    const char *color2;
    const char *color3;
    const char *bgcolor;
    const char *bkcolor;

#define setcolor(c,cs) if ((c&0x0f)<8) cs=fgdark[c>>4]; else cs=fgbright[c>>4];

    setcolor(c0,color0);
    setcolor(c1,color1);
    setcolor(c2,color2);
    setcolor(c3,color3);
    setcolor(bk,bkcolor);

    if ((c2&0x0f)<8)
        bgcolor = bgdark[c2>>4];
    else
        bgcolor = bgbright[c2>>4];

    if (!strcmp(color2, color1)) { // force always contrasting colors in gr. 0
        if (color1 == fgdark[c1>>4]) {
            color1 = fgbright[c1>>4];
        } else {
            color1 = fgdark[c1>>4];
        }
    }

    if ((bk&0x0f)<8)
        bkcolor = bgdark[bk>>4];
    else
        bkcolor = bgbright[bk>>4];

    dmactl &= 0x3;

    int empty = 0;
    int scr = 0;

    dl = mem + dlist;

    for (int i=0; i<1024; i++) {
        int wid = 0;
        int instr = *dl++;
        _Bool prn = false;
        _Bool drw = false;

        switch (instr & 0x4f) {     // mask out DLI and scrolling
        case 0x00:
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:
        case 0x60:
        case 0x70:
            empty += (instr>>4)+1;
            break;
        case 0x41:
            goto endstop;
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
            empty = 0;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = widths40[dmactl];
            prn = true;
            break;
        case 0x46:
        case 0x47:
            empty = 0;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = widths20[dmactl];
            prn = true;
            break;
        case 0x48:      // gr. 3    40 pixels, 4 colors = 10 bytes
            empty += 8;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 10;
            drw = true;
            break;
        case 0x49:      // gr. 4    80 pixels, 2 colors = 10 bytes
            empty += 4;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 10;
            drw = true;
            break;
        case 0x4a:      // gr. 5    80 pixels, 4 colors = 20 bytes
            empty += 4;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 20;
            drw = true;
            break;
        case 0x4b:      // gr. 6    160 pixels, 2 colors = 20 bytes
            empty += 2;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 20;
            drw = true;
            break;
        case 0x4c:      // gr. 15-  160 pixels, 2 colors = 20 bytes
            empty += 1;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 20;
            drw = true;
            break;
        case 0x4d:      // gr. 7    160 pixels, 4 colors = 40 bytes
            empty += 2;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 40;
            drw = true;
            break;
        case 0x4e:      // gr. 15   160 pixels, 4 colors = 40 bytes
            empty += 1;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 40;
            drw = true;
            break;
        case 0x4f:      // gr. 8    320 pixels, 2 colors = 40 bytes
            empty += 1;
            scr = *dl++ | (*dl++<<8);
            lms = mem + scr;
            wid = 40;
            drw = true;
            break;
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
            empty = 0;
            wid = widths40[dmactl];
            prn = true;
            break;
        case 0x06:
        case 0x07:
            empty = 0;
            wid = widths20[dmactl];
            prn = true;
            break;
        case 0x08:      // gr. 3    40 pixels, 4 colors = 10 bytes
            empty += 8;
            wid = 10;
            drw = true;
            break;
        case 0x09:      // gr. 4    80 pixels, 2 colors = 10 bytes
            empty += 4;
            wid = 10;
            drw = true;
            break;
        case 0x0a:      // gr. 5    80 pixels, 4 colors = 20 bytes
            empty += 4;
            wid = 20;
            drw = true;
            break;
        case 0x0b:      // gr. 6    160 pixels, 2 colors = 20 bytes
            empty += 2;
            wid = 20;
            drw = true;
            break;
        case 0x0c:      // gr. 15-  160 pixels, 2 colors = 20 bytes
            empty += 1;
            wid = 20;
            drw = true;
            break;
        case 0x0d:      // gr. 7    160 pixels, 4 colors = 40 bytes
            empty += 2;
            wid = 40;
            drw = true;
            break;
        case 0x0e:      // gr. 15   160 pixels, 4 colors = 40 bytes
            empty += 1;
            wid = 40;
            drw = true;
            break;
        case 0x0f:      // gr. 8    320 pixels, 2 colors = 40 bytes
            empty += 1;
            wid = 40;
            drw = true;
            break;
        default:        // all non-character graphics modes
            break;
        }
        if (prn) {
            prn = false;
            if (lms) {
                fputs(bkcolor, stdout);
                if (wid == 32 || wid == 16)
                    fputs("        ", stdout);
                if (wid == 40 || wid == 20)
                    fputs("    ", stdout);

                print_lms(lms, wid, color0, color1, color2, color3, bgcolor, bkcolor);

                fputs(NORMAL, stdout);
                fputs(bkcolor, stdout);
                if (wid == 32 || wid == 16)
                    fputs("        ", stdout);
                if (wid == 40 || wid == 20)
                    fputs("    ", stdout);
            }
            fputs("\r\n",stdout);
            h++;
            if (instr & 7 == 7) {       // double height characters gr. 2
                fputs("                        "
                      "                        \r\n", stdout);
                h++;
            }
        }
        while (empty >= 8) {
            h++;
            fputs(bkcolor, stdout);
            fputs("                        "
                  "                        \r\n", stdout);
            empty -= 8;
        }
        if (lms)
            lms += wid;
        if (h == 30) break;
    }
endstop:
    fputs(bkcolor, stdout);
    for (; h < 30; h++)
        fputs("                        "
              "                        \r\n", stdout);
stop:
    fputs("[m", stdout);
    printf("[1MDL: %04X ", dlist);
    fflush(stdout);
}

static void reset_terminal_mode(void) {
    tcsetattr(0, TCSANOW, &orig_termios);
    fputs(RESET, stdout);
}

static int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int main(int argc, char **argv) {
    char keybuf[32];
    input_template_t input;
    int i, j;

    // Fill in some useless setting to suppress error. 
    argv[0] = "-pal";

    libatari800_init(argc, argv);
    libatari800_clear_input_array(&input);

    struct termios new_termios;

    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);

    fputs(CLEAR, stdout);
    fputs(CURSOROFF, stdout);
    fflush(stdout);

    int len = 0;
    int cnt = 0;

    while(1) {
        libatari800_next_frame(&input);
            libatari800_clear_input_array(&input);
        fake_antic();

            keybuf[len] = 0;
            printf("%d: ", len);
            for (int i=0; i<len; i++)
                printf("%02X ", keybuf[i]);
            fflush(stdout);

        nanosleep(&ts, NULL);
        if (kbhit()) {
            len = read(0, keybuf,32);

            if (!strcmp(KEY_F2, keybuf))
                input.option = 1;
            if (!strcmp(KEY_F3, keybuf))
                input.select = 1;
            if (!strcmp(KEY_F4, keybuf))
                input.start = 1;
            if (!strcmp(KEY_F5, keybuf))
                input.special = abs(RAW_AKEY_WARMSTART);
            if (!strcmp(KEY_SHIFT_F5, keybuf))
                input.special = abs(RAW_AKEY_COLDSTART);
            if (!strcmp(KEY_F6, keybuf))
               input.keycode = RAW_AKEY_HELP; 
            if (!strcmp(KEY_F7, keybuf))
                input.special = abs(RAW_AKEY_BREAK);
            if (!strcmp(KEY_F8, keybuf))
                input.keycode = RAW_AKEY_CAPSTOGGLE;
            if (!strcmp(KEY_F9, keybuf))
                exit(0);

            if (!strcmp(KEY_F1, keybuf)) {
                printf("PAUSE");
                fflush(stdout);
                while (!kbhit())
                    ;
            }

            if (!strcmp(KEY_UP, keybuf))
                input.keycode = RAW_AKEY_UP;
            if (!strcmp(KEY_DOWN, keybuf))
                input.keycode = RAW_AKEY_DOWN;
            if (!strcmp(KEY_RIGHT, keybuf))
                input.keycode = RAW_AKEY_RIGHT;
            if (!strcmp(KEY_LEFT, keybuf))
                input.keycode = RAW_AKEY_LEFT;

            if (!strcmp(KEY_LALT_COMMA, keybuf))
                input.keycode = RAW_AKEY_COMMA | RAW_AKEY_CTRL;
            if (!strcmp(KEY_LALT_FULLSTOP, keybuf))
                input.keycode = RAW_AKEY_FULLSTOP | RAW_AKEY_CTRL;
            if (!strcmp(KEY_LALT_SEMI, keybuf))
                input.keycode = RAW_AKEY_SEMICOLON | RAW_AKEY_CTRL;

            if (!strcmp(KEY_LALT_LBRACKET, keybuf) ||
                !strcmp(KEY_LALT_H,keybuf))
                input.keycode = RAW_AKEY_h | RAW_AKEY_CTRL;
            if (!strcmp(KEY_LALT_RBRACKET, keybuf) ||
                !strcmp(KEY_LALT_I,keybuf))
                input.keycode = RAW_AKEY_i | RAW_AKEY_CTRL;
            if (!strcmp(KEY_LALT_BACKSLASH, keybuf) ||
                !strcmp(KEY_LALT_M,keybuf))
                input.keycode = RAW_AKEY_m | RAW_AKEY_CTRL;

            if (!strcmp(KEY_HOME, keybuf))
                input.keycode = RAW_AKEY_CLEAR;
            if (!strcmp(KEY_INS, keybuf))
                input.keycode = RAW_AKEY_INSERT_CHAR;
            if (!strcmp(KEY_DEL, keybuf))
                input.keycode = RAW_AKEY_DELETE_CHAR;
            if (!strcmp(KEY_SHIFT_INS, keybuf))
                input.keycode = RAW_AKEY_INSERT_LINE;
            if (!strcmp(KEY_SHIFT_DEL, keybuf))
                input.keycode = RAW_AKEY_DELETE_LINE;

            if (len == 1 && !input.keycode && !input.special) {
                int k = keybuf[0];
                if (k == 0x08 || k == 0x7f)
                    input.keycode = RAW_AKEY_BACKSPACE;
                if (k == 0x09)
                    input.keycode = RAW_AKEY_TAB;
                if (k == 0x0d)
                    input.keycode = RAW_AKEY_RETURN;
                if (k == '`')
                    input.keycode = RAW_AKEY_ATARI;
                if (!input.keycode) {
                    if (k >=  1 && k <=26) {
                        input.keycode = alphabet[k-1] | RAW_AKEY_CTRL;
                    } else if (k >= 65 && k <=90) {
                        input.keycode = alphabet[k-65] | RAW_AKEY_SHFT;
                    } else {
                        input.keychar = k;
                    }
                }
            }
            cnt = 5;
        } // kbhit
	} // while 1
}
