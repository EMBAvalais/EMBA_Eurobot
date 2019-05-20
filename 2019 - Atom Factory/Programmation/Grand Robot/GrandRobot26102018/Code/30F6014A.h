//////// Standard Header file for the DSPIC30F6014A device ////////////////
#device DSPIC30F6014A
#nolist
//////// Program memory: 49152x24  Data RAM: 8192  Stack: 31
//////// I/O: 68   Analog Pins: 16
//////// Data EEPROM: 4096
//////// Fuses: XTL,HS,XT,XT_PLL4,XT_PLL8,XT_PLL16,ER_IO,ER,EC,EC_IO,EC_PLL4
//////// Fuses: EC_PLL8,EC_PLL16,LP,FRC,LPRC,PR,NOCKSFSM,CKSNOFSM,CKSFSM,WDT
//////// Fuses: NOWDT,WPSB1,WPSB2,WPSB3,WPSB4,WPSB5,WPSB6,WPSB7,WPSB8,WPSB9
//////// Fuses: WPSB10,WPSB11,WPSB12,WPSB13,WPSB14,WPSB15,WPSB16,WPSA1,WPSA8
//////// Fuses: WPSA64,WPSA512,NOPUT,PUT4,PUT16,PUT64,BROWNOUT,NOBROWNOUT
//////// Fuses: BORV20,BORV27,BORV42,BORV47,LPOL_HIGH,LPOL_LOW,HPOL_HIGH
//////// Fuses: HPOL_LOW,PWMPIN,NOPWMPIN,MCLR,NOMCLR,PROTECT,NOPROTECT,WRT
//////// Fuses: NOWRT,DEBUG,NODEBUG,COE,NOCOE,ICSP1,ICSP2,ICSP3,ICSP4
//////// Fuses: FRC_PLL4,FRC_PLL8,FRC_PLL16,HS2_PLL4,HS2_PLL8,HS2_PLL16
//////// Fuses: HS3_PLL4,HS3_PLL8,HS3_PLL16,PR_PLL
//////// 
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         SET_PULLUP(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Constants used to identify pins in the above are:

#define PIN_A6  5654
#define PIN_A7  5655
#define PIN_A9  5657
#define PIN_A10  5658
#define PIN_A12  5660
#define PIN_A13  5661
#define PIN_A14  5662
#define PIN_A15  5663

#define PIN_B0  5696
#define PIN_B1  5697
#define PIN_B2  5698
#define PIN_B3  5699
#define PIN_B4  5700
#define PIN_B5  5701
#define PIN_B6  5702
#define PIN_B7  5703
#define PIN_B8  5704
#define PIN_B9  5705
#define PIN_B10  5706
#define PIN_B11  5707
#define PIN_B12  5708
#define PIN_B13  5709
#define PIN_B14  5710
#define PIN_B15  5711

#define PIN_C1  5745
#define PIN_C2  5746
#define PIN_C3  5747
#define PIN_C4  5748
#define PIN_C13  5757
#define PIN_C14  5758
#define PIN_C15  5759

#define PIN_D0  5792
#define PIN_D1  5793
#define PIN_D2  5794
#define PIN_D3  5795
#define PIN_D4  5796
#define PIN_D5  5797
#define PIN_D6  5798
#define PIN_D7  5799
#define PIN_D8  5800
#define PIN_D9  5801
#define PIN_D10  5802
#define PIN_D11  5803
#define PIN_D12  5804
#define PIN_D13  5805
#define PIN_D14  5806
#define PIN_D15  5807

#define PIN_F0  5888
#define PIN_F1  5889
#define PIN_F2  5890
#define PIN_F3  5891
#define PIN_F4  5892
#define PIN_F5  5893
#define PIN_F6  5894
#define PIN_F7  5895
#define PIN_F8  5896

#define PIN_G0  5936
#define PIN_G1  5937
#define PIN_G2  5938
#define PIN_G3  5939
#define PIN_G6  5942
#define PIN_G7  5943
#define PIN_G8  5944
#define PIN_G9  5945
#define PIN_G12  5948
#define PIN_G13  5949
#define PIN_G14  5950
#define PIN_G15  5951

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE unsigned int8
#define BOOLEAN int1

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// UART
// Constants used in setup_uart() are:
// FALSE - Turn UART off
// TRUE  - Turn UART on
#define UART_ADDRESS           2
#define UART_DATA              4
#define UART_AUTODETECT        8
#define UART_AUTODETECT_NOWAIT 9
#define UART_WAKEUP_ON_RDA     10
#define UART_SEND_BREAK        13


////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT() and RESTART_WDT()
//
// Constants used for SETUP_WDT() are:
#define WDT_ON      1
#define WDT_OFF     0

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Constants passed into RESTART_CAUSE() are:
#define RESTART_POWER_UP      0
#define RESTART_BROWNOUT      1
#define RESTART_WATCHDOG      4
#define RESTART_SOFTWARE      6
#define RESTART_MCLR          7
#define RESTART_ILLEGAL_OP    14
#define RESTART_TRAP_CONFLICT 15
//
// Constants passed into SLEEP() are:
#define SLEEP_FULL      0  // Default
#define SLEEP_IDLE      1  // Clock and peripherals don't stop

////////////////////////////////////////////////////////////////// INTERNAL RC
// Constants used in setup_oscillator() are:
#define OSC_INTERNAL     32
#define OSC_CRYSTAL       1
#define OSC_CLOCK         2
#define OSC_RC            3
#define OSC_SECONDARY    16

////////////////////////////////////////////////////////////////// Timer
// Timer Functions: SETUP_TIMERx, GET_TIMERx, GET_TIMERxy,
// SET_TIMERx, SET_TIMERxy
// Constants used for SETUP_TIMERx() are:
//      (or (via |) together constants from each group)
#define TMR_DISABLED 0x0000
#define TMR_INTERNAL 0xA000
#define TMR_EXTERNAL 0xA002
#define TMR_GATE     0x0040 
#define T1_EXTERNAL_SYNC 0xA006 //This only applies to Timer1
#define T1_EXTERNAL_RTC  0xC002 //This only applies to Timer1

#define TMR_DIV_BY_1   0x0000
#define TMR_DIV_BY_8   0x0010
#define TMR_DIV_BY_64  0x0020
#define TMR_DIV_BY_256 0x0030
#define TMR_32_BIT     0x0008 // Only for even numbered timers

/////////////////////////////////////////////////////////// INPUT CAPTURE
// Functions: SETUP_CAPTURE, GET_CAPTURE,
//
// Constants used for SETUP_CAPTURE() are:
#define CAPTURE_OFF               0x0000  // Capture OFF
#define CAPTURE_EE                0x0001  // Capture Every Edge
#define CAPTURE_FE                0x0002  // Capture Falling Edge
#define CAPTURE_RE                0x0003  // Capture Rising Edge
#define CAPTURE_DIV_4             0x0004  // Capture Every 4th Rising Edge
#define CAPTURE_DIV_16            0x0005  // Capture Every 16th Rising Edge
#define CAPTURE_INTERRUPT_ONLY    0x0007  // Interrupt on Rising Edge when in Sleep or Idle

// The following defines can be ORed | with above to configure interrupts
#define INTERRUPT_EVERY_CAPTURE   0x0000  // Interrupt on every capture event
#define INTERRUPT_SECOND_CAPTURE  0x0020  // Interrupt on every second capture event
#define INTERRUPT_THIRD_CAPTURE   0x0040  // Interrupt on every third capture event
#define INTERRUPT_FOURTH_CAPTURE  0x0060  // Interrupt on every fourth capture event

// The following defines can be ORed | with above to select timer
#define CAPTURE_TIMER2            0x0080  // On capture event Timer 2 is captured
#define CAPTURE_TIMER3            0x0000  // On capture event Timer 3 is captured

// The following defines can be ORed | with above to select idle operation mode
#define CAPTURE_HALT_IDLE         0x2000  // Capture module halts during idle mode
#define CAPTURE_CONTINUE_IDLE     0x0000  // Capture module continues during idle mode

/////////////////////////////////////////////////////////// OUTPUT COMPARE
// Functions: SETUP_COMPARE, SET_PWM_DUTY, SET_COMPARE_TIME
//
// Constants used for SETUP_COMPARE() are:
#define COMPARE_OFF               0x0000  // Compare OFF
#define COMPARE_SET_ON_MATCH      0x0001  // Pin from low to high on match
#define COMPARE_CLR_ON_MATCH      0x0002  // Pin from high to low on match
#define COMPARE_TOGGEL            0x0003  // Pin will toggle on every match occurrence
#define COMPARE_SINGLE_PULSE      0x0004  // Pin will generate single pulse on first match
#define COMPARE_CONT_PULSE        0x0005  // Pin will pulse for every match
#define COMPARE_PWM               0x0006  // Compare operates as PWM with fault pin disabled
#define COMPARE_PWM_FAULT         0x0007  // Compare operates as PWM with fault pin enabled

// The following defines can be ORed | with above to select timer
#define COMPARE_TIMER2            0x0000  // Timer 2 is the base timer
#define COMPARE_TIMER3            0x0008  // Timer 3 is the base timer

// The following defines can be ORed | with above to select idle operation mode
#define COMPARE_HALT_IDLE         0x2000  // Compare module halts during idle mode
#define COMPARE_CONTINUE_IDLE     0x0000  // Compare module continues during idle mode


////////////////////////////////////////////////////////////////// SPI
// SPI Functions: SETUP_SPI, SPI_WRITE, SPI_READ, SPI_DATA_IN
// Constants used in SETUP_SPI() are:
#define SPI_MASTER       0x0020
#define SPI_SLAVE        0x1000
#define SPI_L_TO_H       0
#define SPI_H_TO_L       0x0100
#define SPI_CLK_DIV_1    0x001F
#define SPI_CLK_DIV_4    0x001E
#define SPI_CLK_DIV_16   0x001D
#define SPI_CLK_DIV_64   0x001C
#define SPI_MODE_16B     0x0400
#define SPI_SS_DISABLED  0x8000

////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS()
//                SET_ADC_CHANNEL(), READ_ADC()
//
// Constants used for SETUP_ADC() are:
// Clock is at ADCS<5:0> of ADCON3 Reg. (0x02A4)
// Tad = (Tcy/2)*(ADCS<5:0>+1)
#define ADC_OFF           0x10000
#define ADC_CLOCK          0x0000     // External
#define ADC_CLOCK_DIV_2    0x0001
#define ADC_CLOCK_DIV_4    0x0003
#define ADC_CLOCK_DIV_8    0x0007
#define ADC_CLOCK_DIV_16   0x000F
#define ADC_CLOCK_DIV_32   0x001F
#define ADC_CLOCK_DIV_64   0x003F   
#define ADC_CLOCK_INTERNAL 0x0080     // Internal

// The following may be OR'ed in with the above using |
// Auto-Sample Time bits
#define ADC_TAD_MUL_0      0x0000
#define ADC_TAD_MUL_2      0x0200
#define ADC_TAD_MUL_4      0x0400
#define ADC_TAD_MUL_8      0x0800
#define ADC_TAD_MUL_16     0x1000
#define ADC_TAD_MUL_31     0x1F00

// Constants used in READ_ADC() are:
#define ADC_START_AND_READ 0x07
#define ADC_START_ONLY     0x01
#define ADC_READ_ONLY      0x06

// Constants used in SETUP_ADC_PORTS() are:
// First argument:
// OR together desired pins
#define sAN0                0x0001 //| B0
#define sAN1                0x0002 //| B1 
#define sAN2                0x0004 //| B2 
#define sAN3                0x0008 //| B3 
#define sAN4                0x0010 //| B4 
#define sAN5                0x0020 //| B5 
#define sAN6                0x0040 //| B6 
#define sAN7                0x0080 //| B7 
#define sAN8                0x0100 //| B8 
#define sAN9                0x0200 //| B9 
#define sAN10               0x0400 //| B10 
#define sAN11               0x0800 //| B11 
#define sAN12               0x1000 //| B12 
#define sAN13               0x2000 //| B13 
#define sAN14               0x4000 //| B14 
#define sAN15               0x8000 //| B15 
#define NO_ANALOGS      0           // None
#define ALL_ANALOG      0xFFFFFFFF  //

// Optional Second argument:
#define VSS_VDD            0x0000 // Range 0-Vdd
#define VREF_VREF          0x6000 // Range VrefL-VrefH
#define VREF_VDD           0x4000 // Range VrefL-Vdd
#define VSS_VREF           0x2000 // Range 0-VrefH


////////////////////////////////////////////////////////////////// DCI
// DCI Functions: setup_dci(), dci_start(), dci_read(), dci_write(),
//                , dci_data_received(), dci_transmit_ready()
//
#define MULTICHANNEL_MODE  0x0000
#define I2S_MODE           0x0001
#define AC97_16BIT_MODE    0x0002
#define AC97_20BIT_MODE    0x0003

#define JUSTIFY_DATA       0x0020 //Start data transmission on the same clock cycle as COFS pulses (multichannel)
#define MULTI_DEVICE_BUS   0x0040 //Tri-states the CSDO pin during unused time slots, normally drives '0'

#define UNDERFLOW_LAST     0x0080 //Transmits the last written value to the dci when data underflow occurs. Default is undeflow silence.
#define UNDERFLOW_SILENCE  0x0000 //Transmit '0's on data undeflow. This will cause a clicking noise if you are underflowing data while outputing to a codec.

#define DCI_SLAVE          0x0100 //Default is master
#define DCI_MASTER         0x0000 

#define SAMPLE_FALLING_EDGE 0x0000 //Default is Sample on the rising edge of the clock
#define SAMPLE_RISING_EDGE 0x0200

#define DCI_CLOCK_INPUT    0x0400 //SCLK is an input (supplied by codec or external source)
#define DCI_CLOCK_OUTPUT   0x0000 //Default is clock output

#define ENABLE_LOOPBACK    0x0800 //Connect the CSDI/CSDO internally; loops all of the sound back onto the bus

#define CODEC_MULTICHANNEL  0x0000  //enables multichannel (generic) codec support
#define CODEC_I2S           0x0001  //enables the I2S protocol
#define CODEC_AC16          0x0002  //enables the AC-16 protocol, setupCodecTransmission has no effect
#define CODEC_AC20          0x0003  //enables the AC-20 protocol, setupCodecTransmission has no effect

#define BUS_MASTER          0x0000  //designates this device as the bus master
#define BUS_SLAVE           0x0300  //designates this device as a slave on a bus controlled by another codec

#define TRISTATE_BUS        0x0040        //when in master mode, the module will be in high impedance 
                                    //during disabled frames (default drives 0's onto bus)
#define SYNC_COFS_DATA_PULSE 0x0020 //signifies that data starts transmitting on the same SCK pulse as the edge of the COFS pulse
                                    //(default data starts on the clock after the rising edge of COFS             
/* Determines when a sample is taken */
#define SAMPLE_RISING        0x0200 //sample data on the rising edge of the clock
#define SAMPLE_FALLING       0x0000 //sample data on the falling edge of the clock

#define DCI_4BIT_WORD      0x0003
#define DCI_5BIT_WORD      0x0004
#define DCI_6BIT_WORD      0x0005
#define DCI_7BIT_WORD      0x0006
#define DCI_8BIT_WORD      0x0007
#define DCI_9BIT_WORD      0x0008
#define DCI_10BIT_WORD     0x0009
#define DCI_11BIT_WORD     0x000A
#define DCI_12BIT_WORD     0x000B
#define DCI_13BIT_WORD     0x000C
#define DCI_14BIT_WORD     0x000D
#define DCI_15BIT_WORD     0x000E
#define DCI_16BIT_WORD     0x000F

#define DCI_1WORD_FRAME    0x0000
#define DCI_2WORD_FRAME    0x0010 << 1
#define DCI_3WORD_FRAME    0x0020 << 1
#define DCI_4WORD_FRAME    0x0030 << 1
#define DCI_5WORD_FRAME    0x0040 << 1
#define DCI_6WORD_FRAME    0x0050 << 1
#define DCI_7WORD_FRAME    0x0060 << 1
#define DCI_8WORD_FRAME    0x0070 << 1
#define DCI_9WORD_FRAME    0x0080 << 1
#define DCI_10WORD_FRAME   0x0090 << 1
#define DCI_11WORD_FRAME   0x00A0 << 1
#define DCI_12WORD_FRAME   0x00B0 << 1
#define DCI_13WORD_FRAME   0x00C0 << 1
#define DCI_14WORD_FRAME   0x00D0 << 1
#define DCI_15WORD_FRAME   0x00E0 << 1
#define DCI_16WORD_FRAME   0x00F0 << 1

#define DCI_1WORD_INTERRUPT 0x0000
#define DCI_2WORD_INTERRUPT 0x0400
#define DCI_3WORD_INTERRUPT 0x0800
#define DCI_4WORD_INTERRUPT 0x0C00

#define RECEIVE_NONE    0x0000
#define RECEIVE_ALL     0xFFFF
#define RECEIVE_SLOT0   0x0001
#define RECEIVE_SLOT1   0x0002
#define RECEIVE_SLOT2   0x0004
#define RECEIVE_SLOT3   0x0008
#define RECEIVE_SLOT4   0x0010
#define RECEIVE_SLOT5   0x0020
#define RECEIVE_SLOT6   0x0040
#define RECEIVE_SLOT7   0x0080
#define RECEIVE_SLOT8   0x0100
#define RECEIVE_SLOT9   0x0200
#define RECEIVE_SLOT10  0x0400
#define RECEIVE_SLOT11  0x0800
#define RECEIVE_SLOT12  0x1000
#define RECEIVE_SLOT13  0x2000
#define RECEIVE_SLOT14  0x4000
#define RECEIVE_SLOT15  0x8000

#define TRANSMIT_NONE   0x0000
#define TRANSMIT_ALL    0xFFFF
#define TRANSMIT_SLOT0  0x0001
#define TRANSMIT_SLOT1  0x0002
#define TRANSMIT_SLOT2  0x0004
#define TRANSMIT_SLOT3  0x0008
#define TRANSMIT_SLOT4  0x0010
#define TRANSMIT_SLOT5  0x0020
#define TRANSMIT_SLOT6  0x0040
#define TRANSMIT_SLOT7  0x0080
#define TRANSMIT_SLOT8  0x0100
#define TRANSMIT_SLOT9  0x0200 
#define TRANSMIT_SLOT10 0x0400
#define TRANSMIT_SLOT11 0x0800
#define TRANSMIT_SLOT12 0x1000
#define TRANSMIT_SLOT13 0x2000 
#define TRANSMIT_SLOT14 0x4000
#define TRANSMIT_SLOT15 0x8000


////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      CLEAR_INTERRUPT(), INTERRUPT_ACTIVE(),
//                      EXT_INT_EDGE()
//
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
//
// Constants used in other interrupt functions are:
#define INTR_GLOBAL               0x400
#define INTR_NORMAL               0x100
#define INTR_ALTERNATE            0x200
#define INTR_NESTING              0x300
#define INTR_LEVEL0               0x500
#define INTR_LEVEL1               0x501
#define INTR_LEVEL2               0x502
#define INTR_LEVEL3               0x503
#define INTR_LEVEL4               0x504
#define INTR_LEVEL5               0x505
#define INTR_LEVEL6               0x506
#define INTR_LEVEL7               0x507

#define INTR_CN_PIN              0x8000  // or in a PIN_xx constant

#define INT_OSCFAIL               1
#define INT_ADDRERR               2
#define INT_STACKERR              3
#define INT_MATHERR               4
#define INT_DMAERR                5
#define INT_EXT0                  6
#define INT_IC1                   7
#define INT_OC1                   8
#define INT_TIMER1                9
#define INT_IC2                   10
#define INT_OC2                   11
#define INT_TIMER2                12
#define INT_TIMER3                13
#define INT_SPI1                  14
#define INT_RDA                   15
#define INT_TBE                   16
#define INT_ADC1                  17
#define INT_EEPROM                18
#define INT_SI2C                  19
#define INT_MI2C                  20
#define INT_CNI                   21
#define INT_EXT1                  22
#define INT_IC7                   24
#define INT_IC8                   25
#define INT_OC3                   27
#define INT_OC4                   29
#define INT_TIMER4                31
#define INT_TIMER5                33
#define INT_EXT2                  35
#define INT_RDA2                  36
#define INT_TBE2                  37
#define INT_SPI2                  38
#define INT_CAN1                  39
#define INT_IC3                   41
#define INT_IC4                   42
#define INT_IC5                   44
#define INT_IC6                   46
#define INT_OC5                   48
#define INT_OC6                   50
#define INT_OC7                   51
#define INT_OC8                   52
#define INT_EXT3                  53
#define INT_EX4                   54
#define INT_CAN2                  56
#define INT_DCI                   62
#define INT_LOWVOLT               64

#list
