//
// Created by caesar kekxv on 2024/1/15.
//

#ifndef OCRCAPTCHAMNN_OCRCAPTCHA_HPP
#define OCRCAPTCHAMNN_OCRCAPTCHA_HPP

#include "string"
#include <MNN/ImageProcess.hpp>
#include <MNN/Interpreter.hpp>
#include "words.h"
#include "opencv2/opencv.hpp"

using namespace MNN;
using namespace std;
using namespace cv;

class OcrCaptcha {
private:
  int height = 64;
  std::shared_ptr<MNN::Interpreter> mnn_interpreter;
  MNN::BackendConfig backend_config;
  MNN::ScheduleConfig schedule_config;
public:
  explicit inline OcrCaptcha(int height = 64) : height(height) {};

  inline bool init_model(const char *path) {
    if (path == nullptr)return false;
    mnn_interpreter = std::shared_ptr<MNN::Interpreter>(
        MNN::Interpreter::createFromFile(path));
    if (mnn_interpreter == nullptr) {
      return false;
    }
    backend_config.precision = MNN::BackendConfig::Precision_High; // default Precision_High
    schedule_config.numThread = (int) 2;
    schedule_config.backendConfig = &backend_config;
    return true;
  }

  void mat2tensor(const Mat &image, MNN::Session *session) {
    cv::Mat preImage = image.clone();
    if (preImage.channels() == 3) {
      cv::cvtColor(preImage, preImage, cv::COLOR_BGR2GRAY);
    }
    preImage.convertTo(preImage, CV_32F, 1. / 255.);
    preImage = (preImage - 0.5) / 0.5;

    auto inTensor = mnn_interpreter->getSessionInput(session, nullptr);
    mnn_interpreter->resizeTensor(inTensor, 1, 1, preImage.size().height, preImage.size().width);
    mnn_interpreter->resizeSession(session);

    auto nchw_Tensor = new MNN::Tensor(inTensor, MNN::Tensor::CAFFE);
    ::memcpy(nchw_Tensor->host<float>(), preImage.data, nchw_Tensor->elementSize() * 4);
    inTensor->copyFromHostTensor(nchw_Tensor);
    delete nchw_Tensor;
  }

  inline int detect(std::string &result, const char *file) {
    return detect(result, cv::imread(file, cv::IMREAD_COLOR));
  }

  inline int detect(std::string &result, const cv::Mat &image) {
    if (image.empty())return -2; // 2. init schedule_config
    auto mnn_session = mnn_interpreter->createSession(schedule_config);
    auto size = cv::Size{
        (int) (static_cast<float >(image.size().width) *
               (static_cast<float >(height) / static_cast<float >(image.size().height))), height};
    cv::Mat mat_rs = image.clone();
    cv::resize(mat_rs, mat_rs, size);
    mat2tensor(mat_rs, mnn_session);

    mnn_interpreter->runSession(mnn_session);

    auto output = mnn_interpreter->getSessionOutput(mnn_session, nullptr);
    auto ptr = output->host<int>();
    int last_item = 0;
    for (int i = 0; i < output->shape()[1]; i++) {
      if (last_item == ptr[i])continue;
      last_item = ptr[i];
      if (last_item == 0)continue;
      result += words[last_item];
    }
    mnn_interpreter->releaseSession(mnn_session);
    return static_cast<int>(result.size());
  }
};

#endif //OCRCAPTCHAMNN_OCRCAPTCHA_HPP
