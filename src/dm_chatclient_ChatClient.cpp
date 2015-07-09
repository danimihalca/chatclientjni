#include "dm_chatclient_ChatClient.h"

#include "IChatClient.h"
#include "ChatClient.h"

#include <android/log.h>

JavaVM* gJavaVM = NULL;
jobject gJavaChatClient;

const char* gJavaChatClientPath = "dm/chatclient/ChatClient";
/*
 * Class:     dm_chatclient_ChatClient
 * Method:    createClientNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_dm_chatclient_ChatClient_createClientNative
(JNIEnv * env, jobject obj)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "createClientNative");
    IChatClient* chatClient = new ChatClient();

    return (long)chatClient;
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    initializeNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_initializeNative
(JNIEnv * env, jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "initializeNative");
    IChatClient* chatClient  = reinterpret_cast<IChatClient*>(pointer);
    chatClient->initialize();
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    connectNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_connectNative
(JNIEnv * env, jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "connectNative");
    IChatClient* chatClient  = reinterpret_cast<IChatClient*>(pointer);
    chatClient->connect("ws://192.168.0.3:9002");
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    disconnectNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_disconnectNative
(JNIEnv * env, jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "disconnectNative");
    IChatClient* chatClient  = reinterpret_cast<IChatClient*>(pointer);
    chatClient->closeConnection();
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    startServiceNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_startServiceNative
(JNIEnv * env, jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "startServiceNative");
    IChatClient* chatClient  = reinterpret_cast<IChatClient*>(pointer);
    chatClient->startService();
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    sendMessageNative
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_sendMessageNative
(JNIEnv *env, jobject obj, jlong pointer, jstring message)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "sendMessageNative");
    const char* messageCStr= (env)->GetStringUTFChars(message,0);
    IChatClient* chatClient  = reinterpret_cast<IChatClient*>(pointer);
    chatClient->sendMessage(messageCStr);
    (env)->ReleaseStringUTFChars(message, messageCStr);
}

/*
 * Class:     dm_chatclient_ChatClient
 * Method:    destroyClientNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_ChatClient_destroyClientNative
(JNIEnv *env , jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "destroyClientNative");
    IChatClient* chatClient  = reinterpret_cast<IChatClient*>(pointer);
    if (chatClient != nullptr)
    {
        delete chatClient;
        env->DeleteGlobalRef(gJavaChatClient);
    }

}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jVm, void* /*aReserved*/)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "JNI_OnLoad");

    gJavaVM = jVm;

    JNIEnv* env;
    if (jVm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK)
    {
        __android_log_write(ANDROID_LOG_ERROR, "ChatClientNative", "GetEnv failed");
        return -1;
    }

    jclass chatClientClass = env->FindClass(gJavaChatClientPath);
    if (!chatClientClass)
    {
        __android_log_write(ANDROID_LOG_ERROR, "ChatClientNative", "FindClass failed");
        return -1;
    }
    gJavaChatClient = env->NewGlobalRef(chatClientClass);

    return JNI_VERSION_1_6;

}


JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* jVm, void* /*reserved*/)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "JNI_OnUnload");

    JNIEnv* env;
    if (jVm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK)
    {
        __android_log_write(ANDROID_LOG_ERROR, "ChatClientNative", "GetEnv failed");
        return;
    }

    //    env->DeleteGlobalRef(gJavaChatClient);
}
