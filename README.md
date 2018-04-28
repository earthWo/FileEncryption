# FileEncryption
### 使用jni对文件加密、解密、合并、分割

加密文件：

```
val fileEncryption= FileEncryption()
fileEncryption.fileEncryption(picPath,picEncodePath)
```

解密文件：

```
val fileEncryption= FileEncryption()
fileEncryption.fileDecrypt(picEncodePath,picDncodePath)
```

文件分割：

```
val fileEncryption= FileEncryption()
fileEncryption.fileDivision(picPath,divisionPath,10)
```

文件合并：

```
fileEncryption.fileDivision(picPath,divisionPath,10)
```

