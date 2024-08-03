#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>
#include "ManageItems.h"




using namespace std;


enum class AppState {
	MainPage,
	NewTaskPage
};

enum class FilterState {
	ALL = 0,
	High = 1,
	Medium = 2,
	Low = 3,
	In_Progress = 4,
	Completed = 5
};

class UseImGui {

private:

	char inputText[128];
	size_t selectedButtonIndex = 0;
	bool is_window_open = true;
	bool remove_btn_pressed = false;
	int selectedElementIndex = -1;
	vector<string> entries = { "ALL","HIGH","MEDIUM","LOW","IN PROGRESS","COMPLETED" };
	vector<const char*>priority_list = {"Low","Medium","High"};
	ManageItems manage;
	AppState currentState = AppState::MainPage;
	FilterState currentFilterState = FilterState::ALL;
	


	void MainPage();
	void render_entries();
	void NewTaskPage();

	void GetUserInput();
	void renderPriorityList();
	
	

public:
	UseImGui() {
		memset(inputText, 0, sizeof(inputText));
	}

	static std::vector<Item> filtered_items;

	void Init(GLFWwindow* window,const char* glsl_version);
	void Update();
	void NewFrame();
	void Render();
	void Shutdown();
	void clearInputText(char* text);
	void renderImage(int imageIndex, float posX, float posY,float width, float height);
	void updateFilterState(size_t buttonIndex);
	void updateFilterItems();
	void renderUserTasks();

};
