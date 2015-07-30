#include "dm_chatclient_ChatClient.h"

#include <ChatClient/IChatClient.h>
#include <ChatClient/ChatClient.h>
#include <chat_client_common.h>

#include "JNIChatClientListener.h"

#include <android/log.h>

JavaVM* gJavaVM = NULL;


/*
 * Class:     dm_chatclient_ChatClient
 * Method:    createClientNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_dm_chatclient_ChatClient_createClientNative
    (JNIEnv* env, jobject obj)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "createClientNative");
    IChatClient* chatClient = new ChatClient();
    std::shared_ptr<IChatClientListener> listener(new JNIChatClientListener(
                                                      gJavaVM,
                                                      obj));
    chatClient->addChatClientListener(listener);

    return (long)chatClient;
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    setServerPropertiesNative
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_setServerPropertiesNative
    (JNIEnv* env, jobject obj, jlong pointer, jstring address, jint port)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "setServerPropertiesNative");

    const char* addressCStr = (env)->GetStringUTFChars(address,0);
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->setServerProperties(addressCStr,(uint16_t)port);

    (env)->ReleaseStringUTFChars(address, addressCStr);
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    loginNative
 * Signature: (JLjava/lang/String;Ljava/lang/String)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_loginNative
    (JNIEnv* env, jobject obj, jlong pointer, jstring username, jstring password)
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
 * Class:     dm_chatclient_ChatClient
 * Method:    disconnectNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_disconnectNative
    (JNIEnv* env, jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative",
                        "disconnectNative");
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->disconnect();
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    sendMessageNative
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_sendMessageNative
    (JNIEnv* env, jobject obj, jlong pointer, jstring message)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "sendMessageNative");
    const char* messageCStr = (env)->GetStringUTFChars(message,0);
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->sendMessage(messageCStr);
    (env)->ReleaseStringUTFChars(message, messageCStr);
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    destroyClientNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_destroyClientNative
    (JNIEnv* env, jobject obj, jlong pointer)
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

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jVm, void* /*aReserved*/)
{
    gJavaVM = jVm;

    return JNI_VERSION_1_6;

}
