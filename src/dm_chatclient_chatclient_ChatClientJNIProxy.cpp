#include "dm_chatclient_chatclient_ChatClientJNIProxy.h"

#include <ChatClient/IChatClient.hpp>
#include <ChatClient/ChatClient.hpp>

#include "JNIChatClientListener.hpp"

#include <android/log.h>


/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    createClientNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_createClientNative
  (JNIEnv * env, jobject obj)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "createClientNative");
    IChatClient* chatClient = new ChatClient();
//    std::shared_ptr<IChatClientListener> listener(new JNIChatClientListener(
//                                                      gJavaVM,
//                                                      obj));
//    chatClient->addListener(listener);

    return (long)chatClient;
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    setServerPropertiesNative
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_setServerPropertiesNative
    (JNIEnv* env, jobject /*obj*/, jlong pointer, jstring address, jint port)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "setServerPropertiesNative");

    const char* addressCStr = (env)->GetStringUTFChars(address,0);
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->setServerProperties(addressCStr,(uint16_t)port);

    (env)->ReleaseStringUTFChars(address, addressCStr);
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    loginNative
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_loginNative
    (JNIEnv* env, jobject /*obj*/, jlong pointer, jstring username, jstring password)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "loginNative");

    const char* usernameCStr = (env)->GetStringUTFChars(username,0);
    const char* passwordCStr = (env)->GetStringUTFChars(password,0);

    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->login(usernameCStr,passwordCStr);

    (env)->ReleaseStringUTFChars(username, usernameCStr);
    (env)->ReleaseStringUTFChars(password, passwordCStr);
}


/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    disconnectNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_disconnectNative
    (JNIEnv* env, jobject /*obj*/, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative",
                        "disconnectNative");
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->disconnect();
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    sendMessageNative
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_sendMessageNative
    (JNIEnv* env, jobject /*obj*/, jlong pointer, jint receiverId, jstring message)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "sendMessageNative");
    const char* messageCStr = (env)->GetStringUTFChars(message,0);
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->sendMessage(receiverId,messageCStr);
    (env)->ReleaseStringUTFChars(message, messageCStr);
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    destroyClientNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_destroyClientNative
    (JNIEnv* /*env*/, jobject /*obj*/, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "destroyClientNative");
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    if (chatClient != nullptr)
    {
        delete chatClient;
    }
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    requestContactsNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_requestContactsNative
  (JNIEnv *env, jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "requestContactsNative");

    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->getContacts();
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    addListenerNative
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_addListenerNative
  (JNIEnv *, jobject, jlong chatClientPointer, jlong listenerPointer)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);

    IChatClientListener* listener =
        reinterpret_cast<IChatClientListener*>(listenerPointer);

    chatClient->addListener(listener);
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    removeListenerNative
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_chatclient_ChatClientJNIProxy_removeListenerNative
  (JNIEnv *, jobject, jlong chatClientPointer, jlong listenerPointer)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);

    IChatClientListener* listener =
        reinterpret_cast<IChatClientListener*>(listenerPointer);

    chatClient->removeListener(listener);
}