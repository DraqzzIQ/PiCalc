#pragma once
#include "calculator/Equation.h"
#include "constant/Error.h"
#include "constant/Graphics.h"
// #include "datastructs/Number.h"
#include "windows/Window.h"
#include <iostream>

class CalculatorWindow: public Window
{
	public:
	CalculatorWindow();
	~CalculatorWindow();
	void update_window() override;
	bool handle_key_down(KeyPress keypress) override;

	private:
	enum class Menu {
		None,
		Error,
		Mode,
		Mode_Stat,
		Mode_Dist,
		Setup_Pg1,
		Setup_Pg2,
		Setup_Input,
		Setup_Output,
		Setup_Fix,
		Setup_Sci,
		Setup_Norm,
		Setup_Stat,
		Setup_PerD,
		Setup_TurnOff,
		Hyp,
		Verify,
		Stat,
		Dist,
		Base,
		Drg
	};
	Menu _menu = Menu::None;
	/// <summary>
	/// right to left:
	/// 0: Input (Math2d, Linear)
	/// 1: Output (Math2d, Linear)
	/// 2, 3: Angle (Degrees, Radians, Gradians)
	/// 4, 5, 6, 7: Fix (0-9)
	/// 8, 9, 10, 11: Sci (0-9)
	/// 12: Norm (1, 2)
	/// 13: fraction (mixed / not mixed)
	/// 14: Stat (On, Off)
	/// 15: PerD (Peridoic, round)
	/// 16: TurnOff (10 Min, 60 Min)
	/// </summary>
	uint16_t _setup = 0;

	void set_menu(Menu menu);

	enum class Mode {
		COMP,
		STAT,
		TABLE,
		DIST,
		VERIF,
		BASE_N,
		EQ_SOLV,
		GRAPH,
	};

	Mode _mode = Mode::COMP;

	std::vector<Equation> equations;
	Equation* _equation_selected;
	uint8_t _result_selected;
	Number _ans;
	Number _prev_ans;
	std::vector<Number*> _variables;

	Number _result;
	std::vector<KEY_SET> _result_key_sets;
	Equation _result_equation;
	Bitset2D _result_rendered;
	bool calculated;
};
