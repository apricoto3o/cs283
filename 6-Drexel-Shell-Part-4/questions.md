1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client detects that the output by using an EOF marker. The client has to loop on recv() until the entire message is received. If it weren't for this then the client will most likely be processing data that is incomplete. 

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

With TCP, message boundaries aren't preserved which means that an delimiter has to be used to mark command boundaries. If it weren't for this then the client will receive incomplete data or misinterpreted data. 

3. Describe the general differences between stateful and stateless protocols.

The general difference between stateful and stateless protocols is stateful retain session data which enables persistent interactions. While on the other hand stateless treats each and every request from the server independently, making it quicker and more scalable. 

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

UDP is used for its quickness when it comes to real time applications like video/content streaming. In events like this packet loss is acceptable to a certain degree. 

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

Sockets are used as the abstraction for network communcation. 
