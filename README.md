### PSLib - library for stm32 microcontrollers

Example
``` cpp
#include "ps_stm32.h"
#include "ps_system.h"
#include "ps_gpio.h"
#include "ps_usart.h"
#include "ps_logger.h"

using namespace ps;

typedef hw::gpio::gpio< hw::gpio::gpio_a > gpio_a;
typedef hw::gpio::gpio< hw::gpio::gpio_c > gpio_c;
typedef hw::usart::usart< hw::usart::usart_1 > usart_1;
typedef log::logger< usart_1 > logger;

int main()
{
    gpio_a::enable_clock();
    gpio_a::init(
            hw::gpio::speed_10MHz,
            hw::gpio::mode_af_pp,
            hw::pin::pin_9 | hw::pin::pin_10);

    usart_1::enable_clock();
    usart_1::init(9600);
    usart_1::init_nvic();
    usart_1::enable_it(hw::usart::it::it_rxne);
    usart_1::enable();
    
    usart_1::write((uint8_t*)"Hello world\n");

    logger log("main.cpp", ps::log::debug);

    log.debug("Hello world");
    
    char dma_buff[] = "Hello from DMA\n";
    usart_1::init_dma_tx();
    usart_1::write_dma((uint8_t*)dma_buff, 15);
    
    gpio_c::enable_clock();
    gpio_c::init(
            hw::gpio::speed_2MHz,
            hw::gpio::mode_out_pp,
            hw::pin::pin_8 | hw::pin::pin_9);

    sys::tick_init(10000);
    while(1)
    {
        GPIOC->ODR ^= GPIO_Pin_8;
        sys::sleep_ms(500);
    }
}
