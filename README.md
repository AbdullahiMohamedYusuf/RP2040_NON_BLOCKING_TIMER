# RP2040 Non-Blocking Timer (Polling Method)

This project demonstrates how to handle timing on the Raspberry Pi Pico (RP2040) without using blocking delay functions like `sleep_ms()` or `busy_wait()`. 

## 🎯 The Goal
In embedded systems (like a RISC-V CPU simulation), the processor must be free to handle logic, memory reads, and I/O constantly. This code uses **Hardware Timer Polling** to toggle LEDs while keeping the main `while(true)` loop completely free for other tasks.

## 🛠️ How it Works
Instead of stopping the CPU, we:
1. Read the current hardware time from `timer_hw->timelr`.
2. Set a future "timestamp" target (current time + 1,000,000µs).
3. Check every loop iteration if the current time has passed the target.
4. Execute the LED toggle only when the condition is met.

## 📟 Hardware Setup
- **PIN 13:** Green LED
- **PIN 14:** Yellow LED
- **PIN 15:** Red LED

## 🚀 Future Improvements
- [ ] Implement via Hardware Interrupts (Alarm IRQs).
- [ ] Transition LED brightness control to PWM Slices.
