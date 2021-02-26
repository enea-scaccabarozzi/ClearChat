# ClearChat

A simple program written in c++ that uses linux sockests to enable communication between two different machines, and RSA security to guarantee a safe and strong cryptation



------



### Dependecies

In order to compile and install this program it is necessary downloads some depencencies:

- **g++** : To compile the source code

  You can easily found it in every repository.

  *for example in debian-based distros:*

  ```bash
  sudo apt-get install g++
  ```

- **CryptoPP libs**: In order to crypt correctly the connection and the messages

  Also in this case this libraries are supported by most of the famous repository

  *for example in debian-based distros:*

  ```bash
  sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils.
  ```

  

------



### Installation

You can easily this program downloading [or cloning] this repository.

Now you have to enter in your new directory

```bash
cd ClearChat
```

And if you run the make command  with root privileges g++ will compile the source file and create the two executables

```bash
sudo make
```

Now wait for a few seconds and ClearChat is correctly installed on your machine



------



### Usage

In order to start a chat you have first of all open the server, to do it simply run:

> $ CLRchatServer 22222

where CLRchatServer is the name of the program and 22222 is the number of the port where listen for incoming connection.

At this point go to another machine and start the client program:

> CLRchatClient 127.0.0.1 22222

Where CLRchatClient is the name program, 127.0.0.1 is the server ip address [in this case localhost] and 22222 is the server port opened



At this point, after an initial handshacke, you'll be abled to chat correctly!



------



##### If you find a bug please open an issue on [github](https://github.com/enea-scaccabarozzi/ClearChat)