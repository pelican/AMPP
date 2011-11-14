#ifndef BANDPASSADAPTER_H
#define BANDPASSADAPTER_H


#include "pelican/core/AbstractServiceAdapter.h"


/**
 * @file BandPassAdapter.h
 */

namespace pelican {

namespace lofar {

/**
 * @class BandPassAdapter
 *  
 * @brief
 *    Fills a BandPass object from a suitable bandpass data stream
 * @details
 * 
 */

class BandPassAdapter : public AbstractServiceAdapter
{
    public:
        BandPassAdapter( const ConfigNode&  );
        ~BandPassAdapter();

        // Method to deserialise chunks of memory provided by the I/O device.
        void deserialise(QIODevice* device);

    private:
};

PELICAN_DECLARE_ADAPTER(BandPassAdapter)

} // namespace lofar
} // namespace pelican
#endif // BANDPASSADAPTER_H 
