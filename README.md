SilentArena Lite v0.1
========================

# SilentArena Lite v0.1

[🔽 Download SilentArena v0.1 (.tar.gz)](https://github.com/SilentPuck/SilentArena/releases/download/v0.1/SilentArena_v0.1.tar.gz)  
Released for educational use. Safe by design.

> A safe simulation of ransomware-like behavior — built to teach, not to destroy.

---

## 🧠 What is this?

**SilentArena Lite** is a training environment that simulates how a basic file encryption malware might operate — without any real danger.

- It only affects files inside the folder `victim_data/`
- It does not delete or overwrite your real files
- It logs its actions in `attack.log`
- It includes a simple `scanner` to analyze traces

---

## 🧪 What it does

- The `encryptor` finds files inside `victim_data/`
- Applies XOR encryption (`0x5A`) to each file
- Creates `.locked` encrypted versions
- Writes log entries for each encrypted file

---

## 🚀 How to run

⚠️ Always run tools from the **root of the project folder**, not from inside `build/`!

Example:

```bash
./build/encryptor --simulate
./build/scanner
./build/decryptor
```

You’ll see:
- `.locked` files in `victim_data/`
- `attack.log` with timestamps and actions

---

## 🔍 What the `scanner` does

```bash
./build/scanner
```

- Scans for `.locked` files
- Shows how many were encrypted
- Displays contents of `attack.log`

---

## 🔓 How to decrypt

```bash
./build/decryptor
```

- Finds all `.locked` files
- Reverses the XOR encryption
- Restores the original filenames

---

## ⚠️ Is this dangerous?

No. Absolutely not.

- It does not affect your real system
- It does not encrypt anything outside `victim_data/`
- It requires `--simulate` to run
- The source code is open and safe to inspect

---

## 💬 Why does this exist?

Because learning to defend means learning how attacks behave.  
This is not a toy. It’s a tool to think like an attacker — and train like a defender.

---

## 💰 Want more realism?

This version is intentionally limited for safety and clarity.

If you found it useful and want to see deeper, more realistic simulations  
(such as auto-delete, stealth, obfuscated logs)...

→ **support the project**:

XMR: 46vt374N1tRduTQZFodskNbqygTnkFFo3SLJ8btmGkbyFpib65qFVMycF2PsDFpr1dUAv77JnpV5669HnRnULJ2Y6JkuFiS

BTC: bc1q7jrq0u4yu6s5jgtrwkmwjaqhttam3ch3ura4aw

> I won't promise anything. But I might just build more...

---

## 🕶 Author

SilentPuck  
Forged in silence. Written in C.  
Tools for invisible people.

https://x.com/SilentPuck  
https://github.com/SilentPuck
