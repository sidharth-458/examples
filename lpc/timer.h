#define CLOCK_FREQ	60000000.0
#define TIMER_PERIOD_MS(x) (CLOCK_FREQ * x * 0.001)

void TIMER_INIT(void);
void TIMER_ISR_INIT(void);