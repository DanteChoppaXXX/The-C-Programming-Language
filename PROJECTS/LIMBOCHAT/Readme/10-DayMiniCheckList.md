## **10-Day Mini Checklist for LimboChat Program**

---

### **Day 1 – Setup & Skeleton Server**
- ✅ Create folder and organize files (`server.c`, `client.c`, `users.txt`, etc.)
- ✅ Initialize TCP server: `socket()`, `bind()`, `listen()`
- ✅ Accept one client connection
- ✅ Basic send/recv loop with client
- ✅ Clean exit on `Ctrl+C` (optional)

---

### **Day 2 – One Client, Authentication System**
- [ ] Send "Login or Register?" prompt
- [ ] Handle `/login <user> <pass>` and `/register <user> <pass>`
- [ ] Create `users.txt` to store credentials (plain text or hashed)
- [ ] Check credentials on login
- [ ] Prevent duplicate usernames during registration
- [ ] Allow only authenticated users to chat

---

### **Day 3 – Support Multiple Clients (with `select()`)**
- [ ] Replace blocking `accept()`/`recv()` with `select()`
- [ ] Track multiple client sockets
- [ ] Handle new client connections and data from existing clients
- [ ] Disconnect idle/closed clients gracefully

---

### **Day 4 – Client Tracking and Messaging Logic**
- [ ] Create `struct Client` to store socket, username, and auth status
- [ ] Maintain a dynamic list or array of connected clients
- [ ] After successful auth, allow client to send chat messages
- [ ] Broadcast messages to all other authenticated clients
- [ ] Prefix messages with `[username]:`

---

### **Day 5 – Join/Leave Notifications + Cleanup**
- [ ] When user connects and authenticates, broadcast: `User [X] joined`
- [ ] On disconnect, broadcast: `User [X] left`
- [ ] Cleanly remove clients on disconnect
- [ ] Free memory / remove client from list

---

### **Day 6 – Add Basic Commands**
- [ ] Implement `/users` command to list online users
- [ ] Implement `/quit` to let client disconnect intentionally
- [ ] Implement `/help` for available commands (optional)

---

### **Day 7 – Error Handling & Robustness**
- [ ] Handle bad input (e.g., malformed login/register)
- [ ] Protect against crashing on invalid socket data
- [ ] Retry authentication on failure (limit attempts?)
- [ ] Check for file read/write errors (user DB)

---

### **Day 8 – Optional Extras**
- [ ] Log chat messages to `chat.log`
- [ ] Add timestamps (e.g., `[12:34] [user]: msg`)
- [ ] Add basic encryption (Caesar cipher or XOR)
- [ ] Refactor repeated logic into helper functions

---

### **Day 9 – Testing & Refinement**
- [ ] Open multiple terminal clients and test:
  - Auth
  - Broadcasts
  - Disconnects
  - Edge cases (duplicate usernames, invalid passwords)
- [ ] Optimize file handling
- [ ] Add comments and clean code

---

### **Day 10 – Final Touches & Demo**
- [ ] Final test and polish
- [ ] Document how to run the server and client
- [ ] Optional: Create a README
- [ ] Optional: Record a short demo video or write usage notes
- [ ] Celebrate—you built something solid and powerful in C!

---
