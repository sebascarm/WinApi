## WinApi v3.3
    
### 04/06/2020
    - Button v2.0 (Eventos Press y Release)
### 02/06/2020
    - Shape v1.2 (Cambio de color)
### 28/05/2020
    - Shape v1.0 (Final)

### 28/05/2020
    - Shape     v0.6 (Cont)

### 27/05/2020
    - Shape     v0.5 (Creacion)

### 21/03/2020
    - ListBox   v2.1 (Doble Click)

### 18/03/2020
    - RichText  v2.4 (RichText con SetFont)

### 17/03/2020
    - RichText  v2.3 (RichText)

### 15/03/2020
    - MultiLine v1.1 (Correccion al resize)
    - Objeto    v2.1 (habilitar y deshabilitar objetos)

### 08/03/2020
    - ListBox   v2.0 (SetFont)
    - ListBox   v2.0 (Event ChangeCell)
    - Objeto    v2.0 (SetFont)

### 06/02/2020
    - ListBox   v1.0 (ListBox)



## GIT + Github

 - Crear Proyecto en GitHub (Web)
```
 - git init 'Nombre de carpeta' 
 - // Copiar archivos al folder
 - // agregar .gitignore
 - // agregar readme.md
 - git add . // Agrega los archivos al proyecto
 - git commit -m "primer commit"
 - git remote add origin https://github.com/USUARIO/PROYECTO.git
 - git push -u origin master
```
 
### Usuario
- git config --global user.email "sebascarm@gmail.com"
- git config --global user.name "sebascar"

### GitHub Comando
- Crear proyecto
- git remote add origin
- git push -u origin master
- git pull // trae los cambios del servidor
- git clone DIRECCION // se trae a local los archivos del repositorio

### Actualizar el -gitignore
- git rm -r --cached .
- git add .
- git commit -m "Atualizando .gitignore para..."

----------------

# Transmisor P3D
Software encargado de la intercomunicacion entre Arduino y P3D PMDG mediante dos canales de comunicaci�n.

## Caracteristicas principales
Gesti�n de la comunicaci�n con Arduino.
Gesti�n de comunicaci�n con P3D mediante SimConnect.
Gesti�n de transmision de datos a procesos remotos mediante Socket.
Gesti�n remota.

## Comunicaci�n
En resumen este software se instala en un Equipo mediador, el cual se conectar� fisicamente con 2 placas Arduino a travez de su puertos serie y el programa se encargara de analizar los paquetes y datos recibidos para traducirlos y transmitir en forma remota o local al Servidor P3D mediante SimConnect.

## Transmisor de datos remotos
Comunicaci�n conta software Comandos para ejecuci�n de procesos y eventos en forma remota.

## Gesti�n Remota
Aplicaci�n Cliente Servidor para analizar y gestionar la transmisi�n de forma remota.


