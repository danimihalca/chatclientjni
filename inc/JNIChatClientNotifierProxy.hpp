#ifndef JNICHATCLIENTNOTIFIERPROXY_HPP
#define JNICHATCLIENTNOTIFIERPROXY_HPP

#include <jni.h>

#include <string>

enum CALLBACK_METHOD
{
//    ON_CONNECTED,
    ON_DISCONNECTED,
    ON_CONNECTION_ERROR,
    ON_LOGIN_SUCCESSFUL,
    ON_LOGIN_FAILED,
    ON_CONTACT_STATUS_CHANGED,
    ON_MESSAGE_RECEIVED,
    ON_CONTACTS_RECEIVED,

    ON_REMOVED_BY_CONTACT,
    ON_ADD_CONTACT_RESPONSE,
    ON_ADD_REQUEST,

    ON_REGISTER_UPDATE_RESPONSE
};

const char* const METHOD_SIGNATURE_VOID = "()V";
const char* const METHOD_SIGNATURE_VOID_INT = "(I)V";
const char* const METHOD_SIGNATURE_VOID_BYTE = "(B)V";
const char* const METHOD_SIGNATURE_VOID_STRING = "(Ljava/lang/String;)V";
const char* const METHOD_SIGNATURE_VOID_INT_BYTE = "(IB)V";
const char* const METHOD_SIGNATURE_VOID_STRING_BOOL = "(Ljava/lang/String;Z)V";
const char* const METHOD_SIGNATURE_VOID_STRING_BYTE = "(Ljava/lang/String;B)V";
const char* const METHOD_SIGNATURE_VOID_INT_STRING = "(ILjava/lang/String;)V";
const char* const METHOD_SIGNATURE_VOID_BYTEARRAY_INT = "([BI)V";

const char* const METHOD_SIGNATURE_BOOL_STRING = "(Ljava/lang/String;)Z";


class JNIChatClientNotifierProxy
{
public:
    JNIChatClientNotifierProxy(JavaVM* javaVM, jobject& obj);
    ~JNIChatClientNotifierProxy();

    void setMethodCallback(CALLBACK_METHOD    callbackMethod,
                           const std::string& methodName);

//    void notifyOnConnected();
    void notifyOnDisconnected();
    void notifyOnConnectionError();
    void notifyOnLoginSuccessful(const char* userDetailsByteBuffer, int size);
    void notifyOnLoginFailed(char reason);
    void notifyOnContactsReceived(const char* contactsByteBuffer, int size);
    void notifyOnContactStatusChanged(int contactId, char state);
    void notifyOnMessageReceived(int senderId, const std::string& message);

    void notifyOnRemovedByContact(int contactId);
    void notifyOnAddContactResponse(const std::string& userName, char status);
    bool notifyOnAddRequest(const std::string& requester);

    void notifyOnRegisterUpdateResponse(char status);

private:
    JNIEnv* getJavaEnvironment();
    void tryDetachThread();

    void setMethod(jmethodID&         javaMethod,
                   const std::string& methodName,
                   const std::string& methodSignature);

private:
    JavaVM* p_javaVM;
    bool b_threadAttachedToEnv;

    jobject m_actualNotifier;

    jmethodID m_onMessageReceivedMethod;
    jmethodID m_onConnectedMethod;
    jmethodID m_onDisconnectedMethod;
    jmethodID m_onLoginSuccesfulMethod;
    jmethodID m_onConnectionErrorMethod;
    jmethodID m_onLoginFailedMethod;
    jmethodID m_onContactsReceivedMethod;
    jmethodID m_onContactStateChangedMethod;

    jmethodID m_onRemovedByContactMethod;
    jmethodID m_onAddContactResponseMethod;
    jmethodID m_onAddRequestMethod;

    jmethodID m_onRegisterUpdateResponseMethod;
};

#endif // JNICHATCLIENTNOTIFIERPROXY_HPP

