#ifndef JNICHATCLIENTLISTENER_H
#define JNICHATCLIENTLISTENER_H

#include <jni.h>

#include <ChatClient/IChatClientListener.hpp>

class JNIChatClientNotifierProxy;

class JNIChatClientListener :
    public IChatClientListener
{
public:
    JNIChatClientListener(JNIChatClientNotifierProxy* notifierProxy);
    ~JNIChatClientListener();

    // Implements IChatClientListener interface
public:
    void onMessageReceived(int senderId, const std::string& message);
    void onConnected();
    void onDisconnected();
    void onLoginSuccessful();
    void onLoginFailed(const std::string& message);
    void onConnectionError();
    void onContactOnlineStatusChanged(int contactId, bool isOnline);
    void onContactsReceived(const Contacts& contacts);

private:
    JNIChatClientNotifierProxy* p_notifierProxy;

};

#endif // JNICHATCLIENTLISTENER_H

