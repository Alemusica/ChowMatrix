#include "BaseNode.h"
#include "InputNode.h"
#include "DelayNode.h"
#include "../gui/DelayNodeComponent.h"

template<typename Child>
BaseNode<Child>::BaseNode()
{

}

template<typename Child>
void BaseNode<Child>::prepare (double newSampleRate, int newSamplesPerBlock)
{
    sampleRate = newSampleRate;
    samplesPerBlock = newSamplesPerBlock;

    for (auto* child : children)
        child->prepare (sampleRate, samplesPerBlock);
}

template<typename Child>
void BaseNode<Child>::process (AudioBuffer<float>& inBuffer, AudioBuffer<float>& outBuffer, const int numSamples)
{
    for (auto* child : children)
        child->process (inBuffer, outBuffer, numSamples);
}

template<typename Child>
NodeComponent* BaseNode<Child>::getEditor()
{
    return editor;
}

template<typename Child>
Child* BaseNode<Child>::addChild()
{
    auto newChild = std::make_unique<Child>();
    newChild->setParent (this);

    return children.add (std::move (newChild));
}

template<typename Child>
void BaseNode<Child>::setParent (BaseNode* newParent)
{
    parent = newParent;
    prepare (parent->sampleRate, parent->samplesPerBlock);
}

template class BaseNode<DelayNode>;
