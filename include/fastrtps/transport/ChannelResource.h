// Copyright 2018 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CHANNEL_RESOURCE_INFO_
#define CHANNEL_RESOURCE_INFO_

#include <memory>
#include <map>
#include <fastrtps/rtps/messages/MessageReceiver.h>
#include <fastrtps/utils/Semaphore.h>
#include <fastrtps/log/Log.h>

namespace eprosima{
namespace fastrtps{
namespace rtps{

#if defined(ASIO_HAS_MOVE)
    // Typedefs
	typedef asio::ip::udp::socket eProsimaUDPSocket;
	typedef asio::ip::tcp::socket eProsimaTCPSocket;
    typedef eProsimaUDPSocket& eProsimaUDPSocketRef;
    typedef eProsimaTCPSocket& eProsimaTCPSocketRef;

    // UDP
	inline eProsimaUDPSocket* getSocketPtr(eProsimaUDPSocket &socket)
    {
        return &socket;
    }
    inline eProsimaUDPSocket moveSocket(eProsimaUDPSocket &socket)
    {
        return std::move(socket);
    }
    inline eProsimaUDPSocket createUDPSocket(asio::io_service& io_service)
    {
        return std::move(asio::ip::udp::socket(io_service));
    }
    inline eProsimaUDPSocket& getRefFromPtr(eProsimaUDPSocket* socket)
    {
        return *socket;
    }
    // TCP
	inline eProsimaTCPSocket* getSocketPtr(eProsimaTCPSocket &socket)
    {
        return &socket;
    }
    inline eProsimaTCPSocket moveSocket(eProsimaTCPSocket &socket)
    {
        return std::move(socket);
    }
    inline eProsimaTCPSocket createTCPSocket(asio::io_service& io_service)
    {
        return std::move(asio::ip::tcp::socket(io_service));
    }
    inline eProsimaTCPSocket& getRefFromPtr(eProsimaTCPSocket* socket)
    {
        return *socket;
    }
#else
    // Typedefs
	typedef std::shared_ptr<asio::ip::udp::socket> eProsimaUDPSocket;
	typedef std::shared_ptr<asio::ip::tcp::socket> eProsimaTCPSocket;
    typedef eProsimaUDPSocket eProsimaUDPSocketRef;
    typedef eProsimaTCPSocket eProsimaTCPSocketRef;

    // UDP
    inline eProsimaUDPSocket getSocketPtr(eProsimaUDPSocket socket)
    {
        return socket;
    }
    inline eProsimaUDPSocket moveSocket(eProsimaUDPSocket socket)
    {
        return socket;
    }
    inline eProsimaUDPSocket createUDPSocket(asio::io_service& io_service)
    {
        return std::make_shared<asio::ip::udp::socket>(io_service);
    }
    inline eProsimaUDPSocket getRefFromPtr(eProsimaUDPSocket socket)
    {
        return socket;
    }
    // TCP
    inline eProsimaTCPSocket getSocketPtr(eProsimaTCPSocket socket)
    {
        return socket;
    }
    inline eProsimaTCPSocket moveSocket(eProsimaTCPSocket socket)
    {
        return socket;
    }
    inline eProsimaTCPSocket createTCPSocket(asio::io_service& io_service)
    {
        return std::make_shared<asio::ip::tcp::socket>(io_service);
    }
    inline eProsimaTCPSocket getRefFromPtr(eProsimaTCPSocket socket)
    {
        return socket;
    }
#endif

class ChannelResource
{
public:
    ChannelResource();
    ChannelResource(ChannelResource&& channelResource);
    ChannelResource(uint32_t rec_buffer_size);
    virtual ~ChannelResource();
    virtual void Clear();

    inline void SetThread(std::thread* pThread)
    {
        mThread = pThread;
    }

    std::thread* ReleaseThread();

    inline bool IsAlive() const
    {
        return mAlive;
    }

    inline virtual void Disable()
    {
        mAlive = false;
    }

    inline CDRMessage_t& GetMessageBuffer()
    {
        return m_rec_msg;
    }

protected:
    //!Received message
    CDRMessage_t m_rec_msg;
#if HAVE_SECURITY
    CDRMessage_t m_crypto_msg;
#endif

    std::atomic<bool> mAlive;
    std::thread* mThread;
};

class UDPChannelResource : public ChannelResource
{
public:
    UDPChannelResource(eProsimaUDPSocket& socket);
    UDPChannelResource(eProsimaUDPSocket& socket, uint32_t maxMsgSize);
    UDPChannelResource(UDPChannelResource&& channelResource);
    virtual ~UDPChannelResource();

    UDPChannelResource& operator=(UDPChannelResource&& channelResource)
    {
        socket_ = moveSocket(channelResource.socket_);
        return *this;
    }

    void only_multicast_purpose(const bool value)
    {
        only_multicast_purpose_ = value;
    };

    bool& only_multicast_purpose()
    {
        return only_multicast_purpose_;
    }

    bool only_multicast_purpose() const
    {
        return only_multicast_purpose_;
    }

#if defined(ASIO_HAS_MOVE)
    inline eProsimaUDPSocket* getSocket()
#else
    inline eProsimaUDPSocket getSocket()
#endif
    {
        return getSocketPtr(socket_);
    }

    inline void SetMessageReceiver(MessageReceiver* receiver)
    {
        mMsgReceiver = receiver;
    }

    inline MessageReceiver* GetMessageReceiver()
    {
        return mMsgReceiver;
    }

private:

    MessageReceiver* mMsgReceiver; //Associated Readers/Writers inside of MessageReceiver
    eProsimaUDPSocket socket_;
    bool only_multicast_purpose_;
    UDPChannelResource(const UDPChannelResource&) = delete;
    UDPChannelResource& operator=(const UDPChannelResource&) = delete;
};

class TCPChannelResource : public ChannelResource
{
enum eConnectionStatus
{
    eDisconnected = 0,
    eConnected,                 // Output -> Send bind message.
    eWaitingForBind,            // Input -> Waiting for the bind message.
    eWaitingForBindResponse,    // Output -> Waiting for the bind response message.
    eEstablished,
    eUnbinding
};

public:
    TCPChannelResource(eProsimaTCPSocket& socket, Locator_t& locator, bool outputLocator, bool inputSocket);

    TCPChannelResource(eProsimaTCPSocket& socket, Locator_t& locator, bool outputLocator, bool inputSocket,
        uint32_t maxMsgSize);
/*
    TCPChannelResource(TCPChannelResource&& channelResource);
*/
    virtual ~TCPChannelResource();

/*
    TCPChannelResource& operator=(TCPChannelResource&& channelResource)
    {
        mSocket = moveSocket(channelResource.mSocket);
        std::cout << "############ MOVE ASSIGN ###########" << std::endl;
        return *this;
    }
*/

    bool operator==(const TCPChannelResource& channelResource) const
    {
        return &mSocket == &(channelResource.mSocket);
    }

    void fillLogicalPorts(std::vector<Locator_t>& outVector);

    void EnqueueLogicalPort(uint16_t port);

	virtual void Disable() override;

	uint32_t GetMsgSize() const;

#if defined(ASIO_HAS_MOVE)
    inline eProsimaTCPSocket* getSocket()
#else
    inline eProsimaTCPSocket getSocket()
#endif
    {
        return getSocketPtr(mSocket);
    }

    std::recursive_mutex* GetReadMutex() const
    {
        return mReadMutex;
    }

    std::recursive_mutex* GetWriteMutex() const
    {
        return mWriteMutex;
    }

    inline void SetRTCPThread(std::thread* pThread)
    {
        mRTCPThread = pThread;
    }

    std::thread* ReleaseRTCPThread();

    inline bool GetIsInputSocket() const
    {
        return m_inputSocket;
    }

    inline void SetIsInputSocket(bool bInput)
    {
        m_inputSocket = bInput;
    }

    bool IsLogicalPortOpened(uint16_t port)
    {
        return std::find(mLogicalOutputPorts.begin(), mLogicalOutputPorts.end(), port) != mLogicalOutputPorts.end();
    }

    bool IsConnectionEstablished()
    {
        return mConnectionStatus == eConnectionStatus::eEstablished;
    }

    bool AddMessageReceiver(uint16_t logicalPort, MessageReceiver* receiver);

    MessageReceiver* GetMessageReceiver(uint16_t logicalPort);

    inline const Locator_t& GetLocator() const
    {
        return mLocator;
    }

    inline bool HasLogicalConnections() const
    {
        std::unique_lock<std::recursive_mutex> scoped(mLogicalConnectionsMutex);
        return mLogicalConnections > 0;
    }

    inline void AddLogicalConnection()
    {
        std::unique_lock<std::recursive_mutex> scoped(mLogicalConnectionsMutex);
        ++mLogicalConnections;
    }

    inline void RemoveLogicalConnection()
    {
        std::unique_lock<std::recursive_mutex> scoped(mLogicalConnectionsMutex);
        assert(mLogicalConnections > 0);
        --mLogicalConnections;
    }

protected:
    inline void ChangeStatus(eConnectionStatus s)
    {
        mConnectionStatus = s;
    }

    friend class TCPv4Transport;
    friend class TCPv6Transport;
    friend class RTCPMessageManager;
    friend class test_RTCPMessageManager;

private:
    Locator_t mLocator;
    bool m_inputSocket;
    bool mWaitingForKeepAlive;
    uint16_t mPendingLogicalPort; // Must be accessed after lock mPendingLogicalMutex
    uint16_t mNegotiatingLogicalPort; // Must be accessed after lock mPendingLogicalMutex
    uint16_t mCheckingLogicalPort; // Must be accessed after lock mPendingLogicalMutex
    std::thread* mRTCPThread;
    std::vector<uint16_t> mPendingLogicalOutputPorts; // Must be accessed after lock mPendingLogicalMutex
    std::vector<uint16_t> mLogicalOutputPorts;
    std::vector<uint16_t> mLogicalInputPorts;
    std::vector<uint16_t> mOpenedPorts;
    std::recursive_mutex* mReadMutex;
    std::recursive_mutex* mWriteMutex;
    std::map<uint16_t, MessageReceiver*> mReceiversMap;  // The key is the logical port.
    std::recursive_mutex mPendingLogicalMutex;
    std::map<uint16_t, uint16_t> mLogicalPortRouting;
	Semaphore mNegotiationSemaphore;
    eProsimaTCPSocket mSocket;
    eConnectionStatus mConnectionStatus;

    uint32_t mLogicalConnections; // Count of writers/readers using this socket.
    mutable std::recursive_mutex mLogicalConnectionsMutex;

    TCPChannelResource(const TCPChannelResource&) = delete;
    TCPChannelResource& operator=(const TCPChannelResource&) = delete;
};


} // namespace rtps
} // namespace fastrtps
} // namespace eprosima

#endif // CHANNEL_RESOURCE_INFO_