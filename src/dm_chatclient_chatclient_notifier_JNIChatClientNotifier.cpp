#include "dm_chatclient_chatclient_notifier_JNIChatClientNotifier.h"

#include "JNIChatClientListener.hpp"
#include "JNIChatClientNotifierProxy.hpp"
#include <debug_utils/log_debug.hpp>

/*
 * Class:     dm_chatclient_chatclient_notifier_JNIChatClientNotifier
 * Method:    createNativeJNIListener
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_dm_chatclient_chatclient_notifier_JNIChatClientNotifier_createNativeJNIListener
    (JNIEnv*, jobject, jlong notifierProxyPointer)
{
    LOG_DEBUG_METHOD;
    JNIChatClientNotifierProxy* notifierProxy =
        reinterpret_cast<JNIChatClientNotifierProxy*> (notifierProxyPointer);

    IChatClientListener* listener = new JNIChatClientListener(notifierProxy);

    return (long) listener;
}

/*
 * Class:     dm_chatclient_chatclient_notifier_JNIChatClientNotifier
 * Method:    destroyNativeJNIListener
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_notifier_JNIChatClientNotifier_destroyNativeJNIListener
    (JNIEnv*, jobject, jlong listenerPointer)
{
    LOG_DEBUG_METHOD;
    IChatClientListener* listener =
        reinterpret_cast<IChatClientListener*>(listenerPointer);
}

