# MIDI Organ Key Scanner  
A custom MIDI overlay for church organs using Arduino Micro and CD74HC4067 multiplexers

## 🎹 Overview
This project is a hardware–software system designed to read the current state of keys in a traditional church organ and convert them into USB‑MIDI messages.  
The goal is to create a **non-invasive MIDI overlay**, allowing the organ to function as a fully playable MIDI keyboard without modifying its internal mechanics.

The system continuously scans the state of all keys using mechanical limit switches and sends corresponding **Note On/Note Off** messages via native USB‑MIDI.

---

## 🛠️ Hardware Used
- **Arduino Micro**  
  - Chosen for its native USB‑MIDI support  
  - Low latency and stable communication with DAWs

- **CD74HC4067 (x4)**  
  - 16‑channel analog/digital multiplexers  
  - Used to expand the number of readable inputs  
  - Allows scanning 58 keys using only a few Arduino pins

- **Mechanical limit switches (krańcówki)**  
  - Mounted under each organ key  
  - Provide a simple and reliable ON/OFF signal  
  - Work with internal pull‑ups for noise‑resistant readings

---

## 🎛️ Features
- Reads **58 keys** from a church organ manual  
- Sends MIDI notes from **C2 (36)** to **A6 (93)**  
- Native USB‑MIDI (no serial-to-MIDI converters required)  
- Debounce-free scanning using digital logic and pull‑ups  
- Modular design — easy to expand to more manuals or pedals  
- Fully compatible with DAWs such as Ableton, Logic, FL Studio, etc.

---

## 🔌 How It Works
1. Each organ key presses a **limit switch**.
2. The switches are connected to four **CD74HC4067 multiplexers**.
3. Arduino Micro cycles through all MUX channels and reads their states.
4. When a key changes state:
   - `LOW` → **Note On**
   - `HIGH` → **Note Off**
5. A USB‑MIDI message is sent to the computer.

This creates a responsive and reliable MIDI controller while preserving the original organ mechanics.


