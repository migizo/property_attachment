/*
  ==============================================================================

    IPropertyAttachmentHolder.h
    Author:  migizo

  ==============================================================================
*/

#pragma once
#include <juce_core/juce_core.h>
#include "PropertyAttachment.h"

class IPropertyAttachmentHolder
{
public:
    IPropertyAttachmentHolder() {}
    virtual ~IPropertyAttachmentHolder() {}
    
    // このクラスのコンストラクタを呼び出した後に対象コンポーネントのセットアップを行なう場合
    // この関数をセットアップ後に呼び出す
    virtual void sendInitialUpdate() = 0;
    
    virtual void addListener(PropertyAttachment::Listener* l) = 0;
    virtual void removeListener(PropertyAttachment::Listener* l) = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IPropertyAttachmentHolder)
};
