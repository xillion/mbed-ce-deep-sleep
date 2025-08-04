#include "mbed.h"

InterruptIn my_sw(BOOT_BTN);


DigitalOut  myled(LED1,0);
DigitalOut analog_pwr(PWR_KEY, 0);
LowPowerTimeout   ticker;
EventFlags        wakeupEvents;

#define LPT_WAKEUP_EVENT1  0x00
#define LPT_WAKEUP_EVENT2  0x01

//Thread threadFirst(osPriorityNormal, 1024);


void sw_irq();
void threadFirstWorker();


int main()
{
    //threadFirst.start(threadFirstWorker);
    analog_pwr=0;
    //sw_irq();

    //sleep_manager_unlock_deep_sleep();
    while (true) {
        ThisThread::sleep_for(10s);
        myled = 1;         
        ThisThread::sleep_for(1ms);
        myled = 0;
    }
}


void threadFirstWorker(){
    //sleep_manager_unlock_deep_sleep();
    while(true)
    {   
        wakeupEvents.wait_all(LPT_WAKEUP_EVENT1);
        myled = 1;         
        ThisThread::sleep_for(1ms);
        myled = 0;
        //sleep_manager_unlock_deep_sleep();
    }
}


void sw_irq(void)
{
    wakeupEvents.set(LPT_WAKEUP_EVENT1);
    ticker.attach(&sw_irq, 10s);
}

