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

void JNIChatClientListener::onMessageReceived(const Message& message)
{
    p_notifierProxy->notifyOnMessageReceived(message.getSenderId(), message.getMessageText());
}

void JNIChatClientListener::onConnected()
{
    p_notifierProxy->notifyOnConnected();
}

void JNIChatClientListener::onDisconnected()
{
    p_notifierProxy->notifyOnDisconnected();

}

void JNIChatClientListener::onLoginSuccessful(const UserDetails& userDetails)
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



void JNIChatClientListener::onContactsReceived(const std::vector<Contact>& contacts)
{
    int size = 0;

    char buffer[10000];

    for (Contact c: contacts)
    {
        int id = c.getId();

        memcpy(buffer + size, &id, sizeof(int));
        size += sizeof(int);

        size_t length = c.getUserName().length();
        memcpy(buffer + size,c.getUserName().c_str(), length);
        size += length;
        buffer[size++] = 0;

        length = c.getFirstName().length();
        memcpy(buffer + size, c.getFirstName().c_str(), length);
        size += length;
        buffer[size++] = 0;

        length = c.getLastName().length();
        memcpy(buffer + size, c.getLastName().c_str(), length);
        size += length;
        buffer[size++] = 0;

        //TODO: sent state
        bool isOnlone = c.getState() == ONLINE;
        memcpy(buffer + size,&isOnlone,sizeof(bool));
        size++;
    }
    LOG_DEBUG("Size:%d\n",size);

    p_notifierProxy->notifyOnContactsReceived(buffer, size);
}


void JNIChatClientListener::onContactStateChanged(int  contactId,
                                                         CONTACT_STATE state)
{
    //TODO: send enum
    p_notifierProxy->notifyOnContactStatusChanged(contactId,state == ONLINE);
}
