# sockets-message-application

sockets message application with C and Java

---

## The program provides sequential communication between two clients which are in the same network

---

### Instructions

-   Execute makefile both in server and client folder
-   Change the ip-address that is provided by default "192.168.100.36" for the equipment you are going to use as a server.
-   Do the above step for each of the client files, client1 and client2
-   Next, run the server executable, secure client1 and client2
-   Write the first message to client1 and immediately the server will send your message to client 2, where client2 will send the message to the server and the server the message to client1 and so on.
-   Lastly, if you want to terminate the communication from any client you have, you just need to type exit

---

This program corresponds to the subject of Distributed Computing of the [National Polytechnic School](https://www.epn.edu.ec/)

The code shown below was developed taking as an example the one provided in the course and
[WhileTrueThenDream](https://github.com/WhileTrueThenDream/ExamplesCLinuxUserSpace/blob/master/server_secuencial.c), in addition to the solution that arises for the communication of clients through the server in [StackOverflow](https://stackoverflow.com/questions/41077820/c-language-sockets-a-chat-between-two-clients-using-one-server-as-middle-ma).

--- 
![client](https://github.com/Afkerian/sockets-message-application/blob/main/client.png)

![server](https://github.com/Afkerian/sockets-message-application/blob/main/server.png)

---

It is proposed to improve this application by connecting a Java graphical interface with C through sockets.


