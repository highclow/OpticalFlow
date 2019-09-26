#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <cstdint>
#include <memory>
#include <cstring>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

enum CollapseType{collapse_average,collapse_max,collapse_min};
enum ColorType{RGB=0,BGR=1,DATA=2,GRAY=3};

template <class T>
class Image {
public:
    Image(void);
    Image(size_t width, size_t height, size_t channels=1);
    Image(const T& value,size_t width,size_t height,size_t channels=1);
    Image(const Image<T>& other);
    ~Image(void);
//    virtual Image<T>& operator=(const Image<T>& other);

    inline void setDimension(size_t width, size_t height, size_t channels=1) {
        width_ = width;
        height_ = height;
        channels_ = channels;
        pixels_ = width_ * height_;
        elements_ = pixels_ * channels_;
    };
    inline void clearDimension() {
        width_ = height_ = channels_ = pixels_ = elements_ = 0;
    }
    inline void setColorType(ColorType color_type) {color_type_ = color_type;}
    inline void setDerivative(bool derivative) {is_derivative_image_ = derivative;}
    void clear(void);
    void setValue(const T& value);
//    void setValue(const T& value,size_t _width,size_t _height,size_t _nchannels=1);

    void allocate(size_t width, size_t height, size_t channels=1);

    inline size_t width() const {return width_;}
    inline size_t height() const {return height_;}
    inline size_t channels() const {return channels_;}
    inline size_t pixels() const {return pixels_;}
    inline size_t elements() const {return elements_;}
    inline bool isDerivativeImage() const {return is_derivative_image_;};
    inline ColorType colorType() const{return color_type_;};


    inline T& operator[](size_t index) {return mutable_data()[index];};
    inline const T& operator [] (size_t index) const {return data()[index];};
    inline T* mutable_data(){return static_cast<T*>(data_);};
    inline const T* data() const{return (const T*)data_;};

    inline bool matchDimension (int width,int height,int channels) const {
        return width_ == width && height_ == height && channels_ == channels;
    }

    void generate2DGaussian(int wsize,double sigma);

    // Image Resize
    bool imresize(double ratio);

private:
    void* data_;
    size_t width_, height_, channels_;
    size_t pixels_, elements_;
    bool is_derivative_image_;
    ColorType color_type_;
};

typedef Image<uint8_t> BiImage;
typedef Image<uint8_t> UCImage;
typedef Image<uint16_t> IntImage;
typedef Image<float> FImage;
typedef Image<double> DImage;


#endif //__IMAGEIO_H__
