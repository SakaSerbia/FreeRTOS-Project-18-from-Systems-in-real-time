# About the project
This work present project number 18 for the school year 2016/2017 in [the Systems in real time](http://tnt.etf.bg.ac.rs/~oe4srv) in the 4th year, Department of Electronics, School of Electrical Engineering, University of Belgrade. The basic idea for this work demonstrating the acquired knowledge from lab exercises and lectures about FreeRTOS (Real Time Operating System), Code Composer Studio 7 etc.

# Text of the project 
Realize the system that starts acquiring from channels A14 and A15 for every 100 ms with software timer.

In an interrupt routine, the conversion results are entered in line with Queue, which is protected by mutex, so when someone wants to read a message from the line, he must first take a mutex. The message should contain the information about the channel that was evaluated and the 12 bit value that was read.

The tasks xTask1 and xTask2 read messages from the line, where xTask1 reads only messages related to channel A14, and xTask2 reads only messages related to channel A15.

Therefore, it is necessary for the tasks to first check what is at the top of the line (peek), so if it finds that the message is intended for them, they then read the message and remove it from the line (receive).

Task xTask1 counts the average of the last 16 received bounces and immediately into the mailbox (Queue length 1) with overwrite.

Task xTask2 counts the average of the last 32 received bounces and immediately into the mailbox (Queue length 1) with overwrite.

At the push of the button S1 and S2, the task xTask3 reads the corresponding mailbox and displays the measured mean value on the multiplexed LED display.

# Acknowledgment
I dedicate this project to **Nikolina**, whose notebooks I copied during the entire study. My real friend thank you from the heart for all.

# Block scheme of the system
![slika1](https://user-images.githubusercontent.com/16638876/27803714-33906526-602b-11e7-9d4c-93b166e2d2ea.jpg)

# Synchronization and communication mechanism
![slika2](https://user-images.githubusercontent.com/16638876/27803757-7253a278-602b-11e7-920e-aceb0fdb86c7.jpg)

# Time diagram for task execution and interrupt routines
![slika3](https://user-images.githubusercontent.com/16638876/27803771-85bffa64-602b-11e7-9eb7-c5cbd7b0f5cd.jpg)

# MSP430F5438A 
![received_10213299826712440](https://user-images.githubusercontent.com/16638876/27803975-a75d2cf4-602c-11e7-9a33-6f38611dc4fa.jpeg)

