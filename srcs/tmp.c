// /*
//
// int main(int argc, char **argv)
// {
// 	int status;
// 	int i;
//
// 	// arguments for commands; your parser would be responsible for
// 	// setting up arrays like these
//
// 	char *cat_args[] = {"cat", "scores", NULL};
// 	char *grep_args[] = {"grep", "Villanova", NULL};
// 	char *cut_args[] = {"cut", "-b", "1-10", NULL};
//
// 	// make 2 pipes (cat to grep and grep to cut); each has 2 fds
//
// 	int pipes[4];
// 	pipe(pipes); // sets up 1st pipe
// 	pipe(pipes + 2); // sets up 2nd pipe
//
// 	// we now have 4 fds:
// 	// pipes[0] = read end of cat->grep pipe (read by grep)
// 	// pipes[1] = write end of cat->grep pipe (written by cat)
// 	// pipes[2] = read end of grep->cut pipe (read by cut)
// 	// pipes[3] = write end of grep->cut pipe (written by grep)
//
// 	// Note that the code in each if is basically identical, so you
// 	// could set up a loop to handle it.  The differences are in the
// 	// indicies into pipes used for the dup2 system call
// 	// and that the 1st and last only deal with the end of one pipe.
//
// 	// fork the first child (to execute cat)
//
// 	if (fork() == 0)
// 	{
// 		// replace cat's stdout with write part of 1st pipe
//
// 		dup2(pipes[1], 1);
//
// 		// close all pipes (very important!); end we're using was safely copied
//
// 		close(pipes[0]);
// 		close(pipes[1]);
// 		close(pipes[2]);
// 		close(pipes[3]);
//
// 		execvp(*cat_args, cat_args);
// 	}
// 	else
// 	{
// 		// fork second child (to execute grep)
//
// 		if (fork() == 0)
// 		{
// 			// replace grep's stdin with read end of 1st pipe
//
// 			dup2(pipes[0], 0);
//
// 			// replace grep's stdout with write end of 2nd pipe
//
// 			dup2(pipes[3], 1);
//
// 			// close all ends of pipes
//
// 			close(pipes[0]);
// 			close(pipes[1]);
// 			close(pipes[2]);
// 			close(pipes[3]);
//
// 			execvp(*grep_args, grep_args);
// 		}
// 		else
// 		{
// 			// fork third child (to execute cut)
//
// 			if (fork() == 0)
// 			{
// 				// replace cut's stdin with input read of 2nd pipe
//
// 				dup2(pipes[2], 0);
//
// 				// close all ends of pipes
//
// 				close(pipes[0]);
// 				close(pipes[1]);
// 				close(pipes[2]);
// 				close(pipes[3]);
//
// 				execvp(*cut_args, cut_args);
// 			}
// 		}
// 	}
//
// 	// only the parent gets here and waits for 3 children to finish
//
// 	close(pipes[0]);
// 	close(pipes[1]);
// 	close(pipes[2]);
// 	close(pipes[3]);
//
// 	for (i = 0; i < 3; i++)
// 	wait(&status);
// }
// */
//
//
//
// /*
//
// int main()
// {
//   char *ls[] = {"ls", NULL};
//   char *grep[] = {"grep", "pipe", NULL};
//   char *wc[] = {"wc", NULL};
//   char **cmd[] = {ls, grep, wc, NULL};
//
//   loop_pipe(cmd);
//   return (0);
// }
//
//
//
// void    loop_pipe(char ***cmd)
// {
//   int   p[2];
//   pid_t pid;
//   int   fd_in = 0;
//
//   while (*cmd != NULL)
//     {
//       pipe(p);
//       if ((pid = fork()) == -1)
//         {
//           exit(EXIT_FAILURE);
//         }
//       else if (pid == 0)
//         {
//           dup2(fd_in, 0); //change the input according to the old one
//           if (*(cmd + 1) != NULL)
//             dup2(p[1], 1);
//           close(p[0]);
//           execvp((*cmd)[0], *cmd);
//           exit(EXIT_FAILURE);
//         }
//       else
//         {
//           wait(NULL);
//           close(p[1]);
//           fd_in = p[0]; //save the input for the next command
//           cmd++;
//         }
//     }
// }
//
//
//
//
//
// static void
// pipeline(char ***cmd)
// {
// 	int fd[2];
// 	pid_t pid;
// 	int fdd = 0;				/* Backup */
//
// 	while (*cmd != NULL) {
// 		pipe(fd);
// 		if ((pid = fork()) == -1) {
// 			perror("fork");
// 			exit(1);
// 		}
// 		else if (pid == 0) {
// 			dup2(fdd, 0);
// 			if (*(cmd + 1) != NULL) {
// 				dup2(fd[1], 1);
// 			}
// 			close(fd[0]);
// 			execvp((*cmd)[0], *cmd);
// 			exit(1);
// 		}
// 		else {
// 			wait(NULL); 		/* Collect childs */
// 			close(fd[1]);
// 			fdd = fd[0];
// 			cmd++;
// 		}
// 	}
// }
//
// */
//
// //ps aux | grep system | grep stat | grep daemon
// //ps aux | /usr/bin/grep system | /usr/bin/grep stat | /usr/bin/grep daemon
