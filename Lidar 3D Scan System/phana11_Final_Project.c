// NAME: Annie Phan
// STUDENT #: 400380760
// MACID: phana11
// ASSIGNED BUS SPEED: 80 MHz
// ASSIGNED MEASUREMENT STATUS PIN: PF4
// ASSIGNED ADDUTIONAL STATUS PIN: PF0

#include <stdint.h>
#include "Systick.h"
#include "PLL.h"
#include "tm4c1294ncpdt.h"
#include "vl53l1x_api.h"
#include "uart.h"
#include "onboardLEDs.h"
#include "StepperMotor.h"
#include "I2CInit.h"
#include "OnboardButton.h"
#include "variables.h"

uint16_t	dev=0x52;

int status = 0;

volatile int IntCount;

//Used for interrupt
int state = 0;

//capture values from VL53L1X for inspection
uint16_t debugArray[512];

// BUS SPEED through AD2
void PortE_Init(void){
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // activate the clock for Port E
while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R4) == 0){}; // allow time for clock to stabilize
    GPIO_PORTE_DIR_R = 0b00000010;
    GPIO_PORTE_DEN_R = 0b00000010; // Enable PE1
return;
}
 
void bus_speed_test(void){ // this function would be called to validate Bus Speed
	//SysTick_Wait(10000000);
	GPIO_PORTE_DATA_R ^= 0b00000010;
	SysTick_Wait10ms(100);
	//GPIO_PORTE_DATA_R ^= 0b00000010;
	//SysTick_Wait(10000000);
	//GPIO_PORTE_DATA_R ^= 0b00000010;
}

int main(void) {
  uint8_t byteData, sensorState=0, myByteArray[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} , i=0;
  uint16_t wordData;
  uint8_t ToFSensor = 1; // not used
  uint16_t SignalRate; // not used
  uint16_t AmbientRate; // not used
  uint16_t SpadNum;  // not used
	uint8_t RangeStatus;
	uint8_t dataReady;
	uint16_t Distance;
  
	// initialization
  PLL_Init(); // Initialize the system clock
  SysTick_Init(); // Initialize the SysTick timer
  onboardLEDs_Init(); // Initialize onboard LEDs
  I2C_Init(); // Initialize I2C for ToF sensor communication
  UART_Init(); // Initialize UART for serial communication
  PortH_Init(); // Initialize GPIO Port H for stepper motor control
  
	
	// hello world!
	UART_printf("Program Begins\r\n");
	sprintf(printf_buffer,"2DX4 Project Code\r\n");
	UART_printf(printf_buffer);
	
  // I2C read functions to check ToF sensor initialization
  status = VL53L1_RdByte(dev, 0x010F, &byteData);					// This is the model ID.  Expected returned value is 0xEA
  myByteArray[i++] = byteData;

  status = VL53L1_RdByte(dev, 0x0110, &byteData);					// This is the module type.  Expected returned value is 0xCC
  myByteArray[i++] = byteData;
	
	status = VL53L1_RdWord(dev, 0x010F, &wordData);
	status = VL53L1X_GetSensorId(dev, &wordData);

	sprintf(printf_buffer,"Model_ID=0x%x , Module_Type=0x%x\r\n",myByteArray[0],myByteArray[1]);
	UART_printf(printf_buffer);

	// Booting ToF chip
	while(sensorState==0){
		status = VL53L1X_BootState(dev, &sensorState);
		SysTick_Wait10ms(10);
  }
	FlashAllLEDs(); //Flash all LEDS to indicate boot
	UART_printf("ToF Chip Booted!\r\n");
 	UART_printf("One moment...\r\n");
	
	status = VL53L1X_ClearInterrupt(dev); /* clear interrupt has to be called to enable next interrupt*/

	
  /* This function must to be called to initialize the sensor with the default setting  */
  status = VL53L1X_SensorInit(dev);
	Status_Check("SensorInit", status);


	UART_printf("Press GPIO J1 to start/stop data capture\r\n");
	
	ExternalButton_Init(); //Enable button interrupt
	
	
	// Infinite loop to handle data capture and rotation
	while (1) { 
		if (state == 1) {
    status = VL53L1X_StartRanging(dev); // Start ranging
    Status_Check("StartRanging", status);
    
    int scanIntervalSteps = 16; // Perform a scan every 16 steps for a total of 32 scans per rotation (everyscan
    int totalSteps = 512; // Total steps for a full rotation
    int stepCounter = 0; // Counter to keep track of the number of steps
    
    // Perform rotation and scanning
    for(int i = 0; i < totalSteps; i += scanIntervalSteps) {
        for (int step = 0; step < scanIntervalSteps; ++step) {
            rotate(1, 1, 1); // Rotate 1 step at a time
            ++stepCounter; // Increment step counter
        }
        
        // Ensure data is ready
        while (dataReady == 0) {
            status = VL53L1X_CheckForDataReady(dev, &dataReady);
            FlashLED3(1); // flash to indicate data processing/distance measured
            VL53L1_WaitMs(dev, 5);
        }

        dataReady = 0;
        status = VL53L1X_GetRangeStatus(dev, &RangeStatus);
        status = VL53L1X_GetDistance(dev, &Distance);
        FlashLED3(1); // Flash every time data is collected
        
        debugArray[i / scanIntervalSteps] = Distance; // Store distance
        
        status = VL53L1X_ClearInterrupt(dev); // Clear interrupt to enable next interrupt

        sprintf(printf_buffer, "%u\r\n", Distance);
        UART_printf(printf_buffer); // Transmit distance measurement

        FlashLED4(1); // Flash every rotation or scan
        
        // Check if the stop condition is met
        if (state == 0) {
            break;
        }
    }
    
    // If stopped early or after completing rotation, unwind the steps
    if (state == 0 || stepCounter == totalSteps) {
        rotate(stepCounter, 1, -1); // Unwind the rotation
    }
    
    VL53L1X_StopRanging(dev);
    UART_printf("Data capture has stopped, press the button to restart data capture\r\n");
    state = 0;
}
	
		if (state == 0) { // If data capture is off
			while (state == 0) {
				SysTick_Wait10ms(50);
				if (state == 1) break; // If interrupt triggered, exits loop to enter data capture loop
			}
		}
	}
}

