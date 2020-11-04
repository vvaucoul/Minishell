#!/bin/bash
make re
valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./minishell
