package win.whitelife.fileencryption

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import win.whitelife.fileencryptionlibrary.FileEncryption
import java.io.File

class MainActivity : AppCompatActivity() {


    var fileEncryption :FileEncryption?=null


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //初始化文件
        val picPath= PictureUtil.init(this)
        val picEncodePath=PictureUtil.getImagePath("/加密图片.jpg")
        val picDncodePath=PictureUtil.getImagePath("/解密图片.jpg")
        val divisionPath=PictureUtil.getImagePath("/分解/division")
        val mergePath=PictureUtil.getImagePath("/合并图片.jpg")
        fileEncryption= FileEncryption()

        btn_encode.setOnClickListener({
            val succrss= fileEncryption!!.fileEncryption(picPath,picEncodePath)
            if(succrss==1){
                tv.text="加密成功"
            }else{
                tv.text="加密失败"
            }
        })

        btn_decode.setOnClickListener({
            val succrss= fileEncryption!!.fileDecrypt(picEncodePath,picDncodePath)
            if(succrss==1){
                tv.text="解密成功"
            }else{
                tv.text="解密失败"
            }
        })


        btn_division.setOnClickListener {

            val file= File(divisionPath)
            if(!file.parentFile.exists()){
                file.parentFile.mkdirs()
            }
            val success= fileEncryption!!.fileDivision(picPath,divisionPath,10)
            if(success==1){
                tv.text="分解成功"
            }else{
                tv.text="分解失败"
            }
        }


        btn_merge.setOnClickListener{
            val file=File(divisionPath).parentFile
            if(!file.exists()||!file.isDirectory){
                Toast.makeText(this,"文件夹不存在",Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val listFiles = file.listFiles()
            val listPath=Array<String>(listFiles.size,{
                listFiles[it].absolutePath
            })
            val success= fileEncryption!!.fileMerge(mergePath,listPath)
            if(success==1){
                tv.text="合并成功"
            }else{
                tv.text="合并失败"
            }
        }
    }



    //初始化jni库
    companion object {
        init {
            System.loadLibrary("FileOperation")
        }
    }



}
