/*
/////////////////// DATOS DEL PROGRAMA ////////////////////

//  TTITULO: Led Blinkng
//  MICRO:PIC16F15244
//  ESTUDIANTES: Harold F MURCIA
//  Profesor: Harold F MURCIA
//  FECHA: 19 de abril de 2021

///////////// CONFIGURACION del MCU ////////////////// */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>


#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ    // Power-up Default Value for COSC bits->HFINTOSC (1 MHz)
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O function on RA4
#pragma config VDDAR = HI    // VDD Range Analog Calibration Selection bit->Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V

// CONFIG2
#pragma config MCLRE = EXTMCLR    // Master Clear Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR
#pragma config PWRTS = PWRT_OFF    // Power-up Timer Selection bits->PWRT is disabled
#pragma config WDTE = OFF    // WDT Operating Mode bits->WDT disabled; SEN is ignored
#pragma config BOREN = ON    // Brown-out Reset Enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO    // Brown-out Reset Voltage Selection bit->Brown-out Reset Voltage (VBOR) set to 1.9V
#pragma config PPS1WAY = ON    // PPSLOCKED One-Way Set Enable bit->The PPSLOCKED bit can be cleared and set only once in software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block is disabled
#pragma config SAFEN = OFF    // SAF Enable bit->SAF is disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block is not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block is not write-protected
#pragma config WRTC = OFF    // Configuration Registers Write Protection bit->Configuration Registers are not write-protected
#pragma config WRTSAF = OFF    // Storage Area Flash (SAF) Write Protection bit->SAF is not write-protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.

// CONFIG5
#pragma config CP = OFF    // User Program Flash Memory Code Protection bit->User Program Flash Memory code protection is disabled



///////////// DEFINICIONES  //////////////////
#define _XTAL_FREQ 1000000
#define LED0_SetHigh()            LATAbits.LATA2 = 1;
#define LED0_SetLow()             LATAbits.LATA2 = 0;
#define ACQ_US_DELAY 10
///////////////

///////////// VARIABLES GLOBALES  //////////////////
int par_impar=0;
uint16_t dutyCycle10 = 10;
uint16_t dutyCycle50 = 0x01F4;
uint16_t dutyCycle75 = 0x02EE;
uint16_t dutyCycle100 = 0x03E7;

///////////// DECLARACI�N DE FUNCIONES Y PROCEDIMIENTOS ///////////////////
void PIN_MANAGER_Initialize(void)
{
    // LATx registers
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    // TRISx registers
    TRISA = 0x3B;
    TRISB = 0xF0;
    TRISC = 0xFF;

    // ANSELx registers
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x00;

    // WPUx registers
    WPUB = 0x00;
    WPUA = 0x04;
    WPUC = 0x04;

    // TRISx registers
    TRISA2 = 0;          // Definiendo puerto A2 como salida digital
    TRISC2 = 1;          // Definiendo puerto C2 como entada digital
    WPUC2  = 1;          // Activando resistencia d pull-up
    ANSELAbits.ANSA1 = 1;// Definiendo entrada como analoga                                                         // RA2->PWM3:PWM3OUT;

}



void OSCILLATOR_Initialize(void)
{
    OSCEN = 0x00;                                                               // MFOEN disabled; LFOEN disabled; ADOEN disabled; HFOEN disabled;
    OSCFRQ = 0x00;                                                              // HFFRQ0 1_MHz
    OSCTUNE = 0x00;

}

/////////////  INICIO DEL PROGRAMA PRINCIPAL //////////////////////////

void main(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    // Led off
    LATAbits.LATA2 = 1;
    while(1){
        if (PORTCbits.RC2==1){
            LATAbits.LATA2 = 0;
        }else{
           LATAbits.LATA2 = 1;
        }
    }
}
