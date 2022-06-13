{
  "targets": [
    {
      "target_name": "tess",
      # 被编译的 cpp 源文件
      "sources": [
        "tess.cpp"
      ],
      "cflags!": [ "-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      # 增加一个头文件搜索路径
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/usr/local/include"
      ],
      'libraries': [
        '/usr/local/lib/libtesseract.dylib',
        '/usr/local/lib/libleptonica.dylib'
      ],
      # 添加一个预编译宏，避免编译的时候并行抛错
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}