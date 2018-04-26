package win.whitelife.fileencryption

import android.content.Context
import android.os.Environment
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream

/**
 * wuzefeng
 * 2018/4/26
 */
class PictureUtil {


    //初始化时将图片复制到sd卡上
    companion object {

         fun init(content: Context):String {
            val filePath=getImagePath("/pic1.jpg")
            val file = File(filePath)
            //文件不存在
            if(!file.exists()){
                //保存文件
                file.createNewFile()
                val inputStream= content.assets.open("pic1.jpg")
                saveToFile(file,inputStream)
            }
            return filePath
        }

        /**
         * 根据名字获取图片地址
         */
        fun getImagePath(name :String):String{
            return getSDCardPath()+name
        }

        /**
         * 获取sd卡位置
         */
        private fun getSDCardPath():String{
            return Environment.getExternalStorageDirectory().absolutePath
        }

        /**
         * 将图片保存到文件
         */
        private fun saveToFile(file: File, stream:InputStream){

            val outputStream=FileOutputStream(file)

            var b :Int
            var bytes= ByteArray(1024)
            do {
                b=stream.read(bytes,0,bytes.size)
                if(b==-1){
                    break
                }
                outputStream.write(bytes,0,b)
            }while(true)

            outputStream.close()
            stream.close()
        }
    }

}