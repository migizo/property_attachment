/*
  ==============================================================================

    PropertyAttachment.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_data_structures/juce_data_structures.h>

//==============================================================================
class PropertyAttachment final
: private juce::ValueTree::Listener
, private juce::AsyncUpdater
{
public:
    struct Listener
    {
        virtual ~Listener() = default;

        virtual void gestureBegan(const PropertyAttachment&) = 0;
        virtual void gestureEnded(const PropertyAttachment&) = 0;
    };
    
    PropertyAttachment() = delete;
    PropertyAttachment(juce::ValueTree vt,
                       const juce::Identifier& propId,
                       juce::UndoManager* um,
                       std::function<void(const juce::var&)> propertyChangedCallback);
    ~PropertyAttachment();

    void addListener(Listener* l) { listenerList.add(l); }
    void removeListener(Listener* l) { listenerList.remove(l); }

    void sendInitialUpdate();
    void setValueAsCompleteGesture(const juce::var& v);

    void beginGesture();
    void setValueAsPartOfGesture(const juce::var& v);
    void endGesture();
    
    juce::ValueTree getValueTree() const { return state; }
    const juce::Identifier& getPropertyID() const { return propertyId; }
    juce::UndoManager* getUndoManager() { return undoManager; }
    
private:
    // juce::ValueTree::Listener
    void valueTreePropertyChanged (juce::ValueTree&,
                                   const juce::Identifier&) override;
    
    // juce::AsyncUpdater
    void handleAsyncUpdate() override;
    
    bool isPropertySynchronized(const juce::var& v);
    
    juce::ListenerList<Listener> listenerList;

    juce::ValueTree state;
    const juce::Identifier propertyId;
    juce::UndoManager* undoManager = nullptr;
    std::function<void(const juce::var&)> setValue;
    
    //! property変更に伴うUI更新時に、〇〇Gesture()関数の処理をスキップする
    //! isPropertySynchronized()でも判定しているため必要ないかもしれない
    bool ignoreCallbacks = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyAttachment)
};
