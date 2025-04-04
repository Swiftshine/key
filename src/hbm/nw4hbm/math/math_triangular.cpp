#include "math_triangular.hpp"

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "math_arithmetic.hpp"

/*******************************************************************************
 * types
 */

// typedef names are from the nw4r version

// [SGLEA4]/GormitiDebug.elf:.debug_info::0x4a08a4
typedef struct /* explicitly untagged */
{
	f32	sin_val;	// size 0x04, offset 0x00
	f32	cos_val;	// size 0x04, offset 0x04
	f32	sin_delta;	// size 0x04, offset 0x08
	f32	cos_delta;	// size 0x04, offset 0x0c
} SinCosSample; // size 0x10

// [SGLEA4]/GormitiDebug.elf:.debug_info::0x4a090d
typedef struct /* explicitly untagged */
{
	f32	atan_val;	// size 0x04, offset 0x00
	f32	atan_delta;	// size 0x04, offset 0x04
} ArcTanSample; // size 0x08

/*******************************************************************************
 * local function declarations
 */

namespace nw4hbm { namespace math { namespace
{
	f32 AtanFIdx_(f32 x);
}}} // namespace nw4hbm::math::(unnamed)

/*******************************************************************************
 * variables
 */

namespace nw4hbm { namespace math { namespace
{
	// .data
	// clang-format off
	static SinCosSample sSinCosTbl[0x100 + 1] =
	{
		{0.0f,       1.0f,       0.024541f,  -3.01e-4f },
		{0.024541f,  0.999699f,  0.024526f,  -9.03e-4f },
		{0.049068f,  0.998795f,  0.024497f,  -0.001505f},
		{0.073565f,  0.99729f,   0.024453f,  -0.002106f},
		{0.098017f,  0.995185f,  0.024394f,  -0.002705f},
		{0.122411f,  0.99248f,   0.02432f,   -0.003303f},
		{0.14673f,   0.989177f,  0.024231f,  -0.003899f},
		{0.170962f,  0.985278f,  0.024128f,  -0.004492f},
		{0.19509f,   0.980785f,  0.024011f,  -0.005083f},
		{0.219101f,  0.975702f,  0.023879f,  -0.005671f},
		{0.24298f,   0.970031f,  0.023733f,  -0.006255f},
		{0.266713f,  0.963776f,  0.023572f,  -0.006836f},
		{0.290285f,  0.95694f,   0.023397f,  -0.007412f},
		{0.313682f,  0.949528f,  0.023208f,  -0.007984f},
		{0.33689f,   0.941544f,  0.023005f,  -0.008551f},
		{0.359895f,  0.932993f,  0.022788f,  -0.009113f},
		{0.382683f,  0.92388f,   0.022558f,  -0.00967f },
		{0.405241f,  0.91421f,   0.022314f,  -0.01022f },
		{0.427555f,  0.903989f,  0.022056f,  -0.010765f},
		{0.449611f,  0.893224f,  0.021785f,  -0.011303f},
		{0.471397f,  0.881921f,  0.021501f,  -0.011834f},
		{0.492898f,  0.870087f,  0.021205f,  -0.012358f},
		{0.514103f,  0.857729f,  0.020895f,  -0.012875f},
		{0.534998f,  0.844854f,  0.020573f,  -0.013384f},
		{0.55557f,   0.83147f,   0.020238f,  -0.013885f},
		{0.575808f,  0.817585f,  0.019891f,  -0.014377f},
		{0.595699f,  0.803208f,  0.019532f,  -0.014861f},
		{0.615232f,  0.788346f,  0.019162f,  -0.015336f},
		{0.634393f,  0.77301f,   0.01878f,   -0.015802f},
		{0.653173f,  0.757209f,  0.018386f,  -0.016258f},
		{0.671559f,  0.740951f,  0.017982f,  -0.016704f},
		{0.689541f,  0.724247f,  0.017566f,  -0.01714f },
		{0.707107f,  0.707107f,  0.01714f,   -0.017566f},
		{0.724247f,  0.689541f,  0.016704f,  -0.017982f},
		{0.740951f,  0.671559f,  0.016258f,  -0.018386f},
		{0.757209f,  0.653173f,  0.015802f,  -0.01878f },
		{0.77301f,   0.634393f,  0.015336f,  -0.019162f},
		{0.788346f,  0.615232f,  0.014861f,  -0.019532f},
		{0.803208f,  0.595699f,  0.014377f,  -0.019891f},
		{0.817585f,  0.575808f,  0.013885f,  -0.020238f},
		{0.83147f,   0.55557f,   0.013384f,  -0.020573f},
		{0.844854f,  0.534998f,  0.012875f,  -0.020895f},
		{0.857729f,  0.514103f,  0.012358f,  -0.021205f},
		{0.870087f,  0.492898f,  0.011834f,  -0.021501f},
		{0.881921f,  0.471397f,  0.011303f,  -0.021785f},
		{0.893224f,  0.449611f,  0.010765f,  -0.022056f},
		{0.903989f,  0.427555f,  0.01022f,   -0.022314f},
		{0.91421f,   0.405241f,  0.00967f,   -0.022558f},
		{0.92388f,   0.382683f,  0.009113f,  -0.022788f},
		{0.932993f,  0.359895f,  0.008551f,  -0.023005f},
		{0.941544f,  0.33689f,   0.007984f,  -0.023208f},
		{0.949528f,  0.313682f,  0.007412f,  -0.023397f},
		{0.95694f,   0.290285f,  0.006836f,  -0.023572f},
		{0.963776f,  0.266713f,  0.006255f,  -0.023733f},
		{0.970031f,  0.24298f,   0.005671f,  -0.023879f},
		{0.975702f,  0.219101f,  0.005083f,  -0.024011f},
		{0.980785f,  0.19509f,   0.004492f,  -0.024128f},
		{0.985278f,  0.170962f,  0.003899f,  -0.024231f},
		{0.989177f,  0.14673f,   0.003303f,  -0.02432f },
		{0.99248f,   0.122411f,  0.002705f,  -0.024394f},
		{0.995185f,  0.098017f,  0.002106f,  -0.024453f},
		{0.99729f,   0.073565f,  0.001505f,  -0.024497f},
		{0.998795f,  0.049068f,  9.03e-4f,   -0.024526f},
		{0.999699f,  0.024541f,  3.01e-4f,   -0.024541f},
		{1.0f,       0.0f,       -3.01e-4f,  -0.024541f},
		{0.999699f,  -0.024541f, -9.03e-4f,  -0.024526f},
		{0.998795f,  -0.049068f, -0.001505f, -0.024497f},
		{0.99729f,   -0.073565f, -0.002106f, -0.024453f},
		{0.995185f,  -0.098017f, -0.002705f, -0.024394f},
		{0.99248f,   -0.122411f, -0.003303f, -0.02432f },
		{0.989177f,  -0.14673f,  -0.003899f, -0.024231f},
		{0.985278f,  -0.170962f, -0.004492f, -0.024128f},
		{0.980785f,  -0.19509f,  -0.005083f, -0.024011f},
		{0.975702f,  -0.219101f, -0.005671f, -0.023879f},
		{0.970031f,  -0.24298f,  -0.006255f, -0.023733f},
		{0.963776f,  -0.266713f, -0.006836f, -0.023572f},
		{0.95694f,   -0.290285f, -0.007412f, -0.023397f},
		{0.949528f,  -0.313682f, -0.007984f, -0.023208f},
		{0.941544f,  -0.33689f,  -0.008551f, -0.023005f},
		{0.932993f,  -0.359895f, -0.009113f, -0.022788f},
		{0.92388f,   -0.382683f, -0.00967f,  -0.022558f},
		{0.91421f,   -0.405241f, -0.01022f,  -0.022314f},
		{0.903989f,  -0.427555f, -0.010765f, -0.022056f},
		{0.893224f,  -0.449611f, -0.011303f, -0.021785f},
		{0.881921f,  -0.471397f, -0.011834f, -0.021501f},
		{0.870087f,  -0.492898f, -0.012358f, -0.021205f},
		{0.857729f,  -0.514103f, -0.012875f, -0.020895f},
		{0.844854f,  -0.534998f, -0.013384f, -0.020573f},
		{0.83147f,   -0.55557f,  -0.013885f, -0.020238f},
		{0.817585f,  -0.575808f, -0.014377f, -0.019891f},
		{0.803208f,  -0.595699f, -0.014861f, -0.019532f},
		{0.788346f,  -0.615232f, -0.015336f, -0.019162f},
		{0.77301f,   -0.634393f, -0.015802f, -0.01878f },
		{0.757209f,  -0.653173f, -0.016258f, -0.018386f},
		{0.740951f,  -0.671559f, -0.016704f, -0.017982f},
		{0.724247f,  -0.689541f, -0.01714f,  -0.017566f},
		{0.707107f,  -0.707107f, -0.017566f, -0.01714f },
		{0.689541f,  -0.724247f, -0.017982f, -0.016704f},
		{0.671559f,  -0.740951f, -0.018386f, -0.016258f},
		{0.653173f,  -0.757209f, -0.01878f,  -0.015802f},
		{0.634393f,  -0.77301f,  -0.019162f, -0.015336f},
		{0.615232f,  -0.788346f, -0.019532f, -0.014861f},
		{0.595699f,  -0.803208f, -0.019891f, -0.014377f},
		{0.575808f,  -0.817585f, -0.020238f, -0.013885f},
		{0.55557f,   -0.83147f,  -0.020573f, -0.013384f},
		{0.534998f,  -0.844854f, -0.020895f, -0.012875f},
		{0.514103f,  -0.857729f, -0.021205f, -0.012358f},
		{0.492898f,  -0.870087f, -0.021501f, -0.011834f},
		{0.471397f,  -0.881921f, -0.021785f, -0.011303f},
		{0.449611f,  -0.893224f, -0.022056f, -0.010765f},
		{0.427555f,  -0.903989f, -0.022314f, -0.01022f },
		{0.405241f,  -0.91421f,  -0.022558f, -0.00967f },
		{0.382683f,  -0.92388f,  -0.022788f, -0.009113f},
		{0.359895f,  -0.932993f, -0.023005f, -0.008551f},
		{0.33689f,   -0.941544f, -0.023208f, -0.007984f},
		{0.313682f,  -0.949528f, -0.023397f, -0.007412f},
		{0.290285f,  -0.95694f,  -0.023572f, -0.006836f},
		{0.266713f,  -0.963776f, -0.023733f, -0.006255f},
		{0.24298f,   -0.970031f, -0.023879f, -0.005671f},
		{0.219101f,  -0.975702f, -0.024011f, -0.005083f},
		{0.19509f,   -0.980785f, -0.024128f, -0.004492f},
		{0.170962f,  -0.985278f, -0.024231f, -0.003899f},
		{0.14673f,   -0.989177f, -0.02432f,  -0.003303f},
		{0.122411f,  -0.99248f,  -0.024394f, -0.002705f},
		{0.098017f,  -0.995185f, -0.024453f, -0.002106f},
		{0.073565f,  -0.99729f,  -0.024497f, -0.001505f},
		{0.049068f,  -0.998795f, -0.024526f, -9.03e-4f },
		{0.024541f,  -0.999699f, -0.024541f, -3.01e-4f },
		{0.0f,       -1.0f,      -0.024541f, 3.01e-4f  },
		{-0.024541f, -0.999699f, -0.024526f, 9.03e-4f  },
		{-0.049068f, -0.998795f, -0.024497f, 0.001505f },
		{-0.073565f, -0.99729f,  -0.024453f, 0.002106f },
		{-0.098017f, -0.995185f, -0.024394f, 0.002705f },
		{-0.122411f, -0.99248f,  -0.02432f,  0.003303f },
		{-0.14673f,  -0.989177f, -0.024231f, 0.003899f },
		{-0.170962f, -0.985278f, -0.024128f, 0.004492f },
		{-0.19509f,  -0.980785f, -0.024011f, 0.005083f },
		{-0.219101f, -0.975702f, -0.023879f, 0.005671f },
		{-0.24298f,  -0.970031f, -0.023733f, 0.006255f },
		{-0.266713f, -0.963776f, -0.023572f, 0.006836f },
		{-0.290285f, -0.95694f,  -0.023397f, 0.007412f },
		{-0.313682f, -0.949528f, -0.023208f, 0.007984f },
		{-0.33689f,  -0.941544f, -0.023005f, 0.008551f },
		{-0.359895f, -0.932993f, -0.022788f, 0.009113f },
		{-0.382683f, -0.92388f,  -0.022558f, 0.00967f  },
		{-0.405241f, -0.91421f,  -0.022314f, 0.01022f  },
		{-0.427555f, -0.903989f, -0.022056f, 0.010765f },
		{-0.449611f, -0.893224f, -0.021785f, 0.011303f },
		{-0.471397f, -0.881921f, -0.021501f, 0.011834f },
		{-0.492898f, -0.870087f, -0.021205f, 0.012358f },
		{-0.514103f, -0.857729f, -0.020895f, 0.012875f },
		{-0.534998f, -0.844854f, -0.020573f, 0.013384f },
		{-0.55557f,  -0.83147f,  -0.020238f, 0.013885f },
		{-0.575808f, -0.817585f, -0.019891f, 0.014377f },
		{-0.595699f, -0.803208f, -0.019532f, 0.014861f },
		{-0.615232f, -0.788346f, -0.019162f, 0.015336f },
		{-0.634393f, -0.77301f,  -0.01878f,  0.015802f },
		{-0.653173f, -0.757209f, -0.018386f, 0.016258f },
		{-0.671559f, -0.740951f, -0.017982f, 0.016704f },
		{-0.689541f, -0.724247f, -0.017566f, 0.01714f  },
		{-0.707107f, -0.707107f, -0.01714f,  0.017566f },
		{-0.724247f, -0.689541f, -0.016704f, 0.017982f },
		{-0.740951f, -0.671559f, -0.016258f, 0.018386f },
		{-0.757209f, -0.653173f, -0.015802f, 0.01878f  },
		{-0.77301f,  -0.634393f, -0.015336f, 0.019162f },
		{-0.788346f, -0.615232f, -0.014861f, 0.019532f },
		{-0.803208f, -0.595699f, -0.014377f, 0.019891f },
		{-0.817585f, -0.575808f, -0.013885f, 0.020238f },
		{-0.83147f,  -0.55557f,  -0.013384f, 0.020573f },
		{-0.844854f, -0.534998f, -0.012875f, 0.020895f },
		{-0.857729f, -0.514103f, -0.012358f, 0.021205f },
		{-0.870087f, -0.492898f, -0.011834f, 0.021501f },
		{-0.881921f, -0.471397f, -0.011303f, 0.021785f },
		{-0.893224f, -0.449611f, -0.010765f, 0.022056f },
		{-0.903989f, -0.427555f, -0.01022f,  0.022314f },
		{-0.91421f,  -0.405241f, -0.00967f,  0.022558f },
		{-0.92388f,  -0.382683f, -0.009113f, 0.022788f },
		{-0.932993f, -0.359895f, -0.008551f, 0.023005f },
		{-0.941544f, -0.33689f,  -0.007984f, 0.023208f },
		{-0.949528f, -0.313682f, -0.007412f, 0.023397f },
		{-0.95694f,  -0.290285f, -0.006836f, 0.023572f },
		{-0.963776f, -0.266713f, -0.006255f, 0.023733f },
		{-0.970031f, -0.24298f,  -0.005671f, 0.023879f },
		{-0.975702f, -0.219101f, -0.005083f, 0.024011f },
		{-0.980785f, -0.19509f,  -0.004492f, 0.024128f },
		{-0.985278f, -0.170962f, -0.003899f, 0.024231f },
		{-0.989177f, -0.14673f,  -0.003303f, 0.02432f  },
		{-0.99248f,  -0.122411f, -0.002705f, 0.024394f },
		{-0.995185f, -0.098017f, -0.002106f, 0.024453f },
		{-0.99729f,  -0.073565f, -0.001505f, 0.024497f },
		{-0.998795f, -0.049068f, -9.03e-4f,  0.024526f },
		{-0.999699f, -0.024541f, -3.01e-4f,  0.024541f },
		{-1.0f,      -0.0f,      3.01e-4f,   0.024541f },
		{-0.999699f, 0.024541f,  9.03e-4f,   0.024526f },
		{-0.998795f, 0.049068f,  0.001505f,  0.024497f },
		{-0.99729f,  0.073565f,  0.002106f,  0.024453f },
		{-0.995185f, 0.098017f,  0.002705f,  0.024394f },
		{-0.99248f,  0.122411f,  0.003303f,  0.02432f  },
		{-0.989177f, 0.14673f,   0.003899f,  0.024231f },
		{-0.985278f, 0.170962f,  0.004492f,  0.024128f },
		{-0.980785f, 0.19509f,   0.005083f,  0.024011f },
		{-0.975702f, 0.219101f,  0.005671f,  0.023879f },
		{-0.970031f, 0.24298f,   0.006255f,  0.023733f },
		{-0.963776f, 0.266713f,  0.006836f,  0.023572f },
		{-0.95694f,  0.290285f,  0.007412f,  0.023397f },
		{-0.949528f, 0.313682f,  0.007984f,  0.023208f },
		{-0.941544f, 0.33689f,   0.008551f,  0.023005f },
		{-0.932993f, 0.359895f,  0.009113f,  0.022788f },
		{-0.92388f,  0.382683f,  0.00967f,   0.022558f },
		{-0.91421f,  0.405241f,  0.01022f,   0.022314f },
		{-0.903989f, 0.427555f,  0.010765f,  0.022056f },
		{-0.893224f, 0.449611f,  0.011303f,  0.021785f },
		{-0.881921f, 0.471397f,  0.011834f,  0.021501f },
		{-0.870087f, 0.492898f,  0.012358f,  0.021205f },
		{-0.857729f, 0.514103f,  0.012875f,  0.020895f },
		{-0.844854f, 0.534998f,  0.013384f,  0.020573f },
		{-0.83147f,  0.55557f,   0.013885f,  0.020238f },
		{-0.817585f, 0.575808f,  0.014377f,  0.019891f },
		{-0.803208f, 0.595699f,  0.014861f,  0.019532f },
		{-0.788346f, 0.615232f,  0.015336f,  0.019162f },
		{-0.77301f,  0.634393f,  0.015802f,  0.01878f  },
		{-0.757209f, 0.653173f,  0.016258f,  0.018386f },
		{-0.740951f, 0.671559f,  0.016704f,  0.017982f },
		{-0.724247f, 0.689541f,  0.01714f,   0.017566f },
		{-0.707107f, 0.707107f,  0.017566f,  0.01714f  },
		{-0.689541f, 0.724247f,  0.017982f,  0.016704f },
		{-0.671559f, 0.740951f,  0.018386f,  0.016258f },
		{-0.653173f, 0.757209f,  0.01878f,   0.015802f },
		{-0.634393f, 0.77301f,   0.019162f,  0.015336f },
		{-0.615232f, 0.788346f,  0.019532f,  0.014861f },
		{-0.595699f, 0.803208f,  0.019891f,  0.014377f },
		{-0.575808f, 0.817585f,  0.020238f,  0.013885f },
		{-0.55557f,  0.83147f,   0.020573f,  0.013384f },
		{-0.534998f, 0.844854f,  0.020895f,  0.012875f },
		{-0.514103f, 0.857729f,  0.021205f,  0.012358f },
		{-0.492898f, 0.870087f,  0.021501f,  0.011834f },
		{-0.471397f, 0.881921f,  0.021785f,  0.011303f },
		{-0.449611f, 0.893224f,  0.022056f,  0.010765f },
		{-0.427555f, 0.903989f,  0.022314f,  0.01022f  },
		{-0.405241f, 0.91421f,   0.022558f,  0.00967f  },
		{-0.382683f, 0.92388f,   0.022788f,  0.009113f },
		{-0.359895f, 0.932993f,  0.023005f,  0.008551f },
		{-0.33689f,  0.941544f,  0.023208f,  0.007984f },
		{-0.313682f, 0.949528f,  0.023397f,  0.007412f },
		{-0.290285f, 0.95694f,   0.023572f,  0.006836f },
		{-0.266713f, 0.963776f,  0.023733f,  0.006255f },
		{-0.24298f,  0.970031f,  0.023879f,  0.005671f },
		{-0.219101f, 0.975702f,  0.024011f,  0.005083f },
		{-0.19509f,  0.980785f,  0.024128f,  0.004492f },
		{-0.170962f, 0.985278f,  0.024231f,  0.003899f },
		{-0.14673f,  0.989177f,  0.02432f,   0.003303f },
		{-0.122411f, 0.99248f,   0.024394f,  0.002705f },
		{-0.098017f, 0.995185f,  0.024453f,  0.002106f },
		{-0.073565f, 0.99729f,   0.024497f,  0.001505f },
		{-0.049068f, 0.998795f,  0.024526f,  9.03e-4f  },
		{-0.024541f, 0.999699f,  0.024541f,  3.01e-4f  },
		{-0.0f,      1.0f,       0.024541f,  -3.01e-4f }
	};

	static ArcTanSample sArcTanTbl[0x20 + 1] =
	{
		{0.0f,        1.2728254f },
		{1.2728254f,  1.2703458f },
		{2.5431712f,  1.2654155f },
		{3.8085866f,  1.2580916f },
		{5.0666785f,  1.2484571f },
		{6.3151355f,  1.2366195f },
		{7.551755f,   1.2227072f },
		{8.774462f,   1.2068666f },
		{9.981329f,   1.1892582f },
		{11.170587f,  1.1700529f },
		{12.34064f,   1.149428f  },
		{13.4900675f, 1.1275644f },
		{14.617632f,  1.1046423f },
		{15.722275f,  1.0808387f },
		{16.803114f,  1.0563251f },
		{17.859438f,  1.0312649f },
		{18.890703f,  1.005812f  },
		{19.896515f,  0.98010963f},
		{20.876625f,  0.9542891f },
		{21.830914f,  0.9284698f },
		{22.759384f,  0.90275896f},
		{23.662142f,  0.87725157f},
		{24.539394f,  0.8520309f },
		{25.391424f,  0.8271689f },
		{26.218594f,  0.802727f  },
		{27.02132f,   0.77875656f},
		{27.800077f,  0.7553001f },
		{28.555378f,  0.7323915f },
		{29.28777f,   0.7100574f },
		{29.997826f,  0.6883175f },
		{30.686144f,  0.66718566f},
		{31.353329f,  0.6466705f },
		{32.0f,       0.62677616f}
	};
	// clang-format on
}}} // namespace nw4hbm::math::(unnamed)

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace math {

namespace {

f32 AtanFIdx_(f32 x)
{
	u16 idx;
	f32 val;
	f32 r;

	x *= 32.0f;

	idx = F32ToU16(x);
	r = x - U16ToF32(idx);
	val = sArcTanTbl[idx].atan_val + r * sArcTanTbl[idx].atan_delta;

	return val;
}

} // unnamed namespace

f32 SinFIdx(f32 fidx)
{
	f32 abs_fidx = FAbs(fidx); // hm
	f32 val;
	u16 idx;
	f32 r;

	while (abs_fidx >= 65536.0f)
		abs_fidx -= 65536.0f;

	idx = F32ToU16(abs_fidx);
	r = abs_fidx - U16ToF32(idx);

	idx &= 0xff;
	val = sSinCosTbl[idx].sin_val + r * sSinCosTbl[idx].sin_delta;

	return fidx < 0.0f ? -val : val;
}

f32 CosFIdx(f32 fidx)
{
	u16 idx;
	f32 r;

	fidx = FAbs(fidx);
	while (fidx >= 65536.0f)
		fidx -= 65536.0f;

	idx = F32ToU16(fidx);
	r = fidx - U16ToF32(idx);

	idx &= 0xff;

	return sSinCosTbl[idx].cos_val + r * sSinCosTbl[idx].cos_delta;
}

extern void __deadstrip1();
extern void __deadstrip1()
{
	(void)1.0f;
	(void)32.0f;
	(void)64.0f;
	(void)-1.0f;
}

f32 Atan2FIdx(f32 y, f32 x)
{
	f32 a;
	f32 b;
	f32 c;
	bool minus;

	if (x == 0.0f && y == 0.0f)
		return 0.0f;

	// clang-format off
	if (x >= 0.0f)
	{
		if (y >= 0.0f)
		{
			if (x >= y)
			{
				a = x;
				b = y;
				c = 0.0f;

				minus = false;
			}
			else
			{
				a = y;
				b = x;
				c = 64.0f;

				minus = true;
			}
		}
		else
		{
			if (x >= -y)
			{
				a = x;
				b = -y;
				c = 0.0f;

				minus = true;
			}
			else
			{
				a = -y;
				b = x;
				c = -64.0f;

				minus = false;
			}
		}
	}
	else
	{
		if (y >= 0.0f)
		{
			if (-x >= y)
			{
				a = -x;
				b = y;
				c = 128.0f;

				minus = true;
			}
			else
			{
				a = y;
				b = -x;
				c = 64.0f;

				minus = false;
			}
		}
		else
		{
			if (-x >= -y)
			{
				a = -x;
				b = -y;
				c = -128.0f;

				minus = false;
			}
			else
			{
				a = -y;
				b = -x;
				c = -64.0f;

				minus = true;
			}
		}
	}
	// clang-format on

	return minus ? c - AtanFIdx_(b / a) : c + AtanFIdx_(b / a);
}

}} // namespace nw4hbm::math
