#include "image.h"
#include "image_process.h"


template <class T>
Image<T>::Image(void) {
    data_ = nullptr;
    clearDimension();
    setColorType(RGB);
    setDerivative(false);
}

template <class T>
Image<T>::Image(size_t width, size_t height, size_t channels) {
    setDimension(width, height, channels);
    setColorType(RGB);
    setDerivative(false);
    assert(elements_ > 0);
    data_ = (void*) malloc(sizeof(T) * elements_);
    memset(data_, 0, sizeof(T)*elements_);
}

template <class T>
Image<T>::Image(const T& value, size_t width, size_t height,size_t channels) {
    setDimension(width, height, channels);
    setColorType(RGB);
    setDerivative(false);
    assert(elements_ > 0);
    data_ = (void*) malloc(sizeof(T) * elements_);
    setValue(value);
}

template <class T>
Image<T>::Image(const Image<T>& other) {
    setDimension(other.width(), other.height(), other.channels());
    setColorType(other.colorType());
    setDerivative(other.isDerivativeImage());
    assert(elements_ > 0);
    data_ = (void*) malloc(sizeof(T) * elements_);
    memcpy(data_,other.data_,sizeof(T)*elements_);
}

template <class T>
Image<T>::~Image(void) {
    free(data_);
}


template <class T>
void Image<T>::clear(void) {
    if (data_ != nullptr) {
      free(data_);
      data_ = nullptr;
    }
    clearDimension();
}


template <class T>
void Image<T>::allocate(size_t width, size_t height, size_t channels) {
    if (matchDimension(width, height, channels))
        return;
    setDimension(width, height, channels);
    assert(elements_ > 0);
    data_ = (void*) malloc(sizeof(T) * elements_);
}


template <class T>
void Image<T>::setValue(const T &value) {
    for(size_t i=0; i<elements_; i++){
        mutable_data()[i]=value;
    }
}


template <class T>
void Image<T>::generate2DGaussian(int wsize,double sigma) {
    size_t wlen = wsize * 2 + 1;
    allocate(wlen, wlen, 1);
    if(sigma == -1) {
        sigma = wsize/2;
    }
    double alpha = 1 / (2*sigma*sigma);
    double total = 0;
    T *pData = this->mutable_data();
    for(int i=-wsize; i<=wsize; i++) {
        for(int j=-wsize; j<=wsize; j++) {
            *pData = exp(static_cast<double>(-alpha*(i*i+j*j)));
            total += pData[0];
            ++pData;
        }
    }
    for(size_t i = 0;i<elements_;i++) {
        this->mutable_data()[i] /= total;
    }
}


template <class T>
bool Image<T>::imresize(double ratio) {
    if (data_ == nullptr) {
        return false;
    }
    size_t dstWidth, dstHeight, dstChannels;
    dstWidth = static_cast<size_t>(ratio * width_);
    dstHeight = static_cast<size_t>(ratio * height_);
    dstChannels = channels_;
    size_t size = dstWidth * dstHeight * dstChannels * sizeof(T);
    T* pDstData = (T*)malloc(size);
    memset(pDstData, 0, size);
    ResizeImage((T*)data_, pDstData, width_, height_, channels_,ratio);
    clear();
    setDimension(dstWidth, dstHeight, dstChannels);
    data_ = (void*)pDstData;
    return true;
}


template class Image<float>;
template class Image<double>;
