#ifndef JNICHATCLIENTNOTIFIERPROXY_HPP
#define JNICHATCLIENTNOTIFIERPROXY_HPP

#include <jni.h>

#include <string>

enum CALLBACK_METHOD
{
    ON_CONNECTED,
    ON_DISCONNECTED,
    ON_CONNECTION_ERROR,
    ON_LOGIN_SUCCESSFUL,
    ON_LOGIN_FAILED,
    ON_CONTACT_STATUS_CHANGED,
    ON_MESSAGE_RECEIVED,
    ON_CONTACTS_RECEIVED
};

const char* const METHOD_SIGNATURE_VOID = "()V";
const char* const METHOD_SIGNATURE_VOID_STRING = "(Ljava/lang/String;)V";
const char* const METHOD_SIGNATURE_VOID_INT_BYTE = "(IB)V";
const char* const METHOD_SIGNATURE_VOID_INT_STRING = "(ILjava/lang/String;)V";
const char* const METHOD_SIGNATURE_VOID_BYTEARRAY_INT = "([BI)V";

class JNIChatClientNotifierProxy
{
public:
    JNIChatClientNotifierProxy(JavaVM* javaVM, jobject& obj);
    ~JNIChatClientNotifierProxy();

    void setMethodCallback(CALLBACK_METHOD    callbackMethod,
                           const std::string& methodName);

    void notifyOnConnected();
    void notifyOnDisconnected();
    void notifyOnConnectionError();
    void notifyOnLoginSuccessful(const char* userDetailsByteBuffer, int size);
    void notifyOnLoginFailed(const std::string& reason);
    void notifyOnContactsReceived(const char* contactsByteBuffer, int size);
    void notifyOnContactStatusChanged(int contactId, char state);
    void notifyOnMessageReceived(int senderId, const std::string& message);


private:
    JNIEnv* getJavaEnvironment();
    void tryDetachThread();

    void setMethod(jmethodID&         javaMethod,
                   const std::string& methodName,
                   const std::string& methodSignature);

private:
    JavaVM* p_javaVM;
    bool b_threadAttachedToEnv;

    jobject m_actualNotifierObject;

    jmethodID m_onMessageJavaMethod;
    jmethodID m_onConnectedJavaMethod;
    jmethodID m_onDisconnectedJavaMethod;
    jmethodID m_onLoginSuccesfulJavaMethod;
    jmethodID m_onConnectionErrorJavaMethod;
    jmethodID m_onLoginFailedJavaMethod;
    jmethodID m_onContactsReceivedJavaMethod;
    jmethodID m_onContactStatusChangedJavaMethod;
};

#endif // JNICHATCLIENTNOTIFIERPROXY_HPP

