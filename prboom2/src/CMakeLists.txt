
function(ApplySDL2NetOptions TARGET)
    if (SDL2_NET_FOUND)
        target_include_directories(${TARGET} PRIVATE ${SDL2_NET_INCLUDE_DIRS})
        target_link_libraries(${TARGET} PRIVATE ${SDL2_NET_LIBRARIES})
    endif ()
endfunction()

# PrBoom main executable

set(COMMON_SRC
        am_map.cc
        am_map.hh
        cpp/chars.cc
        cpp/chars.hh
        cpp/strings.cc
        cpp/strings.hh
        doomdata.hh
        doomdef.cc
        doomdef.hh
        doomstat.cc
        doomstat.hh
        doomtype.hh
        dsda.cc
        dsda.hh
        dsda/demo.cc
        dsda/demo.hh
        dsda/ghost.cc
        dsda/ghost.hh
        dsda/global.cc
        dsda/global.hh
        dsda/hud.cc
        dsda/hud.hh
        dsda/input.cc
        dsda/input.hh
        dsda/key_frame.cc
        dsda/key_frame.hh
        dsda/msecnode.cc
        dsda/msecnode.hh
        dsda/palette.cc
        dsda/palette.hh
        dsda/settings.cc
        dsda/settings.hh
        dstrings.cc
        dstrings.hh
        d_deh.cc
        d_deh.hh
        d_englsh.hh
        d_event.hh
        d_items.cc
        d_items.hh
        d_main.cc
        d_main.hh
        d_net.hh
        d_player.hh
        d_think.hh
        d_ticcmd.hh
        e6y.cc
        e6y.hh
        f_finale.cc
        f_finale.hh
        f_finale2.cc
        f_wipe.cc
        f_wipe.hh
        g_game.cc
        g_game.hh
        g_overflow.cc
        g_overflow.hh
        heretic/d_main.cc
        heretic/def.cc
        heretic/def.hh
        heretic/dstrings.hh
        heretic/dstrings.cc
        heretic/f_finale.hh
        heretic/f_finale.cc
        heretic/info.cc
        heretic/in_lude.cc
        heretic/in_lude.hh
        heretic/level_names.cc
        heretic/mn_menu.cc
        heretic/mn_menu.hh
        heretic/p_action.hh
        heretic/sb_bar.cc
        heretic/sb_bar.hh
        heretic/sounds.cc
        hu_lib.cc
        hu_lib.hh
        hu_stuff.cc
        hu_stuff.hh
        hu_tracers.cc
        hu_tracers.hh
        info.cc
        info.hh
        i_capture.cc
        i_capture.hh
        i_joy.hh
        i_main.hh
        i_network.hh
        i_pcsound.cc
        i_pcsound.hh
        i_sound.hh
        i_system.hh
        i_video.hh
        lprintf.cc
        lprintf.hh
        md5.cc
        md5.hh
        m_argv.cc
        m_argv.hh
        m_bbox.cc
        m_bbox.hh
        m_cheat.cc
        m_cheat.hh
        m_fixed.hh
        m_menu.cc
        m_menu.hh
        m_misc.cc
        m_misc.hh
        m_random.cc
        m_random.hh
        m_swap.hh
        protocol.hh
        p_ceilng.cc
        p_checksum.cc
        p_checksum.hh
        p_doors.cc
        p_enemy.cc
        p_enemy.hh
        p_floor.cc
        p_genlin.cc
        p_inter.cc
        p_inter.hh
        p_lights.cc
        p_map.cc
        p_map.hh
        p_maputl.cc
        p_maputl.hh
        p_mobj.cc
        p_mobj.hh
        p_plats.cc
        p_pspr.cc
        p_pspr.hh
        p_saveg.cc
        p_saveg.hh
        p_setup.cc
        p_setup.hh
        p_sight.cc
        p_spec.cc
        p_spec.hh
        p_switch.cc
        p_telept.cc
        p_tick.cc
        p_tick.hh
        p_user.cc
        p_user.hh
        r_bsp.cc
        r_bsp.hh
        r_data.cc
        r_data.hh
        r_defs.hh
        r_demo.cc
        r_demo.hh
        r_draw.cc
        r_draw.hh
        r_filter.cc
        r_filter.hh
        r_fps.cc
        r_fps.hh
        r_main.cc
        r_main.hh
        r_patch.cc
        r_patch.hh
        r_plane.cc
        r_plane.hh
        r_segs.cc
        r_segs.hh
        r_sky.cc
        r_sky.hh
        r_state.hh
        r_things.cc
        r_things.hh
        scanner.cpp
        scanner.hh
        sc_man.cc
        sc_man.hh
        sounds.cc
        sounds.hh
        statdump.cc
        statdump.hh
        st_lib.cc
        st_lib.hh
        st_stuff.cc
        st_stuff.hh
        s_advsound.cc
        s_advsound.hh
        s_sound.cc
        s_sound.hh
        tables.cc
        tables.hh
        umapinfo.cc
        umapinfo.hh
        version.cc
        version.hh
        v_video.cc
        v_video.hh
        wi_stuff.cc
        wi_stuff.hh
        w_wad.cc
        w_wad.hh
        z_bmalloc.cc
        z_bmalloc.hh
        )

set(NET_CLIENT_SRC
        d_client.cc
        )

if (HAVE_MMAP)
    set(WAD_SRC w_mmap.cc)
else ()
    set(WAD_SRC w_memcache.cc)
endif ()

set(MUS2MID_SRC
        memio.cc
        memio.hh
        mus2mid.cc
        mus2mid.hh
        )

set(SDLDOOM_SOURCES
        SDL/i_joy.cc
        SDL/i_main.cc
        SDL/i_network.cc
        SDL/i_sound.cc
        SDL/i_sshot.cc
        SDL/i_system.cc
        SDL/i_video.cc
        )

set(PCSOUND_SOURCES
        PCSOUND/pcsound.cc
        PCSOUND/pcsound.hh
        PCSOUND/pcsound_linux.cc
        PCSOUND/pcsound_sdl.cc
        PCSOUND/pcsound_win32.cc
        )

set(TEXTSCREEN_SOURCES
        TEXTSCREEN/doomkeys.hh
        TEXTSCREEN/txt_main.hh
        TEXTSCREEN/txt_font.hh
        TEXTSCREEN/txt_largefont.hh
        TEXTSCREEN/txt_sdl.cc
        TEXTSCREEN/txt_sdl.hh
        TEXTSCREEN/txt_smallfont.hh
        )

set(DOOMMUSIC_SOURCES
        MUSIC/dbopl.cc
        MUSIC/dbopl.hh
        MUSIC/dumbplayer.cc
        MUSIC/dumbplayer.hh
        MUSIC/fl_object.cc
        MUSIC/fl_object.hh
        MUSIC/fl_settings.cc
        MUSIC/fl_settings.hh
        MUSIC/flplayer.cc
        MUSIC/flplayer.hh
        MUSIC/madplayer.cc
        MUSIC/madplayer.hh
        MUSIC/midifile.cc
        MUSIC/midifile.hh
        MUSIC/musicplayer.hh
        MUSIC/opl.cc
        MUSIC/opl.hh
        MUSIC/oplplayer.cc
        MUSIC/oplplayer.hh
        MUSIC/opl_queue.cc
        MUSIC/opl_queue.hh
        MUSIC/portmidiplayer.cc
        MUSIC/portmidiplayer.hh
        MUSIC/vorbisplayer.cc
        MUSIC/vorbisplayer.hh
        )

set(EXTRA_FILES
        r_drawcolpipeline.inl
        r_drawcolumn.inl
        r_drawflush.inl
        r_drawspan.inl
        )

set(PRBOOM_PLUS_SOURCES
        ${COMMON_SRC}
        ${NET_CLIENT_SRC}
        ${WAD_SRC}
        ${MUS2MID_SRC}
        ${SDLDOOM_SOURCES}
        ${PCSOUND_SOURCES}
        ${TEXTSCREEN_SOURCES}
        ${DOOMMUSIC_SOURCES}
        ${EXTRA_FILES}
        )

function(AddGameExecutable TARGET SOURCES)
    if (OPENGL_FOUND AND OPENGL_GLU_FOUND)
        set(SOURCES
                ${SOURCES}
                gl_clipper.cc
                gl_detail.cc
                gl_drawinfo.cc
                gl_fbo.cc
                gl_gamma.cc
                gl_hires.cc
                gl_hqresize.cc
                gl_intern.hh
                gl_light.cc
                gl_main.cc
                gl_map.cc
                gl_missingtexture.cc
                gl_opengl.cc
                gl_opengl.hh
                gl_preprocess.cc
                gl_shader.cc
                gl_shadow.cc
                gl_sky.cc
                gl_struct.hh
                gl_texture.cc
                gl_vertex.cc
                gl_wipe.cc
                )
    endif ()

    if (WIN32)
        add_definitions("-DUSE_WIN32_PCSOUND_DRIVER -DUSE_WINDOWS_LAUNCHER")
        set(SOURCES
                ${SOURCES}
                ../ICONS/icons.rc
                e6y_launcher.cc
                e6y_launcher.hh
                SDL/SDL_windows_main.cc
                )
    endif ()

    add_definitions("-DUSE_EXPERIMENTAL_MUSIC")

    add_executable(${TARGET} WIN32 ${SOURCES})
    target_include_directories(${TARGET} PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${CMAKE_BINARY_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}
            )
    target_link_libraries(${TARGET} PRIVATE
            ${SDL2_LIBRARIES}
            )
    if (WIN32)
        target_link_libraries(${TARGET} PRIVATE
                winmm
                comctl32
                )
    endif ()
    set_target_properties(${TARGET} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${PRBOOM_OUTPUT_PATH}
            )
    if (SDL2_IMAGE_FOUND)
        target_include_directories(${TARGET} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
        target_link_libraries(${TARGET} PRIVATE ${SDL2_IMAGE_LIBRARIES})
    endif ()
    if (SDL2_MIXER_FOUND)
        target_include_directories(${TARGET} PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
        target_link_libraries(${TARGET} PRIVATE ${SDL2_MIXER_LIBRARIES})
    endif ()
    if (PCREPOSIX_FOUND)
        target_include_directories(${TARGET} PRIVATE ${PCRE_INCLUDE_DIR})
        target_link_libraries(${TARGET} PRIVATE ${PCREPOSIX_LIBRARIES})
    endif ()
    ApplySDL2NetOptions(${TARGET})
    if (ZLIB_FOUND)
        target_include_directories(${TARGET} PRIVATE ${ZLIB_INCLUDE_DIRS})
        target_link_libraries(${TARGET} PRIVATE ${ZLIB_LIBRARIES})
    endif ()
    if (LIBMAD_FOUND)
        target_include_directories(${TARGET} PRIVATE ${LIBMAD_INCLUDE_DIRS})
        target_link_libraries(${TARGET} PRIVATE ${LIBMAD_LIBRARIES})
    endif ()
    if (FLUIDSYNTH_FOUND)
        target_include_directories(${TARGET} PRIVATE ${FLUIDSYNTH_INCLUDE_DIR})
        target_link_libraries(${TARGET} PRIVATE ${FLUIDSYNTH_LIBRARIES})
    endif ()
    if (DUMB_FOUND)
        target_include_directories(${TARGET} PRIVATE ${DUMB_INCLUDE_DIR})
        target_link_libraries(${TARGET} PRIVATE ${DUMB_LIBRARY})
    endif ()
    if (VORBIS_FOUND)
        target_include_directories(${TARGET} PRIVATE ${VORBIS_INCLUDE_DIR})
        target_link_libraries(${TARGET} PRIVATE ${VORBISFILE_LIBRARY})
    endif ()
    if (PortMidi_FOUND)
        target_include_directories(${TARGET} PRIVATE ${PORTMIDI_INCLUDE_DIR})
        target_link_libraries(${TARGET} PRIVATE ${PORTMIDI_LIBRARIES})
    endif ()
    add_dependencies(${TARGET} prboom-pp-wad)

    if (MSVC)
        set_target_properties(${TARGET} PROPERTIES
                LINK_FLAGS "/MANIFEST:NO"
                )
        add_custom_command(TARGET ${TARGET} POST_BUILD
                COMMAND "mt.exe" -manifest \"${CMAKE_CURRENT_SOURCE_DIR}\\..\\ICONS\\prboom-plus.exe.manifest\" -outputresource:\"$<TARGET_FILE:prboom-pp>\"\;\#1
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${WAD_DATA_PATH} $<TARGET_FILE_DIR:prboom-pp>
                )
    endif ()

    install(TARGETS ${TARGET} COMPONENT "Game executable" RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    if (OPENGL_FOUND AND OPENGL_GLU_FOUND)
        target_compile_definitions(${TARGET} PRIVATE
                GL_DOOM
                USE_SHADERS
                USE_FBO_TECHNIQUE
                USE_GLU_IMAGESCALE
                USE_GLU_MIPMAP
                USE_GLU_TESS
                )
        target_link_libraries(${TARGET} PRIVATE
                ${OPENGL_gl_LIBRARY}
                ${OPENGL_glu_LIBRARY}
                )
    endif ()
endfunction()

AddGameExecutable(prboom-pp "${PRBOOM_PLUS_SOURCES}")


# PrBoom-Plus server executable

option(BUILD_SERVER "Build PrBoom-PP server executable" ON)

if (BUILD_SERVER AND SDL2_NET_FOUND)
    set(PRBOOM_PLUS_GAME_SERVER_SOURCES
            d_server.cc
            protocol.hh
            SDL/i_network.cc
            )

    if (MSVC)
        set(PRBOOM_PLUS_GAME_SERVER_SOURCES
                ${PRBOOM_PLUS_GAME_SERVER_SOURCES}
                SDL/i_system.cc
                )
    else ()
        set(PRBOOM_PLUS_GAME_SERVER_SOURCES
                ${PRBOOM_PLUS_GAME_SERVER_SOURCES}
                POSIX/i_system.cc
                )
    endif ()

    add_executable(prboom-plus-game-server ${PRBOOM_PLUS_GAME_SERVER_SOURCES})
    target_include_directories(prboom-plus-game-server PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${CMAKE_BINARY_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}
            )
    target_link_libraries(prboom-plus-game-server PRIVATE
            ${SDL2_LIBRARIES}
            )
    set_target_properties(prboom-plus-game-server PROPERTIES
            COMPILE_DEFINITIONS PRBOOM_SERVER
            RUNTIME_OUTPUT_DIRECTORY ${PRBOOM_OUTPUT_PATH}
            )
    ApplySDL2NetOptions(prboom-plus-game-server)
    install(TARGETS prboom-plus-game-server COMPONENT "Game server executable" RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif ()


# PrBoom-Plus macOS launcher

if (APPLE)
    set(LAUNCHER_SOURCES
            MAC/ANSIString.m
            MAC/ConsoleController.h
            MAC/ConsoleController.m
            MAC/DrawerButton.h
            MAC/DrawerButton.m
            MAC/FileButtonController.h
            MAC/FileButtonController.m
            MAC/LauncherApp.h
            MAC/LauncherApp.m
            MAC/LauncherMain.m
            MAC/ResolutionDataSource.h
            MAC/ResolutionDataSource.m
            MAC/UKFileWatcher.h
            MAC/UKKQueue.h
            MAC/UKKQueue.m
            MAC/UKMainThreadProxy.h
            MAC/UKMainThreadProxy.m
            MAC/WadViewController.h
            MAC/WadViewController.m
            )

    set(LAUNCHER_RESOURCES
            MAC/Launcher.icns
            MAC/PrBoom.icns
            MAC/PrBoom.sdef
            )
    set_source_files_properties(${LAUNCHER_RESOURCES} PROPERTIES
            MACOSX_PACKAGE_LOCATION Resources
            )

    set(LAUNCHER_MAINMENU_RESOURCES
            MAC/English.lproj/MainMenu.nib/classes.nib
            MAC/English.lproj/MainMenu.nib/info.nib
            MAC/English.lproj/MainMenu.nib/keyedobjects.nib
            )
    set_source_files_properties(${LAUNCHER_MAINMENU_RESOURCES} PROPERTIES
            MACOSX_PACKAGE_LOCATION Resources/English.lproj/MainMenu.nib
            )

    add_executable(prboom-pp-launcher MACOSX_BUNDLE
            ${LAUNCHER_SOURCES}
            ${LAUNCHER_RESOURCES}
            ${LAUNCHER_MAINMENU_RESOURCES}
            )
    target_include_directories(prboom-pp-launcher PRIVATE
            ${CMAKE_BINARY_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}
            )
    set_target_properties(prboom-pp-launcher PROPERTIES
            LINK_FLAGS "-framework Cocoa"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/MAC/Info.plist"
            OUTPUT_NAME "Launcher"
            RUNTIME_OUTPUT_DIRECTORY ${PRBOOM_OUTPUT_PATH}
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
            )
    add_dependencies(prboom-plus-launcher prboom-pp)

    set(BUNDLE_GAME_EXECUTABLE prboom-pp)

    add_custom_command(TARGET prboom-pp-launcher POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${BUNDLE_GAME_EXECUTABLE}> $<TARGET_FILE_DIR:prboom-pp-launcher>/PrBoom-PP
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${WAD_DATA_PATH} $<TARGET_FILE_DIR:prboom-plus-launcher>
            )

    if (BUILD_SERVER AND SDL2_NET_FOUND)
        add_dependencies(prboom-pp-launcher prboom-pp-game-server)
        add_custom_command(TARGET prboom-pp-launcher POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:prboom-plus-game-server> $<TARGET_FILE_DIR:prboom-pp-launcher>
                )
    endif ()
endif ()
