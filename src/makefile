test : main.o EventLoopThreadPool.o httpHandler.o httpRequest.o httpResponse.o TcpServer.o TcpConnection.o Acceptor.o EventLoopThread.o EventLoop.o Epoll.o Timer.o Channel.o
	g++ -o test EventLoopThreadPool.o main.o httpHandler.o httpRequest.o httpResponse.o TcpServer.o TcpConnection.o Acceptor.o EventLoopThread.o EventLoop.o Epoll.o Timer.o Channel.o -std=c++11 -lpthread

main.o : main.cpp EventLoopThread.o EventLoop.h Channel.h
	g++ -c main.cpp -std=c++11 -lpthread
EventLoopThreadPool.o : EventLoopThreadPool.cpp EventLoopThreadPool.h EventLoopThread.h
	g++ -c EventLoopThreadPool.cpp -std=c++11 -lpthread
httpHandler.o : httpHandler.cpp httpHandler.h httpRequest.h httpResponse.h
	g++ -c httpHandler.cpp -std=c++11 -lpthread
TcpServer.o : TcpServer.cpp TcpServer.h Acceptor.h EventLoop.h TcpConnection.h
	g++ -c TcpServer.cpp -std=c++11 -lpthread
TcpConnection.o : TcpConnection.cpp TcpConnection.h EventLoop.h Channel.h
	g++ -c TcpConnection.cpp -std=c++11 -lpthread
Acceptor.o : Acceptor.cpp Acceptor.h Channel.h EventLoop.h
	g++ -c Acceptor.cpp -std=c++11 -lpthread
EventLoopThread.o : EventLoopThread.cpp EventLoopThread.h EventLoop.h
	g++ -c  EventLoopThread.cpp -std=c++11 -lpthread
EventLoop.o : EventLoop.cpp EventLoop.h Epoll.h Channel.h Timer.h
	g++ -c EventLoop.cpp -std=c++11 -lpthread
Epoll.o : Epoll.cpp Epoll.h Channel.h
	g++ -c Epoll.cpp -std=c++11
Timer.o : Timer.cpp Timer.h Channel.h
	g++ -c Timer.cpp -std=c++11
Channel.o : Channel.cpp Channel.h EventLoop.h
	g++ -c Channel.cpp -std=c++11
httpRequest.o : httpRequest.cpp httpRequest.h
	g++ -c httpRequest.cpp -std=c++11
httpResponse.o : httpResponse.cpp httpResponse.h
	g++ -c httpResponse.cpp -std=c++11
clean :
	rm test main.o  EventLoopThreadPool.o httpHandler.o httpRequest.o httpResponse.o TcpServer.o TcpConnection.o Acceptor.o EventLoopThread.o EventLoop.o Epoll.o Timer.o Channel.o

#g++ main.cpp TcpServer.cpp TcpServer.h TcpConnection.cpp TcpConnection.h Acceptor.cpp Acceptor.h EventLoopThread.cpp EventLoopThread.h EventLoop.cpp EventLoop.h Epoll.cpp Epoll.h Timer.cpp Timer.h Channel.cpp Channel.h -o test -std=c++11 -lpthread

