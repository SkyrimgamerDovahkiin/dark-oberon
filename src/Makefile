SOUND ?= 1
DEBUG ?= 0
WINDOWS ?= 0
UNIX ?= 1

# NEEDED: logs, callbacks, sound, doberon

# CXX=i686-w64-mingw32-g++
CXX=g++

CPP = $(CXX) $(CPPFLAGS) $(INCLUDES) $(DEFINES)
CPPFLAGS = -g -w
#DEFINES = -DDATA_DIR='""' -DUNIX=$(UNIX) -DSOUND=$(SOUND) -DDEBUG=$(DEBUG) -DWINDOWS=$(WINDOWS) 
#DEFINES = -DDATA_DIR='""' -DSOUND=$(SOUND) -DDEBUG=$(DEBUG) -DNEW_GLFW3=1
#INCLUDES = -I/usr/X11R6/include -I/usr/X11R6/include/GL -I../libs
#LIBPATHS = -L/usr/X11R6/lib -L/usr/lib -L/usr/local/lib -L../libs
#LIBRARIES = -pthread -lglfw -lGL -lX11 -lGLU 
#INCLUDES = -I/mingw32/include -I/mingw32/include/GLFW -I../libs/fmod3/include -I../libs/tinycthread/include
#LIBPATHS = -L/mingw32/lib -L../libs/fmod3/lib -L../libs/tinycthread/lib
# DEFINES = -DDATA_DIR='""' -DSOUND=$(SOUND) -DDEBUG=$(DEBUG)
INCLUDES = -I/usr/include/GLFW \
			-I../libs/fmod3/include \
			-I/usr/include/x86_64-linux-gnu/SDL2 \
			-I../libs/imgui/include \
			-I../libs/imgui/include/backends/OpenGLglfw \
			-I../libs/GLAD/include -I../libs/stb_image/include -I../libs/glm/include -I./event
# LIBPATHS = -L/mingw32/lib -L../libs/fmod3/lib -L../libs/glfw-legacy/lib
# LIBPATHS = -L/mingw32/lib -L../libs/fmod3/lib -L../libs/glfw-legacy/lib
# LIBPATHS = -L/mingw32/lib -L../libs/fmod3/lib -L../libs/glfw-legacy/lib

# LIBRARIES = -static -mwindows -lmingw32 -lSDLmain -lSDL -lSDL_image -lglfw -lopengl32 -lglu32 -lfmod -s -lSDL_gfx -lSDL_mixer  -lvorbisfile -lvorbis -lmingw32 -lbz2 -lharfbuzz -lglib-2.0 -lintl -liconv -ltiff -ljpeg -llzma -lpng16 -lstdc++ -lwebp -lwinpthread -lz -larchive -lwinmm -lgdi32 -ldxguid -lasprintf -lcharset -lcrypto -lcurl -lexpat -lffi -lFLAC++ -lFLAC -lfontconfig -lformw -lfreeglut_static -lgdbm -lgettextlib -lgettextpo -lgif -lgio-2.0 -lglew32 -lglew32mx -lgmodule-2.0 -lgmp -lgmpxx -lgnurx -lgnutls -lgnutlsxx -lgobject-2.0 -lgthread-2.0 -lhistory -lhogweed -lidn -lisl -ljansson  -ljsoncpp -llua  -llzo2  -lmenuw -lmetalink -lminizip -lmpc -lmpfr -lncurses++w -lncursesw -lnettle -lnghttp2 -logg -lopenal -lpanelw -lphysfs -lpixman-1 -lreadline -lregex -lrtmp -lssh2 -lssl -lsystre -ltasn1 -ltclstub86 -ltermcap -ltheora -ltheoradec -ltheoraenc -ltkstub86 -ltre -lturbojpeg -lvorbisenc -lwebpdecoder -lwebpdemux -lwebpmux -lole32 -lws2_32
LIBRARIES = `sdl2-config --cflags --libs` -lSDL2_mixer -lglfw -lGL
# imgui
OBJECTS = imgui_impl_glfw.o imgui_impl_opengl3.o imgui.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o
OBJECTS += stb_image.o
OBJECTS += dovao.o dovbo.o doebo.o doshader.o dotexture.o doberon.o docallbacks.o dosound.o dologs.o utils.o dosimpletypes.o doalloc.o dodraw.o glad.o docamera.o

TARGETS = ../dark-oberon
# OBJECTS = doalloc.o doberon.o dobuildings.o doconfig.o dodata.o dodraw.o doengine.o doevents.o dofactories.o dofight.o dofile.o dofollower.o doforces.o dohost.o doipc.o dolayout.o doleader.o dologs.o domap.o domapunits.o domouse.o donet.o doplayers.o doraces.o doschemes.o doselection.o dosimpletypes.o dosound.o dosources.o dounits.o dowalk.o doworkers.o glfont.o glgui.o tga.o utils.o
# TARGETS = ../dark-oberon

#all: tags ../dark-oberon checking
all: ../dark-oberon

checking: .checking
.checking: *.h *.cpp
	@echo Checking format of source files...
	@if egrep -l "`printf '\t'`|`printf '\r'`" *.cpp *.h; then echo "Error: Previous listed files contain illegal characters (tabs or ^M)"; false; fi
	@echo OK
	@touch .checking

clean:
	rm -f $(OBJECTS) $(TARGETS) *core core.* tags

tags: *.h *.cpp
	-exctags * 2> /dev/null || ctags * 2> /dev/null

docs:
	rm -rf ../docs/documentation/html_local
	doxygen .doxygen.conf 2>&1 | tee .doxygen.log

../dark-oberon: $(OBJECTS)
	$(CPP) $(OBJECTS) $(LIBPATHS) $(LIBRARIES) -o ../dark-oberon


# stb_image
stb_image.o: ../libs/stb_image/include/stb_image.cpp
	$(CPP) -c ../libs/stb_image/include/stb_image.cpp

# GLAD
glad.o: glad.c
	$(CPP) -c glad.c

# imgui stuff
imgui_impl_glfw.o: ../libs/imgui/include/backends/OpenGLglfw/imgui_impl_glfw.cpp
	$(CPP) -c ../libs/imgui/include/backends/OpenGLglfw/imgui_impl_glfw.cpp

imgui_impl_opengl3.o: ../libs/imgui/include/backends/OpenGLglfw/imgui_impl_opengl3.cpp ../libs/imgui/include/backends/OpenGLglfw/imgui_impl_opengl3_loader.h
	$(CPP) -c ../libs/imgui/include/backends/OpenGLglfw/imgui_impl_opengl3.cpp

imgui.o: ../libs/imgui/include/imgui.cpp
	$(CPP) -c ../libs/imgui/include/imgui.cpp

imgui_demo.o: ../libs/imgui/include/imgui_demo.cpp
	$(CPP) -c ../libs/imgui/include/imgui_demo.cpp

imgui_draw.o: ../libs/imgui/include/imgui_draw.cpp
	$(CPP) -c ../libs/imgui/include/imgui_draw.cpp

imgui_tables.o: ../libs/imgui/include/imgui_tables.cpp
	$(CPP) -c ../libs/imgui/include/imgui_tables.cpp

imgui_widgets.o: ../libs/imgui/include/imgui_widgets.cpp
	$(CPP) -c ../libs/imgui/include/imgui_widgets.cpp

doshader.o: doshader.cpp
	$(CPP) -c doshader.cpp

dotexture.o: dotexture.cpp
	$(CPP) -c dotexture.cpp

doebo.o: doebo.cpp
	$(CPP) -c doebo.cpp

dovao.o: dovao.cpp
	$(CPP) -c dovao.cpp

dovbo.o: dovbo.cpp
	$(CPP) -c dovbo.cpp

docamera.o: docamera.cpp
	$(CPP) -c docamera.cpp

# should be correct
doalloc.o: doalloc.cpp cfg.h doalloc.h dologs.h
	$(CPP) -c doalloc.cpp

# should be correct
docallbacks.o: docallbacks.cpp docallbacks.h
	$(CPP) -c docallbacks.cpp

# doberon.o: doberon.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h utils.h
# 	$(CPP) -c doberon.cpp

# doberon.o: doberon.cpp cfg.h doalloc.h dologs.h dosimpletypes.h dosound.h docallbacks.h
# 	$(CPP) -c doberon.cpp

# should be correct
doberon.o: doberon.cpp dologs.h docallbacks.h
	$(CPP) -c doberon.cpp

# dobuildings.o: dobuildings.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dobuildings.cpp

# doconfig.o: doconfig.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doconfig.cpp

# dodata.o: dodata.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h tga.h
# 	$(CPP) -c dodata.cpp

dodata.o: dodata.cpp cfg.h doalloc.h dodata.h dologs.h dosimpletypes.h dosound.h
	$(CPP) -c dodata.cpp

# dodraw.o: dodraw.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dodraw.cpp

dodraw.o: dodraw.cpp cfg.h doalloc.h dodraw.h dologs.h dosimpletypes.h dosound.h doshader.hpp dovao.hpp dovbo.hpp
	$(CPP) -c dodraw.cpp

# doengine.o: doengine.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doengine.cpp

# doevents.o: doevents.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doevents.cpp

# dofactories.o: dofactories.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dofactories.cpp

# dofight.o: dofight.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dofight.cpp

# dofile.o: dofile.cpp cfg.h doalloc.h dodata.h dofile.h doipc.h dologs.h dosimpletypes.h dosound.h glfont.h glgui.h
# 	$(CPP) -c dofile.cpp

# dofollower.o: dofollower.cpp cfg.h doalloc.h doipc.h dologs.h dopool.h dosimpletypes.h
# 	$(CPP) -c dofollower.cpp

# doforces.o: doforces.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doforces.cpp

# dohost.o: dohost.cpp cfg.h doalloc.h doipc.h dologs.h dopool.h dosimpletypes.h
# 	$(CPP) -c dohost.cpp

# doipc.o: doipc.cpp cfg.h doalloc.h doipc.h dologs.h
# 	$(CPP) -c doipc.cpp

# dolayout.o: dolayout.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dolayout.cpp

# doleader.o: doleader.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doleader.cpp

# dologs.o: dologs.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h utils.h
# 	$(CPP) -c dologs.cpp

# dologs.o: dologs.cpp cfg.h doalloc.h dologs.h dosimpletypes.h dosound.h
# 	$(CPP) -c dologs.cpp

# should be correct
dologs.o: dologs.cpp dologs.h utils.h
	$(CPP) -c dologs.cpp

# domap.o: domap.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c domap.cpp

# domapunits.o: domapunits.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c domapunits.cpp

# domouse.o: domouse.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c domouse.cpp

# donet.o: donet.cpp cfg.h doalloc.h doipc.h dologs.h dopool.h dosimpletypes.h utils.h
# 	$(CPP) -c donet.cpp

# doplayers.o: doplayers.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doplayers.cpp

# doraces.o: doraces.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doraces.cpp

# doschemes.o: doschemes.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doschemes.cpp

# doselection.o: doselection.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doselection.cpp

# should be correct
dosimpletypes.o: dosimpletypes.cpp cfg.h doalloc.h dosimpletypes.h
	$(CPP) -c dosimpletypes.cpp

# should be correct
dosound.o: dosound.cpp dosound.h cfg.h dologs.h dosimpletypes.h
	$(CPP) -c dosound.cpp

# dosound.o: dosound.cpp dosound.h cfg.h doalloc.h dologs.h dosimpletypes.h
# 	$(CPP) -c dosound.cpp

# dosources.o: dosources.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dosources.cpp

# dounits.o: dounits.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doengine.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dounits.cpp

# dowalk.o: dowalk.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c dowalk.cpp

# doworkers.o: doworkers.cpp cfg.h doalloc.h doconfig.h dodata.h dodraw.h doevents.h dofight.h dofile.h doipc.h dolayout.h dologs.h domap.h domouse.h doplayers.h dopool.h doraces.h doschemes.h doselection.h dosimpletypes.h dosound.h dothreadpool.h dounits.h dowalk.h glfont.h glgui.h
# 	$(CPP) -c doworkers.cpp

# glfont.o: glfont.cpp glfont.h
# 	$(CPP) -c glfont.cpp

# glgui.o: glgui.cpp cfg.h doipc.h glfont.h glgui.h
# 	$(CPP) -c glgui.cpp

# tga.o: tga.cpp tga.h
# 	$(CPP) -c tga.cpp

# should be correct
utils.o: utils.cpp cfg.h utils.h
	$(CPP) -c utils.cpp

DEVELOPERS = crazych index jojolase libertik martinpp peterpp

devel_stats.html: *.cpp *.h
	@echo "Running annotate..." >&2
	@cvs annotate *.h *.cpp > annotate.out 2> /dev/null
	echo "<? #### DO NOT EDIT ! #### ?>" > devel_stats.html
	echo "<? #### If you want to change this file, edit src/create_makefile.sh #### ?>" >> devel_stats.html
	echo "" >> devel_stats.html
	echo "<h2>All lines</h2>" >> devel_stats.html
	echo "<table class=box><tr><th></th><th>lines</th><th>words</th><th>chars</th><tr>" >> devel_stats.html
	for developer in $(DEVELOPERS) ; do \
		echo -n "$$developer " ; \
		cat annotate.out | grep "($$developer" | sed 's/^[^:]*: //' | grep -v '^ *$$' | wc ; \
	done | sort -n -r -k 2 | \
	sed 's:  *:</td><td>:g' | sed 's:^:<tr><td>:' | sed 's:$$:</td></tr>:' >> devel_stats.html
	echo "</table>" >> devel_stats.html
	echo "" >> devel_stats.html
	echo "<h2>Lines without comments</h2>" >> devel_stats.html
	echo "<table class=box><tr><th></th><th>lines</th><th>words</th><th>chars</th><tr>" >> devel_stats.html
	for developer in $(DEVELOPERS) ; do \
		echo -n "$$developer " ; \
		cat annotate.out | grep "($$developer" | sed 's/^[^:]*: //' | grep -v '^ *$$' | grep -v '^ *\(//\|/\*\|\*\)' | wc ; \
	done | sort -n -r -k 2 | \
	sed 's:  *:</td><td>:g' | sed 's:^:<tr><td>:' | sed 's:$$:</td></tr>:' >> devel_stats.html
	echo "</table>" >> devel_stats.html
	echo "" >> devel_stats.html
	echo "<h2>Comment lines</h2>" >> devel_stats.html
	echo "<table class=box><tr><th></th><th>lines</th><th>words</th><th>chars</th><tr>" >> devel_stats.html
	for developer in $(DEVELOPERS) ; do \
		echo -n "$$developer" ; \
		cat annotate.out | grep "($$developer" | sed 's/^[^:]*: //' | grep '^ *\(//\|/\*\|\*\)' | wc ; \
	done | sort -n -r -k 2 | \
	sed 's:  *:</td><td>:g' | sed 's:^:<tr><td>:' | sed 's:$$:</td></tr>:' >> devel_stats.html
	echo "</table>" >> devel_stats.html
	echo "" >> devel_stats.html
	date "+<p>Last update: %Y-%m-%d %H:%M</p>" >> devel_stats.html
	sed 's/jojolase/jojolaser/' devel_stats.html > ,,devel_stats.html
	mv ,,devel_stats.html devel_stats.html
	rm annotate.out

update_web: devel_stats.html
	scp devel_stats.html user.sf.net:/home/groups/d/da/dark-oberon/htdocs/stats.php
	scp -r ../docs/documentation/html_local user.sf.net:/home/groups/d/da/dark-oberon/htdocs/documentation/
