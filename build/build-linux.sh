ROOT=$(cd "$(dirname "$0")/.."; pwd)

"$ROOT/build/bin/JUCE/Projucer" --resave "$ROOT/owlplug-scanner.jucer"

cd "$ROOT/Builds/LinuxMakefile"
make CONFIG=Release
