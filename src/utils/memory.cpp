#include "memory.h"

#include <TlHelp32.h>
#include <memory>

void m::call_hook(void* info_struct)
{
	void* hooked_fn = GetProcAddress(GetModuleHandleA("win32u.dll"), "NtGdiDdDDIUpdateGpuVirtualAddress");
	auto fn = static_cast<void(_stdcall*)(void*)>(hooked_fn);
	return fn(info_struct);
}

struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

void m::process_id(const std::string name) noexcept {

	PROCESSENTRY32 processentry;

	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
	{
		if (name.compare(processentry.szExeFile) == NULL)
		{
			id = processentry.th32ProcessID;
		}
	}
}

std::uintptr_t m::module_address(const char* name) noexcept {
	NULL_MEMORY instructions = { 0 };
	instructions.pid = id;
	instructions.req_base = TRUE;
	instructions.read = FALSE;
	instructions.write = FALSE;
	instructions.module_name = name;
	call_hook(&instructions);

	ULONG64 base = NULL;
	base = instructions.base_address;
	return base;
}


bool m::draw_box(int x, int y, int w, int h, int t, int r, int g, int b) noexcept
{
	NULL_MEMORY instructions;
	instructions.draw_box = TRUE;
	instructions.read = FALSE;
	instructions.write = FALSE;
	instructions.req_base = FALSE;

	instructions.x = x;
	instructions.y = y;
	instructions.w = w;
	instructions.h = h;
	instructions.t = t;

	instructions.r = r;
	instructions.g = g;
	instructions.b = b;

	call_hook(&instructions);

	return true;
}

bool m::open_handle() noexcept {
	return m::handle = OpenProcess(PROCESS_ALL_ACCESS, 0, m::id);
}

void m::close_handle() noexcept {
	if (m::handle) {
		CloseHandle(m::handle);
	}
}
