/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 11:19:44 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/15 13:07:26 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*------------------------------------------------------------------------------*/

//TIMER

//#define F_CPU 16000000
#define PRESCALER 256
#define DUTYCYCLE 10
#define HZ1 ((F_CPU / PRESCALER) - 1)

void watchdog_2s(void);

/*------------------------------------------------------------------------------*/

//UART

#define UART_BAUDRATE 115200UL
#define MYUBRR (((F_CPU / (8UL * UART_BAUDRATE))) - 1)

void uart_init(void);
void uart_tx(char c);
char uart_rx(void);
void uart_printstr(const char* str);

/*------------------------------------------------------------------------------*/

//BITWISE MACRO

#define SET(reg, pos) (reg |= (1U << pos))
#define SETFIELD(reg, len, start) ((reg) |= (((1U << (len)) - 1) << (start)))
#define CLEAR(reg, pos) (reg &= ~(1U << pos))
#define TOGGLE(reg, pos) (reg ^= (1U << pos))


/*------------------------------------------------------------------------------*/

//BIT STATUS

int is_set(uint8_t reg, int pos);

int is_press(uint8_t sw, int pos);

int is_release(uint8_t sw, int pos);

void ignite(volatile uint8_t *led, int pos);

void turnoff(volatile uint8_t *led, int pos);

/*------------------------------------------------------------------------------*/

//RGB

void init_rgb(void);

void set_rgb(uint8_t r, uint8_t g, uint8_t b);

void wheel(uint8_t pos);

/*------------------------------------------------------------------------------*/


#endif
