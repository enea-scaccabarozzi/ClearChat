all: CLRchatClient CLRchatServer
	@echo "[>>]  Creating trigger command for client..."
	@echo alias CLRchatClient='/etc/ClearChat/Client/CLRchatClient' >> ~/.bashrc
	@echo "[>>]  Creating trigger command for server..."
	@echo alias CLRchatServer='/etc/ClearChat/Server/CLRchatServer' >> ~/.bashrc
	@echo "[VV]  Reopen the shell to use the program"

CLRchatClient : Client.o
	@echo "[>>]  Creating directory system..."
	@mkdir /etc/ClearChat/Client -p
	@echo "[>>]  Unioning objects file..."
	@echo "[>>]  Creating Client executable..."
	@g++ -o CLRchatClient Client.o CLICrypt.o CLISocket.o -l:libcryptopp.a
	@echo "[!!]  Deleting objects file..."
	@rm -f *.o
	@echo "[>>]  Moving Client executable..."
	@mv ./CLRchatClient /etc/ClearChat/Client
	@echo "[VV]  Installation of client part completed correctly"

Client.o : ./Client/Client.cpp CLICrypt.o CLISocket.o
	@echo "[>>]  Compiling Client.o..."
	@g++ -c -o Client.o ./Client/Client.cpp

CLICrypt.o : ./Client/Crypt/Crypt.cpp ./Client/Crypt/Crypt.h
	@echo "[>>]  Compiling CLICrypt.o..."
	@g++ -c -o CLICrypt.o ./Client/Crypt/Crypt.cpp -l:libcryptopp.a

CLISocket.o : ./Client/Socket/Socket.cpp ./Client/Socket/Socket.h
	@echo "[>>]  Compiling CLISocket.o..."
	@g++ -c -o CLISocket.o ./Client/Socket/Socket.cpp




CLRchatServer : Server.o
	@echo "[>>]  Creating directory system..."
	@mkdir /etc/ClearChat/Server -p
	@echo "[>>]  Unioning objects file..."
	@echo "[>>]  Creating Server executable..."
	@g++ -o CLRchatServer Server.o SRVCrypt.o SRVSocket.o -l:libcryptopp.a
	@echo "[!!]  Deleting objects file..."
	@rm -f *.o
	@echo "[>>]  Moving Server executable..."
	@mv ./CLRchatServer /etc/ClearChat/Server
	@echo "[VV]  Installation of Server part completed correctly"

Server.o : ./Server/Server.cpp SRVCrypt.o SRVSocket.o
	@echo "[>>]  Compiling Server.o..."
	@g++ -c -o Server.o ./Server/Server.cpp

SRVCrypt.o : ./Server/Crypt/Crypt.cpp ./Server/Crypt/Crypt.h
	@echo "[>>]  Compiling CLICrypt.o..."
	@g++ -c -o SRVCrypt.o ./Server/Crypt/Crypt.cpp -l:libcryptopp.a

SRVSocket.o : ./Server/Socket/Socket.cpp ./Server/Socket/Socket.h
	@echo "[>>]  Compiling CLISocket.o..."
	@g++ -c -o SRVSocket.o ./Server/Socket/Socket.cpp
