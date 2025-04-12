#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
: valueTree("ROOT")
{
    addAndMakeVisible(slider);
    addAndMakeVisible(comboBox);
    addAndMakeVisible(toggle);
    for (int i = 0; i < 2; i++)
    {
        auto ptr = radioButtons.add(new juce::ToggleButton(juce::String(i)));
        addAndMakeVisible(ptr);
    }
    addAndMakeVisible(label);
    addAndMakeVisible(textEditor);
    
    comboBox.addItemList({"A", "B"}, 1);
    
    sliderAttachment.reset(new SliderPropertyAttachment(valueTree, "Slider", &undoManager, slider));
    comboBoxAttachment.reset(new ComboBoxPropertyAttachment(valueTree, "ComboBox", &undoManager, comboBox));
    toggleAttachment.reset(new TogglePropertyAttachment(valueTree, "Toggle", &undoManager, toggle));
    radioAttachment.reset(new OwnedRadioArrayPropertyAttachment(valueTree, "Radio", &undoManager, radioButtons, 1000));
    labelAttachment.reset(new LabelPropertyAttachment(valueTree, "Label", &undoManager, label));
    textEditorAttachment.reset(new TextEditorPropertyAttachment(valueTree, "TextEditor", &undoManager, textEditor));

    valueTree.setProperty("Slider", 0.5f, &undoManager);
    valueTree.setProperty("ComboBox", 0, &undoManager); // index
    valueTree.setProperty("Toggle", true, &undoManager);
    valueTree.setProperty("Radio", 1, &undoManager); // index
    valueTree.setProperty("Label", "(label ...)", &undoManager);
    valueTree.setProperty("TextEditor", "(text editor ...)", &undoManager);

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    
    slider.setBounds(area.removeFromTop(48));
    comboBox.setBounds(area.removeFromTop(48));
    toggle.setBounds(area.removeFromTop(48));
    for (auto btn: radioButtons) { btn->setBounds(area.removeFromTop(24)); }
    label.setBounds(area.removeFromTop(48));
    textEditor.setBounds(area.removeFromTop(48));
}

bool MainComponent::keyPressed (const juce::KeyPress& key)
{
    if (key == juce::KeyPress('z', juce::ModifierKeys::commandModifier, 0))
    {
        undoManager.undo();
        return true;
    }

    if (key == juce::KeyPress('z', juce::ModifierKeys::commandModifier | juce::ModifierKeys::shiftModifier, 0))
    {
        undoManager.redo();
        return true;
    }

    return juce::Component::keyPressed(key);
}
