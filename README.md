# Microcontroller-Framework

The goal is to create a template project to create applications independent of the microcontroller.  By creating classes to abstract the specifics of the microcontroller one can more easily change between controllers without having to change the higher level application.

## Development

Currently working under OS X, but should easily work under Linux as well...

### OS X
  - [homebrew-avr](https://github.com/larsimmisch/homebrew-avr)
    - brew tap larsimmisch/avr
      - brew install **avrdude --with-usb**
      - brew install avr-libc
        - **avr-libc, avr-binutils, avr-gcc**

## Usage

  - Build
     - build.sh
       - make clean && make MODEL=atmega2560 CLOCK=16000000
  - Deploy
     - Example: avrdude -F -c arduino -p m328 -P /dev/tty.usbmodem1421 -U flash:w:Core.hex
  - Test
     - Under work
     - Example: make -TEST=1

## Implementation

Functions defined to activate at top level */Core/Application.hpp*.  

  -Example: Run.cpp

    #include <stdio.h>
    #include <stdarg.h>
    #include <string.h>

    #include "System/include/Types.h"

    #include "Service/include/Trace.hpp"
    using namespace Service;

    #include "Core/include/Application.hpp"
    using namespace Core;

    void Setup(void)
    {

    }

    void Loop(void)
    {
      Trace::Instance()->Log(Trace::Info, "@")
    }


Include your source in MakeFile under:

  
    \#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    \#### Application Code ####

    \#CPPSRC += \

    /Application/source/Run.cpp 

    \#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Hardware

### Controllers
Currently only one, as others where deprecated.

Important: With threading minimum SRAM is 4kb!

  - **ATmega2560**

### Boards
Currently board independent.

  - Note: ATmega2560 is being developed using [Arduino Mega 2560](http://arduino.cc/en/Main/arduinoBoardMega2560), but not dependent on the board.

### Shields/Hardware
Comming Soon!

## Credits

[FreeRTOS](http://www.freertos.org/)

[Atmel](http://www.atmel.com/products/microcontrollers/avr/)
  
[Arduino](http://arduino.cc/)

## License

LGPLv3

*The intent is to force the sharing of implementations of other microcontrollers into the framework as well as extending and bug fixes.  One does not need to produce source of application code that makes use of the Microcontroller-Framework.  Yet, one does need to open source any changes and/or additions to the Microcontroller-Framework.*