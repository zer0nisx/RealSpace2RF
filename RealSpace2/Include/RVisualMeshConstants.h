#pragma once

_NAMESPACE_REALSPACE2_BEGIN

// ==================== Animation Constants ====================
namespace AnimationConstants {
	// Grenade throwing animation frame threshold
	static constexpr int GRENADE_THROW_FRAME = 2 * 160;

	// Grenade fire delay in milliseconds
	static constexpr u64 GRENADE_FIRE_DELAY_MS = 70;

	// Animation speed constants
	static constexpr float DEFAULT_ANIMATION_SPEED = 4.8f;
	static constexpr float DEFAULT_BLEND_TIME = 1.0f;
	static constexpr float DEFAULT_CURRENT_BLEND_TIME = 0.5f;

	// Frame calculation constants
	static constexpr float FOOT_OFFSET_Y = 12.0f;
	static constexpr float FOOT_BLEND_RATIO = 0.5f;
}

// ==================== Rendering Constants ====================
namespace RenderingConstants {
	// Bounding box scaling factors
	static constexpr float BBOX_SCALE_PHYSIQUE = 1.1f;
	static constexpr float BBOX_SCALE_CALC = 1.2f;

	// Visibility thresholds
	static constexpr float MIN_VISIBILITY_THRESHOLD = 0.001f;

	// Weapon trail constants
	static constexpr float WEAPON_TRAIL_Y_OFFSET = 35.0f;
	static constexpr int WEAPON_TRACK_DEFAULT_SIZE = 10;

	// Color constants for enchants
	static constexpr u32 ENCHANT_FIRE_COLOR_1 = 0x4fff6666;
	static constexpr u32 ENCHANT_FIRE_COLOR_2 = 0x0fff6666;
	static constexpr u32 ENCHANT_COLD_COLOR_1 = 0x4f6666ff;
	static constexpr u32 ENCHANT_COLD_COLOR_2 = 0x0f6666ff;
	static constexpr u32 ENCHANT_LIGHTNING_COLOR_1 = 0x4f66ffff;
	static constexpr u32 ENCHANT_LIGHTNING_COLOR_2 = 0x0f66ffff;
	static constexpr u32 ENCHANT_POISON_COLOR_1 = 0x4f66ff66;
	static constexpr u32 ENCHANT_POISON_COLOR_2 = 0x0f66ff66;
	static constexpr u32 ENCHANT_DEFAULT_COLOR_1 = 0x4fffffff;
	static constexpr u32 ENCHANT_DEFAULT_COLOR_2 = 0x0fffffff;
}

// ==================== Memory Pool Constants ====================
namespace PoolConstants {
	// WeaponTracks pool size
	static constexpr size_t WEAPON_TRACKS_INITIAL_POOL_SIZE = 16;
	static constexpr size_t WEAPON_TRACKS_MAX_POOL_SIZE = 64;

	// Animation node table initial size
	static constexpr size_t ANIMATION_NODE_TABLE_INITIAL_SIZE = 32;
}

// ==================== LOD Constants ====================
namespace LODConstants {
	// Distance thresholds for LOD switching
	static constexpr float LOD_HIGH_DISTANCE = 100.0f;
	static constexpr float LOD_MEDIUM_DISTANCE = 250.0f;
	static constexpr float LOD_LOW_DISTANCE = 500.0f;

	// Screen size thresholds (pixels)
	static constexpr float LOD_HIGH_SCREEN_SIZE = 200.0f;
	static constexpr float LOD_MEDIUM_SCREEN_SIZE = 100.0f;
	static constexpr float LOD_LOW_SCREEN_SIZE = 50.0f;
}

// ==================== Fire Effect Constants ====================
namespace FireEffectConstants {
	// Fire texture size
	static constexpr int DEFAULT_FIRE_TEXTURE_WIDTH = 128;
	static constexpr int DEFAULT_FIRE_TEXTURE_HEIGHT = 128;

	// Fire processing constants
	static constexpr int FIRE_FUEL_VARIANCE = 64;
	static constexpr int FIRE_FUEL_OFFSET = 29;
	static constexpr int FIRE_STEP_X = 2;
	static constexpr int FIRE_BORDER_OFFSET = 10;

	// Fire effect rendering
	static constexpr float FIRE_EFFECT_Z_OFFSET = 50.0f;
	static constexpr u32 FIRE_EFFECT_COLOR = 0xaf9f9f9f;
	static constexpr u8 FIRE_ALPHA_FLAGS = 180;
}

// ==================== Performance Constants ====================
namespace PerformanceConstants {
	// Query timeouts
	static constexpr int QUERY_MAX_ITERATIONS = 5000;
	static constexpr u32 QUERY_FALLBACK_COUNT = 1000;
	static constexpr u32 QUERY_RENDER_THRESHOLD = 10;

	// Spline interpolation
	static constexpr float SPLINE_MIN_LENGTH = 10.0f;
	static constexpr float SPLINE_STEP_SIZE = 10.0f;
}

_NAMESPACE_REALSPACE2_END
