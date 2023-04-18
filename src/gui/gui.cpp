#include "imgui.h"
#include "implot.h"

#include "gui.h"

namespace gui
{
    Configuration config;
    Simulation simulation(config);

    static ImGuiTableFlags table_flags = ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendX;

    static bool show_demo_window = true;
    static bool show_another_window = false;

    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /*
    static void drawFirstWindow();
    static void drawSecondWindow();
    static void drawThirdWindow();
    static void drawFourthWindow();
    static void drawFifthWindow();
    */
    static void drawSetup();
    static void drawSimulation();
    static void drawPlotWindow();
    static void drawStats();

    void Render_GUI()
    {
        //drawFirstWindow();
        //drawSecondWindow();
        //drawThirdWindow();
        //drawFourthWindow();
        //drawFifthWindow();
        drawSetup();
        drawStats();
        drawSimulation();
        drawPlotWindow();
    }

    static void drawSetup()
    {
        if (ImGui::Begin("Setup"))
        {
            if(ImGui::Button("Start"))
            {
                config.running = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Pause"))
            {
                config.running = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Stop"))
            {
                config.running = false;
                simulation.Restart();
            }

            ImGui::NewLine();

            ImGui::Text("Iteration time gap(ms): ");
            ImGui::SameLine();
            ImGui::SliderInt(" ", &(config.pause_milliseconds_count), 10, 1000);

            ImGui::NewLine();

            // ---------------------------------------------------------------------------------------

            ImGui::Text("Probability vehicle direction:");
            ImGui::Text("Top: ");
            ImGui::SameLine();
            ImGui::SliderFloat("  ", &(config.prob_vehicle_create_top), 0.0f, 1.0f);

            ImGui::Text("Bottom: ");
            ImGui::SameLine();
            ImGui::SliderFloat("   ", &(config.prob_vehicle_create_bottom), 0.0f, 1.0f);

            ImGui::Text("Right: ");
            ImGui::SameLine();
            ImGui::SliderFloat("    ", &(config.prob_vehicle_create_right), 0.0f, 1.0f);

            ImGui::NewLine();

            // ---------------------------------------------------------------------------------------

            ImGui::Text("Probability create vehicle:");
            ImGui::Text("Motorbike: ");
            ImGui::SameLine();
            ImGui::SliderFloat("     ", &(config.prob_motorbike), 0.0f, 1.0f);

            ImGui::Text("Car: ");
            ImGui::SameLine();
            ImGui::SliderFloat("      ", &(config.prob_car), 0.0f, 1.0f);

            ImGui::Text("Van: ");
            ImGui::SameLine();
            ImGui::SliderFloat("       ", &(config.prob_van), 0.0f, 1.0f);

            ImGui::NewLine();

            // ---------------------------------------------------------------------------------------

            ImGui::Text("Probability parking vehicle:");
            ImGui::Text("Probability park: ");
            ImGui::SameLine();
            ImGui::SliderFloat("        ", &(config.prob_park), 0.0f, 1.0f);

            ImGui::Text("Park in Jungmann street: ");
            ImGui::SameLine();
            ImGui::SliderFloat("         ", &(config.prob_park_in_jung), 0.0f, 1.0f);

            ImGui::Text("Park in Smetanova street: ");
            ImGui::SameLine();
            ImGui::SliderFloat("           ", &(config.prob_park_in_smet), 0.0f, 1.0f);

            ImGui::NewLine();

            // ---------------------------------------------------------------------------------------

            ImGui::Text("Minimum park time: ");
            ImGui::SameLine();
            ImGui::SliderInt("            ", &(config.min_iteration_for_park), 10, 99);

            ImGui::Text("Maximum park time: ");
            ImGui::SameLine();
            ImGui::SliderInt("             ", &(config.max_iteration_for_park), 100, 1000);

        }

        ImGui::End();
    }

    static void drawPlotWindow()
    {
        if (ImGui::Begin("Plots"))
        {
            if (ImPlot::BeginPlot("Statistics:"))
            {
                ImPlot::PlotLine("Vehicle count", config.iteration_array.data(), config.amount_of_vehicles.data(), (int)config.iteration_array.size());
                ImPlot::PlotLine("Vans count", config.iteration_array.data(), config.amount_of_vans.data(), (int)config.iteration_array.size());
                ImPlot::PlotLine("Cars count", config.iteration_array.data(), config.amount_of_cars.data(), (int)config.iteration_array.size());
                ImPlot::PlotLine("Motorbike count", config.iteration_array.data(), config.amount_of_motorbikes.data(), (int)config.iteration_array.size());
                ImPlot::EndPlot();
            }
        }

        ImGui::End();
    }

    static void drawStats()
    {
        if (ImGui::Begin("Stats")) {
            ImGui::Text("Vehicle type parked succesfully: %d", config.vehicle_parked);
            ImGui::Text("Vans parked: %d", config.vans_parked);
            ImGui::Text("Cars parked: %d", config.cars_parked);
            ImGui::Text("Motorbikes parked: %d", config.motorbike_parked);

            ImGui::Text("Vehicle park attempts:");
            ImGui::Text("1. attempt: %d", config.park_attempt_stats[0]);
            ImGui::Text("2. attempt: %d", config.park_attempt_stats[1]);
            ImGui::Text("3. attempt: %d", config.park_attempt_stats[2]);
            ImGui::Text("4. attempt: %d", config.park_attempt_stats[3]);
            ImGui::Text("5. attempt: %d", config.park_attempt_stats[4]);
            ImGui::Text("6. attempt: %d", config.park_attempt_stats[5]);
            ImGui::Text("7. attempt: %d", config.park_attempt_stats[6]);
            ImGui::Text("8. attempt: %d", config.park_attempt_stats[7]);
            ImGui::Text("9. attempt: %d", config.park_attempt_stats[8]);
            ImGui::Text("10. attempt: %d", config.park_attempt_stats[9]);

            ImGui::Text("Vehicle type cant parked: %d", config.vehicle_not_parked);
            ImGui::Text("Vans: %d", config.vans_not_parked);
            ImGui::Text("Cars: %d", config.cars_not_parked);
            ImGui::Text("Motorbikes: %d", config.motorbike_not_parked);
            ImGui::NewLine();
        }
        ImGui::End();
    }
/*
    static void drawFirstWindow()
    {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
    }

    static void drawSecondWindow()
    {
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.
        ImGui::Text("This is some useful text.");   // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);  // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);    // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color);     // Edit 3 floats representing a color

        if (ImGui::Button("Button"))
        {                                                       // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        }

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    static void drawThirdWindow()
    {
        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
            {
                show_another_window = false;
            }
            ImGui::End();
        }
    }

    static void drawFourthWindow()
    {
        static std::default_random_engine randomEngine(time(nullptr));
        static std::uniform_real_distribution<double> distribution(std::numeric_limits<double>::min(),
                                                                   std::numeric_limits<double>::max());

        static std::vector<double> data;
        
        for (int i = 0; i < 10; i++)
        {
            data.emplace_back(distribution(randomEngine));
        }

        //ImGui::Begin("My Window");
        //if (ImPlot::BeginPlot("My Plot"))
        //{
        //    ImPlot::PlotBars("My Bar Plot", &data[0], data.size());
        //    ImPlot::EndPlot();
        //}
        ImGui::End();
    }

    static void drawFifthWindow()
    {
        //ImPlot::ShowDemoWindow();
    }
    */
    static void drawSimulation()
    {
        if (config.running) {
            simulation.Update();
        }
        ImGui::Begin("Simulation grid");
        int map_width = simulation.Get_Map().Get_Map_Width();
        int map_height = simulation.Get_Map().Get_Map_Height();


        if (ImGui::BeginTable("map_grid", map_width, table_flags))
        {
            for (int i = 0; i < map_width; ++i) {
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, cell_size);
            }
            for (int row = 0; row < map_height; row++) {
                ImGui::TableNextRow(table_flags, cell_size);
                for (int column = 0; column < map_width; column++) {
                    Map::NCell_Type cell_type = simulation.Get_Map().Get_Cell_Type(row, column);
                    ImGui::TableSetColumnIndex(column);
                    //ImGui::Text("%d%d", row + 1, column);
                    ImGui::Text("");
                    ImU32 cell_bg_color = ImGui::GetColorU32(Get_Cell_Color(cell_type));
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
                }
            }
            ImGui::EndTable();
        }
        ImGui::End();
    }

    ImVec4 Get_Cell_Color(Map::NCell_Type cell_type)
    {
        ImVec4 color;
        switch (cell_type) {
            case Map::NCell_Type::V:
                color = ImVec4(0.0, 0.0, 1.0, 1.0);
                break;
            case Map::NCell_Type::R:
                color = ImVec4(0.3, 0.3, 0.3, 1.0);
                break;
            case Map::NCell_Type::B:
                color = ImVec4(1.0, 1.0, 0.0, 1.0);
                break;
            case Map::NCell_Type::S:
                color = ImVec4(0.0, 0.0, 0.0, 1.0);
                break;
            case Map::NCell_Type::S_R:
                color = ImVec4(1.0, 0.0, 0.0, 1.0);
                break;
            case Map::NCell_Type::S_G:
                color = ImVec4(0.0, 1.0, 0.0, 1.0);
                break;
            case Map::NCell_Type::P_F:
                color = ImVec4(0.3, 0.5, 1.0, 1.0);
                break;
            case Map::NCell_Type::P_O:
                color = ImVec4(0.1, 0.1, 0.9, 1.0);
                break;
            case Map::NCell_Type::G:
                color = ImVec4(0.0, 0.6, 0.0, 1.0);
                break;
            case Map::NCell_Type::W:
                color = ImVec4(0.75, 0.75, 0.75, 1.0);
                break;
            default:
                color = ImVec4(1.0, 1.0, 1.0, 1.0);
        }
        return color;
    }
}