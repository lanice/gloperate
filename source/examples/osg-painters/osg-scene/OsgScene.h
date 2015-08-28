
#pragma once

#include <gloperate-osg/OsgPainter.h>


class OsgScene : public gloperate_osg::OsgPainter
{
public:
    OsgScene(gloperate::ResourceManager & resourceManager, const std::map<std::string, std::string> & relDataPaths);
    virtual ~OsgScene();


protected:
    virtual void onInitialize() override;
};
