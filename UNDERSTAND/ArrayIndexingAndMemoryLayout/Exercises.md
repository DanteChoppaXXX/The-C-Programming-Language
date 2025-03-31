Here are three exercises to help you understand **array indexing and memory layout** in C:  

---

### **Basic Level: Array Indexing & Pointers**  
**Task:**  
Write a program that:  
1. Declares an integer array of size `5` and initializes it with values `{10, 20, 30, 40, 50}`.  
2. Prints each element using both **array indexing** (`arr[i]`) and **pointer notation** (`*(arr + i)`).  
3. Prints the address of each element using both **&arr[i]** and **(arr + i)**.  

**Concepts Covered:** Array indexing, pointer notation, array element addresses.  

---

### **Intermediate Level: Understanding Row-Major Order in 2D Arrays**  
**Task:**  
Write a program that:  
1. Declares a `3x3` matrix (2D array) and initializes it with numbers `1` to `9`.  
2. Prints the matrix in **row-major order** using both **array notation (`arr[i][j]`)** and **pointer arithmetic (`*(*(arr + i) + j)`)**.  
3. Prints the memory addresses of all elements in the matrix to observe how they are stored in contiguous memory.  

**Concepts Covered:** Memory layout of 2D arrays, pointer arithmetic, row-major order storage.  

---

### **Advanced Level: Simulating 2D Arrays Using Pointers**  
**Task:**  
Write a program that:  
1. Asks the user for two integers, `rows` and `cols`, to define a **dynamic 2D array**.  
2. Allocates memory for the 2D array using an array of pointers (`int**`).  
3. Fills the array with values such that `arr[i][j] = i * j`.  
4. Prints the array using **array indexing** and **pointer arithmetic**.  
5. Properly deallocates memory using `free()`.  

**Concepts Covered:** Dynamic 2D arrays, pointer-to-pointer (`int**`), manual memory management.  

---

These exercises will help reinforce your understanding of **array indexing, memory layout, and pointer arithmetic**. Would you like hints or explanations for any of them? 🚀