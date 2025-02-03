#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11



int luz_atual = 1; // RED = 1 - BLUE = 2 - GREEN = 3

// Função de callback chamada a cada 3 segundos
bool repeating_timer_callback(struct repeating_timer *t) {
    // Alternar entre os estados do semáforo
    switch (luz_atual) {
        case 1:
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_BLUE, 1);
            gpio_put(LED_PIN_GREEN, 0);
            printf("Sinal Vermelho\n");
            luz_atual = 2;
            break;
        case 2:
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_BLUE, 0);
            gpio_put(LED_PIN_GREEN, 0);
            printf("Sinal Amarelo\n");
            luz_atual = 3;
            break;
        case 3:
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_BLUE, 0);
            gpio_put(LED_PIN_GREEN, 1);
            printf("Sinal Verde\n");
            luz_atual = 1;
            break;
    }
    return true; 
}

int main() {
    stdio_init_all();

    // Inicializa os GPIOs como saída
    gpio_init(LED_PIN_RED);
    gpio_init(LED_PIN_BLUE);
    gpio_init(LED_PIN_GREEN);
    
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Configura um temporizador para chamar a função a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Sistema operacional - aguardando mudança de sinal...\n");
        sleep_ms(1000);
    }
    return 0;
}
