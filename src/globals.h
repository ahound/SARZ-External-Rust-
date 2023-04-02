#pragma once
#include <vector>
#include <thread>
#include <array>
#include "../xorstr.hpp"

#include "sdk/entity.h"
#include "../vector.h"

__declspec(align(16)) struct Color
{
	constexpr Color(const float r, const float g, const float b, const float a = 1.f) noexcept :
		r(r), g(g), b(b), a(a) { }

	float r, g, b, a;
};

// globals
namespace g {
	inline bool run = true;

	inline bool isVerified = false;
	inline char key[50] = "Enter your key";

	// Chosen Game
	inline bool rustChosen = false;
	inline bool apexChosen = false;
	inline bool r6sChosen = false;


	inline std::vector<c_entity> entity_list;
	inline c_entity local_player;

	void entities() noexcept;

// ==================================================================================================================

	// "BasePlayer" class
	constexpr const std::uintptr_t base_networkable() noexcept {
		return m::read<std::uintptr_t>(m::game + 52641616); // BaseEntity_TypeInfo
	}

	constexpr const std::uintptr_t unk1() noexcept {
		return m::read<std::uintptr_t>(base_networkable() + 0xB8);
	}

	constexpr const std::uintptr_t client_entities() noexcept {
		return m::read<std::uintptr_t>(unk1() + 0x10);
	}

	constexpr const std::uintptr_t entity_realm() noexcept {
		return m::read<std::uintptr_t>(client_entities() + 0x10);
	}

	constexpr const std::uintptr_t buffer_list() noexcept {
		return m::read<std::uintptr_t>(entity_realm() + 0x28);
	}

	constexpr const std::uintptr_t object_list() noexcept {
		return m::read<std::uintptr_t>(buffer_list() + 0x18);
	}

	constexpr const int object_list_size() noexcept {
		return m::read<int>(buffer_list() + 0x10);
	}

	constexpr const std::uintptr_t object_unkZ(const std::uintptr_t& element) noexcept {
		return m::read<std::uintptr_t>(element);
	}

	constexpr const std::uintptr_t base_mono_object(const std::uintptr_t& element) noexcept {
		return m::read<std::uintptr_t>(element + 0x10);
	}

	constexpr const std::uintptr_t object(const std::uintptr_t& element) noexcept {
		std::uintptr_t object = m::read<std::uintptr_t>(base_mono_object(element) + 0x30);
		return m::read<std::uintptr_t>(object + 0x30);
	}

	constexpr const std::uintptr_t object_unk(const std::uintptr_t& element) noexcept {
		return m::read<std::uintptr_t>(object(element) + 0x18);
	}
// ==================================================================================================================

	// "OcclusionCulling" class
	constexpr const std::uintptr_t occlusion_culling() noexcept {
		return m::read<std::uintptr_t>(m::game + 52605616);
	}

	constexpr const std::uintptr_t occlusion_object() noexcept {
		return m::read<std::uintptr_t>(occlusion_culling() + 0xB8);
	}

	constexpr const std::uintptr_t occlusion_singleton() noexcept {
		return m::read<std::uintptr_t>(occlusion_object() + 128);
	}

	constexpr const float occlusion_color_in() noexcept {
		return m::read<float>(occlusion_singleton() + 0x48);
	}

	constexpr const float occlusion_color_out() noexcept {
		return m::read<float>(occlusion_singleton() + 0x50);
	}

	static void set_culling_color(const float& r, const float& g, const float& b, const float& a) noexcept {
		m::write(occlusion_color_in() + 0x0, r);
		m::write(occlusion_color_in() + 0x4, g);
		m::write(occlusion_color_in() + 0x8, b);
		m::write(occlusion_color_in() + 0xC, a);
	}

	constexpr const std::uintptr_t occlusion_settings() noexcept {
		return m::read<std::uintptr_t>(occlusion_singleton() + 0x18);
	}

	constexpr const bool verify_layer_filter(const std::uintptr_t& value) noexcept {
		if (m::read<std::uintptr_t>(occlusion_settings() + 0x20) != value) { // AmbientMultiplier
			return false;
		}

		return true;
	}

	constexpr const int get_debug_mask() noexcept {
		return m::read<int>(occlusion_settings() + 0x1C);
	}

	static bool set_debug_mask(const std::uintptr_t& value) noexcept {
		return m::write(occlusion_settings() + 0x1C, value);
	}

	static bool set_layer_filter(const std::uintptr_t& value) noexcept {
		return m::write(occlusion_settings() + 0x20, value);
	}
// ==================================================================================================================

	// "ConVar.Graphics" class
	constexpr const std::uintptr_t fov_manager() noexcept {
		return m::read<std::uintptr_t>(m::game + 52694120); // ConVar.Graphics_TypeInfo
	}

	constexpr const std::uintptr_t graphics_instance() noexcept {
		return m::read<std::uintptr_t>(fov_manager() + 0xB8);
	}

	constexpr const std::uintptr_t get_graphics_fov() noexcept {
		return m::read<std::uintptr_t>(graphics_instance() + 0x18);
	}

	static bool set_graphics_fov(const float& value) noexcept {
		return m::write(graphics_instance() + 0x18, value);
	}

// ==================================================================================================================

	// "TOD_SKY" class
	constexpr const std::uintptr_t tod_sky() noexcept {
		return m::read<std::uintptr_t>(m::game + 52702440); // TOD_Sky_TypeInfo
	}

	constexpr const std::uintptr_t sky_parameters() noexcept {
		return m::read<std::uintptr_t>(tod_sky() + 0xB8);
	}

	constexpr const std::uintptr_t sky_base() noexcept {
		return m::read<std::uintptr_t>(sky_parameters());
	}

	constexpr const std::uintptr_t sky_func() noexcept {
		return m::read<std::uintptr_t>(sky_base() + 0x10);
	}

	constexpr const std::uintptr_t sky_config() noexcept {
		return m::read<std::uintptr_t>(sky_func() + 0x20);
	}

	constexpr const std::uintptr_t sky_night() noexcept {
		return m::read<std::uintptr_t>(sky_config() + 0x58);
	}

	constexpr const bool verify_full_bright(const float& amb, const float& light) noexcept {
		if (m::read<std::uintptr_t>(sky_night() + 0x50) != amb) { // AmbientMultiplier
			return false;
		}
		if (m::read<std::uintptr_t>(sky_night() + 0x48) != light) { // AmbientMultiplier
			return false;
		}

		return true;
	}


	static bool set_full_bright(const float& amb, const float& light) noexcept {
		m::write(sky_night() + 0x50, amb); // AmbientMultiplier
		m::write(sky_night() + 0x48, light); // LightIntensity

		return true;
	}

	constexpr const std::uintptr_t sky_components() noexcept {
		return m::read<std::uintptr_t>(sky_config() + 0xA8);
	}

	constexpr const std::uintptr_t sky_scattering() noexcept {
		return m::read<std::uintptr_t>(sky_components() + 0x1A0);
	}

	constexpr const std::uintptr_t sky_material() noexcept {
		return m::read<std::uintptr_t>(sky_scattering() + 0x78);
	}
}

// vars
namespace v {
	inline bool adminFlags = false;
	inline bool adminESP = false;
	inline bool rustChams = false;
	inline bool spiderMan = false;
	inline bool funnyJump = false;
	inline bool jumpShoot = false;
	inline bool omniSprint = false;
	inline bool rustFovChanger = false;
	inline bool	rustRecoil = false;
	inline bool	rustBullets = false;
	inline bool	fullBright = false;

	inline bool	noSpread = false;
	inline bool	thickBullet = false;
	inline bool	fullAuto = false;
	inline bool	instaEoka = false;
	inline bool	instaBow = false;
	inline bool	instaComp = false;

	inline float rustFovSlider = 90.f;
}
