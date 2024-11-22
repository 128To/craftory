# Craftory

This is a small game mixing Factorio, Cookie Clicker and Minecraft

## How to install on Windows

Setup vcpkg for dependencies

```
git clone https://github.com/microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg integrate install
```

Install dependencies

```
.\vcpkg\vcpkg install nana
```

Clone the project

```
git clone https://github.com/128To/craftory.git
```

Build the project

```
$msbuild = "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
msbuild <PATH_TO_CLONE> /p:Configuration=Release /p:Platform=x64
```

Run the project

```
<PATH_TO_CLONE>\x64\Release\craftory.exe
```
