# Smart-DC-Motor-Speed-Control-Using-Bluetooth-and-Microcontroller

---

## 📘 Project Overview

This project implements a system that uses a **Bluetooth serial mobile app** to regulate the speed of a **12V DC motor**, displaying that speed as a **percentage (0–100%)** on a **2x16 I2C LCD**. The system is built around an **MSP430 microcontroller**, which interprets inputs from the **HC-05 Bluetooth module** and controls the motor speed using **PWM (Pulse Width Modulation)**. 

The system ensures:
- Seamless Bluetooth communication
- Real-time LCD updates
- Accurate PWM speed modulation

---

## ✨ Key Features

- 📱 **Bluetooth-Controlled Input**: Adjust motor speed wirelessly via phone
- ⚡ **PWM-Based Motor Speed Control**: Fine-grained control over DC motor output
- 📟 **Real-Time I2C LCD Feedback**: User-friendly visual display of speed %
- 🧠 **Interrupt-Driven UART**: Efficient handling of serial input
- 🔁 **Timeout Safety**: Resets system on incomplete input or inactivity

---
## **Tools & Technologies**

🧠 Microcontroller	    : MSP430 LaunchPad

📶 Communication	      : HC-05 Bluetooth Module

⚡ Motor Control	      : 12V DC Motor, PWM via TimerB

📟 Display	            : 16x2 I2C LCD

💻 IDE & Simulations	  : Code Composer Studio, Energia

🧪 Debugging	          : Serial Monitor, LCD Feedback

🔌 Power	              : External 12V Source + 5V Regulator

----
## 🔄 **Pseudocode Summary**

```plaintext
Include necessary libraries for MSP430 and LCD display
Define PERIOD for PWM as 655
Declare external variables:
  - entered_value: stores user input
  - is_complete: flag for input status

Main Program:
- Stop watchdog timer

Configure Timer B0 for PWM:
- Up mode using ACLK
- Set max count value
- Start with 0% duty cycle
- Enable and clear interrupts

Configure Timer B1 for timeout detection

Configure UART (HC-05 Bluetooth):
- Set baud rate and clock source
- Configure RX pins
- Enable RX interrupt

Configure GPIO:
- P6.1 for PWM output (initial LOW)
- P2.1 for motor direction (initial HIGH)
- Disable high-impedance mode

Initialize LCD via I2C
Enable global interrupts
Display real-time speed % on LCD

```

----

## Final results

🎯 Achieved accurate real-time motor speed control (0–100%)

📲 Bluetooth app control was smooth with no lag or input delays

📟 LCD displayed correct % in real-time as user modified speed

🔄 PWM updated dynamically based on UART input

🧪 All test cases passed for min/max/invalid input

-----
## Wiring digram

![Wiringdiagram](https://github.com/nandiniyamani/Smart-DC-Motor-Speed-Control-Using-Bluetooth-and-Microcontroller/tree/main/wiringdiagram.png)

### Conclusion

This project successfully demonstrates a Bluetooth-controlled, real-time PWM system for motor speed modulation using the MSP430 microcontroller. With efficient UART communication, real-time LCD feedback, and robust PWM control, the system offers a practical, scalable solution for remote motor applications. The integration of interrupts, timeout logic, and I2C display handling makes it both reliable and user-friendly.
