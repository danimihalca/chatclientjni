#ifndef JNICHATCLIENTLISTENER_H
#define JNICHATCLIENTLISTENER_H

#include <jni.h>

#include <ChatClient/IChatClientListener.hpp>

#include <Model/User.hpp>
#include <Model/Message.hpp>

class JNIChatClientNotifierProxy;

class JNIChatClientListener :
    public IChatClientListener
{
public:
    JNIChatClientListener(JNIChatClientNotifierProxy* notifierProxy);
    ~JNIChatClientListener();

    // Implements IChatClientListener interface
public:
    void onMessageReceived(const Message& message);
    void onConnected();
    void onDisconnected();
    void onLoginSuccessful(const UserDetails& userDetails);
    void onLoginFailed(const std::string& message);
    void onConnectionError();
    void onContactStateChanged(int contactId, CONTACT_STATE state);
    void onContactsReceived(const std::vector<Contact>& contacts);

private:
    JNIChatClientNotifierProxy* p_notifierProxy;

};

#endif // JNICHATCLIENTLISTENER_H

