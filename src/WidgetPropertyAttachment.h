/*
  ==============================================================================

    WidgetPropertyAttachment.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "IPropertyAttachmentHolder.h"

//==============================================================================
class SliderPropertyAttachment
: public IPropertyAttachmentHolder
, private juce::Slider::Listener
{
public:
    SliderPropertyAttachment(juce::ValueTree vt,
                             const juce::Identifier& propId,
                             juce::UndoManager* um,
                             juce::Slider& slider);
    template<typename T>
    SliderPropertyAttachment(juce::CachedValue<T>& cv,
                             juce::Slider& s)
    : SliderPropertyAttachment(cv.getValueTree(),
                               cv.getPropertyID(),
                               cv.getUndoManager(),
                               s) {}
    ~SliderPropertyAttachment() override;
    
    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
    //! この関数をセットアップ後に呼び出す
    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }
    
    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }

private:
    // juce::Slider::Listener
    void sliderDragStarted(juce::Slider*) override;
    void sliderValueChanged(juce::Slider*) override;
    void sliderDragEnded(juce::Slider*) override;
    
    void setValue(const juce::var&);
    
    juce::Slider& slider;
    PropertyAttachment attachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderPropertyAttachment)
};

//==============================================================================
class ComboBoxPropertyAttachment
: public IPropertyAttachmentHolder
, private juce::ComboBox::Listener
{
public:
    ComboBoxPropertyAttachment() = delete;
    ComboBoxPropertyAttachment(juce::ValueTree vt,
                               const juce::Identifier& propId,
                               juce::UndoManager* um,
                               juce::ComboBox& combo,
                               bool usingIndexToManage = true);
    template<typename T>
    ComboBoxPropertyAttachment(juce::CachedValue<T>& cv,
                               juce::ComboBox& c,
                               bool usingIndexToManage = true)
    : ComboBoxPropertyAttachment(cv.getValueTree(),
                                 cv.getPropertyID(),
                                 cv.getUndoManager(),
                                 c,
                                 usingIndexToManage) {}
    ~ComboBoxPropertyAttachment() override;
    
    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
    //! この関数をセットアップ後に呼び出す
    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }

    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    
private:
    // juce::ComboBox::Listener
    void comboBoxChanged(juce::ComboBox*) override;
    
    void setValue(const juce::var&);

    juce::ComboBox& comboBox;
    bool usingIndexToManage; // attachmentの初期化前に行なっておく必要あり
    PropertyAttachment attachment;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComboBoxPropertyAttachment)
};

//==============================================================================
class TogglePropertyAttachment
: public IPropertyAttachmentHolder
, private juce::Button::Listener
{
public:
    TogglePropertyAttachment() = delete;
    TogglePropertyAttachment(juce::ValueTree vt,
                             const juce::Identifier& propId,
                             juce::UndoManager* um,
                             juce::Button& toggle);
    template<typename T>
    TogglePropertyAttachment(juce::CachedValue<T>& cv,
                             juce::Button& t)
    : TogglePropertyAttachment(cv.getValueTree(),
                               cv.getPropertyID(),
                               cv.getUndoManager(),
                               t) {}
    ~TogglePropertyAttachment() override;
    
    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
    //! この関数をセットアップ後に呼び出す
    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }

    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    
private:
    // juce::Button::Listener
    void buttonClicked(juce::Button*) override;
    
    void setValue(const juce::var&);

    juce::Button& toggle;
    PropertyAttachment attachment;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TogglePropertyAttachment)
};

//==============================================================================
class LabelPropertyAttachment
: public IPropertyAttachmentHolder
, private juce::Label::Listener
{
public:
    LabelPropertyAttachment() = delete;
    LabelPropertyAttachment(juce::ValueTree vt,
                            const juce::Identifier& propId,
                            juce::UndoManager* um,
                            juce::Label& label);
    template<typename T>
    LabelPropertyAttachment(juce::CachedValue<T>& cv,
                             juce::Label& l)
    : LabelPropertyAttachment(cv.getValueTree(),
                               cv.getPropertyID(),
                               cv.getUndoManager(),
                               l) {}
    ~LabelPropertyAttachment() override;
    
    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
    //! この関数をセットアップ後に呼び出す
    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }

    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    
private:
    // juce::Label::Listener
    void labelTextChanged(juce::Label*) override;
    
    void setValue(const juce::var&);

    juce::Label& label;
    PropertyAttachment attachment;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LabelPropertyAttachment)
};

//==============================================================================
class TextEditorPropertyAttachment
: public IPropertyAttachmentHolder
, private juce::TextEditor::Listener
{
public:
    TextEditorPropertyAttachment() = delete;
    TextEditorPropertyAttachment(juce::ValueTree vt,
                                 const juce::Identifier& propId,
                                 juce::UndoManager* um,
                                 juce::TextEditor& textEditor);
    template<typename T>
    TextEditorPropertyAttachment(juce::CachedValue<T>& cv,
                                 juce::TextEditor& te)
    : TextEditorPropertyAttachment(cv.getValueTree(),
                                   cv.getPropertyID(),
                                   cv.getUndoManager(),
                                   te) {}
    ~TextEditorPropertyAttachment() override;
    
    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
    //! この関数をセットアップ後に呼び出す
    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }
    
    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
    
private:
    // juce::TextEditor::Listener
    void textEditorTextChanged(juce::TextEditor&) override;
    void textEditorReturnKeyPressed(juce::TextEditor&) override;
    void textEditorEscapeKeyPressed(juce::TextEditor&) override;
    void textEditorFocusLost(juce::TextEditor&) override;

    void setValue(const juce::var&);

    juce::TextEditor& textEditor;
    PropertyAttachment attachment;
    bool isChanging = false;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextEditorPropertyAttachment)
};

//==============================================================================
/*
 WebView関連アタッチメント
 ただし、JUCE8のスライダー、トグル、コンボボックスのParameterAttachmentではsendInitialUpdate()で
 parameterIndexやスライダー範囲など各種関連プロパティをemitする仕様になっており、
 PropertyAttachmentとwidgetのみで使用するには無理がある。
 各種関連プロパティを指定する用のOptionsをコンストラクタ引数で受け取るか、Property用Relayやjs側ライブラリを整備するかの
 どちらかの対応を行う必要がある
 というか、そもそもWeb〇〇Relay用のAttachmentは、property値をwebview側とで同期できれば必要ないかもしれないので、実装しなくてよさそうかも
 */
//==============================================================================
#if JUCE_VERSION >= 0x080000

//class WebSliderPropertyAttachment
//: public IPropertyAttachmentHolder
//, private juce::WebSliderRelay::Listener
//{
//public:
//    struct Options
//    {
//        juce::String name;
//        juce::String label;
//        juce::NormalisableRange<float> normalisableRange;
//        int parameterIndex = -1;
//    };
//    
//    WebSliderPropertyAttachment(juce::ValueTree vt,
//                                const juce::Identifier& propId,
//                                juce::UndoManager* um,
//                                juce::WebSliderRelay& slider,
//                                const Options& options);
//    template<typename T>
//    WebSliderPropertyAttachment(juce::CachedValue<T>& cv,
//                                juce::WebSliderRelay& s,
//                                const Options& opt)
//    : SliderPropertyAttachment(cv.getValueTree(),
//                               cv.getPropertyID(),
//                               cv.getUndoManager(),
//                               s,
//                               opt) {}
//    ~WebSliderPropertyAttachment() override;
//    
//    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
//    //! この関数をセットアップ後に呼び出す
//    void sendInitialUpdate() override;
//    
//    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
//    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
//
//private:
//    // juce::WebSliderRelay::Listener
//    void initialUpdateRequested(juce::WebSliderRelay*) override;
//    void sliderDragStarted(juce::WebSliderRelay*) override;
//    void sliderValueChanged(juce::WebSliderRelay*) override;
//    void sliderDragEnded(juce::WebSliderRelay*) override;
//    
//    void setValue(const juce::var&);
//    
//    juce::WebSliderRelay& slider;
//    Options options;
//    PropertyAttachment attachment;
//    
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WebSliderPropertyAttachment)
//};

////==============================================================================
//class WebComboBoxPropertyAttachment
//: public IPropertyAttachmentHolder
//, private juce::WebComboBoxRelay::Listener
//{
//public:
//    WebComboBoxPropertyAttachment() = delete;
//    WebComboBoxPropertyAttachment(juce::ValueTree vt,
//                                  const juce::Identifier& propId,
//                                  juce::UndoManager* um,
//                                  juce::WebComboBoxRelay& combo);
//    template<typename T>
//    WebComboBoxPropertyAttachment(juce::CachedValue<T>& cv,
//                                  juce::WebComboBoxRelay& c)
//    : WebComboBoxPropertyAttachment(cv.getValueTree(),
//                                    cv.getPropertyID(),
//                                    cv.getUndoManager(),
//                                    c) {}
//    ~WebComboBoxPropertyAttachment() override;
//    
//    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
//    //! この関数をセットアップ後に呼び出す
//    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }
//
//    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
//    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
//    
//private:
//    // juce::ComboBox::Listener
//    void initialUpdateRequested() override;
//    void valueChanged(float) override;
//    
//    void setValue(const juce::var&);
//
//    juce::WebComboBoxRelay& comboBox;
//    PropertyAttachment attachment;
//
//    //==============================================================================
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WebComboBoxPropertyAttachment)
//};
//
////==============================================================================
//class WebTogglePropertyAttachment
//: public IPropertyAttachmentHolder
//, private juce::WebToggleButtonRelay::Listener
//{
//public:
//    WebTogglePropertyAttachment() = delete;
//    WebTogglePropertyAttachment(juce::ValueTree vt,
//                                const juce::Identifier& propId,
//                                juce::UndoManager* um,
//                                juce::WebToggleButtonRelay& toggle);
//    template<typename T>
//    WebTogglePropertyAttachment(juce::CachedValue<T>& cv,
//                                juce::WebToggleButtonRelay& t)
//    : WebTogglePropertyAttachment(cv.getValueTree(),
//                                  cv.getPropertyID(),
//                                  cv.getUndoManager(),
//                                  t) {}
//    ~WebTogglePropertyAttachment() override;
//    
//    //! このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
//    //! この関数をセットアップ後に呼び出す
//    void sendInitialUpdate() override { attachment.sendInitialUpdate(); }
//
//    void addListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
//    void removeListener(PropertyAttachment::Listener* l) override { attachment.addListener(l); }
//    
//private:
//    // juce::Button::Listener
//    void initialUpdateRequested() override;
//    void toggleStateChanged(bool) override;
//    
//    void setValue(const juce::var&);
//
//    juce::WebToggleButtonRelay& toggle;
//    PropertyAttachment attachment;
//    
//    //==============================================================================
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WebTogglePropertyAttachment)
//};

#endif // JUCE_VERSION >= 0x080000
