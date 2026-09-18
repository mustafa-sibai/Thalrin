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

$ScriptsDir = Join-Path $PSScriptRoot "Scripts"

# Ordered so dependencies (e.g. Chocolatey, Go) run before what relies on them.
$applications = @(
    [PSCustomObject]@{ Name = "Chocolatey (package manager)"; Script = "install-chocolatey.ps1" }
    [PSCustomObject]@{ Name = "PowerShell Core (pwsh)";       Script = "install-powershell-core.ps1" }
    [PSCustomObject]@{ Name = "Go (programming language)";    Script = "install-go.ps1" }
    [PSCustomObject]@{ Name = "gup (go binary updater)";      Script = "install-gup.ps1" }
    [PSCustomObject]@{ Name = "Task (task runner)";           Script = "install-taskfile.ps1" }
    [PSCustomObject]@{ Name = "NASM (assembler)";             Script = "install-nasm.ps1" }
    [PSCustomObject]@{ Name = "Perl (programming language)";  Script = "install-perl.ps1" }
    [PSCustomObject]@{ Name = "CMake (build system)";         Script = "install-cmake.ps1" }
)

Write-Host "Please select the application(s) you would like to install."
Write-Host "Enter the numbers separated by commas (e.g. 1,3,5)."
Write-Host "Press Enter without selecting anything to install all by default."
Write-Host ""
for ($i = 0; $i -lt $applications.Count; $i++) {
    Write-Host ("  {0}) {1}" -f ($i + 1), $applications[$i].Name)
}
Write-Host ""

$selection = Read-Host "Selection"

if ([string]::IsNullOrWhiteSpace($selection)) {
    $selected = $applications
}
else {
    $indexes = $selection -split "[,\s]+" | Where-Object { $_ -ne "" }
    $selected = foreach ($index in $indexes) {
        $number = 0
        if (-not [int]::TryParse($index, [ref]$number) -or $number -lt 1 -or $number -gt $applications.Count) {
            Write-Host "Invalid selection: '$index'. Please run setup again and choose valid numbers."
            exit 1
        }
        $applications[$number - 1]
    }
    # Preserve defined order and remove duplicates.
    $selected = $applications | Where-Object { $selected -contains $_ }
}

Write-Host ""
Write-Host "The following applications will be installed on your system:"
foreach ($app in $selected) {
    Write-Host "  - $($app.Name)"
}

$continue = Read-Host "Do you want to continue? (Y/N)"
if ($continue -ne "Y" -and $continue -ne "y") {
    Write-Host "Setup aborted by user."
    exit 1
}

foreach ($app in $selected) {
    & "$ScriptsDir\$($app.Script)"
}

Write-Host "OK: Setup complete."
