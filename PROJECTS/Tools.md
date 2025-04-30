## **Custom "Gray Hat C" for C Language — Project-Based Track**
Here’s a tailored lineup of security tools and concepts we can build in **pure C**, often on Linux:

### **1. TCP Port Scanner**
- Use raw sockets to send SYN packets and listen for replies.
- Learn about packet crafting with `struct iphdr`, `struct tcphdr`.

### **2. Packet Sniffer**
- Build a basic sniffer using `libpcap` or raw sockets.
- Later, detect passwords or protocols like HTTP.

### **3. Process Injection Tool**
- Inject shellcode or shared libraries into other processes via `ptrace`.

### **4. Keylogger (for educational sandbox)**
- Capture keystrokes from `/dev/input` or via hooks (in X11 environments).

### **5. Custom Backdoor**
- Simple reverse shell in C that connects back to you.
- Learn persistence, obfuscation, and C2 (Command and Control) basics.

### **6. Exploit Simulation Lab**
- Create vulnerable C programs with buffer overflows.
- Write proof-of-concept exploits against them.

### **7. Malware Sandbox**
- Write a C program to analyze unknown binaries by tracking their system calls (`strace` style).

### **8. Rootkit (Userland)**
- Hide processes and files by intercepting libc functions like `readdir()`.

---
