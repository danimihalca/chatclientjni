#ifndef JNICHATCLIENTLISTENER_H
#define JNICHATCLIENTLISTENER_H

#include <jni.h>

#include <ChatClient/IChatClientListener.h>

class JNIChatClientListener :
    public IChatClientListener
{
public:
    JNIChatClientListener(JavaVM* javaVM, jobject& obj);
    ~JNIChatClientListener();

    //Implements IChatClientListener
public:
    void onMessageReceived(const std::string& message);
    void onConnected();
    void onDisconnected();

private:
    JNIEnv* getEnv();
    jclass getCalledClass(JNIEnv* env);
    void setOnMessageJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnConnectedJavaMethod(JNIEnv* env, jclass javaClass);
    void setOnDisconnectedJavaMethod(JNIEnv* env, jclass javaClass);
private:
    JavaVM* p_javaVM;
    bool b_threadAttachedToEnv;
    jobject m_calledJavaObject;
    jmethodID m_onMessageJavaMethod;
    jmethodID m_onConnectedJavaMethod;
    jmethodID m_onDisconnectedJavaMethod;

};

#endif // JNICHATCLIENTLISTENER_H

