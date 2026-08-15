$ErrorActionPreference = "Stop"

# Only Windows is supported for now (macOS/Linux setup.sh may come later).
if ($env:OS -ne "Windows_NT") {
    Write-Host "This setup script only supports Windows. Exiting."
    exit 1
}

# Check if the script is running with administrative privileges
$principal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
if (-not $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host "This script must be run as an administrator. Please restart PowerShell with 'Run as Administrator' and try again."
    exit 1
}

Write-Host "The following applications will be installed on your system:"
Write-Host "  - Chocolatey (package manager)"
Write-Host "  - PowerShell Core (pwsh)"
Write-Host "  - Task (task runner)"
Write-Host "  - NASM (assembler)"
Write-Host "  - Perl (programming language)"

$continue = Read-Host "Do you want to continue? (Y/N)"
if ($continue -ne "Y" -and $continue -ne "y") {
    Write-Host "Setup aborted by user."
    exit 1
}

$ScriptsDir = Join-Path $PSScriptRoot "Scripts"

& "$ScriptsDir\install-chocolatey.ps1"
& "$ScriptsDir\install-powershell-core.ps1"
& "$ScriptsDir\install-task.ps1"
& "$ScriptsDir\install-nasm.ps1"
& "$ScriptsDir\install-perl.ps1"

Write-Host "OK: Setup complete."
