7700 #pragma once
7701 
7702 // PC keyboard interface constants
7703 
7704 #define KBSTATP         0x64    // kbd controller status port(I)
7705 #define KBS_DIB         0x01    // kbd data in buffer
7706 #define KBDATAP         0x60    // kbd data port(I)
7707 
7708 #define NO              0
7709 
7710 #define SHIFT           (1<<0)
7711 #define CTL             (1<<1)
7712 #define ALT             (1<<2)
7713 
7714 #define CAPSLOCK        (1<<3)
7715 #define NUMLOCK         (1<<4)
7716 #define SCROLLLOCK      (1<<5)
7717 
7718 #define E0ESC           (1<<6)
7719 
7720 // Special keycodes
7721 #define KEY_HOME        0xE0
7722 #define KEY_END         0xE1
7723 #define KEY_UP          0xE2
7724 #define KEY_DN          0xE3
7725 #define KEY_LF          0xE4
7726 #define KEY_RT          0xE5
7727 #define KEY_PGUP        0xE6
7728 #define KEY_PGDN        0xE7
7729 #define KEY_INS         0xE8
7730 #define KEY_DEL         0xE9
7731 
7732 // C('A') == Control-A
7733 #define C(x) (x - '@')
7734 
7735 static uchar shiftcode[256] =
7736 {
7737   [0x1D] CTL,
7738   [0x2A] SHIFT,
7739   [0x36] SHIFT,
7740   [0x38] ALT,
7741   [0x9D] CTL,
7742   [0xB8] ALT
7743 };
7744 
7745 
7746 
7747 
7748 
7749 
7750 static uchar togglecode[256] =
7751 {
7752   [0x3A] CAPSLOCK,
7753   [0x45] NUMLOCK,
7754   [0x46] SCROLLLOCK
7755 };
7756 
7757 static uchar normalmap[256] =
7758 {
7759   NO,   0x1B, '1',  '2',  '3',  '4',  '5',  '6',  // 0x00
7760   '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
7761   'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  // 0x10
7762   'o',  'p',  '[',  ']',  '\n', NO,   'a',  's',
7763   'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  // 0x20
7764   '\'', '`',  NO,   '\\', 'z',  'x',  'c',  'v',
7765   'b',  'n',  'm',  ',',  '.',  '/',  NO,   '*',  // 0x30
7766   NO,   ' ',  NO,   NO,   NO,   NO,   NO,   NO,
7767   NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',  // 0x40
7768   '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
7769   '2',  '3',  '0',  '.',  NO,   NO,   NO,   NO,   // 0x50
7770   [0x9C] '\n',      // KP_Enter
7771   [0xB5] '/',       // KP_Div
7772   [0xC8] KEY_UP,    [0xD0] KEY_DN,
7773   [0xC9] KEY_PGUP,  [0xD1] KEY_PGDN,
7774   [0xCB] KEY_LF,    [0xCD] KEY_RT,
7775   [0x97] KEY_HOME,  [0xCF] KEY_END,
7776   [0xD2] KEY_INS,   [0xD3] KEY_DEL
7777 };
7778 
7779 static uchar shiftmap[256] =
7780 {
7781   NO,   033,  '!',  '@',  '#',  '$',  '%',  '^',  // 0x00
7782   '&',  '*',  '(',  ')',  '_',  '+',  '\b', '\t',
7783   'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',  // 0x10
7784   'O',  'P',  '{',  '}',  '\n', NO,   'A',  'S',
7785   'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',  // 0x20
7786   '"',  '~',  NO,   '|',  'Z',  'X',  'C',  'V',
7787   'B',  'N',  'M',  '<',  '>',  '?',  NO,   '*',  // 0x30
7788   NO,   ' ',  NO,   NO,   NO,   NO,   NO,   NO,
7789   NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',  // 0x40
7790   '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
7791   '2',  '3',  '0',  '.',  NO,   NO,   NO,   NO,   // 0x50
7792   [0x9C] '\n',      // KP_Enter
7793   [0xB5] '/',       // KP_Div
7794   [0xC8] KEY_UP,    [0xD0] KEY_DN,
7795   [0xC9] KEY_PGUP,  [0xD1] KEY_PGDN,
7796   [0xCB] KEY_LF,    [0xCD] KEY_RT,
7797   [0x97] KEY_HOME,  [0xCF] KEY_END,
7798   [0xD2] KEY_INS,   [0xD3] KEY_DEL
7799 };
7800 static uchar ctlmap[256] =
7801 {
7802   NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO,
7803   NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO,
7804   C('Q'),  C('W'),  C('E'),  C('R'),  C('T'),  C('Y'),  C('U'),  C('I'),
7805   C('O'),  C('P'),  NO,      NO,      '\r',    NO,      C('A'),  C('S'),
7806   C('D'),  C('F'),  C('G'),  C('H'),  C('J'),  C('K'),  C('L'),  NO,
7807   NO,      NO,      NO,      C('\\'), C('Z'),  C('X'),  C('C'),  C('V'),
7808   C('B'),  C('N'),  C('M'),  NO,      NO,      C('/'),  NO,      NO,
7809   [0x9C] '\r',      // KP_Enter
7810   [0xB5] C('/'),    // KP_Div
7811   [0xC8] KEY_UP,    [0xD0] KEY_DN,
7812   [0xC9] KEY_PGUP,  [0xD1] KEY_PGDN,
7813   [0xCB] KEY_LF,    [0xCD] KEY_RT,
7814   [0x97] KEY_HOME,  [0xCF] KEY_END,
7815   [0xD2] KEY_INS,   [0xD3] KEY_DEL
7816 };
7817 
7818 
7819 
7820 
7821 
7822 
7823 
7824 
7825 
7826 
7827 
7828 
7829 
7830 
7831 
7832 
7833 
7834 
7835 
7836 
7837 
7838 
7839 
7840 
7841 
7842 
7843 
7844 
7845 
7846 
7847 
7848 
7849 
