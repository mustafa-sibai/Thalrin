#!/usr/bin/env pwsh

$VERSION_FILE = "Core/Version.h"
$TODAY = Get-Date -Format "yyyy-MM-dd"

# Read the file content
$content = Get-Content $VERSION_FILE -Raw

# Extract current build date
if ($content -match '#define CORE_BUILD_DATE "([^"]+)"') {
    $CURRENT_DATE = $matches[1]
} else {
    Write-Error "Could not find CORE_BUILD_DATE"
    exit 1
}

# Extract current build number
if ($content -match '#define CORE_BUILD_NUMBER (\d+)') {
    $CURRENT_BUILD = [int]$matches[1]
} else {
    Write-Error "Could not find CORE_BUILD_NUMBER"
    exit 1
}

Write-Host "Current date: $CURRENT_DATE"
Write-Host "Today: $TODAY"
Write-Host "Current build: $CURRENT_BUILD"

if ($CURRENT_DATE -eq $TODAY) {
    # Same date, increment build number
    $NEW_BUILD = $CURRENT_BUILD + 1
    $content = $content -replace "(#define CORE_BUILD_NUMBER) \d+", "`$1 $NEW_BUILD"
    Write-Host "Build number incremented: $CURRENT_BUILD -> $NEW_BUILD"
} else {
    # Different date, update date and reset build number
    $content = $content -replace '(#define CORE_BUILD_DATE) "[^"]+"', "`$1 `"$TODAY`""
    $content = $content -replace "(#define CORE_BUILD_NUMBER) \d+", "`$1 0"
    Write-Host "Build date updated: $CURRENT_DATE -> $TODAY"
    Write-Host "Build number reset to 0"
}

# Write back to file
$content | Set-Content $VERSION_FILE -NoNewline