/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 18 Nov 2020 11:52:50am
    Author:  Erik Frej Knudsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================


class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    // method for changing the visual appearance of rotary sliders
    void drawRotarySlider (juce::Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) override
    {
        // values to feed the method
        auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
        auto centreX = (float) x + (float) width  * 0.5f;
        auto centreY = (float) y + (float) height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (juce::Colours::grey);
        g.fillEllipse (rx, ry, rw, rw);
 
        // outline
        g.setColour (juce::Colours::white);
        g.drawEllipse (rx, ry, rw, rw, 1.7f);
        
        // slider pointer
        juce::Path p;
        auto pointerLength = radius * 0.50f;
        auto pointerThickness = 3.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
        
        g.setColour (juce::Colours::white);
        g.fillPath (p);
        
    }
    
    
    // method for changing the visual appearance of ToggleButton
    void drawRoundThumb (juce::Graphics& g, float x, float y, float diameter, juce::Colour colour, float outlineThickness)
    {
        auto halfThickness = outlineThickness * 0.5f;

        juce::Path p;
        p.addEllipse (x + halfThickness,
                      y + halfThickness,
                      diameter - outlineThickness,
                      diameter - outlineThickness);


        g.setColour (juce::Colours::white);
        g.fillPath (p);

        g.setColour (colour.brighter());
        g.strokePath(p, juce::PathStrokeType(outlineThickness));
    }
    
    // method for changing the visual appearance of ToggleButton
    void drawTickBox (juce::Graphics& g, juce::Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override
    {
        auto boxSize = w * 0.7f;

        auto isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());

        auto colour = component.findColour (juce::TextButton::buttonColourId)
                               .withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                               .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f);

        drawRoundThumb (g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
                        isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

        if (ticked)
        {
            g.setColour (isEnabled ? findColour (juce::TextButton::buttonOnColourId) : juce::Colours::grey);

            auto scale = 9.0f;
            auto trans = juce::AffineTransform::scale (w / scale, h / scale).translated (x - 2.5f, y + 1.0f);

            g.fillPath (LookAndFeel_V4::getTickShape (6.0f), trans);
        }
     
    }
     
          
    
    
    OtherLookAndFeel()
    {
        //getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Gill Sans");
        //setColour(Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
        //setPopupDisplayEnabled(true, false, this);
        //setTextValueSuffix (" Hz or whatever");
    }

};



class CustomLookAndFeel  : public juce::Component
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel)
};

