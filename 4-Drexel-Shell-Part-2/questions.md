1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**: We use fork because it allows for the creation of a child process from the parent process which runs a new command with execvp. Calling execvp directly would cause the process to be replaced by a new program, thus losing control of it. 

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If fork() fails it would mean that the system is out of process resources. In my inplementation exec_cmd() checks the return value of fork(). If it were to return a negative value then it returns ERR_EXEC_CMD, meaning there is an execution error. 

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  Execvp() looks for the command acorss all the directories that are in the PATH environment variable. It will continue to execute the command in each directory until it finds an executable that matches. 

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  The purpose of wait() is to ensure that the parent process waits for the child process to be completely done for it to move on. If wait() is not called then the child process may lead to resource leaks. 

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  WEXITSTATUS() provices the exit status of the child process which is returned by waitpid(). This is important because it plays a role in error handling, allowing the shell to see if a command fails or does whatever accordingly. 

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  build_cmd_buff() handles quoted arguments by checking for double quotes. If a double quote is found, it treats what is enclosed as a single argument. This is necessary because some commands have words that are separated with spaces and we want to treat them as a single argument instead of separate ones. 

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  My parsing logic has handling for spaces and strings with quotes. Some challenges were taking into account a few edge cases like having multiple spaces or random usage of quotes. 

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  The purpose of signals in a Linus system is it allows for processes to talk to each other through notifications to indicate various events. It differs from other IPC methods by being more lightweight and having the ability to interrupt a process right away. 

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGKILL: This signal is used to terminate a process while not allowing cleanup, SIGTERM: This signal is used to request a process to terminate gracefully, SIGINT: This signal is used for signal sending whenever the user presses control c, which ends whatever process is currently running. 

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  SIGSTOP would immediately pause a process and can not be caught or ignored. This is because it's designed to give admin control of the process, allowing for free pausing/control. 

