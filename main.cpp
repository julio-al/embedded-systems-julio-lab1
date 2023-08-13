#include "mbed.h"

//Lab 1 part 1
//Recived error message 
//++ MbedOS Error Info ++
//Error Status: 0x80010133 Code: 307 Module: 1
//Error Message: Mutex: 0x20000160, Not allowed in ISR context
//Location: 0x8009119
//Error Value: 0x20000160
//Current Thread: main Id: 0x200003B0 Entry: 0x800685F StackSize: 0x1000 StackMem: 0x10000548 SP: 0x20017F48 
//For more info, visit: https://mbed.com/s/error?error=0x80010133&tgt=DISCO_L475VG_IOT01A
//-- MbedOS Error Info --
//= System will be rebooted due to a fatal error =
//= Reboot count(=1) reached maximum, system will halt after rebooting =

//Error explanation:
//Recived error message indicates the use of a mutex (mechanism that prevents concurrent
//access to a shared resource) in an interrupt service routine (ISR) context, which is a 
//function that is executed when an interrupt occurs, which is not allowed.
//In the code below is the btn_interrupt funtion with the printf statement.
//Recommended solution is to use boolean flag to indicate the interrupt, 
//or EventQueue to defer the function call to different context 
//or switch to bare metal profile that does not use RTOS or mutexes

InterruptIn btn(PC_13);

void btn_interrupt(){
    printf("Button pressed\r\n");
}
// main() runs in its own thread in the OS
int main()
{
    btn.fall(&btn_interrupt);
    while (true) {

    }
}

