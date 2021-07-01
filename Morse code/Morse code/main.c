/*
 * Morse code.c
 *
 * Created: 10-3-2021 15:14:11
 * Authors : Pascal de Bruijn en Rümeysa Yavuz
 */ 
#define F_CPU 8E6

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

typedef struct node {
	char* data;
	struct node* next;
}node;

//node* createLinkedList(int n);
node* createLinkedList(node* head, char data);
void displayList(node* head);
void morseCode(void);

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

node* createLinkedList(node * head, char data) {
	//int i = 0;

	//node* head = NULL;
	node* temp = NULL;
	node* p = NULL;

	temp = (node*)malloc(sizeof(node));
	temp->next = NULL;
		
	temp->data = &data;
		
	if (head == NULL)
	{
		head = temp;
	}
	else
	{
		p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = temp;
	}

	return head;
}

void displayList(node* head) {
	node* p = head;
	
	while(p != NULL) {
		printf("\t%d", p->data);
		p = p->next;
	}
}
void morseCode(void) {
		char* alphabetMorse[26] =
		{
			".-",		//A
			"-...",		//B
			"-.-.",		//C
			"-..",		//D
			".",		//E
			"..-.",		//F
			"--.",		//G
			"....",		//H
			"..",		//I
			".---",		//J
			"-.-",		//K
			".-..",		//L
			"--",		//M
			"-.",		//N
			"---",		//O
			".--.",		//P
			"--.-",		//Q
			".-.",		//R
			"...",		//S
			"-",		//T
			"..-",		//U
			"...-",		//V
			".--",		//W
			"-..-",		//X
			"-.--",		//Y
			"--.."		//Z
		};

		/*for (int i = 0; i < 26; i++) {
			printf("\n[%2d]: %s", i, alphabetMorse[i]);
		}*/
}


int main(void)
{	
	DDRB = 0x00;
	DDRD = 0xFF;
	
	lcd_init();
	
	unsigned int count = 0;
	bool buttonWasPressed = false;
	TCCR1A = 0x00; //0b00000000;
	TCCR1B = 0x05; //0b00000101; //Prescaler van 1024 _ 1 tic is 8.388.608 TIMER 1 (MET DEZE ZOU HET LUKKEN)
	
	char buffer[17];

    /* Replace with your application code */
    while (1)
    {
		//Als de oude waarde niet ingedrukt is en de nieuwe is wel ingedrukt ga de if binnen. 
		bool buttonPressed = PINB & 0x01;
		
		if (buttonPressed && !buttonWasPressed) {
			TCNT1 = 0;
		}
		else if (!buttonPressed && buttonWasPressed) {
			lcd_clear_display();
			
			count = TCNT1;
			sprintf(buffer, "%u", count); //sprintf schrijft de count naar de buffer //Omrekenen naar milliseconden
			lcd_display_text(buffer);
			
			//1 tic is 128 ms 0,125 * 1024 --> 128 * 256 = 32.768 ms TIMER 2
			
			//Tussen de 0 en 65535
			if (count >= 500 && count < 3000) {
				createLinkedList()
			}
			
			if (count >= 3000) {
			}
		}
		buttonWasPressed = buttonPressed;
    }
	
}

