@echo scan start...
@echo.
@for /l %%i in (1,1,254) do @ping 192.168.137.%%i -n 1 -w 10 | find /C "¶ªÊ§ = 0">nul && @echo 192.168.137.%%i
@echo.
@pause