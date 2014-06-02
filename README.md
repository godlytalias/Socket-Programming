Chat-Server
===========

This repository includes the source code files for setting up a chat server.
<br/>Compile the code for SERVER and CLIENT as two separate programs with the argument -lpthread 
<br/>
<br/>Example :  <br/> gcc -o server server.c -lpthread
               <br/>    gcc -o client client.c -lpthread
<br/><br/>
and then execute in the order
 <br/>  ./server \<port no\>
 <br/>  ./client \<server ip\> \<port no\>
