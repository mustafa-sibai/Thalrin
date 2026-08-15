if (-not (Test-Path -Path ".\Dependencies")) {
    New-Item -Path "./Dependencies" -ItemType Directory
    exit
}