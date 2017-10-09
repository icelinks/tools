@echo scan start...
@echo.
@for /l %%i in (1,1,60) do @ping 10.0.44.%%i -n 1 -w 10 | find /C "¶ªÊ§ = 0">nul && @echo 10.0.44.%%i
@echo.
@pause