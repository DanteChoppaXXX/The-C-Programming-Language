## **Phase 1: Shell MVP Algorithm (Comprehensive)**

### **Goal**: Build a simple shell that can execute external commands (like `ls`, `echo`, etc.) with arguments.

---

### **Algorithm Breakdown**

#### **1. Setup the Main Loop**
- Start an infinite loop to keep the shell running.
- This loop will:
  - Display a prompt
  - Read input
  - Parse the command
  - Execute the command
  - Repeat

---

#### **2. Display a Prompt**
- Use `printf("$ ")` or a custom prompt.
- Flush the output buffer with `fflush(stdout)` to ensure it shows immediately.

---

#### **3. Read Input**
- Use `getline()` (preferred for dynamic buffer) or `fgets()` to read a line from `stdin`.
- If user presses `Ctrl+D` (EOF), exit the shell.

```c
ssize_t nread = getline(&line, &bufsize, stdin);
```

- Check if `nread == -1` to detect EOF or read failure.

---

#### **4. Strip the Trailing Newline**
- `getline()` includes the `\n`, so remove it.

```c
if (line[nread - 1] == '\n') {
    line[nread - 1] = '\0';
}
```

---

#### **5. Tokenize the Input**
- Split the line into **command and arguments**.
- Use `strtok()` or a custom parser.
- Store the tokens in a `char *argv[]` array.
- Null-terminate the array (important for `execvp()`).

```c
char *argv[MAX_ARGS];
argv[0] = strtok(line, " ");
argv[1] = strtok(NULL, " ");
...
argv[n] = NULL;
```

- Alternatively, loop and dynamically build the array.

---

#### **6. Check for Empty Input**
- If the line is just whitespace or empty, `continue` to the next loop.

---

#### **7. Fork a New Process**
- Use `fork()` to create a child process.

```c
pid_t pid = fork();
```

- If `pid < 0`: fork failed, print an error.
- If `pid == 0`: you're in the child process.
- If `pid > 0`: you're in the parent process.

---

#### **8. In Child Process – Execute the Command**
- Use `execvp(argv[0], argv)` to run the command.
- If `execvp()` fails, print an error and `exit(1)`.

```c
if (execvp(argv[0], argv) == -1) {
    perror("exec failed");
    exit(1);
}
```

---

#### **9. In Parent Process – Wait for Child**
- Use `wait(NULL)` to wait for the child to complete.
- Optional: capture and print exit status.

---

#### **10. Loop Again**
- After the child exits, go back to the beginning of the loop.

---

### **Extras You Can Add Even in Phase 1**
- Print error if user enters a command that doesn't exist
- Print a message when exiting
- Exit shell on `Ctrl+D` or typed `exit`

---

### **Pseudocode Version**

```c
loop forever {
    print "$ "
    read line from stdin
    if (EOF) break

    strip newline from line
    if (line is empty) continue

    tokenize line into argv[]
    if (argv[0] is NULL) continue

    pid = fork()
    if (pid == 0) {
        execvp(argv[0], argv)
        if failed, print error and exit
    } else if (pid > 0) {
        wait for child
    } else {
        print fork error
    }
}
```

---

### **Constants**
- `MAX_ARGS`: Set this to a reasonable value (e.g. 10 or 100)

### Quick reminder:

-	Don’t forget to link with -Wall -Wextra -g when compiling to catch warnings and debug more easily.
---
