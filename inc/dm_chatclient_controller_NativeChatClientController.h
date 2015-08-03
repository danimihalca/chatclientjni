/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class dm_chatclient_controller_NativeChatClientController */

#ifndef _Included_dm_chatclient_controller_NativeChatClientController
#define _Included_dm_chatclient_controller_NativeChatClientController
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     dm_chatclient_controller_NativeChatClientController
 * Method:    createClientNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_dm_chatclient_controller_NativeChatClientController_createClientNative
  (JNIEnv *, jobject);

/*
 * Class:     dm_chatclient_controller_NativeChatClientController
 * Method:    setServerPropertiesNative
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_controller_NativeChatClientController_setServerPropertiesNative
  (JNIEnv *, jobject, jlong, jstring, jint);

/*
 * Class:     dm_chatclient_controller_NativeChatClientController
 * Method:    loginNative
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_controller_NativeChatClientController_loginNative
  (JNIEnv *, jobject, jlong, jstring, jstring);

/*
 * Class:     dm_chatclient_controller_NativeChatClientController
 * Method:    disconnectNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_controller_NativeChatClientController_disconnectNative
  (JNIEnv *, jobject, jlong);

/*
 * Class:     dm_chatclient_controller_NativeChatClientController
 * Method:    sendMessageNative
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_controller_NativeChatClientController_sendMessageNative
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     dm_chatclient_controller_NativeChatClientController
 * Method:    destroyClientNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_controller_NativeChatClientController_destroyClientNative
  (JNIEnv *, jobject, jlong);

/*
 * Class:     dm_chatclient_controller_NativeChatClientController
 * Method:    requestContactsNative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_dm_chatclient_controller_NativeChatClientController_requestContactsNative
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
