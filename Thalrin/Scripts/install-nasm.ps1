$ErrorActionPreference = "Stop"

function Assert-Choco {
    if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
        throw "Chocolatey is not installed or not on PATH. Run 01-ensure-chocolatey.ps1 first."
    }
}

function Test-NasmInstalled {
    return [bool](Get-Command nasm -ErrorAction SilentlyContinue)
}

Assert-Choco

if (Test-NasmInstalled) {
    Write-Host "OK: nasm already installed: $((Get-Command nasm).Source)"
    & nasm -v
    exit 0
}

Write-Host "nasm not found. Installing via Chocolatey..."
choco install -y nasm --force

# Add to PATH + make usable immediately
& "$PSScriptRoot\add-application-to-system-path.ps1" "C:\Program Files\NASM"

# Verify install
if (-not (Get-Command nasm -ErrorAction SilentlyContinue)) {
    throw "NASM installed but still not accessible from PATH."
}

Write-Host "OK: nasm installed successfully: $((Get-Command nasm).Source)"
& nasm -v
