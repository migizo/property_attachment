/*
  ==============================================================================

    WidgetPropertyAttachment.cpp
    Author:  migizo

  ==============================================================================
*/

#include "WidgetPropertyAttachment.h"

//==============================================================================
// Slider
//==============================================================================
SliderPropertyAttachment::SliderPropertyAttachment(juce::ValueTree vt,
                                                   const juce::Identifier& propId,
                                                   juce::UndoManager* um,
                                                   juce::Slider& s)
: slider(s)
, attachment(vt,
             propId,
             um, [this](auto v){ setValue(v); })
{
    slider.addListener(this);
}

SliderPropertyAttachment::~SliderPropertyAttachment()
{
    slider.removeListener(this);
}

//==============================================================================
void SliderPropertyAttachment::sliderDragStarted(juce::Slider*)
{
    attachment.beginGesture();
}

void SliderPropertyAttachment::sliderValueChanged(juce::Slider*)
{
    attachment.setValueAsPartOfGesture(slider.getValue());
}

void SliderPropertyAttachment::sliderDragEnded(juce::Slider*)
{
    attachment.endGesture();
}

//==============================================================================
void SliderPropertyAttachment::setValue(const juce::var& v)
{
    slider.setValue(v, juce::sendNotificationSync);
}

//==============================================================================
// ComboBoxPropertyAttachment
//==============================================================================
ComboBoxPropertyAttachment::ComboBoxPropertyAttachment(juce::ValueTree vt,
                                                       const juce::Identifier& propId,
                                                       juce::UndoManager* um,
                                                       juce::ComboBox& c,
                                                       bool usingIndex)
: comboBox(c)
, usingIndexToManage(usingIndex)
, attachment(vt,
             propId,
             um,
             [this](auto v){ setValue(v); })

{
    comboBox.addListener(this);
}

ComboBoxPropertyAttachment::~ComboBoxPropertyAttachment()
{
    comboBox.removeListener(this);
}

//==============================================================================
void ComboBoxPropertyAttachment::comboBoxChanged(juce::ComboBox*)
{
    if (usingIndexToManage)
        attachment.setValueAsCompleteGesture(comboBox.getSelectedItemIndex());
    else
        attachment.setValueAsCompleteGesture(comboBox.getSelectedId());

}

//==============================================================================
void ComboBoxPropertyAttachment::setValue(const juce::var& v)
{
    if (usingIndexToManage)
        comboBox.setSelectedItemIndex(v, juce::sendNotificationSync);
    else
        comboBox.setSelectedId(v, juce::sendNotificationSync);
}

//==============================================================================
// Toggle
//==============================================================================
TogglePropertyAttachment::TogglePropertyAttachment(juce::ValueTree vt,
                                                   const juce::Identifier& propId,
                                                   juce::UndoManager* um,
                                                   juce::Button& t)
: toggle(t)
, attachment(vt,
             propId,
             um, [this](auto v){ setValue(v); })
{
    if (! t.getClickingTogglesState()) t.setClickingTogglesState(true);
    
    toggle.addListener(this);
}

TogglePropertyAttachment::~TogglePropertyAttachment()
{
    toggle.removeListener(this);
}

void TogglePropertyAttachment::buttonClicked(juce::Button*)
{
    attachment.setValueAsCompleteGesture(toggle.getToggleState());
}

void TogglePropertyAttachment::setValue(const juce::var& v)
{
    toggle.setToggleState((bool)v, juce::sendNotificationSync);
}

//==============================================================================
// Label
//==============================================================================
LabelPropertyAttachment::LabelPropertyAttachment(juce::ValueTree vt,
                                                 const juce::Identifier& propId,
                                                 juce::UndoManager* um,
                                                 juce::Label& l)
: label(l)
, attachment(vt,
             propId,
             um, [this](auto v){ setValue(v); })
{
    label.addListener(this);
}

LabelPropertyAttachment::~LabelPropertyAttachment()
{
    label.removeListener(this);
}

void LabelPropertyAttachment::labelTextChanged(juce::Label*)
{
    attachment.setValueAsCompleteGesture(label.getText());
}

void LabelPropertyAttachment::setValue(const juce::var& v)
{
    label.setText(v.toString(), juce::sendNotificationSync);
}

//==============================================================================
// TextEditor
//==============================================================================
TextEditorPropertyAttachment::TextEditorPropertyAttachment(juce::ValueTree vt,
                                                           const juce::Identifier& propId,
                                                           juce::UndoManager* um,
                                                           juce::TextEditor& te)
: textEditor(te)
, attachment(vt,
             propId,
             um, [this](auto v){ setValue(v); })
{
    textEditor.addListener(this);
}

TextEditorPropertyAttachment::~TextEditorPropertyAttachment()
{
    textEditor.removeListener(this);
}

void TextEditorPropertyAttachment::textEditorTextChanged(juce::TextEditor&)
{
    if (! isChanging)
    {
        isChanging = true;
        attachment.beginGesture();
    }
    attachment.setValueAsPartOfGesture(textEditor.getText());
}

void TextEditorPropertyAttachment::textEditorReturnKeyPressed(juce::TextEditor&)
{
    textEditorFocusLost(textEditor);
}

void TextEditorPropertyAttachment::textEditorEscapeKeyPressed(juce::TextEditor&)
{
    textEditorFocusLost(textEditor);
}

void TextEditorPropertyAttachment::textEditorFocusLost(juce::TextEditor&)
{
    if (isChanging)
    {
        attachment.endGesture();
        isChanging = false;
    }
}

void TextEditorPropertyAttachment::setValue(const juce::var& v)
{
    textEditor.setText(v.toString(), true);
}

//==============================================================================
//==============================================================================
#if JUCE_VERSION >= 0x080000

int getParameterIndex()
{
    static int paramIndex = 0;
    return paramIndex++;
}

//==============================================================================
// WebSlider
//==============================================================================
//WebSliderPropertyAttachment::WebSliderPropertyAttachment(juce::ValueTree vt,
//                                                         const juce::Identifier& propId,
//                                                         juce::UndoManager* um,
//                                                         juce::WebSliderRelay& s,
//                                                         const Options& opt)
//: slider(s)
//, options(opt)
//, attachment(vt,
//             propId,
//             um, [this](auto v){ setValue(v); })
//{
//    slider.addListener(this);
//}
//
//WebSliderPropertyAttachment::~WebSliderPropertyAttachment()
//{
//    slider.removeListener(this);
//}
//
////==============================================================================
//void WebSliderPropertyAttachment::sendInitialUpdate()
//{
//    auto range = options.normalisableRange;
//    auto getNumSteps = [&range]
//    {
//        if (range.interval > 0)
//            return (static_cast<int> ((range.end - range.start) / range.interval) + 1);
//        return juce::AudioProcessor::getDefaultNumParameterSteps();
//    };
//    int parameterIndex = options.parameterIndex != -1 ? options.parameterIndex : getParameterIndex();
//    juce::DynamicObject::Ptr object { new juce::DynamicObject };
//    object->setProperty (juce::detail::WebSliderRelayEvents::Event::eventTypeKey, "propertiesChanged");
//    object->setProperty ("start", range.start);
//    object->setProperty ("end", range.end);
//    object->setProperty ("skew", range.skew);
//    object->setProperty ("name", options.name.substring(0, 100));
//    object->setProperty ("label", options.label);
//    object->setProperty ("numSteps", getNumSteps());
//    object->setProperty ("interval", range.interval);
//    object->setProperty ("parameterIndex", parameterIndex);
//    slider.emitEvent (object.get());
//    attachment.sendInitialUpdate();
//}
//
////==============================================================================
//void WebSliderPropertyAttachment::initialUpdateRequested(juce::WebSliderRelay*)
//{
//    sendInitialUpdate();
//}
//
//void WebSliderPropertyAttachment::sliderDragStarted(juce::WebSliderRelay*)
//{
//    attachment.beginGesture();
//}
//
//void WebSliderPropertyAttachment::sliderValueChanged(juce::WebSliderRelay*)
//{
//    attachment.setValueAsPartOfGesture(slider.getValue());
//}
//
//void WebSliderPropertyAttachment::sliderDragEnded(juce::WebSliderRelay*)
//{
//    attachment.endGesture();
//}
//
////==============================================================================
//void WebSliderPropertyAttachment::setValue(const juce::var& v)
//{
//    slider.setValue(v); // juce::sendNotificationSyncのようなもの必要?
//}

////==============================================================================
//// WebComboBoxPropertyAttachment
////==============================================================================
//WebComboBoxPropertyAttachment::WebComboBoxPropertyAttachment(juce::ValueTree vt,
//                                                             const juce::Identifier& propId,
//                                                             juce::UndoManager* um,
//                                                             juce::WebComboBoxRelay& c)
//: comboBox(c)
//, attachment(vt,
//             propId,
//             um,
//             [this](auto v){ setValue(v); })
//
//{
//    comboBox.addListener(this);
//}
//
//WebComboBoxPropertyAttachment::~WebComboBoxPropertyAttachment()
//{
//    comboBox.removeListener(this);
//}
//
////==============================================================================
//void WebComboBoxPropertyAttachment::initialUpdateRequested()
//{
//    sendInitialUpdate();
//}
//
//void WebComboBoxPropertyAttachment::valueChanged(float v)
//{
//    attachment.setValueAsCompleteGesture(v);
//}
//
////==============================================================================
//void WebComboBoxPropertyAttachment::setValue(const juce::var& v)
//{
//    comboBox.setValue(v); // juce::sendNotificationSyncのようなもの必要?emit?
//}
//
////==============================================================================
//// WebToggle
////==============================================================================
//WebTogglePropertyAttachment::WebTogglePropertyAttachment(juce::ValueTree vt,
//                                                         const juce::Identifier& propId,
//                                                         juce::UndoManager* um,
//                                                         juce::WebToggleButtonRelay& t)
//: toggle(t)
//, attachment(vt,
//             propId,
//             um, [this](auto v){ setValue(v); })
//{
//    toggle.addListener(this);
//}
//
//WebTogglePropertyAttachment::~WebTogglePropertyAttachment()
//{
//    toggle.removeListener(this);
//}
//
//void WebTogglePropertyAttachment::initialUpdateRequested()
//{
//    sendInitialUpdate();
//}
//
//void WebTogglePropertyAttachment::toggleStateChanged(bool toggleState)
//{
//    attachment.setValueAsCompleteGesture(toggleState);
//}
//
//void WebTogglePropertyAttachment::setValue(const juce::var& v)
//{
//    toggle.setToggleState(v); // juce::sendNotificationSyncのようなもの必要?emit?
//}


#endif // JUCE_VERSION >= 0x080000
