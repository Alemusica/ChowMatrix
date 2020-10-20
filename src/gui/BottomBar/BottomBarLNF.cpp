#include "BottomBarLNF.h"

namespace
{
    constexpr float heightFrac = 0.6f;
}

int getNameWidth (int height, const String& text)
{
    Font f = Font ((float) height * heightFrac);
    return f.getStringWidth (text);
}

void BottomBarLNF::drawRotarySlider (Graphics& g, int x, int y, int, int height,
                                          float, const float, const float, Slider& slider)
{
    g.setColour (Colours::yellow); // @TODO: make colour selectable
    g.setFont ((float) height * heightFrac);

    String text = slider.getName() + ":";
    int width = getNameWidth (height, text);
    g.drawFittedText (text, 0, 0, width, height, Justification::centred, 1);
}

Slider::SliderLayout BottomBarLNF::getSliderLayout (Slider& slider)
{
    auto layout = LookAndFeel_V4::getSliderLayout (slider);
    layout.textBoxBounds = slider.getLocalBounds()
        .removeFromRight (slider.getWidth()
        - getNameWidth (slider.getHeight(), slider.getName()) + 5);
    return layout;
}

Label* BottomBarLNF::createSliderTextBox (Slider& slider)
{
    auto* label = LookAndFeel_V4::createSliderTextBox (slider);
    label->setInterceptsMouseClicks (false, false);
    label->setColour (Label::outlineColourId, Colours::transparentBlack);
    label->setColour (Label::outlineWhenEditingColourId, Colours::transparentBlack);
    label->setJustificationType (Justification::centred);

    label->onEditorShow = [label]
    {
        if (label->getCurrentTextEditor() != nullptr)
            label->getCurrentTextEditor()->setJustification (Justification::centred);
    };

    return label;
}
