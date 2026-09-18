<#
.SYNOPSIS
    Creates a new Thalrin game project with its own solution.

.DESCRIPTION
    Generates <Name>/<Name>.slnx containing the engine's Core and Editor projects
    alongside the new game project, so the whole thing opens as one solution.

    Anything not passed as a parameter is prompted for. Pass every parameter to run
    it unattended.

    The engine is reached either by cloning it into the game folder (Embedded) or by
    pointing at an engine checkout already on this machine (Linked). Only Engine.props
    references the engine, so switching later is a one-line edit.

.EXAMPLE
    ./New-Project.ps1
    ./New-Project.ps1 -Name Chronicle -EngineMode Embedded -Destination C:\repos -InitGit
    ./New-Project.ps1 -Name Chronicle -EngineMode Linked -EnginePath C:\repos\thalrin -NoGit
#>
[CmdletBinding()]
param(
    [string]$Name,

    # Folder the project directory is created in.
    [string]$Destination,

    [ValidateSet('Embedded', 'Linked')]
    [string]$EngineMode,

    # Linked mode: path to an existing engine checkout (repo root, not the Thalrin subfolder).
    [string]$EnginePath,

    # Embedded mode: branch or tag to pin the cloned engine to.
    [string]$EngineRef,

    [string]$EngineRepo = 'https://github.com/mustafa-sibai/Thalrin',

    # Initialise a git repo in the new project. Pass -NoGit to skip without being asked.
    [switch]$InitGit,
    [switch]$NoGit
)

$ErrorActionPreference = 'Stop'

$EngineRepoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$TemplateRoot = Join-Path $EngineRepoRoot 'Templates/Game'
if (-not (Test-Path $TemplateRoot)) { throw "Template not found at $TemplateRoot" }

function Read-WithDefault([string]$Prompt, [string]$Default) {
    $value = Read-Host "$Prompt [$Default]"
    if ([string]::IsNullOrWhiteSpace($value)) { return $Default }
    return $value.Trim()
}

function Read-YesNo([string]$Prompt, [bool]$Default) {
    $hint = if ($Default) { 'Y/n' } else { 'y/N' }
    while ($true) {
        $value = Read-Host "$Prompt [$hint]"
        if ([string]::IsNullOrWhiteSpace($value)) { return $Default }
        switch -Regex ($value.Trim()) {
            '^(y|yes)$' { return $true }
            '^(n|no)$'  { return $false }
            default     { Write-Host "  Please answer y or n." -ForegroundColor Yellow }
        }
    }
}

# ------------------------------------------------------------------- 1. name
while ([string]::IsNullOrWhiteSpace($Name)) { $Name = (Read-Host 'Project name').Trim() }
if ($Name -notmatch '^[A-Za-z_][A-Za-z0-9_]*$') {
    throw "'$Name' is not a valid project name. Use letters, digits and underscores, starting with a letter."
}

# ------------------------------------------------------------------- 2. engine mode
if (-not $EngineMode) {
    Write-Host ''
    Write-Host 'How should this project reach the engine?'
    Write-Host '  [1] Embedded - clone the engine into the project (self-contained, builds its own copy)'
    Write-Host '  [2] Linked   - use an engine checkout already on this machine (shared, faster to set up)'
    while (-not $EngineMode) {
        switch ((Read-WithDefault 'Choice' '1')) {
            '1' { $EngineMode = 'Embedded' }
            '2' { $EngineMode = 'Linked' }
            default { Write-Host '  Enter 1 or 2.' -ForegroundColor Yellow }
        }
    }
}

if ($EngineMode -eq 'Linked') {
    if ([string]::IsNullOrWhiteSpace($EnginePath)) {
        # Default to the engine this script was run from.
        $EnginePath = (Read-WithDefault 'Path to the existing engine checkout' $EngineRepoRoot).Trim('"', ' ')
    }
    if (-not (Test-Path (Join-Path $EnginePath 'Thalrin/Thalrin.props'))) {
        throw "No engine found at '$EnginePath' (expected Thalrin/Thalrin.props)."
    }
    $EngineRepoDir = (Resolve-Path $EnginePath).Path
}

# ------------------------------------------------------------------- 3. location
if ([string]::IsNullOrWhiteSpace($Destination)) {
    $Destination = Read-WithDefault 'Create the project in' (Split-Path $EngineRepoRoot -Parent)
}
$Destination = $Destination.Trim('"', ' ')
if (-not (Test-Path $Destination)) {
    if (-not (Read-YesNo "'$Destination' does not exist. Create it?" $true)) { throw 'Cancelled.' }
    New-Item -ItemType Directory -Path $Destination -Force | Out-Null
}
$Destination = (Resolve-Path $Destination).Path
$ProjectRoot = Join-Path $Destination $Name
if (Test-Path $ProjectRoot) { throw "$ProjectRoot already exists." }

# ------------------------------------------------------------------- 4. git
if ($InitGit -and $NoGit) { throw 'Pass either -InitGit or -NoGit, not both.' }
if ($InitGit)      { $WantGit = $true }
elseif ($NoGit)    { $WantGit = $false }
else               { $WantGit = Read-YesNo 'Initialise a git repository for this project?' $true }

# ------------------------------------------------------------------- create
Write-Host ''
Write-Host "Creating $Name in $ProjectRoot ($EngineMode engine)..."
New-Item -ItemType Directory -Path $ProjectRoot | Out-Null

if ($EngineMode -eq 'Embedded') {
    $EngineRepoDir = Join-Path $ProjectRoot 'Engine'
    Write-Host 'Cloning engine into Engine/...'
    git clone $EngineRepo $EngineRepoDir
    if ($LASTEXITCODE -ne 0) { throw 'git clone failed.' }
    if ($EngineRef) {
        Write-Host "Checking out engine at $EngineRef..."
        git -C $EngineRepoDir checkout $EngineRef
        if ($LASTEXITCODE -ne 0) { throw "Could not check out '$EngineRef'." }
    }
}

# Engine paths as seen from the generated solution.
$EngineDirAbs = Join-Path $EngineRepoDir 'Thalrin'
if ($EngineMode -eq 'Embedded') {
    $EngineRel = 'Engine/Thalrin'
    $EngineDirProp = '$(MSBuildThisFileDirectory)Engine\Thalrin'
}
else {
    Push-Location $ProjectRoot
    try { $rel = (Resolve-Path -Relative $EngineDirAbs -ErrorAction SilentlyContinue) } catch { $rel = $null }
    Pop-Location
    # A long ../../.. chain is fragile and unreadable - fall back to an absolute path.
    if ($rel -and (([regex]::Matches($rel, [regex]::Escape('..' + [char]92))).Count -le 3)) {
        if ($rel.StartsWith('.' + [char]92)) { $rel = $rel.Substring(2) }
        $EngineRel = $rel.Replace([char]92, '/')
        $EngineDirProp = '$(MSBuildThisFileDirectory)' + $EngineRel.Replace('/', [char]92)
    }
    else {
        $EngineRel = $EngineDirAbs.Replace([char]92, '/')
        $EngineDirProp = $EngineDirAbs
    }
}

Write-Host 'Generating project files...'
Copy-Item (Join-Path $TemplateRoot '*') $ProjectRoot -Recurse -Force

$engineModeNote = if ($EngineMode -eq 'Embedded') {
    'Engine is cloned into this repo under Engine/.'
} else {
    "Engine is linked from $EngineDirAbs."
}

$tokens = @{
    '__PROJECT_NAME__' = $Name
    '__PROJECT_GUID__' = [guid]::NewGuid().ToString()
    '__CORE_GUID__'    = [guid]::NewGuid().ToString()
    '__EDITOR_GUID__'  = [guid]::NewGuid().ToString()
    '__ENGINE_REL__'   = $EngineRel
    '__ENGINE_DIR__'   = $EngineDirProp
    '__ENGINE_MODE__'  = $engineModeNote
}

# Rename templated paths, deepest first so parents stay valid while renaming.
Get-ChildItem $ProjectRoot -Recurse -Force |
    Where-Object { $_.Name -like '*__PROJECT_NAME__*' } |
    Sort-Object { $_.FullName.Length } -Descending |
    ForEach-Object { Rename-Item $_.FullName ($_.Name -replace '__PROJECT_NAME__', $Name) }

Get-ChildItem $ProjectRoot -Recurse -File -Force |
    Where-Object { $_.Extension -in '.slnx', '.vcxproj', '.filters', '.props', '.cpp', '.h', '.yml', '.md' -or $_.Name -in '.gitignore', '.gitattributes' } |
    ForEach-Object {
        $content = Get-Content $_.FullName -Raw
        foreach ($k in $tokens.Keys) { $content = $content.Replace($k, $tokens[$k]) }
        # Windows line endings, so git has nothing to convert on add.
        $content = $content -replace "`r?`n", "`r`n"
        Set-Content $_.FullName -Value $content -NoNewline
    }

if ($WantGit) {
    Write-Host 'Initialising git repository...'
    git -C $ProjectRoot init --quiet
    if ($LASTEXITCODE -ne 0) {
        Write-Warning 'git init failed - skipping commit.'
    }
    else {
        git -C $ProjectRoot add -A
        git -C $ProjectRoot commit --quiet -m "Initial commit: $Name created from the Thalrin game template"
        if ($LASTEXITCODE -ne 0) {
            Write-Warning 'Nothing committed - configure your git identity and commit manually.'
        }
    }
}

Write-Host ''
Write-Host "Done. $Name created at $ProjectRoot" -ForegroundColor Green
Write-Host ''
if ($EngineMode -eq 'Embedded') {
    Write-Host 'Next: build the engine dependencies (this takes a while the first time):'
    Write-Host "  cd $ProjectRoot"
    Write-Host '  task setup'
    Write-Host ''
}
Write-Host "Then open $Name.slnx and build."
