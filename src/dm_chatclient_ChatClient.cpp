#include "dm_chatclient_ChatClient.h"

#include "IChatClient.h"
#include "ChatClient.h"
#include "common.h"

#include <android/log.h>

JavaVM* gJavaVM = NULL;
jobject gJavaChatClientObj;

const char* gJavaChatClientPath = "dm/chatclient/ChatClient";
const char* newMessageMethod = "notifyNewMessage";


void messageCallback(const char* message)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "newMessageCallback");

    bool isAttached = false;

    JNIEnv *env;
    if (gJavaVM->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK)
    {
        __android_log_write(ANDROID_LOG_ERROR, "ChatClientNative", "GetEnv failed");
        if (gJavaVM->AttachCurrentThread(&env, NULL) != JNI_OK)
        {
            __android_log_write(ANDROID_LOG_ERROR, "ChatClientNative", "Env failed to attach thread");
            return;
        }
        __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "Env attached to thread");

        isAttached = true;
    }

    jclass chatClientJavaClass = env->GetObjectClass(gJavaChatClientObj);
    if (!chatClientJavaClass)
    {
        __android_log_write(ANDROID_LOG_ERROR, "ChatClientNative", "GetObjectClass failed");
        if (isAttached)
        {
            gJavaVM->DetachCurrentThread();
        }
        return;
    }
    ///////////////////////////////// list methods for class
//    jobject strObj = env->AllocObject(chatClientJavaClass);
//    jmethodID midGetClass = env->GetMethodID(chatClientJavaClass, "getClass", "()Ljava/lang/Class;");
//    jobject clsObj = env->CallObjectMethod(strObj, midGetClass);
//    jclass jCls = env->GetObjectClass(clsObj);
//    jmethodID midGetFields = env->GetMethodID(jCls, "getMethods", "()[Ljava/lang/reflect/Method;");
//    jobjectArray jobjArray = (jobjectArray)env->CallObjectMethod(clsObj, midGetFields);
//    jsize len = env->GetArrayLength(jobjArray);
//    jsize i;

//    for (i = 0 ; i < len ; i++)
//    {
//        jobject _strMethod = env->GetObjectArrayElement(jobjArray , i) ;
//        jclass _methodClazz = env->GetObjectClass(_strMethod) ;
//        jmethodID mid = env->GetMethodID(_methodClazz , "getName" , "()Ljava/lang/String;") ;
//        jstring _name = (jstring)env->CallObjectMethod(_strMethod , mid ) ;
//        const char *str = env->GetStringUTFChars(_name, 0);
//        __android_log_write(ANDROID_LOG_INFO, "MMMMM", str);

//        env->ReleaseStringUTFChars(_name, str);
//    }
    /// /////////////////////////////

    jmethodID jNewMessageMethod = env->GetMethodID(chatClientJavaClass, "notifyNewMessage", "(Ljava/lang/String;)V");
    if (!jNewMessageMethod)
    {
        __android_log_write(ANDROID_LOG_ERROR, "ChatClientNative", "GetMethodID failed");
        if (isAttached)
        {
            gJavaVM->DetachCurrentThread();
        }
        return;
    }
    jstring jMessage = env->NewStringUTF(message);
    env->CallVoidMethod(gJavaChatClientObj,jNewMessageMethod,jMessage);

    if (isAttached)
    {
        gJavaVM->DetachCurrentThread();
    }
}

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
    chatClient->setNewMessageCallback(&messageCallback);

    //##########################################
    gJavaChatClientObj = env->NewGlobalRef(obj);
    //##########################################

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
(JNIEnv * env, jobject obj, jlong pointer, jstring uri)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "connectNative");

    const char* uriCStr = (env)->GetStringUTFChars(uri,0);
    IChatClient* chatClient  = reinterpret_cast<IChatClient*>(pointer);
    chatClient->connect(uriCStr);
    (env)->ReleaseStringUTFChars(uri, uriCStr);

//    chatClient->connect("ws://192.168.0.3:9002");
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
        env->DeleteGlobalRef(gJavaChatClientObj);
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
    //    gJavaChatClientObj = env->NewGlobalRef(chatClientClass);

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
