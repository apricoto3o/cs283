1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  It is a good choice for this application because it doesn't need break input at spaces, prevents buffer overflow, detects EOF, and makes sure that the input doesn't go over the buffer size.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  I needed to do this because it allows the memory to dynamically change because the buffer size is unknown and it helps to avoid stack overflow when the buffer gets really large. 


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  This is necessary because trimming the trailing and leading spaces ensures the correct parsing and execution of commands according to the assignment. If we don't trim some problems might arise like argument misinterpretation and issues with pipe/redirections.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  One example is, >, which redirects the output of whatever before the symbol to whatever is after it. A second example is, 2>, which redirects error messages to a log file. A third example is, <, which takes input from a text file instead of what the user types in. 

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:   Pipes are used to send output of a command as the input to another command, in doing so, allows you to have multiple commands chained together forming a pipeline. Redirection is used to read from or write to files instead of stdin/stdout

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  It's important to keep these separate in a shell because it can aid in debugging, allows for better redirection, and allowing the user to clearly see error messages. 

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  Our program should check the exit codes after executions. We should probably provide a way to merge them by uding redirection. When a command fails it should print out a message along with an exit  code. 
