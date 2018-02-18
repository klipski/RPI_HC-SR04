// gcc -Wall -pthread -o ultrasonic_distance ultrasonic_distance.c -lpigpio

#include <stdio.h>
#include <pigpio.h>

#define TRIGGER 5
#define ECHO  6

int main(int argc, char *argv[]) {
    double start, stop, measure;

    if (gpioInitialise() < 0) {
        fprintf(stderr, "pigpio initialisation failed\n");
        return 1;
    }

    /* Set GPIO modes */
    gpioSetMode(TRIGGER , PI_OUTPUT);  // trigger
    gpioSetMode(ECHO , PI_INPUT);  // echo
    fprintf(stdout, "Set GPIO modes\n");

    gpioWrite(TRIGGER, 1);
    gpioSleep(PI_TIME_RELATIVE, 0, 10); // sleep for 0.00001 seconds
    gpioWrite(TRIGGER, 0);

    while (gpioRead(ECHO) == 0)
	start = time_time();
    while (gpioRead(ECHO) == 1)
        stop = time_time();

    measure = ((stop-start) *34300.0)/2.0;

    fprintf(stdout, "Measure: %lf\n", measure);

    /* Stop DMA, release resources */
    gpioTerminate();
    return 0;
}
