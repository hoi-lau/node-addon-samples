#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <napi.h>

#define EXPORT_JS_FUNCTION_PARAM(name) exports.Set(#name, Napi::Function::New(env, name));

tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

// clang++   tess.o  -std=c++20 -v  -ltesseract -llept  -stdlib=libc++  -o tess
void InitTess(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() == 0 || !info[0].IsString()) {
    Napi::TypeError::New(env, "Language code expected").ThrowAsJavaScriptException();
    return;
  }
  // 0 is ok
  if (api->Init(NULL, (info[0].As<Napi::String>()).Utf8Value().c_str())) {
    Napi::TypeError::New(env, "Init failed").ThrowAsJavaScriptException();
    return;
  }
}

void SetImage(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() == 0 || !info[0].IsString()) {
    Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    return ;
  }
  Pix *image = pixRead((info[0].As<Napi::String>()).Utf8Value().c_str());
  api->SetImage(image);
}

Napi::String GetUTF8Text(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  char *outText = api->GetUTF8Text();
  Napi::String str = Napi::String::New(env, outText);
  delete outText;
  return str;
}

void ChangeLang(const Napi::CallbackInfo& info) {
  api->End();
  InitTess(info);
}

void DestroyTess(const Napi::CallbackInfo& info) {
  api->End();
  delete api;
}

// 导出注册函数
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  EXPORT_JS_FUNCTION_PARAM(InitTess)
  EXPORT_JS_FUNCTION_PARAM(DestroyTess)
  EXPORT_JS_FUNCTION_PARAM(ChangeLang)
  EXPORT_JS_FUNCTION_PARAM(SetImage)
  EXPORT_JS_FUNCTION_PARAM(GetUTF8Text)
  return exports;
}
// node-addon-api 中用于注册函数的宏
// hello 为 key, 可以是任意变量
// Init 则会注册的函数
NODE_API_MODULE(Tess, Init);