#include<stdio.h>
#include<stdlib.h>

#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

int main(int argc,char *argv[])
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L,"test.lua");

	lua_settop(L,0);
	lua_close(L);
	return 0;
}
