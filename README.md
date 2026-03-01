## C# Interop (.dll via P/Invoke)

The C API used by Python is available in a shared library target for C# as well.

### Build the DLL (Windows)

Use a Visual Studio Developer Command Prompt, then:

```bash
mkdir build
cd build
cmake .. -DWITH_CSHARP_DLL=ON -DWITH_TESTS=OFF
cmake --build . --target PlateTectonicsCSharp --config Release
```

Output library name:
- `PlateTectonicsC.dll` (plus import library `PlateTectonicsC.lib`)

Depending on generator, artifacts are in `build/` or `build/Release/`.

### Minimal C# usage

```csharp
using System;
using System.Runtime.InteropServices;

internal static class PlatecNative
{
    private const string DllName = "PlateTectonicsC";

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr platec_api_create(
        int seed, uint width, uint height, float sea_level, uint erosion_period,
        float folding_ratio, uint aggr_overlap_abs, float aggr_overlap_rel,
        uint cycle_count, uint num_plates);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void platec_api_step(IntPtr litho);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern uint platec_api_is_finished(IntPtr litho);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr platec_api_get_heightmap(IntPtr litho);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern uint lithosphere_getMapWidth(IntPtr litho);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern uint lithosphere_getMapHeight(IntPtr litho);

    [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void platec_api_destroy(IntPtr litho);
}

// Example:
// var p = PlatecNative.platec_api_create(3, 512, 512, 0.65f, 60, 0.02f, 1000000, 0.33f, 2, 10);
// while (PlatecNative.platec_api_is_finished(p) == 0) PlatecNative.platec_api_step(p);
// uint w = PlatecNative.lithosphere_getMapWidth(p), h = PlatecNative.lithosphere_getMapHeight(p);
// float[] hm = new float[w * h];
// Marshal.Copy(PlatecNative.platec_api_get_heightmap(p), hm, 0, hm.Length);
// PlatecNative.platec_api_destroy(p);

