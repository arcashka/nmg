#ifndef INTENSITYMAP_H
#define INTENSITYMAP_H

#include <QImage>

class IntensityMap
{
public:
    enum Mode {
        AVERAGE,
        MAX
    };

    IntensityMap();
    IntensityMap(int width, int height);
    IntensityMap(const QImage &rgbImage, Mode mode, bool useRed = true, bool useGreen = true, bool useBlue = true, bool useAlpha = false);
    double at(int x, int y) const;
    double at(int pos) const;
    void setValue(int x, int y, double value);
    void setValue(int pos, double value);
    size_t getWidth() const;
    size_t getHeight() const;
    void invert();
    QImage convertToQImage() const;

private:
    std::vector< std::vector<double> > map;
};

#endif // INTENSITYMAP_H
