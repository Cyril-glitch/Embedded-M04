/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:52:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/15 18:06:37 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
PD2 -> INT0 -> PCINT18
INT0 = External Interrupt
PINT = Pin Change interrupt
EICRA = External Interupt Control Register A
EIMSK = External Interrupt Mask Register
EIFR – External Interrupt Flag Register
*/


void INT0_vect(void) __attribute__ ((signal, used));

void INT0_vect(void)
{ 
    TOGGLE(PORTB, PB0);
    CLEAR(EIMSK, INT0);         // disable interruptions
}

int main()
{
    /*GPIO INIT*/
    SET(DDRB, DDB0);            //ddr led d1
    CLEAR(DDRD, DD2);           //ddr sw1
    SET(PORTD, PD2);            // resistor sw1
    
    /*INTERRUTPTIONS INIT*/

    SET(SREG, SREG_I);          // enable global interuptions
    SET(EICRA, ISC01);          // falling edge interruptions
    SET(EIMSK, INT0);           // enable external interrupts 0

    while (1)
    {
        if (!(is_set(EIMSK, INT0)))
        {
            _delay_ms(200);
            EIFR = (1U << INT0);
            SET(EIMSK, INT0);
        }
    }
}