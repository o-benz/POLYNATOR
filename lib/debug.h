#ifdef DEBUG
#include "uart.h"
# define DEBUG_PRINT(x) {\
    UART::sendData((uint8_t*)x, sizeof(x));\
    UART::sendByte('\n');\
}
# define DEBUG_PRINTF(x, ...) {\
    UART::printf((uint8_t*)x, sizeof(x), ##__VA_ARGS__);\
}
#else
# define DEBUG_PRINT(x) do {} while (0) 
# define DEBUG_PRINTF(x, ...) do {} while (0)
#endif