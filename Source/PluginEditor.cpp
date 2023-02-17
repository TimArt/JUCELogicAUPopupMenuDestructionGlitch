/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    
    button.onClick = [this]
    {
        popup.clear();
        
        popup.addSectionHeader ("Popup Header");
        popup.addItem(1, "Option 1");
        popup.addItem(2, "Option 2");
        popup.addItem(3, "Option 3");
        
        
        popup.showMenuAsync (
            juce::PopupMenu::Options()//.withParentComponent(this)
                                      .withTargetComponent (button)
                                      .withPreferredPopupDirection (juce::PopupMenu::Options::PopupDirection::downwards),
            [this](int selected)
            {
                DBG("Option " + juce::String (selected) + " selected");
            });
    };
    
    constructionTimeLabel.setText ("Construction Time\n" + juce::Time::getCurrentTime().toString(false, true), juce::NotificationType::sendNotification);
    currentTimeLabel.setText ("Current Time\n" + juce::Time::getCurrentTime().toString(false, true), juce::NotificationType::sendNotification);
    
    addAndMakeVisible(button);
    addAndMakeVisible(constructionTimeLabel);
    addAndMakeVisible(currentTimeLabel);
    
    // Update current time every 1 second
    startTimer (1000);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    button.setTitle("Some work here so we can hit in debugger.");
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void NewProjectAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    button.setBounds (bounds.withSizeKeepingCentre (200, 80));
    constructionTimeLabel.setBounds(bounds.removeFromTop(40));
    currentTimeLabel.setBounds(bounds.removeFromTop(40));
}

void NewProjectAudioProcessorEditor::timerCallback()
{
    // Update current time
    currentTimeLabel.setText ("Current Time\n" + juce::Time::getCurrentTime().toString(false, true), juce::NotificationType::sendNotification);
}
