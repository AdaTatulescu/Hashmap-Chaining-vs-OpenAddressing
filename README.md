# Hashmap-Chaining-vs-OpenAddressing
This repository contains a C implementation of a data management system for clothing articles using **Hash Tables**. The project focuses on handling data efficiently and managing memory rigorously.

## Core Concepts

The application implements a Hash Map to store articles based on their properties. An "Articol" (Article) consists of:
* **Name** (String)
* **Size** (Integer)
* **Color** (String)



## Key Features
* **Custom Hash Function**: Generates an index by summing the ASCII values of the name and color, then adding the size, all modulo the table size ($$m$$).
* **Collision Handling**: 
    * **Chaining**: Uses singly linked lists to store multiple articles at the same index.
    * **Open Addressing**: Included in testing logic to find the minimum table size where no collisions occur (Linear Probing).
* **Memory Management**: Full cleanup implementation to prevent memory leaks using `free()` for every dynamically allocated node.

## Functionality
The program supports different execution modes based on a `test` variable:
1. **Simple List**: Displays all articles in the order they were added.
2. **Hash Map View**: Displays articles organized by their calculated hash index.
3. **Collision Analysis**: Logic to calculate the minimum table size where Chaining and Open Addressing produce identical storage patterns.

## Compiling
Use any C compiler (like `gcc`):
```bash
gcc test.c -o inventory_manager
