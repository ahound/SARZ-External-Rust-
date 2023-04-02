#pragma once
#include "../utils/memory.h"


class c_entity {
	// BasePlayer
	constexpr const std::uintptr_t playerFlags() const noexcept { return 0x688; }
	constexpr const std::uintptr_t lifeState() const noexcept { return 0x224; }

	// Inventory
	constexpr const std::uintptr_t inventory() const noexcept { return 0x698; }
	constexpr const std::uintptr_t activeItem() const noexcept { return 0x5D0; }
	constexpr const std::uintptr_t baseProjectile() const noexcept { return 0x98; }
	constexpr const std::uintptr_t createdProjectile() const noexcept { return 0x370; }
	constexpr const std::uintptr_t recoilProperties() const noexcept { return 0x2E0; }
	constexpr const std::uintptr_t newRecoilProperties() const noexcept { return 0x78; }

	constexpr const std::uintptr_t recoilYawMin() const noexcept { return 0x18; }
	constexpr const std::uintptr_t recoilYawMax() const noexcept { return 0x1C; }
	constexpr const std::uintptr_t recoilPitchMin() const noexcept { return 0x20; }
	constexpr const std::uintptr_t recoilPitchMax() const noexcept { return 0x24; }
	constexpr const std::uintptr_t aimconecurvescale() const noexcept { return 0x60; }

	constexpr const std::uintptr_t stringHoldDurationMax() const noexcept { return 0x390; }
	constexpr const std::uintptr_t wasAiming() const noexcept { return 0x388; }
	constexpr const std::uintptr_t successFraction() const noexcept { return 0x378; }
	constexpr const std::uintptr_t arrowBack() const noexcept { return 0x37C; }

	constexpr const std::uintptr_t fullAuto() const noexcept { return 0x290; }

	// PlayerModel
	constexpr const std::uintptr_t playerModel() const noexcept { return 0x4C8; }
	constexpr const std::uintptr_t isNPC() const noexcept { return 0x320; }
	constexpr const std::uintptr_t isLocalPlayer() const noexcept { return 0x299; }
	constexpr const std::uintptr_t maleSkin() const noexcept { return 0x1A0; }
	constexpr const std::uintptr_t femaleSkin() const noexcept { return 0x1A8; }
	constexpr const std::uintptr_t skinType() const noexcept { return 0x1CC; }
	constexpr const std::uintptr_t skins() const noexcept { return 0x18; }
	constexpr const std::uintptr_t skinSize() const noexcept { return 0x18; }
	constexpr const std::uintptr_t skin() const noexcept { return 0x20; }

	constexpr const std::uintptr_t bodyMesh() const noexcept { return 0x68; }
	constexpr const std::uintptr_t headMesh() const noexcept { return 0x70; }
	constexpr const std::uintptr_t eyeMesh() const noexcept { return 0x78; }

	// ModelState
	constexpr const std::uintptr_t modelState() const noexcept { return 0x5F8; }
	constexpr const std::uintptr_t modelStateFlags() const noexcept { return 0x24; }

	// BaseMovement
	constexpr const std::uintptr_t baseMovement() const noexcept { return 0x4F0; }

public:
	c_entity() = default;

	c_entity(const std::uintptr_t& addr_to_read) noexcept :
		_addr(m::read<std::uintptr_t>(addr_to_read)) { }

	void set_address(const std::uintptr_t& addr_to_read) noexcept {
		_addr = m::read<std::uintptr_t>(addr_to_read);
	}

	constexpr const bool is_valid() const noexcept {
		return _addr != 0;
	}

public:
	constexpr bool operator==(const c_entity& other_ent) const noexcept {
		return _addr == other_ent._addr;
	}

public:
	// For anything that requires writing memory, return a boolean value to determine if it has successfully written memory.
	// If it contains more than 1 line, then make it a void, but have strict exceptions.

// ==================================================================================================================
	// BasePlayer
	const void set_player_flags(const int& flag) const noexcept {
		m::write(_addr + playerFlags(), flag); 
	}

	constexpr const int get_player_flags() const noexcept {
		return m::read<int>(_addr + playerFlags());
	}

	constexpr const float get_health() const noexcept {
		return m::read<float>(_addr + 0x22C);
	}

	constexpr const int get_life_state() const noexcept {
		return m::read<int>(_addr + lifeState());
	}

	const void set_clothes_rebuild(const bool& value) const noexcept {
		m::write(_addr + 0x528, value); // needsClothesRebuild
	}

	// ==================================================================================================================
		// Inventory
	constexpr const std::uintptr_t get_inventory() const noexcept {
		return m::read<std::uintptr_t>(_addr + inventory());
	}

	constexpr const std::uintptr_t get_active_item() const noexcept {
		return m::read<std::uintptr_t>(_addr + activeItem());
	}

	constexpr const std::uintptr_t get_items(const std::uintptr_t& inventory) const noexcept {
		auto belt = m::read<std::uintptr_t>(inventory + 0x28);
		auto itemlist = m::read<std::uintptr_t>(belt + 0x38);
		return m::read<std::uintptr_t>(itemlist + 0x10);
	}

	constexpr const std::uintptr_t get_item(const std::uintptr_t& items, const int& etc) const noexcept {
		return m::read<std::uintptr_t>(items + 0x20 + etc);
	}

	constexpr const std::uintptr_t get_item_id(const std::uintptr_t& item) const noexcept {
		return m::read<std::uintptr_t>(item + 0x28);
	}

	constexpr const std::uintptr_t get_base_projectile(const std::uintptr_t& item) const noexcept {
		return m::read<std::uintptr_t>(item + 0x98);
	}

	constexpr const std::uintptr_t get_created_projectile(const std::uintptr_t& baseproj) const noexcept {
		return m::read<std::uintptr_t>(baseproj + createdProjectile());
	}

	constexpr const std::uintptr_t get_projectile_list(const std::uintptr_t& proj) const noexcept {
		return m::read<std::uintptr_t>(proj + 0x10);
	}

	constexpr const std::uintptr_t get_projectile_list_size(const std::uintptr_t& projList) const noexcept {
		return m::read<std::uintptr_t>(projList + 0x18);
	}

	constexpr const std::uintptr_t get_projectile(const std::uintptr_t& projlist, const int& etc) const noexcept {
		return m::read<std::uintptr_t>(projlist + 0x20 + etc);
	}

	constexpr const std::uintptr_t get_recoil_props(const std::uintptr_t& baseproj) const noexcept {
		return m::read<std::uintptr_t>(baseproj + 0x2E0);
	}

	constexpr const std::uintptr_t get_new_recoil_props(const std::uintptr_t& recoilprop) const noexcept {
		return m::read<std::uintptr_t>(recoilprop + 0x78);
	}

	constexpr const bool verify_recoil_props(const std::uintptr_t& recoilprop, const float& value) const noexcept {

		if (m::read<float>(recoilprop + recoilYawMin()) != value) {
			return false;
		}
		else if (m::read<float>(recoilprop + recoilYawMax()) != value) {
			return false;
		}
		else if (m::read<float>(recoilprop + recoilPitchMin()) != value) {
			return false;
		}
		else if (m::read<float>(recoilprop + recoilPitchMax()) != value) {
			return false;
		}
		else if (m::read<float>(recoilprop + aimconecurvescale()) != -100.f) {
			return false;
		}

		return true;
	}

	const void set_recoil_props(const std::uintptr_t& recoilprop, const float& value) const noexcept {
		m::write(recoilprop + recoilYawMin(), value);
		m::write(recoilprop + recoilYawMax(), value);
		m::write(recoilprop + recoilPitchMin(), value);
		m::write(recoilprop + recoilPitchMax(), value);
		m::write(recoilprop + aimconecurvescale(), -100.f);
	}

	constexpr const bool verify_projectile_thickness(const std::uintptr_t& projectile, const float& value) const noexcept {
		if (m::read<float>(projectile + 0x2C) != value) {
			return false;
		}

		return true;
	}

	const void set_projectile_thickness(const std::uintptr_t& projectile, const float& value) const noexcept {
		m::write(projectile + 0x2C, value);
	}

	const void set_projectile_spread(const std::uintptr_t& projectile, const float& value) const noexcept {
		auto mod = m::read<uintptr_t>(projectile + 0xE8); // ItemModProjectile 
		m::write(mod + 0x30, value); // projectileSpread
		m::write(mod + 0x38, value); // projectileVelocitySpread
	}

	constexpr const bool verify_full_auto(const std::uintptr_t& baseproj) const noexcept {
		if (m::read<bool>(baseproj + 0x290) != true) {
			return false;
		}
	}

	constexpr const bool verify_insta_eoka(const std::uintptr_t& baseproj) const noexcept {
		if (m::read<float>(baseproj + successFraction()) != 1.f) {
			return false;
		}

		return true;
	}

	constexpr const bool verify_insta_bow(const std::uintptr_t& baseproj) const noexcept {
		if (m::read<float>(baseproj + arrowBack()) != 0.f) {
			return false;
		}
		if (m::read<float>(baseproj + stringHoldDurationMax()) != 0.f) {
			return false;
		}
		if (m::read<bool>(baseproj + successFraction()) != true) {
			return false;
		}
		if (m::read<bool>(baseproj + wasAiming()) != true) {
			return false;
		}

		return true;
	}

	const void set_full_auto(const std::uintptr_t& baseproj) const noexcept {
		m::write(baseproj + 0x290, true); // fullAuto
	}

	const void set_insta_eoka(const std::uintptr_t& baseproj) const noexcept {
		m::write(baseproj + successFraction(), 1.f);
	}

	const void set_insta_bow(const std::uintptr_t& baseproj) const noexcept {
		m::write(baseproj + arrowBack(), 0.f);
		m::write(baseproj + stringHoldDurationMax(), 0.f);
		m::write(baseproj + successFraction(), true);
		m::write(baseproj + wasAiming(), true);
	}

	// ==================================================================================================================
		// PlayerModel
	constexpr const std::uintptr_t get_player_model() const noexcept {
		return m::read<std::uintptr_t>(_addr + playerModel());
	}

	constexpr const bool is_local_player(const std::uintptr_t& playerModel) const noexcept {
		return m::read<bool>(playerModel + isLocalPlayer());
	}

	constexpr const bool is_npc(const std::uintptr_t& playerModel) const noexcept {
		return m::read<bool>(playerModel + isNPC());
	}

	constexpr const std::uintptr_t get_skin_type(const std::uintptr_t& playerModel) const noexcept {
		return m::read<std::uintptr_t>(playerModel + skinType());
	}

	constexpr const std::uintptr_t get_male_skin(const std::uintptr_t& playerModel) const noexcept {
		return m::read<std::uintptr_t>(playerModel + maleSkin());
	}

	constexpr const std::uintptr_t get_female_skin(const std::uintptr_t& playerModel) const noexcept {
		return m::read<std::uintptr_t>(playerModel + femaleSkin());
	}

	constexpr const std::uintptr_t get_skins(const std::uintptr_t& skinComponent) const noexcept {
		return m::read<std::uintptr_t>(skinComponent + skins());
	}

	constexpr const std::uintptr_t get_skins_size(const std::uintptr_t& skins) const noexcept {
		return m::read<std::uintptr_t>(skins + skinSize());
	}

	constexpr const std::uintptr_t get_skin(const std::uintptr_t& skins, const int& etc) const noexcept {
		return m::read<std::uintptr_t>(skins + skin() + etc);
	}


	const void set_skin_material(const std::uintptr_t& skin, const std::uintptr_t& value) const noexcept {
		m::write(skin + bodyMesh(), value);
		m::write(skin + headMesh(), value);
		m::write(skin + eyeMesh(), value);
	}

	// ==================================================================================================================
		// ModelState
	constexpr const std::uintptr_t get_model_state() const noexcept {
		return m::read<std::uintptr_t>(_addr + modelState());
	}

	constexpr const int get_model_state_flags(const std::uintptr_t& modelstate) const noexcept {
		return m::read<int>(modelstate + 0x24); // modelStateFlags
	}

	const void set_model_state_flags(const std::uintptr_t& modelstate, const int& flag) const noexcept {
		m::write(modelstate + 0x24, flag);
	}

	// ==================================================================================================================
		// BaseMovement
	constexpr const std::uintptr_t get_base_movement() const noexcept {
		return m::read<std::uintptr_t>(_addr + baseMovement());
	}

	const void set_spider_man(const std::uintptr_t& movement) const noexcept {
		m::write(movement + 0xC4, 0.f); // private float groundAngle; 
		m::write(movement + 0xC8, 0.f); // private float groundAngleNew; 
	}

	const void set_funny_jump(const std::uintptr_t& movement) const noexcept {
		m::write(movement + 0x90, 999.f); // maxAngleClimbing; 
		m::write(movement + 0x8C, 999.f); // maxAngleWalking; 
		m::write(movement + 0xCC, 99999999999999.f); // groundTime; 
	}

	const void set_grounded(const std::uintptr_t& movement, const float& value) const noexcept {
		m::write(movement + 0x4C, value); // <Grounded>k__BackingField
	}

	const void set_running(const std::uintptr_t& movement, const float& value) const noexcept {
		m::write(movement + 0x40, value); // <Running>k__BackingField
	}


protected:
	std::uintptr_t _addr;
};
