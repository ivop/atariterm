#ifndef RAW_AKEY_HEADER
#define RAW_AKEY_HEADER

/* Special key codes. */
#define RAW_AKEY_WARMSTART             -2
#define RAW_AKEY_COLDSTART             -3
#define RAW_AKEY_EXIT                  -4
#define RAW_AKEY_BREAK                 -5
#define RAW_AKEY_UI                    -7
#define RAW_AKEY_SCREENSHOT            -8
#define RAW_AKEY_SCREENSHOT_INTERLACE  -9
#define RAW_AKEY_START                 -10
#define RAW_AKEY_SELECT                -11
#define RAW_AKEY_OPTION                -12
#define RAW_AKEY_PBI_BB_MENU           -13
#define RAW_AKEY_CX85_1                -14
#define RAW_AKEY_CX85_2                -15
#define RAW_AKEY_CX85_3                -16
#define RAW_AKEY_CX85_4                -17
#define RAW_AKEY_CX85_5                -18
#define RAW_AKEY_CX85_6                -19
#define RAW_AKEY_CX85_7                -20
#define RAW_AKEY_CX85_8                -21
#define RAW_AKEY_CX85_9                -22
#define RAW_AKEY_CX85_0                -23
#define RAW_AKEY_CX85_PERIOD           -24
#define RAW_AKEY_CX85_MINUS            -25
#define RAW_AKEY_CX85_PLUS_ENTER       -26
#define RAW_AKEY_CX85_ESCAPE           -27
#define RAW_AKEY_CX85_NO               -28
#define RAW_AKEY_CX85_DELETE           -29
#define RAW_AKEY_CX85_YES              -30
#define RAW_AKEY_TURBO                 -31

#define RAW_AKEY_SHFT 0x40
#define RAW_AKEY_CTRL 0x80
#define RAW_AKEY_SHFTCTRL 0xc0

#define RAW_AKEY_0 0x32
#define RAW_AKEY_1 0x1f
#define RAW_AKEY_2 0x1e
#define RAW_AKEY_3 0x1a
#define RAW_AKEY_4 0x18
#define RAW_AKEY_5 0x1d
#define RAW_AKEY_6 0x1b
#define RAW_AKEY_7 0x33
#define RAW_AKEY_8 0x35
#define RAW_AKEY_9 0x30

#define RAW_AKEY_CTRL_0 (RAW_AKEY_CTRL | RAW_AKEY_0)
#define RAW_AKEY_CTRL_1 (RAW_AKEY_CTRL | RAW_AKEY_1)
#define RAW_AKEY_CTRL_2 (RAW_AKEY_CTRL | RAW_AKEY_2)
#define RAW_AKEY_CTRL_3 (RAW_AKEY_CTRL | RAW_AKEY_3)
#define RAW_AKEY_CTRL_4 (RAW_AKEY_CTRL | RAW_AKEY_4)
#define RAW_AKEY_CTRL_5 (RAW_AKEY_CTRL | RAW_AKEY_5)
#define RAW_AKEY_CTRL_6 (RAW_AKEY_CTRL | RAW_AKEY_6)
#define RAW_AKEY_CTRL_7 (RAW_AKEY_CTRL | RAW_AKEY_7)
#define RAW_AKEY_CTRL_8 (RAW_AKEY_CTRL | RAW_AKEY_8)
#define RAW_AKEY_CTRL_9 (RAW_AKEY_CTRL | RAW_AKEY_9)

#define RAW_AKEY_a 0x3f
#define RAW_AKEY_b 0x15
#define RAW_AKEY_c 0x12
#define RAW_AKEY_d 0x3a
#define RAW_AKEY_e 0x2a
#define RAW_AKEY_f 0x38
#define RAW_AKEY_g 0x3d
#define RAW_AKEY_h 0x39
#define RAW_AKEY_i 0x0d
#define RAW_AKEY_j 0x01
#define RAW_AKEY_k 0x05
#define RAW_AKEY_l 0x00
#define RAW_AKEY_m 0x25
#define RAW_AKEY_n 0x23
#define RAW_AKEY_o 0x08
#define RAW_AKEY_p 0x0a
#define RAW_AKEY_q 0x2f
#define RAW_AKEY_r 0x28
#define RAW_AKEY_s 0x3e
#define RAW_AKEY_t 0x2d
#define RAW_AKEY_u 0x0b
#define RAW_AKEY_v 0x10
#define RAW_AKEY_w 0x2e
#define RAW_AKEY_x 0x16
#define RAW_AKEY_y 0x2b
#define RAW_AKEY_z 0x17

#define RAW_AKEY_A (RAW_AKEY_SHFT | RAW_AKEY_a)
#define RAW_AKEY_B (RAW_AKEY_SHFT | RAW_AKEY_b)
#define RAW_AKEY_C (RAW_AKEY_SHFT | RAW_AKEY_c)
#define RAW_AKEY_D (RAW_AKEY_SHFT | RAW_AKEY_d)
#define RAW_AKEY_E (RAW_AKEY_SHFT | RAW_AKEY_e)
#define RAW_AKEY_F (RAW_AKEY_SHFT | RAW_AKEY_f)
#define RAW_AKEY_G (RAW_AKEY_SHFT | RAW_AKEY_g)
#define RAW_AKEY_H (RAW_AKEY_SHFT | RAW_AKEY_h)
#define RAW_AKEY_I (RAW_AKEY_SHFT | RAW_AKEY_i)
#define RAW_AKEY_J (RAW_AKEY_SHFT | RAW_AKEY_j)
#define RAW_AKEY_K (RAW_AKEY_SHFT | RAW_AKEY_k)
#define RAW_AKEY_L (RAW_AKEY_SHFT | RAW_AKEY_l)
#define RAW_AKEY_M (RAW_AKEY_SHFT | RAW_AKEY_m)
#define RAW_AKEY_N (RAW_AKEY_SHFT | RAW_AKEY_n)
#define RAW_AKEY_O (RAW_AKEY_SHFT | RAW_AKEY_o)
#define RAW_AKEY_P (RAW_AKEY_SHFT | RAW_AKEY_p)
#define RAW_AKEY_Q (RAW_AKEY_SHFT | RAW_AKEY_q)
#define RAW_AKEY_R (RAW_AKEY_SHFT | RAW_AKEY_r)
#define RAW_AKEY_S (RAW_AKEY_SHFT | RAW_AKEY_s)
#define RAW_AKEY_T (RAW_AKEY_SHFT | RAW_AKEY_t)
#define RAW_AKEY_U (RAW_AKEY_SHFT | RAW_AKEY_u)
#define RAW_AKEY_V (RAW_AKEY_SHFT | RAW_AKEY_v)
#define RAW_AKEY_W (RAW_AKEY_SHFT | RAW_AKEY_w)
#define RAW_AKEY_X (RAW_AKEY_SHFT | RAW_AKEY_x)
#define RAW_AKEY_Y (RAW_AKEY_SHFT | RAW_AKEY_y)
#define RAW_AKEY_Z (RAW_AKEY_SHFT | RAW_AKEY_z)

#define RAW_AKEY_CTRL_a (RAW_AKEY_CTRL | RAW_AKEY_a)
#define RAW_AKEY_CTRL_b (RAW_AKEY_CTRL | RAW_AKEY_b)
#define RAW_AKEY_CTRL_c (RAW_AKEY_CTRL | RAW_AKEY_c)
#define RAW_AKEY_CTRL_d (RAW_AKEY_CTRL | RAW_AKEY_d)
#define RAW_AKEY_CTRL_e (RAW_AKEY_CTRL | RAW_AKEY_e)
#define RAW_AKEY_CTRL_f (RAW_AKEY_CTRL | RAW_AKEY_f)
#define RAW_AKEY_CTRL_g (RAW_AKEY_CTRL | RAW_AKEY_g)
#define RAW_AKEY_CTRL_h (RAW_AKEY_CTRL | RAW_AKEY_h)
#define RAW_AKEY_CTRL_i (RAW_AKEY_CTRL | RAW_AKEY_i)
#define RAW_AKEY_CTRL_j (RAW_AKEY_CTRL | RAW_AKEY_j)
#define RAW_AKEY_CTRL_k (RAW_AKEY_CTRL | RAW_AKEY_k)
#define RAW_AKEY_CTRL_l (RAW_AKEY_CTRL | RAW_AKEY_l)
#define RAW_AKEY_CTRL_m (RAW_AKEY_CTRL | RAW_AKEY_m)
#define RAW_AKEY_CTRL_n (RAW_AKEY_CTRL | RAW_AKEY_n)
#define RAW_AKEY_CTRL_o (RAW_AKEY_CTRL | RAW_AKEY_o)
#define RAW_AKEY_CTRL_p (RAW_AKEY_CTRL | RAW_AKEY_p)
#define RAW_AKEY_CTRL_q (RAW_AKEY_CTRL | RAW_AKEY_q)
#define RAW_AKEY_CTRL_r (RAW_AKEY_CTRL | RAW_AKEY_r)
#define RAW_AKEY_CTRL_s (RAW_AKEY_CTRL | RAW_AKEY_s)
#define RAW_AKEY_CTRL_t (RAW_AKEY_CTRL | RAW_AKEY_t)
#define RAW_AKEY_CTRL_u (RAW_AKEY_CTRL | RAW_AKEY_u)
#define RAW_AKEY_CTRL_v (RAW_AKEY_CTRL | RAW_AKEY_v)
#define RAW_AKEY_CTRL_w (RAW_AKEY_CTRL | RAW_AKEY_w)
#define RAW_AKEY_CTRL_x (RAW_AKEY_CTRL | RAW_AKEY_x)
#define RAW_AKEY_CTRL_y (RAW_AKEY_CTRL | RAW_AKEY_y)
#define RAW_AKEY_CTRL_z (RAW_AKEY_CTRL | RAW_AKEY_z)

#define RAW_AKEY_CTRL_A (RAW_AKEY_CTRL | RAW_AKEY_A)
#define RAW_AKEY_CTRL_B (RAW_AKEY_CTRL | RAW_AKEY_B)
#define RAW_AKEY_CTRL_C (RAW_AKEY_CTRL | RAW_AKEY_C)
#define RAW_AKEY_CTRL_D (RAW_AKEY_CTRL | RAW_AKEY_D)
#define RAW_AKEY_CTRL_E (RAW_AKEY_CTRL | RAW_AKEY_E)
#define RAW_AKEY_CTRL_F (RAW_AKEY_CTRL | RAW_AKEY_F)
#define RAW_AKEY_CTRL_G (RAW_AKEY_CTRL | RAW_AKEY_G)
#define RAW_AKEY_CTRL_H (RAW_AKEY_CTRL | RAW_AKEY_H)
#define RAW_AKEY_CTRL_I (RAW_AKEY_CTRL | RAW_AKEY_I)
#define RAW_AKEY_CTRL_J (RAW_AKEY_CTRL | RAW_AKEY_J)
#define RAW_AKEY_CTRL_K (RAW_AKEY_CTRL | RAW_AKEY_K)
#define RAW_AKEY_CTRL_L (RAW_AKEY_CTRL | RAW_AKEY_L)
#define RAW_AKEY_CTRL_M (RAW_AKEY_CTRL | RAW_AKEY_M)
#define RAW_AKEY_CTRL_N (RAW_AKEY_CTRL | RAW_AKEY_N)
#define RAW_AKEY_CTRL_O (RAW_AKEY_CTRL | RAW_AKEY_O)
#define RAW_AKEY_CTRL_P (RAW_AKEY_CTRL | RAW_AKEY_P)
#define RAW_AKEY_CTRL_Q (RAW_AKEY_CTRL | RAW_AKEY_Q)
#define RAW_AKEY_CTRL_R (RAW_AKEY_CTRL | RAW_AKEY_R)
#define RAW_AKEY_CTRL_S (RAW_AKEY_CTRL | RAW_AKEY_S)
#define RAW_AKEY_CTRL_T (RAW_AKEY_CTRL | RAW_AKEY_T)
#define RAW_AKEY_CTRL_U (RAW_AKEY_CTRL | RAW_AKEY_U)
#define RAW_AKEY_CTRL_V (RAW_AKEY_CTRL | RAW_AKEY_V)
#define RAW_AKEY_CTRL_W (RAW_AKEY_CTRL | RAW_AKEY_W)
#define RAW_AKEY_CTRL_X (RAW_AKEY_CTRL | RAW_AKEY_X)
#define RAW_AKEY_CTRL_Y (RAW_AKEY_CTRL | RAW_AKEY_Y)
#define RAW_AKEY_CTRL_Z (RAW_AKEY_CTRL | RAW_AKEY_Z)

#define RAW_AKEY_HELP 0x11
#define RAW_AKEY_DOWN 0x8f
#define RAW_AKEY_LEFT 0x86
#define RAW_AKEY_RIGHT 0x87
#define RAW_AKEY_UP 0x8e
#define RAW_AKEY_BACKSPACE 0x34
#define RAW_AKEY_DELETE_CHAR 0xb4
#define RAW_AKEY_DELETE_LINE 0x74
#define RAW_AKEY_INSERT_CHAR 0xb7
#define RAW_AKEY_INSERT_LINE 0x77
#define RAW_AKEY_ESCAPE 0x1c
#define RAW_AKEY_ATARI 0x27
#define RAW_AKEY_CAPSLOCK 0x7c
#define RAW_AKEY_CAPSTOGGLE 0x3c
#define RAW_AKEY_TAB 0x2c
#define RAW_AKEY_SETTAB 0x6c
#define RAW_AKEY_CLRTAB 0xac
#define RAW_AKEY_RETURN 0x0c
#define RAW_AKEY_SPACE 0x21
#define RAW_AKEY_EXCLAMATION 0x5f
#define RAW_AKEY_DBLQUOTE 0x5e
#define RAW_AKEY_HASH 0x5a
#define RAW_AKEY_DOLLAR 0x58
#define RAW_AKEY_PERCENT 0x5d
#define RAW_AKEY_AMPERSAND 0x5b
#define RAW_AKEY_QUOTE 0x73
#define RAW_AKEY_AT 0x75
#define RAW_AKEY_PARENLEFT 0x70
#define RAW_AKEY_PARENRIGHT 0x72
#define RAW_AKEY_LESS 0x36
#define RAW_AKEY_GREATER 0x37
#define RAW_AKEY_EQUAL 0x0f
#define RAW_AKEY_QUESTION 0x66
#define RAW_AKEY_MINUS 0x0e
#define RAW_AKEY_PLUS 0x06
#define RAW_AKEY_ASTERISK 0x07
#define RAW_AKEY_SLASH 0x26
#define RAW_AKEY_COLON 0x42
#define RAW_AKEY_SEMICOLON 0x02
#define RAW_AKEY_COMMA 0x20
#define RAW_AKEY_FULLSTOP 0x22
#define RAW_AKEY_UNDERSCORE 0x4e
#define RAW_AKEY_BRACKETLEFT 0x60
#define RAW_AKEY_BRACKETRIGHT 0x62
#define RAW_AKEY_CIRCUMFLEX 0x47
#define RAW_AKEY_BACKSLASH 0x46
#define RAW_AKEY_BAR 0x4f
#define RAW_AKEY_CLEAR (RAW_AKEY_SHFT | RAW_AKEY_LESS)
#define RAW_AKEY_CARET (RAW_AKEY_SHFT | RAW_AKEY_ASTERISK)
#define RAW_AKEY_F1 0x03
#define RAW_AKEY_F2 0x04
#define RAW_AKEY_F3	0x13
#define RAW_AKEY_F4 0x14

#endif
