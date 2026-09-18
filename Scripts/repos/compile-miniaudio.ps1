. "$PSScriptRoot/toolchain.ps1"

Push-Location ./Thalrin/dependencies/miniaudio
Write-Host "Building miniaudio..."
cmake -S . -B build -G "Visual Studio 18 2026" -A x64 -T "v145,version=$ToolsetVersion" `
    -DCMAKE_SYSTEM_VERSION="$SdkVersion" `
    -DMINIAUDIO_BUILD_EXAMPLES=OFF `
    -DMINIAUDIO_BUILD_TESTS=OFF `
    -DMINIAUDIO_BUILD_TOOLS=OFF `
    -DMINIAUDIO_NO_EXTRA_NODES=ON `
    -DMINIAUDIO_NO_LIBVORBIS=ON `
    -DMINIAUDIO_NO_LIBOPUS=ON `
    -DCMAKE_INSTALL_PREFIX="$PWD/output" `
    -DCMAKE_INSTALL_LIBDIR="lib/x64/debug" `
    -DCMAKE_INSTALL_INCLUDEDIR="include"
cmake --build build --config Debug --parallel
cmake --install build --config Debug
Pop-Location
