//######################################################//
// C_WinAPI v2.0										//
//######################################################//
// ULTIMA MODIFICACION DOCUMENTADA                      //
// 08/07/2020                                           //
// Tecla TAB											//
// NextContenedor										//
// Procedimento propio de Boton y Texto					//
// Creacion                                             //
//######################################################//

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
	static LRESULT CALLBACK Text_Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	static void Test(UINT msg, int ID, int ID_Long, int Notificacion, int Elementos, TipoObjeto Tipo, bool Test1 = false);
	
	void TeclaTab(MSG msg);
	int NextContenedor(int ID_Actual);
	
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

