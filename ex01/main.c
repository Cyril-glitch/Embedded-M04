/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyril <cyril@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:52:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/16 15:15:47 by cyril            ###   ########.fr       */
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
    /* On set la frequence du timer( ici prescale 256 -> (62500hz)) */                       // sa vitesse (62500 incrementation par sec)
    SET(TCCR1B, CS12);                                  

    /* On determine son action sur sa sortie (ici set a bottom clear a compare match) */     // son action (faire clignoter la led)
    SET(TCCR1A, COM1A1); 

    /* On determine le motif de ses periode (ici pwm 8 bit 0 a 255 soit (244hz) 4ms */       // sa boucle (toute les 4ms)
    SET(TCCR1A, WGM10);
    SET(TCCR1B, WGM12);
    
    /* Compare match */                                                                     // la duree de son action (plus elle est longue plus la lumiere est intense); 
    OCR1A = 0 ;
}

/**
 *@brief: On veut que l'interrution se leve toutes les 0.6 sec soit 6000ms et augmente le rapport cyclique de 1 %
 */
void init_timer0()
{
    /* On set la frequence du timer( ici prescale 256 -> (62500hz))(0.1ms) */                       // sa vitesse
    SET(TCCR0B, CS12);

    /* On determine le mode d'interuption (ici interuption a compare match A)*/                     // son action
    SET(TIMSK0, OCIE0A);

    /* On configure ses periodes (moment et interval d'action) (ici de 0 a compare match)(CTC mode)*/   //sa boucle
    SET(TCCR0A, WGM01);

    /* Compare match */
    OCR1A = 121 ;
}


void TIMER0_COMPA_vect(void) __attribute__ ((signal, used));

void TIMER0_COMPA_vect(void)
{ 
    OCR1A++ ;
}

int main()
{
    /* GPIO INIT*/
    SET(DDRB, DDB1);

    /* INTERUPT INIT */
    SET(SREG, SREG_I);

    init_timer1();
    while (1);
}