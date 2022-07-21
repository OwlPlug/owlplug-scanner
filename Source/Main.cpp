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
		std::cout << "\nYou must add an audio plugin path or identifier: ./owlplug-scanner /path/to/plugin\n";
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
		std::cout << "\nError: No plugin has been detected in the given file ";
		std::cout << pluginPath;
		std::cout << "\n";
		return -1;
	}

	for (int i = 0; i < pluginDescriptions.size(); i++) {
		std::cout << "\n---BEGIN PLUGIN COMPONENT DELIMITER---\n";
		std::cout << pluginDescriptions[i]->createXml()->toString();
		std::cout << "\n---END PLUGIN COMPONENT DELIMITER---";

	}

    return 0;
}
