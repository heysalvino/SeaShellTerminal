# SeaShell

## Description
The Shell is a simple Unix-like command-line shell written in C. It provides basic command execution, input/output redirection, and support for a few built-in commands. This shell is designed for educational purposes and serves as a starting point for learning about shell functionality and basic process management in a Unix-like environment.

## Features
- Execute external commands.
- Support for basic built-in commands like `exit`, `pwd`, and `cd`.
- Input/output redirection using the `>` operator.
- Command-line interface with a prompt (`shell$`).

## Usage
1. Compile the Shell program by running the following command:

   ```bash
   gcc -o shell shell.c -lreadline
   ```

2. Execute the compiled program:

   ```bash
   ./shell
   ```

3. You'll see a welcome message and a prompt to enter commands. The built-in commands and basic external commands can be executed.

4. To exit the shell, type `exit`.

5. The `pwd` command displays the current working directory.

6. The `cd` command allows you to change the working directory, for example:

   ```shell
   shell$ cd /path/to/your/directory
   ```

7. Use the `>` operator for output redirection, for example:

   ```shell
   shell$ ls > output.txt
   ```

## File Structure
- `shell.c`: The main source code file for the Shell program.

## Notes
- The Shell program is a basic implementation and does not cover all the features of a full-fledged shell. It is meant for educational purposes and as a starting point for more advanced shell development.


Feel free to explore, modify, and learn from this simple shell implementation!
