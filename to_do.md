## to_do
* [ ] 마지막에 개행이 없는 경우, %가 붙어야 하는데 어떻게 하지? 줄바꿈이 있는지 확인하는 방법이 있나?
    예를 들어, echo -n test.
    원래 방법으로는 가능했는데, pipe를 쓰게되면서 이거 해결이 다시 필요.
    편법으로 위의 경우는 고칠 수 있으나, echo -n test > test | ./a.out 와 같이 실질적인 해결은 못함.
* [ ] (makefile에 빌트인 함수들은 따로 폴더를 만들까?)
* [ ] signal 처리
	- [x] SIGINT(ctrl + c)
	- [ ] SIGQUIT(ctrl + \)


## norm
* [x] cmd_switch.c: fd 인자때문에 구조 수정 여지 있음.
* [ ] exec_line.c
* [ ] get_args.c
* [x] main.c
* [x] pipe.c
* [x] print_art.c
* [x] print_commandline.c
* [x] semicolon.c


## we_did
20.05.17
* [x] 따옴표 안의 명령어 처리.
* [x] fork로 안되는 함수(cd, export, unset, exit ...) 처리.

20.05.18
* [x] triple_char_free() 추가.
* [x] sh_exec(): argv 받도록 수정.
* [x] print_art(): 메모리 누수 수정.
* [x] is_command() 삭제 후 is_same()으로 통일.
* [x] exec_line(): valgrind 에러 수정.
* [x] envs free 추가.

20.05.19
* [x] cd, pwd, clear, env 에러처리
	- cd : 몇 가지 에러 추가
	- pwd : 인자가 2 개 이상인 경우 에러
	- clear : 인자가 2 개 이상인 경우 에러
	- env : 인자가 2 개 이상인 경우 에러
* [x] store_status(): exec_line 함수 마지막에 함수가 종료되면 상태를 그 상태를 저장한다.
					기본적으로 환경변수에 key(?)를 추가하고 wstatus을 value로 넣는다.
					env에서는 출력되지 않게 구현.
* [x] ctrl + d(EOF)
* [x] $? 구현. > export, unset 제외하고 함. 이 녀석들은 추후 에러 찾고 추가할 것.
* [x] export, unset, cd 같이 fork 안하는 함수들도 리다이렉션 되게 수정.
* [x] 에러 처리.
* [x] 그냥 echo만 해도 $?가 139인거 수정.
* [x] echo "$HOME>me" 추가. (다른 특수문자는 아직 추가 안함)
* [x] `> a` 처리.
* [x] `echo hello > a asdf`와 같은 경우 asdf도 인자로 들어가게 수정.