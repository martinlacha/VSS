# Simulace městské dopravy

## Požadavky

Projekt je napsaný v jazyce C++ a pro úspěšné sestavení projektu je potřeba mít nainstalované následující nástroje:
- `CMake`
- Linux: `make`
- Windows: `mingw32-make`

## Sestavení projektu a stáhnutí závislostí

Sestavení projektu se provede v kořenovém adresáři následujícím příkazem:

```
cmake -S . -B build/release -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
```

### Závislosti

V semestrální práci jsem si pro simulaci vybral následující knihovny pro vytvoření uživatelského rozhraní 
a zobrazení grafů a nastavení konfiguračních prvků, které nástroj `CMake` stáhne při z Github repozitářů při
sestavování projektu.

- https://github.com/ocornut/imgui
- https://github.com/epezent/implot


### Sestavení aplikace

Linux:
```
make -C build/release
```

Windows:

```
mingw32-make -C build\release
```

### Spuštění aplikace

Linux:

```
./build/release/src/simulation
```

Windows:

```
build\release\src\simulation.exe
```