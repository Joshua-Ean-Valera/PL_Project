# Multi-Language Lexical Analyzer using Flex

## Overview

This project is a multi-language lexical analyzer built using **Flex**. It allows users to select between C, Python, or Java source code and performs lexical analysis (tokenization) based on the selected language.

---

## What is Flex?

**Flex** (Fast Lexical Analyzer Generator) is a tool for generating programs that perform lexical analysis. Lexical analysis is the process of converting a sequence of characters (source code) into a sequence of tokens, which are meaningful character strings such as keywords, identifiers, operators, and constants.

---

## What is Lexical Analysis?

Lexical analysis is the first phase of a compiler. It reads the source code and breaks it into tokens, which are then used by the parser to understand the structure and meaning of the code. Tokens include:
- **Keywords** (e.g., `if`, `while`)
- **Identifiers** (e.g., variable names)
- **Operators** (e.g., `+`, `==`)
- **Constants** (e.g., numbers, strings)
- **Delimiters** (e.g., `;`, `{`, `}`)
- **Punctuators** (e.g., `.`, `::`)

---

## Project Structure

- `main.c` - Main driver program to select language and run the corresponding lexer.
- `c_lexer.l` - Flex specification for C language.
- `python_lexer.l` - Flex specification for Python language.
- `java_lexer.l` - Flex specification for Java language.
- `input.c`, `input.py`, `input.java` - Sample input files for each language.

---

## How It Works

1. **User runs the main program** (`main.c`).
2. **User selects a language** (C, Python, or Java).
3. The main program:
    - Runs Flex on the corresponding `.l` file to generate a lexer.
    - Compiles the generated lexer using GCC.
    - Runs the lexer on the corresponding input file (`input.c`, `input.py`, or `input.java`).
4. **The lexer reads the input file and prints tokens** with their types.

---

## How to Run

### Prerequisites

- **Flex** and **GCC** must be installed and available in your system's PATH.
- Windows users: Use Command Prompt or PowerShell.

### Steps

1. **Navigate to the project directory:**
   ```
   cd C:\Users\Joshua Ean\Desktop\PL_Project
   ```

2. **Compile the main driver:**
   ```
   gcc main.c -o main
   ```

3. **Run the main program:**
   ```
   .\main
   ```

4. **Follow the prompt:**
   - Enter `1` for C, `2` for Python, or `3` for Java.
   - The program will process the corresponding input file and print the tokens.

---

## Example Output

For a simple Java input:
```java
public class Main {
    public static void main(String[] args) {
        int a = 5;
        if(a > 0) {
            a = a + 1;
        }
        System.out.println(a);
    }
}
```
The lexer might output:
```
KEYWORD(public)
KEYWORD(class)
IDENTIFIER(Main)
DELIMITERS({)
...
IDENTIFIER(System)
PUNCTUATORS(.)
IDENTIFIER(out)
PUNCTUATORS(.)
IDENTIFIER(println)
DELIMITERS(() 
IDENTIFIER(a)
DELIMITERS())
DELIMITERS(;)
DELIMITERS(})
```

---

## Notes

- You can modify `input.c`, `input.py`, or `input.java` to test different code samples.
- Each `.l` file can be extended to recognize more tokens as needed.
- The project demonstrates the basics of lexical analysis and how Flex can be used for different programming languages.

---
