#include "timer.h"




static time_t time_counter = -1;
static time_t time_checker = -1;

void timer_start(int restart) {
    if(time_counter == -1 || restart) {
        time_counter = time(NULL);
    }
}
int timer_times_up(double sec) {
    time_checker = time(NULL);

    if(time_checker == -1) {
        time_checker = time(NULL);
    }
    if(sec < difftime(time_checker, time_counter)) {
        time_counter = -1;
        time_checker = -1;
        return 1;
    }
    return 0;

}