package win.whitelife.fileencryptionlibrary


/**
 * wuzefeng
 * 2018/4/27
 */
class FileEncryption {


    /**
     * 文件加密
     */
    external fun fileEncryption(sourcePath :String, filePath :String):Int


    /**
     * 文件解密
     */
    external fun fileDecrypt(sourcePath: String,filePath: String):Int


    /**
     * 文件分割
     */
    external fun fileDivision(sourcePath: String,name: String,count: Int):Int


    /**
     * 文件合并
     */
    external fun fileMerge(mergePath :String,filePaths: Array<String>):Int

}