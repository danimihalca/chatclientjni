#include "JNIChatClientListener.h"

#include <android/log.h>

JNIChatClientListener::JNIChatClientListener(JavaVM* javaVM, jobject& obj) :
    p_javaVM(javaVM),
    b_threadAttachedToEnv(false)
{
    JNIEnv* env = getEnv();

    m_calledJavaObject = env->NewGlobalRef(obj);
    jclass javaClass = getCalledClass(env);


    setOnMessageJavaMethod(env, javaClass);
    setOnConnectedJavaMethod(env, javaClass);
    setOnDisconnectedJavaMethod(env, javaClass);
    setOnLoginSuccesfullJavaMethod(env,javaClass);
    setOnLoginFailedJavaMethod(env,javaClass);
    setOnConnectionErrorJavaMethod(env,javaClass);

    if (b_threadAttachedToEnv)
    {
        __android_log_write(ANDROID_LOG_INFO,
                            "ChatClientNative",
                            "Thread deattached from env");
        p_javaVM->DetachCurrentThread();
        b_threadAttachedToEnv = false;
    }
}

JNIChatClientListener::~JNIChatClientListener()
{
    JNIEnv* env = getEnv();
    env->DeleteGlobalRef(m_calledJavaObject);

    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
    }
}

void JNIChatClientListener::onMessageReceived(const std::string& message)
{
    JNIEnv* env = getEnv();

    jstring jMessage = env->NewStringUTF(message.c_str());
    env->CallVoidMethod(m_calledJavaObject,m_onMessageJavaMethod,jMessage);

    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
    }
}

void JNIChatClientListener::onConnected()
{
    JNIEnv* env = getEnv();

    env->CallVoidMethod(m_calledJavaObject,m_onConnectedJavaMethod);

    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
        __android_log_write(ANDROID_LOG_INFO,
                            "ChatClientNative",
                            "Thread deattached from env");
    }
}

void JNIChatClientListener::onDisconnected()
{
    JNIEnv* env = getEnv();

    env->CallVoidMethod(m_calledJavaObject,m_onDisconnectedJavaMethod);

    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
    }
}

void JNIChatClientListener::onLoginSuccessfull()
{
    JNIEnv* env = getEnv();

    env->CallVoidMethod(m_calledJavaObject,m_onLoginSuccesfullJavaMethod);

    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
        __android_log_write(ANDROID_LOG_INFO,
                            "ChatClientNative",
                            "Thread deattached from env");
    }
}

void JNIChatClientListener::onLoginFailed(const std::string& message)
{
    JNIEnv* env = getEnv();

    jstring jMessage = env->NewStringUTF(message.c_str());
    env->CallVoidMethod(m_calledJavaObject,m_onLoginFailedJavaMethod,jMessage);

    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
    }
}

void JNIChatClientListener::onConnectionError()
{
    JNIEnv* env = getEnv();

    env->CallVoidMethod(m_calledJavaObject,m_onConnectionErrorJavaMethod);

    if (b_threadAttachedToEnv)
    {
        p_javaVM->DetachCurrentThread();
        __android_log_write(ANDROID_LOG_INFO,
                            "ChatClientNative",
                            "Thread deattached from env");
    }
}

JNIEnv* JNIChatClientListener::getEnv()
{
    b_threadAttachedToEnv = false;

    JNIEnv* env;
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

jclass JNIChatClientListener::getCalledClass(JNIEnv* env)
{
    jclass javaClass = env->GetObjectClass(m_calledJavaObject);
    if (!javaClass)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "GetObjectClass failed");
        if (b_threadAttachedToEnv)
        {
            p_javaVM->DetachCurrentThread();
            b_threadAttachedToEnv = false;
        }
    }
}

void JNIChatClientListener::setOnMessageJavaMethod(JNIEnv* env,
                                                   jclass  javaClass)
{
    m_onMessageJavaMethod = env->GetMethodID(javaClass,
                                             "notifyOnMessage",
                                             "(Ljava/lang/String;)V");
    if (!m_onMessageJavaMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "GetMethodID failed");
        if (b_threadAttachedToEnv)
        {
            p_javaVM->DetachCurrentThread();
        }
        return;
    }
}

void JNIChatClientListener::setOnConnectedJavaMethod(JNIEnv* env,
                                                     jclass  javaClass)
{
    m_onConnectedJavaMethod = env->GetMethodID(javaClass,
                                               "notifyOnConnected",
                                               "()V");
    if (!m_onConnectedJavaMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "GetMethodID failed");
        if (b_threadAttachedToEnv)
        {
            p_javaVM->DetachCurrentThread();
        }
        return;
    }
}

void JNIChatClientListener::setOnDisconnectedJavaMethod(JNIEnv* env,
                                                        jclass  javaClass)
{
    m_onDisconnectedJavaMethod = env->GetMethodID(javaClass,
                                                  "notifyOnDisconnected",
                                                  "()V");
    if (!m_onDisconnectedJavaMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "GetMethodID failed");
        if (b_threadAttachedToEnv)
        {
            p_javaVM->DetachCurrentThread();
        }
        return;
    }
}

void JNIChatClientListener::setOnLoginSuccesfullJavaMethod(JNIEnv* env,
                                                           jclass  javaClass)
{
    m_onLoginSuccesfullJavaMethod = env->GetMethodID(javaClass,
                                                     "notifyOnLoginSuccessfull",
                                                     "()V");
    if (!m_onLoginSuccesfullJavaMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "GetMethodID failed");
        if (b_threadAttachedToEnv)
        {
            p_javaVM->DetachCurrentThread();
        }
    }
}

void JNIChatClientListener::setOnConnectionErrorJavaMethod(JNIEnv* env,
                                                           jclass  javaClass)
{
    m_onConnectionErrorJavaMethod = env->GetMethodID(javaClass,
                                                     "notifyOnConnectionError",
                                                     "()V");
    if (!m_onConnectionErrorJavaMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "GetMethodID failed");
        if (b_threadAttachedToEnv)
        {
            p_javaVM->DetachCurrentThread();
        }
    }
}

void JNIChatClientListener::setOnLoginFailedJavaMethod(JNIEnv* env,
                                                       jclass  javaClass)
{
    m_onLoginFailedJavaMethod = env->GetMethodID(javaClass,
                                                 "notifyOnLoginFailed",
                                                 "(Ljava/lang/String;)V");
    if (!m_onLoginFailedJavaMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR,
                            "ChatClientNative",
                            "GetMethodID failed");
        if (b_threadAttachedToEnv)
        {
            p_javaVM->DetachCurrentThread();
        }
    }
}
