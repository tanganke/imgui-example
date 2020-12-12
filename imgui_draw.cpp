#include "imgui_draw.h"

#include <implot/implot.h>

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <climits>
#include <string>
#include <vector>

extern double prev_frame_time, current_frame_time;


void imgui_init()
{
    ImGui::GetIO().IniFilename = "imgui.ini";
    ImGui::StyleColorsLight();
}

void imgui_draw()
{
    static bool implot_window_open = true;
    static float x_data[100];
    static float y1_data[100];
    static float y2_data[100];
    for (int i = 0; i < 100; i++)
    {
        x_data[i] = glfwGetTime() + i / 20.0f;
        y1_data[i] = sinf(x_data[i]);
        y2_data[i] = cosf(y1_data[i]);
    }

    if (implot_window_open)
    {
        ImGui::SetNextWindowSizeConstraints({500.0f, 500.0f}, {INFINITY, INFINITY});
        ImGui::Begin("ImPlot Window", &implot_window_open);
        {
            ImGui::Text("FPS: %lf", 1.0 / (current_frame_time - prev_frame_time));

            // plot
            ImPlot::SetNextPlotLimitsX(x_data[0], x_data[99], ImGuiCond_Always);
            ImPlot::SetNextPlotLimitsY(-1, 1, ImGuiCond_Appearing);
            if (ImPlot::BeginPlot("implot", "x", "y", ImVec2(-1, 0)))
            {
                ImPlot::PlotLine("y1", x_data, y1_data, 100);
                ImPlot::PlotStems("y2", x_data, y2_data, 100);
                ImPlot::EndPlot();
            }
            
            ImPlot::SetNextPlotLimits(0,1,0,1,ImGuiCond_Always);
            if(ImPlot::BeginPlot("heatmap" ,NULL,NULL,ImVec2(-1,0),ImPlotFlags_NoLegend,ImPlotAxisFlags_NoTickLabels,ImPlotAxisFlags_NoTickLabels))
            {
                ImPlot::PlotHeatmap("y1",y1_data,10,10,-1.0,1.0);
                ImPlot::EndPlot();
            }
        }
        ImGui::End();
    }
}