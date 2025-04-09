## LimboChat Program Algorithm 🧠
#### (A Multi-Client Chat Server With User Authentication)
This is structured for clarity and completeness, with modular logic, clean separation of responsibilities, and a flow that encourages further expansion (like commands or encryption later).

---

## **High-Level Overview**
- A TCP server handles multiple clients.
- Clients must authenticate or register.
- Once authenticated, they can send messages.
- Messages are broadcasted to all connected clients, prefixed with the sender’s username.
- The server maintains a list of authenticated, connected clients.
- Disconnections and errors are handled gracefully.

---

## **Modules and Responsibilities**

### **1. Server Initialization**
- Create a socket.
- Bind it to a port.
- Set it to listen for incoming connections.
- Initialize a list/array of connected clients.
- Initialize a file or in-memory list for storing user credentials (username/password).

---

### **2. Main Loop with Multiplexing (using `select()` or `poll()`)**

#### **Loop Structure**
```
while true:
    clear and set up the file descriptor set (fd_set)
    add the server socket to the set
    add all active client sockets to the set
    call select() to wait for activity
```

#### **If Server Socket is Active**
- Accept new client connection.
- Add new client to the list of pending clients (unauthenticated).
- Send authentication prompt: `LOGIN` or `REGISTER`

#### **If Client Socket is Active**
- Read data from client.
- If client disconnected (recv returns 0 or error):
  - Remove client from the list.
  - Broadcast that the user has left (if authenticated).
  - Close socket and free memory.

---

## **3. Authentication Phase**
**Each new client must pass through this before being allowed to chat.**

### **Client chooses LOGIN or REGISTER:**

#### **If REGISTER**
- Server requests username and password.
- Check if username already exists in the credentials store.
  - If yes, notify client and re-prompt.
  - If no, store the new username/password securely.
  - Notify client of success and mark as authenticated.

#### **If LOGIN**
- Server requests username and password.
- Validate against stored credentials.
  - If match, mark client as authenticated and add username to active list.
  - If mismatch, re-prompt or disconnect after max attempts.

> **Note**: Store credentials in a secure file format. Use a hash if you're going for more security.

---

## **4. Authenticated Client Communication Phase**

### **Upon receiving a message:**
- Prefix message with `[username]:`
- Loop through all authenticated clients and send the message.
- Skip the sender if you don’t want to echo back.

---

## **5. Message Format Handling**
Clients should follow a basic protocol:

```
/login <username> <password>
/register <username> <password>
/msg <message>
/quit
```

On the server side:
- Parse commands based on prefix.
- `/msg` means it's a normal message.
- `/quit` triggers graceful disconnect.

---

## **6. Broadcast Function**
Reusable logic:
```
function broadcast(message, exclude_client=None):
    for each authenticated client:
        if client != exclude_client:
            send message
```

---

## **7. Client Tracking Structure**
Maintain a structure like:
```
struct Client {
    int socket_fd;
    char username[32];
    bool is_authenticated;
};
```

And store them in:
- `clients[]` — all connected clients.
- You can use a linked list or a dynamically growing array.

---

## **8. User Credentials Store**
Options:
- Plain text file: format like `username:hashed_password`
- On load: read into memory for faster lookup
- On new registration: append to file and memory

---

## **9. Error Handling & Cleanup**
- Handle all errors from `recv()`, `send()`, `accept()`
- On disconnection or error:
  - Remove client from list
  - Close socket
  - Free memory
  - Notify others

---

## **10. Optional Extras**
- Logging: Save all messages to a log file with timestamps.
- Commands: `/users` shows active users.
- Private messaging: `/pm <user> <message>`
- Encryption: Encrypt messages before sending (simple XOR to start).

---

## **Execution Plan**
Break this down into stages:

| Stage | Milestone |
|-------|-----------|
| 1     | Set up server socket and accept one client |
| 2     | Add authentication logic (login/register) |
| 3     | Allow only authenticated clients to send messages |
| 4     | Use `select()` to allow multiple clients |
| 5     | Implement message broadcasting |
| 6     | Track users, handle disconnects, and broadcast join/leave |
| 7     | Add optional features like private messages or commands |

---
