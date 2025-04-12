#pragma once

#include <JuceHeader.h>
#include <property_attachment/property_attachment.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    bool keyPressed (const juce::KeyPress& key) override;

private:
    //==============================================================================
    juce::UndoManager undoManager;
    juce::ValueTree valueTree;

    juce::Slider slider;
    juce::ComboBox comboBox;
    juce::ToggleButton toggle;
    juce::OwnedArray<juce::Button> radioButtons;
    juce::Label label;
    juce::TextEditor textEditor;
    
    std::unique_ptr<SliderPropertyAttachment> sliderAttachment;
    std::unique_ptr<ComboBoxPropertyAttachment> comboBoxAttachment;
    std::unique_ptr<TogglePropertyAttachment> toggleAttachment;
    std::unique_ptr<OwnedRadioArrayPropertyAttachment> radioAttachment;
    std::unique_ptr<LabelPropertyAttachment> labelAttachment;
    std::unique_ptr<TextEditorPropertyAttachment> textEditorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
