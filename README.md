Socket-Programming
===========

This repository includes the source code files for setting up a chat server & proxy server.

Chat-Server
----------
<br/>Compile the code for SERVER and CLIENT as two separate programs with the argument -lpthread 
<br/>
<br/>Example :  <br/> gcc -o server chat_server.c -lpthread
               <br/>    gcc -o client chat_client.c -lpthread
<br/><br/>
and then execute in the order
 <br/>&nbsp;&nbsp;&nbsp;&nbsp;./server \<port no\>
 <br/>&nbsp;&nbsp;&nbsp;&nbsp;./client \<server ip\> \<port no\>

Proxy-Server
---------
<br/>Compile the code
<br/>
<br/>Example :  <br/> gcc -o proxy proxy_server.c
<br/><br/>
and then execute by
<br/>&nbsp;&nbsp;&nbsp;&nbsp;./proxy \<port no\>
