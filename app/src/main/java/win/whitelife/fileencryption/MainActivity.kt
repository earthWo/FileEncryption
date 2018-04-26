package win.whitelife.fileencryption

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //初始化文件
        val picPath= PictureUtil.init(this)
        val picEncodePath=PictureUtil.getImagePath("/加密图片.jpg")
        val picDncodePath=PictureUtil.getImagePath("/解密图片.jpg")
        btn_encode.setOnClickListener({
            val succrss=fileEncryption(picPath,picEncodePath)
            if(succrss==1){
                tv.text="加密成功"
            }else{
                tv.text="加密失败"
            }
        })

        btn_decode.setOnClickListener({
            val succrss=fileDecrypt(picEncodePath,picDncodePath)
            if(succrss==1){
                tv.text="解密成功"
            }else{
                tv.text="解密失败"
            }
        })
    }

    external fun fileEncryption(sourcePath :String, filePath :String):Int


    external fun fileDecrypt(sourcePath: String,filePath: String):Int

    //初始化jni库
    companion object {
        init {
            System.loadLibrary("FileOperation")
        }
    }



}
