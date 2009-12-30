@echo. >cc.x
@echo. >cc.y
@%2 %3 %4 %5 >cc.x 2>cc.y
@type cc.y >> cc.x
@find %1 cc.x >nul
