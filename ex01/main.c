/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:52:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/17 14:41:15 by cyril            ###   ########.fr       */
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
    /* On set la frequence du timer( ici prescale 256 -> (62500hz))*/                                                           // sa vitesse 
    SET(TCCR1B, CS12);                                  

    /* On determine son action sur sa sortie (ici set a bottom clear a compare match) */                                         // son action
    SET(TCCR1A, COM1A1); 

    /* On determine la frequence de ses periode (ici pwm 8 bit 0 a 255 soit (244hz)(4ms)) */                                    // sa recurrence
    SET(TCCR1A, WGM10);
    SET(TCCR1B, WGM12);
    
    /* On determine le rapport cyclique ( selon le Compare match -> ici duree d'allumage de la led par periode) */              // la duree de son action
    OCR1A = 0;
}

/**
 *@brief: duty cycle -> 0 -> 255 -> 0 soit 512 interuption necessaires par secondes
 */
void init_timer0()
{
    /* On set la frequence du timer( ici prescale 256 -> (62500hz))*/                               // sa vitesse
    SET(TCCR0B, CS12);

    /* On determine le mode d'interuption (ici interuption a compare match A)*/                     // son action
    SET(TIMSK0, OCIE0A);

    /* On set la frequence de ces periodes (ici de 0 a compare match)(CTC mode)*/                   // sa recurrence
    SET(TCCR0A, WGM01);
    OCR0A = 121 ;
}


void TIMER0_COMPA_vect(void) __attribute__ ((signal, used));

void TIMER0_COMPA_vect(void)
{  
    static volatile uint8_t up = 1; 

        if (up)
            OCR1A++;
        else
            OCR1A--;
        if (OCR1A == 255 || OCR1A == 0)
            TOGGLE(up, 0);
}

int main()
{
    /* GPIO INIT*/
    SET(DDRB, DDB1);

    /* */
    SET(SREG, SREG_I);

    init_timer0();
    init_timer1();
    while (1);
}