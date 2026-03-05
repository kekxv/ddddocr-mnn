# 验证码识别MNN版本

## 使用方式

### 基本编译和运行

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

### 运行测试

编译完成后，可以使用以下命令运行测试：

```shell
# 方式1: 使用CTest
cd build
ctest --output-on-failure -V

# 方式2: 使用测试脚本
bash test.sh build/ocrCaptchaMnn ocr.captcha.sim.mnn captcha.png
```

## 模型来源

模型来自： https://github.com/sml2h3/ddddocr
[OcrCaptcha.hpp](OcrCaptcha.hpp)
[main.cpp](main.cpp)

模型：
[ocr.captcha.sim.mnn](ocr.captcha.sim.mnn)

执行结果

![result.png](assets%2Fresult.png)