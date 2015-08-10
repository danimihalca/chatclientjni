#include "JNIChatClientNotifierProxy.hpp"

#include <android/log.h>

JNIChatClientNotifierProxy::JNIChatClientNotifierProxy(JavaVM*  javaVM,
                                                       jobject& obj) :
    p_javaVM(javaVM),
    b_threadAttachedToEnv(false)
{
    JNIEnv* env = getJavaEnvironment();

    m_actualNotifierObject = env->NewGlobalRef(obj);
}

JNIChatClientNotifierProxy::~JNIChatClientNotifierProxy()
{
    JNIEnv* env = getJavaEnvironment();
    env->DeleteGlobalRef(m_actualNotifierObject);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::setMethodCallback(
    CALLBACK_METHOD    callbackMethod,
    const std::string& methodName)
{
    switch (callbackMethod)
    {
        case ON_CONNECTED:
        {
            setMethod(m_onConnectedJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID);
            break;
        }

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
                      METHOD_SIGNATURE_VOID);
            break;
        }

        case ON_LOGIN_FAILED:
        {
            setMethod(m_onLoginFailedJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_STRING);
            break;
        }

        case ON_CONTACT_STATUS_CHANGED:
        {
            setMethod(m_onContactStatusChangedJavaMethod,
                      methodName,
                      METHOD_SIGNATURE_VOID_INT_BOOL);
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
                      METHOD_SIGNATURE_VOID_BYTEARRAY);
            break;
        }
    }
}

void JNIChatClientNotifierProxy::notifyOnConnected()
{
    JNIEnv* env = getJavaEnvironment();
    env->CallVoidMethod(m_actualNotifierObject,m_onConnectedJavaMethod);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnDisconnected()
{
    JNIEnv* env = getJavaEnvironment();
    env->CallVoidMethod(m_actualNotifierObject,m_onDisconnectedJavaMethod);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnConnectionError()
{
    JNIEnv* env = getJavaEnvironment();
    env->CallVoidMethod(m_actualNotifierObject,m_onConnectionErrorJavaMethod);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnLoginSuccessful()
{
    JNIEnv* env = getJavaEnvironment();
    env->CallVoidMethod(m_actualNotifierObject,m_onLoginSuccesfulJavaMethod);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnLoginFailed(const std::string& reason)
{
    JNIEnv* env = getJavaEnvironment();

    jstring jReason = env->NewStringUTF(reason.c_str());
    env->CallVoidMethod(m_actualNotifierObject,
                        m_onLoginFailedJavaMethod,
                        jReason);

    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnContactsReceived(
    const char* contactsByteBuffer,
    int         size)
{
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
                                                              bool isOnline)
{
    JNIEnv* env = getJavaEnvironment();

    env->CallVoidMethod(m_actualNotifierObject,
                        m_onContactStatusChangedJavaMethod,
                        (jint)contactId,
                        (jboolean)isOnline);
    tryDetachThread();
}

void JNIChatClientNotifierProxy::notifyOnMessageReceived(
    int                senderId,
    const std::string& message)
{
    JNIEnv* env = getJavaEnvironment();

    jstring jMessage = env->NewStringUTF(message.c_str());
    env->CallVoidMethod(m_actualNotifierObject,
                        m_onMessageJavaMethod,
                        (jint)senderId,
                        jMessage);

    tryDetachThread();
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
    JNIEnv* javaEnvironment = getJavaEnvironment();
    jclass actualNotifierClass = javaEnvironment->GetObjectClass(m_actualNotifierObject);
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
