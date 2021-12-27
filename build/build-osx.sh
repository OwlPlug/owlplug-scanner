ROOT=$(cd "$(dirname "$0")/.."; pwd)

echo $JAVA_HOME

ls $JAVA_HOME/include/darwin

# Resave jucer files
"$ROOT/build/bin/JUCE/Projucer.app/Contents/MacOS/Projucer" --resave "$ROOT/owlplug-scanner.jucer"

cd "$ROOT/Builds/MacOSX"
xcodebuild -configuration Release || exit 1