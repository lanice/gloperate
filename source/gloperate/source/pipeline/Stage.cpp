
#include <gloperate/pipeline/Stage.h>

#include <algorithm>

#include <gloperate/pipeline/Pipeline.h>
#include <gloperate/pipeline/AbstractInput.h>
#include <gloperate/pipeline/AbstractParameter.h>
#include <gloperate/pipeline/AbstractOutput.h>
#include <gloperate/pipeline/AbstractProxyOutput.h>


namespace gloperate
{


Stage::Stage(ViewerContext * viewerContext, const std::string & name, Pipeline * parent)
: cppexpose::Object(name, parent)
, m_viewerContext(viewerContext)
, m_parentPipeline(parent)
{
    if (parent) {
        parent->registerStage(this);
    }
}

Stage::~Stage()
{
    if (m_parentPipeline) {
        m_parentPipeline->unregisterStage(this);
    }
}

bool Stage::isPipeline() const
{
    return false;
}

ViewerContext * Stage::viewerContext() const
{
    return m_viewerContext;
}

Pipeline * Stage::parentPipeline() const
{
    return m_parentPipeline;
}

void Stage::transferStage(Pipeline * parent)
{
    // Abort if the parent pipeline is already set or parameter is empty
    if (m_parentPipeline || !parent) {
        return;
    }

    // Set new parent
    m_parentPipeline = parent;
    m_parentPipeline->registerStage(this);
    initProperty(m_parentPipeline, m_name);
    parent->takeOwnership(m_parentPipeline);
}

void Stage::initContext(AbstractGLContext * context)
{
    onContextInit(context);
}

void Stage::deinitContext(AbstractGLContext * context)
{
    onContextDeinit(context);
}

void Stage::process(AbstractGLContext * context)
{
    onProcess(context);
}

const std::vector<AbstractInput *> & Stage::inputs() const
{
    return m_inputs;
}

const AbstractInput * Stage::input(const std::string & name) const
{
    return m_inputsMap.at(name);
}

const std::vector<AbstractParameter *> & Stage::parameters() const
{
    return m_parameters;
}

const AbstractParameter * Stage::parameter(const std::string & name) const
{
    return m_parametersMap.at(name);
}

const std::vector<AbstractOutput *> & Stage::outputs() const
{
    return m_outputs;
}

const AbstractOutput * Stage::output(const std::string & name) const
{
    return m_outputsMap.at(name);
}

const std::vector<AbstractProxyOutput *> & Stage::proxyOutputs() const
{
    return m_proxyOutputs;
}

const AbstractProxyOutput * Stage::proxyOutput(const std::string & name) const
{
    return m_proxyOutputsMap.at(name);
}

void Stage::registerInput(AbstractInput * input)
{
    // Check parameters
    if (!input) {
        return;
    }

    // Add input
    m_inputs.push_back(input);
    if (input->name() != "") {
        m_inputsMap.insert(std::make_pair(input->name(), input));        
    }

    // Emit signal
    inputAdded(input);
}

void Stage::unregisterInput(AbstractInput * input)
{
    // Check parameters
    if (!input)
    {
        return;
    }

    // Find input
    auto it = std::find(m_inputs.begin(), m_inputs.end(), input);
    if (it != m_inputs.end())
    {
        // Remove input
        m_inputs.erase(it);
        m_inputsMap.erase(input->name());
        inputRemoved(input);
    }
}

void Stage::registerParameter(AbstractParameter * parameter)
{
    // Check parameters
    if (!parameter) {
        return;
    }

    // Add parameter
    m_parameters.push_back(parameter);
    if (parameter->name() != "") {
        m_parametersMap.insert(std::make_pair(parameter->name(), parameter));        
    }

    // Emit signal
    parameterAdded(parameter);
}

void Stage::unregisterParameter(AbstractParameter * parameter)
{
    // Check parameters
    if (!parameter)
    {
        return;
    }

    // Find parameter
    auto it = std::find(m_parameters.begin(), m_parameters.end(), parameter);
    if (it != m_parameters.end())
    {
        // Remove parameter
        m_parameters.erase(it);
        m_parametersMap.erase(parameter->name());
        parameterRemoved(parameter);
    }
}

void Stage::registerOutput(AbstractOutput * output)
{
    // Check parameters
    if (!output) {
        return;
    }

    // Add output
    m_outputs.push_back(output);
    if (output->name() != "") {
        m_outputsMap.insert(std::make_pair(output->name(), output));        
    }

    // Emit signal
    outputAdded(output);
}

void Stage::unregisterOutput(AbstractOutput * output)
{
    // Check parameters
    if (!output)
    {
        return;
    }

    // Find output
    auto it = std::find(m_outputs.begin(), m_outputs.end(), output);
    if (it != m_outputs.end())
    {
        // Remove output
        m_outputs.erase(it);
        m_outputsMap.erase(output->name());
        outputRemoved(output);
    }
}

void Stage::registerProxyOutput(AbstractProxyOutput * proxyOutput)
{
    // Check parameters
    if (!proxyOutput) {
        return;
    }

    // Add proxy output
    m_proxyOutputs.push_back(proxyOutput);
    if (proxyOutput->name() != "") {
        m_proxyOutputsMap.insert(std::make_pair(proxyOutput->name(), proxyOutput));        
    }

    // Emit signal
    proxyOutputAdded(proxyOutput);
}

void Stage::unregisterProxyOutput(AbstractProxyOutput * proxyOutput)
{
    // Check parameters
    if (!proxyOutput)
    {
        return;
    }

    // Find proxy output
    auto it = std::find(m_proxyOutputs.begin(), m_proxyOutputs.end(), proxyOutput);
    if (it != m_proxyOutputs.end())
    {
        // Remove proxy output
        m_proxyOutputs.erase(it);
        m_proxyOutputsMap.erase(proxyOutput->name());
        proxyOutputRemoved(proxyOutput);
    }
}

void Stage::onContextInit(AbstractGLContext *)
{
}

void Stage::onContextDeinit(AbstractGLContext *)
{
}

void Stage::onProcess(AbstractGLContext *)
{
}


} // namespace gloperate
