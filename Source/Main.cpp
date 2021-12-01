/*
  ==============================================================================

    owlplug-scanner main file

  ==============================================================================
*/

#include <iostream>
#include <JuceHeader.h>

//==============================================================================
int main (int argc, char* argv[])
{

	if (argc != 2) {
		std::cout << "\nError: Wrong program argument number";
		std::cout << "\nYou must add an audio plugin path: ./owlplug-scanner /path/to/plugin";
		return -1;
	}

	// Used by Console / Library app to take care of Juce components lifecycle
    // MessageManager is automatically released at the end of function scope
	juce::ScopedJuceInitialiser_GUI initGui;

	char* pluginPath = argv[1];

	juce::AudioPluginFormatManager pluginFormatManager;
	pluginFormatManager.addDefaultFormats();
	juce::KnownPluginList plugList;

	// Array of plugin description
	juce::OwnedArray<juce::PluginDescription> pluginDescriptions;

	// For each managed format, we try to fill pluginDescriptions array.
	for (int i = 0; i < pluginFormatManager.getNumFormats(); ++i) {
		plugList.scanAndAddFile(pluginPath, false, pluginDescriptions,
			*pluginFormatManager.getFormat(i));
	}

	if (pluginDescriptions.size() == 0) {
		std::cout << "\nError: No plugin detected in the given p^lugin file ";
		std::cout << pluginPath;
		return -1;
	}

	std::cout << pluginDescriptions[0]->createXml()->toString();

    return 0;
}
