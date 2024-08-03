
#include "loadTexture.h"
#include "UseImgui.h"
#include <GLFW/glfw3.h>
#include "ImGuiStyles.h"


#define TITLE_FONT_SISE 45
#define DEFAULT_FONT_SIZE 21
#define SCREEN_WIDTH	1980
#define SCREEN_HEIGHT 1080
#define TIME_FONT_SIZE 18

/*globals*/

ImFont* title_font = nullptr;
ImFont* default_font = nullptr;
ImFont* time_font = nullptr;


std::vector<Item> UseImGui::filtered_items;

struct ImageData {
	GLuint textureID;
	int width;
	int height;
	std::string name;
};

std::vector<ImageData> images;



void UseImGui::Init(GLFWwindow* window, const char* glsl_version) {


	if (!window) {
		fprintf(stderr, "GLFW window is not initialized\n");
		return;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit()) {
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	io.Fonts->AddFontDefault();

	title_font = io.Fonts->AddFontFromFileTTF("C:/Users/Mihai/Desktop/ImguiProject/ImguiProject/Fonts/inter-bold.ttf", TITLE_FONT_SISE);
	default_font = io.Fonts->AddFontFromFileTTF("C:/Users/Mihai/Desktop/ImguiProject/ImguiProject/Fonts/inter.ttf", DEFAULT_FONT_SIZE);

	time_font = io.Fonts->AddFontFromFileTTF("C:/Users/Mihai/Desktop/ImguiProject/ImguiProject/Fonts/inter.ttf", TIME_FONT_SIZE);
	IM_ASSERT(title_font != NULL);



	get_ImGui_color_styles();
	get_ImGui_window_border_radius_style();
	button_styles();

	ImageData backImage;
	LoadTextureFromFile("C:/Users/Mihai/Desktop/ImguiProject/ImguiProject/icons/back.png", &backImage.textureID, &backImage.width, &backImage.height);
	backImage.name = "Back Image";
	images.push_back(backImage);

	ImageData removeImage;
	LoadTextureFromFile("C:/Users/Mihai/Desktop/ImguiProject/ImguiProject/icons/remove.png",&removeImage.textureID, &removeImage.width, &removeImage.height);
	removeImage.name = "Remove Image";
	images.push_back(removeImage);

	


}



void UseImGui::renderPriorityList()
{
	ImVec4 priority_text_color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	ImGui::PushStyleColor(ImGuiCol_Text, priority_text_color);
	ImGui::Text("Priority");
	ImGui::PopStyleColor();

	//Combo list styles
	ImVec4 combo_bg_color = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	ImVec4 arrow_color = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	ImVec4 combo_text_color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	ImVec4 arrow_hover_color = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, combo_bg_color);
	ImGui::PushStyleColor(ImGuiCol_Text, combo_text_color);
	ImGui::PushStyleColor(ImGuiCol_Button, arrow_color);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, arrow_hover_color);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7.0f, 7.0f));

	ImGui::SetNextItemWidth(200.0f);

	const char* combo_preview_value = (selectedElementIndex >= 0 && selectedElementIndex < priority_list.size()) ? priority_list[selectedElementIndex] : "Priority";
	if (ImGui::BeginCombo("##Priority", combo_preview_value)) {
		for (int i = 0; i < priority_list.size(); i++) {
			const bool is_selected = (selectedElementIndex == i);
			if (ImGui::Selectable(priority_list[i], is_selected)) {
				selectedElementIndex = i;
			}

			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(4);

}






void UseImGui::MainPage()
{


	ImGui::PushFont(title_font);
	ImGui::Text("Your To Do");

	ImGui::PopFont();
	ImGui::SameLine();

	float window_width = ImGui::GetWindowSize().x;
	float button_width = ImGui::CalcTextSize("New Task").x + ImGui::GetStyle().FramePadding.x * 2.5f;
	float button_x = window_width - button_width - ImGui::GetStyle().WindowPadding.x;

	ImGui::SetCursorPosX(button_x);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));

	if (ImGui::Button("New Task")) {
		currentState = AppState::NewTaskPage;
		
	}
	
	ImGui::PopStyleColor();


	render_entries();


}

void UseImGui::updateFilterItems() {
	// Get the list of all items
	vector<Item> item_list = manage.getItems();
	filtered_items.clear();

	// Filter items based on the current filter state
	for (const auto& item : item_list) {
		bool should_add = false;
		switch (currentFilterState) {
		case FilterState::ALL:
			should_add = true;
			break;
		case FilterState::High:
			if (item.selected_priority == "High") should_add = true;
			break;
		case FilterState::Medium:
			if (item.selected_priority == "Medium") should_add = true;
			break;
		case FilterState::Low:
			if (item.selected_priority == "Low") should_add = true;
			break;
		case FilterState::In_Progress:
			if (!item.checked) should_add = true;
			break;
		case FilterState::Completed:
			if (item.checked) should_add = true;
			break;
		}
		if (should_add) {
			filtered_items.push_back(item);
		}
	}
}



void UseImGui::NewTaskPage()
{
	GetUserInput();
	renderPriorityList();
	
	float back_img_x = 20.0f;
	float back_img_y = 40.0f;
	float window_size_y = ImGui::GetWindowSize().y;
	ImVec2 cursorPos = ImGui::GetCursorPos();
	float pos_img_y = window_size_y - back_img_y - ImGui::GetStyle().FramePadding.y - ImGui::GetStyle().ItemSpacing.y * 5.0f;
	renderImage(0,cursorPos.x,pos_img_y,back_img_x,back_img_y);
	ImGui::SetCursorPos(cursorPos);

}

void UseImGui::GetUserInput()
{
	ImGui::PushFont(title_font);
	ImGui::Text("Add New Task");
	ImGui::PopFont();

	ImGui::NewLine();

	ImVec4 description_text_color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	ImGui::PushStyleColor(ImGuiCol_Text, description_text_color);
	ImGui::Text("Description");
	ImGui::PopStyleColor();

	//Input Styles
	ImVec4 input_bg_color = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
	ImVec4 input_border_color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	ImVec4 input_text_color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, input_bg_color);
	ImGui::PushStyleColor(ImGuiCol_Border, input_border_color);
	ImGui::PushStyleColor(ImGuiCol_Text, input_text_color);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 12.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
	ImGui::SetNextItemWidth(400.0f);

	ImGui::InputText("##input", inputText, IM_ARRAYSIZE(inputText));
	
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(3);

	//Position of add button 

	ImVec2 cursor_pos = ImGui::GetCursorPos();
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(70.0f, 7.0f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
	float window_x = ImGui::GetWindowSize().x;
	float window_y = ImGui::GetWindowSize().y;
	float button_width = ImGui::CalcTextSize("Add").x + ImGui::GetStyle().FramePadding.x * 2.0f;
	float button_x = window_x - button_width - ImGui::GetStyle().WindowPadding.x;
	float button_hight = ImGui::CalcTextSize("Add").y + ImGui::GetStyle().FramePadding.y * 2.5;
	float button_y = window_y - button_hight - ImGui::GetStyle().WindowPadding.y;

	

	ImGui::SetCursorPos(ImVec2(button_x, button_y));
	bool disable_button = (selectedElementIndex == -1 || strlen(inputText) == 0);
	if (disable_button) {
		ImGui::BeginDisabled();
	}

	if (ImGui::Button("Add")) {
		if (strlen(inputText) > 0) {
			string task(inputText);
			manage.add_new_item(task);
			if (selectedElementIndex != -1) {
				printf("task %s priority %s", task.c_str(), priority_list[selectedElementIndex]);
				string priority = priority_list[selectedElementIndex];
				manage.setPriority(task, priority);
				manage.sort_items_by_priority();
			}
			clearInputText(inputText);
		}
	}

	if (disable_button) {
		ImGui::EndDisabled();
	}

	ImGui::PopStyleVar(1);
	ImGui::PopStyleColor(1);
	ImGui::SetCursorPos(cursor_pos);

}


void UseImGui::render_entries()
{
	
	float window_width = ImGui::GetWindowSize().x;
	float cursor_pos = ImGui::GetCursorPosX();
	float text_width = 0.0f;

	for (const string& entry : entries) {
		text_width += ImGui::CalcTextSize(entry.c_str()).x + ImGui::GetStyle().FramePadding.x;
	}
	float text_x = window_width - text_width * 1.2;
	ImGui::SetCursorPosX(text_x);
	ImGui::Text("");

	ImVec4 button_color = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);  
	ImVec4 button_hovered_color = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); 
	ImVec4 button_active_color = ImVec4(0.2f, 0.4f, 0.7f, 1.0f);

	ImGui::PushStyleColor(ImGuiCol_Button, button_color);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, button_hovered_color);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, button_active_color);


	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 40.0f); 
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 5.0f));
	for (size_t i = 0; i < entries.size(); ++i) {
		ImGui::SameLine();
		std::string button_id = "Button_" + std::to_string(i); // Create a unique ID for each button

		ImVec4 current_button_color = (i == selectedButtonIndex) ? ImVec4(0.5f, 0.5f, 0.5f, 1.0f) : button_color;
		ImVec4 current_button_hovered_color = (i == selectedButtonIndex) ? ImVec4(0.5f, 0.5f, 0.5f, 1.0f) : button_hovered_color;
		ImVec4 current_button_active_color = (i == selectedButtonIndex) ? ImVec4(0.8f, 0.8f, 0.8f, 1.0f) : button_active_color;

		ImGui::PushStyleColor(ImGuiCol_Button, current_button_color);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, current_button_hovered_color);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, current_button_active_color);
		
		if (ImGui::Button(entries[i].c_str())) {
			selectedButtonIndex = i;
			updateFilterState(i);
			
			
		}
		ImGui::PopStyleColor(3);
	}
	ImGui::PopStyleVar(2); 
	ImGui::PopStyleColor(3);

	updateFilterItems();

	renderUserTasks();
	
}

void UseImGui::updateFilterState(size_t buttonIndex)
{

	switch (buttonIndex) {
	case 0:
		currentFilterState = FilterState::ALL;
		break;
	case 1:
		currentFilterState = FilterState::High;
		break;
	case 2:
		currentFilterState = FilterState::Medium;
		break;
	case 3:
		currentFilterState = FilterState::Low;

		break;
	case 4:
		currentFilterState = FilterState::In_Progress;

		break;
	case 5:
		currentFilterState = FilterState::Completed;

		break;
	default:
		currentFilterState = FilterState::ALL; 
		break;
	}
}


void UseImGui::renderUserTasks()
{
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float start_y = ImGui::GetCursorPosY() + 10.0f;
	ImGui::SetCursorPosY(start_y);

	int item_to_remove = -1;
	int item_to_change_pr = -1;

	if (filtered_items.empty()) {
		ImGui::Text("There is nothing here.");
		return;
	}

	for (size_t i = 0; i < filtered_items.size(); ++i) {
		Item& item = filtered_items[i];

		ImGui::PushID(static_cast<int>(i));

		ImVec2 cursor_pos = ImGui::GetCursorPos();
		ImVec2 cursor_screen_pos = ImGui::GetCursorScreenPos();

		ImVec2 circle_pos = ImVec2(cursor_screen_pos.x + 15, cursor_screen_pos.y + ImGui::GetTextLineHeight() / 2);

		ImU32 circle_color;
		if (item.selected_priority == "Low") {
			circle_color = IM_COL32(0, 255, 0, 255);
		}
		else if (item.selected_priority == "Medium") {
			circle_color = IM_COL32(255, 255, 0, 255);
		}
		else if (item.selected_priority == "High") {
			circle_color = IM_COL32(255, 0, 0, 255);
		}
		else {
			circle_color = IM_COL32(0, 255, 0, 255);
		}

		draw_list->AddCircleFilled(circle_pos, 9.0f, circle_color);

		ImGui::InvisibleButton("circle_button", ImVec2(18.0f, 18.0f));

		if (ImGui::IsItemClicked()) {
			item_to_change_pr = static_cast<int>(i);
		}

		float image_pos_x = cursor_pos.x + 31;
		float image_pos_y = cursor_pos.y;
		float image_size = 20;
		ImGui::SetCursorPos(ImVec2(image_pos_x, image_pos_y));
		renderImage(1, image_pos_x, image_pos_y, image_size, image_size);

		if (remove_btn_pressed) {
			item_to_remove = static_cast<int>(i);
		}

		remove_btn_pressed = false;

		float checkbox_pos_x = image_pos_x + image_size + 10;
		ImGui::SetCursorPos(ImVec2(checkbox_pos_x, cursor_pos.y - 5.0f));


		bool original_checked_state = item.checked;
		if (ImGui::Checkbox(("##checkbox_" + item.name).c_str(), &item.checked)) {
			
			manage.updateItemCheckedState(item.name, item.checked);
		}

		float text_pos_x = checkbox_pos_x + ImGui::GetFrameHeight() + 10;
		ImGui::SetCursorPos(ImVec2(text_pos_x, cursor_pos.y - 10));
		ImGui::Text("%s", item.name.c_str());

		ImGui::SetCursorPos(ImVec2(text_pos_x, cursor_pos.y + ImGui::GetTextLineHeight() - 12.0f));
		ImVec4 timestamp_color = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
		ImGui::PushStyleColor(ImGuiCol_Text, timestamp_color);
		ImGui::PushFont(time_font);
		ImGui::Text("%s", item.time_posted.c_str());
		ImGui::PopFont();
		ImGui::PopStyleColor();

		cursor_pos.y += ImGui::GetTextLineHeightWithSpacing() + 20.0f;
		ImGui::SetCursorPos(cursor_pos);

		ImGui::PopID();
	}

	if (item_to_remove != -1) {
		manage.remove_item_from_list(filtered_items[item_to_remove].name);
	}
	if (item_to_change_pr != -1) {
		manage.changePriority(filtered_items[item_to_change_pr]);
	}
}


void  UseImGui::Update() {

	ImGui::SetNextWindowSize(ImVec2(1000, 650));
	ImVec2 imgui_window_pos((SCREEN_WIDTH - 1000) / 2, (SCREEN_HEIGHT - 650) / 2);
	ImGui::SetNextWindowPos(imgui_window_pos, ImGuiCond_Once);

	if (ImGui::Begin("To Do App", &is_window_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
		
		switch (currentState) {
		case AppState::MainPage:
			ImGui::PushFont(default_font);
				MainPage();
			ImGui::PopFont();
			break;
		case AppState::NewTaskPage:
			ImGui::PushFont(default_font);
				NewTaskPage();
			ImGui::PopFont();
			break;
		default:
			break;
		}
		

	}ImGui::End();

	if (!is_window_open) {
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
	}
	

}

void UseImGui::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void  UseImGui::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}




void  UseImGui::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UseImGui::clearInputText(char* text)
{
	memset(inputText, 0, sizeof(inputText));
}



void UseImGui::renderImage(int imageIndex, float posX, float posY, float width, float height) {

	ImGui::SetCursorPos(ImVec2(posX, posY));
	ImGui::Image((void*)(intptr_t)images[imageIndex].textureID, ImVec2(width, height));

	ImGui::SetCursorPos(ImVec2(posX, posY));

	if (ImGui::InvisibleButton("imageButton", ImVec2(width, height))) {
		if (imageIndex == 0) {
			printf("Image clicked: %s\n", images[imageIndex].name.c_str());
			currentState = AppState::MainPage;
		}
		else if(imageIndex == 1) {
			remove_btn_pressed = true;
		}
		
	}
	
	
}


