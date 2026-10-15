/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 11:21:28 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/15 13:30:39 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"


/*------------------------------------------------------------------------------*/

//BIT STATUS

int is_set(uint8_t reg, int pos)
{
    return (reg & (1 << pos));
}

int is_press(uint8_t sw, int pos)
{
    return !(sw & (1 << pos));
}

int is_release(uint8_t sw, int pos)
{
    return (sw & (1 << pos));
}

void ignite(volatile uint8_t *led, int pos)
{
    volatile uint8_t* ddr = led - 1;
    SET(*led, pos);
    SET(*ddr, pos);
}

void turnoff(volatile uint8_t *led, int pos)
{
    volatile uint8_t* ddr = led - 1;
    CLEAR(*led, pos);
    CLEAR(*ddr, pos);
}

/*------------------------------------------------------------------------------*/

//UART

void uart_init(void)
{
    /*Set baudrate prescaler (cf p.204)*/
    UBRR0H = (uint8_t)(MYUBRR >> 8);
    UBRR0L = (uint8_t)(MYUBRR);

    /* Enable double speed mode (cf p.199) */
    SET(UCSR0A, U2X0);

    /* enable transmitter (cf p.202)*/
    SET(UCSR0B,TXEN0);                       

    /* enable receiver (cf p.202)*/
    SET(UCSR0B,RXEN0);                       

    /* set the size of the transmited data to 8 (cf p.202)*/
    SET(UCSR0C,UCSZ01);  
    SET(UCSR0C,UCSZ00);  

    /* disable parity (cf .203) */
    CLEAR(UCSR0C,UPM01);
    CLEAR(UCSR0C,UPM00);
    
    /* set the number of stop bits to one (cf p.203)*/
    CLEAR(UCSR0C,USBS0);
}

void uart_tx(char c)
{
    /* wait for UDRN (transmiter buffer) to be empty (cf p.200)*/
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

char uart_rx(void)
{
    /* wait for the UDR0 (buffer) to be full(cf p.200)*/
    while (!(UCSR0A & (1 << RXC0)));

    /* return received data from buffer */
    return UDR0;
}

void uart_printstr(const char* str)
{
    while(*str)
        uart_tx(*(str++));
}


/*------------------------------------------------------------------------------*/

//INTERUPTIONS  

void watchdog_2s(void)
{
    /* enable watchdog (cf p.64) */
    WDTCSR |= (1 << WDCE) | (1 << WDE);

    /* set the timeout  (cf p.64)*/
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0);
}


/*------------------------------------------------------------------------------*/

//RGB
void init_rgb()
{
    /* set data direction on output mode */
    DDRD |= (1U << DD5) | (1U << DD6) | (1U << DD3);

    /* set the prescaler to 256(62500hz)(cf p.116)*/
    SET(TCCR0B, CS02);                                 //timer 0
    TCCR2B |= (1U << CS22) | (1U << CS21);            //timer 2

    /* compare output mode (how the led react(non inverting))(cf p.113) */
    SET(TCCR0A, COM0B1);                              //red
    SET(TCCR0A, COM0A1);                              //green
    SET(TCCR2A, COM2B1);                              //blue 

    /* set fast PWM 8bits (counter count 0 to 255(244 hz))*/
    TCCR0A |= (1U << WGM01) | (1U << WGM00);            //timer 0
    TCCR2A |= (1U << WGM21) | (1U << WGM20);            //timer 2
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    /* more the outcompare is hight more intense the color is*/
    OCR0B = r;
    OCR0A = g;
    OCR2B = b;
}

void wheel(uint8_t pos)
{
    pos = 255 - pos;
    if (pos < 85)
    {
        set_rgb(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170)
    {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else
    {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}


/*------------------------------------------------------------------------------*/