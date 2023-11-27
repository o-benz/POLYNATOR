#include "uart.h"

UART::UART()
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0B |= (1 << RXEN0)|(1 << TXEN0);    
    UCSR0B &= ~(1 << UCSZ02);
    UCSR0C &= ~(1 << UPM00)|~(1 << UPM01)|~(1 << USBS0);
    UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00);

    if (_parity)
    {
        UCSR0C |= (1 << UPM01);
        if (_isOdd)
        {
            UCSR0C |= (1 << UPM00);
        }
    }
    if (_stopBits == 2)
    {
        UCSR0C |= (1 << USBS0);
    }
;    switch(_size)
    {
        case 5:
            UCSR0C &= ~(1 << UCSZ00)|~(1 << UCSZ01);
            break;
        case 6:
            UCSR0C |= (1 << UCSZ00);
            UCSR0C &= ~(1 << UCSZ01);
            break;
        case 7:
            UCSR0C |= (1 << UCSZ01);
            UCSR0C &= ~(1 << UCSZ00);
            break;
        case 8:
            UCSR0C |= (1 << UCSZ00)|(1 << UCSZ01);
            break;
        case 9:
            UCSR0C |= (1 << UCSZ00)|(1 << UCSZ01);
            UCSR0B |= (1 << UCSZ02);
            break;
        default:
            UCSR0C |= (1 << UCSZ00)|(1 << UCSZ01);
            break;
    }
}

void UART::sendByte(uint8_t byte)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = byte;
}

void UART::sendData(uint8_t data[], uint8_t length)
{
    uint8_t i;
    for (i = 0; i < length; i++) {
        sendByte(data[i]);
    }
}

void UART::sendNumber(uint8_t number)
{
    uint8_t hundreds = '0' + number / 100;
    uint8_t tens = '0' + number % 100 / 10;
    uint8_t ones = '0' + number % 10;

    if (hundreds != '0') {
        sendByte(hundreds);
    }
    if (hundreds != '0' || tens != '0') {
        sendByte(tens);
    }
    sendByte(ones);
}

void UART::sendNumber(uint16_t number)
{
    const int8_t MAX_POWER_10 = 4;
    bool firstDigitTransmitted = false;

    for (int8_t i = MAX_POWER_10; i >= 0; i--) {
        uint16_t n = number;
        uint16_t digitPosition = 1;
        for (int j = 1; j <= i; j++) {
            digitPosition *= 10;
        }
        if (i < 4) {
            n %= (10 * digitPosition);
        }
        uint8_t digit = n / digitPosition;
        if (digit != 0 || firstDigitTransmitted) {
            firstDigitTransmitted = true;
            sendByte('0' + digit);
        }
    }

    if (!firstDigitTransmitted) {
        sendByte('0');
    }
}

void UART::printf(const uint8_t data[], uint8_t length, ...)
{
    bool percentFound = false;
    va_list values;
    va_start(values, length);

    for (uint8_t i = 0; i < length; i++) {
        if (percentFound) {
            if (data[i] == 'd') {
                sendNumber((uint16_t)va_arg(values, int));
            }
            else {
                sendByte('%');
                sendByte('d');
            }
            percentFound = false;
        }
        else if (data[i] == '%' && i < length - 1) {
            percentFound = true;
        }
        else {
            sendByte(data[i]);
        }
    }
    va_end(values);
    sendByte('\n');
}


unsigned char UART::receiveUsart() 
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void UART::changeSize(uint8_t size)
{
    _size = size;
}

void UART::changeStopBits(uint8_t stopBits)
{
    _stopBits = stopBits;
}

void UART::changeParity(bool parity)
{
    _parity = parity;
}

void UART::changeIsOdd(bool isOdd)
{
    _isOdd = isOdd;
}