#include "dm_chatclient_chatclient_ChatClientJNIProxy.h"

#include <ChatClient/IChatClient.hpp>
#include <ChatClient/ChatClient.hpp>

#include "JNIChatClientListener.hpp"

#include <android/log.h>

#include <Model/User.hpp>

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    createClientNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_createClientNative
    (JNIEnv* env, jobject obj)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "createClientNative");
    IChatClient* chatClient = new ChatClient();
    return (long)chatClient;
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    setServerNative
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_setServerNative
    (JNIEnv* env, jobject /*obj*/, jlong pointer, jstring address, jint port)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "setServerPropertiesNative");

    const char* addressCStr = (env)->GetStringUTFChars(address,0);
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->setServer(addressCStr,(uint16_t)port);

    (env)->ReleaseStringUTFChars(address, addressCStr);
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    loginNative
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_loginNative
    (JNIEnv* env,
    jobject /*obj*/,
    jlong    pointer,
    jstring  username,
    jstring  password,
    jint     state)
{
    __android_log_write(ANDROID_LOG_INFO, "ChatClientNative", "loginNative");

    const char* usernameCStr = (env)->GetStringUTFChars(username,0);
    const char* passwordCStr = (env)->GetStringUTFChars(password,0);

    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);

    UserCredentials userCredentials(usernameCStr,passwordCStr);
    chatClient->login(userCredentials,static_cast<USER_STATE>(state));

    (env)->ReleaseStringUTFChars(username, usernameCStr);
    (env)->ReleaseStringUTFChars(password, passwordCStr);
}


/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    disconnectNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_disconnectNative
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
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_sendMessageNative
    (JNIEnv* env,
    jobject /*obj*/,
    jlong    address,
    jint     receiverId,
    jstring  message)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "sendMessageNative");
    if (address != 0)
    {
        const char* messageCStr = (env)->GetStringUTFChars(message,0);
        IChatClient* chatClient = reinterpret_cast<IChatClient*>(address);
        chatClient->sendMessage(receiverId,messageCStr);
        (env)->ReleaseStringUTFChars(message, messageCStr);
    }
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    destroyClientNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_destroyClientNative
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
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_requestContactsNative
    (JNIEnv* env, jobject obj, jlong pointer)
{
    __android_log_write(ANDROID_LOG_INFO,
                        "ChatClientNative",
                        "requestContactsNative");

    IChatClient* chatClient = reinterpret_cast<IChatClient*>(pointer);
    chatClient->requestContacts();
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    addListenerNative
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_addListenerNative
    (JNIEnv*, jobject, jlong chatClientPointer, jlong listenerPointer)
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
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_removeListenerNative
    (JNIEnv*, jobject, jlong chatClientPointer, jlong listenerPointer)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);

    IChatClientListener* listener =
        reinterpret_cast<IChatClientListener*>(listenerPointer);

    chatClient->removeListener(listener);
}


/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    removeContactNative
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_removeContactNative
    (JNIEnv*, jobject, jlong chatClientPointer, jint contactId)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);

    chatClient->removeContact((int) contactId);
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    addContactNative
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_dm_chatclient_chatclient_ChatClientJNIProxy_addContactNative
    (JNIEnv* env, jobject, jlong chatClientPointer, jstring jUserName)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);
    const char* userName = (env)->GetStringUTFChars(jUserName,0);

    chatClient->addContact(userName);

    (env)->ReleaseStringUTFChars(jUserName, userName);
}

/*
 * Class:     dm_chatclient_chatclient_ChatClientJNIProxy
 * Method:    changeStateNative
 * Signature: (JI)V
 */
void Java_dm_chatclient_chatclient_ChatClientJNIProxy_changeStateNative
    (JNIEnv*, jobject, jlong chatClientPointer, jint state)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);
    chatClient->changeState(static_cast<USER_STATE>(state));
}


void Java_dm_chatclient_chatclient_ChatClientJNIProxy_registerUserNative
    (JNIEnv* env,
    jobject,
    jlong   chatClientPointer,
    jstring jusername,
    jstring jpassword,
    jstring jfirstname,
    jstring jlastname)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);

    const char* username = (env)->GetStringUTFChars(jusername,0);
    const char* password = (env)->GetStringUTFChars(jpassword,0);
    const char* firstname = (env)->GetStringUTFChars(jfirstname,0);
    const char* lastname = (env)->GetStringUTFChars(jlastname,0);

    User user(-1, username,password,firstname,lastname);
    chatClient->registerUser(user);

    (env)->ReleaseStringUTFChars(jusername, username);
    (env)->ReleaseStringUTFChars(jpassword, password);
    (env)->ReleaseStringUTFChars(jfirstname, firstname);
    (env)->ReleaseStringUTFChars(jlastname, lastname);

}


void Java_dm_chatclient_chatclient_ChatClientJNIProxy_updateUserNative
(JNIEnv* env,
jobject,
jlong   chatClientPointer,
jstring jusername,
jstring jpassword,
jstring jfirstname,
jstring jlastname)
{
    IChatClient* chatClient = reinterpret_cast<IChatClient*>(chatClientPointer);

    const char* username = (env)->GetStringUTFChars(jusername,0);
    const char* password = (env)->GetStringUTFChars(jpassword,0);
    const char* firstname = (env)->GetStringUTFChars(jfirstname,0);
    const char* lastname = (env)->GetStringUTFChars(jlastname,0);

    User user(-1, username,password,firstname,lastname);
    chatClient->updateUser(user);

    (env)->ReleaseStringUTFChars(jusername, username);
    (env)->ReleaseStringUTFChars(jpassword, password);
    (env)->ReleaseStringUTFChars(jfirstname, firstname);
    (env)->ReleaseStringUTFChars(jlastname, lastname);
}
