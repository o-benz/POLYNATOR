#include <avr/io.h> 
#include <stdarg.h>

class UART
{
public:
    UART();
    ~UART(){};
    void changeSize(uint8_t size);
    void changeStopBits(uint8_t stopBits);
    void changeParity(bool parity);
    void changeIsOdd(bool isOdd);
    static void sendByte(uint8_t byte);
    static void sendData(uint8_t data[], uint8_t length);
    static void sendNumber(uint8_t number);
    static void sendNumber(uint16_t number);
    static void printf(const uint8_t data[], uint8_t length, ...);
    static unsigned char receiveUsart();

private:
    uint8_t _size = 8;
    uint8_t _stopBits = 1;
    bool _parity = false;
    bool _isOdd = true;
};