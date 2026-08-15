$ErrorActionPreference = "Stop"

function Assert-Choco {
    if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
        throw "Chocolatey is not installed. Run choco script first."
    }
}

function Test-PerlInstalled {
    return [bool](Get-Command perl -ErrorAction SilentlyContinue)
}

Assert-Choco

if (Test-PerlInstalled) {
    Write-Host "OK: Perl already installed"
    perl -v
    exit 0
}

Write-Host "Installing Strawberry Perl..."
choco install -y strawberryperl --force

# Add Perl to PATH (machine + current session)
& "$PSScriptRoot\add-application-to-system-path.ps1" "C:\Strawberry\perl\bin"
& "$PSScriptRoot\add-application-to-system-path.ps1" "C:\Strawberry\c\bin"

Write-Host "Verifying..."
perl -v