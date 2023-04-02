#include "hacks.h"

#include <thread>

auto FloatFromBytes = [](uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
{
	return ((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0);
};

void h::adminflags() noexcept {
	while (g::run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		for (const auto& entity : g::entity_list) {
			float localHealth = g::local_player.get_health();

			if (!localHealth) {
				continue;
			}

			int playerFlags = g::local_player.get_player_flags();

			if (!playerFlags) {
				continue;
			}

			if (v::adminFlags) {
				if (!g::verify_layer_filter(131072)) {
					g::set_layer_filter(131072);
				}

				playerFlags |= 4;
				
				g::local_player.set_player_flags(playerFlags);	
			}
		}
	}
	std::terminate();
}

void h::jumpshoot() noexcept {
	while (g::run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		for (const auto& entity : g::entity_list) {
			float localHealth = g::local_player.get_health();

			if (!localHealth) {
				continue;
			}

			auto baseMovement = g::local_player.get_base_movement();

			if (!baseMovement) {
				continue;
			}

			auto modelState = g::local_player.get_model_state();

			if (!modelState) {
				continue;
			}

			auto modelStateFlags = g::local_player.get_model_state_flags(modelState);

			modelStateFlags |= 4;

			if (v::jumpShoot) {
				g::local_player.set_grounded(baseMovement, 1.f);
				g::local_player.set_model_state_flags(modelState, modelStateFlags);
			}
		}
	}

	std::terminate();
}

void h::spiderman() noexcept {
	while (g::run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		for (const auto& entity : g::entity_list) {
			float localHealth = g::local_player.get_health();

			if (!localHealth) {
				continue;
			}

			auto baseMovement = g::local_player.get_base_movement();

			if (!baseMovement) {
				continue;
			}

			if (v::spiderMan) {
				g::local_player.set_spider_man(baseMovement);
			}

			if (v::funnyJump) {
				g::local_player.set_funny_jump(baseMovement);
			}
		}
	}

	std::terminate();
}

void h::rustfov() noexcept {
	while (g::run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		for (const auto& entity : g::entity_list) {
			float localHealth = g::local_player.get_health();

			if (!localHealth) {
				continue;
			}

			if (v::rustFovChanger && (g::get_graphics_fov() != v::rustFovSlider)) {
				g::set_graphics_fov(v::rustFovSlider);
			}
		}

	}
	std::terminate();
}

void h::fullbright() noexcept {
	while (g::run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		for (const auto& entity : g::entity_list) {
			float localHealth = g::local_player.get_health();

			if (!localHealth) {
				continue;
			}

			if (v::fullBright && (!g::verify_full_bright(4.f, 25.f))) {
				g::set_full_bright(4.f, 25.f);
			}
		}

	}
	std::terminate();
}

void h::chams() noexcept {
	while (g::run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		for (const auto& entity : g::entity_list) {
			int localHealth = g::local_player.get_health();

			if (!localHealth) {
				continue;
			}

			auto playerModel = entity.get_player_model();

			auto skinType = entity.get_skin_type(playerModel);

			std::uintptr_t playerSkinComponent = NULL;

			if (!playerSkinComponent)
				playerSkinComponent = entity.get_male_skin(playerModel);
			if (!playerSkinComponent)
				playerSkinComponent = entity.get_female_skin(playerModel);

			if (!playerSkinComponent) {
				continue;
			}

			auto skins = entity.get_skins(playerSkinComponent);

			if (!skins) {
				continue;
			}

			auto skinSize = entity.get_skins_size(skins);


			for (int i = 0; i <= skinSize; i++) {
				auto skin = entity.get_skin(skins, (i * 0x8));

				if (v::rustChams) {
					entity.set_skin_material(skin, g::sky_material());
				}
			}

			if (v::rustChams) {
				entity.set_clothes_rebuild(true);
			}
		}
	}

	std::terminate();
}

void h::rustrecoil() noexcept {
	while (g::run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		for (const auto& entity : g::entity_list) {
			float localHealth = g::local_player.get_health();

			if (!localHealth) {
				continue;
			}

			auto inventory = g::local_player.get_inventory();
			auto activeItem = g::local_player.get_active_item();

			if (!activeItem) {
				continue;
			}

			auto items = g::local_player.get_items(inventory);

			for (int i = 0; i <= 6; i++) {

				auto item = g::local_player.get_item(items, (i * 8));
				auto itemID = g::local_player.get_item_id(item);

				if (!itemID) {
					continue;
				}

				if (itemID == activeItem) {
					auto baseProjectile = g::local_player.get_base_projectile(item);


					if (!baseProjectile) {
						continue;
					}


					if (v::fullAuto) {
						if (!g::local_player.verify_full_auto(baseProjectile)) {
							g::local_player.set_full_auto(baseProjectile);
						}
					}

					if (v::instaEoka) {
						if (!g::local_player.verify_insta_eoka(baseProjectile)) {
							g::local_player.set_insta_eoka(baseProjectile);
						}
					}

					if (v::instaBow) {
						if (!g::local_player.verify_insta_bow(baseProjectile)) {
							g::local_player.set_insta_bow(baseProjectile);
						}
					}

					auto createdProjectile = g::local_player.get_created_projectile(baseProjectile);

					auto projectileList = g::local_player.get_projectile_list(createdProjectile);
					auto projectileListSize = g::local_player.get_projectile_list_size(projectileList);

					for (int i = 0; i <= projectileListSize; i++) {
						auto projectile = g::local_player.get_projectile(projectileList, (i * 0x8));

						if (!projectile) {
							continue;
						}

						if (v::thickBullet) {
							if (!g::local_player.verify_projectile_thickness(projectile, 1.5f)) {
								g::local_player.set_projectile_thickness(projectile, 1.5f);
							}
						}

						if (v::noSpread) {
							g::local_player.set_projectile_spread(projectile, 0.f);
						}
					}


					auto recoilProperties = g::local_player.get_recoil_props(baseProjectile);
					auto newRecoilProperties = g::local_player.get_new_recoil_props(recoilProperties);

					if (v::rustRecoil) {
						if (!g::local_player.verify_recoil_props(recoilProperties, 0.f)) {
							g::local_player.set_recoil_props(recoilProperties, 0.f);
						}

						if (!g::local_player.verify_recoil_props(newRecoilProperties, 0.f)) {
							g::local_player.set_recoil_props(newRecoilProperties, 0.f);
						}
					}

				}
			}
		}

	}

	std::terminate();
}
