//essentially a fork of https://github.com/Mellonyt/Roblox-Lua-Type-Scanner/blob/master/main.cpp with a few changes that i like

struct types {
  	int none = 0;
	int nil = 0;
	int userdata = 0;
	int function = 0;
	int string = 0;
	int boolean = 0;
	int number = 0;
	int thread = 0;
	int table = 0;
	int lightuserdata = 0;
  	int proto = 0; //not in mellons :shock:
};

types retrievetypes(int rL) {
	types typesfound;
	
	r_lua_settop(rL, 0);
	r_lua_pushnil(rL);
	typesfound.nil = r_lua_type(rL, -1);

	r_lua_settop(rL, 0);
	r_lua_getfield(rL, -10002, "warn");
	typesfound.function = r_lua_type(rL, -1);

	r_lua_settop(rL, 0);
	r_lua_pushlstring(rL, "a", 1);
	typesfound.string = r_lua_type(rL, -1);

	r_lua_settop(rL, 0);
	r_lua_getfield(rL, -10002, "game");
	r_lua_getfield(rL, -1, "Workspace");
	r_lua_getfield(rL, -1, "FilteringEnabled");
	typesfound.boolean = r_lua_type(rL, -1);

	r_lua_settop(rL, 0);
	r_lua_getfield(rL, -10002, "game");
	r_lua_getfield(rL, -1, "PlaceId");
	typesfound.number = r_lua_type(rL, -1);

	r_lua_settop(rL, 0);
	r_lua_newthread(rL);
	typesfound.thread = r_lua_type(rL, -1);
  
  	r_lua_settop(rL, 0);
  	r_lua_pushlightuserdata(rL, NULL);
  	typesfound.lightuserdata = r_lua_type(rL, -1);
	
	r_lua_settop(rL, 0);
	r_lua_getfield(rL, -10002, "table");
	typesfound.table = r_lua_type(rL, -1);
  
  	r_lua_settop(rL, 0);
  	r_luaF_newproto(rL);
  	typesfound.proto = r_lua_type(rL, -1);
  
  	r_lua_settop(rL, 0);
  	typesfound.none = r_lua_type(rL, -1); //different from nil
  
  	r_lua_settop(rL, 0);
  	return typesfound;
}
