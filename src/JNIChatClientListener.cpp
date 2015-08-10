#include "JNIChatClientListener.hpp"

#include "JNIChatClientNotifierProxy.hpp"

#include <android/log.h>

#include <debug_utils/log_debug.hpp>

JNIChatClientListener::JNIChatClientListener(
    JNIChatClientNotifierProxy* notifierProxy) :
    p_notifierProxy(notifierProxy)
{
}

JNIChatClientListener::~JNIChatClientListener()
{
    delete p_notifierProxy;
}

void JNIChatClientListener::onMessageReceived(int                senderId,
                                              const std::string& message)
{
    p_notifierProxy->notifyOnMessageReceived(senderId, message);
}

void JNIChatClientListener::onConnected()
{
    p_notifierProxy->notifyOnConnected();
}

void JNIChatClientListener::onDisconnected()
{
    p_notifierProxy->notifyOnDisconnected();

}

void JNIChatClientListener::onLoginSuccessful()
{
    p_notifierProxy->notifyOnLoginSuccessful();

}

void JNIChatClientListener::onLoginFailed(const std::string& message)
{
    p_notifierProxy->notifyOnLoginFailed(message);

}

void JNIChatClientListener::onConnectionError()
{
    p_notifierProxy->notifyOnConnectionError();

}



void JNIChatClientListener::onContactsReceived(const Contacts& contacts)
{
    int size = 0;

    char buffer[10000];

    for (Contact c: contacts)
    {
        int id = c.getDetails().getId();

        memcpy(buffer + size, &id, sizeof(int));
        size += sizeof(int);

        size_t length = c.getUserName().length();
        memcpy(buffer + size,c.getUserName().c_str(), length);
        size += length;
        buffer[size++] = 0;

        length = c.getDetails().getFullName().length();
        memcpy(buffer + size, c.getDetails().getFullName().c_str(), length);
        size += length;
        buffer[size++] = 0;

        bool isOnlone = c.isOnline();
        memcpy(buffer + size,&isOnlone,sizeof(bool));
        size++;
    }
    LOG_DEBUG("Size:%d\n",size);

    p_notifierProxy->notifyOnContactsReceived(buffer, size);
}


void JNIChatClientListener::onContactOnlineStatusChanged(int  contactId,
                                                         bool isOnline)
{
    p_notifierProxy->notifyOnContactStatusChanged(contactId,isOnline);
}
