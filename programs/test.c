#include <kilolib.h>

void setup() {
    // put your setup code here, to be run only once
}

void loop() {
    // put your main code here, to be run repeatedly
}

int main() {
    // initialize hardware
    kilo_init();
    // start program
    kilo_start(setup, loop);

    return 0;
}
