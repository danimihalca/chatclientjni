#include "dm_chatclient_chatclient_notifier_JNIChatClientNotifierProxy.h"

#include "JNIChatClientNotifierProxy.hpp"
#include <debug_utils/log_debug.hpp>


/*
 * Class:     dm_chatclient_chatclient_notifier_JNIChatClientNotifierProxy
 * Method:    createNativeNotifierProxy
 * Signature: (Ldm/chatclient/chatclient/notifier/JNIChatClientNotifier;)J
 */
JNIEXPORT jlong JNICALL
Java_dm_chatclient_chatclient_notifier_JNIChatClientNotifierProxyWrapper_createNativeNotifierProxy
    (JNIEnv* env, jobject, jobject actualNotifier)
{
    JavaVM* javaVM;
    env->GetJavaVM(&javaVM);
    JNIChatClientNotifierProxy* notifier = new JNIChatClientNotifierProxy(
        javaVM,
        actualNotifier);

    return (long) notifier;
}

/*
 * Class:     dm_chatclient_chatclient_notifier_JNIChatClientNotifierProxy
 * Method:    setCallbackMethodNative
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_notifier_JNIChatClientNotifierProxyWrapper_setCallbackMethodNative
    (JNIEnv* env,
    jobject,
    jlong    notifierPointer,
    jint     callbackMethod,
    jstring  methodName)
{
    LOG_DEBUG_METHOD;
    JNIChatClientNotifierProxy* notifier =
        reinterpret_cast<JNIChatClientNotifierProxy*>(notifierPointer);

    const char* methodNameStr = (env)->GetStringUTFChars(methodName,0);

    notifier->setMethodCallback(static_cast<CALLBACK_METHOD>(callbackMethod),
                                methodNameStr);

    (env)->ReleaseStringUTFChars(methodName, methodNameStr);
}

/*
 * Class:     dm_chatclient_chatclient_notifier_JNIChatClientNotifierProxy
 * Method:    destroyNativeNotifierProxy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_notifier_JNIChatClientNotifierProxyWrapper_destroyNativeNotifierProxy
    (JNIEnv*, jobject, jlong notifierPointer)
{
    LOG_DEBUG_METHOD;
    JNIChatClientNotifierProxy* notifier =
        reinterpret_cast<JNIChatClientNotifierProxy*>(notifierPointer);

    delete notifier;
}
