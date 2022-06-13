# README

## dependencies

```shell
mkdir node-addon && cd node-addon
npm init -y
# 全局安装node-gyp 打包工具
npm i node-gyp -g
npm i node-addon-api
# 安装tesseract
brew install tesseract 
brew install leptonica
```
## build

```shell
node-gyp configure build
node test_tess.js
```