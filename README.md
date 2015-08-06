# proyectodama

Libreria: ALLEGRO 5
Instalacion 
 Primero vamos a actualizar , abrimos la terminal presionando ctrl+ alt+ T, y escribimos lo siguiente:
$ sudo apt-get update

Después instalamos las dependencias necesarias:
$ sudo apt-get install build-essential subversion cmake xorg-dev libgl1-mesa-dev libglu-dev

Luego Instalamos las dependencias complementarias:
$ sudo apt-get install libpng-dev libcurl4-nss-dev libfreetype6-dev libjpeg-dev libvorbis-dev libopenal-dev libphysfs-dev libgtk2.0-dev liboss4-salsa-dev libpulse-dev libflac-dev libdumb1-dev

En seguida, instalamos las dependencias para la documentación:
$ sudo apt-get install exuberant-ctags dvi2ps dvipdfmx latex2html pandoc

Descargamos Allegro 5 desde el repositorio.
$ svn co https://alleg.svn.sourceforge.net/svnroot/alleg/allegro/branches/5.0 allegro-5.0

Lo siguiente que haremos es crear una carpeta llamada "allegro-5.0" donde se descargará el código fuente. Después dentro de "allegro-5.0" crearemos otra llamada "build" que utilizaremos para compilar e instalar el código, seguimos escribiendo en la terminal:

$ cd allegro-5.0
$ mkdir build
$ cd build

Tenemos que usar  cmake para poder compilar los archivos de la libreria que acabamos de descargar , si no tienen instalado cmake, antes de continuar, lo instalan escribiendo lo siguiente: $ sudo apt-get install cmake .

Ahora si,compilamos nuestra libreria: 
$ sudo cmake -DCMAKE_INSTALL_PREFIX=/usr ..

*Si nos lo pidiera, presionamos la tecla "c" un par de veces y luego "g" para volver a la terminal.

Este proceso nos sirve para:

    Definir dónde queremos  instalar los archivos .h
    añadir  es siguiente path "/usr/local/lib" a "/etc/ld.so.conf"
    Y ejecutar "ldconfig" (que configurar el enlazador dinámico en tiempo de ejecución).


Por último, sólo nos queda instalar, escribimos lo siguiente y esperamos a que termine: 
$ sudo make install 

Una vez terminado el proceso, habremos installado allegro 5.0, pero aun falta el paso mas importante, configurar la libreria para que funcione en nuestro IDE Codeblocks, mi version es la 12.11.

Dentro de CodeBlocks a la opcion  "Settings" --- "Compiler ..." y luego en la ventana que aparece buscamos donde diga "Linker Settings".

Dentro de "Linker Settings" encontraremos 2 apartados: "Link libraries" y "Other linker options". Debemos enlazar los archivos de la librería con nuestro codeblocks:

Nos debe de quedar así

    Link libraries:

        /usr/lib/liballegro_dialog.so
        /usr/lib/liballegro_color.so
        /usr/lib/liballegro_audio.so
        /usr/lib/liballegro_image.so
        /usr/lib/liballegro_physfs.so
        /usr/lib/liballegro.so
        /usr/lib/liballegro_font.so
        /usr/lib/liballegro_acodec.so
        /usr/lib/liballegro_main.so
        /usr/lib/liballegro_memfile.so
        /usr/lib/liballegro_primitives.so
        /usr/lib/liballegro_ttf.so

    Other linker options

        `pkg-config --libs allegro-5.0`  // aquí copiamos todo                                            incluyendo el tilde.`

Luego de estos pasos la libreria allegro ya esta instalada y lista para ejecutar con codeblocks.
