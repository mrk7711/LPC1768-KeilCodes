#include "lpc17xx_uart.h"

void UART_IntReceive(void);
void UART_IntTransmit(void);
void UART_IntErr(uint8_t bLSErrType);

/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void UART0_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(LPC_UART0);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(LPC_UART0);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			UART_IntReceive();
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART_IntTransmit();
	}

}


/********************************************************************//**
 * @brief 		UART receive function 
 * @param[in]	None
 * @return 		None
 *********************************************************************/
__weak void UART_IntReceive(void)
{	
	 UART_ReceiveByte(LPC_UART0);
}

/********************************************************************//**
 * @brief 		UART transmit function
 * @param[in]	None
 * @return 		None
 *********************************************************************/
__weak void UART_IntTransmit(void)
{	
	
}

/*********************************************************************//**
 * @brief		UART Line Status Error
 * @param[in]	bLSErrType	UART Line Status Error Type
 * @return		None
 **********************************************************************/
__weak void UART_IntErr(uint8_t bLSErrType)
{
	while(1);
}
