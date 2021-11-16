# MyVibeCatcher

>“Honesty in small things is not a small thing.”
>> Robert C. Martin

You arrived on the GitHub of MyVibeCatcher, software that is created only by me, the author (duh), mainly to develop my own skills in embedded applications development, and hopefully to provide a better structured and more reliable version of application than previous, not documented one. Yep, there was first working prototype, written as I learnt the basics, without further investigation and planning, with additional soft written in Python for DAQ. But now i would like to cut the past with thick line, and with new experience and knowledge, make it work, make it right and make it fast.

## The origins

Project is inspired by problem that i've encountered in my very first job, when i was working in the company manufacturing mostly camshafts, but also the dynamometers.
There were some engines, which were vibrating so strong, that they were breaking drive shafts, and so there were some constructors who were working to minimize those vibrations. And so, the need to measure those vibrations, at least roughly, appeared.  

## Soft assumptions
Purpose of this software was to operate on STM32 controller, interfaced with two MPU6050 accelerometers, collect the data about the vibrations of engine working on the dyno and send it to computer. During the process of creation some GUI-things for PC appeared, including data acquisition, plotting, FFT, and measurement controls.

## Details
What i'm up to is to create a software working on STM32 which will be:
- Working on the state machine
- Controlled by PC application, through UART commands
- Interfacing two MPU6050 accelerometers through I2C
- Buffer data on SD Card, to minimize UART speed impact on sampling rate
- Signalize device state through LEDs or motherboard-like LED Codes

Probably more will appear here

And additionally, a Python-based GUI, which will be:
- Based on tkinter
- Managing serial connection
- Sending commands to STM32, and listening to incoming data
- Including data-plotting and analyzing "studio", by which i mean FFT, and probably some data filters

### Additionally
I'm going to try to use TDD methodology, successfully i hope. Which I expect will be quite difficult due to usage of HAL drivers.

I'll try to document important decisions, changes of assumptions and mine reflections in kind of devstories in appropriate direction in project body.

And btw, i'm going to use:

- STM32 CubeIde, cause that's where you develop code for STM32 basically,
- clang format, cause i want. And i can. And i want the code to be nicely formatted
- cppcheck, cause i want to get familiar with it, and i want to mumble angrily when he found something,
- pyCharm, because i already did
