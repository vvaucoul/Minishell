
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

	tab_exec = r_update_redirection_tab(tab_exec, envp, "<");
	tab_exec = r_get_tab_without_redirection(tab_exec);
	fd = open(tab_exec[1], O_RDONLY);
	tab_exec[1] = NULL;
	print_table(tab_exec, "tab exec redirection");
	if (!(pid = fork()))
	{
		dup2(fd, 0);
		close(fd);
		execve(tab_exec[0], tab_exec, NULL);
	}
	else
	{
		close(fd);
		waitpid(pid, &state, WUNTRACED);
	}
	return (0);
