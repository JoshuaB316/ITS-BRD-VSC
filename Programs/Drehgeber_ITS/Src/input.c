/**
 *******************************************************************
 * @file    input.c 
 * @author  Franz Korf
 *        	HAW-Hamburg
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @date    WS 2016
 * @brief   Implementation of module input
 *******************************************************************
*/

#include "input.h"
#include <stm32f4xx_hal.h>

#define INPUT_REG							            GPIOF

#define OFFSET_CHANNEL_B       					   0    // channel B connected to BIT 0
#define OFFSET_CHANNEL_A       					   1    // channel A connected to bit 1
#define OFFSET_ERROR_RESET_BUTTON			      6
#define OFFSET_COUNTER_REG_RESET_BUTTON			7

#define CHANNEL_A_AND_B_MASK						   ((0x01 << OFFSET_CHANNEL_A) | (0x01 << OFFSET_CHANNEL_B))
#define ERROR_RESET_BUTTON_MASK					   (0x01 << OFFSET_ERROR_RESET_BUTTON)
#define COUNTER_REG_RESET_BUTTON_MASK				(0x01 << OFFSET_COUNTER_REG_RESET_BUTTON)

bool errorResetButtonPressed(void){
   return 0x0000 == (INPUT_REG->IDR & ERROR_RESET_BUTTON_MASK);
}

// Mapping of channel value pairs to phases
// PhaseA = 0x00, /* A = 0 B = 0 */
// PhaseD = 0x01, /* A = 0 B = 1 */
// PhaseB = 0x02, /* A = 1 B = 0 */
// PhaseC = 0x03, /* A = 1 B = 1 */

static PhaseType mapChannelValueToPhaseType[] = {PhaseA, PhaseD, PhaseB, PhaseC};

PhaseType giveCurrentPhase(void){
   return mapChannelValueToPhaseType[INPUT_REG->IDR & CHANNEL_A_AND_B_MASK];
}

// EOF
