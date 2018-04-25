package win.whitelife.fileencryption

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)



    }

    external fun a():Int


    //初始化jni库
    companion object {
        init {
            System.loadLibrary("FileOperation")
        }
    }



}
