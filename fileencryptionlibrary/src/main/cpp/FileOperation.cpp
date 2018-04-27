/**
 *  wuzefeng
 *  2018/4/25
 */

//
#include <jni.h>
#include <string>
#include <stdio.h>
#include <android/log.h>


#define TAG "native打印"
#define LOGV(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);



int encode(int b){
    return b+100;
}

int decode(int b){
    return b-100;
}

//对传入的文件进行加密，保存
extern "C"
JNIEXPORT jint JNICALL
fileEncryption(JNIEnv *env,jobject,jstring sourcePath,jstring filePath){

    //将jstring转化为普通的字符串
    const char *SPath=env->GetStringUTFChars(sourcePath, false);
    const char *FPath=env->GetStringUTFChars(filePath, false);

    //获取到两个文件，没有则创建
    FILE *SOURCE_FILE= fopen(SPath,"rb");
    FILE *ENCODE_FILE= fopen(FPath,"wb+");

    if(SOURCE_FILE==NULL){
        LOGV("文件不存在");
        return EOF;
    }

    int b;
    while((b=fgetc(SOURCE_FILE))!=EOF){
        fputc(encode(b),ENCODE_FILE);
    }

    fclose(SOURCE_FILE);
    fclose(ENCODE_FILE);

    env->ReleaseStringUTFChars(sourcePath,SPath);
    env->ReleaseStringUTFChars(filePath,FPath);

    LOGV("文件加密完成");
    return 1;
}


/**
 * 解密图片
 * @param env
 * @param sourseFile
 * @param file
 * @return
 */
JNIEXPORT jint JNICALL
decodeFile(JNIEnv *env,jobject ,jstring sourceFile,jstring file){

    const char *SFILE=env->GetStringUTFChars(sourceFile, false);
    const char *PFILE=env->GetStringUTFChars(file, false);

    FILE *SOURCE_FILE= fopen(SFILE,"rb");
    FILE *DECODE_FILE= fopen(PFILE,"wb+");

    if(SOURCE_FILE==NULL){
        LOGV("没有文件");
        return EOF;
    }

    int b;

    while ((b=fgetc(SOURCE_FILE))!=EOF){
        fputc(decode(b),DECODE_FILE);
    }

    fclose(SOURCE_FILE);
    fclose(DECODE_FILE);

    env->ReleaseStringUTFChars(sourceFile,SFILE);
    env->ReleaseStringUTFChars(file,PFILE);
    LOGV("解码成功");
    return 1;
}


/**
 * 将文件分为多个
 * @param env
 * @param filePath
 * @param fileName
 * @param count
 * @return
 */
JNIEXPORT jint JNICALL
division(JNIEnv *env,jobject,jstring filePath,jstring path,jint count){

    const char *FILE_PATH=env->GetStringUTFChars(filePath, false);
    const char *FILE_NAME=env->GetStringUTFChars(path, false);

    FILE *FILE=fopen(FILE_PATH,"rb");
    if(FILE==NULL){
        LOGV("没有文件");
        return EOF;
    }

    for(int i=1;i<=count;i++){
    }

    int b;
    while ((b=fgetc(FILE))!=EOF){



    }



    return 1;
}


static JNINativeMethod methods[]={
        {"fileEncryption","(Ljava/lang/String;Ljava/lang/String;)I",(void *)fileEncryption},
        {"fileDecrypt","(Ljava/lang/String;Ljava/lang/String;)I",(void *)decodeFile},
        {"fileDivision","(Ljava/lang/String;Ljava/lang/String;I;)I",(void *)division}
};

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void * reserved){
    //判断是是否有1_6的环境
    JNIEnv * env;
    if(vm->GetEnv((void **)&env,JNI_VERSION_1_6)!=JNI_OK){
        return JNI_ERR;
    }

    jclass cla;
    if((cla=env->FindClass("win/whitelife/fileencryptionlibrary/FileEncryption"))==NULL){
        return JNI_ERR;
    }

    if(env->RegisterNatives(cla,methods, sizeof(methods)/sizeof(methods[0]))==EOF){
        return JNI_ERR;
    }


    return JNI_VERSION_1_6;
}










