
/*
int main(int argc, char *argv[]) {
    int fd0;
    char *args[3] = { NULL };
    args[0] = argv[1];

    if (strcmp(argv[2], "<") == 0) {
        if ((fd0 = open(argv[3], O_RDONLY)) < 0) {
            perror("open");
            exit(1);
        }

        dup2(fd0, STDIN_FILENO);
        close(fd0);

        execvp(argv[1], args);

    } else {
        args[1] = argv[2];
        execvp(argv[1], args);
    }

    return EXIT_SUCCESS;
}
*/


/*

    int main(int argc, char **argv) {
      int fd, status;
      pid_t child_pid;
      char c;
      char *args[2] = {"/opt/prog", NULL};

      if (argc != 2)
        exit(1);
      fd = open(argv[1], O_RDONLY);
      child_pid = fork();
      if (child_pid == 0) {
        if (dup2(fd, STDIN_FILENO) == -1) {
          perror("dup2");
          return (EXIT_FAILURE);
        }
        close(fd);
        execve(args[0], args, NULL);
      }
      if (child_pid != 0) {
        close(fd);
        wait(&status);
      }
      return (EXIT_SUCCESS);
    }
	*/
