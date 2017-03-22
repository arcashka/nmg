#ifndef SOBEL_H
#define SOBEL_H

#include <QImage>
#include "intensitymap.h"

class NormalmapGenerator
{
public:
    enum Kernel {
        SOBEL,
        PREWITT
    };

    NormalmapGenerator(IntensityMap::Mode mode, bool useRed, bool useGreen, bool useBlue, bool useAlpha);
    QImage calculateNormalmap(const QImage& input, Kernel kernel, double strength = 2.0, bool invert = false, 
                              bool tileable = true, bool keepLargeDetail = true,
                              int largeDetailScale = 25, double largeDetailHeight = 1.0);
    const IntensityMap& getIntensityMap() const;

private:
    IntensityMap intensity;
    bool tileable;
    bool useRed, useGreen, useBlue, useAlpha;
    IntensityMap::Mode mode;

    int handleEdges(int iterator, int maxValue) const;
    int mapComponent(double value) const;
    QVector3D sobel(const double convolution_kernel[3][3], double strengthInv) const;
    QVector3D prewitt(const double convolution_kernel[3][3], double strengthInv) const;
    int blendSoftLight(int color1, int color2) const;
};

#endif // SOBEL_H
