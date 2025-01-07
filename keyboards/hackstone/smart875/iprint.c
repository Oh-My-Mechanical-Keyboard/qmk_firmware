// Copyright 2024 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef GPIO_UART_ENABLE

#    include "quantum.h"
#    include <stdarg.h>

#    define DEALY_NS_250()    wait_cpuclock(CPU_CLOCK / 1000000L / 4)

#    define GPIO_UART_DELAY() delay(26) // CPU_CLOCK Set to 72MHz BOUND 115200. In other cases, please modify it yourself.

#    define MAX_FILLER        11

#    ifndef GPIO_UART_TX_PIN
#        define GPIO_UART_TX_PIN A13 // swdio
#    endif

static void delay(uint32_t times) {
    while (times--) {
        DEALY_NS_250();
    }
}

void iprint_init(void) {
    setPinOutput(GPIO_UART_TX_PIN);
    writePinHigh(GPIO_UART_TX_PIN);
}

void gpiouart_send(uint8_t data) {
    chSysLock();

    writePin(GPIO_UART_TX_PIN, 0);
    GPIO_UART_DELAY();

    for (uint8_t i = 0; i < 8; i++) {
        if ((data >> i) & 0x01) {
            writePin(GPIO_UART_TX_PIN, 1);
            GPIO_UART_DELAY();
        } else {
            writePin(GPIO_UART_TX_PIN, 0);
            GPIO_UART_DELAY();
        }
    }

    writePin(GPIO_UART_TX_PIN, 1);
    GPIO_UART_DELAY();

    chSysUnlock();
}

static char *long_to_string_with_divisor(char *p,
                                         long num,
                                         unsigned radix,
                                         long divisor) {
    int i;
    char *q;
    long l, ll;

    l = num;
    if (divisor == 0) {
        ll = num;
    } else {
        ll = divisor;
    }

    q = p + MAX_FILLER;
    do {
        i = (int)(l % radix);
        i += '0';
        if (i > '9') {
            i += 'A' - '0' - 10;
        }
        *--q = i;
        l /= radix;
    } while ((ll /= radix) != 0);

    i = (int)(p + MAX_FILLER - q);
    do {
        *p++ = *q++;
    } while (--i);

    return p;
}

static char *ch_ltoa(char *p, long num, unsigned radix) {
    return long_to_string_with_divisor(p, num, radix, 0);
}

static int ivprintf(const char *fmt, va_list ap) {
    char *p, *s, c, filler;
    int i, precision, width;
    int n = 0;
    bool is_long, left_align, do_sign;
    long l;
#    if CHPRINTF_USE_FLOAT
    float f;
    char tmpbuf[2 * MAX_FILLER + 1];
#    else
    char tmpbuf[MAX_FILLER + 1];
#    endif

    while (true) {
        c = *fmt++;
        if (c == 0) {
            return n;
        }

        if (c != '%') {
            gpiouart_send((uint8_t)c);
            n++;
            continue;
        }

        p = tmpbuf;
        s = tmpbuf;

        /* Alignment mode.*/
        left_align = false;
        if (*fmt == '-') {
            fmt++;
            left_align = true;
        }

        /* Sign mode.*/
        do_sign = false;
        if (*fmt == '+') {
            fmt++;
            do_sign = true;
        }

        /* Filler mode.*/
        filler = ' ';
        if (*fmt == '0') {
            fmt++;
            filler = '0';
        }

        /* Width modifier.*/
        if (*fmt == '*') {
            width = va_arg(ap, int);
            ++fmt;
            c = *fmt++;
        } else {
            width = 0;
            while (true) {
                c = *fmt++;
                if (c == 0) {
                    return n;
                }
                if (c >= '0' && c <= '9') {
                    c -= '0';
                    width = width * 10 + c;
                } else {
                    break;
                }
            }
        }

        /* Precision modifier.*/
        precision = 0;
        if (c == '.') {
            c = *fmt++;
            if (c == 0) {
                return n;
            }
            if (c == '*') {
                precision = va_arg(ap, int);
                c         = *fmt++;
            } else {
                while (c >= '0' && c <= '9') {
                    c -= '0';
                    precision = precision * 10 + c;
                    c         = *fmt++;
                    if (c == 0) {
                        return n;
                    }
                }
            }
        }

        /* Long modifier.*/
        if (c == 'l' || c == 'L') {
            is_long = true;
            c       = *fmt++;
            if (c == 0) {
                return n;
            }
        } else {
            is_long = (c >= 'A') && (c <= 'Z');
        }

        /* Command decoding.*/
        switch (c) {
            case 'c':
                filler = ' ';
                *p++   = va_arg(ap, int);
                break;
            case 's':
                filler = ' ';
                if ((s = va_arg(ap, char *)) == 0) {
                    s = "(null)";
                }
                if (precision == 0) {
                    precision = 32767;
                }
                for (p = s; *p && (--precision >= 0); p++)
                    ;
                break;
            case 'D':
            case 'd':
            case 'I':
            case 'i':
                if (is_long) {
                    l = va_arg(ap, long);
                } else {
                    l = va_arg(ap, int);
                }
                if (l < 0) {
                    *p++ = '-';
                    l    = -l;
                } else if (do_sign) {
                    *p++ = '+';
                }
                p = ch_ltoa(p, l, 10);
                break;
#    if CHPRINTF_USE_FLOAT
            case 'f':
                f = (float)va_arg(ap, double);
                if (f < 0) {
                    *p++ = '-';
                    f    = -f;
                } else {
                    if (do_sign) {
                        *p++ = '+';
                    }
                }
                p = ftoa(p, f, precision);
                break;
#    endif
            case 'X':
            case 'x':
            case 'P':
            case 'p':
                c = 16;
                goto unsigned_common;
            case 'U':
            case 'u':
                c = 10;
                goto unsigned_common;
            case 'O':
            case 'o':
                c = 8;
            unsigned_common:
                if (is_long) {
                    l = va_arg(ap, unsigned long);
                } else {
                    l = va_arg(ap, unsigned int);
                }
                p = ch_ltoa(p, l, c);
                break;
            default:
                *p++ = c;
                break;
        }
        i = (int)(p - s);
        if ((width -= i) < 0) {
            width = 0;
        }
        if (left_align == false) {
            width = -width;
        }
        if (width < 0) {
            if ((*s == '-' || *s == '+') && filler == '0') {
                gpiouart_send((uint8_t)*s++);
                n++;
                i--;
            }
            do {
                gpiouart_send((uint8_t)filler);
                n++;
            } while (++width != 0);
        }
        while (--i >= 0) {
            gpiouart_send((uint8_t)*s++);
            n++;
        }

        while (width) {
            gpiouart_send((uint8_t)filler);
            n++;
            width--;
        }
    }
}

int iprintf(const char *fmt, ...) {
    va_list ap;
    int formatted_bytes;

    va_start(ap, fmt);
    formatted_bytes = ivprintf(fmt, ap);
    va_end(ap);

    return formatted_bytes;
}
#endif
