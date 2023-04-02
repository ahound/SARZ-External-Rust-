#include "Main.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <winbase.h>
#include <tchar.h>
#include <WinInet.h>
#include "../ext/keyauth/auth.hpp"
#include "globals.h"
#include "memory.h"
#include "../xorstr.hpp"
#include "../src/hacks/hacks.h"
#pragma comment(lib, "Urlmon.lib") //urlmon library for the URL Open Blocking Stream function
#pragma comment(lib,"Wininet.lib")
#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 2660)
#pragma warning(disable : 4996)
#define _WIN32_WINNT 0x0500
 
using namespace std;

using namespace KeyAuth;

std::string name = xorstr_("LSD"); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = xorstr_("2hHuDUa4cU"); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = xorstr_("96155315c9105d6a0da798299a1ebd7d016e97c685c305e261ab3910c0f9e911"); // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.1/"; // change if you're self-hosting
std::string sslPin = "ssl pin key (optional)";

api KeyAuthApp(name, ownerid, secret, version, url, sslPin);

void HelpMarker(const char* desc)
{
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}


const int dialog(const std::string& text) noexcept {
    MessageBeep(MB_ICONERROR);
    return MessageBox(
        NULL,
        text.c_str(),
        "Externalia",
        MB_ICONERROR | MB_OK
    );
}

std::string RandomString(const size_t length)
{
    std::string r;
    static const char bet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYabcdefghijklmnopqrstuvwxyzZ1234567890" };
    srand((unsigned)time(NULL) * 5);
    for (int i = 0; i < length; ++i)
        r += bet[rand() % (sizeof(bet) - 1)];
    return r;
}

bool DoesFileExist(const char* name) {
    if (FILE* file = fopen(name, "r")) {
        fclose(file);
        return true;
    }

    return false;
}

int __stdcall WinMain(
    const HINSTANCE instance,
    const HINSTANCE prev_instance,
    const LPSTR args,
    const int cmd_show
) {

    bool poo = false;
    if (poo == true)
    {
        FILE* pFile = nullptr;

        AllocConsole();
        freopen_s(&pFile, "CONOUT$", "w", stdout);
        freopen_s(&pFile, "CONIN$", "r", stdin);

        SetConsoleTitle(RandomString(25).c_str());
        std::cout << xorstr_("Connecting..\n");

        KeyAuthApp.init();

        if (!KeyAuthApp.data.success)
            return dialog("Failed to connect to Cloud");

        std::string key;

        std::cout << xorstr_("Enter license : ");
        std::cin >> key;

        KeyAuthApp.license(key);

        if (!KeyAuthApp.data.success)
            return dialog("Failed to verify Key");

        std::cout << xorstr_("\nIP address : \n") << KeyAuthApp.data.ip;
        std::cout << xorstr_("\nHardware-Id : \n") << KeyAuthApp.data.hwid;
        std::cout << xorstr_("\nSubscription expiry : \n") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.expiry)));

        Sleep(2000);
    }

    m::process_id(xorstr_("RustClient.exe"));

    if (!m::id)
        return dialog("Failed to find Rust");

    m::game = m::module_address(xorstr_("GameAssembly.dll"));

    if (!m::game)
        return dialog("Failed to find get module");

    std::thread(&g::entities).detach();
    std::thread(&h::adminflags).detach();
    std::thread(&h::spiderman).detach();
    std::thread(&h::rustfov).detach();
    std::thread(&h::fullbright).detach();
    std::thread(&h::rustrecoil).detach();

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, LOADER_BRAND, NULL };
    RegisterClassEx(&wc);
    main_hwnd = CreateWindow(wc.lpszClassName, LOADER_BRAND, WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);


    if (!CreateDeviceD3D(main_hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return dialog("Failed to create device");
    }


    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImVec4 keyColorB = ImColor(255, 0, 0, 255);
    ImVec4 keyColorG = ImColor(0, 255, 0, 255);

    ImFont* font1{};
    ImFont* font2{};

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        void Theme(); {



            auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
            {
                return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0);
            };

            auto& style = ImGui::GetStyle();
            ImVec4* colors = style.Colors;

            const ImVec4 bgColor = ColorFromBytes(41, 43, 47);
            const ImVec4 titleColor = ColorFromBytes(32, 34, 37);
            const ImVec4 lightBgColor = ColorFromBytes(82, 82, 85);
            const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 95);

            const ImVec4 panelColor = ColorFromBytes(32, 34, 37);
            const ImVec4 panelHoverColor = ColorFromBytes(29, 151, 236);
            const ImVec4 panelActiveColor = ColorFromBytes(0, 119, 200);

            const ImVec4 textColor = ColorFromBytes(255, 255, 255);
            const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
            const ImVec4 borderColor = ColorFromBytes(78, 78, 78);

            colors[ImGuiCol_Text] = textColor;
            colors[ImGuiCol_TextDisabled] = textDisabledColor;
            colors[ImGuiCol_TextSelectedBg] = panelActiveColor;
            colors[ImGuiCol_WindowBg] = bgColor;
            colors[ImGuiCol_ChildBg] = bgColor;
            colors[ImGuiCol_PopupBg] = bgColor;
            colors[ImGuiCol_Border] = borderColor;
            colors[ImGuiCol_BorderShadow] = borderColor;
            colors[ImGuiCol_FrameBg] = panelColor;
            colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
            colors[ImGuiCol_FrameBgActive] = panelActiveColor;
            colors[ImGuiCol_TitleBg] = titleColor;
            colors[ImGuiCol_TitleBgActive] = titleColor;
            colors[ImGuiCol_TitleBgCollapsed] = titleColor;
            colors[ImGuiCol_MenuBarBg] = panelColor;
            colors[ImGuiCol_ScrollbarBg] = panelColor;
            colors[ImGuiCol_ScrollbarGrab] = lightBgColor;
            colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
            colors[ImGuiCol_ScrollbarGrabActive] = veryLightBgColor;
            colors[ImGuiCol_CheckMark] = panelActiveColor;
            colors[ImGuiCol_SliderGrab] = panelHoverColor;
            colors[ImGuiCol_SliderGrabActive] = panelActiveColor;
            colors[ImGuiCol_Button] = panelColor;
            colors[ImGuiCol_ButtonHovered] = panelHoverColor;
            colors[ImGuiCol_ButtonActive] = panelHoverColor;
            colors[ImGuiCol_Header] = panelColor;
            colors[ImGuiCol_HeaderHovered] = panelHoverColor;
            colors[ImGuiCol_HeaderActive] = panelActiveColor;
            colors[ImGuiCol_Separator] = borderColor;
            colors[ImGuiCol_SeparatorHovered] = borderColor;
            colors[ImGuiCol_SeparatorActive] = borderColor;
            colors[ImGuiCol_ResizeGrip] = bgColor;
            colors[ImGuiCol_ResizeGripHovered] = panelColor;
            colors[ImGuiCol_ResizeGripActive] = lightBgColor;
            colors[ImGuiCol_PlotLines] = panelActiveColor;
            colors[ImGuiCol_PlotLinesHovered] = panelHoverColor;
            colors[ImGuiCol_PlotHistogram] = panelActiveColor;
            colors[ImGuiCol_PlotHistogramHovered] = panelHoverColor;
            colors[ImGuiCol_DragDropTarget] = bgColor;
            colors[ImGuiCol_NavHighlight] = bgColor;
            colors[ImGuiCol_Tab] = bgColor;
            colors[ImGuiCol_TabActive] = panelActiveColor;
            colors[ImGuiCol_TabUnfocused] = bgColor;
            colors[ImGuiCol_TabUnfocusedActive] = panelActiveColor;
            colors[ImGuiCol_TabHovered] = panelHoverColor;

            style.WindowPadding = { 15, 15 };
            style.WindowRounding = 1.f;
            style.WindowTitleAlign = { 0.5f, 0.5f };
            style.WindowBorderSize = 0;

            style.FrameRounding = 0.f;
            style.FramePadding = { 20, 7 };
            style.FrameBorderSize = 1;

            font1 = io.Fonts->AddFontFromFileTTF(xorstr_("C:\\Ruda-Bold.ttf"), 15.0f);
            font2 = io.Fonts->AddFontFromFileTTF(xorstr_("C:\\legacyfont.ttf"), 18.0f);

        }
    }


    ImGui_ImplWin32_Init(main_hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto x = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
    auto y = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {

        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        std::string keyAuthKey;



        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            if (m::game) {
                ImGuiStyle* style = &ImGui::GetStyle();

                ImGui::SetNextWindowSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
                ImGui::Begin(LOADER_BRAND, &loader_active,
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoSavedSettings);

                static auto current_tab = 0;

                ImGui::PushFont(font2);
                const auto tabSize = ImVec2(74, 40);
                if (ImGui::Button("a", { tabSize })) { current_tab = 0; }
                ImGui::SameLine();
                if (ImGui::Button("b", { tabSize })) { current_tab = 1; }
                ImGui::SameLine();
                if (ImGui::Button("f", { tabSize })) { current_tab = 2; }
                ImGui::SameLine();
                if (ImGui::Button("d", { tabSize })) { current_tab = 3; }
                ImGui::PopFont();

                if (ImGui::BeginChild(
                    1,
                    ImGui::GetContentRegionAvail(),
                    true)) {

                    const auto avail = ImGui::GetContentRegionAvail();
                    const auto offset = 195.f;

                    ImGui::PushFont(font1);

                    switch (current_tab) {
                    case 0:
                        ImGui::BeginGroup();
                        ImGui::BeginChild(1, { (avail.x - 4) * 0.51f, avail.y / 2 }, true);
                        ImGui::Text("Weapons:");
                        HelpMarker("Modify base features of your gun.");
                        ImGui::Separator();

                        ImGui::Checkbox("No Recoil", &v::rustRecoil);
                        HelpMarker("Nullify the yaw and pitch of weapon recoil.");
                        ImGui::Checkbox("Full Auto", &v::fullAuto);
                        HelpMarker("Forcefully make your weapon fire full automatic.");
                        ImGui::Checkbox("Insta Eoka", &v::instaEoka);
                        HelpMarker("Shoot your eoka with only 1 tap.");
                        ImGui::Checkbox("Insta Bow", &v::instaBow);
                        HelpMarker("Instantly shoot your bow. (Sometimes works)");
                        ImGui::Checkbox("Thick Bullet", &v::thickBullet);
                        HelpMarker("Increase the 'hitbox' of players.");
                        ImGui::Checkbox("No Spread", &v::noSpread);
                        HelpMarker("Nullify the spread of projectiles (Dominant on Shotgunts)");
                        ImGui::EndChild();

                        ImGui::SameLine();

                        ImGui::BeginChild(2, { (avail.x - 4) * 0.5f, avail.y / 2 }, true);
                        ImGui::Text("BaseMovement:");
                        HelpMarker("Modify movement of your character.");
                        ImGui::Separator();


                        ImGui::Checkbox("Omnisprint", &v::omniSprint);
                        HelpMarker("Allow the ability to run sideways.");
                        ImGui::Checkbox("Jump Shoot", &v::jumpShoot);
                        HelpMarker("Allow the ability to jump while shooting.");
                        ImGui::Checkbox("Spiderman", &v::spiderMan);
                        HelpMarker("Allow the ability to mitigate fall damage & climb walls.");
                        ImGui::Checkbox("Funny Jump", &v::funnyJump);
                        HelpMarker("Glide and Take no Jump Penalties.");

                        ImGui::EndChild();
                        ImGui::BeginChild(3, { (avail.x - 4) * 0.5f, avail.y / 2 }, true);
                        ImGui::Text("Graphics:");
                        HelpMarker("Modify the graphics of your game.");
                        ImGui::Separator();

                        ImGui::Checkbox("Full Bright", &v::fullBright);
                        HelpMarker("Make night time brighter than day.");
                        ImGui::Checkbox("FOV Changer", &v::rustFovChanger);
                        HelpMarker("Change your FOV past the maximum limit (90)");
                        ImGui::SliderFloat("FOV:", &v::rustFovSlider, 0.f, 200.f);
                        ImGui::EndChild();

                        ImGui::SameLine();

                        ImGui::BeginChild(4, { (avail.x - 4) * 0.5f, avail.y / 2 }, true);
                        ImGui::Text("Misc:");
                        HelpMarker("Modify base features of your player.");
                        ImGui::Separator();
                        ImGui::Checkbox("Admin Flags", &v::adminFlags);
                        HelpMarker("Allow the ability to use admin commands. (ESP, Admintime, Debug etc.)");
                        ImGui::EndChild();
                        ImGui::EndGroup();

                        break;

                    case 1:
                        break;

                    case 2:
       
                        break;

                    case 3:
                        ImGui::BeginChild(1, { (avail.x - 4) * 0.8f, avail.y * 0.4f }, true);
                        for (const auto& entity : g::entity_list) {
                            ImGui::Text("Found BasePlayer : 0x%X", entity);
                        }
                        ImGui::EndChild();
                        ImGui::Text("GameAssembly : 0x%X", m::game);
                        ImGui::Text("LocalPlayer : 0x%X", g::local_player);
                        ImGui::Text("TOD Sky : 0x%X", g::tod_sky());
                        ImGui::Text("Occlussion Settings : 0x%X", g::occlusion_settings());
                        ImGui::Text("Graphics Instance : 0x%X", g::graphics_instance());
                        ImGui::Text("Sky Material : 0x%X", g::sky_material());
                        break;
                    }

                    ImGui::EndChild();
                }
            }

            ImGui::PopFont();
            ImGui::End();
        }

        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }


        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);


        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!loader_active) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 666;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

