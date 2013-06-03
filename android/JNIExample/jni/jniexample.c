/*
 * jniexample.c
 *
 *  Created on: Jun 2, 2013
 *      Author: mehoggan
 */

#include <jni.h>
#include <stdlib.h>
/**
 * Simple jni code to generate the fibonacci sequence
 */
JNIEXPORT jintArray JNICALL
Java_mehdroid_jniexample_MainActivity_fib(JNIEnv * env, jobject obj, jint f)
{
	if (f <= 0) {
		return NULL;
	}

    jintArray array = (*env)->NewIntArray(env, f);
    if (array == NULL) {
    	return NULL;
    }

    jint * n_array = (jint*)malloc(sizeof(jint) * f);
    n_array[0] = 0;
    unsigned int i = 1;
    for (; i < f; ++i) {
    	if (i == 1) {
    		n_array[i] = 1;
    	} else {
    		n_array[i] = n_array[i - 1] + n_array[i - 2];
    	}
    }
    (*env)->SetIntArrayRegion(env, array, 0, f, n_array);
    free(n_array);

    return array;
}


