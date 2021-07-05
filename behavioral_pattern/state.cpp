#include <iostream>

// 状态模式
// 意图: 允许一个对象在其内部状态改变时改变他的行为
// 参与者:
// Context: (环境， 定义相关的接口)
// State: (状态， 定义接口封装与Context的一个特定状态相关的行为)
// ConcreteState subclasses(具体状态子类， 实现接口)

// 应做成单例，否则有内存泄漏

class tcpConnection;
class tcpState
{
    public:
        tcpState() = default;
        virtual void listen(tcpConnection *){}
        virtual void send(tcpConnection *){}
        virtual void receive(tcpConnection *){}
        virtual void close(tcpConnection *){}
        virtual void getResult() {}
    protected:
        void changeState(tcpConnection *, tcpState *);
};

class tcpListen : public tcpState
{
    public:
        tcpListen() = default;
        virtual void listen(tcpConnection *) final;
        virtual void getResult() final;
};

class tcpEstablished : public tcpState
{
    public:
        tcpEstablished() = default;
        virtual void send(tcpConnection *) final;
        virtual void receive(tcpConnection *) final;
        virtual void close(tcpConnection *) final;
        virtual void getResult() final;
};

class tcpClosed : public tcpState
{
    public:
        tcpClosed() = default;
        virtual void listen(tcpConnection *) final;
        virtual void getResult() final;
};

class tcpConnection
{
    public:
        tcpConnection() : _state(new tcpListen())
        {
            
        }
        void listen()
        {
            _state->listen(this);
        }
        void send()
        {
            _state->send(this);
        }
        void receive()
        {
            _state->receive(this);
        }
        void close()
        {
            _state->close(this);
        }
        void getstate()
        {
            _state->getResult();
        }
    private:
        friend tcpState;
        void changeState(tcpState *s)
        {
            _state = s;
        }
        tcpState *_state;
};

void tcpState::changeState(tcpConnection *connection, tcpState *state)
{
    connection->changeState(state);
}

void tcpListen::listen(tcpConnection *connection)
{
    std::cout << "listen" << std::endl;
    changeState(connection, new tcpEstablished());
}

void tcpListen::getResult()
{
    std::cout << "current state: listen" << std::endl;
}

void tcpEstablished::send(tcpConnection *connection)
{
    std::cout << "send" << std::endl;
}

void tcpEstablished::receive(tcpConnection *connection)
{
    std::cout << "receive" << std::endl;
}

void tcpEstablished::close(tcpConnection *connection)
{
    std::cout << "close" << std::endl;
    changeState(connection, new tcpClosed());
}

void tcpEstablished::getResult()
{
    std::cout << "current state: Established" << std::endl;
}

void tcpClosed::listen(tcpConnection *connection)
{
    std::cout << "restart connection" << std::endl;
    changeState(connection, new tcpListen());
}

void tcpClosed::getResult()
{
    std::cout << "current state: closed" << std::endl;
}

int main()
{
    tcpConnection connect;
    connect.getstate();
    connect.listen();
    connect.getstate();
    connect.send();
    connect.receive();
    connect.close();
    connect.getstate();
    connect.listen();
    connect.getstate();
    return 0;
}