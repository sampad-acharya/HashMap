# HashMap Implementation in C++

This is a basic implementation of **HashMap / unordered_map** in C++ using `std::vector` and dynamic memory allocation.  

---

## 📂 Benchmark Information
The `benchmark` folder contains benchmark results for the **insert** operation.  
More benchmark tests will be added soon.  

---

## 📊 Results of Insert Benchmark

### HashMap built using `std::vector`

**Number of operations: 100**  
- HashMap Container `[]` operator time per operation: `2.25458e-06s`  
- HashMap Dynamic Memory `[]` operator time per operation: `1.60458e-06s`  
- `unordered_map []` operator time per operation: `9.65e-07s`  

**Number of operations: 100000**  
- HashMap Container `[]` operator time per operation: `7.52087e-07s`  
- HashMap Dynamic Memory `[]` operator time per operation: `6.24375e-07s`  
- `unordered_map []` operator time per operation: `3.68396e-07s`  

**Number of operations: 10000000**  
- HashMap Container `[]` operator time per operation: `1.21402e-06s`  
- HashMap Dynamic Memory `[]` operator time per operation: `1.32808e-06s`  
- `unordered_map []` operator time per operation: `1.21972e-06s`  

**Number of operations: 100000000**  
- HashMap Container `[]` operator time per operation: `2.25889e-06s`  
- HashMap Dynamic Memory `[]` operator time per operation: `4.97214e-06s`  
- `unordered_map []` operator time per operation: `4.00163e-06s`  

---

### HashMap built using Dynamic Memory

**Number of operations: 100**  
- HashMap Container `insert` time per operation: `7.7042e-07s`  
- HashMap Dynamic Memory `insert` time per operation: `6.1e-07s`  
- `unordered_map insert` time per operation: `4.5041e-07s`  

**Number of operations: 100000**  
- HashMap Container `insert` time per operation: `7.2994e-07s`  
- HashMap Dynamic Memory `insert` time per operation: `6.17517e-07s`  
- `unordered_map insert` time per operation: `3.6857e-07s`  

**Number of operations: 10000000**  
- HashMap Container `insert` time per operation: `1.09762e-06s`  
- HashMap Dynamic Memory `insert` time per operation: `1.21919e-06s`  
- `unordered_map insert` time per operation: `1.194
