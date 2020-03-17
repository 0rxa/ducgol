# Conways game of life
This is my implementation of Conways game of life 
in C with ncurses. It uses vim keys to navigate,
press space to toggle a cell and enter to iterate
the current generation. If you press tab the
generations iterate automatically until you
press tab again or quit the program by pressing
'q' or the escape button.

To compile:
```sh
gcc -lncurses main.c game.c -o main
```
