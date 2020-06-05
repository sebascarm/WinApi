#pragma once
#include "WinApi.h"
#include <vector>
#include "C_Frame.h"

class C_WinApi :public Win_Api
{
protected:
	WNDCLASSEX wc = { 0 };
	HINSTANCE hInstance;
	std::string NombreClase;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Boton_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	static void Test(UINT msg, int ID, int ID_Long, int Notificacion, int Elementos, TipoObjeto Tipo, bool Test1 = false);
	// friends
	//friend C_Frame;

public:
	void Create(HINSTANCE hInstance);
	void Draw();
	int  Loop();
	void Exit();
	// Metodos
	HINSTANCE Get_Instance();
	string GetClass();
};

