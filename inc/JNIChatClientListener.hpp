#ifndef JNICHATCLIENTLISTENER_H
#define JNICHATCLIENTLISTENER_H

#include <jni.h>

#include <ChatClient/IChatClientListener.hpp>

class JNIChatClientListener :
    public IChatClientListener
{
public:
    JNIChatClientListener(JavaVM* javaVM, jobject& obj);
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
    JNIEnv* getEnv();
    jclass getCalledClass(JNIEnv* env);
    void setOnMessageJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnConnectedJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnDisconnectedJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnLoginSuccesfullJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnConnectionErrorJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnLoginFailedJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnContactsReceivedJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnContactOnlineStatusChangedJavaMethod(JNIEnv* env, jclass javaClass);

private:
    JavaVM* p_javaVM;
    bool b_threadAttachedToEnv;
    jobject m_calledJavaObject;
    jmethodID m_onMessageJavaMethod;
    jmethodID m_onConnectedJavaMethod;
    jmethodID m_onDisconnectedJavaMethod;
    jmethodID m_onLoginSuccesfullJavaMethod;
    jmethodID m_onConnectionErrorJavaMethod;
    jmethodID m_onLoginFailedJavaMethod;
    jmethodID m_onContactsReceivedJavaMethod;
    jmethodID m_onContactOnlineStatusChangedJavaMethod;

};

#endif // JNICHATCLIENTLISTENER_H

