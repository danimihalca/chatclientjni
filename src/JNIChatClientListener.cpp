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
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnMessageReceived(message.getSenderId(), message.getMessageText());
}

//void JNIChatClientListener::onConnected()
//{
//    p_notifierProxy->notifyOnConnected();
//}

void JNIChatClientListener::onDisconnected()
{
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnDisconnected();

}

void JNIChatClientListener::onLoginSuccessful(const UserDetails& userDetails)
{
    LOG_DEBUG_METHOD;

    int size = 0;

    char buffer[10000];

    int id = userDetails.getId();
    memcpy(buffer + size, &id, sizeof(int));
    size += sizeof(int);

    size_t length = userDetails.getFirstName().length();
    memcpy(buffer + size, userDetails.getFirstName().c_str(), length);
    size += length;
    buffer[size++] = 0;

    length = userDetails.getLastName().length();
    memcpy(buffer + size, userDetails.getLastName().c_str(), length);
    size += length;
    buffer[size++] = 0;

    p_notifierProxy->notifyOnLoginSuccessful(buffer, size);

}

void JNIChatClientListener::onLoginFailed(AUTH_STATUS reason)
{
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnLoginFailed(static_cast<char>(reason));
}

void JNIChatClientListener::onConnectionError()
{
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnConnectionError();

}



void JNIChatClientListener::onContactsReceived(const std::vector<Contact>& contacts)
{
    LOG_DEBUG_METHOD;
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

        char state = static_cast<char>(c.getState());
        memcpy(buffer + size,&state,sizeof(char));
        size++;
    }
    LOG_DEBUG("Size:%d\n",size);

    p_notifierProxy->notifyOnContactsReceived(buffer, size);
}

void JNIChatClientListener::onRemovedByContact(int contactId)
{
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnRemovedByContact(contactId);
}

void JNIChatClientListener::onAddContactResponse(const std::string& userName, ADD_STATUS status)
{
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnAddContactResponse(userName,static_cast<char>(status));
}

bool JNIChatClientListener::onAddRequest(const std::string& requester)
{
    LOG_DEBUG_METHOD;
    return p_notifierProxy->notifyOnAddRequest(requester);
}

void JNIChatClientListener::onRegisterUpdateResponse(REGISTER_UPDATE_USER_STATUS status)
{
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnRegisterUpdateResponse(static_cast<char>(status));
}


void JNIChatClientListener::onContactStateChanged(int  contactId,
                                                         USER_STATE state)
{
    LOG_DEBUG_METHOD;
    p_notifierProxy->notifyOnContactStatusChanged(contactId, static_cast<char>(state));
}
