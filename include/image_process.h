#ifndef __IMAGE_PROCESS_H__
#define __IMAGE_PROCESS_H__

enum InterpolationType {BILINEAR=0, BICUBIC};

template <class T1,class T2>
inline T1 __min(T1 a, T2 b) {
    return (a>b) ? b : a;
}

template <class T1,class T2>
inline T1 __max(T1 a, T2 b) {
    return (a<b) ? b : a;
}

template <class T>
inline T EnforceRange(const T& x,const int& MaxValue) {
    return __min(__max(x,0),MaxValue-1);
}

template <class T1,class T2>
inline void BilinearInterpolate(const T1* pImage, 
                                int width, int height, int nChannels,
                                double x, double y, T2* result) {   
    int xx,yy,m,n,u,v,l,offset;
    xx=x;
    yy=y;
    double dx,dy,s;
    dx=__max(__min(x-xx,1),0);
    dy=__max(__min(y-yy,1),0);
    
    for(m=0;m<=1;m++) {
        for(n=0;n<=1;n++) {   
            u=EnforceRange(xx+m,width);
            v=EnforceRange(yy+n,height);
            offset=(v*width+u)*nChannels;
            s=fabs(1-m-dx)*fabs(1-n-dy);
            for(l=0;l<nChannels;l++) {
                result[l]+=pImage[offset+l]*s;
            }
        }
    }
}


template <class T1,class T2>
void ResizeImage(const T1* pSrcImage, T2* pDstImage,
                 size_t srcWidth, size_t srcHeight, size_t channels,
                 double ratio, InterpolationType type=BILINEAR) {
    size_t dstWidth, dstHeight;
    dstWidth=static_cast<double>(srcWidth*ratio);
    dstHeight=static_cast<double>(srcHeight*ratio);
    double x,y;
    size_t offset = 0;
    assert(type==BILINEAR);
    for(size_t i=0; i<dstHeight; ++i) {
        for(size_t j=0; j<dstWidth; ++j) {
            x=static_cast<double>((j+1)/ratio-1);
            y=static_cast<double>((i+1)/ratio-1);
            BilinearInterpolate(pSrcImage,srcWidth,srcHeight,channels,x,y,pDstImage+offset);
            offset += channels;
        }
    }
}

//template <class T1,class T2>
//void ResizeImage(const T1 *pSrcImage, T2 *pDstImage,
//                 int SrcWidth, int SrcHeight, int nChannels,
//                 int DstWidth, int DstHeight, InterpolationType=BILINEAR) {
//    double xRatio=(double)DstWidth/SrcWidth;
//    double yRatio=(double)DstHeight/SrcHeight;
//    memset(pDstImage,sizeof(T2)*DstWidth*DstHeight*nChannels,0);
//
//    double x,y;
//
//    for(int i=0;i<DstHeight;i++)
//        for(int j=0;j<DstWidth;j++)
//        {
//            x=(double)(j+1)/xRatio-1;
//            y=(double)(i+1)/yRatio-1;
//
//            // bilinear interpolation
//            BilinearInterpolate(pSrcImage,SrcWidth,SrcHeight,nChannels,x,y,pDstImage+(i*DstWidth+j)*nChannels);
//        }
//}




#endif // __IMAGE_PROCESS_H__
