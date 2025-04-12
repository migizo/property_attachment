/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 property_attachment
  vendor:             migizo
  version:            0.0.1
  name:               Property Attachment
  description:        valueTree property attachment like JUCE's ParameterAttachment
  website:            https://twitter.com/migizo

  dependencies:       juce_data_structures juce_gui_basics

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once

#define PROPERTY_ATTACHMENT_H_INCLUDED

#include "src/PropertyAttachment.h"
#include "src/IPropertyAttachmentHolder.h"
#include "src/WidgetPropertyAttachment.h"
#include "src/RadioGroupPropertyAttachment.h"
