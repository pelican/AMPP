#ifndef BANDPASS_H
#define BANDPASS_H


#include "pelican/data/DataBlob.h"
#include "BinMap.h"
#include "Range.h"

#include <QtCore/QVector>
#include <QtCore/QHash>
#include <QtCore/QPair>
#include <QtCore/QSet>

/**
 * @file BandPass.h
 */

namespace pelican {

namespace lofar {

/**
 * @class BandPass
 *
 * @brief
 *    Interface to the stations bandpass
 * @details
 *    Takes a description of the bandpass as a polynomial
 * and allows rescaling etc. appropriately. The polynomial
 * is always linked to a primary BinMap and all conversions
 * are done relative to this primary map
 */
class BinnedData;

class BandPass : public DataBlob
{
    public:
        BandPass(  );
        ~BandPass();
        void setData(const BinMap&,const QVector<float>& params );
        void setRMS(float);
        /// set a new median and rescale the polynomial
        //  appropriately. Does not rebin the hash
        void setMedian(float);

        /// return the coefficients of the underlying polynomial
        const QVector<float>& params() const { return _params; };

        // rest object to use the primary binning map
        void resetMap();
        const BinMap& primaryMap() const { return _primaryMap; };

        void reBin(const BinMap& map);
        float startFrequency() const;
        float endFrequency() const;
        float intensity(float frequency) const;

        /// return a reference to the binned data corresponding to the current bin mapping
        //  (call to reBin)
        const QVector<float>& currentSet() { return _dataSets[_currentMapId]; };

        inline float intensityOfBin(unsigned int index) const {
            return _dataSets[_currentMapId][index];
        };
        /// return the median for the current bin mapping
        inline float median() const { return _median[_currentMapId]; }

        /// return the median for the primary bin mapping
        inline float primaryMedian() const { return _median[_primaryMapId]; }

        /// return the rms for the current bin mapping
        inline float rms() const { return _rms[_currentMapId]; }

        /// return the rms for the primary bin mapping
        inline float primaryRms() const { return _rms[_primaryMapId]; }

        // Mark channels to be killed (set to 0)
        void killChannel(unsigned int index);
        void killBand(float startFreq, float endFreq);

        // return true if bin has been killed
        bool filterBin( unsigned int i ) const;

    protected:
        float _evaluate(float) const; // calculate value of parameterised eqn
        void _zeroChannelsMap(const BinMap& map);
        // build a data map, scaled appropriately
        void _buildData(const BinMap& map, float scale, float offset);

    private:
        int _nChannels;
        BinMap _primaryMap;
        BinMap _currentMap;
        int _currentMapId;
        int _primaryMapId;
        QVector<float> _params;
        float _deltaFreq;
        QHash<int, QVector<float> > _dataSets;
        QHash<int,float> _rms;
        QHash<int,float> _median;
        QHash<int,float> _mean;
        Range<float> _killed;
};

PELICAN_DECLARE_DATABLOB(BandPass)

} // namespace lofar
} // namespace pelican


#endif // BANDPASS_H
