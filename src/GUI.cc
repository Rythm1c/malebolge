/* #include "../headers/GUI.h"
#include "../headers/assets.h"
#include "../headers/engine.h"
#include "../headers/window.h"
#include "../headers/world.h"
#include "../shapes/shape.h"

GUI::GUI(World *_w)
    : P_world(_w), pos(Vector3f(0.0)), color(Color3f(1.0)), rotation(Vector3f(0.0)),
      size(Vector3f(0.0)), velocity(Vector3f(0.0)), renderObj(false), choosenObj("") {}

void GUI::processevents(SDL_Event &event)
{
  ImGui_ImplSDL2_ProcessEvent(&event);
}

void GUI::load()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  this->io = &ImGui::GetIO();
  (void)this->io;
  this->io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
  this->io->Fonts->AddFontFromFileTTF("fonts/roboto/Roboto-Regular.ttf", 15.0);

  ImGui::StyleColorsDark();

  auto &style = ImGui::GetStyle();
  style.TabRounding = 2;
  style.ScrollbarRounding = 4;
  style.WindowRounding = 4;
  style.GrabRounding = 2;
  style.FrameRounding = 2;
  style.PopupRounding = 2;
  style.ChildRounding = 2;

  ImGui_ImplSDL2_InitForOpenGL(Engine::getInstance()->P_window->win,
                               Engine::getInstance()->P_window->context);
  ImGui_ImplOpenGL3_Init();
}
void GUI::overlay()
{
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
      ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
      ImGuiWindowFlags_NoNav;
  ImGui::Begin("overlay", (bool *)true, window_flags);
  ImGui::Text("fps: %.1f", Engine::getInstance()->fps);
  ImGui::End();
}
// select between different objects
// very primitve and simple at the moment
// TODO: improve model loading code and add more factionality
void GUI::editObject()
{

  static int objIndex = 0;

  ImGui::Begin("edit model");
  ImGui::Text("objects:");

  ImGui::Separator();
  ImGui::Checkbox("render", &renderObj);
  ImGui::Separator();
  // for editting model scale
  ImGui::Text("scale");
  ImGui::InputFloat3("##scale", this->size.v.data(), "%.1f");
  // edit model position
  ImGui::Separator();
  ImGui::Text("position");
  ImGui::InputFloat3("##pos", this->pos.v.data(), "%.1f");
  // model rotation
  ImGui::Separator();
  ImGui::Text("rotation:");
  ImGui::SliderFloat("X", &this->rotation.x, 0.0, 360.0, "%.1f");
  ImGui::SliderFloat("Y", &this->rotation.y, 0.0, 360.0, "%.1f");
  ImGui::SliderFloat("Z", &this->rotation.z, 0.0, 360.0, "%.1f");
  // model velocity
  ImGui::Text("velocity: %f   %f   %f", velocity.x, velocity.y, velocity.z);

  // chnage model color
  ImGui::Separator();
  ImGui::Text("color picker");
  ImGui::ColorPicker3("##colorpicker", this->color.v.data());
  ImGui::End();
}

void GUI::effects()
{
  ImGui::Begin("effects");
  ImGui::Checkbox("pause", &P_world->pause);
  ImGui::End();
}
void GUI::update()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  overlay();
  editObject();
  effects();
}
void GUI::render() const
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void GUI::clean() const
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}
 */