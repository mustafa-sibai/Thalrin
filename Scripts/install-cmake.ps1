$ErrorActionPreference = "Stop"

# VS 2026 ("Visual Studio 18 2026") CMake generator requires 4.2 or newer.
$MinimumVersion = [version]"4.2.0"
$CMakeBinDir = "C:\Program Files\CMake\bin"

function Assert-Choco {
    if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
        throw "Chocolatey is not installed or not on PATH. Run install-chocolatey.ps1 first."
    }
}

function Get-CMakeVersion {
    param([string]$Exe = "cmake")
    if (-not (Get-Command $Exe -ErrorAction SilentlyContinue)) {
        return $null
    }
    $line = & $Exe --version | Select-Object -First 1
    if ($line -match "(\d+\.\d+\.\d+)") {
        return [version]$Matches[1]
    }
    return $null
}

# Move the CMake bin directory to the front of PATH so a newer install wins over
# any older cmake already on PATH (e.g. the one bundled with Strawberry Perl).
function Set-CMakePathFirst {
    $machinePath = [Environment]::GetEnvironmentVariable("Path", "Machine")
    $entries = $machinePath -split ";" | Where-Object { $_ -and ($_ -ne $CMakeBinDir) }
    [Environment]::SetEnvironmentVariable("Path", (@($CMakeBinDir) + $entries) -join ";", "Machine")

    $sessionEntries = $env:Path -split ";" | Where-Object { $_ -and ($_ -ne $CMakeBinDir) }
    $env:Path = (@($CMakeBinDir) + $sessionEntries) -join ";"
    Write-Host "Prepended to PATH: $CMakeBinDir"
}

Assert-Choco

$version = Get-CMakeVersion
if ($version -and $version -ge $MinimumVersion) {
    Write-Host "OK: cmake $version already installed: $((Get-Command cmake).Source)"
    exit 0
}

if ($version) {
    Write-Host "cmake $version found but $MinimumVersion or newer is required. Installing latest via Chocolatey..."
}
else {
    Write-Host "cmake not found. Installing latest via Chocolatey..."
}

choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System' --force

Set-CMakePathFirst

# Verify the freshly installed CMake, not whatever else is on PATH.
$version = Get-CMakeVersion "$CMakeBinDir\cmake.exe"
if (-not $version) {
    throw "CMake installed but still not accessible from PATH."
}
if ($version -lt $MinimumVersion) {
    throw "CMake $version installed but $MinimumVersion or newer is required. Chocolatey may not yet provide a compatible version."
}

Write-Host "OK: cmake installed successfully: $((Get-Command cmake).Source)"
& cmake --version
