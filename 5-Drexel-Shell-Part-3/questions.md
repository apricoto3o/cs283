1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

The shell ensures that all child processes complete before it accepts new input by taking advantage of waitpid() which is called in a loop for every child process it creates when the program executes the piped commands. If waitpid() is not called then child processes would consume system resources which might lead to unexpected/unwanted behavior of the program.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

It is necessary because the function facilitates command piping so its necessary to close unused pipe ends after calling dup2() to help avoid any descriptor leaks. If pipes are left open then it could lead to processes waiting for input indefinitely eventually resulting in resource exhaustion. 

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

Cd is implemented as a built-in command because it facilitates directory changes across the entire process. If cd was implemented as an external command then it would only change the working directory within the chiid process and wouldn't affect the parent shell. 

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

I would probably allow the shell to dynamically allocate memory for pipes. To do so, I would defintely have to use malloc() to allocate the space needed for the number of pipes and processes. While doing this would be nice, there are a few trade-offs such as additional memory management and more error handling in the effort to avoid memory leaks. 
