param(
    [switch]$Clean = $false
)

. "$PSScriptRoot/toolchain.ps1"

$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "../../Thalrin")).Path
$ZlibRoot = "$RepoRoot/Thalrin/Dependencies/zlib/output"

if ($Clean) {
    Write-Host "Cleaning build directories..."
    Remove-Item -Recurse -Force "$RepoRoot/Thalrin/Dependencies/protobuf/build" -ErrorAction SilentlyContinue
    Remove-Item -Recurse -Force "$RepoRoot/Thalrin/Dependencies/protobuf/output" -ErrorAction SilentlyContinue
}

if (-not (Test-Path "$ZlibRoot/include/zlib.h")) {
    Write-Error "zlib was not found at $ZlibRoot. Run 'task compile-zlib' first."
    exit 1
}

Push-Location "$RepoRoot/Thalrin/Dependencies/protobuf"
Write-Host "Building protobuf..."
cmake -S . -B build -G "Visual Studio 18 2026" -A x64 -T "v145,version=$ToolsetVersion" `
    -DCMAKE_SYSTEM_VERSION="$SdkVersion" `
    -DCMAKE_INSTALL_PREFIX="$PWD/output" `
    -DCMAKE_CXX_STANDARD=20 `
    -DBUILD_SHARED_LIBS=OFF `
    -Dprotobuf_BUILD_SHARED_LIBS=OFF `
    -Dprotobuf_MSVC_STATIC_RUNTIME=OFF `
    -Dprotobuf_BUILD_TESTS=OFF `
    -Dprotobuf_BUILD_EXAMPLES=OFF `
    -Dprotobuf_BUILD_PROTOC_BINARIES=ON `
    -Dprotobuf_ABSL_PROVIDER=module `
    -Dprotobuf_WITH_ZLIB=ON `
    -Dprotobuf_INSTALL=ON `
    -DCMAKE_PREFIX_PATH="$ZlibRoot" `
    -DZLIB_ROOT="$ZlibRoot" `
    -DZLIB_USE_STATIC_LIBS=ON

cmake --build build --config Debug --parallel
cmake --install build --config Debug
Write-Host "protoc is available at $PWD/output/bin/protoc.exe"
Pop-Location
