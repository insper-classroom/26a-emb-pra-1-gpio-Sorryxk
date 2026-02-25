#include <stdio.h>
#include "pico/stdlib.h"

const int LED    = 16;
const int BOTAO  = 12;
const int MOTOR[4] = {2, 3, 4, 5};

const int PASSOS[8][4] = {
    {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
    {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1}
};

void girar_360() {
    printf("motor: iniciando\n");
    for (int i = 0; i < 4096; i++) {
        for (int pino = 0; pino < 4; pino++) {
            gpio_put(MOTOR[pino], PASSOS[i % 8][pino]);
        }
        sleep_ms(2);
    }
    for (int pino = 0; pino < 4; pino++) gpio_put(MOTOR[pino], 0);
    printf("motor: concluido\n");
}

int main() {
    stdio_init_all();
    sleep_ms(2000);
    printf("sistema iniciado\n");

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    for (int i = 0; i < 4; i++) {
        gpio_init(MOTOR[i]);
        gpio_set_dir(MOTOR[i], GPIO_OUT);
    }

    while (true) {
        if (!gpio_get(BOTAO)) {
            sleep_ms(20); // debounce
            if (!gpio_get(BOTAO)) {
                printf("botao pressionado\n");
                gpio_put(LED, 1);
                girar_360();
                gpio_put(LED, 0);
                while (!gpio_get(BOTAO)) sleep_ms(1); // aguarda soltar
                printf("pronto para proximo pressionamento\n");
            }
        }
        sleep_ms(1);
    }
}
