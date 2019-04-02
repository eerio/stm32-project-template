#include<stm32f0xx.h>

/* This is a demonstration of my Operating System
 *
 * It's designed for STM32F091RC development board
 * and you should test this example on it.
 * After compiling the example and programming the binary
 * onto the board, run it and you should see
 * your User LED (LD2, pin 5 @ GPIO port A) blinking periodically
 *
 * author: Paweł Balawender, github.com/eerio
 *
 */

#define LED_PIN (5U)
#define LED_ON() (GPIOA->BSRR |= (1U << LED_PIN))
#define LED_OFF() (GPIOA->BRR |= (1U << LED_PIN))
#define LED_TOG() (GPIOA->ODR ^= (1U << LED_PIN))


/**
 * @brief Simple delay function
 *
 * @param n number of loop cycles to accomplish
 */
void delay(unsigned int n);

/**
 * @brief Main function.
 * Demo: blink User LED (LD2) 10 times, then terminate
 * @return 0: terminated succesfully
 */
int main(void) {
    /* At this point we assume that the stack is initialized,
     * .data segment is copied to SRAM, .bss segment is zero-filled,
     * SystemCoreClock variable is set to current system clock source,
     * internal clocks are initialized and __libc_init_array routine has
     * been called. These things are done by ResetHandler in
     * startup_<device>.s file and SystemInit func in system_<device_fam>.c
     */
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER5_0;
    for (unsigned int i=0; i < 20; ++i) {LED_TOG(); delay(100000);}

    /* Main thread after return from the main function goes to an infinite
     * loop in the startup_stm32f091xc.s file */
    return 0;
}

void delay(volatile unsigned int n) {
    while(--n);
}

