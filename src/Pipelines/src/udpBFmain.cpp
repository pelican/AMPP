#include "pelican/core/PipelineApplication.h"

#include "LofarStreamDataClient.h"
#include "UdpBFPipeline.h"
#include "AdapterTimeSeriesDataSet.h"
#include "PumaOutput.h"
#include "BandPassOutput.h"

#include <QtCore/QCoreApplication>

#include <iostream>
#include <map>

using std::cout;
using std::endl;
using namespace pelican;
using namespace pelican::lofar;

int main(int argc, char* argv[])
{
    // Create a QCoreApplication.
    QCoreApplication app(argc, argv);

    try {
        // Create a PipelineApplication.
        PipelineApplication pApp(argc, argv);

        // Register the pipelines that can run.
        pApp.registerPipeline(new UdpBFPipeline("LofarDataStream1"));

        // Set the data client.
        pApp.setDataClient("LofarStreamDataClient");

        // Start the pipeline driver.
        pApp.start();
    }
    catch (const QString& err) {
        cout << "Error caught in updBFmain.cpp: " << err.toStdString() << endl;
    }

    return 0;
}
