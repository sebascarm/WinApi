#include "C_WinApi.h"
#include "Contenedor.h"

#include "C_Button.h"
#include "C_Menu.h"
#include "C_ListBox.h"
#include "C_Shape.h"

extern std::vector <Contenedor> CONTENEDOR;

//*********************************************
//*** CREACION								***
//*********************************************
void C_WinApi::Create(HINSTANCE hInstance) {
	HICON hIcon;
	hIcon = (HICON)LoadImage(	// returns a HANDLE so we have to cast to HICON
		NULL,					// hInstance must be NULL when loading from a file
		"iconfile.ico",			// the icon file name
		IMAGE_ICON,				// specifies that the file is an icon
		0,						// width of the image (we'll specify default later on)
		0,						// height of the image
		LR_LOADFROMFILE |		// we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |		// default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED				// let the system release the handle when it's no longer used
	);


	this->hInstance = hInstance;
	NombreClase = "WinApi";
	//registrar la clase windows
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = hIcon;											//LoadIcon(NULL, IDI_APPLICATION);					//nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = CreateSolidBrush(RGB(250, 250, 250));	//nullptr; //GetSysColorBrush(COLOR_3DFACE);  
	wc.lpszMenuName = nullptr;
	wc.hIconSm = nullptr;
	wc.lpszClassName = (LPSTR)NombreClase.c_str();
	//Registrar
	RegisterClassEx(&wc);

}

string C_WinApi::GetClass() {
	return NombreClase;
}

HINSTANCE C_WinApi::Get_Instance(){
	return hInstance;
}

void C_WinApi::Draw() {
	//Dibujamos solo todos los frame creados (sin mostrarlos)
	int Elemento = (int)CONTENEDOR.size();
	for (int i = 0; i < Elemento; i++) {
		if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) {
			CONTENEDOR[i].Draw();
		}
	}
	//Dibujar controles
	for (int i = 0; i < Elemento; i++) {
		if (CONTENEDOR[i].Tipo != TipoObjeto::T_FRAME) {
			// No Creamos los objetos Shape
			if (CONTENEDOR[i].Tipo != TipoObjeto::T_SHAPE) {
				CONTENEDOR[i].Draw();
			}
		}
	}

	//Mostramos Frames
	for (int i = 0; i < Elemento; i++) {
		if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) {
			CONTENEDOR[i].Show();
		}
	}
}

//*********************************************
//*** CALLBACK								***
//*********************************************
LRESULT CALLBACK C_WinApi::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//Debug de mensajes										
	//static WindowsMessageMap mm;							
	//OutputDebugString(mm(msg, lParam, wParam).c_str());	
	
	int ID			 = LOWORD(wParam);				// Identificador del control		
	int ID_Long		 = GetDlgCtrlID((HWND)lParam);  // Identificador en cambio de color	
	int Notificacion = HIWORD(wParam);	// Codigo de notificacion recibida (ej: click, doble click)
	int Elementos    = (int)CONTENEDOR.size();
	
	HDC hdc = NULL;
	PAINTSTRUCT PStruc;

	switch (msg) {
	//	Crear controles		//								
	case WM_CREATE:
		break;
	// DIBUJADO DE ELEMENTOS								
	case WM_PAINT:
		for (int i = 0; i < Elementos; i++) {
			// Buscamos el frame donde dibuja				
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) {
				bool inicial = true;
				HWND*	hPadreElem;
				// REcorremos los elementos del frame		
				for (int j = 0; j < Elementos; j++) {
					if (CONTENEDOR[j].Tipo == TipoObjeto::T_SHAPE) {
						if (CONTENEDOR[j].pShape->Redibujar) {	
							hPadreElem = CONTENEDOR[j].pShape->Get_hWnd_Padre();
							if (hWnd == *hPadreElem) {
								// Iniciar pintado	
								if (inicial) {
									hdc = BeginPaint(hWnd, &PStruc);
									inicial = false;
								}
								// Dibujar			
								CONTENEDOR[j].pShape->Draw_Shape(hdc);			// Enviamos el evento 	
							}
						}
					}
				}
				// Fin de pintado				
				if (!inicial) {
					EndPaint(hWnd, &PStruc);
				}
			}
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	// CAMBIAR COLOR DE FONDOS DE TODOS LOS LABELS			
	case WM_CTLCOLORSTATIC: {
		for (int i = 0; i < Elementos; i++) {
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_LABEL) {
				if (CONTENEDOR[i].Get_ID() == ID_Long) {
					return (LRESULT)CONTENEDOR[i].ColorEdit(wParam); // devuelve el pincel modificado
				}
			}
		}
		break;
	}
	// RECEPCION DE COMANDOS								
	case WM_COMMAND: {
		for (int i = 0; i < Elementos; i++) {
			// **** Envio de click a botones				
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_BUTTON) {
				// Buscamos el boton que recibe el evento	
				if (CONTENEDOR[i].Get_ID() == ID)
					CONTENEDOR[i].pButton->Event_Click();		// Enviamos el evento 
			}
			// **** Envio de click a Menu					
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_MENU) {
				//Recorremos los elementos del menu			
				for (int j = 0; j < CONTENEDOR[i].pMenu->V_ID.size(); j++) {
					if (CONTENEDOR[i].pMenu->V_ID[j] == ID)
						CONTENEDOR[i].pMenu->Event_Click(wParam);
				}
			}
			// **** List box								
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_LISTBOX) {
				// Buscamos el list que recibe el evento	
				if (CONTENEDOR[i].Get_ID() == ID) {
					// Buscamos el evento (SELL CHANGE)		
					if (LBN_SELCHANGE == Notificacion) {
						// Cambio de celda					
						CONTENEDOR[i].pListBox->Event_ChangeCell();
					} else if (LBN_DBLCLK == Notificacion) {
						// Cambio de celda	(DOBLE CLICK)	
						CONTENEDOR[i].pListBox->Event_DobleClick();
					}
				}
			}
		}
		break;
	}
	//CAMBIO DE TAMA�O										
	case WM_SIZE: {
		//Envio resize										
		for (int i = 0; i < Elementos; i++) {
			if (CONTENEDOR[i].Tipo == TipoObjeto::T_FRAME) {
				//Revisamos que sea la ventana que recive el event			
				if (CONTENEDOR[i].Get_hWnd() == hWnd) {
					//Evento interno para cambiar los valores de las var	
					CONTENEDOR[i].pFrame->Event_Resize(lParam);
				}
			}
		}
		break;
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//*********************************************
//*** LOOP									***
//*********************************************
int C_WinApi::Loop() {
	MSG msg;
	BOOL Result;
	while ((Result = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};
	if (Result == -1) {
		return -1;
	}
	else {
		return (int)msg.wParam;
	}
}
//*********************************************
//*** EXIT									***
//*********************************************

void C_WinApi::Exit() {
	PostQuitMessage(69);
}


//*********************************************
//*** Export								***
//*********************************************

Win_Api* New_Api() {
	return new C_WinApi();
};
