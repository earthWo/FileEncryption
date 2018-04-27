/**
 *
 *  wuzefeng
 *  2018/4/25
 */

//
#include <jni.h>
#include <string.h>
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


    //获取到地址
    const char *FILE_PATH=env->GetStringUTFChars(filePath, false);
    const char *FILE_NAME=env->GetStringUTFChars(path, false);


    //打开原文件
    FILE *SOURCE_FILE=fopen(FILE_PATH,"rb");

    if(SOURCE_FILE==NULL){
        LOGV("没有文件");
        return EOF;
    }


    //分解文件的列表
    FILE *file_array[count];

    //创建分解文件
    for(int i=0;i<count;i++){
        char buf[1024];
        strcpy(buf,FILE_NAME);
        sprintf(buf, "%s%d",buf,i);
        const char *mp=(const char*)buf;
        FILE *D_FILE=fopen(mp,"wb+");
        file_array[i]=D_FILE;
    }

    //将数据依次写到各个文件
    int b;
    int i=0;
    while ((b=fgetc(SOURCE_FILE))!=EOF){
        fputc(b,file_array[i]);
        i++;
        if(i>=count){
            i=0;
        }
    }

    //关闭各个文件
    for(int a=0;a<count;a++){
        fclose(file_array[a]);
    }

    //释放内存
    env->ReleaseStringUTFChars(filePath,FILE_PATH);
    env->ReleaseStringUTFChars(path,FILE_NAME);

    return 1;
}


JNIEXPORT jint JNICALL
merge(JNIEnv *env,jobject,jstring sourcePath,jobjectArray paths){

    const char *SOURCE_PATH=env->GetStringUTFChars(sourcePath, false);

    int fileCount=env->GetArrayLength(paths);


    FILE *source_file=fopen(SOURCE_PATH,"wb+");

    FILE *files[fileCount];


    for(int i=0;i<fileCount;i++){
        jstring jb= static_cast<jstring>(env->GetObjectArrayElement(paths, i));
        const char *file =env->GetStringUTFChars(jb, false);

        FILE *f=fopen(file,"rb");

        if(f==NULL){
            LOGV("%s没有找到",file);
            return 0;
        }
        files[i]=f;
    }

    int i=0;
    int byte;

    int ct=0;

    while ((byte=fgetc(files[i]))!=EOF){
        fputc(byte,source_file);
        i++;
        if(i>=fileCount){
            i=0;
            ct++;
        }
    }


    for(int a=0;a<fileCount;a++){
        fclose(files[a]);
    }

    env->ReleaseStringUTFChars(sourcePath,SOURCE_PATH);
    return 1;
}


static JNINativeMethod methods[]={
        {"fileEncryption","(Ljava/lang/String;Ljava/lang/String;)I",(void *)fileEncryption},
        {"fileDecrypt","(Ljava/lang/String;Ljava/lang/String;)I",(void *)decodeFile},
        {"fileDivision","(Ljava/lang/String;Ljava/lang/String;I)I",(void *)division},
        {"fileMerge","(Ljava/lang/String;[Ljava/lang/String;)I",(void *)merge}
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










