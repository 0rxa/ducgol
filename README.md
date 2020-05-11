# Conways game of life
This is my implementation of Conways game of life 
in C with ncurses. It uses vim keys to navigate,
press space to toggle a cell and enter to iterate
the current generation. If you press tab the
generations iterate automatically until you
press tab again or quit the program by pressing
'q' or the escape button. If you specify a file
using the -f flag the game will load it as a
template. If any lines in the file are longer
than your terminal the game will ignore the extra
characters. If the file has more lines than your
terminal the game will ignore the extra lines.
