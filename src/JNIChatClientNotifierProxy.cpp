#include "JNIChatClientNotifierProxy.hpp"

#include <android/log.h>

#include <debug_utils/log_debug.hpp>

JNIChatClientNotifierProxy::JNIChatClientNotifierProxy(JavaVM*  javaVM,
                                                       jobject& obj) :
    p_javaVM(javaVM),
    b_threadAttachedToEnv(false)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    m_actualNotifierObject = env->NewGlobalRef(obj);
}

JNIChatClientNotifierProxy::~JNIChatClientNotifierProxy()
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();
    env->DeleteGlobalRef(m_actualNotifierObject);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::setMethodCallback(
    CALLBACK_METHOD    callbackMethod,
    const std::string& methodName)
{
    LOG_DEBUG_METHOD;
    switch (callbackMethod)
    {

//        case ON_CONNECTED:
//        {
//            setMethod(m_onConnectedJavaMethod,
//                      methodName,
//                      METHOD_SIGNATURE_VOID);
//            break;
//        }

        case ON_DISCONNECTED:
        {
            setMethod(m_onDisconnectedJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID);
            break;
        }

        case ON_CONNECTION_ERROR:
        {
            setMethod(m_onConnectionErrorJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID);
            break;
        }

        case ON_LOGIN_SUCCESSFUL:
        {
            setMethod(m_onLoginSuccesfulJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_BYTEARRAY_INT);
            break;
        }

        case ON_LOGIN_FAILED:
        {
            setMethod(m_onLoginFailedJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_BYTE);
            break;
        }

        case ON_CONTACT_STATUS_CHANGED:
        {
            setMethod(m_onContactStatusChangedJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_INT_BYTE);
            break;
        }

        case ON_MESSAGE_RECEIVED:
        {
            setMethod(m_onMessageJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_INT_STRING);
            break;
        }

        case ON_CONTACTS_RECEIVED:
        {
            setMethod(m_onContactsReceivedJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_BYTEARRAY_INT);
            break;
        }

        case ON_REMOVED_BY_CONTACT:
        {
            setMethod(m_onRemovedByContactJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_INT);
            break;
        }

        case ON_ADD_CONTACT_RESPONSE:
        {
            setMethod(m_onAddContactResponseJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_STRING_BYTE);
            break;
        }

        case ON_ADD_REQUEST:
        {
            setMethod(m_onAddingByContactJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_BOOL_STRING);
            break;
        }
        case ON_REGISTER_UPDATE_RESPONSE:
        {
            setMethod(m_onRegisterUpdateResponseJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_BYTE);
            break;
        }
    }
}

//void JNIChatClientNotifierProxy::notifyOnConnected()
//{
//    LOG_DEBUG_METHOD;
//    JNIEnv* env = getJavaEnvironment();
//    env->CallVoidMethod(m_actualNotifierObject,m_onConnectedJavaMethod);

//    tryDetachThread();
//}

void JNIChatClientNotifierProxy::notifyOnDisconnected()
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();
    env->CallVoidMethod(m_actualNotifierObject,m_onDisconnectedJavaMethod);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnConnectionError()
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();
    env->CallVoidMethod(m_actualNotifierObject,m_onConnectionErrorJavaMethod);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnLoginSuccessful(
    const char* userDetailsByteBuffer,
    int         size)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    jbyteArray jByteArray = env->NewByteArray(size);
    char* bytes = (char*)env->GetByteArrayElements(jByteArray, 0);
    memcpy(bytes,userDetailsByteBuffer,size);
    env->ReleaseByteArrayElements(jByteArray, (jbyte*) bytes, JNI_COMMIT);


    env->CallVoidMethod(m_actualNotifierObject,
                        m_onLoginSuccesfulJavaMethod,
                        jByteArray,
                        (jint)size);

    tryDetachThread();

}

void JNIChatClientNotifierProxy::notifyOnLoginFailed(char reason)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    env->CallVoidMethod(m_actualNotifierObject,
                        m_onLoginFailedJavaMethod,
                        (jbyte)reason);
    LOG_DEBUG_METHOD;
    tryDetachThread();
    LOG_DEBUG_METHOD;
}

void JNIChatClientNotifierProxy::notifyOnContactsReceived(
    const char* contactsByteBuffer,
    int         size)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    jbyteArray jByteArray = env->NewByteArray(size);
    char* bytes = (char*)env->GetByteArrayElements(jByteArray, 0);
    memcpy(bytes,contactsByteBuffer,size);
    env->ReleaseByteArrayElements(jByteArray, (jbyte*) bytes, JNI_COMMIT);


    env->CallVoidMethod(m_actualNotifierObject,
                        m_onContactsReceivedJavaMethod,
                        jByteArray,
                        (jint)size);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnContactStatusChanged(int  contactId,
                                                              char state)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    env->CallVoidMethod(m_actualNotifierObject,
                        m_onContactStatusChangedJavaMethod,
                        (jint)contactId,
                        (jbyte)state);
    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnMessageReceived(
    int                senderId,
    const std::string& message)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    jstring jMessage = env->NewStringUTF(message.c_str());
    env->CallVoidMethod(m_actualNotifierObject,
                        m_onMessageJavaMethod,
                        (jint)senderId,
                        jMessage);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnRemovedByContact(int contactId)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    env->CallVoidMethod(m_actualNotifierObject,
                        m_onRemovedByContactJavaMethod,
                        (jint)contactId);
    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnAddContactResponse(
    const std::string& userName,
     char status)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();
    jstring jUserName = env->NewStringUTF(userName.c_str());

    env->CallVoidMethod(m_actualNotifierObject,
                        m_onAddContactResponseJavaMethod,
                        jUserName,
                        (jbyte)status);
    tryDetachThread();
}

bool JNIChatClientNotifierProxy::notifyOnAddRequest(
    const std::string& requester)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();
    jstring jUserName = env->NewStringUTF(requester.c_str());

    jboolean jAccepted = env->CallBooleanMethod(m_actualNotifierObject,
                        m_onAddingByContactJavaMethod,
                        jUserName);
    bool accepted = jAccepted != 0;
    tryDetachThread();
    return  accepted;
}

void JNIChatClientNotifierProxy::notifyOnRegisterUpdateResponse(char status)
{
    LOG_DEBUG_METHOD;
    JNIEnv* env = getJavaEnvironment();

    env->CallVoidMethod(m_actualNotifierObject,
                        m_onRegisterUpdateResponseJavaMethod,
                        (jbyte)status);
    LOG_DEBUG_METHOD;
    tryDetachThread();
    LOG_DEBUG_METHOD;
}

JNIEnv* JNIChatClientNotifierProxy::getJavaEnvironment()
{
    b_threadAttachedToEnv = false;

    JNIEnv* env = nullptr;
    if (p_javaVM->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK)
    {
        if (p_javaVM->AttachCurrentThread(&env, NULL) != JNI_OK)
        {
            __android_log_write(ANDROID_LOG_ERROR,
                                "ChatClientNative",
                                "Env failed to attach thread");
        }
        __android_log_write(ANDROID_LOG_INFO,
                            "ChatClientNative",
                            "Thread attached to env");

        b_threadAttachedToEnv = true;
    }
    return env;
}

void JNIChatClientNotifierProxy::tryDetachThread()
{
    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
        __android_log_write(ANDROID_LOG_INFO,
                            "ChatClientNative",
                            "Thread deattached from env");
    }
}

void JNIChatClientNotifierProxy::setMethod(jmethodID&         javaMethod,
                                           const std::string& methodName,
                                           const std::string& methodSignature)
{
    LOG_DEBUG_METHOD;
    JNIEnv* javaEnvironment = getJavaEnvironment();
    jclass actualNotifierClass = javaEnvironment->GetObjectClass(
        m_actualNotifierObject);
    javaMethod = javaEnvironment->GetMethodID(actualNotifierClass,
                                              methodName.c_str(),
                                              methodSignature.c_str());
    if (!javaMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "Failet to set method");
        tryDetachThread();
    }
}
