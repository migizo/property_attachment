/*
  ==============================================================================

    PropertyAttachment.cpp
    Author:  migizo

  ==============================================================================
*/

#include "PropertyAttachment.h"

//==============================================================================
PropertyAttachment::PropertyAttachment(juce::ValueTree vt,
                                       const juce::Identifier& propId,
                                       juce::UndoManager* um,
                                       std::function<void(const juce::var&)> propertyChangedCallback)
: state(vt)
, propertyId(propId)
, undoManager(um)
, setValue(std::move(propertyChangedCallback))
{
    sendInitialUpdate();
    state.addListener(this);
}

PropertyAttachment::~PropertyAttachment()
{
    state.removeListener(this);
    cancelPendingUpdate();
}

//==============================================================================
void PropertyAttachment::sendInitialUpdate()
{
    valueTreePropertyChanged(state, propertyId);
}

void PropertyAttachment::setValueAsCompleteGesture(const juce::var& v)
{
    if (isPropertySynchronized(v)) return;
    if (ignoreCallbacks) return;
    
    beginGesture();
    setValueAsPartOfGesture(v);
    endGesture();
}

//==============================================================================
void PropertyAttachment::beginGesture()
{
    if (undoManager)
        undoManager->beginNewTransaction();
    
    listenerList.call(&Listener::gestureBegan, *this);
}

void PropertyAttachment::setValueAsPartOfGesture(const juce::var& v)
{
    if (isPropertySynchronized(v)) return;
    if (ignoreCallbacks) return; 

    state.setPropertyExcludingListener(this, propertyId, v, undoManager);
}

void PropertyAttachment::endGesture()
{
    listenerList.call(&Listener::gestureEnded, *this);
}

//==============================================================================
// private
//==============================================================================
void PropertyAttachment::valueTreePropertyChanged (juce::ValueTree& vt,
                                                   const juce::Identifier& ids)
{
    if (state != vt || propertyId != ids) return;
    
    if (juce::MessageManager::getInstance()->isThisTheMessageThread())
    {
        cancelPendingUpdate();
        handleAsyncUpdate();
    }
    else
    {
        triggerAsyncUpdate();
    }
}

void PropertyAttachment::handleAsyncUpdate()
{
    const juce::ScopedValueSetter<bool> svs (ignoreCallbacks, true);

    // ui値が更新されるようコールバック呼び出し
    juce::NullCheckedInvocation::invoke(setValue, state[propertyId]);
}

bool PropertyAttachment::isPropertySynchronized(const juce::var& v)
{
    return state[propertyId] == v;
}

