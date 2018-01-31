# Microcontroller-Framework

The goal is to create a template project to create applications independent of the microcontroller MCU.  By creating classes to abstract the specifics of the microcontroller one can more easily change between controllers without having to change the higher level application.

## Development

Currently working under OS X, but should easily work under Linux as well...

### OS X
  - [homebrew-avr](https://github.com/osx-cross/homebrew-avr/)
    - brew tap osx-cross/avr
      - brew install **avr-libc**
        - avr-libc, avr-binutils, avr-gcc
      - brew install **avrdude --with-usb**

### Ubuntu
  - Avrdude
    - apt-get install **avrdude**
    - apt-get install **gcc-avr binutils-avr avr-libc**
    - apt-get install **gdb-avr**

## Usage

Currently only setup for [Atmel](http://www.atmel.com/products/microcontrollers/avr/) Family MCUs! Simply use #if, #elfi, #else to seperate "MODEL" when expanding to other model families in makefile.

     run --program [/dev/tty.usbmodem1411]
     run --screen
       * starts screen tty

  - Test
     - Under work

## Implementation

Application code placement under *Application/*

  -Example: Run.cpp

    void Echo(object *value)
    {
      // debug echoes trace input char at a time

      intsys iptr = (intsys)value;  //cast objects
      int8 result = (int8)iptr;
      Trace::Instance()->Log(Trace::Info,"%s", result);
    }

    void Setup(void)
    {
      // your setup code goes here

      TRACE_LINE();  // example debug with line
    }

    void Loop(void)
    {
      // your runtime code goes here
      
      Trace::Instance()->Log(Trace::Info, "*");
      Delay(1000);
    }

Include your source in MakeFile under:

    \#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    \#### Application Code ####

    \#CPPSRC += \

    /Application/source/Run.cpp

    \#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Hierarchy

  This is the framework layout for usage in the application development

    |--
      |-- run
            * default arguments, used to save typing (and remembering) for repeat terminal operations
      |-- makefile
      |-- makefile.common
            * helper makefile functions, outside the boiler-plate atmel ardunio makefile
      |-- makefile.extra
            * files related to specific application using framework (i.e. not framework dependent)
      |-- System
            * Mostly C level microcontroller specifics (e.g. ports, pins, registry, ...) and common type definitions
      |-- Service
            * Design Pattern(s) and abstraction from the system level hardware specifics
      |-- External
            * 3rd party
      |-- Driver
            * Specifcs for attached hardware (e.g. sensors, contacts, motor, ...)
      |-- Component
            * Complementing software for operation (e.g. software counter, keyboard interaction, ...)
      |-- Core
            * Entry point with simple extern functions (see Implementation) as starting point for application specifics
      |-- Application
            * Everything (i.e. catch-all) for the application specific files (i.e. not framework dependent)

## Hardware

### Controllers
Currently only one, as others were deprecated.

Important: With threading minimum SRAM is 4kb!

  - **[ATmega2560](http://www.atmel.com/devices/atmega2560.aspx)**
    - Timer 1: Taken for [FreeRTOS](http://www.freertos.org/) operation.
    - If Instantiated:
      - Timer 2: Selected timer for controlling 2 PWM motors.
      - Timer 3: Selected timer for controlling 2 PWM servos.

### Boards
Currently board independent.

  - Note: ATmega2560 is being developed using [Arduino Mega 2560](http://arduino.cc/en/Main/arduinoBoardMega2560), but not dependent on the board.

### Shields/Hardware

  - UltrasonicSensor (model: Parallax HC-SR03/4)
    - Note: 4 pin connect Trig & Echo pins together to make 3 pin
  - 180 Degree Servo (model: Parallax #900-00005)

## Acknowledgement

[FreeRTOS](http://www.freertos.org/)
  
[Atmel](http://www.atmel.com/products/microcontrollers/avr/)
  
[Arduino](http://arduino.cc/)
  
## Thanks

[homebrew-avr](https://github.com/osx-cross/homebrew-avr/)

## License

LGPLv3

*The intent is to force the sharing of implementations of other microcontrollers into the framework as well as extending and bug fixes.  One does not need to produce source of application code that makes use of the Microcontroller-Framework.  Yet, one does need to open source any changes and/or additions to the Microcontroller-Framework.*
