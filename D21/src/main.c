#include "project.h"
#include <samd21.h>
#include <stdbool.h>
#include <stdint.h>
#define F_CPU 8000000	// 8MHz
#define PERIOD_FAST     100
#define PERIOD_SLOW     500


void uart_putc(char c);
void uart_puts(char *s);
void delay(int n);


void delay(int n)
{
    int i;

    for (;n >0; n--)
    {
        for (i=0;i<(F_CPU/10000);i++)
            __asm("nop");
    }
}

//-----------------------------------------------------------------------------
void uart_init() {
	uint32_t baud = 115200;

	// FBAUD = ( fREF/ S) (1 – BAUD/65,536)
	// FBAUD = baud frequency
	// fref – SERCOM generic clock frequency
	// S – Number of samples per bit
	// BAUD – BAUD register value
	uint64_t br = (uint64_t)65536 * (F_CPU - 16 * baud) / (float)F_CPU;	// Variable for baud rate

	PORT->Group[0].DIRSET.reg = (1 << 22);							// Set TX Pin direction to output
	PORT->Group[0].PINCFG[22].reg |= PORT_PINCFG_INEN;				// Set TX Pin config for input enable (required for usart)
	PORT->Group[0].PINCFG[22].reg |= PORT_PINCFG_PMUXEN;			// enable PMUX
	PORT->Group[0].PMUX[22>>1].bit.PMUXE = PORT_PMUX_PMUXE_C_Val;	// Set the PMUX bit (if pin is even, PMUXE, if odd, PMUXO)

	PORT->Group[0].DIRCLR.reg = (1 << 23);							// Set RX Pin direction to input
	PORT->Group[0].PINCFG[23].reg |= PORT_PINCFG_INEN;				// Set RX Pin config for input enable
	PORT->Group[0].PINCFG[23].reg &= ~PORT_PINCFG_PULLEN;			// enable pullup/down resistor
	PORT->Group[0].PINCFG[23].reg |= PORT_PINCFG_PMUXEN;			// enable PMUX
	PORT->Group[0].PMUX[23>>1].bit.PMUXO = PORT_PMUX_PMUXE_C_Val;	// Set the PMUX bit (if pin is even, PMUXE, if odd, PMUXO)

	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM3;						// Set the PMUX for SERCOM3 and turn on module in PM

	// Generic clock “SERCOM3_GCLK_ID_CORE” uses GCLK Generator 0 as source (generic clock source can be
	// changed as per the user needs), so the SERCOM3 clock runs at 8MHz from OSC8M
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SERCOM3_GCLK_ID_CORE) | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(0);

	// By setting the DORD bit LSB is transmitted first and setting the RXPO bit as 1
	// corresponding SERCOM PAD[1] will be used for data reception, PAD[0] will be used as TxD
	// pin by setting TXPO bit as 0, 16x over-sampling is selected by setting the SAMPR bit as
	// 0, Generic clock is enabled in all sleep modes by setting RUNSTDBY bit as 1,
	// USART clock mode is selected as USART with internal clock by setting MODE bit into 1.
	SERCOM3->USART.CTRLA.reg = SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_MODE_USART_INT_CLK | SERCOM_USART_CTRLA_RXPO(1/*PAD1*/) | SERCOM_USART_CTRLA_TXPO(0/*PAD0*/);

	// 8-bits size is selected as character size by setting the bit CHSIZE as 0,
	// TXEN bit and RXEN bits are set to enable the Transmitter and receiver
	SERCOM3->USART.CTRLB.reg = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_CHSIZE(0/*8 bits*/);

	// baud register value corresponds to the device communication baud rate
	SERCOM3->USART.BAUD.reg = (uint16_t)br;

	// SERCOM3 peripheral enabled
	SERCOM3->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
}

void uart_putc(char c)
{
	while (!(SERCOM3->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_DRE));
	SERCOM3->USART.DATA.reg = c;
}
void uart_puts(char *s)
{
	const char* temp = s;
	while (*temp)
	{
		uart_putc(*temp++);
	}
	uart_putc('\n');

}

bool uart_has_data()
{
	if ((SERCOM3->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_RXC) >> SERCOM_USART_INTFLAG_RXC_Pos)
	{

		return true;
	}
	return false;
}

static char uart_getc()
{
 return SERCOM3->USART.DATA.reg;
}
//-----------------------------------------------------------------------------
void sys_init(void)
{
	// Switch to 8MHz clock (disable prescaler)
	SYSCTRL->OSC8M.bit.PRESC = 0;

	// Enable interrupts
	asm volatile ("cpsie i");
}

int main()
{
	// Initialize the SAM system
	// SystemInit();
	//
	// sys_init();
	// REG_PORT_DIR1 |= PORT_PB30;
	// REG_PORT_OUT1 &= ~PORT_PB30;
	//
	// uart_init();
	// //timer_init();
	//
	// //delay(2000);
	// //uart_puts("ZZZZZZ\n\n");
	// //uart_puts("\r\nType in Something and press Enter.\r\n");
	// char x[1024];
	//
	// int ctr = 0;
	// while(1)
	// {
	//
	// 	if (uart_has_data())
	// 	{
	// 		REG_PORT_OUT1 ^= 1 << 30;
	// 		char c = uart_getc();
	// 		uart_putc(c);
	// 	}
	//
	// }
	SystemInit();
	NVIC_EnableIRQ(TC3_IRQn);
	uart_init();

	
	for(;;)
	{

	}

}
