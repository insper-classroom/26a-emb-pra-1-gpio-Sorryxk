#include <stdio.h>
#include "pico/stdlib.h"

const int LED  = 16;
const int BOTAO = 12;
const int IN1  = 2;
const int IN2  = 3;
const int IN3  = 4;
const int IN4  = 5;

void passo(int in1, int in2, int in3, int in4) {
    gpio_put(IN1, in1);
    gpio_put(IN2, in2);
    gpio_put(IN3, in3);
    gpio_put(IN4, in4);
    sleep_ms(2);
}

void girar_360() {
    printf("motor: iniciando\n");
    for (int i = 0; i < 512; i++) {
        passo(1,0,0,0);
        passo(1,1,0,0);
        passo(0,1,0,0);
        passo(0,1,1,0);
        passo(0,0,1,0);
        passo(0,0,1,1);
        passo(0,0,0,1);
        passo(1,0,0,1);
    }
    passo(0,0,0,0); // desliga bobinas
    printf("motor: concluido\n");
}

int main() {
    stdio_init_all();
    sleep_ms(2000);
    printf("sistema iniciado\n");

    gpio_init(LED);   gpio_set_dir(LED,   GPIO_OUT);
    gpio_init(BOTAO); gpio_set_dir(BOTAO, GPIO_IN); gpio_pull_up(BOTAO);
    gpio_init(IN1);   gpio_set_dir(IN1,   GPIO_OUT);
    gpio_init(IN2);   gpio_set_dir(IN2,   GPIO_OUT);
    gpio_init(IN3);   gpio_set_dir(IN3,   GPIO_OUT);
    gpio_init(IN4);   gpio_set_dir(IN4,   GPIO_OUT);

    while (true) {
        if (!gpio_get(BOTAO)) {
            sleep_ms(20);
            if (!gpio_get(BOTAO)) {
                printf("botao pressionado\n");
                gpio_put(LED, 1);
                girar_360();
                gpio_put(LED, 0);
                while (!gpio_get(BOTAO)) sleep_ms(1);
                printf("pronto\n");
            }
        }
        sleep_ms(1);
    }
}
