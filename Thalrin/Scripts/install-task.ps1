$ErrorActionPreference = "Stop"

function Assert-Choco {
    if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
        throw "Chocolatey is not installed or not on PATH. Run install-chocolatey.ps1 first."
    }
}

function Test-TaskInstalled {
    return [bool](Get-Command task -ErrorAction SilentlyContinue)
}

Assert-Choco

if (Test-TaskInstalled) {
    Write-Host "OK: Task already installed: $((Get-Command task).Source)"
    & task --version
    exit 0
}

Write-Host "Task not found. Installing via Chocolatey..."
choco install -y go-task --force

# Verify install
if (-not (Get-Command task -ErrorAction SilentlyContinue)) {
    throw "Task installed but still not accessible from PATH. Try opening a new PowerShell window."
}

Write-Host "OK: Task installed successfully: $((Get-Command task).Source)"
& task --version
