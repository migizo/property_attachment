/*
  ==============================================================================

    RadioGroupPropertyAttachment.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "IPropertyAttachmentHolder.h"

//==============================================================================
//! @note 配列数が途中で変わる場合はこのAttachmentを作り直すこと
template<typename ButtonPtrArray>
class RadioGroupPropertyAttachment
: public IPropertyAttachmentHolder
, private juce::Button::Listener
{
public:
    RadioGroupPropertyAttachment() = delete;
    
    //! @param radioGroupId you can specified RadioButtonID. If you want to call setRadioGroupID() yourself, specify a value less than or equal to 0.
    RadioGroupPropertyAttachment(juce::ValueTree vt,
                                   const juce::Identifier& propId,
                                   juce::UndoManager* um,
                                   ButtonPtrArray& radioButtons,
                                   int radioGroupId);
    template<typename T>
    RadioGroupPropertyAttachment(juce::CachedValue<T>& cv,
                                   ButtonPtrArray& rbs,
                                   int radioGroupId)
    : RadioGroupPropertyAttachment(cv.getValueTree(),
                                    cv.getPropertyID(),
                                    cv.getUndoManager(),
                                    rbs) {}
    ~RadioGroupPropertyAttachment() override;
    
    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
    //! この関数をセットアップ後に呼び出す
    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }

    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    
private:
    // juce::Button::Listener
    void buttonClicked(juce::Button*) override;
    
    void setValue(const juce::var&);

    ButtonPtrArray& radioButtons;
    PropertyAttachment attachment;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioGroupPropertyAttachment)
};

//==============================================================================
// RadioButton
//==============================================================================
template<typename ButtonPtrArray>
RadioGroupPropertyAttachment<ButtonPtrArray>::RadioGroupPropertyAttachment(juce::ValueTree vt,
                                                                               const juce::Identifier& propId,
                                                                               juce::UndoManager* um,
                                                                               ButtonPtrArray& rbs,
                                                                               int radioGroupId)
: radioButtons(rbs)
, attachment(vt,
             propId,
             um, [this](auto v){ setValue(v); })
{
    for (auto* ptr : radioButtons)
    {
        ptr->addListener(this);
        if (radioGroupId >= 1)
        {
            ptr->setRadioGroupId(radioGroupId);
        }
    }
}

template<typename ButtonPtrArray>
RadioGroupPropertyAttachment<ButtonPtrArray>::~RadioGroupPropertyAttachment()
{
    for (auto* ptr : radioButtons)
    {
        ptr->removeListener(this);
    }
}

template<typename ButtonPtrArray>
void RadioGroupPropertyAttachment<ButtonPtrArray>::buttonClicked(juce::Button* radio)
{
    if (radio->getToggleState() == false) return;
    
    attachment.setValueAsCompleteGesture(radioButtons.indexOf(radio));
}

template<typename ButtonPtrArray>
void RadioGroupPropertyAttachment<ButtonPtrArray>::setValue(const juce::var& v)
{
    if (radioButtons.isEmpty()) return;

    int index = v;
        
    // 全てオフの場合
    if (index < 0)
    {
        for (auto* ptr : radioButtons)
        {
            ptr->setToggleState(false, juce::sendNotificationSync);
        }
        return;
    }
    
    // 全てオフでは無い場合
    if (radioButtons.size() <= index)
    {
        jassert(index < radioButtons.size());
        index = std::min(index, (int)radioButtons.size() - 1);
    }
    radioButtons[index]->setToggleState(true, juce::sendNotificationSync);
}

//==============================================================================
using RadioArrayPropertyAttachment = RadioGroupPropertyAttachment<juce::Array<juce::Button*>>;
using OwnedRadioArrayPropertyAttachment = RadioGroupPropertyAttachment<juce::OwnedArray<juce::Button>>;
