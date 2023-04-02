#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <string>

typedef struct _NULL_MEMORY
{
	void* buffer_address;
	UINT_PTR address;
	ULONGLONG size;
	ULONG pid;
	BOOLEAN write;
	BOOLEAN read;
	BOOLEAN allocate;
	BOOLEAN free;
	BOOLEAN req_base;
	BOOLEAN draw_box;
	BOOLEAN draw_fbox;
	void* output;
	const char* module_name;
	ULONG64 base_address;
	int		r, g, b, x, y, w, h, t;
}NULL_MEMORY;

// memory
namespace m {
	inline int id = 0;
	inline void* handle = nullptr;

	// RUST MODULES
	inline std::uintptr_t game = 0;
	inline std::uintptr_t unity = 0;

	// APEX MODULES
	inline std::uintptr_t r5base = 0;

	// R6S MODULES
	inline std::uintptr_t r6base = 0;

	void call_hook(void* info_struct);

	// get process id from process name
	void process_id(const std::string name) noexcept;

	// get module base addr from module name
	std::uintptr_t module_address(const char* name) noexcept;

	// draw box using matrix
	bool draw_box(int x, int y, int w, int h, int t, int r, int g, int b) noexcept;

	// proc handle stuff
	bool open_handle() noexcept;
	void close_handle() noexcept;

	// rpm wrapper
	template <typename T>
	constexpr T read(const std::uintptr_t& addr) noexcept {
		T response{};
		NULL_MEMORY instructions;
		instructions.pid = id;
		instructions.size = sizeof(T);
		instructions.address = addr;
		instructions.read = TRUE;
		instructions.write = FALSE;
		instructions.req_base = FALSE;
		instructions.output = &response;
		call_hook(&instructions);

		return response;
	}

	template <typename T>
	constexpr T allocate(const T& size_ptr) noexcept {
		PVOID response{};
		NULL_MEMORY instructions;
		instructions.pid = id;
		instructions.size = sizeof(size_ptr);
		instructions.allocate = TRUE;
		instructions.read = FALSE;
		instructions.write = FALSE;
		instructions.req_base = FALSE;
		instructions.draw_box = FALSE;
		instructions.draw_fbox = FALSE;
		instructions.output = &response;

		call_hook(&instructions);

		return response;
	}

	// wpm wrapper
	static bool write_memory(const std::uintptr_t& write_address, const std::uintptr_t& source_address, const SIZE_T& write_size) noexcept {
		NULL_MEMORY instructions;
		instructions.address = write_address;
		instructions.pid = id;
		instructions.write = TRUE;
		instructions.read = FALSE;
		instructions.req_base = FALSE;
		instructions.draw_box = FALSE;
		instructions.draw_fbox = FALSE;
		instructions.buffer_address = (void*)source_address;
		instructions.size = write_size;

		call_hook(&instructions);

		return true;
	}

	template<typename S>
	static bool write(const std::uintptr_t& write_address, const S& value) noexcept {
		return m::write_memory(write_address, (UINT_PTR)&value, sizeof(S));
	}
}

