#include <iostream>
#include "OcrCaptcha.hpp"

int main(int argc, const char *argv[]) {
  std::string onnx_path = "ocr.captcha.sim.mnn";
  std::string img_path = "captcha.png";
  if (argc == 3) {
    onnx_path = argv[1];
    img_path = argv[2];
  }
  if (argc == 2) {
    img_path = argv[1];
  }
  auto ocrCaptcha = std::make_shared<OcrCaptcha>();
  if (!ocrCaptcha->init_model(onnx_path.c_str())) {
    std::cerr << "load model error : " << onnx_path << std::endl;
    return 2;
  }
  std::cout << "load model success : " << onnx_path << std::endl;
  std::string result;
  auto ret = ocrCaptcha->detect(result, img_path.c_str());
  if (ret <= 0) {
    std::cerr << "ocr captcha error." << std::endl;
    return 1;
  }
  std::cout << "ocr captcha : " << result << std::endl;
  return 0;
}
