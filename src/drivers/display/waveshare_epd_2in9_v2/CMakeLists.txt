zephyr_library()

zephyr_library_sources_ifdef(CONFIG_WAVESHARE_EPD_2IN9_V2     waveshare_epd_2in9_v2.c)
zephyr_library_sources_ifdef(CONFIG_WAVESHARE_EPD_2IN9_V2     waveshare_epd_2in9_v2_priv.c)