#include "globals.h"

void g::entities() noexcept {
	entity_list.reserve(object_list_size());

	while (run) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// clear ent list when not in-game
		if (object_list() == 0) {
			entity_list.clear();
			continue;
		}

		// populate entity list
		for (int i = 0; i <= object_list_size(); ++i) {

			std::uintptr_t element = m::read<std::uintptr_t>(object_list() + (0x20 + (i * 0x8)));

			if (!element) {
				continue;
			}

			// 0x28 is the "BasePlayer" Class
			const auto entity = c_entity{ object_unk(element) + 0x28 };

			if (!entity.is_valid()) {
				continue;
			}

			const auto result = std::find_if(
				entity_list.begin(),
				entity_list.end(),
				[&entity](const c_entity& ent) noexcept -> bool {
					return ent == entity; 
				}
			);

			// if it is already in the list
			if (result != std::end(g::entity_list)) {
				continue;
			}

			if (entity.is_local_player(entity.get_player_model())) {
				g::local_player.set_address(object_unk(element) + 0x28);
			}

			entity_list.emplace_back(entity);
		}
	}
}

