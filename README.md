### PSLib - library for stm32 microcontrollers

Just for fun experemental C++ static template library. No source files, only headers.

Example
``` cpp
#include "ps_stm32.h"
#include "ps_sys.h"
#include "ps_gpio.h"
#include "ps_usart.h"
#include "ps_logger.h"
#include "ps_util.h"

using namespace ps;

typedef log::logger< usart_1 > logger;

char itoa32_buff[12];

int main()
{
    gpio_a::enable_clock();
    gpio_a::init(
            gpio::speed_10MHz,
            gpio::mode_af_pp,
            pin::pin_9 | pin::pin_10);

    usart_1::enable_clock();
    usart_1::init(9600);
    usart_1::init_nvic();
    usart_1::enable_it(usart::it::it_rxne);
    usart_1::enable();
    
    usart_1.write("Hello World!\n")

    logger log("main.cpp", log::debug);

    log.debug("System Timer");
    log.debug("\tInitialization...");
    sys::tick_init(1000);
    log.debug("\tDone");

    log.debug("GPIOC");
    log.debug("\tInitialization...");
    gpio_c::enable_clock();
    gpio_c::init(
            gpio::speed_2MHz,
            gpio::mode_out_pp,
            pin::pin_8 | pin::pin_9);
    log.debug("\tDone");
    
    char dma_buff[] = "Hello from DMA!\n";
    usart_1::init_dma_tx();
    usart_1::write_dma((uint8_t*)dma_buff, 16);

    while(1)
    {
        GPIOC->ODR ^= GPIO_Pin_9;
        sys::sleep_ms(200);
        GPIOC->ODR ^= GPIO_Pin_8;
    }
}
