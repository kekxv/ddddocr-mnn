# 验证码识别MNN版本

使用方式：
```shell
git clone https://github.com/kekxv/ddddocr-mnn.git
cd ddddocr-mnn 
git submodule update --init 
mkdir build 
cd build 
cmake ..
make ocrCaptchaMnn
./ocrCaptchaMnn ../ocr.captcha.sim.mnn ../captcha.png
# 输出结果
```

模型来自： https://github.com/sml2h3/ddddocr

相关源码：
[OcrCaptcha.hpp](OcrCaptcha.hpp)
[main.cpp](main.cpp)

模型：
[ocr.captcha.sim.mnn](ocr.captcha.sim.mnn)

执行结果

![result.png](assets%2Fresult.png)