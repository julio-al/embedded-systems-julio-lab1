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

//Lab 1 part 2
//The reason why the program is not working as expected is because the flag variable is shared between 
//the main funtion and the interrupt handler. This means that there is a possibility of a race condition, 
//where the flag value is changed by one thread while the other thread is reading or writing it. 
//This can lead to inconsistent or incorrect results. To avoid this problem, the program need to ensure that the access 
//to the flag variable is atomic, meaning that it cannot be interrupted by another thread. One way to do this is 
//to use a mutex or a critical section to protect the flag variable or to use an atomic type, 
//such as std::atomic<bool>, which guarantees that operations on it are indivisible and visible to all threads.

InterruptIn btn(PC_13);
//declare global flag variable
bool flag = false;

void btn_interrupt(){
    printf("Button pressed\r\n");
    //set the flag to true whenr button is pressed
    flag = true;
}
// main() runs in its own thread in the OS
int main()
{
    btn.fall(&btn_interrupt);
    while (1) {
        if(flag) {
            printf("Button presses\r\n");
            //reste flag after prinitng
            flag = false;
        }        
    }
}

