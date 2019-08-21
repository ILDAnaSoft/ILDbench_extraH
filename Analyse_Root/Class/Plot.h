#pragma once
#ifndef GLOBAL_PARA_PLOT_H
#define GLOBAL_PARA_PLOT_H
#include "TStyle.h"
#include <string> 
#include <vector>
#include "yaml-cpp/yaml.h"

#include "Function/Fbasic.h"
#include "RWpara/RWbasic.h"
#include "Class/Path.h"
#include "Lib/MessageFormat.h"

class CColor{
	private:
		int  _max_color_num   ;
		int  _color; 
	protected:
		std::vector<int>      _colornum;
		void _Init_Color();
	public:
		int _auto_color_num ;
		bool user_color;

		CColor();

		int Color();

		int Origin_Color();

		int Last_Color();

		void Get_Color(int input);

		int Auto_Color_Num(){
			return(_auto_color_num);
		}

};

class CStyle{
	private:
		int  _max_style_num   ;
		int  _style; 
	protected:
		std::vector<int>      _stylenum;
		void _Init_Style();
	public:
		bool user_style;

		CStyle();

		int Style();

		void Get_Style(int input);
};



class CWidth{
	private:
		int  _width; 
	public:
		bool user_width;

		CWidth();

		int Width();

		void Get_Width(int width);
};

class CPosition{
	private:
	public:
		float         left   ;
		float         up     ;
		float         right  ;
		float         down   ;

		CPosition(){
		    left     = 0.6   ;
		    up       = 0.6   ;
		    right    = 0.9   ;
		    down     = 0.9   ;
		}
};

class Cplot_basic_color_style: public CColor, public CStyle, public CWidth{
	public:
		//stack
		bool user_basic_color_style;

		Cplot_basic_color_style(){
			user_basic_color_style = false;
		}

		void Print();

};

std::ostream & operator<< (std::ostream & ostr, Cplot_basic_color_style str);



class Cplot_line{
	public:
		//stack
		bool include;
		bool fill_switch;
		bool norm_switch;

        Cplot_basic_color_style line_setting;
		CColor                  fill_color  ;

		Cplot_line(){
			include = true;
			fill_switch= false;
		    norm_switch= false;
		}

		void Get_Color(int i){
			fill_color.Get_Color(i);
			line_setting.Get_Color(i);
		}

		void Print();

};


std::ostream & operator<< (std::ostream & ostr, Cplot_line str);


class Cplot_stack{
	public:
		//stack
		std::string draw_option; 

		Cplot_stack(){
		    draw_option = "Hist, nostack"; 
		}

		void Print();
};


class Cplot_legend{
	public:
		//stack
		std::string header; 


		CPosition   pos;

		Cplot_legend(){
			header = "";
		}

		void Print();
};


class Cplot_setting{
	public:
		//stack
		bool show_title;

		//line
		int  line_width; 
		int  with_color_or_line; 

		Cplot_basic_color_style line_setting;

		Cplot_setting(){
			show_title = false;
		}
};


class Cplot_drawing{
	public:
		std::string plot_type;
		std::vector<std::string> single_plot;
		std::vector<std::string> class_plot;
		Cplot_drawing(){
			plot_type = ".png";
		}
};


class Cplot_canvas{
	public:
		Int_t border_mode;
		Int_t border_size;
		Int_t color;
		Int_t height;
		Int_t width;
		Int_t Xpos;
		Int_t Ypos;
};


class Cplot_rootset{
	public:
		Cplot_canvas canvas;
};

class CPlot{
	private:
	public:
		Cplot_setting  setting;
		Cplot_drawing  drawing;
		Cplot_rootset  rootset;
		void Read_Plot(CPath &path);
};

#include "Class/Plot.hpp"
#endif