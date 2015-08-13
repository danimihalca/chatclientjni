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
    void onLoginFailed(AUTH_STATUS reason);
    void onConnectionError();
    void onContactStateChanged(int contactId, USER_STATE state);
    void onContactsReceived(const std::vector<Contact>& contacts);

    void onRemovedByContact(int contactId);
    void onAddContactResponse(const std::string& userName,  ADD_STATUS status);
    bool onAddingByContact(const std::string& requester);

    void onRegisterUpdateResponse(REGISTER_UPDATE_USER_STATUS status);

private:
    JNIChatClientNotifierProxy* p_notifierProxy;

};

#endif // JNICHATCLIENTLISTENER_H

