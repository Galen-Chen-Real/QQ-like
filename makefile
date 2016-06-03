all:server_file client_file udp_server udp_grp server client

server_file:fun_trans_file.o server_file.c
	gcc $+ -o $@
client_file:fun_trans_file.o client_file.c
	gcc $+ -o $@
fun_trans_file.o:fun_trans_file.c filetrans.h
	gcc -c $< -o $@
udp_server:udp_server.c
	gcc $+ -o $@
udp_grp:udp_grp.c
	gcc $+ -o $@
server:server.c itoa.o ser_wait_frd.o ser_leav_cli.o ser_mod_usrdat.o ser_read_usrdat.o ser_add_friend.o ser_update.o ser_chat_friend.o ser_leav_ser.o ser_slct_friend.o ser_login_user.o ser_register.o
	gcc $+ -o $@
ser_wait_frd.o:ser_wait_frd.c serheard.h
	gcc -c $< -o $@
ser_leav_cli.o:ser_leav_cli.c serheard.h
	gcc -c $< -o $@
ser_mod_usrdat.o:ser_mod_usrdat.c serheard.h
	gcc -c $< -o $@
ser_read_usrdat.o:ser_read_usrdat.c serheard.h
	gcc -c $< -o $@
ser_add_friend.o:ser_add_friend.c serheard.h
	gcc -c $< -o $@
ser_update.o:ser_update.c serheard.h
	gcc -c $< -o $@
ser_chat_friend.o:ser_chat_friend.c serheard.h
	gcc -c $< -o $@
ser_leav_ser.o:ser_leav_ser.c serheard.h
	gcc -c $< -o $@
ser_slct_friend.o:ser_slct_friend.c serheard.h
	gcc -c $< -o $@
ser_login_user.o:ser_login_user.c serheard.h
	gcc -c $< -o $@
ser_register.o:ser_register.c serheard.h
	gcc -c $< -o $@
client:client.c itoa.o lgn_menu.o chat_group.o chat_friend.o chat_leav_cli.o slct_friend.o login_user.o register_user.o modification.o add_friend.o send_ser_cmd.o
	gcc $+ -o $@
itoa.o:itoa.c
	gcc -c $+ -o $@
lgn_menu.o:lgn_menu.c cliheard.h
	gcc -c $< -o $@
chat_group.o:chat_group.c cliheard.h
	gcc -c $< -o $@
chat_friend.o:chat_friend.c cliheard.h
	gcc -c $< -o $@
chat_leav_cli.o:chat_leav_cli.c cliheard.h
	gcc -c $< -o $@
slct_friend.o:slct_friend.c cliheard.h
	gcc -c $< -o $@
login_user.o:login_user.c cliheard.h
	gcc -c $< -o $@
register_user.o:register_user.c cliheard.h
	gcc -c $< -o $@
modification.o:modification.c cliheard.h
	gcc -c $< -o $@
add_friend.o:add_friend.c cliheard.h
	gcc -c $< -o $@
send_ser_cmd.o:send_ser_cmd.c cliheard.h
	gcc -c $< -o $@
clean:
	rm -f *.o QQ_Pro
