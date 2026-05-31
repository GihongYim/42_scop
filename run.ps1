param(
	[string]$Config = "Debug",
	[string]$BuildDir = "build",
	[string]$Model = "assets\42.obj",
	[switch]$Clean
)

$ErrorActionPreference = "Stop"

$Root = $PSScriptRoot
if (-not $Root) {
	$Root = (Get-Location).Path
}

$BuildPath = Join-Path $Root $BuildDir

function Assert-PathInsideProject {
	param([string]$Path)

	$projectRoot = [System.IO.Path]::GetFullPath($Root).TrimEnd('\', '/')
	$targetPath = [System.IO.Path]::GetFullPath($Path).TrimEnd('\', '/')

	if ($targetPath.Equals($projectRoot, [System.StringComparison]::OrdinalIgnoreCase) -or
		-not $targetPath.StartsWith($projectRoot + [System.IO.Path]::DirectorySeparatorChar, [System.StringComparison]::OrdinalIgnoreCase)) {
		throw "Refusing to clean outside the project: $targetPath"
	}
}

Set-Location $Root

if ($Clean -and (Test-Path -LiteralPath $BuildPath)) {
	Assert-PathInsideProject $BuildPath
	Remove-Item -LiteralPath $BuildPath -Recurse -Force
}

cmake -S $Root -B $BuildPath
cmake --build $BuildPath --config $Config

$Candidates = @(
	(Join-Path $BuildPath "$Config\scop.exe"),
	(Join-Path $BuildPath "scop.exe")
)

$Executable = $null
foreach ($Candidate in $Candidates) {
	if (Test-Path -LiteralPath $Candidate) {
		$Executable = $Candidate
		break
	}
}

if (-not $Executable) {
	throw "scop.exe was not found in $BuildPath"
}

& $Executable $Model
