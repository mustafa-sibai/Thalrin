param(
    [switch]$Clean = $false,
    [switch]$BuildZlib = $false,
    [switch]$BuildOpenSSL = $false,
    [switch]$BuildCurl = $false
)

$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "../..")).Path

if ($Clean) {
    Write-Host "Cleaning build directories..."
    Remove-Item -Recurse -Force "$RepoRoot/Dependencies/zlib/build" -ErrorAction SilentlyContinue
    Remove-Item -Recurse -Force "$RepoRoot/Dependencies/zlib/output" -ErrorAction SilentlyContinue
    Remove-Item -Recurse -Force "$RepoRoot/Dependencies/openssl/install" -ErrorAction SilentlyContinue
    Remove-Item -Recurse -Force "$RepoRoot/Dependencies/curl/build" -ErrorAction SilentlyContinue
    Remove-Item -Recurse -Force "$RepoRoot/Dependencies/curl/output" -ErrorAction SilentlyContinue
}

if ($BuildZlib) {
    Write-Host "Building zlib..."
    & (Join-Path $PSScriptRoot "compile-zlib.ps1")
}

if ($BuildOpenSSL) {
    Write-Host "Building OpenSSL..."
    & (Join-Path $PSScriptRoot "compile-openssl.ps1")
}

if ($BuildCurl) {
    Write-Host "Building curl..."
    Push-Location "$RepoRoot/Dependencies/curl"
    cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
        -DBUILD_SHARED_LIBS=OFF `
        -DCMAKE_INSTALL_PREFIX="$PWD/output" `
        -DCMAKE_PREFIX_PATH="$RepoRoot/Dependencies/openssl/install;$RepoRoot/Dependencies/zlib/output" `
        -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=TRUE `
        -DZLIB_ROOT="$RepoRoot/Dependencies/zlib/output" `
        -DCURL_ZLIB=ON `
        -DCURL_USE_OPENSSL=ON `
        -DOPENSSL_USE_STATIC_LIBS=TRUE `
        -DCURL_USE_LIBPSL=OFF `
        -DCURL_USE_LIBSSH2=OFF `
        -DUSE_LIBIDN2=OFF
        
    cmake --build build --config Debug --parallel
    cmake --install build --config Debug
    Pop-Location
}