/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:52:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/15 20:36:58 by cycolonn         ###   ########.fr       */
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

volatile uint8_t duty_cycle = 0;

void init_timer1()
{
    /* set le prescaler a 256 */
    SET(TCCR1B, CS12);                                  

    /* action sur la led en sortie (set on bottom clear on compare match) */
    SET(TCCR1A, COM1A1); 

    /* largeur d'impulsion (0 a 255)(PWM 8bit)*/
    TCCR1A |= (1U << WGM12) | (1U << WGM10);
    
    /* Compare match */
    OCR1A = 0;
}

void init_timer0()
{
    /* set prescaler */
    SET(TCCR0B, CS02);                                  


}


void TIMER0_COMPA_vect(void) __attribute__ ((signal, used));

void TIMER0_COMPA_vect(void)
{ 
    OCR1A += ((255 / 100) * duty_cycle);
}

int main()
{
    /* GPIO INIT*/
    SET(DDRB, DDB1);

    init_timer1();
    while (1);
}

