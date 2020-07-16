function Generate-BuildFiles {
	param(
		[string] $BuildType,
		[string] $AdditionalConfigureParams
	)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Generating Build Files" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake -A Win32 -DCMAKE_BUILD_TYPE=' + $BuildType + ' ' + $AdditionalConfigureParams + ' ..'
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd

}
function Build-Solution {
	param(
		[string] $BuildType,		
		[int]    $Parallelism = 1
	)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Building Solution" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'cmake --build . --config ' + $BuildType + ' --parallel ' + $Parallelism
	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}

function Run-Tests {
	param(
		[string] $BuildType,
		[bool]   $Progress = $False
	)

	Write-Host "===================================" -ForegroundColor Yellow
	Write-Host "Running Tests" -ForegroundColor Yellow
	Write-Host "===================================" -ForegroundColor Yellow

	$cmd = 'ctest --build-config ' + $BuildType + ' --output-on-failure --no-label-summary --no-subproject-summary'
	If(-Not $Progress){
		$cmd = $cmd + " --progress"
	}

	Write-Host $cmd -ForegroundColor Cyan
	Invoke-Expression $cmd
}

function Execute-AdventOfCodeScript {
	param(
		[Parameter(Mandatory=$true)]
		[string] $BuildType,
		[string] $AdditionalConfigureParams,
		[int]    $Parallelism = 1,
		[bool]   $Progress = $False,
		[bool]   $Clean = $True
	)

	Push-Location

	If($Clean) {	
		If (Test-Path -Path build) {
			Remove-Item -LiteralPath build -Force -Recurse
		}
	}

	If (-Not (Test-Path -Path build)) {
		New-Item -Path build -ItemType Directory | out-null	
	}

	Set-Location -Path build
	
	If($Clean) {	
		Generate-BuildFiles -BuildType $BuildType -AdditionalConfigureParams $AdditionalConfigureParams
	}

	Build-Solution -BuildType $BuildType -Parallelism $Parallelism
	Run-Tests -BuildType $BuildType -Progress $Progress

	Pop-Location
}

# Build from scratch/clean
# Clear-Host;. .\scripts\build_and_test.ps1;Execute-AdventOfCodeScript -BuildType "Debug" -Parallelism 4 -Clean $True -AdditionalConfigureParams "-DZENO_ROOT=`"C:/Workspace/Libraries/Zeno`""

# Build and run tests
# Clear-Host;. .\scripts\build_and_test.ps1;Execute-AdventOfCodeScript -BuildType "Debug" -Parallelism 4 -Clean $False