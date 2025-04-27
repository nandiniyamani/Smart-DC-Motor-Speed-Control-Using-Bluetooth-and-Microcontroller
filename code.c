#include <msp430.h> 
#include "LiquidCrystal_I2C.h"
#define PERIOD 655
// Define PWM period
extern unsigned int entered_value = 0; // External variable to store the input value
from user
extern unsigned int is_complete = 0;
is complete
int main(void)
{
WDTCTL = WDTPW | WDTHOLD;
// External flag to check if the user input
// Stop the watchdog timer
/* Timer B0 configuration for PWM output */
TB0CTL |= TBCLR;
// Clear the timer settings
TB0CTL |= MC UP;
TB0CTL |= TBSSEL ACLK;
TB0CCR0 = PERIOD;
TB0CCR1 = 0;
TB0CCTL0 |= CCIE;
TB0CCTL1 |= CCIE;
TB0CCTL0 &= ~CCIFG;
TB0CCTL1 &= ~CCIFG;
// Set timer to up mode
// Set timer source to ACLK
// Set the maximum count value for PWM
// Start with 0% duty cycle
// Enable interrupt for CCR0
// Enable interrupt for CCR1
// Clear interrupt flags for CCR0
// Clear interrupt flags for CCR1
/* Timer B1 configuration for timeout detection */
TB1CTL |= TBCLR;
// Clear timer B1 settings
TB1CTL |= MC UP;
TB1CTL |= TBSSEL ACLK;
TB1R = 0;
TB1CCR0 = 3500;
/* Bluetooth module setup */
UCA0CTLW0 |= UCSWRST;
UCA0CTLW0 |= UCSSEL ACLK;
UCA0BRW = 3;
UCA0MCTLW = 0x9200;
P1SEL1 &= ~BIT6;
P1SEL0 |= BIT6;
UCA0CTLW0 &= ~UCSWRST;
UCA0IE |= UCRXIE;
I2C_Init(0x27);
/* PWM output pin setup */
P6DIR |= BIT1;
P6OUT &= ~BIT1;
// Set timer to up mode
// Set timer source to ACLK
// Reset the timer value
// Set the value for timeout
// Put UART in software reset
// Set UART clock source to ACLK
// Set baud rate divider
// Set modulation settings
// Configure pin for UART RX
// Release UART from reset
// Enable UART RX interrupt
// Initialize I2C communication
// Set direction to output
// Set output to low
/* Set motor direction */
P2DIR |= BIT1;
P2OUT |= BIT1;
PM5CTL0 &= ~LOCKLPM5;
enable_interrupt();
LCD_Setup();
LCD_SetCursor(0, 0);
// Set direction pin as output
// Set direction to high
// Disable high impedance mode
// Enable global interrupts
// Initialize the LCD
// Position cursor at the beginning
LCD_Write("Motor Speed: "); // Display initial message on LCD
while (1)
{
/* Wait for complete user input */
while(is_complete == 0)
{
// Idle loop until user input is complete
}
int i;
for(i = 0; i < 10000; i++){} // Delay for value stabilization
/* Process input value */
if (entered_value < 100)
{
TB0CCTL1 |= CCIE;
// Enable CCR1 interrupt
TB0CCR1 = (entered_value * PERIOD) / 100; // Calculate duty cycle
LCD_ClearDisplay();
LCD_Write("Motor Speed: ");
LCD_WriteNum(entered_value);
}
else
{
TB0CCTL1 &= ~CCIE;
LCD_ClearDisplay();
// Disable CCR1 interrupt
LCD_Write("Motor Speed: 100"); // Display max speed
}
TB1CCTL0 &= ~CCIE;
TB1CCTL0 &= ~CCIFG;
entered_value = 0;
is_complete = 0;
}
}
/* UART RX interrupt service routine */
#pragma vector = EUSCI_A0_VECTOR
interrupt void ISR_A0_RX(void)
{
// Disable Timer B1 interrupts
// Clear interrupt flag
// Reset entered value
// Reset complete flag
unsigned int value = UCA0RXBUF; // Read received data
if (value >= '0' && value <= '9') // Check if the value is a digit
{
entered_value = (entered_value * 10) + (value - '0'); // Append digit
TB1CCTL0 |= CCIE; // Enable Timer B1 interrupts
}
TB1R = 1; // Reset the timer
}
/* Timer B0 CCR0 interrupt service routine */
#pragma vector = TIMER0_B0_VECTOR
interrupt void ISR_TB0_CCR0(void)
{
if (TB0CCR1 != 0) // If duty cycle is not zero
{
P6OUT |= BIT1; // Turn on the motor/LED
}
TB0CCTL0 &= ~CCIFG; // Clear interrupt flag
}
/* Timer B0 CCR1 interrupt service routine */
#pragma vector = TIMER0_B1_VECTOR
interrupt void ISR_TB0_CCR1(void)
{
P6OUT &= ~BIT0;
// Turn off the motor/LED
TB0CCTL1 &= ~CCIFG; // Clear interrupt flag
}
/* Timer B1 CCR0 interrupt service routine */
#pragma vector = TIMER1_B0_VECTOR
interrupt void ISR_TB1_CCR0(void)
{
is_complete = 1;
}
