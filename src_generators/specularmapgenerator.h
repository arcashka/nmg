#ifndef SPECULARMAPGENERATOR_H
#define SPECULARMAPGENERATOR_H

#include "src_generators/intensitymap.h"

class SpecularmapGenerator
{
public:
    SpecularmapGenerator(IntensityMap::Mode mode, double redMultiplier, double greenMultiplier, double blueMultiplier, double alphaMultiplier);
    QImage calculateSpecmap(const QImage& input, double scale, double contrast);

private:
    double redMultiplier, greenMultiplier, blueMultiplier, alphaMultiplier;
    IntensityMap::Mode mode;
};

#endif // SPECULARMAPGENERATOR_H
