
#include "OsgScene.h"

#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>


using namespace gloperate;
using namespace gloperate_osg;


OsgScene::OsgScene(gloperate::ResourceManager & resourceManager, const std::map<std::string, std::string> & relDataPaths)
: OsgPainter("osgScene", resourceManager, relDataPaths)
{
}

OsgScene::~OsgScene()
{
}

void OsgScene::onInitialize()
{
    OsgPainter::onInitialize();

    setScene(osgDB::readNodeFile(m_relDataPaths[""] + "data/osg-scene/cow.osg"));

    viewer()->setCameraManipulator(new osgGA::TrackballManipulator());

    osgViewer::StatsHandler * statsHandler = new osgViewer::StatsHandler;
    viewer()->addEventHandler(statsHandler);
}
